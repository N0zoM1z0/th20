#!/usr/bin/env python3
"""Verify complete original 46B/54B Bullet shared_ptr STL move native code.

Reads the immutable TH20 original PE, true original caller sites, the genuine
pinned MSVC template COFF and three canonical exact receipts. Does not build
any source, patch object files, or invoke an unfiltered cold replay.
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
ORIGINAL = (
    ("shot_shared_ptr_move_ctor_library", 0x0047B820, 46, 18),
    ("shot_ptr_base_move_construct_from_library", 0x0047ADA0, 54, 19),
)


def e8_target(pe: bytes, tool: dict, site: int) -> int:
    code = tool["pe_bytes_at"](pe, site, 5)
    assert code[0] == 0xE8
    return (site + 5 + struct.unpack_from("<i", code, 1)[0]) & 0xFFFFFFFF


def main() -> None:
    sys.path.insert(0, str(ROOT / "scripts"))
    tool = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    pe = tool["verified_target"]()
    with (ROOT / "config/match-units.toml").open("rb") as file:
        units = tomllib.load(file)["units"]
    with (ROOT / "config/matches.csv").open(newline="", encoding="utf8") as file:
        authored = list(csv.DictReader(file))
    accepted = {
        int(row["address"], 16): (int(row["size"]), row["unit"])
        for row in authored
    }
    assert len(accepted) == len(authored)
    dis = Cs(CS_ARCH_X86, CS_MODE_32)

    for name, address, size, heads in ORIGINAL:
        unit = units[name]
        assert (unit["target_address"], unit["size"]) == (address, size)
        assert unit["source"] == "src/ShotSharedPtrMoveLegacy.cpp"
        assert address not in accepted
        original_ops = list(dis.disasm(tool["pe_bytes_at"](pe, address, size), address))
        assert len(original_ops) == heads
        assert original_ops[-1].address + original_ops[-1].size == address + size
        assert original_ops[-1].mnemonic == "ret"
        result = subprocess.run(
            [sys.executable, str(ROOT / "scripts/compare-coff-function.py"), "--unit", name],
            cwd=ROOT,
            capture_output=True,
            text=True,
            check=True,
        )
        assert f"{name}: exact ({size}/{size} bytes)" in result.stdout
        print(f"PASS original {name}: {size}/{size} whole native bytes")

    ctor = units[ORIGINAL[0][0]]
    assert [r["type"] for r in ctor["relocations"]] == ["REL32"] * 3
    assert [(r["offset"], r["target"]) for r in ctor["relocations"]] == [
        (11, 0x00414030),
        (20, 0x0040B280),
        (32, 0x0047ADA0),
    ]
    for r in ctor["relocations"]:
        assert e8_target(pe, tool, ctor["target_address"] + r["offset"] - 1) == r["target"]
    assert not units[ORIGINAL[1][0]]["relocations"]

    boss = list(dis.disasm(tool["pe_bytes_at"](pe, 0x0047DCF0, 12140), 0x0047DCF0))
    assert len(boss) == 2490
    assert e8_target(pe, tool, 0x0047F935) == 0x0047B820
    assert e8_target(pe, tool, 0x0047C549) == 0x0047B820
    assert e8_target(pe, tool, 0x0047B83F) == 0x0047ADA0

    old = units["shot_shared_ptr_legacy_move_assignment"]
    assert old["size"] == 63
    old_result = subprocess.run(
        [
            sys.executable,
            str(ROOT / "scripts/compare-coff-function.py"),
            "--unit",
            "shot_shared_ptr_legacy_move_assignment",
        ],
        cwd=ROOT,
        capture_output=True,
        text=True,
        check=True,
    )
    assert "exact (63/63 bytes)" in old_result.stdout
    print("PASS existing original shared_ptr move assignment: 63/63 bytes")
    print(
        "PASS original 12140B Bullet E8 -> 46B ctor -> 54B helper; "
        "all genuine original native PE call sites"
    )
    print("Both new original functions are STL/library, excluded from game-authored credit.")


if __name__ == "__main__":
    main()
