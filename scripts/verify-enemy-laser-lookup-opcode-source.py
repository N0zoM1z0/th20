#!/usr/bin/env python3
"""Verify the original inline Enemy opcode-704 Laser position mutation."""
from __future__ import annotations

import hashlib
import re
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE = ROOT / "resources/th20.exe"
PE_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
START = 0x00494FD3
END = 0x00495083
SIZE = END - START
SHA256 = "e348b0806a20d6a2fb48e480d00ac785d21a6845be8374e2217965e34fd079df"
SELECTOR_TABLE = 0x004966B8
IMAGE_BASE = 0x00400000
OBJECT = ROOT / "build/core223-canonical/EnemyStateLaserOpcode.obj"
SYMBOL = "?execute_enemy_laser_lookup_opcode@th20@@YA_NAAUEnemyState@1@H@Z"

NATIVE_CALLS = [
    (0x00494FDF, 0x0041CA90),  # Context::laser_controller
    (0x00494FF2, 0x004AB080),  # EnemyState::integer_argument(0)
    (0x0049500A, 0x00498FF0),  # LaserController::find_laser
    (0x0049501B, 0x00422E10),  # zero Vector3 construction
    (0x00495028, 0x004AAFB0),  # EnemyState::float_argument(1)
    (0x0049503B, 0x004AAFB0),  # EnemyState::float_argument(2)
]

COFF_CALLS = [
    "?laser_controller@Context@th20@@QAEPAVLaserController@2@XZ",
    "?integer_argument@EnemyState@th20@@QAEHH@Z",
    "?find_laser@LaserController@th20@@QAEPAVLaser@2@H@Z",
    "??0Vector3@th20@@QAE@XZ",
    "?float_argument@EnemyState@th20@@QAEMH@Z",
    "?float_argument@EnemyState@th20@@QAEMH@Z",
    "@__security_check_cookie@4",
]


def main() -> None:
    pe_bytes = PE.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == PE_SHA256
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    native = pe.get_data(START - pe.OPTIONAL_HEADER.ImageBase, SIZE)
    assert len(native) == 176
    assert hashlib.sha256(native).hexdigest() == SHA256

    selectors = pe.get_data(SELECTOR_TABLE - pe.OPTIONAL_HEADER.ImageBase, 704 - 300 + 1)
    assert selectors[704 - 300] == 156
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(native, START))
    assert len(instructions) == 37
    assert instructions[0].address == START
    assert instructions[-1].address + instructions[-1].size == END
    assert instructions[-1].mnemonic == "jmp" and instructions[-1].op_str == "0x4963df"
    calls = [
        (insn.address, int(insn.op_str, 16))
        for insn in instructions
        if insn.mnemonic == "call" and insn.op_str.startswith("0x")
    ]
    assert calls == NATIVE_CALLS, calls
    indirect = [insn for insn in instructions if insn.mnemonic == "call" and not insn.op_str.startswith("0x")]
    assert len(indirect) == 1
    assert indirect[0].address == 0x00495077
    assert indirect[0].op_str == "dword ptr [ebp - 0xed8]"

    # Native order is Context capture, handle read/search, Vector3 ctor,
    # float operands 1/2, then a conditional virtual set_position call.
    native_ops = "\n".join(f"{insn.mnemonic} {insn.op_str}" for insn in instructions)
    assert native_ops.index("call 0x498ff0") < native_ops.index("call 0x422e10")
    assert native_ops.index("call 0x422e10") < native_ops.index("call 0x4aafb0")
    assert native_ops.count("call 0x4aafb0") == 2
    assert "cmp dword ptr [ebp - 0x588], 0" in native_ops
    assert "movss dword ptr [ebp - 0x100], xmm0" in native_ops

    source = (ROOT / "src/EnemyStateLaserOpcode.cpp").read_text(encoding="utf8")
    start = source.index("bool execute_enemy_laser_lookup_opcode")
    end = source.index("bool execute_enemy_laser_opcode", start)
    helper = source[start:end]
    for fragment in (
        "if (opcode != 704) return false;",
        "state.context->laser_controller()",
        "state.integer_argument(0)",
        "controller->find_laser(handle)",
        "Vector3 position;",
        "state.float_argument(1)",
        "state.float_argument(2)",
        "position.z = 0.0f;",
        "laser->set_position(position);",
    ):
        assert fragment in helper, fragment
    assert helper.index("laser_controller()") < helper.index("integer_argument(0)")
    assert helper.index("find_laser(handle)") < helper.index("float_argument(1)")
    assert helper.index("float_argument(1)") < helper.index("float_argument(2)")
    assert helper.index("float_argument(2)") < helper.index("set_position(position)")

    tests = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    for fragment in (
        "set_packet(704, {static_cast<std::uint32_t>(-101),bits(-102.0f),bits(-103.0f)",
        "retarget_context_during_integer_read",
        "retarget_context_player_during_first_float_read",
        "dispatch_integer_read_value = static_cast<std::int32_t>(0xdeadbeefu)",
        "laser_704_integer_threw",
        "laser_704_second_float_threw",
        "laser_704_primary.position_calls == 2",
        "laser_704_alternate.position_calls == 0",
    ):
        assert fragment in tests, fragment

    dump = subprocess.run(
        ["objdump", "-dr", str(OBJECT)], cwd=ROOT, check=True,
        text=True, capture_output=True,
    ).stdout
    marker = f"<{SYMBOL}>:"
    assert marker in dump
    function = dump.split(marker, 1)[1].split("Disassembly of section", 1)[0]
    coff_calls = re.findall(r"DISP32\s+([^\r\n]+)", function)
    assert len(coff_calls) == len(COFF_CALLS), (coff_calls, COFF_CALLS)
    for actual, expected in zip(coff_calls, COFF_CALLS):
        assert expected in actual, (actual, expected)
    assert "call   *-0x20(%ebp)" in function
    assert function.index("?find_laser@LaserController") < function.index("??0Vector3@th20")
    assert function.index("??0Vector3@th20") < function.index("?float_argument@EnemyState")
    assert function.count("?float_argument@EnemyState") == 2
    assert "0x8c(" not in function

    print("PASS original Enemy opcode 704: selector 156, 176B / 37 x86 / six ordered direct E8 calls plus conditional set_position vcall")
    print("PASS native Context capture, handle lookup, Vector3 construction, float operands 1/2 and common epilogue order")
    print("PASS natural C++ COFF preserves Context/handle/find/Vector3/float/float/vcall order")
    print("PASS root-host retargeting, missing handle, handle exception and second-float exception-before-virtual-mutation")


if __name__ == "__main__":
    main()
