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


# The two original game-owned intrusive-list helpers directly called by the
# 456B resolver. All sites/destinations come from immutable original PE.
LINK_SEARCH_BODIES = (
    (0x0044A500, 159, 47,
     {0x0044A542: 0x00449630, 0x0044A55E: 0x00414400,
      0x0044A56B: 0x0040FF90, 0x0044A586: 0x00414400},
     {0x0044A506: 0x0056844D, 0x0044A515: 0x005B25C0}),
    (0x0044A5A0, 154, 46,
     {0x0044A5D2: 0x0040FF90, 0x0044A5DE: 0x0040FF90,
      0x0044A5F2: 0x004140F0, 0x0044A5FA: 0x0044A500,
      0x0044A621: 0x00414400},
     {0x0044A5A6: 0x0056847D, 0x0044A5B5: 0x005B25C0}),
)


def original_highlow_fields(original: bytes) -> set[int]:
    """Read physical IMAGE_REL_BASED_HIGHLOW entries from original PE32."""
    nt = struct.unpack_from("<I", original, 0x3C)[0]
    section_count = struct.unpack_from("<H", original, nt + 6)[0]
    optional_size = struct.unpack_from("<H", original, nt + 20)[0]
    image_base = struct.unpack_from("<I", original, nt + 24 + 28)[0]
    highlow: set[int] = set()
    for index in range(section_count):
        at = nt + 24 + optional_size + 40 * index
        name, _, _, raw_size, raw_offset = struct.unpack_from("<8sIIII", original, at)
        if name.rstrip(b"\0") != b".reloc":
            continue
        data = original[raw_offset:raw_offset + raw_size]
        offset = 0
        while offset + 8 <= len(data):
            page, length = struct.unpack_from("<II", data, offset)
            if length == 0:
                break
            assert 8 <= length <= len(data) - offset
            for field in range(offset + 8, offset + length, 2):
                word = struct.unpack_from("<H", data, field)[0]
                if word >> 12 == 3:
                    highlow.add(image_base + page + (word & 0xFFF))
            offset += length
    assert len(highlow) > 1000
    return highlow


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
    equality_call = next(x for x in closure if x.address == 0x00449620)
    assert equality_call.mnemonic == "call" and equality_call.op_str == "0x449400"
    comparison = decode(image, 0x00449400, 47)
    assert len(comparison) == 16 and any(x.mnemonic == "cmp" for x in comparison)
    assert comparison[-1].mnemonic == "ret" and comparison[-1].op_str == "4"
    # Original 159B predicate-node walker and 154B list wrapper form
    # independently complete native game functions; compare every original
    # E8 call and every PE HIGHLOW field, including true SEH/cookie data.
    highlow = original_highlow_fields(image)
    for head, size, instruction_count, expected_calls, expected_data in LINK_SEARCH_BODIES:
        helper = decode(image, head, size)
        assert len(helper) == instruction_count and helper[-1].mnemonic == "ret"
        observed_calls = {
            insn.address: (insn.address + 5 + struct.unpack_from("<i", insn.bytes, 1)[0]) & 0xFFFFFFFF
            for insn in helper if len(insn.bytes) == 5 and insn.bytes[0] == 0xE8
        }
        assert observed_calls == expected_calls, (hex(head), observed_calls)
        observed_highlow = {at for at in highlow if head <= at < head + size}
        assert observed_highlow == set(expected_data), (hex(head), observed_highlow)
        for field, physical_target in expected_data.items():
            assert struct.unpack("<I", original_bytes(image, field, 4))[0] == physical_target
        print(f"PASS original Animation link search {head:#010x}: {size}/{size}B, "
              f"{instruction_count}/{instruction_count} x86, {len(expected_calls)} native E8, "
              f"{len(expected_data)} true PE HIGHLOW")

    # The actual 26-byte original lambda constructor copies four ID value
    # bytes from the argument pointer *into* the closure object. It is not
    # a source expression that only stores an external reference pointer.
    closure_constructor = decode(image, 0x00447960, 26)
    assert len(closure_constructor) == 12
    assert any(x.address == 0x0044796A and x.mnemonic == "mov"
               and x.op_str == "ecx, dword ptr [eax]" for x in closure_constructor)
    assert any(x.address == 0x0044796F and x.mnemonic == "mov"
               and x.op_str == "dword ptr [edx], ecx" for x in closure_constructor)

    # Both physically distinct original RTTI lambda types share a single
    # original _Do_call implementation and one physical 43B operator() body.
    # Verify real PE32 relocated original vtables, not Ghidra names.
    for table in (0x0056E600, 0x0056E61C):
        assert table + 8 in highlow
        assert struct.unpack("<I", original_bytes(image, table + 8, 4))[0] == 0x0044B3D0
    shared_invoker = decode(image, 0x0044B3D0, 41)
    assert any(x.address == 0x0044B3EB and x.op_str == "0x447920"
               for x in shared_invoker if x.mnemonic == "call")
    forwarding_call = decode(image, 0x00447920, 17)
    assert any(x.mnemonic == "call" and x.op_str == "0x449600" for x in forwarding_call)
    original_lambda = decode(image, 0x00449600, 43)
    assert len(original_lambda) == 15
    observed_lambda_calls = {
        x.address: (x.address + 5 + struct.unpack_from("<i", x.bytes, 1)[0]) & 0xFFFFFFFF
        for x in original_lambda if len(x.bytes) == 5 and x.bytes[0] == 0xE8
    }
    assert observed_lambda_calls == {0x0044960C: 0x0040C300, 0x00449620: 0x00449400}
    assert original_lambda[-1].mnemonic == "ret" and original_lambda[-1].op_str == "4"
    print("PASS original by-value SprtID lambda capture, two real PE vtables sharing one 43B predicate body")
    print("PASS original 43B/15 x86 lambda uses 0x0040C300 node +0x00449400 SprtID equality calls")

    # These exact names are real bytes embedded in this locked executable's
    # RTTI, not guesses made from C++ or an imported reference repository.
    for address, role in ((0x005B31B0, b"<lambda_2>"), (0x005B3200, b"<lambda_1>")):
        raw = original_bytes(image, address, 120)
        assert role in raw and b"getSprt@SprtCtrlInf" in raw and b"SprtID" in raw
    print("PASS original Animation pool getSprt native 456/456B, 141/141 i386, 20/20 E8 original destinations")
    print("PASS native 0x48 special-slot / 0x600 pooled-record strides, +0x5F8 active, +0x4C0 handle identity")
    print("PASS two distinct original RTTI lambda captures and native 40B std::function call ABI")
    print("PASS original 0x00449620 E8 to complete 47B/16-instruction SprtID-by-reference equality")
    print("Original PE verifier is independent of the pinned canonical C++ replay; see animation_pool_resolve_handle_whole_456.")


if __name__ == "__main__":
    main()
