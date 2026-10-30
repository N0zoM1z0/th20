#!/usr/bin/env python3
"""Audit the complete original 44-byte dual-word C++ helper and its callers.

This checks the immutable PE, not an inferred C++ signature or reconstructed
object. A valid original body/call graph is not canonical codegen exactness.
"""
import importlib.util
from pathlib import Path
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "locked_original", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD = 0x0045F310
SIZE = 44
ORIGINAL_CALL = 0x0040B280
CALLERS = (0x0045EE7F, 0x0046B887, 0x0046BAA9, 0x00481129, 0x00483BDC)


def require(condition, message):
    if not condition:
        raise AssertionError(message)


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    highlow = pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    raw = pe.raw_at(image, base, sections, HEAD, SIZE)
    instructions = list(decoder.disasm(raw, HEAD))
    require(len(instructions) == 18, "44B original must have 18 instructions")
    require(instructions[-1].address + instructions[-1].size == HEAD + SIZE,
            "original boundary is not completely decoded")
    require((instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "8"),
            "original constructor ABI must return and pop 8 bytes")
    calls = {
        ins.address - HEAD: (ins.address + 5 + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
        for ins in instructions if ins.size == 5 and ins.bytes[0] == 0xE8
    }
    require(calls == {0x0B: ORIGINAL_CALL}, f"original E8 sites/targets changed: {calls}")
    require(not any(HEAD <= loc < HEAD + SIZE for loc in highlow),
            "unexpected original HIGHLOW within 44B body")

    # Check the real register order and both 32-bit field writes, rather than
    # inferring them from an otherwise similarly sized source candidate.
    at = {ins.address - HEAD: (ins.mnemonic, ins.op_str) for ins in instructions}
    expected = {
        0x13: ("mov", "ecx, dword ptr [eax]"),
        0x15: ("mov", "edx, dword ptr [ebp - 4]"),
        0x18: ("mov", "dword ptr [edx], ecx"),
        0x1D: ("mov", "ecx, dword ptr [ebp + 0xc]"),
        0x20: ("mov", "dword ptr [eax + 4], ecx"),
    }
    for offset, instruction in expected.items():
        require(at.get(offset) == instruction,
                f"original store operand/register ordering changed at +{offset:#x}")

    # This head is a genuine eight-byte folded address/move/forward helper;
    # its original machine code is independently checked, not assigned a
    # unique C++ template name (multiple templates may fold to this code).
    helper = list(decoder.disasm(pe.raw_at(image, base, sections, ORIGINAL_CALL, 8), ORIGINAL_CALL))
    require([(ins.mnemonic, ins.op_str) for ins in helper] == [
        ("push", "ebp"), ("mov", "ebp, esp"),
        ("mov", "eax, dword ptr [ebp + 8]"),
        ("pop", "ebp"), ("ret", "")
    ], "unexpected original folded 8B forwarding/address helper")
    require(helper[-1].address + helper[-1].size == ORIGINAL_CALL + 8,
            "folded helper extent is incomplete")

    for caller in CALLERS:
        original = pe.raw_at(image, base, sections, caller, 5)
        decoded = list(decoder.disasm(original, caller))
        require(len(decoded) == 1 and decoded[0].size == 5 and original[0] == 0xE8,
                f"original E8 instruction missing at {caller:#010x}")
        destination = (caller + 5 + struct.unpack_from("<i", original, 1)[0]) & 0xFFFFFFFF
        require(destination == HEAD, f"unexpected caller target {caller:#010x} -> {destination:#010x}")
        print(f"PASS original caller {caller:#010x} E8 -> {HEAD:#010x}")

    print("PASS native pair44: complete 44B/18 i386, 2 field stores, one E8 to original 8B helper")
    print("PASS original PE: five physical callers, zero in-body HIGHLOW, RET 8")
    print("NOTE compiler candidate still NONEXACT: no accepted unit or authored source credit")


if __name__ == "__main__":
    verify()
