#!/usr/bin/env python3
"""Check entire immutable original 76B ribbon LINESTRIP rendering wrapper."""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "original", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD, SIZE = 0x0045EAC0, 76
CALLS = {0x19: 0x00414580, 0x24: 0x0040BDA0, 0x40: 0x0043D1A0}
DATA = {0x3C: 0x005C0028}
PARENT_CALL = 0x0045EAA4


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    highlow = pe.physical_highlow(image, base, sections)
    instructions = list(decoder.disasm(pe.raw_at(image, base, sections, HEAD, SIZE), HEAD))
    assert len(instructions) == 27 and instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "4")
    calls = {
        ins.address - HEAD: (ins.address + ins.size + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    assert calls == CALLS, (calls, CALLS)
    absolute = {
        pos - HEAD: struct.unpack("<I", pe.raw_at(image, base, sections, pos, 4))[0]
        for pos in highlow if HEAD <= pos < HEAD + SIZE
    }
    assert absolute == DATA, (absolute, DATA)
    assert any((ins.mnemonic, ins.op_str) == ("add", "eax, 0x1e0") for ins in instructions)
    assert any((ins.mnemonic, ins.op_str) == ("push", "0x3c") for ins in instructions)
    original_parent = pe.raw_at(image, base, sections, PARENT_CALL, 5)
    assert original_parent[0] == 0xE8
    destination = (PARENT_CALL + 5 + struct.unpack_from("<i", original_parent, 1)[0]) & 0xFFFFFFFF
    assert destination == HEAD
    for pos, target in CALLS.items():
        print(f"PASS original 76B E8 +{pos:#04x} -> {target:#010x}")
    print("PASS original 76B/27 i386, +0x1E0 colors, count60, RET4")
    print("PASS single original PE HIGHLOW +0x3C -> animation pool 0x005C0028")
    print(f"PASS parent draw 156B E8 {PARENT_CALL:#010x} -> original 76B segment renderer")


if __name__ == "__main__":
    verify()
