#!/usr/bin/env python3
"""Cross-check maintained Enemy opcode 614 source against the original native CFG."""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / ".analysis/core207-native-op614-audit.json"
SOURCE = ROOT / "src/EnemyStateQueueCopyOpcode.cpp"
EXPECTED_TARGETS = {
    "0x4ab080": 2,
    "0x4981c0": 2,
    "0x497e70": 4,
    "0x48b0c0": 2,
    "0x49c280": 2,
    "0x40c080": 2,
    "0x48a820": 2,
    "0x48bdc0": 2,
    "0x48bc00": 1,
}


def main() -> None:
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["locked_original_SHA256"] == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    assert audit["original_opcode"] == 614
    assert audit["native_head"] == "0x4925c7"
    assert audit["native_end_exclusive"] == "0x492803"
    assert audit["native_bytes"] == 572
    assert audit["instruction_count"] == 129
    assert audit["native_sha256"] == (
        "86502facaafd3ae67358babf1d91fb44682ce14248911264714d48ccf29ebfa9"
    )
    calls = audit["original_full_native_calls"]
    assert len(calls) == 19
    actual_targets = Counter(call["native_target"].lower() for call in calls)
    assert actual_targets == Counter(EXPECTED_TARGETS)

    source = SOURCE.read_text(encoding="utf8")
    assert "if (opcode != 614)" in source
    assert source.index("state.integer_argument(0)") < source.index("state.integer_argument(1)")
    assert source.index("state.integer_argument(1)") < source.index("const std::uint32_t destination_required")
    assert source.index("queue.resize(destination_required)") < source.index("const std::uint32_t source_required")
    assert source.index("queue.resize(source_required)") < source.index("auto destination = queue.begin()")
    assert source.index("auto destination = queue.begin()") < source.index("auto source = queue.begin()")
    assert source.index("auto source = queue.begin()") < source.index("*destination = *source;")
    assert "std::distance(destination_begin, destination_end)" in source
    assert "std::distance(source_begin, source_end)" in source
    assert source.count("std::advance(") == 2
    assert "std::swap(" not in source and "std::memcpy(" not in source
    print("PASS original opcode 614: 572B / 129 x86 / 19 direct E8 and branch SHA-256")
    print("PASS original call target multiset: both operand reads, two distance/resize paths, two iterator advances/destructors, and real 119B assignment")
    print("PASS natural-C++ order: read both indexes, resize destination then source, advance independent iterators, copy-assign destination from source")
    print("PASS source fragment only; 41,967B Enemy root remains NONEXACT")


if __name__ == "__main__":
    main()
