#!/usr/bin/env python3
"""Verify the original 32-byte Animation flag-bit clear leaf."""
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
ADDRESS = 0x00472A10
SIZE = 32
EXPECTED = bytes.fromhex(
    "55 8b ec 51 89 4d fc 8b 45 fc 8a 88 9a 04 00 00 "
    "80 e1 fe 8b 55 fc 88 8a 9a 04 00 00 8b e5 5d c3")


def main():
    image, _ = pe.verified_target()
    assert hashlib.sha256(image).hexdigest() == EXPECTED_SHA256
    base, sections = pe.parse_sections(image)
    raw = pe.raw_at(image, base, sections, ADDRESS, SIZE)
    assert raw == EXPECTED
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, ADDRESS))
    assert len(ins) == 12
    assert ins[5].op_str == "cl, byte ptr [eax + 0x49a]"
    assert ins[6].op_str == "cl, 0xfe"
    assert ins[8].op_str == "byte ptr [edx + 0x49a], cl"
    assert ins[-1].mnemonic == "ret" and ins[-1].op_str == ""
    source = (ROOT / "src/AnimationClearFlag02.cpp").read_text()
    assert "base.flags.bits_02.bit_10 = 0;" in source
    print("PASS original Animation+0x49A bit-zero clear: 32B/12 i386, no calls/relocations")
    print("PASS source uses the natural AnimationFlagByte02::bit_10 C++ bitfield assignment")
    print("NOTE isolated helper origin remains unknown; no authored match credit is inferred")


if __name__ == "__main__":
    main()
