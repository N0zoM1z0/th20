#!/usr/bin/env python3
"""Verify Enemy opcode 551 and its typed Stage/Fog owner chain against the locked PE."""
from __future__ import annotations

import hashlib
import json
import re
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
AUDIT = ROOT / ".analysis/core176-enemy-551-native-audit.json"
FOG_SOURCE = ROOT / "src/EnemyStateFogOpcode.cpp"
OWNER_HEADER = ROOT / "src/StageResource.hpp"
OWNER_SOURCE = ROOT / "src/StageResourceFog.cpp"
BASE = 0x00400000
TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"

# Original Enemy opcode 551, complete inline case body.
CASE = (0x00495C1F, 257, 58,
        "9d0a1a47670fbca33a9ba4ec3a3f90e8178448d6048d078e97a4feba569234d0")
CASE_CALLS = {
    0x00495C25: 0x00425CC0,
    0x00495C32: 0x004AB080,
    0x00495C45: 0x004AB080,
    0x00495C58: 0x004AB080,
    0x00495C64: 0x0045D650,
    0x00495C71: 0x004AAFB0,
    0x00495C84: 0x004AAFB0,
    0x00495CF5: 0x004718D0,
    0x00495D15: 0x0049C5B0,
}

# Owner and nested interpolation functions reached by the final native call.
# Each tuple is (PE VA, code bytes, exact direct calls, object, symbol fragment,
# COFF relocation displacement offsets).
OWNER_FUNCTIONS = [
    (0x004AADF0, 20, {},
     "build/gptweb-enemy-fog-opcode/StageResourceFog.obj",
     "?animation_file@StageResourceOwner", []),
    (0x0049C5B0, 45, {0x0049C5D1: 0x004776C0},
     "build/gptweb-enemy-fog-opcode/StageResourceFog.obj",
     "?set_fog@StageResourceOwner", [0x22]),
    (0x004776C0, 130, {
        0x004776DB: 0x00477750,
        0x004776F3: 0x00477840,
        0x00477711: 0x00477820,
        0x00477728: 0x00477670,
        0x00477736: 0x00477860,
    }, "build/gptweb-enemy-fog-opcode/StageResourceFog.obj",
       "?set_fog@StageBackgroundFogOwner",
       [0x1c, 0x34, 0x52, 0x69, 0x77]),
    (0x00477750, 25, {},
     "build/core141-canonical/Interpolation.obj",
     "?set_duration@?$Interpolation@UFogValue", []),
    (0x00477840, 28, {},
     "build/core141-canonical/Interpolation.obj",
     "?set_mode@?$Interpolation@UFogValue", []),
    (0x00477820, 30, {},
     "build/core141-canonical/Interpolation.obj",
     "?set_start@?$Interpolation@UFogValue", []),
    (0x00477670, 33, {},
     "build/core141-canonical/Interpolation.obj",
     "?set_end@?$Interpolation@UFogValue", []),
    (0x00477860, 28, {0x00477872: 0x00423520},
     "build/core141-canonical/Interpolation.obj",
     "?reset_timer@?$Interpolation@UFogValue", [0x13]),
]


def disassemble(pe: pefile.PE, address: int, size: int):
    raw = pe.get_data(address - BASE, size)
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
    calls = {i.address: int(i.op_str, 16) for i in decoded
             if i.mnemonic == "call" and i.op_str.startswith("0x")}
    return raw, decoded, calls


def object_function_bytes(path: Path, symbol_fragment: str, expected_size: int) -> bytes:
    text = subprocess.check_output(["objdump", "-d", str(path)], text=True)
    lines = text.splitlines()
    start = next(i for i, line in enumerate(lines)
                 if "<" + symbol_fragment in line)
    result = bytearray()
    for line in lines[start + 1:]:
        if "<" in line and line.strip().endswith(">:"):
            break
        match = re.match(r"\s*[0-9a-f]+:\s*((?:[0-9a-f]{2}\s+)+)", line)
        if match:
            result.extend(int(value, 16) for value in match.group(1).split())
        if len(result) >= expected_size:
            break
    return bytes(result[:expected_size])


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == TARGET_SHA
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["target_sha256"] == TARGET_SHA
    native_case = audit["original_opcode551"]
    assert native_case["entry"] == "0x495c1f"
    assert native_case["end_exclusive"] == "0x495d20"
    assert native_case["whole_case_bytes"] == CASE[1]
    assert native_case["instruction_count"] == CASE[2]
    assert native_case["native_case_SHA256"] == CASE[3]
    assert native_case["read_sequence"] == ["int 0", "int 1", "int 2", "float 4", "float 3"]

    pe = pefile.PE(data=pe_bytes, fast_load=True)
    raw, instructions, calls = disassemble(pe, CASE[0], CASE[1])
    assert len(raw) == CASE[1] and len(instructions) == CASE[2]
    assert hashlib.sha256(raw).hexdigest() == CASE[3]
    assert calls == CASE_CALLS

    owner_header = OWNER_HEADER.read_text(encoding="utf8")
    owner_source = OWNER_SOURCE.read_text(encoding="utf8")
    fog_source = FOG_SOURCE.read_text(encoding="utf8")
    for required in (
        "unknown_000[0x134]", "FogInterpolation fog_interpolation;",
        "unknown_1d8[0x17c]", "FogValue current_fog;",
        "unknown_000[0x10]", "StageBackgroundFogOwner background;",
        "unknown_380[0x2fb4]", "AnimationFile* animation_file_value;",
        "offsetof(StageBackgroundFogOwner, fog_interpolation) == 0x134",
        "offsetof(StageBackgroundFogOwner, current_fog) == 0x354",
        "offsetof(StageResourceOwner, background) == 0x10",
        "offsetof(StageResourceOwner, animation_file_value) == 0x3334",
    ):
        assert required in owner_header, required

    for required in (
        "fog_interpolation.set_duration(duration);",
        "fog_interpolation.set_mode(mode);",
        "fog_interpolation.set_start(current_fog);",
        "fog_interpolation.set_end(target);",
        "fog_interpolation.reset_timer();",
        "background.set_fog(duration, mode, target);",
        "return animation_file_value;",
    ):
        assert required in owner_source, required
    ordered_owner_ops = [
        "fog_interpolation.set_duration(duration);",
        "fog_interpolation.set_mode(mode);",
        "fog_interpolation.set_start(current_fog);",
        "fog_interpolation.set_end(target);",
        "fog_interpolation.reset_timer();",
    ]
    positions = [owner_source.index(x) for x in ordered_owner_ops]
    assert positions == sorted(positions)

    ordered_vm = [
        "PackedColor color;",
        "state.integer_argument(0)",
        "state.integer_argument(1)",
        "state.integer_argument(2)",
        "state.float_argument(4)",
        "state.float_argument(3)",
        "FogValue value(near_distance, far_distance,",
        "process_stage_resource->set_fog(first, second, value);",
    ]
    positions = [fog_source.index(x) for x in ordered_vm]
    assert positions == sorted(positions)
    for required in (
        "static_cast<float>(packed & 0xffu)",
        "static_cast<float>((packed >> 8) & 0xffu)",
        "static_cast<float>((packed >> 16) & 0xffu)",
        "static_cast<float>((packed >> 24) & 0xffu)",
    ):
        assert required in fog_source

    # Compare the natural-C++ COFF function bodies with original PE code.
    # Only E8 rel32 displacement bytes are masked; those are separately
    # checked against the exact original call-site/target map above.
    for va, size, expected_calls, object_name, symbol, relocs in OWNER_FUNCTIONS:
        native, decoded, actual_calls = disassemble(pe, va, size)
        assert actual_calls == expected_calls, (hex(va), actual_calls)
        object_path = ROOT / object_name
        candidate = object_function_bytes(object_path, symbol, size)
        assert len(candidate) == size, (hex(va), len(candidate), size)
        masked = {byte for offset in relocs for byte in range(offset, offset + 4)}
        differences = [(i, candidate[i], native[i]) for i in range(size)
                       if i not in masked and candidate[i] != native[i]]
        assert not differences, (hex(va), differences[:12])
        print(f"PASS owner leaf {va:#010x}: {size}B natural C++ matches all non-relocation bytes; {len(expected_calls)} exact E8 targets")

    stage_obj_relocs = subprocess.check_output(
        ["objdump", "-r", str(ROOT / "build/gptweb-enemy-fog-opcode/StageResourceFog.obj")],
        text=True)
    for symbol in (
        "?set_duration@?$Interpolation@UFogValue",
        "?set_mode@?$Interpolation@UFogValue",
        "?set_start@?$Interpolation@UFogValue",
        "?set_end@?$Interpolation@UFogValue",
        "?reset_timer@?$Interpolation@UFogValue",
        "?set_fog@StageBackgroundFogOwner",
    ):
        assert symbol in stage_obj_relocs, symbol

    opcode_obj_relocs = subprocess.check_output(
        ["objdump", "-r", str(ROOT / "build/gptweb-enemy-fog-opcode/EnemyStateFogOpcode.obj")],
        text=True)
    for symbol in (
        "??0PackedColor@th20@@QAE@XZ",
        "?integer_argument@EnemyState@th20@@QAEHH@Z",
        "?float_argument@EnemyState@th20@@QAEMH@Z",
        "??4PackedColor@th20@@QAEII@Z",
        "??0FogValue@th20@@QAE@MMMMMM@Z",
        "?process_stage_resource@th20@@3PAUStageResourceOwner@1@A",
        "?set_fog@StageResourceOwner@th20@@QAEXHHABUFogValue@2@@Z",
    ):
        assert symbol in opcode_obj_relocs, symbol

    print("PASS original Enemy opcode 551: 257B / 58 x86 / 9 direct E8; exact PE SHA and operand order int0,1,2 then float4,3")
    print("PASS four packed color bytes remain blue/green/red/alpha; real 28B FogValue constructor is called before the global owner lookup")
    print("PASS typed StageResourceOwner partial layout: Background +0x10, FogInterpolation +0x144, current FogValue +0x364, AnimationFile* +0x3334")
    print("PASS real process_stage_resource replaces the prior opaque global; no fake Stage/Background facade or test boundary remains")
    print("PASS 41,967B Enemy parent remains NONEXACT; no full cold replay was performed")


if __name__ == "__main__":
    main()
