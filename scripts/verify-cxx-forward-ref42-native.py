#!/usr/bin/env python3
"""Independent immutable-PE proof for the full 42B forwarded-reference slot.

Only original x86 instructions/relocations/caller edges are used; the C++
source and COFF reproduction are compared by the separate canonical oracle.
"""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
module = importlib.util.spec_from_file_location(
    "original_pe", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
original_pe = importlib.util.module_from_spec(module)
module.loader.exec_module(original_pe)
HEAD = 0x0045ECC0
SIZE = 42
FOLDED_HELPER = 0x0040B280
CALLER = 0x0045EE77


def verify():
    image, _ = original_pe.verified_target()
    base, sections = original_pe.parse_sections(image)
    highlow = original_pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    code = original_pe.raw_at(image, base, sections, HEAD, SIZE)
    instructions = list(decoder.disasm(code, HEAD))
    assert instructions and instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "4")
    calls = {
        ins.address - HEAD: (ins.address + ins.size + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    assert calls == {0x0B: FOLDED_HELPER, 0x14: FOLDED_HELPER}, calls
    assert not any(HEAD <= address < HEAD + SIZE for address in highlow)
    meaningful_stores = [(ins.mnemonic, ins.op_str) for ins in instructions]
    assert ("mov", "dword ptr [ecx], eax") in meaningful_stores
    assert ("mov", "eax, dword ptr [ebp - 4]") in meaningful_stores
    raw_call = original_pe.raw_at(image, base, sections, CALLER, 5)
    assert raw_call[0] == 0xE8
    destination = (CALLER + 5 + struct.unpack_from("<i", raw_call, 1)[0]) & 0xFFFFFFFF
    assert destination == HEAD, (hex(CALLER), hex(destination))
    print(f"PASS original 0x{HEAD:08X}: complete {SIZE}B/{len(instructions)} i386, RET 4")
    print(f"PASS two original E8 at +0x0B/+0x14 to {FOLDED_HELPER:#010x}, zero HIGHLOW")
    print(f"PASS original parent E8 at {CALLER:#010x} -> {HEAD:#010x}")


if __name__ == "__main__":
    verify()
