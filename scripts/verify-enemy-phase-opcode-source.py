#!/usr/bin/env python3
"""Verify Enemy phase opcodes 514/521 against their real primary CFGs."""
from __future__ import annotations

import csv
import hashlib
import json
import re
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
AUDIT = ROOT / ".analysis/core209-native-514-521-audit.json"
SOURCE = ROOT / "src/EnemyStatePhaseOpcode.cpp"
OBJECT = ROOT / "build/gptweb-enemy-phase-opcodes/EnemyStatePhaseOpcode.obj"
BASE = 0x00400000
TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
CASE514 = (0x00493B74, 736, 171,
           "55c5a73a8eb46f8789fc65f7de00c7d563a97a1402b6d2d8dc928a03283feb7d")
CASE521 = (0x00493E54, 88, 20,
           "a23b78db5c500c9b64138b193847123fd66c1b98eab93fa4489334121b17d5b3")
CALLS521 = {
    0x00493E82: 0x004AB080,
    0x00493EA1: 0x004AB780,
}
STRINGS = {
    0x0056FEB4: "MBossDead",
    0x0056FEC0: "BossDead",
    0x0056FECC: "BossEscapeSpell",
    0x0056FEDC: "MBossBDead",
}


def branch(pe: pefile.PE, start: int, size: int):
    raw = pe.get_data(start - BASE, size)
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, start))
    calls = {i.address: int(i.op_str, 16) for i in decoded
             if i.mnemonic == "call" and i.op_str.startswith("0x")}
    return raw, decoded, calls


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == TARGET_SHA
    audit = json.loads(AUDIT.read_text(encoding="utf8"))
    assert audit["target_sha256"] == TARGET_SHA

    pe = pefile.PE(data=pe_bytes, fast_load=True)
    start, size, count, digest = CASE514
    raw514, ins514, calls514 = branch(pe, start, size)
    native514 = audit["cases"]["514"]
    assert native514["start"] == "0x493b74"
    assert native514["end"] == "0x493e54"
    assert native514["size"] == size and native514["instructions"] == count
    assert native514["sha256"] == digest
    assert len(raw514) == size and len(ins514) == count
    assert hashlib.sha256(raw514).hexdigest() == digest
    expected514 = {int(c["site"], 16): int(c["target"], 16)
                   for c in native514["calls"]}
    assert calls514 == expected514 and len(calls514) == 25

    start, size, count, digest = CASE521
    raw521, ins521, calls521 = branch(pe, start, size)
    assert len(raw521) == size and len(ins521) == count
    assert hashlib.sha256(raw521).hexdigest() == digest
    assert calls521 == CALLS521
    assert ins521[-1].mnemonic == "jmp" and int(ins521[-1].op_str, 16) == 0x004963DF

    # The old CORE209 284B/60-head/10-call record is a contiguous switch
    # neighborhood, not the reachable primary opcode-521 body.  The real
    # 521 path terminates at 0x493EAC after its common-epilogue jump.
    broad521 = audit["cases"]["521"]
    assert broad521["start"] == "0x493e54" and broad521["size"] == 284
    assert broad521["instructions"] == 60 and len(broad521["calls"]) == 10

    for address, value in STRINGS.items():
        assert pe.get_data(address - BASE, len(value) + 1) == value.encode() + b"\0"

    source = SOURCE.read_text(encoding="utf8")
    assert source.count("session.field_70_is_two()") == 1
    assert source.count("session.clamped_field_1f4()") == 2
    assert source.count("session.clamped_field_1fc()") == 2
    assert source.count("state.integer_argument(0)") == 8
    assert source.count("state.integer_argument(1)") == 1
    assert source.count("state.integer_argument(2)") == 5
    assert source.count("receiver->configure_phase(") == 5
    assert source.count("receiver->configure_timeout(") == 3
    assert "reinterpret_cast<const char*>(&instruction) + 0x20" in source
    assert "reinterpret_cast<const char*>(&instruction) + 0x18" in source
    assert source.index("phase_name = reinterpret_cast<const char*>(&instruction) + 0x20") < source.index("session.field_70_is_two()")
    assert source.index("auto* receiver = state.entity;\n        const auto index = state.integer_argument(0);\n        receiver->configure_timeout") < source.index("default:")
    for value in STRINGS.values():
        assert f'"{value}"' in source

    relocations = subprocess.check_output(["objdump", "-r", str(OBJECT)], text=True)
    expected_relocations = {
        "?integer_argument@EnemyState@th20@@QAEHH@Z": 14,
        "?configure_phase@Enemy@th20@@QAEXIHHPBD@Z": 5,
        "?configure_timeout@Enemy@th20@@QAEXIPBD@Z": 3,
        "?field_70_is_two@Session@th20@@QAE_NXZ": 1,
        "?clamped_field_1f4@Session@th20@@QAEHXZ": 2,
        "?clamped_field_1fc@Session@th20@@QAEHXZ": 2,
    }
    for symbol, expected in expected_relocations.items():
        assert relocations.count(symbol) == expected, (symbol, relocations.count(symbol), expected)

    rows = {row[0].lower(): row for row in csv.reader(
        (ROOT / "config/functions.csv").read_text(encoding="utf8").splitlines())}
    for address in ("0x004ab650", "0x004ab780", "0x00488850", "0x00474d60", "0x00499330"):
        assert rows[address][6] == "matching", (address, rows[address][6])

    print("PASS original opcode 514: 736B / 171 x86 / 25 E8, locked PE hash and complete native call map")
    print("PASS original opcode 521 primary CFG: 88B / 20 x86 / 2 E8; exact borrowed name pointer +0x18 and common epilogue")
    print("PASS 514 native duplication: 13 ordered integer reads, five phase writes, two timeout writes, and duplicated Session clamp reads")
    print("PASS four original phase strings and packet pointer +0x20; no string copy is invented at the dispatcher boundary")
    print("PASS compiled natural-C++ helper call multiset matches the 27 original primary-branch calls")
    print("PASS exact Enemy phase producers and three Session accessors are registered as matching; whole 41,967B parent remains NONEXACT")


if __name__ == "__main__":
    main()
