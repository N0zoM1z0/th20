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

LIMITED_CASES = {
    627: {
        "index": 145,
        "start": 0x00495580,
        "end": 0x00495636,
        "sha256": "d96ea10c41ab59bb9c8ac91d7300ca628e526129df3fa781f2d655755f4c91e3",
        "calls": [
            (0x00495588, 0x004AAFB0),
            (0x0049559F, 0x0040C300),
            (0x004955B0, 0x00499350),
            (0x004955DF, 0x0047CF60),
            (0x004955F0, 0x0041CA90),
            (0x00495601, 0x00499350),
            (0x0049562B, 0x004CAAD0),
        ],
        "pushes": {
            0x004955BB: "0",
            0x004955BD: "0x1869f",
            0x004955C2: "0",
            0x0049560C: "1",
            0x0049560E: "0",
        },
    },
    628: {
        "index": 146,
        "start": 0x00495636,
        "end": 0x004956EC,
        "sha256": "856fa32d1333be48c1b329ae6fc5e18aa4e0a36272ac575dcecbcc1dcb669080",
        "calls": [
            (0x0049563E, 0x004AAFB0),
            (0x00495655, 0x0040C300),
            (0x00495666, 0x00499350),
            (0x00495695, 0x0047CF60),
            (0x004956A6, 0x0041CA90),
            (0x004956B7, 0x00499350),
            (0x004956E1, 0x004CAAD0),
        ],
        "pushes": {
            0x00495671: "0",
            0x00495673: "0x1869f",
            0x00495678: "0",
            0x004956C2: "1",
            0x004956C4: "0",
        },
    },
}


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
    start = source.index("    const float radius = state.float_argument(0);")
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

    # The paired 627/628 cases use the capped 401B Bullet boss, preserving
    # mode=0, maximum=0x1869f and effects=0, followed by Laser mode=0/arg=1.
    for opcode, case in LIMITED_CASES.items():
        index = selector[opcode - 300]
        assert index == case["index"], (opcode, index)
        assert pointers[index] == case["start"], (opcode, hex(pointers[index]))
        raw = pe.get_data(case["start"] - image_base, case["end"] - case["start"])
        assert len(raw) == 182
        assert hashlib.sha256(raw).hexdigest() == case["sha256"]
        instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, case["start"]))
        assert len(instructions) == 39
        assert instructions[-1].address + instructions[-1].size == case["end"]
        calls = [
            (instruction.address, int(instruction.op_str, 16))
            for instruction in instructions
            if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
        ]
        assert calls == case["calls"], (opcode, calls)
        by_address = {instruction.address: instruction for instruction in instructions}
        for address, operand in case["pushes"].items():
            instruction = by_address[address]
            assert instruction.mnemonic == "push" and instruction.op_str == operand, (
                opcode, hex(address), instruction.mnemonic, instruction.op_str
            )

    limited_order = [
        "state.float_argument(0)",
        "state.context->bullet_controller()",
        "state.position_ref()",
        "bullets->cancel_near_limited(bullet_center, radius, 0, 0x1869f, 0)",
        "state.context->laser_controller()",
        "state.position_ref()",
        "lasers->cancel_near(laser_center, radius, 0, 1)",
    ]
    cursor = 0
    for item in limited_order:
        position = source.index(item, cursor)
        cursor = position + len(item)
    assert "const bool limited = opcode == 627 || opcode == 628;" in source
    assert "BulletController::cancel_near_limited" in (
        ROOT / "src/BulletLimitedCancellation.cpp"
    ).read_text(encoding="utf8")

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
        "run_limited_radial_cancel_case(627);",
        "run_limited_radial_cancel_case(628);",
        "limited_field_excluded.state == 1",
        "limited_first.flags.fields.effect_mode == 0",
        "opcode628_radius_threw",
        "limited_laser_zero.circle_argument == 1",
    ):
        assert marker in test, marker

    print("PASS original Enemy opcode 616: selector 134, 175B / 37 x86 / 7 ordered E8 calls")
    print("PASS exact native branch SHA-256, call-site map and common dispatcher epilogue")
    print("PASS natural C++ reads radius, then Bullet Context/position/Boss and independent Laser Context/position/Boss")
    print("PASS real Bullet/Laser cancellation Bosses, Context retargeting, live aliased position and Laser virtual filtering regression coverage")
    print("PASS original Enemy opcode 627: selector 145, 182B / 39 x86 / 7 ordered E8 calls")
    print("PASS original Enemy opcode 628: selector 146, 182B / 39 x86 / 7 ordered E8 calls")
    print("PASS native capped Bullet arguments: mode 0, 99,999 maximum, effects 0; Laser mode 0 / argument 1")
    print("PASS natural C++ 627/628 re-read Context and live Enemy position between the real capped Bullet and Laser Bosses")
    print("PASS 627/628 root tests: state/field filters, effect-bit reset, 99,999 limit contract, retargeting and radius exception")
    print("PASS inline fragments only; no standalone unit or 41,967B parent byte credit")


if __name__ == "__main__":
    main()
