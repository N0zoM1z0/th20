#!/usr/bin/env python3
"""Cross-check maintained Enemy 602-604 source against original native case audit."""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / ".analysis/core205-native-602-604-audit.json"
SOURCE = ROOT / "src/EnemyStateSharedQueuedParametersOpcode.cpp"
EXPECTED = {
    602: ("0x492a54", "0x492b09", 181, 43, "0f8f8b4289d81074be058e194184278486643e755b996833229818e72c598005", {
        "0x4ab080": 3, "0x498d10": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1,
    }),
    603: ("0x492b09", "0x492bc6", 189, 43, "6b9f8e3a7ca2c7bc6cd2052837b79ced5082014596c18cd50fe64f1096e83a99", {
        "0x4ab080": 1, "0x498d10": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1, "0x4aafb0": 2,
    }),
    604: ("0x492e47", "0x492f1c", 213, 51, "e0e6e80655dfbc9744e2a43895b7d8d1b79058993ed505f748b5d670bee81dee", {
        "0x4ab080": 1, "0x498d10": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1, "0x4aafb0": 2, "0x438540": 2,
    }),
}


def main() -> None:
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["original_target_sha256"] == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    cases = {entry["opcode"]: entry for entry in audit["original_complete_local_cases"]}
    source = SOURCE.read_text(encoding="utf8")
    for opcode, expected in EXPECTED.items():
        head, end, size, instructions, digest, targets = expected
        case = cases[opcode]
        assert case["original_entry"].lower() == head
        assert case["original_end_exclusive"].lower() == end
        assert case["original_bytes"] == size
        assert case["instruction_count"] == instructions
        assert case["native_sha256"] == digest
        actual = Counter(call["native_target"].lower()
                         for call in case["original_direct_calls"])
        assert actual == Counter(targets)
        assert f"case {opcode}:" in source
        print(f"PASS original opcode {opcode}: {size}B/{instructions} x86 and {sum(targets.values())} E8")

    assert source.count("state.shared_shot(") == 3
    assert "state.writable_shot(" not in source
    for required in (
        "parameters.type = static_cast<std::uint32_t>(state.integer_argument(1));",
        "parameters.color = static_cast<std::uint32_t>(state.integer_argument(2));",
        "offset.x = state.float_argument(1);",
        "offset.y = state.float_argument(2);",
        "parameters.angle = normalize_angle(state.float_argument(1));",
        "parameters.angle_step = normalize_angle(state.float_argument(2));",
    ):
        assert required in source, required
    print("PASS real ensure-only shared_shot selector; no COW clone path")
    print("PASS ordered type/color, vector x/y, and individually normalized angle/angle_step writes")
    print("PASS source fragments only; original 41,967B Enemy parent remains NONEXACT")


if __name__ == "__main__":
    main()
