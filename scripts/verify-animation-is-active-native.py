#!/usr/bin/env python3
"""Verify the original 42-byte Animation state predicate."""
from pathlib import Path
import hashlib
import importlib.util
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))
spec = importlib.util.spec_from_file_location(
    "animation_native_pe", ROOT / "scripts/verify-animation-draw-boss-native.py")
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
EXPECTED_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
ADDRESS = 0x00474DD0
SIZE = 42
EXPECTED = bytes.fromhex(
    "55 8b ec 83 ec 08 89 4d f8 8b 45 f8 83 78 28 00 "
    "7c 09 c7 45 fc 01 00 00 00 eb 07 c7 45 fc 00 00 "
    "00 00 0f b6 45 fc 8b e5 5d c3")


def main():
    image, _ = pe.verified_target()
    assert hashlib.sha256(image).hexdigest() == EXPECTED_SHA256
    base, sections = pe.parse_sections(image)
    raw = pe.raw_at(image, base, sections, ADDRESS, SIZE)
    assert raw == EXPECTED
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, ADDRESS))
    assert len(ins) == 14
    assert ins[5].op_str == "dword ptr [eax + 0x28], 0"
    assert ins[6].mnemonic == "jl"
    assert ins[7].op_str == "dword ptr [ebp - 4], 1"
    assert ins[8].mnemonic == "jmp"
    assert ins[9].op_str == "dword ptr [ebp - 4], 0"
    assert ins[10].op_str == "eax, byte ptr [ebp - 4]"
    assert ins[-1].mnemonic == "ret" and ins[-1].op_str == ""
    source = (ROOT / "src/AnimationIsActive.cpp").read_text()
    assert "return base.field_28 >= 0;" in source
    print("PASS original Animation state predicate: 42B/14 i386, no calls/relocations")
    print("PASS source returns the signed nonnegative test of AnimationBase+0x28")
    print("NOTE original authored/accessor identity remains unresolved; no authored match credit is inferred")


if __name__ == "__main__":
    main()
