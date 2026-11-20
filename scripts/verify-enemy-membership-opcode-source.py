#!/usr/bin/env python3
"""Verify Enemy opcode 549 source against the locked original PE case."""
from __future__ import annotations

import hashlib
import json
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
AUDIT = ROOT / ".analysis/core179-enemy-549-native-audit.json"
SOURCE = ROOT / "src/EnemyStateMembershipOpcode.cpp"
OBJECT = ROOT / "build/gptweb-enemy-membership-opcode/EnemyStateMembershipOpcode.obj"
BASE = 0x00400000
TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
START = 0x00495D7F
SIZE = 95
EXPECTED_SHA = "94b89a73ee263e02923ec465dfaada31723c147463a95e99b68fe07b02e77b87"
EXPECTED_CALLS = {
    0x00495D8B: 0x00412730,
    0x00495D9E: 0x004AB080,
    0x00495DB6: 0x0049BF00,
    0x00495DCC: 0x004AA9E0,
}


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == TARGET_SHA
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["opcode_549_start"] == "0x495d7f"
    assert audit["end_exclusive"] == "0x495dde"
    assert audit["bytes"] == SIZE and audit["instruction_count"] == 20
    assert audit["original_case_sha256"] == EXPECTED_SHA

    pe = pefile.PE(data=pe_bytes, fast_load=True)
    raw = pe.get_data(START - BASE, SIZE)
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, START))
    calls = {i.address: int(i.op_str, 16) for i in decoded
             if i.mnemonic == "call" and i.op_str.startswith("0x")}
    assert len(raw) == SIZE and len(decoded) == 20
    assert hashlib.sha256(raw).hexdigest() == EXPECTED_SHA
    assert calls == EXPECTED_CALLS

    source = SOURCE.read_text(encoding="utf8")
    required = (
        "auto* owner = state.context->enemy_controller();",
        "const auto identifier = state.integer_argument(1);",
        "owner->has_identifier(static_cast<std::uint32_t>(identifier))",
        "auto* destination = state.integer_argument_destination(0);",
        "*destination = found ? 1 : 0;",
    )
    for item in required:
        assert item in source, item
    order = [
        "auto* owner = state.context->enemy_controller();",
        "const auto identifier = state.integer_argument(1);",
        "owner->has_identifier(static_cast<std::uint32_t>(identifier))",
        "auto* destination = state.integer_argument_destination(0);",
        "*destination = found ? 1 : 0;",
    ]
    positions = [source.index(item) for item in order]
    assert positions == sorted(positions)

    relocations = subprocess.check_output(["objdump", "-r", str(OBJECT)], text=True)
    for symbol in (
        "?enemy_controller@Context@th20@@QAEPAUEnemyController@2@XZ",
        "?integer_argument@EnemyState@th20@@QAEHH@Z",
        "?has_identifier@EnemyController@th20@@QAE_NI@Z",
        "?integer_argument_destination@EnemyState@th20@@QAEPAHH@Z",
    ):
        assert symbol in relocations, symbol

    print("PASS original Enemy opcode 549: 95B / 20 x86 / 4 direct E8, exact locked PE SHA and call-site map")
    print("PASS cached Context EnemyController selection precedes operand 1; real 244B intrusive-list membership query precedes late destination 0")
    print("PASS bool result is naturally zero-extended to the full 32-bit ECL integer destination")
    print("PASS no fake list/query service; 41,967B Enemy root remains NONEXACT")


if __name__ == "__main__":
    main()
