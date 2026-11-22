#!/usr/bin/env python3
"""Verify the original Enemy ECL opcode-712 bullet-rectangle cancellation case."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE_PATH = ROOT / "src/EnemyStateBulletCancelOpcode.cpp"

pe_bytes = PE_PATH.read_bytes()
assert hashlib.sha256(pe_bytes).hexdigest() == (
    "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
)
pe = pefile.PE(data=pe_bytes, fast_load=True)
image_base = pe.OPTIONAL_HEADER.ImageBase
selector = pe.get_data(0x004966B8 - image_base, 704)
pointer_table = pe.get_data(0x00496400 - image_base, 174 * 4)
pointers = struct.unpack("<174I", pointer_table)
unique = sorted(set(pointers))
ends = {
    start: unique[index + 1] if index + 1 < len(unique) else 0x004963DF
    for index, start in enumerate(unique)
}

opcode = 712
selector_index = selector[opcode - 300]
start = pointers[selector_index]
end = ends[start]
body = pe.get_data(start - image_base, end - start)
instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(body, start))
call_sites = [
    (instruction.address, int(instruction.op_str, 16))
    for instruction in instructions
    if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
]
expected_call_sites = [
    (0x00495413, 0x00422E10),  # Vector3 temporary
    (0x00495420, 0x004AAFB0),  # float operand 0
    (0x00495433, 0x004AAFB0),  # float operand 1
    (0x00495455, 0x0048BCE0),  # EnemyAnimationLink vector[0]
    (0x0049545C, 0x0044CED0),  # AnimationHandle::resolve
    (0x00495473, 0x0040C300),  # Context primary-owner word getter
    (0x00495484, 0x00437930),  # Animation::rotation_z_value
    (0x00495495, 0x00499350),  # EnemyState::position_ref
    (0x004954C6, 0x0047CC90),  # BulletController::cancel_in_rectangle
]
expected_calls = [
    0x00422E10,  # Vector3 temporary
    0x004AAFB0,  # float operand 0
    0x004AAFB0,  # float operand 1
    0x0048BCE0,  # EnemyAnimationLink vector[0]
    0x0044CED0,  # AnimationHandle::resolve
    0x0040C300,  # Context primary-owner word getter
    0x00437930,  # Animation::rotation_z_value
    0x00499350,  # EnemyState::position_ref
    0x0047CC90,  # BulletController::cancel_in_rectangle
]
assert selector_index == 164, selector_index
assert start == 0x0049540D and end == 0x004954D1, (hex(start), hex(end))
assert len(body) == 196, len(body)
assert hashlib.sha256(body).hexdigest() == (
    "d7fe973dc2a13c2a161ca9e99220b46579422719db4eae024fac9edce9bfd0f9"
)
assert len(instructions) == 42, len(instructions)
assert instructions[-1].address + instructions[-1].size == end
assert call_sites == expected_call_sites, [
    (hex(address), hex(target)) for address, target in call_sites
]
assert [target for _, target in call_sites] == expected_calls

source = SOURCE_PATH.read_text()
ordered = [
    "state.float_argument(0)",
    "state.float_argument(1)",
    "state.animations[0]",
    ".handle.resolve()",
    "state.context->bullet_controller()",
    "animation->rotation_z_value()",
    "state.position_ref()",
    "cancel_in_rectangle(center, dimensions, direction, 1, 0)",
]
positions = [source.index(fragment) for fragment in ordered]
assert positions == sorted(positions), positions
assert "if (opcode != 712) return false;" in source
for forbidden in ("__asm", "__declspec(naked)", "_emit", "__nop"):
    assert forbidden not in source

print(
    "PASS original Enemy opcode 712: selector 164, 196B / 42 x86 / 9 ordered E8"
)
print(
    "PASS nine original E8 call sites and targets, in exact address/order: Vector3, float 0/1, animation link/resolve, "
    "Context Bullet owner, rotation, Enemy position and 707B rectangle-cancel Boss"
)
print(
    "PASS natural-C++ opcode 712 fragment preserves operand/handle/owner/rotation/"
    "position/cancellation order; parent remains inline and NONEXACT"
)
