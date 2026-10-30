#!/usr/bin/env python3
"""Independent original-PE verification for complete 156B ribbon draw Boss."""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "original_pe", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD, SIZE = 0x0045EA20, 156
CALLS = {
    0x20: 0x00445BC0,
    0x28: 0x00422E10,
    0x3D: 0x004376E0,
    0x4F: 0x0040BDA0,
    0x5A: 0x0045ECA0,
    0x84: 0x0045EAC0,
    0x93: 0x005429EE,
}
HIGHLOW = {0x07: 0x005B25C0, 0x1C: 0x005C0028}


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    highlow = pe.physical_highlow(image, base, sections)
    instructions = list(decoder.disasm(pe.raw_at(image, base, sections, HEAD, SIZE), HEAD))
    assert len(instructions) == 53, len(instructions)
    assert instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "")
    calls = {
        ins.address - HEAD: (ins.address + ins.size + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    assert calls == CALLS, (calls, CALLS)
    absolute_fields = {
        pos - HEAD: struct.unpack("<I", pe.raw_at(image, base, sections, pos, 4))[0]
        for pos in highlow if HEAD <= pos < HEAD + SIZE
    }
    assert absolute_fields == HIGHLOW, (absolute_fields, HIGHLOW)
    body = {(ins.address - HEAD): (ins.mnemonic, ins.op_str) for ins in instructions}
    assert body[0x42] == ("nop", ""), body.get(0x42)
    assert ("add", "eax, 0x3c0") in body.values()
    assert 0x0056EDE4 in highlow
    assert struct.unpack("<I", pe.raw_at(image, base, sections, 0x0056EDE4, 4))[0] == HEAD
    for offset, target in CALLS.items():
        print(f"PASS original draw E8 +{offset:#04x} -> {target:#010x}")
    print("PASS whole original 156B/53 i386, native NOP +0x42, 0x3C0 stride")
    print("PASS two actual HIGHLOW fields: 0x5B25C0 cookie, 0x5C0028 pool")
    print("PASS original polymorphic ribbon vtable 0x56EDE4 -> draw at 0x45EA20")


if __name__ == "__main__":
    verify()
