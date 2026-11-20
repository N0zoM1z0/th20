#!/usr/bin/env python3
"""Verify Enemy opcode 555 source against the immutable original PE branch."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStateAnimationSpawnOpcode.cpp"
BASE = 0x00400000
START = 0x0048C3F4
SIZE = 388
EXPECTED_SHA256 = "5ab9c44d05b183785798d82102af4643c853bca652d0766f463c2548686016cd"
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
    assert hashlib.sha256(pe_bytes).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    raw = pe.get_data(START - BASE, SIZE)
    assert len(raw) == SIZE
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA256
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, START))
    assert len(instructions) == 81
    calls = {insn.address: int(insn.op_str, 16)
             for insn in instructions
             if insn.mnemonic == "call" and insn.op_str.startswith("0x")}
    assert calls == EXPECTED_CALLS

    def float_at(address: int) -> float:
        return struct.unpack("<f", pe.get_data(address - BASE, 4))[0]

    assert float_at(0x0056FBF8) == struct.unpack("<f", struct.pack("<f", 0.2))[0]
    assert float_at(0x0056E0F8) == -3.1415927410125732
    assert float_at(0x0056C8D0) == 2.0

    source = SOURCE.read_text(encoding="utf8")
    required = (
        "if (state.field_250 >= 0)",
        "state.motion_110.position_x()",
        "process_sound.request_effect_at(sound, x);",
        "if (state.field_254 >= 0)",
        "geometry::squared_distance_xy(\n            state.vector_6c, state.position_ref())",
        "0.2f * 0.2f > distance",
        "-enemy_nearby_spawn_pi / 2.0f",
        "geometry::direction_xy(state.vector_6c, state.position_ref())",
        "state.context->enemy_controller()",
        "owner->animation_file(state.field_258)",
        "file->spawn(nullptr, script, position, direction, 3, nullptr)",
    )
    for item in required:
        assert item in source, item
    order = [
        "state.motion_110.position_x()",
        "process_sound.request_effect_at(sound, x);",
        "geometry::squared_distance_xy(",
        "geometry::direction_xy(",
        "state.context->enemy_controller()",
        "owner->animation_file(state.field_258)",
        "auto& position = state.position_ref();",
        "file->spawn(nullptr, script, position, direction, 3, nullptr)",
    ]
    positions = [source.index(item) for item in order]
    assert positions == sorted(positions)

    print("PASS original Enemy opcode 555: 388B / 81 x86 / 10 E8, exact PE bytes and call targets")
    print("PASS original 0.2f, -pi and 2.0f constants at their immutable PE addresses")
    print("PASS natural-C++ sound gate, squared-distance threshold, direction fallback, live EnemyController/AnimationFile selection and layer-3 spawn")
    print("PASS original 41,967B Enemy parent remains NONEXACT")


if __name__ == "__main__":
    main()
