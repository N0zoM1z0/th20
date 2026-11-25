#!/usr/bin/env python3
"""Attest original Animation callback methods and callback-owner leaves."""
from pathlib import Path
import hashlib
import importlib.util
import struct
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
    "Animation::interrupt": (0x004388F0, 79, 26, {}),
    "AnimationCallback::AnimationCallback": (0x00446B60, 57, 20, {0x2A: 0x00446BF0}),
    "AnimationCallback::~AnimationCallback": (0x00446BA0, 20, 9, {}),
    "AnimationCallback::scalar_deleting_destructor": (
        0x00446BC0, 46, 18, {0x0A: 0x00446BA0, 0x1D: 0x0054278D}),
    "Animation::set_callback": (0x00446BF0, 28, 11, {}),
}


def decode(image, base, sections, address, size):
    raw = pe.raw_at(image, base, sections, address, size)
    ins = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
    assert ins and ins[0].address == address
    assert ins[-1].address + ins[-1].size == address + size
    return ins


def direct_calls(ins, base):
    calls = {}
    for item in ins:
        if item.mnemonic == "call" and item.op_str.startswith("0x"):
            calls[item.address - base] = int(item.op_str, 16)
    return calls


def main():
    image, _ = pe.verified_target()
    assert hashlib.sha256(image).hexdigest() == EXPECTED_SHA256
    base, sections = pe.parse_sections(image)
    decoded = {}
    for name, (address, size, instruction_count, expected_calls) in LEAVES.items():
        ins = decode(image, base, sections, address, size)
        assert len(ins) == instruction_count, (name, len(ins), instruction_count)
        assert ins[-1].mnemonic == "ret"
        calls = direct_calls(ins, address)
        assert calls == expected_calls, (name, calls, expected_calls)
        decoded[name] = ins
        print(f"PASS original {name}: {size}B/{instruction_count} i386, E8={len(calls)}")

    # The actual original five-slot callback vtable. Its RTTI name is not
    # asserted to be the maintained source alias AnimationCallback.
    vtable = struct.unpack("<5I", pe.raw_at(image, base, sections, 0x0056E1AC, 20))
    assert vtable == (0x00446BC0, 0x00412540, 0x00412540,
                      0x00412540, 0x00414B50), tuple(hex(x) for x in vtable)

    ctor = decoded["AnimationCallback::AnimationCallback"]
    assert ctor[5].op_str == "dword ptr [eax], 0x56e1ac"
    assert ctor[7].op_str == "dword ptr [ecx + 4], 0"
    assert ctor[10].op_str == "dword ptr [edx + 4], eax"
    assert ctor[14].mnemonic == "call" and ctor[14].op_str == "0x446bf0"
    assert ctor[-1].op_str == "4"

    dtor = decoded["AnimationCallback::~AnimationCallback"]
    assert dtor[5].op_str == "dword ptr [eax], 0x56e1ac"
    assert dtor[-1].mnemonic == "ret" and dtor[-1].op_str == ""

    deleting = decoded["AnimationCallback::scalar_deleting_destructor"]
    assert deleting[5].op_str == "0x446ba0"
    assert deleting[7].op_str == "eax, 1"
    assert deleting[9].op_str == "8"
    assert deleting[12].op_str == "0x54278d"
    assert deleting[-1].op_str == "4"

    setter = decoded["Animation::set_callback"]
    assert setter[6].op_str == "dword ptr [eax + 0x568], ecx"
    assert setter[7].op_str == "eax, dword ptr [ebp + 8]"
    assert setter[-1].op_str == "4"

    interrupt = decoded["Animation::interrupt"]
    assert interrupt[5].op_str == "dword ptr [eax + 0x568], 0"
    assert interrupt[6].mnemonic == "je"
    assert interrupt[13].op_str == "eax, dword ptr [edx + 0x10]"
    assert interrupt[18].op_str == "dword ptr [ebp - 0xc]"
    assert interrupt[22].op_str == "dword ptr [edx + 0x438], eax"
    assert interrupt[-1].op_str == "4"

    print("PASS original callback vtable: deleting dtor + four int-return virtual slots")
    print("PASS constructor publishes Animation+4 and registers this at Animation+0x568")
    print("PASS destructor restores base vtable; scalar deleting path releases exactly 8 bytes")
    print("PASS Animation::set_callback stores +0x568 and returns the incoming pointer")
    print("PASS Animation::interrupt snapshots virtual slot +0x10 before publishing event at +0x438")
    print("NOTE original RTTI spells the callback base SprtFuncBaseInf; AnimationCallback is a maintained semantic alias")


if __name__ == "__main__":
    main()
