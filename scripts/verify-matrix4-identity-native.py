#!/usr/bin/env python3
"""Verify the original 452-byte Matrix4 identity helper and natural source order."""
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
ADDRESS = 0x00472840
SIZE = 452
ZERO_ORDER = [(3,2),(3,1),(3,0),(2,3),(2,1),(2,0),
              (1,3),(1,2),(1,0),(0,3),(0,2),(0,1)]
ONE_ORDER = [(3,3),(2,2),(1,1),(0,0)]


def main():
    image, _ = pe.verified_target()
    assert hashlib.sha256(image).hexdigest() == EXPECTED_SHA256
    base, sections = pe.parse_sections(image)
    raw = pe.raw_at(image, base, sections, ADDRESS, SIZE)
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, ADDRESS))
    assert len(ins) == 117
    assert ins[-1].mnemonic == "ret" and ins[-1].op_str == ""
    assert sum(i.mnemonic == "xorps" and i.op_str == "xmm0, xmm0" for i in ins) == 12
    constants = [i for i in ins if i.mnemonic == "movss" and i.op_str == "xmm0, dword ptr [0x56c8cc]"]
    assert [i.address - ADDRESS for i in constants] == [0x154,0x172,0x192,0x1b2]
    stores = [i for i in ins if i.mnemonic == "movss" and i.op_str.endswith(", xmm0")]
    assert len(stores) == 16
    assert not any(i.mnemonic == "call" for i in ins)

    source = (ROOT / "src/Matrix4Identity.cpp").read_text()
    expected = [f"output->elements[{r}][{c}] = 0.0f;" for r,c in ZERO_ORDER]
    expected += [f"output->elements[{r}][{c}] = 1.0f;" for r,c in ONE_ORDER]
    positions = [source.index(line) for line in expected]
    assert positions == sorted(positions)
    assert source.count("output->elements[") == 16
    print("PASS original Matrix4 identity helper: 452B/117 i386, 16 scalar stores, 4 DIR32 constant references")
    print("PASS source restores the original 12-zero reverse row/column order then 4 diagonal ones")
    print("NOTE generic matrix helper origin remains unknown; no authored match credit is inferred")


if __name__ == "__main__":
    main()
