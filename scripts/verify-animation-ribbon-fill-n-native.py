#!/usr/bin/env python3
"""Attest two complete original unsigned-count C++20 fill_n bodies.

The target-only verification separately checks actual native branch signedness,
call/relocation roles, full function extent and real 31B forwarding callers.
Source/COFF equality is a separate strict canonical replay gate.
"""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "original_target", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
# (head, size, instruction count, original full E8 instruction sites/destinations,
#  original physical DIR32 fields/destinations, unsigned native branch offsets,
#  one true parent wrapper's original E8 instruction address)
BODIES = (
    (
        0x0045D430, 123, 45,
        {0x24: 0x0040B2A0, 0x2F: 0x00411170, 0x62: 0x004185E0,
         0x72: 0x005429EE},
        {0x07: 0x005B25C0}, (0x1A, 0x4C), 0x0045DD31,
    ),
    (
        0x0045D360, 202, 73,
        {0x28: 0x0040B2A0, 0x33: 0x00411170, 0x43: 0x0045D270,
         0x5A: 0x00425320, 0x76: 0x004185E0,
         0xB1: 0x004185E0, 0xC1: 0x005429EE},
        {0x07: 0x005B25C0}, (0x1A, 0x9B), 0x0045DD11,
    ),
)


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    relocations = pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    for head, size, instruction_count, expected_calls, expected_data, unsigned_jumps, caller in BODIES:
        instructions = list(decoder.disasm(pe.raw_at(image, base, sections, head, size), head))
        assert len(instructions) == instruction_count, (hex(head), len(instructions))
        assert instructions[-1].address + instructions[-1].size == head + size
        assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "")
        calls = {
            ins.address - head: (ins.address + 5 + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
            for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
        }
        data = {
            location - head: struct.unpack("<I", pe.raw_at(image, base, sections, location, 4))[0]
            for location in relocations if head <= location < head + size
        }
        assert calls == expected_calls, (hex(head), calls, expected_calls)
        assert data == expected_data, (hex(head), data, expected_data)
        at = {ins.address - head: ins for ins in instructions}
        for offset in unsigned_jumps:
            assert at[offset].mnemonic == "jbe", (hex(head), hex(offset), at[offset].mnemonic)
        parent = pe.raw_at(image, base, sections, caller, 5)
        assert parent[0] == 0xE8, hex(caller)
        destination = (caller + 5 + struct.unpack_from("<i", parent, 1)[0]) & 0xFFFFFFFF
        assert destination == head, (hex(caller), hex(destination), hex(head))
        print(f"PASS original {head:#010x}: complete {size}B/{instruction_count} x86, {len(calls)} E8, {len(data)} HIGHLOW")
        print(f"PASS native UNSIGNED jbe at {[hex(o) for o in unsigned_jumps]}, original forwarding E8 {caller:#010x}")
        for offset, target in calls.items():
            print(f"PASS original {head:#010x} E8 +{offset:#05x} -> {target:#010x}")
        for offset, target in data.items():
            print(f"PASS original {head:#010x} HIGHLOW +{offset:#05x} -> {target:#010x}")
    print("NOTE source/template origin review remains separate from authored-game exact credit")


if __name__ == "__main__":
    verify()
