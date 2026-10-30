#!/usr/bin/env python3
"""Original-only physical verification of the entire 538B ribbon dynamics Boss.

Checks complete i386 function extent and native PE relocation/call roles;
independent locked-compiler COFF acceptance belongs to canonical replay.
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
HEAD, SIZE = 0x0045E800, 538
E8 = {
    0x034: 0x0040BDA0,
    0x03F: 0x0045DCA0,
    0x069: 0x004298E0,
    0x110: 0x00429210,
    0x11F: 0x0040BDA0,
    0x12A: 0x0045DCC0,
    0x162: 0x00414580,
    0x173: 0x004292E0,
    0x195: 0x00439330,
    0x1BE: 0x004530C0,
    0x1DC: 0x0045D670,
    0x1F7: 0x0045D670,
    0x20C: 0x005429EE,
}
HIGHLOW = {
    0x01A: 0x005B25C0,
    0x065: 0x005BA4C4,
    0x07A: 0x0056C8D0,
    0x0A9: 0x0056C8E0,
    0x0C2: 0x0056C8E0,
    0x0D8: 0x0056C8E0,
    0x0ED: 0x0056C8E0,
    0x1A1: 0x0056E0F0,
    0x1A9: 0x0056C8D0,
    0x1B1: 0x0056EE48,
}
CONSTANTS = {
    0x0056C8D0: 2.0,
    0x0056C8E0: 4.0,
    0x0056EE48: 59.0,
}
PARENT_UPDATE_E8 = 0x0045E7D8


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    highlow = pe.physical_highlow(image, base, sections)
    cs = Cs(CS_ARCH_X86, CS_MODE_32)
    raw = pe.raw_at(image, base, sections, HEAD, SIZE)
    instructions = list(cs.disasm(raw, HEAD))
    assert len(instructions) == 149, len(instructions)
    assert instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "4")
    calls = {
        ins.address - HEAD: (ins.address + ins.size + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    assert calls == E8, (calls, E8)
    native_fields = {
        loc - HEAD: struct.unpack("<I", pe.raw_at(image, base, sections, loc, 4))[0]
        for loc in highlow if HEAD <= loc < HEAD + SIZE
    }
    assert native_fields == HIGHLOW, (native_fields, HIGHLOW)
    by_offset = {ins.address - HEAD: (ins.mnemonic, ins.op_str) for ins in instructions}
    assert by_offset[0x115] == ("nop", "")
    assert ("push", "0x3b") in by_offset.values(), "closure must use last point 59"
    assert ("add", "ecx, 4") in by_offset.values(), "radii array stride must be 4"
    assert ("add", "edx, 8") in by_offset.values(), "point array stride must be 8"
    assert any(op == "comiss" for op, _ in by_offset.values()), "native scalar bounds missing"
    for address, value in CONSTANTS.items():
        actual = struct.unpack("<f", pe.raw_at(image, base, sections, address, 4))[0]
        assert actual == value, (hex(address), actual, value)
    parent = pe.raw_at(image, base, sections, PARENT_UPDATE_E8, 5)
    assert parent[0] == 0xE8
    dest = (PARENT_UPDATE_E8 + 5 + struct.unpack_from("<i", parent, 1)[0]) & 0xFFFFFFFF
    assert dest == HEAD, (hex(PARENT_UPDATE_E8), hex(dest))
    for offset, target in E8.items():
        print(f"PASS original E8 +{offset:#05x} -> {target:#010x}")
    for offset, target in HIGHLOW.items():
        print(f"PASS original HIGHLOW +{offset:#05x} -> {target:#010x}")
    print("PASS complete original 538B/149 i386, 13 E8 +10 HIGHLOW, authentic +0x115 NOP")
    print("PASS physical 60-element radii/points, four/eight-byte strides, 59 closure")
    print(f"PASS original 140B parent E8 {PARENT_UPDATE_E8:#010x} -> {HEAD:#010x}")


if __name__ == "__main__":
    verify()
