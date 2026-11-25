#!/usr/bin/env python3
"""Verify four original Animation callback/lifecycle leaf bodies and callers."""
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
LEAVES = {
    "copy_base": (0x004371F0, 34, 14, {0x14: 0x00543E20}),
    "clear_pending_fields": (0x00429E30, 32, 14, {0x0C: 0x00438A50, 0x16: 0x00438A30}),
    "clear_field_570": (0x00429E50, 24, 9, {}),
    "set_field_5e0": (0x00438A30, 25, 10, {}),
    "set_field_5dc": (0x00438A50, 25, 10, {}),
}

def decode(image, base, sections, address, size):
    raw = pe.raw_at(image, base, sections, address, size)
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
    assert ins and ins[0].address == address
    assert ins[-1].address + ins[-1].size == address + size
    return ins

def e8_targets(ins, base):
    return {i.address - base: (i.address + i.size + int(i.op_str, 16) - (i.address + i.size)) & 0xFFFFFFFF
            for i in ins if i.mnemonic == "call" and i.op_str.startswith("0x")}

def main():
    image, _ = pe.verified_target()
    assert hashlib.sha256(image).hexdigest() == EXPECTED_SHA256
    base, sections = pe.parse_sections(image)
    for name, (address, size, instruction_count, expected_calls) in LEAVES.items():
        ins = decode(image, base, sections, address, size)
        assert len(ins) == instruction_count, (name, len(ins), instruction_count)
        assert ins[-1].mnemonic == "ret", (name, ins[-1].mnemonic)
        calls = e8_targets(ins, address)
        assert calls == expected_calls, (name, calls, expected_calls)
        print(f"PASS original {name}: {size}B/{instruction_count} i386, E8={len(calls)}")

    pending = decode(image, base, sections, 0x00429E30, 32)
    assert pending[4].bytes == bytes.fromhex("6a00")
    assert pending[5].op_str == "ecx, dword ptr [ebp - 4]"
    assert pending[6].mnemonic == "call" and pending[6].op_str == "0x438a50"
    assert pending[7].bytes == bytes.fromhex("6a00")
    assert pending[9].mnemonic == "call" and pending[9].op_str == "0x438a30"

    clear = decode(image, base, sections, 0x00429E50, 24)
    assert clear[5].mnemonic == "mov"
    assert clear[5].op_str == "dword ptr [eax + 0x570], 0"

    setter_5e0 = decode(image, base, sections, 0x00438A30, 25)
    setter_5dc = decode(image, base, sections, 0x00438A50, 25)
    assert setter_5e0[6].op_str == "dword ptr [eax + 0x5e0], ecx"
    assert setter_5dc[6].op_str == "dword ptr [eax + 0x5dc], ecx"
    assert setter_5e0[-1].op_str == "4" and setter_5dc[-1].op_str == "4"

    copy_base = decode(image, base, sections, 0x004371F0, 34)
    assert copy_base[4].op_str == "0x4c0"
    assert copy_base[5].op_str == "eax, dword ptr [ebp + 8]"
    assert copy_base[7].op_str == "ecx, dword ptr [ebp - 4]"
    assert copy_base[9].mnemonic == "call" and copy_base[9].op_str == "0x543e20"
    assert copy_base[-1].op_str == "4"

    # The original AnimationFile template path clears the lifecycle word and
    # then both callback fields before copying the template's 0x5e4-byte base.
    apply = decode(image, base, sections, 0x00438B70, 84)
    assert e8_targets(apply, 0x00438B70).get(0x0A) == 0x00429E50
    assert e8_targets(apply, 0x00438B70).get(0x12) == 0x00429E30
    assert e8_targets(apply, 0x00438B70).get(0x28) == 0x004371F0
    assert apply[8].bytes == bytes.fromhex("69450ce4050000")
    assert apply[10].op_str == "eax, dword ptr [ecx + 0x40]"
    # The original pool allocation/reuse path clears callbacks in both the
    # recycled-node and fresh-allocation branches.
    allocate = decode(image, base, sections, 0x0044C9B0, 298)
    allocate_calls = e8_targets(allocate, 0x0044C9B0)
    assert allocate_calls.get(0x6C) == 0x00429E30
    assert allocate_calls.get(0x111) == 0x00429E30
    print("PASS original AnimationFile::apply_template clears lifecycle/callback state then copies the selected 0x5e4-stride template")
    print("PASS original AnimationPoolOwner::allocate_animation clears callbacks on both paths")
    print("PASS setter receiver/stack ABI and exact +0x5dc/+0x5e0 member stores")

if __name__ == "__main__":
    main()
