#!/usr/bin/env python3
"""Verify Enemy opcode 620's shared queued-record vector update against the locked PE."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStateSharedQueuedParametersOpcode.cpp"
BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
OPCODE = 620
START = 0x00492D4D
SIZE = 250
EXPECTED_SHA256 = "8f8b5e30c38cf65b1e12317a2968d16922826c6078745e2524911ae0cd296a3d"
EXPECTED_CALL_SITES = [
    (0x00492D55, 0x004AB080),  # integer operand 0
    (0x00492D74, 0x00498D10),  # ensure-only shared_shot selector
    (0x00492D80, 0x0040B280),  # std::move(pair)
    (0x00492D89, 0x0048B180),  # std::get<0>(pair&&)
    (0x00492D9E, 0x0040B280),  # std::move(pair)
    (0x00492DA7, 0x0048B160),  # std::get<1>(pair&&)
    (0x00492DBD, 0x004AAFB0),  # float operand 1
    (0x00492DE5, 0x004AAFB0),  # float operand 2
]


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    selector = pe.get_data(SELECTOR_TABLE - image_base, 704)
    pointers = struct.unpack("<174I", pe.get_data(POINTER_TABLE - image_base, 696))
    assert selector[OPCODE - 300] == 138
    assert pointers[selector[OPCODE - 300]] == START

    raw = pe.get_data(START - image_base, SIZE)
    assert len(raw) == SIZE
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA256
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, START))
    assert len(instructions) == 57
    calls = [
        (instruction.address, int(instruction.op_str, 16))
        for instruction in instructions
        if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
    ]
    compare = next(instruction for instruction in instructions if instruction.address == 0x00492E15)
    unordered_branch = next(instruction for instruction in instructions if instruction.address == 0x00492E19)
    assert compare.mnemonic == "comiss" and "xmm0" in compare.op_str and "+ 0x40" in compare.op_str
    assert unordered_branch.mnemonic == "jbe" and int(unordered_branch.op_str, 16) == 0x00492E2D
    assert calls == EXPECTED_CALL_SITES, [
        (hex(address), hex(target)) for address, target in calls
    ]

    assert pe.get_data(0x0056FD74 - image_base, 4) == struct.pack("<f", -990.0)
    assert pe.get_data(0x0056C8CC - image_base, 4) == struct.pack("<f", 1.0)

    source = SOURCE.read_text(encoding="utf8")
    assert "extern const float native_speed_override_threshold;" in source
    assert "extern const float native_one_56c8cc;" in source
    assert "pair_first_address" not in source
    assert "pair_second_address" not in source
    start = source.index("    case 620:")
    end = source.index("        return true;", start)
    branch = source[start:end]
    order = [
        "state.integer_argument(0)",
        "state.shared_shot(",
        "std::get<0>(std::move(selected))",
        "std::get<1>(std::move(selected))",
        "state.float_argument(1)",
        "record->vector_40.x = x",
        "state.float_argument(2)",
        "record->vector_40.y = y",
        "if (x < native_speed_override_threshold)",
        "record->vector_40.z = 0.0f",
        "record->vector_40.z = native_one_56c8cc",
    ]
    positions = []
    cursor = 0
    for item in order:
        position = branch.index(item, cursor)
        positions.append(position)
        cursor = position + len(item)
    assert "writable_shot" not in branch
    assert "std::addressof" not in branch
    assert "metadata" in branch and "(void)metadata;" in branch

    test_source = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    assert "std::numeric_limits<float>::quiet_NaN()" in test_source
    assert "std::isnan(queued_record_620.vector_40.x)" in test_source
    assert "queued_record_620.vector_40.z == 1.0f" in test_source

    print("PASS original Enemy opcode 620: 250B / 57 x86 / 8 ordered direct E8 calls")
    print("PASS selector index 138, exact branch SHA-256 and all eight native call-site/target pairs")
    print("PASS original -990.0f threshold at 0x56FD74 and 1.0f constant at 0x56C8CC")
    print("PASS natural C++ ensure-only shared_shot, std::move/std::get pair extraction and ordered X/Y writes")
    print("PASS COMISS/JBE unordered NaN behavior in the native threshold-controlled Z lane")
    print("PASS source fragment only; no writable COW and no 41,967B parent byte credit")


if __name__ == "__main__":
    main()
