#!/usr/bin/env python3
"""Check the full original Player movement table and all 37 PE data roles.

Run after compiling only src/PlayerDirectionTable.cpp and
src/PlayerMainFrame.cpp with their pinned MSVC native profiles. This checks
original game data, not a source-independent Player main exactness claim.
No native object is patched and no cold/global replay occurs here.
"""
from __future__ import annotations

import argparse
from collections import Counter, defaultdict
import hashlib
from pathlib import Path
import re
import runpy
import struct
import subprocess
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent.parent
PE_DATA_ADDRESS = 0x00572C48
PE_PLAYER_ADDRESS = 0x004F9C30
TABLE_SYMBOL = "?native_player_direction_table@th20@@3QAY01$$CBHA"
PLAYER_SYMBOL = "?update_main_frame@Player@th20@@QAEHXZ"
EXPECTED_SHA256 = "4cf7f804794295868934c5ed0b405f2737beee23ef953538799354b612402f7d"


def read_object_symbol(path: Path, symbol: str, size: int) -> tuple[bytes, str]:
    data = path.read_bytes()
    lines = subprocess.check_output(
        ["objdump", "-t", str(path)], text=True
    ).splitlines()
    rows = [line for line in lines if line.endswith(" " + symbol)]
    if len(rows) != 1:
        raise AssertionError(f"Expected exactly one COFF definition for {symbol}: {rows}")
    match = re.search(r"\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ", rows[0])
    assert match, rows[0]
    section, address = int(match.group(1)), int(match.group(2), 16)
    assert section > 0, f"{symbol} must have a real definition"
    section_base = 20 + 40 * (section - 1)
    section_size = struct.unpack_from("<I", data, section_base + 16)[0]
    section_offset = struct.unpack_from("<I", data, section_base + 20)[0]
    assert address + size <= section_size, f"{symbol} exceeds its native section"
    section_name = data[section_base:section_base + 8].rstrip(b"\0").decode()
    return data[section_offset + address:section_offset + address + size], section_name


def original_pe_highlow(pe: bytes) -> set[int]:
    nt = struct.unpack_from("<I", pe, 0x3C)[0]
    count = struct.unpack_from("<H", pe, nt + 6)[0]
    optional_header_size = struct.unpack_from("<H", pe, nt + 20)[0]
    image_base = struct.unpack_from("<I", pe, nt + 24 + 28)[0]
    result: set[int] = set()
    for index in range(count):
        section = nt + 24 + optional_header_size + index * 40
        name, _, _, data_size, data_offset = struct.unpack_from("<8sIIII", pe, section)
        if name.rstrip(b"\0") != b".reloc":
            continue
        raw = pe[data_offset:data_offset + data_size]
        offset = 0
        while offset + 8 <= len(raw):
            page, length = struct.unpack_from("<II", raw, offset)
            if length == 0:
                break
            assert 8 <= length <= len(raw) - offset
            for field in range(offset + 8, offset + length, 2):
                entry = struct.unpack_from("<H", raw, field)[0]
                if entry >> 12 == 3:
                    result.add(image_base + page + (entry & 0xFFF))
            offset += length
    return result


def main() -> None:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--data-object",
        type=Path,
        default=ROOT / "build/core729-probes/PlayerDirectionTable-production.obj",
    )
    parser.add_argument(
        "--player-object",
        type=Path,
        default=ROOT / "build/core729-probes/PlayerMainFrame.obj",
    )
    args = parser.parse_args()

    checker = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    pe = checker["verified_target"]()
    original = checker["pe_bytes_at"](pe, PE_DATA_ADDRESS, 72)
    table, section = read_object_symbol(args.data_object, TABLE_SYMBOL, 72)
    assert section == ".rdata" and table == original
    assert hashlib.sha256(table).hexdigest() == EXPECTED_SHA256

    expected_pairs = [
        (0, 0), (0, -1), (0, 1), (-1, 0), (1, 0),
        (-1, -1), (1, -1), (-1, 1), (1, 1),
    ]
    assert [
        struct.unpack_from("<ii", table, index * 8)
        for index in range(9)
    ] == expected_pairs

    main_code, relocations = checker["object_function"](
        args.player_object, PLAYER_SYMBOL, 3114
    )
    native_code = checker["pe_bytes_at"](pe, PE_PLAYER_ADDRESS, 3111)
    disassembler = Cs(CS_ARCH_X86, CS_MODE_32)
    original_ops = list(disassembler.disasm(native_code, 0))
    compiled_ops = list(disassembler.disasm(main_code, 0))
    assert len(original_ops) == len(compiled_ops) == 783
    assert [op.mnemonic for op in original_ops] == [
        op.mnemonic for op in compiled_ops
    ], "This original whole-parent candidate changed; reassess the data roles"

    refs = sorted(
        (ref for ref in relocations if ref["type"] == "DIR32"),
        key=lambda ref: ref["offset"],
    )
    assert sum(ref["type"] == "REL32" for ref in relocations) == 67
    sites = sorted(
        address for address in original_pe_highlow(pe)
        if PE_PLAYER_ADDRESS <= address < PE_PLAYER_ADDRESS + 3111
    )
    assert len(refs) == len(sites) == 37

    with (ROOT / "config/match-units.toml").open("rb") as stream:
        units = tomllib.load(stream)["units"]
    separate_anchors: dict[str, set[int]] = defaultdict(set)
    for unit in units.values():
        for ref in unit["relocations"]:
            separate_anchors[ref["symbol"]].add(ref["target"])

    outcomes: Counter[str] = Counter()
    for site, ref in zip(sites, refs):
        target = struct.unpack(
            "<I", checker["pe_bytes_at"](pe, site, 4)
        )[0]
        symbol = ref["symbol"]
        if symbol == TABLE_SYMBOL:
            assert site - PE_PLAYER_ADDRESS in (0x5F7, 0x612)
            assert ref["offset"] in (0x5F7, 0x612)
            assert target == PE_DATA_ADDRESS
            outcomes["game_direction_data"] += 1
        elif symbol.startswith("$SG"):
            assert site - PE_PLAYER_ADDRESS == ref["offset"] == 0x67D
            assert target == 0x0056EC84
            private, private_section = read_object_symbol(
                args.player_object, symbol, 7
            )
            assert private_section == ".rdata"
            assert private == checker["pe_bytes_at"](pe, target, 7) == b"effect\0"
            outcomes["actual_original_effect_literal"] += 1
        else:
            assert target in separate_anchors[symbol], (
                symbol, hex(target), hex(site)
            )
            outcomes["independently_canonical_attested_game_global"] += 1

    assert outcomes == {
        "game_direction_data": 2,
        "actual_original_effect_literal": 1,
        "independently_canonical_attested_game_global": 34,
    }, outcomes
    print(
        f"PASS Player game .rdata: 72/72 original bytes at {PE_DATA_ADDRESS:#010x}; "
        f"SHA-256 {EXPECTED_SHA256}"
    )
    print(
        "PASS original whole Player frame: 37/37 physical PE HIGHLOW "
        "data-reference roles, 34 independent canonical globals, "
        "2 real table fields, 1 original 7-byte effect literal"
    )
    print(
        "Parent remains NONEXACT: original 3111B/783 instructions, "
        "compiled 3114B/783, original 67 E8/37 PE HIGHLOW fields"
    )


if __name__ == "__main__":
    main()
