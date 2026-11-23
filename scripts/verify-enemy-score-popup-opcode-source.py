#!/usr/bin/env python3
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
IMAGE_BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
OPCODE = 630
SELECTOR_INDEX = 148
START = 0x0048C24A
END = 0x0048C2B7
EXPECTED_SHA256 = "664b6390a104a5d366a94e921220b980d3c8644bb9370484b84da12620b6fbd4"
EXPECTED_CALLS = [
    (0x0048C252, 0x004AB080),  # integer_argument(0)
    (0x0048C269, 0x00488550),  # Session::add_score
    (0x0048C27A, 0x00421810),  # Context +0x1C queue accessor
    (0x0048C28B, 0x00499350),  # EnemyState::position_ref
    (0x0048C2AC, 0x00510710),  # ItemRewardPopupQueue::enqueue
]


def main() -> None:
    pe = pefile.PE(str(PE_PATH), fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    selector = pe.get_data(SELECTOR_TABLE - image_base, 704)
    pointer_table = pe.get_data(POINTER_TABLE - image_base, 174 * 4)
    assert selector[OPCODE - 300] == SELECTOR_INDEX
    assert struct.unpack_from("<I", pointer_table, SELECTOR_INDEX * 4)[0] == START

    raw = pe.get_data(START - image_base, END - START)
    assert len(raw) == 109
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA256
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, START))
    assert len(instructions) == 24
    assert instructions[-1].address + instructions[-1].size == END
    calls = [
        (instruction.address, int(instruction.op_str, 16))
        for instruction in instructions
        if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
    ]
    assert calls == EXPECTED_CALLS, calls
    by_address = {instruction.address: instruction for instruction in instructions}
    assert by_address[0x0048C296].mnemonic == "push"
    assert by_address[0x0048C296].op_str == "-1"

    helper = (ROOT / "src/EnemyStateScorePopupOpcode.cpp").read_text()
    order = [
        "integer_argument(0)",
        "session.add_score",
        "item_reward_popup_queue()",
        "position_ref()",
        "queue->enqueue(&position, -1, static_cast<std::uint32_t>(amount))",
    ]
    cursor = 0
    for token in order:
        position = helper.index(token, cursor)
        cursor = position + len(token)

    context = (ROOT / "src/Context.cpp").read_text()
    assert "Context::item_reward_popup_queue()" in context
    assert "static_cast<ItemRewardPopupQueue*>(object_1c)" in context
    popup = (ROOT / "src/ItemRewardPopupQueue.cpp").read_text()
    assert "if (amount>=0)" in popup
    assert "entry->digits[count]=10;" in popup
    assert "entry->position=*position;" in popup
    assert "entry->clock_value=native_one_56c8cc;" in popup
    session = (ROOT / "src/SessionScore.cpp").read_text()
    assert "void Session::add_score(std::uint32_t amount)" in session
    assert "void PlayerRecord::add_score(std::uint64_t amount)" in session
    assert "record.add_score(amount);" in session
    assert "void Session::add_score(std::uint32_t amount)" not in (
        ROOT / "src/DamageQueryProtocol.cpp"
    ).read_text()

    tests = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text()
    for marker in (
        "set_packet(630",
        "retarget_context_during_integer_read",
        "session.table.players[0].score == score_before_630 + 12",
        "score_popup_630.digits[0] == 10",
        "score_popup_630.color == 120",
        "opcode630_integer_threw",
    ):
        assert marker in tests, marker

    print("PASS original Enemy opcode 630: selector 148, 109B / 24 x86 / 5 ordered direct E8 calls")
    print("PASS native opcode 630 call order: integer operand, Session score, Context +0x1C queue, live position, 255B popup enqueue")
    print("PASS native opcode 630 negative amount marker: push -1")
    print("PASS natural C++ uses real Session::add_score and ItemRewardPopupQueue::enqueue; no copied popup/string")
    print("PASS root-host opcode 630: Session score update, live Context retarget, queue payload and operand exception-before-side-effects")


if __name__ == "__main__":
    main()
