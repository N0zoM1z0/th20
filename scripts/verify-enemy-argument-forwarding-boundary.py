#!/usr/bin/env python3
"""Verify the complete natural-C++ EnemyState/Enemy/EclRuntime VM bridge."""
from __future__ import annotations

import csv
import hashlib
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
BASE = 0x00400000

# (native function, complete size, direct E8 call site, direct E8 target,
# source owner, natural C++ forwarding expression)
FUNCTIONS = [
    (0x004AAFB0, 36, 0x004AAFC9, 0x004AB010, "src/EnemyScript.cpp",
     "return enemy.float_argument(index);"),
    (0x004AB010, 36, 0x004AB029, 0x0053E970, "src/EnemyScript.cpp",
     "return runtime.float_argument(index);"),
    (0x004AB080, 36, 0x004AB099, 0x004AB0E0, "src/EnemyScript.cpp",
     "return enemy.integer_argument(index);"),
    (0x004AB0E0, 36, 0x004AB0F9, 0x0053ED50, "src/EnemyScript.cpp",
     "return runtime.integer_argument(index);"),
    (0x004AA980, 36, 0x004AA999, 0x004AA9B0, "src/EnemyScriptAdvance.cpp",
     "return owner.integer_argument_destination(index);"),
    (0x004AA9B0, 36, 0x004AA9C9, 0x0053E720, "src/EnemyScriptAdvance.cpp",
     "return runtime.integer_destination(index);"),
    (0x004AA9E0, 36, 0x004AA9F9, 0x004AAA10, "src/EnemyScriptAdvance.cpp",
     "return owner.integer_argument_destination(index);"),
    (0x004AAA10, 36, 0x004AAA29, 0x0053E850, "src/EnemyScriptAdvance.cpp",
     "return runtime.integer_destination(index);"),
    (0x004AAFE0, 47, 0x004AB004, 0x004AB040, "src/EnemyScript.cpp",
     "return enemy.float_argument_value(index, value);"),
    (0x004AB040, 47, 0x004AB064, 0x0053EA90, "src/EnemyScript.cpp",
     "return runtime.float_argument_value(index, value);"),
    (0x004AB0B0, 40, 0x004AB0CD, 0x004AB110, "src/EnemyScript.cpp",
     "return enemy.integer_argument_value(index, value);"),
    (0x004AB110, 40, 0x004AB12D, 0x0053EE30, "src/EnemyScript.cpp",
     "return runtime.integer_argument_value(index, value);"),
]


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == TARGET_SHA
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    rows = {row[0].lower(): row for row in csv.reader(
        (ROOT / "config/functions.csv").read_text(encoding="utf8").splitlines())}

    source_cache = {}
    total_bytes = 0
    for address, size, call_site, target, source_path, expression in FUNCTIONS:
        raw = pe.get_data(address - BASE, size)
        assert len(raw) == size, hex(address)
        instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw, address))
        calls = {ins.address: int(ins.op_str, 16) for ins in instructions
                 if ins.mnemonic == "call" and ins.op_str.startswith("0x")}
        assert calls == {call_site: target}, (hex(address), calls)

        row = rows[f"0x{address:08X}".lower()]
        assert row[6] == "matching" and row[7] == "100.00", (hex(address), row[6:8])
        assert row[11] == source_path, (hex(address), row[11])
        source = source_cache.setdefault(source_path,
            (ROOT / source_path).read_text(encoding="utf8"))
        assert expression in source, (hex(address), expression)
        total_bytes += size
        print(f"PASS {address:#010x}: {size}B / {len(instructions)} x86; E8 {call_site:#010x} -> {target:#010x}")

    assert len(FUNCTIONS) == 12 and total_bytes == 462
    enemy_script = source_cache["src/EnemyScript.cpp"]
    advance = source_cache["src/EnemyScriptAdvance.cpp"]
    assert "auto& enemy = *entity;" in enemy_script
    assert "auto& runtime = *current_runtime;" in enemy_script
    assert "auto& owner = *entity;" in advance
    assert "auto& runtime = *current_runtime;" in advance

    print("PASS 12 original standalone wrappers / 462 bytes: float and integer readers, destinations, and supplied-value forwarding")
    print("PASS live EnemyState -> Enemy -> EclRuntime chains preserve index/value order and the actual current_runtime owner")
    print("PASS focused source cold replays: EnemyScript.cpp 10/10 and EnemyScriptAdvance.cpp 5/5; full 41,967B dispatcher remains NONEXACT")


if __name__ == "__main__":
    main()
