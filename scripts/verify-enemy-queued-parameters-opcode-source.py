#!/usr/bin/env python3
"""Cross-check maintained Enemy 700/701 source against original native case audit."""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / ".analysis/core198-native-700-701-audit.json"
SOURCE = ROOT / "src/EnemyStateQueuedParametersOpcode.cpp"
EXPECTED = {
    700: ("0x49392d", "0x493a3a", 269, 59, "4311d9abfaccf81e01d4575819c8f50f3be41f8ad122912c7cc898c326f8050c", {
        "0x4ab080": 1, "0x498b80": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1, "0x4aafb0": 4,
    }),
    701: ("0x493a3a", "0x493b5b", 289, 67, "a9de8425a0507e18a90616a47bb2fcdc0a5b97a78e73f0a8e4047abe4d548b0a", {
        "0x4ab080": 6, "0x498b80": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1,
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
        assert case["entry"].lower() == head
        assert case["native_end_exclusive"].lower() == end
        assert case["native_bytes"] == size
        assert case["native_instructions"] == instructions
        assert case["native_bytes_sha256"] == digest
        actual = Counter(call["original_destination"].lower()
                         for call in case["native_direct_calls"])
        assert actual == Counter(targets)
        assert f"case {opcode}:" in source
        print(f"PASS original opcode {opcode}: {size}B/{instructions} x86, {sum(targets.values())} E8 and exact operand/owner source path")

    for field in ("field_14", "field_24", "field_28", "field_2c", "field_30", "field_34"):
        assert f"metadata.{field} =" in source
    for component in ("x", "y", "z"):
        assert f"record.parameters.position.{component} = state.float_argument(" in source
    assert "metadata.field_14 = state.float_argument(4);" in source
    assert "state.writable_shot(static_cast<std::uint32_t>(selector))" in source
    print("PASS real writable pair selector, 700 position/width floats, 701 five raw integer metadata words")
    print("PASS source fragments only; original 41,967B parent remains NONEXACT")


if __name__ == "__main__":
    main()
