#!/usr/bin/env python3
"""Original PE-only proof for the complete 156B ribbon allocation factory.

Do not infer source exactness from this check; canonical C++17 COFF replay
independently tests the whole body and original relocation fields.
"""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "pe", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD, SIZE = 0x0045E5D0, 156
CALLS = {
    0x2D: 0x0054275D,
    0x4D: 0x0040C080,
    0x56: 0x0040B280,
    0x6A: 0x0045E6D0,
}
HIGHLOW = {0x06: 0x00568957, 0x15: 0x005B25C0}


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    physical = pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    ins = list(decoder.disasm(pe.raw_at(image, base, sections, HEAD, SIZE), HEAD))
    assert len(ins) == 46 and ins[-1].address + ins[-1].size == HEAD + SIZE
    assert (ins[-1].mnemonic, ins[-1].op_str) == ("ret", "8")
    calls = {
        i.address - HEAD: (i.address + i.size + struct.unpack_from("<i", i.bytes, 1)[0]) & 0xFFFFFFFF
        for i in ins if i.size == 5 and i.bytes[0] == 0xE8
    }
    assert calls == CALLS, (calls, CALLS)
    highlow = {
        loc - HEAD: struct.unpack("<I", pe.raw_at(image, base, sections, loc, 4))[0]
        for loc in physical if HEAD <= loc < HEAD + SIZE
    }
    assert highlow == HIGHLOW, (highlow, HIGHLOW)
    assert sum((i.mnemonic, i.op_str) == ("push", "0xb60") for i in ins) == 2
    # The original native direct-constructor callee is *the same* 89B
    # polymorphic group whose actual class vtable and 0xB5C word are attested.
    original_ctor = list(decoder.disasm(pe.raw_at(image, base, sections, 0x0045E6D0, 89), 0x0045E6D0))
    assert len(original_ctor) == 25 and original_ctor[-1].address + original_ctor[-1].size == 0x0045E729
    for pos, destination in CALLS.items():
        print(f"PASS original factory E8 +{pos:#04x} -> {destination:#010x}")
    print("PASS complete original 156B/46 i386, two native allocation/class-auto-zero sizes 0xB60")
    print("PASS two original PE HIGHLOW: EH 0x568957, cookie 0x5B25C0")
    print("PASS authentic original 89B polymorphic ribbon group constructor target")


if __name__ == "__main__":
    verify()
