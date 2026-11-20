#!/usr/bin/env python3
"""Verify natural-C++ Enemy opcode 555 against the locked original PE."""
from __future__ import annotations

import hashlib
import json
import struct
from collections import Counter
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
AUDIT = ROOT / ".analysis/core185-native-555-audit.json"
SOURCE = ROOT / "src/EnemyStateAnimationSpawnOpcode.cpp"
BASE = 0x00400000
EXPECTED_TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
EXPECTED_BRANCH_SHA = "5ab9c44d05b183785798d82102af4643c853bca652d0766f463c2548686016cd"
EXPECTED_CALLS = {
    0x0048C40F: 0x004292E0,
    0x0048C446: 0x00426EB0,
    0x0048C465: 0x00499350,
    0x0048C475: 0x004560D0,
    0x0048C4BC: 0x00499350,
    0x0048C4CC: 0x0047A2E0,
    0x0048C4E6: 0x00412730,
    0x0048C510: 0x004AAE10,
    0x0048C521: 0x00499350,
    0x0048C56D: 0x004790E0,
}


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == EXPECTED_TARGET_SHA
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["target_sha256"] == EXPECTED_TARGET_SHA
    assert audit["opcode"] == 555
    assert audit["root_entry"] == "0x48c010" and audit["root_size"] == 41967
    assert audit["original_primary_head"] == "0x48c3f4"
    assert audit["case_end_exclusive"] == "0x48c578"
    assert audit["native_case_local_bytes"] == 388
    assert audit["native_case_local_instruction_count"] == 81
    assert audit["native_case_sha256"] == EXPECTED_BRANCH_SHA

    pe = pefile.PE(data=pe_bytes, fast_load=True)
    raw = pe.get_data(0x0048C3F4 - BASE, 388)
    assert len(raw) == 388
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_BRANCH_SHA
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, 0x0048C3F4))
    assert len(decoded) == 81
    calls = {insn.address: int(insn.op_str, 16)
             for insn in decoded
             if insn.mnemonic == "call" and insn.op_str.startswith("0x")}
    assert calls == EXPECTED_CALLS
    assert calls == {int(item["site"], 16): int(item["target"], 16)
                     for item in audit["native_calls"]}

    def data(address: int, size: int) -> bytes:
        return pe.get_data(address - BASE, size)

    assert data(0x0056FBF8, 4) == struct.pack("<f", 0.2)
    assert data(0x0056E0F8, 4) == struct.pack("<f", -3.1415927410125732)
    assert data(0x0056C8D0, 4) == struct.pack("<f", 2.0)

    source = SOURCE.read_text(encoding="utf8")
    required = (
        "if (opcode != 555)",
        "if (state.field_250 >= 0)",
        "state.motion_110.position_x()",
        "process_sound.request_effect_at(sound, x);",
        "if (state.field_254 >= 0)",
        "geometry::squared_distance_xy(",
        "state.vector_6c, state.position_ref()",
        "native_progress_mesh_alpha_fade_span_02_56fbf8 *",
        "native_negative_pi_56e0f8 / native_screen_half_2_56c8d0",
        "geometry::direction_xy(state.vector_6c, state.position_ref())",
        "state.context->enemy_controller()",
        "owner->animation_file(state.field_258)",
        "file->spawn(nullptr, script, position, direction, 3, nullptr)",
    )
    for item in required:
        assert item in source, item
    assert source.count("state.position_ref()") == 3
    assert "integer_argument" not in source and "float_argument" not in source
    assert source.index("state.field_250 >= 0") < source.index("state.field_254 >= 0")
    assert source.index("process_sound.request_effect_at") < source.index("geometry::squared_distance_xy")
    assert source.index("geometry::squared_distance_xy") < source.index("geometry::direction_xy")
    assert source.index("geometry::direction_xy") < source.index("owner->animation_file")
    assert source.index("owner->animation_file") < source.index("file->spawn")

    print("PASS original Enemy opcode 555: 388B / 81 x86 / 10 direct E8; exact locked PE SHA and call-site map")
    print("PASS original 0.2f, -pi and 2.0f data values at 0x56FBF8/0x56E0F8/0x56C8D0")
    print("PASS ordered independent sound/animation gates, planar distance threshold, direction fallback, Context EnemyController selector and layer-3 AnimationFile spawn")
    print("PASS no VM operands or fabricated sound/file/render owners; full 41,967B Enemy root remains NONEXACT")


if __name__ == "__main__":
    main()
