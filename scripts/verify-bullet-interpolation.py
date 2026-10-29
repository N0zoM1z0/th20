#!/usr/bin/env python3
"""Verify seven original TH20 Bullet interpolation methods against real PE x86.

This reads the immutable TH20 target, real compiled complete C++ methods, native
original Bullet E8 sites, original Timer call and canonical strict receipts.
It does not compile sources, create matches, or perform a global cold replay.
"""
from __future__ import annotations

from pathlib import Path
import csv
import runpy
import struct
import subprocess
import sys
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent.parent
BULLET_HEAD = 0x0047DCF0
BULLET_BYTES = 12140

# Unit name, genuine complete original physical head, whole body size,
# real original command E8 site, actual Bullet interpolation member offset.
ORIGINAL = (
    ("vector3_interpolation_tangent_start", 0x00439480, 38, 0x004803E7, 0x420),
    ("vector3_interpolation_tangent_end", 0x00438B20, 38, 0x00480408, 0x420),
    ("float_interpolation_tangent_start", 0x00439460, 24, 0x00480873, 0x474),
    ("float_interpolation_tangent_end", 0x00438B00, 24, 0x004808A3, 0x474),
    ("vector3_interpolation_reset_timer", 0x004396A0, 25, 0x0048046C, 0x420),
    ("float_interpolation_reset_timer", 0x004395B0, 25, 0x00480903, 0x474),
    ("vector3_interpolation_set_mode", 0x004394F0, 25, 0x0048045B, 0x420),
)


def original_e8_target(pe: bytes, oracle: dict, address: int) -> int:
    data = oracle["pe_bytes_at"](pe, address, 5)
    assert data[:1] == b"\xE8", f"Original {address:#010x} is not direct E8"
    return (address + 5 + struct.unpack_from("<i", data, 1)[0]) & 0xFFFFFFFF


def main() -> None:
    sys.path.insert(0, str(ROOT / "scripts"))
    oracle = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    pe = oracle["verified_target"]()
    with (ROOT / "config/match-units.toml").open("rb") as file:
        units = tomllib.load(file)["units"]

    dis = Cs(CS_ARCH_X86, CS_MODE_32)
    boss = list(
        dis.disasm(
            oracle["pe_bytes_at"](pe, BULLET_HEAD, BULLET_BYTES), BULLET_HEAD
        )
    )
    assert len(boss) == 2490
    assert boss[-1].address + boss[-1].size == BULLET_HEAD + BULLET_BYTES
    instruction_at = {op.address: i for i, op in enumerate(boss)}

    with (ROOT / "config/matches.csv").open(newline="", encoding="utf8") as file:
        ledger = list(csv.DictReader(file))
    booked = {
        int(row["address"], 16): (int(row["size"]), row["unit"])
        for row in ledger
    }
    assert len(booked) == len(ledger)

    total_bytes = 0
    for name, address, length, callsite, offset in ORIGINAL:
        unit = units[name]
        assert unit["target_address"] == address and unit["size"] == length
        assert unit["source"] == "src/Interpolation.cpp"
        assert unit["object"] == "build/core141-canonical/Interpolation.obj"
        assert booked[address] == (length, name)
        original = list(
            dis.disasm(oracle["pe_bytes_at"](pe, address, length), address)
        )
        assert original and original[-1].address + original[-1].size == address + length
        assert original[-1].mnemonic == "ret"
        assert original_e8_target(pe, oracle, callsite) == address

        ix = instruction_at[callsite]
        preceding = boss[max(0, ix - 22):ix]
        assert any(
            op.mnemonic == "add" and op.op_str.endswith(f", 0x{offset:x}")
            for op in preceding
        ), f"{name}: original Bullet receiver offset not established"

        refs = unit["relocations"]
        if name.endswith("reset_timer"):
            assert len(refs) == 1 and refs[0]["type"] == "REL32"
            assert refs[0]["symbol"] == "??4Timer@th20@@QAEXH@Z"
            assert refs[0]["offset"] == 0x10
            assert original_e8_target(
                pe, oracle, address + refs[0]["offset"] - 1
            ) == refs[0]["target"] == 0x00423520
        else:
            assert not refs, f"{name} has unexpected native relocations"

        result = subprocess.run(
            [
                sys.executable,
                str(ROOT / "scripts/compare-coff-function.py"),
                "--unit",
                name,
            ],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=True,
        )
        assert f"{name}: exact ({length}/{length} bytes)" in result.stdout
        total_bytes += length
        print(
            f"PASS original {name}: {length}/{length} native bytes, "
            f"actual Bullet E8 at {callsite:#010x}, member +{offset:#x}"
        )

    assert total_bytes == 199
    new = {(a, a + size) for _, a, size, _, _ in ORIGINAL}
    assert len(new) == len(ORIGINAL)
    for a, b in new:
        assert not any(a < other_b and other_a < b for other_a, other_b in new if (a, b) != (other_a, other_b))
        assert not any(
            a < start + size and start < b
            for start, (size, unit) in booked.items()
            if (start, size) not in {(x, y - x) for x, y in new}
        )

    print("PASS seven complete disjoint game-authored methods: 199 original bytes")
    print(
        "The entire 12,140B Bullet::run_extended_commands parent remains "
        "source-absent and NONEXACT; do not credit its original code."
    )


if __name__ == "__main__":
    main()
