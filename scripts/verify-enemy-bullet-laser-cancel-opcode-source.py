#!/usr/bin/env python3
"""Verify Enemy ECL opcode 616's live Bullet/Laser radial cancellation pair."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStateBulletLaserCancelOpcode.cpp"
ROOT_SOURCE = ROOT / "src/EnemyStateExecuteOpcode.cpp"
CONTEXT_SOURCE = ROOT / "src/Context.cpp"
POSITION_SOURCE = ROOT / "src/MeshInterfaces.cpp"
TEST_SOURCE = ROOT / "tests/enemy_state_dispatch_root.cpp"
BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
OPCODE = 616
START = 0x004954D1
END = 0x00495580
EXPECTED_SHA256 = "f2ea21d098c1ea60855885898a57680558b066fdd2e610ba96fd7e91e1f16c84"
EXPECTED_CALL_SITES = [
    (0x004954D9, 0x004AAFB0),  # EnemyState::float_argument(0)
    (0x004954F0, 0x0040C300),  # Context::bullet_controller (+0 getter body)
    (0x00495501, 0x00499350),  # EnemyState::position_ref
    (0x00495529, 0x0047D100),  # BulletController::cancel_near
    (0x0049553A, 0x0041CA90),  # Context::laser_controller (+0x14 getter body)
    (0x0049554B, 0x00499350),  # re-read EnemyState::position_ref
    (0x00495575, 0x004CAAD0),  # LaserController::cancel_near
]


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    selector = pe.get_data(SELECTOR_TABLE - image_base, 704)
    pointers = struct.unpack("<174I", pe.get_data(POINTER_TABLE - image_base, 696))
    assert selector[OPCODE - 300] == 134
    assert pointers[selector[OPCODE - 300]] == START

    raw = pe.get_data(START - image_base, END - START)
    assert len(raw) == 175
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA256
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, START))
    assert len(instructions) == 37
    calls = [
        (instruction.address, int(instruction.op_str, 16))
        for instruction in instructions
        if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
    ]
    assert calls == EXPECTED_CALL_SITES, [
        (hex(address), hex(target)) for address, target in calls
    ]
    epilogue_jump = next(
        instruction for instruction in instructions if instruction.address == 0x0049557B
    )
    assert epilogue_jump.mnemonic == "jmp"
    assert int(epilogue_jump.op_str, 16) == 0x004963DF

    source = SOURCE.read_text(encoding="utf8")
    start = source.index("    if (opcode != 616)")
    end = source.index("    return true;", start)
    branch = source[start:end]
    order = [
        "state.float_argument(0)",
        "state.context->bullet_controller()",
        "state.position_ref()",
        "bullets->cancel_near(bullet_center, radius, 0)",
        "state.context->laser_controller()",
        "state.position_ref()",
        "lasers->cancel_near(laser_center, radius, 0, 1)",
    ]
    cursor = 0
    for item in order:
        position = branch.index(item, cursor)
        cursor = position + len(item)
    assert branch.count("state.context->") == 2
    assert branch.count("state.position_ref()") == 2

    root = ROOT_SOURCE.read_text(encoding="utf8")
    context = CONTEXT_SOURCE.read_text(encoding="utf8")
    position = POSITION_SOURCE.read_text(encoding="utf8")
    assert "execute_enemy_bullet_laser_cancel_opcode(*this, opcode)" in root
    assert "BulletController* Context::bullet_controller()" in context
    assert "LaserController* Context::laser_controller()" in context
    assert "Vector3& EnemyState::position_ref()" in position

    test = TEST_SOURCE.read_text(encoding="utf8")
    for marker in (
        "retarget_context_player_during_first_float_read",
        "retarget_to_original_and_move_enemy_during_bullet_cancel",
        "bullet_at_retargeted_center.state == 4",
        "bullet_left_at_old_center.state == 1",
        "dispatch_test_bullets_alternate->cancel_counter == 2",
        "laser_state_zero.circle_calls == 1",
        "laser_state_one.circle_calls == 0",
        "laser_state_two.circle_calls == 1",
        "laser_wrong_context.circle_calls == 0",
        "laser_state_zero.circle_argument == 1",
    ):
        assert marker in test, marker

    print("PASS original Enemy opcode 616: selector 134, 175B / 37 x86 / 7 ordered E8 calls")
    print("PASS exact native branch SHA-256, call-site map and common dispatcher epilogue")
    print("PASS natural C++ reads radius, then Bullet Context/position/Boss and independent Laser Context/position/Boss")
    print("PASS real Bullet/Laser cancellation Bosses, Context retargeting, live aliased position and Laser virtual filtering regression coverage")
    print("PASS inline fragment only; no standalone unit or 41,967B parent byte credit")


if __name__ == "__main__":
    main()
