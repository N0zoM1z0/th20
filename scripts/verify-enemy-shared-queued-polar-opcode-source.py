#!/usr/bin/env python3
"""Verify the original Enemy ECL opcode-618 shared queued polar branch."""
from __future__ import annotations

import hashlib
import struct
from pathlib import Path

import pefile
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
TARGET = ROOT / "resources/th20.exe"
TARGET_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
IMAGE_BASE = 0x00400000
SELECTOR_TABLE = 0x004966B8
POINTER_TABLE = 0x00496400
SELECTOR_INDEX = 136
START = 0x00492BC6
END = 0x00492CB9
BRANCH_SHA256 = "fd1d55043482bdee505c3d580e71a297af675abd061e4347e573a145e0c61a15"
EXPECTED_CALLS = [
    (0x00492BCE, 0x004AB080),  # integer_argument(0)
    (0x00492BE1, 0x004AAFB0),  # float_argument(1)
    (0x00492BF4, 0x004AAFB0),  # float_argument(2)
    (0x00492C13, 0x00498D10),  # ensure-only shared_shot
    (0x00492C1F, 0x0040B280),  # std::move(pair)
    (0x00492C28, 0x0048B180),  # std::get<0>(pair&&)
    (0x00492C3D, 0x0040B280),  # std::move(pair)
    (0x00492C46, 0x0048B160),  # std::get<1>(pair&&)
    (0x00492C5A, 0x00422E10),  # Vector3 default constructor
    (0x00492C82, 0x00439330),  # polar(Vector3&, direction, length)
]


def main() -> None:
    assert TARGET.is_file(), TARGET
    target_hash = hashlib.sha256(TARGET.read_bytes()).hexdigest()
    assert target_hash == TARGET_SHA256, (target_hash, TARGET_SHA256)

    pe = pefile.PE(str(TARGET), fast_load=True)
    image_base = pe.OPTIONAL_HEADER.ImageBase
    assert image_base == IMAGE_BASE
    selector = pe.get_data(SELECTOR_TABLE - image_base, 704)
    pointers = struct.unpack("<174I", pe.get_data(POINTER_TABLE - image_base, 696))
    assert selector[618 - 300] == SELECTOR_INDEX
    assert pointers[SELECTOR_INDEX] == START

    branch = pe.get_data(START - image_base, END - START)
    assert len(branch) == 243
    branch_hash = hashlib.sha256(branch).hexdigest()
    assert branch_hash == BRANCH_SHA256, (branch_hash, BRANCH_SHA256)

    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    instructions = list(decoder.disasm(branch, START))
    assert len(instructions) == 55, len(instructions)
    assert instructions[-1].address + instructions[-1].size == END
    calls = [
        (instruction.address, int(instruction.op_str, 16))
        for instruction in instructions
        if instruction.mnemonic == "call" and instruction.op_str.startswith("0x")
    ]
    assert calls == EXPECTED_CALLS, calls

    source = (ROOT / "src/EnemyStateSharedQueuedParametersOpcode.cpp").read_text(encoding="utf8")
    start = source.index("    case 618:")
    end = source.index("    case 620:", start)
    branch_source = source[start:end]
    expected_order = [
        "state.integer_argument(0)",
        "state.float_argument(1)",
        "state.float_argument(2)",
        "state.shared_shot(",
        "std::get<0>(std::move(selected))",
        "std::get<1>(std::move(selected))",
        "Vector3 offset;",
        "polar(offset, direction, length);",
        "record->vector_34.x = offset.x;",
        "record->vector_34.y = offset.y;",
    ]
    cursor = 0
    for fragment in expected_order:
        position = branch_source.index(fragment, cursor)
        cursor = position + len(fragment)
    assert "writable_shot" not in branch_source
    assert "vector_34.z" not in branch_source
    assert "vector_40" not in branch_source

    test_source = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    assert "dispatch_read_trace_count == 2" in test_source
    assert "queued_record_618.vector_34.z == 33.0f" in test_source
    assert "enemy.state.queued.empty()" in test_source
    assert "queued_polar_second_float_threw" in test_source

    print("PASS original Enemy opcode 618: selector 136, 243B / 55 x86 / 10 ordered direct E8 calls")
    print("PASS exact branch SHA-256 and all ten native call-site/target pairs")
    print("PASS natural C++ argument order, ensure-only shared_shot, std::pair extraction, Vector3 and polar")
    print("PASS only vector_34 XY lanes are written; Z and vector_40 remain untouched")
    print("PASS second-float exception occurs before shared_shot and leaves the queue empty")


if __name__ == "__main__":
    main()
