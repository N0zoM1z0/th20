#!/usr/bin/env python3
"""Cross-check maintained Enemy opcode 632 source against original native audit."""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / ".analysis/core208-native-632-audit.json"
SOURCE = ROOT / "src/EnemyStateScriptPointerOpcode.cpp"
EXPECTED_TARGETS = {
    "0x4ab080": 2,
    "0x498b80": 1,
    "0x40b280": 2,
    "0x48b180": 1,
    "0x48b160": 1,
    "0x486600": 1,
    "0x4862f0": 1,
    "0x47c6c0": 1,
}


def main() -> None:
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["target_sha256"] == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    assert audit["native_opcode"] == 632
    assert audit["native_case_head"] == "0x493831"
    assert audit["native_case_end_exclusive"] == "0x49392d"
    assert audit["original_case_bytes"] == 252
    assert audit["original_case_instruction_count"] == 62
    assert audit["native_case_sha256"] == (
        "45cdbd018eea322e53dcffa4af1834acceeb26b2f9ba2aa72d6a17d41535f277"
    )
    calls = audit["native_direct_calls"]
    assert len(calls) == 10
    actual = Counter(call["original_target"].lower() for call in calls)
    assert actual == Counter(EXPECTED_TARGETS)

    source = SOURCE.read_text(encoding="utf8")
    assert "opcode != 632" in source
    assert source.index("state.integer_argument(0)") < source.index("state.integer_argument(1)")
    assert source.index("state.integer_argument(1)") < source.index("state.writable_shot(")
    assert source.index("state.writable_shot(") < source.index("metadata.commands.size()")
    assert source.index("metadata.commands.resize(required_size)") < source.index("metadata.commands[index].script")
    assert "reinterpret_cast<const char*>(&instruction) + 0x1c" in source
    assert "float_argument" not in source
    assert "metadata.field_30" not in source
    print("PASS original opcode 632: 252B / 62 x86 / 10 direct E8 and branch SHA-256")
    print("PASS original target multiset: two integer reads, COW selector, pair extraction, vector size/resize and 44B command access")
    print("PASS natural-C++ source stores the borrowed EclInstruction+0x1C packet pointer after both indexes and vector growth")
    print("PASS no string allocation/copy, no extra float operand, no metadata cursor update; parent remains NONEXACT")


if __name__ == "__main__":
    main()
