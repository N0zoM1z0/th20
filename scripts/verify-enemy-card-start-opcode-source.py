#!/usr/bin/env python3
"""Verify the 552B shared Enemy card-start opcode branch and typed leaves."""
from __future__ import annotations

import csv
import hashlib
import re
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStateCardStartOpcode.cpp"
OBJECT = ROOT / "build/gptweb-enemy-card-start-opcode/EnemyStateCardStartOpcode.obj"
TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
BASE = 0x00400000
START = 0x00494170
SIZE = 552
INSTRUCTIONS = 114
BRANCH_SHA = "0d723e73cdf35e9ae046f705434487b327ddf426ac2a9f9847b27916239d0307"
CALLS = {
    0x0049417E: 0x00544760,
    0x0049423F: 0x004AB080,
    0x00494285: 0x004640A0,
    0x0049429D: 0x004640A0,
    0x004942B9: 0x004640A0,
    0x004942DA: 0x00411700,
    0x004942ED: 0x004AB080,
    0x00494300: 0x004AB080,
    0x0049432D: 0x00487C30,
    0x0049434C: 0x0049C360,
    0x0049436E: 0x0040C300,
    0x0049437A: 0x0049C340,
    0x0049438D: 0x00423520,
}


def native_function(pe: pefile.PE, address: int, size: int):
    raw = pe.get_data(address - BASE, size)
    decoded = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
    calls = {ins.address: int(ins.op_str, 16) for ins in decoded
             if ins.mnemonic == "call" and ins.op_str.startswith("0x")}
    return raw, decoded, calls


def object_function(path: Path, symbol: str, size: int) -> bytes:
    lines = subprocess.check_output(["objdump", "-d", str(path)], text=True).splitlines()
    start = next(i for i, line in enumerate(lines) if "<" + symbol in line)
    code = bytearray()
    for line in lines[start + 1:]:
        if "<" in line and line.strip().endswith(">:"):
            break
        match = re.match(r"\s*[0-9a-f]+:\s*((?:[0-9a-f]{2}\s+)+)", line)
        if match:
            code.extend(int(value, 16) for value in match.group(1).split())
        if len(code) >= size:
            break
    assert len(code) >= size, (symbol, len(code), size)
    return bytes(code[:size])


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == TARGET_SHA
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    raw, instructions, calls = native_function(pe, START, SIZE)
    assert len(raw) == SIZE and len(instructions) == INSTRUCTIONS
    assert hashlib.sha256(raw).hexdigest() == BRANCH_SHA
    assert calls == CALLS
    assert instructions[-1].mnemonic == "jmp"
    assert int(instructions[-1].op_str, 16) == 0x004963DF

    source = SOURCE.read_text(encoding="utf8")
    required = (
        "case 522:", "case 528:", "case 531:", "case 532:", "case 533:",
        "packet + 0x1c", "packet + 0x20", "char decoded[128]{};",
        "std::uint8_t key = 0x77;", "std::uint8_t step = 7;",
        "decoded[i] = static_cast<char>(*input++ ^ key);",
        "key = static_cast<std::uint8_t>(key + step);",
        "step = static_cast<std::uint8_t>(step + 0x10u);",
        "state.integer_argument(0)", "switch (instruction.opcode)",
        "index += static_cast<std::uint32_t>(session.mode());",
        "index = index + static_cast<std::uint32_t>(session.mode()) - 1u;",
        "index = index + static_cast<std::uint32_t>(session.mode()) - 2u;",
        "auto* receiver = state.context->card();",
        "state.integer_argument(2)", "state.integer_argument(1)",
        "receiver->start_spell(static_cast<std::int32_t>(index), decoded,",
        "state.health.set_scaled_enabled(1);",
        "health->set_scaled_health(state.health.get_health());",
        "state.timer_a8 = 0;",
    )
    for item in required:
        assert item in source, item
    order = [
        "packet + 0x1c", "packet + 0x20", "char decoded[128]{};",
        "state.integer_argument(0)", "switch (instruction.opcode)",
        "auto* receiver = state.context->card();",
        "state.integer_argument(2)", "state.integer_argument(1)",
        "receiver->start_spell(", "state.health.set_scaled_enabled(1);",
        "health->set_scaled_health(state.health.get_health());",
        "state.timer_a8 = 0;",
    ]
    positions = [source.index(item) for item in order]
    assert positions == sorted(positions)
    assert source.count("session.mode()") == 3
    assert source.count("state.integer_argument(") == 3

    relocations = subprocess.check_output(["objdump", "-r", str(OBJECT)], text=True)
    expected_symbols = {
        "_memset": 1,
        "?integer_argument@EnemyState@th20@@QAEHH@Z": 3,
        "?mode@Session@th20@@QAEHXZ": 3,
        "?card@Context@th20@@QAEPAUCard@2@XZ": 1,
        "?start_spell@Card@th20@@QAEXHPBDHH@Z": 1,
        "?set_scaled_enabled@EnemyHealth@th20@@QAEXI@Z": 1,
        "?get_health@EnemyHealth@th20@@QBEIXZ": 1,
        "?set_scaled_health@EnemyHealth@th20@@QAEXI@Z": 1,
        "??4Timer@th20@@QAEXH@Z": 1,
    }
    for symbol, count in expected_symbols.items():
        assert relocations.count(symbol) == count, (symbol, relocations.count(symbol), count)

    # Two typed source owners share original leaf bodies with existing native
    # getters. This is a code-folded alias, not duplicate native byte credit.
    alias_functions = [
        ("build/core163-canonical/Context.obj", "?card@Context@th20@@QAEPAUCard@2@XZ", 0x00411700, 17, []),
        ("build/core142-canonical/FunctionChain.obj", "?shutdown_callback_value@FunctionChainNode@th20@@QAEP6AHPAX@ZXZ", 0x00411700, 17, []),
        ("build/core151-canonical/EnemyHealth.obj", "?get_health@EnemyHealth@th20@@QBEIXZ", 0x0040C300, 16, []),
        ("build/core141-canonical/Identifier32.obj", "?get@Identifier32@th20@@QBEIXZ", 0x0040C300, 16, []),
        ("build/core180-canonical/Session.obj", "?mode@Session@th20@@QAEHXZ", 0x004640A0, 25, [0x11, 0x12, 0x13, 0x14]),
        ("build/core151-canonical/EnemyHealth.obj", "?set_scaled_health@EnemyHealth@th20@@QAEXI@Z", 0x0049C340, 23, []),
        ("build/core151-canonical/EnemyHealth.obj", "?set_scaled_enabled@EnemyHealth@th20@@QAEXI@Z", 0x0049C360, 36, []),
        ("build/core141-canonical/Timer.obj", "??4Timer@th20@@QAEXH@Z", 0x00423520, 26, [0x0f, 0x10, 0x11, 0x12]),
    ]
    for object_name, symbol, address, size, masked in alias_functions:
        candidate = object_function(ROOT / object_name, symbol, size)
        original, _, _ = native_function(pe, address, size)
        ignored = set(masked)
        differences = [(i, candidate[i], original[i]) for i in range(size) if i not in ignored and candidate[i] != original[i]]
        assert not differences, (symbol, differences[:12])

    rows = {row[0].lower(): row for row in csv.reader(
        (ROOT / "config/functions.csv").read_text(encoding="utf8").splitlines())}
    for address in ("0x004640A0", "0x0049C340", "0x0049C360", "0x00423520",
                    "0x00411700", "0x0040C300"):
        assert rows[address.lower()][6] == "matching", (address, rows[address.lower()][6])
    assert rows["0x00487c30"][6] == "reconstructed"  # 1,896B Card callee remains open.

    print("PASS original shared card-start branch: 552B / 114 x86 / 13 direct E8; locked PE SHA, complete branch hash and call map")
    print("PASS raw length +0x1C and borrowed payload +0x20; 128B zeroed local and byte-wise 0x77/7 rolling XOR")
    print("PASS operand order 0 then 2 then 1; instruction opcode 531/532/533 mode correction remains three separate Session calls")
    print("PASS cached Context Card owner, 1,896B Card::start_spell call, scaled-health update and Timer reset remain ordered")
    print("PASS Context::card/FunctionChain getter and EnemyHealth/Identifier32 getter aliases match their original 17B/16B native bodies")
    print("PASS exact Session mode, EnemyHealth scaled setters and Timer assignment leaves; Card::start_spell and 41,967B Enemy parent remain NONEXACT")


if __name__ == "__main__":
    main()
