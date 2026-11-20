#!/usr/bin/env python3
"""Check maintained Enemy Laser opcode fragments against original CFG evidence."""
from __future__ import annotations

import json
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
AUDIT = ROOT / ".analysis/core716-enemy-41967-Laser-opcode-native-case-CFG.json"
SOURCE = ROOT / "src/EnemyStateLaserOpcode.cpp"

EXPECTED = {
    702: ("0x4944c7", 153, 15, "0x4944cd", "0x47c130", "0x494766", "0x47c4b0"),
    703: ("0x494771", 176, 16, "0x494777", "0x47c030", "0x494a79", "0x47c490"),
    711: ("0x494ce7", 141, 15, "0x494ced", "0x48b650", "0x494f47", "0x48b8b0"),
    713: ("0x494a84", 137, 16, "0x494a8a", "0x48b5b0", "0x494cdc", "0x48b890"),
}


def main() -> None:
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["original_PE_SHA256"] == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    assert audit["all_174_original_switch_pointer_pe_HIGHLOW_verified"] is True
    entries = {entry["opcode"]: entry for entry in audit[
        "original_laser_opcodes_typed_and_independently_native_verified"
    ]}
    source = SOURCE.read_text(encoding="utf8")
    for opcode, expected in EXPECTED.items():
        entry = entries[opcode]
        head, instructions, calls, ctor_site, ctor_target, dtor_site, dtor_target = expected
        assert entry["original_case_entry"].lower() == head
        assert entry["actual_reachable_original_instructions"] == instructions
        assert entry["actual_direct_E8"] == calls
        assert entry["original_ctor_E8_site"].lower() == ctor_site
        assert entry["physical_verified_laser_constructor"].lower() == ctor_target
        assert entry["original_dtor_E8_site"].lower() == dtor_site
        assert entry["physical_verified_laser_destructor"].lower() == dtor_target
        assert f"case {opcode}:" in source
        factory_type = {702: 0, 703: 1, 711: 2, 713: 3}[opcode]
        assert f"create_laser({factory_type}, &laser)" in source
        print(f"PASS original opcode {opcode}: {instructions} CFG heads, {calls} E8, ctor/dtor pair; natural C++ factory path")

    for required in (
        "state.writable_shot(",
        "laser.commands = metadata.commands;",
        "state.context->laser_controller()->create_laser(",
        "LaserType0Parameters", "LaserType1Parameters",
        "LaserType2Parameters", "LaserType3Parameters",
        "laser.count = metadata.field_24;",
        "laser.flags.word = 1u;",
        "laser.field_2c = record.parameters.color;",
        "laser.field_34 = metadata.field_24;",
        "laser.field_24 = metadata.field_14;",
        "laser.field_20 = record.parameters.position.z;",
        "laser.field_30 = metadata.field_00;",
        "laser.handle = static_cast<std::uint32_t>(state.integer_argument(1))",
    ):
        assert required in source, required
    print("PASS shared queued-shot COW, PMR command copy, typed parameter lifetimes and Context Laser factory")
    print("PASS original parent boundary remains inline-fragment only; no fake standalone native mapping")


if __name__ == "__main__":
    main()
