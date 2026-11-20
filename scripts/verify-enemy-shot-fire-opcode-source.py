#!/usr/bin/env python3
"""Cross-check maintained Enemy 600/601 source against original native case audits."""
from __future__ import annotations

import json
from collections import Counter
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDITS = {
    600: ROOT / ".analysis/core202-native-600-audit.json",
    601: ROOT / ".analysis/core204-native-601-audit.json",
}
SOURCE = ROOT / "src/EnemyStateShotFireOpcode.cpp"
EXPECTED = {
    600: ("0x492434", "0x4925c7", 403, 90, "bc2525ef83d9d18087fdde23327b7492d1721851dd245e20f74dd05dd04a0223", {
        "0x4ab080": 1, "0x498b80": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1, "0x47bd20": 1,
        "0x47bb90": 1, "0x48bb00": 1, "0x47c450": 1,
    }),
    601: ("0x492803", "0x492a54", 593, 136, "d609387a30cbbf027daf25c6f822ba9b8624e1b61d37a14f679329d1d3275319", {
        "0x4ab080": 1, "0x498d10": 1, "0x40b280": 2,
        "0x48b180": 1, "0x48b160": 1, "0x429570": 2,
        "0x40bda0": 1, "0x40c300": 3, "0x49c740": 2,
        "0x47b850": 1, "0x481780": 1,
    }),
}


def main() -> None:
    source = SOURCE.read_text(encoding="utf8")
    for opcode, path in AUDITS.items():
        audit = json.loads(path.read_text(encoding="utf8"))
        if opcode == 600:
            assert audit["original_PE_sha256"] == "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
            head, end = audit["original_case_entry"], audit["original_case_end_exclusive"]
            size, instructions, digest = audit["original_case_native_bytes"], audit["original_case_instructions"], audit["original_case_SHA256"]
            calls = audit["original_direct_calls"]
            site_key, target_key = "address", "target"
        else:
            assert audit["target_sha256"] == "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
            head, end = audit["original_primary_head"], audit["native_case_end_exclusive"]
            size, instructions, digest = audit["original_601_bytes"], audit["original_native_instructions"], audit["original_native_case_sha256"]
            calls = audit["native_call_sites"]
            site_key, target_key = "site", "target"
        expected_head, expected_end, expected_size, expected_instructions, expected_digest, expected_targets = EXPECTED[opcode]
        assert head.lower() == expected_head and end.lower() == expected_end
        assert size == expected_size and instructions == expected_instructions and digest == expected_digest
        actual_targets = Counter(call[target_key].lower() for call in calls)
        assert actual_targets == Counter(expected_targets)
        assert f"case {opcode}:" in source
        print(f"PASS original opcode {opcode}: {size}B/{instructions} x86 and {len(calls)} direct E8 sites")

    assert "record.parameters = ShotParameters{};" in source
    assert "metadata = ShotMetadata{};" in source
    assert "record.vector_34.x = 0.0f;" in source
    assert "record.vector_34.y = 0.0f;" in source
    assert "record.vector_40.x = 0.0f;" in source
    assert "record.vector_40.y = 0.0f;" in source
    assert "record.vector_40.z = 0.0f;" in source
    assert "record.vector_34.z =" not in source
    assert source.index("record.vector_40.z = 0.0f;") < source.index("record.field_30 = 0;")

    opcode601 = source.split("case 601:", 1)[1].split("default:", 1)[0]
    assert "state.shared_shot(static_cast<std::uint32_t>(selector))" in opcode601
    assert "writable_shot" not in opcode601
    assert "record.vector_40.z > 0.9f" in opcode601
    assert "record.parameters.position = record.vector_40 + record.vector_34;" in source
    assert "record.parameters.position = state.position_ref() + record.vector_34;" in source
    assert source.count("state.context->bullet_controller()") == 3
    assert source.count("set_scalar_48(") == 2
    assert "state.context->bullet_controller()->fire(record.parameters, record.owner);" in source
    assert source.index("set_scalar_48(state.field_274)") < source.index("fire(record.parameters, record.owner)") < source.index("set_scalar_48(0.0f)")
    assert "state.writable_shot(static_cast<std::uint32_t>(selector))" in source.split("case 600:", 1)[1].split("case 601:", 1)[0]
    print("PASS opcode 600 native ShotParameters/EtamaArgInf value lifetimes and exact record reset set; vector_34.z preserved")
    print("PASS opcode 601 ensure-only selector, strict 0.9 position gate, real shared_ptr copy, live Context retarget and post-fire reset")
    print("PASS source fragments only; original 339B fire callee and 41,967B parent remain NONEXACT")


if __name__ == "__main__":
    main()
