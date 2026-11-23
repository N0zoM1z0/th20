#!/usr/bin/env python3
"""Verify Enemy ECL opcode 629 and its two native EnemyState callback Bosses."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
OPCODE = 629
SELECTOR_INDEX = 147
CASE_START = 0x00490B4D
CASE_END = 0x00490B7B
CASE_SHA256 = "37da451d83dfe772964395e1cab473a5f784646198a6310eb5ca89fd475b3943"
CALLBACK_TABLE = 0x0056FE8C

CALLBACKS = {
    0x00488B80: {
        "end": 0x00488E76,
        "size": 758,
        "extent_end": 0x00488E80,
        "extent_size": 768,
        "extent_sha256": "6e7dc966aa80eb468ac1ea53755f7dfa5b34e80bcb165d0a54b076b41a388f46",
        "tail_padding": 10,
        "instructions": 205,
        "extent_instructions": 215,
        "sha256": "2f66245e6c05e12b15c2b32030a0d23be74dac207e5c6bf0724beffd0c8df3b1",
        "calls": [
            0x0048BCE0,0x0044CED0,0x004379C0,0x004379A0,0x00437930,
            0x0040C300,0x00485970,0x0040C080,0x00412280,0x00412540,
            0x00411C30,0x00411BB0,0x0040C300,0x0040C300,0x00499370,
            0x00499370,0x00499350,0x00499350,0x00457610,0x0049CAE0,
            0x00421810,0x0044FA10,0x0049C760,0x00411B00,0x0040FF90,
            0x00460850,0x0040FF90,0x00460850,0x00499350,0x00499350,
            0x00457610,0x00460830,0x00479080,0x005429EE,
        ],
        "call_sites": [
            (0x00488BB9,0x0048BCE0),(0x00488BC0,0x0044CED0),
            (0x00488BCB,0x004379C0),(0x00488BD6,0x004379A0),
            (0x00488BE1,0x00437930),(0x00488BF2,0x0040C300),
            (0x00488BF9,0x00485970),(0x00488C06,0x0040C080),
            (0x00488C12,0x00412280),(0x00488C21,0x00412540),
            (0x00488C2E,0x00411C30),(0x00488C3B,0x00411BB0),
            (0x00488C4E,0x0040C300),(0x00488C59,0x0040C300),
            (0x00488C64,0x00499370),(0x00488C76,0x00499370),
            (0x00488C87,0x00499350),(0x00488C99,0x00499350),
            (0x00488D02,0x00457610),(0x00488D25,0x0049CAE0),
            (0x00488D2D,0x00421810),(0x00488D3D,0x0044FA10),
            (0x00488D45,0x0049C760),(0x00488D5A,0x00411B00),
            (0x00488D69,0x0040FF90),(0x00488D70,0x00460850),
            (0x00488D88,0x0040FF90),(0x00488D8F,0x00460850),
            (0x00488DA0,0x00499350),(0x00488DB2,0x00499350),
            (0x00488E1B,0x00457610),(0x00488E2C,0x00460830),
            (0x00488E55,0x00479080),(0x00488E6D,0x005429EE),
        ],
    },
    0x00488E80: {
        "end": 0x00488FA3,
        "size": 291,
        "extent_end": 0x00488FA3,
        "extent_size": 291,
        "extent_sha256": "981d4d97b63177f87684ca7a6bb854b32bbe9213f01c5282869be60323d2024b",
        "tail_padding": 0,
        "instructions": 86,
        "extent_instructions": 86,
        "sha256": "981d4d97b63177f87684ca7a6bb854b32bbe9213f01c5282869be60323d2024b",
        "calls": [
            0x0040C300,0x00485970,0x0040C080,0x00412280,0x00412540,
            0x00411C30,0x00411BB0,0x0040C300,0x0040C300,0x0049CAE0,
            0x00421810,0x0044FA10,0x0049C260,0x00411B00,0x00460830,
            0x00479080,0x005429EE,
        ],
        "call_sites": [
            (0x00488EB4,0x0040C300),(0x00488EBB,0x00485970),
            (0x00488EC8,0x0040C080),(0x00488ED4,0x00412280),
            (0x00488EE3,0x00412540),(0x00488EF0,0x00411C30),
            (0x00488EFD,0x00411BB0),(0x00488F0C,0x0040C300),
            (0x00488F17,0x0040C300),(0x00488F30,0x0049CAE0),
            (0x00488F38,0x00421810),(0x00488F45,0x0044FA10),
            (0x00488F4D,0x0049C260),(0x00488F5F,0x00411B00),
            (0x00488F67,0x00460830),(0x00488F83,0x00479080),
            (0x00488F9A,0x005429EE),
        ],
    },
}


TIMER_SETTER = {
    "end": 0x0049CB07,
    "size": 39,
    "instructions": 14,
    "sha256": "1c8c8efe0e3529f45f58dcb33d31b0403d7a1c2392b694805653ee0889249658",
    "calls": [0x0047C5F0],
    "call_sites": [(0x0049CAFB,0x0047C5F0)],
}

def direct_calls(instructions):
    return [
        int(insn.op_str, 16)
        for insn in instructions
        if insn.mnemonic == "call" and insn.op_str.startswith("0x")
    ]


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    selector = pe.get_data(SELECTOR_TABLE - image_base, 704)
    pointers = pe.get_data(POINTER_TABLE - image_base, 174 * 4)
    assert selector[OPCODE - 300] == SELECTOR_INDEX
    assert struct.unpack_from("<I", pointers, SELECTOR_INDEX * 4)[0] == CASE_START

    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    case = pe.get_data(CASE_START - image_base, CASE_END - CASE_START)
    assert len(case) == 46
    assert hashlib.sha256(case).hexdigest() == CASE_SHA256
    case_insns = list(decoder.disasm(case, CASE_START))
    assert len(case_insns) == 10
    assert case_insns[-1].address + case_insns[-1].size == CASE_END
    assert direct_calls(case_insns) == [0x004AB080]
    indirect = [insn for insn in case_insns if insn.mnemonic == "call" and insn.op_str == "edx"]
    assert len(indirect) == 1 and indirect[0].address == 0x00490B73
    by_address = {insn.address: insn for insn in case_insns}
    assert by_address[0x00490B6C].mnemonic == "mov"
    assert "0x56fe8c" in by_address[0x00490B6C].op_str.lower()
    assert by_address[0x00490B73].mnemonic == "call"
    assert by_address[0x00490B73].op_str == "edx"

    callback_words = struct.unpack(
        "<3I", pe.get_data(CALLBACK_TABLE - image_base, 12)
    )
    assert callback_words == (0, 0x00488B80, 0x00488E80), callback_words

    for start, case_data in CALLBACKS.items():
        raw = pe.get_data(start - image_base, case_data["size"])
        assert len(raw) == case_data["size"]
        assert hashlib.sha256(raw).hexdigest() == case_data["sha256"]
        extent = pe.get_data(start - image_base, case_data["extent_size"])
        assert len(extent) == case_data["extent_size"]
        assert hashlib.sha256(extent).hexdigest() == case_data["extent_sha256"]
        extent_insns = list(decoder.disasm(extent, start))
        assert len(extent_insns) == case_data["extent_instructions"]
        tail = extent[case_data["size"]:]
        assert len(tail) == case_data["tail_padding"]
        assert tail == b"\xCC" * case_data["tail_padding"]
        assert start + case_data["extent_size"] == case_data["extent_end"]
        insns = list(decoder.disasm(raw, start))
        assert len(insns) == case_data["instructions"]
        assert insns[-1].address + insns[-1].size == case_data["end"]
        calls = direct_calls(insns)
        assert calls == case_data["calls"], (hex(start), calls)
        call_sites = [
            (insn.address, int(insn.op_str, 16))
            for insn in insns
            if insn.mnemonic == "call" and insn.op_str.startswith("0x")
        ]
        assert call_sites == case_data["call_sites"], (hex(start), call_sites)

    timer_raw = pe.get_data(0x0049CAE0 - image_base, TIMER_SETTER["size"])
    assert len(timer_raw) == TIMER_SETTER["size"]
    assert hashlib.sha256(timer_raw).hexdigest() == TIMER_SETTER["sha256"]
    timer_insns = list(decoder.disasm(timer_raw, 0x0049CAE0))
    assert len(timer_insns) == TIMER_SETTER["instructions"]
    assert timer_insns[-1].address + timer_insns[-1].size == TIMER_SETTER["end"]
    assert direct_calls(timer_insns) == TIMER_SETTER["calls"]
    timer_call_sites = [
        (insn.address, int(insn.op_str, 16))
        for insn in timer_insns
        if insn.mnemonic == "call" and insn.op_str.startswith("0x")
    ]
    assert timer_call_sites == TIMER_SETTER["call_sites"]
    timer_source = (ROOT / "src/BulletTimer4D8.cpp").read_text(encoding="utf8")
    assert "void Bullet::set_timer_4d8(float value)" in timer_source
    assert "timer_4d8 = value;" in timer_source
    timer_manifest = (ROOT / "config/match-units.toml").read_text(encoding="utf8")
    assert "[units.bullet_timer_4d8]" in timer_manifest
    assert "target_address = 0x0049CAE0" in timer_manifest

    source = (ROOT / "src/EnemyStateBulletClearOpcode.cpp").read_text(encoding="utf8")
    first = source[source.index("int EnemyState::clear_bullets_in_animation_rectangle"):
                   source.index("int EnemyState::clear_all_bullets_for_enemy_clear")]
    second = source[source.index("int EnemyState::clear_all_bullets_for_enemy_clear"):
                    source.index("bool execute_enemy_bullet_clear_opcode")]
    dispatch = source[source.index("bool execute_enemy_bullet_clear_opcode"):]
    first_order = [
        "animations[0].handle.resolve()",
        "scale_x_value()",
        "scale_y_value()",
        "rotation_z_value()",
        "context->bullet_controller()",
        "active_list()",
        "active.begin()",
        "bullet->position_ref().y",
        "bullet->position_ref().x",
        "position_ref().y",
        "position_ref().x",
        "geometry::rectangle_circle",
        "bullet->set_timer_4d8(counters.field_10)",
        "bullet->animation_ref()->set_packed_color(0xffa05000u)",
        "bullet->set_field_18_to_ten()",
        "context->player()->position_ref().y",
        "context->player()->position_ref().x",
        "position_ref().y",
        "position_ref().x",
        "geometry::rectangle_circle",
        "player(0)->set_field_20ec(counters.field_10)",
    ]
    cursor = 0
    for token in first_order:
        position = first.index(token, cursor)
        cursor = position + len(token)
    assert first.count("geometry::rectangle_circle") == 2
    globals_source = (ROOT / "src/NativeFloatGlobals.cpp").read_text()
    assert "native_six_56f00c = 6.0f" in globals_source
    assert "native_ten_56e734 = 10.0f" in globals_source
    assert "bullet->state" not in first and "bullet->field_18 != 0" not in first
    bullet_source = (ROOT / "src/Bullet.cpp").read_text()
    assert "Vector3& Bullet::position_ref() { return position; }" in bullet_source
    assert "Animation* Bullet::animation_ref() { return animation; }" in bullet_source
    assert "void Bullet::set_field_18_to_ten() { field_18 = 10; }" in bullet_source
    assert "void Bullet::clear_field_18() { field_18 = 0; }" in bullet_source
    assert first.count("auto* const link = iterator.get();") == 1
    assert second.count("auto* const link = iterator.get();") == 1
    assert "auto* controller = context->bullet_controller()" not in first + second
    assert "auto* controller = context->bullet_controller()" not in first + second
    assert "void Bullet::set_timer_4d8(float value)" in (ROOT / "src/BulletTimer4D8.cpp").read_text()
    assert "void Player::set_field_20ec(float value) { field_20ec = value; }" in (ROOT / "src/PlayerAccessors.cpp").read_text()
    assert "Player* player(std::int32_t index)" in (ROOT / "src/Player.cpp").read_text()
    assert "Vector3& Player::position_ref()" in (ROOT / "src/PlayerDirection.cpp").read_text()

    second_order = [
        "context->bullet_controller()",
        "active_list()",
        "active.begin()",
        "bullet->set_timer_4d8(native_one_56c8cc)",
        "bullet->animation_ref()->set_packed_color(0xffffffffu)",
        "bullet->clear_field_18()",
        "Player* const target_player = player(0)",
        "target_player->set_field_20ec(native_one_56c8cc)",
    ]
    cursor = 0
    for token in second_order:
        position = second.index(token, cursor)
        cursor = position + len(token)
    assert "animations[" not in second
    assert "geometry::rectangle_circle" not in second

    dispatch_order = [
        "if (opcode != 629)",
        "using Callback = int (EnemyState::*)();",
        "&EnemyState::clear_bullets_in_animation_rectangle",
        "&EnemyState::clear_all_bullets_for_enemy_clear",
        "state.integer_argument(0)",
        "(state.*callbacks[index])()",
    ]
    cursor = 0
    for token in dispatch_order:
        position = dispatch.index(token, cursor)
        cursor = position + len(token)

    header = (ROOT / "src/EnemyState.hpp").read_text(encoding="utf8")
    root = (ROOT / "src/EnemyStateExecuteOpcode.cpp").read_text(encoding="utf8")
    assert "int clear_bullets_in_animation_rectangle();" in header
    assert "int clear_all_bullets_for_enemy_clear();" in header
    assert "execute_enemy_bullet_clear_opcode(*this, opcode)" in root
    assert "offsetof(EnemyState, update_callback) == 0x2e0" in header

    tests = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    for marker in (
        "set_packet(629",
        "dispatch_integer_read_scripted_values[0] = 1",
        "dispatch_integer_read_scripted_values[0] = 2",
        "clear_unfiltered_629.state = 3",
        "clear_unfiltered_629.field_18 = 1",
        "clear_inside_629.field_18 == 10",
        "clear_outside_629.field_18 == 0",
        "dispatch_test_player->field_20ec == 4.25f",
        "dispatch_test_player->field_20ec == 7.5f",
        "clear_all_first_animation_629.base.color_490 == 0xffffffffu",
        "opcode629_integer_threw",
    ):
        assert marker in tests, marker

    print("PASS original Enemy opcode 629: selector 147, 46B / 10 x86 / one direct E8 plus indirect callback")
    print("PASS native callback table 0x56FE8C: null, 0x488B80 animation-rectangle clear, 0x488E80 all-bullet reset")
    print("PASS native EnemyState callback 0x00488B80: 758B body / 205 x86 / 34 ordered direct calls; separate 10B INT3 alignment tail")
    print("PASS native EnemyState callback 0x00488E80: 291B body / 86 x86 / 17 ordered direct calls")
    print("PASS native Bullet Timer +0x4D8 leaf 0x0049CAE0: 39B / 14 x86 / one ordered Timer::operator=(float) E8")
    print("PASS natural C++ animation resolve, rotated rectangle filters, live Enemy/Player positions, Bullet Timer/color/state and callback-table dispatch")
    print("PASS root-host opcode 629 both callbacks, no state/field filter, Player overlap side effect and operand exception-before-side-effects")


if __name__ == "__main__":
    main()
