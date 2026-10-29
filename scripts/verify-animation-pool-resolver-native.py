#!/usr/bin/env python3
"""Independent original-PE audit of the whole 456-byte Animation pool resolver.

This verifies immutable native x86 and physical RTTI evidence; a source
candidate, Ghidra pseudocode or previous handoff is never an exactness oracle.
The maintained C++ source remains NONEXACT until a separately pinned-compiler
whole-function canonical replay including every relocation has passed.
"""
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
from project import verified_target

# All offsets below are original E8 machine-code *instruction* sites, not
# Ghidra guessed function origins or manufactured C++ symbol names.
HEAD = 0x0044CD00
LENGTH = 456
CALLS = {
    0x0044CD0F: 0x00449430,  # value == 0
    0x0044CD2A: 0x004495A0,  # ID & 0xffff
    0x0044CD69: 0x00449490,  # 0x48-byte special lookup group
    0x0044CD80: 0x00447960,  # first by-reference captured ID closure
    0x0044CD88: 0x00446CC0,  # first std::function owner construction
    0x0044CD90: 0x0044A5A0,  # first list predicate search
    0x0044CDA7: 0x0040C300,  # first successful link->node
    0x0044CDC3: 0x00449490,  # group indexed again
    0x0044CDDD: 0x00447960,  # second by-reference captured ID closure
    0x0044CDE5: 0x00446D30,  # second std::function owner construction
    0x0044CDED: 0x0044A5A0,  # second list predicate search
    0x0044CE04: 0x0040C300,  # second successful link->node
    0x0044CE18: 0x004117A0,  # clear rejected by-value ID
    0x0044CE2B: 0x004495A0,  # normal record index masked by 0xffff
    0x0044CE46: 0x004494D0,  # 0x600-byte record subscript
    0x0044CE5B: 0x004117A0,  # clear inactive by-value ID
    0x0044CE77: 0x004494D0,  # record subscript again
    0x0044CE8B: 0x00449460,  # compare record's handle identity
    0x0044CE9C: 0x004117A0,  # clear stale by-value ID
    0x0044CEB8: 0x004494D0,  # final record subscript
}


def original_bytes(original: bytes, address: int, size: int) -> bytes:
    # Parse actual PE32 sections rather than assume a particular file offset.
    nt = struct.unpack_from("<I", original, 0x3C)[0]
    assert original[nt:nt + 4] == b"PE\0\0"
    count = struct.unpack_from("<H", original, nt + 6)[0]
    opt_size = struct.unpack_from("<H", original, nt + 20)[0]
    base = struct.unpack_from("<I", original, nt + 24 + 28)[0]
    rva = address - base
    sections_at = nt + 24 + opt_size
    for i in range(count):
        at = sections_at + i * 40
        _, virtual_size, section_rva, raw_size, raw_at = struct.unpack_from("<8sIIII", original, at)
        if section_rva <= rva and rva + size <= section_rva + max(virtual_size, raw_size):
            off = rva - section_rva
            assert off + size <= raw_size
            return original[raw_at + off:raw_at + off + size]
    raise AssertionError(f"address {address:#x} not in PE raw sections")


def decode(original: bytes, address: int, size: int):
    result = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(original_bytes(original, address, size), address))
    assert result and result[-1].address + result[-1].size == address + size
    return result


def main() -> None:
    image, _ = verified_target()
    insns = decode(image, HEAD, LENGTH)
    assert len(insns) == 141, len(insns)
    assert insns[-1].mnemonic == "ret" and insns[-1].op_str == "4"
    calls = {}
    for inst in insns:
        if len(inst.bytes) == 5 and inst.bytes[0] == 0xE8:
            target = (inst.address + 5 + struct.unpack_from("<i", inst.bytes, 1)[0]) & 0xFFFFFFFF
            calls[inst.address] = target
    assert calls == CALLS, (len(calls), {hex(a): hex(d) for a, d in calls.items() if CALLS.get(a) != d})

    # Actual 16-bit sentinel / ordinary index / active flag / ID identity.
    assert any(x.address == 0x0044CD22 and x.mnemonic == "push" and x.op_str == "0xffff" for x in insns)
    assert any(x.address == 0x0044CD2F and x.mnemonic == "cmp" and x.op_str == "eax, 0xffff" for x in insns)
    assert any(x.address == 0x0044CE4B and x.mnemonic == "movzx" and "+ 0x5f8" in x.op_str for x in insns)
    assert any(x.address == 0x0044CE7C and x.mnemonic == "add" and x.op_str == "eax, 0x4c0" for x in insns)
    # The two different special-list queries share one original native finder.
    assert calls[0x0044CD90] == calls[0x0044CDED] == 0x0044A5A0
    finder = decode(image, 0x0044A5A0, 154)
    assert finder[-1].mnemonic == "ret" and finder[-1].op_str == "0x28"
    # The physical compiler subscripts are 0x48/0x600, not arbitrary guessed
    # struct sizes. Both original native subscript bodies end in ret 4.
    for head, extent, stride in ((0x00449490, 20, "0x48"), (0x004494D0, 23, "0x600")):
        decoded = decode(image, head, extent)
        assert any(x.mnemonic == "imul" and x.op_str.endswith(", " + stride) for x in decoded)
        assert decoded[-1].mnemonic == "ret" and decoded[-1].op_str == "4"
    # The original comparator called from each closure accesses the actual
    # Animation+0x4C0 handle word. Independently corroborate its E8 graph.
    closure = decode(image, 0x00449600, 43)
    assert any(x.mnemonic == "add" and x.op_str.endswith(", 0x4c0") for x in closure)
    assert any(x.mnemonic == "call" and x.op_str == "0x449400" for x in closure)
    comparison = decode(image, 0x00449400, 47)
    assert any(x.mnemonic == "cmp" for x in comparison)
    # These exact names are real bytes embedded in this locked executable's
    # RTTI, not guesses made from C++ or an imported reference repository.
    for address, role in ((0x005B31B0, b"<lambda_2>"), (0x005B3200, b"<lambda_1>")):
        raw = original_bytes(image, address, 120)
        assert role in raw and b"getSprt@SprtCtrlInf" in raw and b"SprtID" in raw
    print("PASS original Animation pool getSprt native 456/456B, 141/141 i386, 20/20 E8 original destinations")
    print("PASS native 0x48 special-slot / 0x600 pooled-record strides, +0x5F8 active, +0x4C0 handle identity")
    print("PASS two distinct original RTTI lambda captures and native 40B std::function call ABI")
    print("Maintained C++ resolver remains NONEXACT; no whole-function byte credit.")


if __name__ == "__main__":
    main()
