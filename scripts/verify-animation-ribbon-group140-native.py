#!/usr/bin/env python3
"""Immutable original-PE proof for the ribbon group native update and vtable.

Evidence only: authentic i386 body, native E8 destinations, .reloc and vtable.
Do not infer exact C++ from this check; use the separate canonical COFF gate.
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
HEAD, SIZE, N_X86 = 0x0045E770, 140, 46
CALLS = {
    0x12: 0x0045D030,  # timer change predicate (nominal C++ owner pending)
    0x27: 0x0040BDA0,  # folded begin/address ref
    0x32: 0x0045ECA0,  # genuine one-past-end pointer helper
    0x5C: 0x004379C0,  # whole-exact Animation::scale_x_value
    0x68: 0x0045E800,  # separate 538B segment dynamics Boss
    0x81: 0x00423540,  # Timer postfix increment
}
VTABLE = 0x0056EDDC
VTABLE_ENTRIES = (
    0x0045E730, HEAD, 0x0045EA20,
    0x00412540, 0x00414B50, 0x00414B50,
)


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    highlow = pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    raw = pe.raw_at(image, base, sections, HEAD, SIZE)
    instructions = list(decoder.disasm(raw, HEAD))
    assert len(instructions) == N_X86
    assert instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "")
    observed_calls = {
        ins.address - HEAD: (ins.address + ins.size + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    assert observed_calls == CALLS, (observed_calls, CALLS)
    assert not any(HEAD <= addr < HEAD + SIZE for addr in highlow)
    assert ("add", "ecx, 0x3c0") in [(ins.mnemonic, ins.op_str) for ins in instructions]
    assert sum(ins.mnemonic == "add" and "0xb4c" in ins.op_str for ins in instructions) == 2
    entries = struct.unpack("<6I", pe.raw_at(image, base, sections, VTABLE, 24))
    assert entries == VTABLE_ENTRIES, entries
    assert all(VTABLE + i * 4 in highlow for i in range(6)), "vtable PE HIGHLOW is not physical"
    # End accessor must be a separate complete original body, not inlined or
    # a single synthetic constant pasted into this parent.
    end = 0x0045ECA0
    original_end = list(decoder.disasm(pe.raw_at(image, base, sections, end, 19), end))
    assert len(original_end) == 9 and original_end[-1].address + original_end[-1].size == end + 19
    assert ("add", "eax, 0xb40") in [(ins.mnemonic, ins.op_str) for ins in original_end]
    for offset, target in CALLS.items():
        print(f"PASS original 140B E8 +{offset:#04x} -> {target:#010x}")
    print("PASS original 140B/46 i386 update: six native E8, zero HIGHLOW, 0x3C0 stride, Timer+0xB4C")
    print("PASS original 0x56EDDC vtable: delete/update/draw plus three inherited methods; all PE HIGHLOW")
    print("PASS original one-past-end +0xB40: 19B/9 i386, separate native body")


if __name__ == "__main__":
    verify()
