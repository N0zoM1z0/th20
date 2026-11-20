#!/usr/bin/env python3
"""Cross-check natural-C++ 609-612 source against the original branch audit."""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / ".analysis/core187-native-609-612-audit.json"
SOURCE = ROOT / "src/EnemyStateShotCommandOpcode.cpp"
EXPECTED_TARGETS = {
    "0x4ab080": 8,  # EnemyState::integer_argument
    "0x498b80": 1,  # EnemyState::writable_shot
    "0x40b280": 2,  # pair element address helpers
    "0x48b180": 1,
    "0x48b160": 1,
    "0x486600": 1,  # PMR vector size
    "0x4862f0": 1,  # PMR vector resize
    "0x47c6c0": 10, # PMR vector<BulletCommand>::operator[]
    "0x4aafb0": 4,  # EnemyState::float_argument
}


def main() -> None:
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["target_sha256"] == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    assert audit["original_whole_root_start"] == "0x0048C010"
    assert audit["original_primary_head"] == "0x4931dd"
    assert audit["native_branch_bytes"] == 1457
    assert audit["native_branch_instruction_count"] == 314
    assert audit["native_branch_sha256"] == (
        "f129e860c6aaf09aa107aca146fc85abc1eb021721d052c6e2f7c2430dabb98b"
    )
    assert audit["original_shared_opcodes"] == [609, 610, 611, 612]
    actual_targets = Counter(call["target"].lower()
                             for call in audit["original_branch_call_sites"])
    assert len(audit["original_branch_call_sites"]) == 29
    assert actual_targets == Counter(EXPECTED_TARGETS)

    source = SOURCE.read_text(encoding="utf8")
    for opcode in (609, 610, 611, 612):
        assert f"case {opcode}:" in source
    for required in (
        "state.integer_argument(0)",
        "state.writable_shot(static_cast<std::uint32_t>(record_index))",
        "opcode == 611 || opcode == 612",
        "opcode == 610 || opcode == 612",
        "metadata.commands.size() < required_size",
        "metadata.commands.resize(required_size)",
        "metadata.commands[command_index].flags",
        "metadata.commands[command_index].opcode",
        "metadata.commands[command_index].operand_10",
        "metadata.commands[command_index].operand_14",
        "metadata.commands[command_index].operand_18",
        "metadata.commands[command_index].operand_1c",
        "metadata.commands[command_index].operand_00",
        "metadata.commands[command_index].operand_04",
        "metadata.commands[command_index].operand_08",
        "metadata.commands[command_index].operand_0c",
        "metadata.field_30 = cursor_mode ? metadata.field_30 + 1u : required_size;",
    ):
        assert required in source, required
    assert source.count("metadata.commands[command_index]") == 10
    assert "auto& command" not in source

    print("PASS original Enemy shared opcode head 0x4931DD: 1457B / 314 x86 / 29 E8")
    print("PASS original 29-call destination multiset: 10 vector access, 8 int args, 4 float args, and exact owner/pair/size/resize helpers")
    print("PASS natural-C++ opcode family 609/610/611/612: 4/6 integer, 2/4 float, cursor/explicit index, resize, per-field access, final cursor commit")
    print("PASS source fragment only; no independent native function mapping or 41967B parent byte credit")


if __name__ == "__main__":
    main()
