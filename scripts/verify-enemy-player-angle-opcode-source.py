#!/usr/bin/env python3
"""Verify Enemy ECL opcode 617's live-Context player-angle calculation."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStatePlayerAngleOpcode.cpp"
ROOT_SOURCE = ROOT / "src/EnemyStateExecuteOpcode.cpp"
CONTEXT_SOURCE = ROOT / "src/Context.cpp"
DAMAGE_QUERY_SOURCE = ROOT / "src/DamageQueryProtocol.cpp"
BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
OPCODE = 617
START = 0x004958C3
SIZE = 203
EXPECTED_SHA256 = "495e3bf841a650d5b5ba51ce400eac059768f8557e0977d941cfb59aec965ff9"
EXPECTED_CALL_SITES = [
    (0x004958CF, 0x0040FF90),  # Context::player (shared +4 accessor body)
    (0x004958D6, 0x00460850),  # Player::position_ref (+0x614)
    (0x004958E5, 0x004AAFB0),  # float_argument(1)
    (0x00495910, 0x0040FF90),  # re-read Context::player
    (0x00495917, 0x00460850),  # re-read Player::position_ref
    (0x00495926, 0x004AAFB0),  # float_argument(2)
    (0x00495962, 0x00459280),  # scalar_math::arctangent(dy, dx)
    (0x00495978, 0x004AA980),  # float_argument_destination(0)
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
    assert selector[OPCODE - 300] == 135
    assert pointers[selector[OPCODE - 300]] == START

    raw = pe.get_data(START - image_base, SIZE)
    assert len(raw) == SIZE
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA256
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, START))
    assert len(instructions) == 41
    calls = [
        (instruction.address, int(instruction.op_str, 16))
        for instruction in instructions
        if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
    ]
    assert calls == EXPECTED_CALL_SITES, [
        (hex(address), hex(target)) for address, target in calls
    ]
    epilogue_jump = next(instruction for instruction in instructions if instruction.address == 0x00495989)
    assert epilogue_jump.mnemonic == "jmp" and int(epilogue_jump.op_str, 16) == 0x004963DF

    source = SOURCE.read_text(encoding="utf8")
    start = source.index("    if (opcode != 617)")
    end = source.index("    return true;", start)
    branch = source[start:end]
    order = [
        "state.context->player()->position_ref()",
        "state.float_argument(1)",
        "first_position.x - target_x",
        "state.context->player()->position_ref()",
        "state.float_argument(2)",
        "second_position.y - target_y",
        "scalar_math::arctangent(delta_y, delta_x)",
        "state.float_argument_destination(0)",
        "*destination = angle",
    ]
    cursor = 0
    for item in order:
        position = branch.index(item, cursor)
        cursor = position + len(item)
    assert branch.count("state.context->player()") == 2
    assert branch.count("position_ref()") == 2
    assert "Player::direction_to" not in branch and "direction_to(" not in branch

    root = ROOT_SOURCE.read_text(encoding="utf8")
    context = CONTEXT_SOURCE.read_text(encoding="utf8")
    damage_query = DAMAGE_QUERY_SOURCE.read_text(encoding="utf8")
    assert "execute_enemy_player_angle_opcode(*this, opcode)" in root
    assert "Player* Context::player()" in context
    assert "Context::player()" not in damage_query

    test_source = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    assert "retarget_context_player_during_first_float_read" in test_source
    assert "expected_player_angle_617" in test_source
    assert "player_angle_second_operand_threw" in test_source
    assert "enemy.main.stack.local(0) == bits(123.0f)" in test_source
    assert "zero_vector_angle_617 == 0.0f" in test_source
    assert "Player player_fixture;" in test_source
    assert "Player alternate_player_fixture;" in test_source
    assert "session.contexts[0].object_04 = dispatch_test_player;" in test_source
    assert "player_fixture.entity_flags.fields.bit_10 == 1" in test_source
    assert "Player* player(std::int32_t index)" not in test_source
    assert "void Player::set_entity_flag_10" not in test_source

    print("PASS original Enemy opcode 617: selector 135, 203B / 41 x86 / 8 ordered E8 calls")
    print("PASS exact native case SHA-256, two Context/player position reads, atan2 and destination order")
    print("PASS natural C++ re-reads Context between VM operands and computes arctangent(dy, dx)")
    print("PASS source ownership: Context::player is linked from Context.cpp; no duplicate DamageQueryProtocol definition")
    print("PASS retarget, direct atan2(0,0)==0, real Player fixtures and second-operand exception regression coverage")
    print("PASS inline fragment only; no standalone unit or 41,967B parent byte credit")


if __name__ == "__main__":
    main()
