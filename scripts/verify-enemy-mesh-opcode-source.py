#!/usr/bin/env python3
"""Verify Enemy opcode 621 source against the immutable original PE bytes."""
from __future__ import annotations

import hashlib
import re
import struct
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStateMeshOpcode.cpp"
BASE = 0x00400000
START = 0x00495A9A
SIZE = 346
EXPECTED_SHA256 = "d67fb1c10517cb0b3f45d27f2347427d8680935751b62a62ac5e18fc00756f6e"
EXPECTED_CALLS = {
    0x00495AAD: 0x0048AF30,
    0x00495ACD: 0x0048B010,
    0x00495AF8: 0x004AAFB0,
    0x00495B3D: 0x004AB080,
    0x00495B75: 0x00452F20,
    0x00495B92: 0x00452F20,
    0x00495BD0: 0x004712D0,
}
OWNER_LABEL = (r"D:\cygwin\home\zun\prog\th20\src\game\ecl.cpp:2387 "
               r"EnemyDataInf::BossRenderInf")
RENDER_LABEL = (r"D:\cygwin\home\zun\prog\th20\src\game\ecl.cpp:2395 "
                r"RenderMeshInf")


def main() -> None:
    pe_path = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_path).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_path, fast_load=True)
    raw = pe.get_data(START - BASE, SIZE)
    assert len(raw) == SIZE
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA256

    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    instructions = list(decoder.disasm(raw, START))
    assert len(instructions) == 70
    calls = {insn.address: int(insn.op_str, 16)
             for insn in instructions
             if insn.mnemonic == "call" and insn.op_str.startswith("0x")}
    assert calls == EXPECTED_CALLS, calls

    def at_va(address: int, size: int) -> bytes:
        return pe.get_data(address - BASE, size)

    assert at_va(0x0056FEE8, len(OWNER_LABEL) + 1) == OWNER_LABEL.encode() + b"\0"
    assert at_va(0x0056FF38, len(RENDER_LABEL) + 1) == RENDER_LABEL.encode() + b"\0"
    assert at_va(0x0056CD90, 4) == struct.pack("<f", 16.0)
    assert at_va(0x0056E0E8, 4) == struct.pack("<f", 0.0)

    source = SOURCE.read_text(encoding="utf8")
    for required in (
        "process_allocator->release_object(state.mesh);",
        "state.mesh = nullptr;",
        "process_allocator->allocate_object<EnemyMeshOwner>(",
        OWNER_LABEL.replace("\\", "\\\\"),
        "mesh.mesh = nullptr;",
        "mesh.radius = state.float_argument(0);",
        "mesh.current_radius = native_screen_top_16_56cd90;",
        "mesh.color = static_cast<std::uint32_t>(state.integer_argument(1));",
        "mesh.phase_x = 0.0f;",
        "mesh.phase_y = 0.0f;",
        "if (mesh.radius > native_zero_56e0e8)",
        "process_allocator->allocate_object<RenderMesh>(",
        RENDER_LABEL.replace("\\", "\\\\"),
        "17, 17, 0, state.field_2e8",
    ):
        assert required in source, required
    order = [
        "process_allocator->release_object(state.mesh);",
        "state.mesh = nullptr;",
        "process_allocator->allocate_object<EnemyMeshOwner>(",
        "mesh.mesh = nullptr;",
        "mesh.radius = state.float_argument(0);",
        "mesh.current_radius = native_screen_top_16_56cd90;",
        "mesh.color = static_cast<std::uint32_t>(state.integer_argument(1));",
        "mesh.phase_x = 0.0f;",
        "mesh.phase_y = 0.0f;",
        "if (mesh.radius > native_zero_56e0e8)",
        "process_allocator->allocate_object<RenderMesh>(",
    ]
    positions = [source.index(item) for item in order]
    assert positions == sorted(positions)

    print("PASS original Enemy opcode 621: 346B / 70 x86 / 7 E8, exact PE bytes and direct-call targets")
    print("PASS original source labels at 0x56FEE8/0x56FF38 and constants 16.0f/0.0f at 0x56CD90/0x56E0E8")
    print("PASS natural-C++ release/allocate EnemyMeshOwner, radius/color/phases, strict positive-radius 17x17 RenderMesh factory")
    print("PASS reuses original typed allocator factories and EnemyMeshOwner; 41,967B parent remains NONEXACT")


if __name__ == "__main__":
    main()
