#!/usr/bin/env python3
"""Audit the FULL original 12140B Bullet command Boss E8s and 53 PE switch words.

Source independent: re-read locked original TH20 PE, actual 2490 i386
instruction heads, all 210 original direct E8 physical destinations and
every real PE HIGHLOW pointer in the three switch tables. Enumerate exact
canonical source roles and the remaining genuine original game/runtime
children, without claiming parent full native exact or global replay.
"""
from __future__ import annotations

from collections import Counter, defaultdict
from pathlib import Path
import csv
import runpy
import struct
import sys
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parent.parent
HEAD = 0x0047DCF0
BYTES = 12140
TABLES = (
    (0x00480C5C, 34, 0x0047DE4D),
    (0x00480CE4, 8, 0x0047E8FF),
    (0x00480D04, 11, 0x0047F48A),
)
EXPECTED_UNMAPPED = {
    0x0044FCD0: (37, "game animation resource/link helper"),
    0x0045E590: (21, "game animation flag byte +0x499 = 0"),
    0x0045E5B0: (21, "game animation flag byte +0x499 = 1"),
    0x004865D0: (21, "game animation flag byte +0x499 = 2"),
    0x00486330: (22, "game animation interrupt with integer 2"),
    0x005429EE: (14, "compiler __security_check_cookie"),
    0x005432F0: (31, "compiler __allshl"),
}


def pe_highlow(original: bytes) -> set[int]:
    nt = struct.unpack_from("<I", original, 0x3C)[0]
    count = struct.unpack_from("<H", original, nt + 6)[0]
    option_size = struct.unpack_from("<H", original, nt + 20)[0]
    image_base = struct.unpack_from("<I", original, nt + 24 + 28)[0]
    result = set()
    for idx in range(count):
        at = nt + 24 + option_size + idx * 40
        name, _, _, size, ptr = struct.unpack_from("<8sIIII", original, at)
        if name.rstrip(b"\0") != b".reloc":
            continue
        data = original[ptr:ptr + size]
        off = 0
        while off + 8 <= len(data):
            page, length = struct.unpack_from("<II", data, off)
            if not length:
                break
            assert 8 <= length <= len(data) - off
            for field in range(off + 8, off + length, 2):
                word = struct.unpack_from("<H", data, field)[0]
                if word >> 12 == 3:
                    result.add(image_base + page + (word & 0xFFF))
            off += length
    return result


def target_e8(pe: bytes, f: dict, address: int) -> int:
    data = f["pe_bytes_at"](pe, address, 5)
    assert data[0] == 0xE8, hex(address)
    return (address + 5 + struct.unpack_from("<i", data, 1)[0]) & 0xFFFFFFFF


def main() -> None:
    sys.path.insert(0, str(ROOT / "scripts"))
    comparator = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    pe = comparator["verified_target"]()
    dis = Cs(CS_ARCH_X86, CS_MODE_32)
    ops = list(dis.disasm(comparator["pe_bytes_at"](pe, HEAD, BYTES), HEAD))
    assert len(ops) == 2490
    assert ops[-1].address + ops[-1].size == HEAD + BYTES
    assert ops[-1].mnemonic == "ret"
    by_va = {op.address: op for op in ops}

    with (ROOT / "config/match-units.toml").open("rb") as file:
        units = tomllib.load(file)["units"]
    owners = defaultdict(list)
    for name, u in units.items():
        owners[u["target_address"]].append(name)
    assert len(owners) > 900

    calls = [
        (op.address, target_e8(pe, comparator, op.address))
        for op in ops if len(op.bytes) == 5 and op.bytes[0] == 0xE8
    ]
    assert len(calls) == 210
    known = [r for r in calls if r[1] in owners]
    unknown = [r for r in calls if r[1] not in owners]
    assert len(known) == 203, (len(known), unknown)
    assert len(unknown) == 7
    assert {target for _, target in unknown} == set(EXPECTED_UNMAPPED)
    assert all(
        len([r for r in unknown if r[1] == target]) == 1
        for target in EXPECTED_UNMAPPED
    )

    for address, (size, role) in sorted(EXPECTED_UNMAPPED.items()):
        method = list(dis.disasm(comparator["pe_bytes_at"](pe, address, size), address))
        assert method and method[-1].address + method[-1].size == address + size
        site = next(site for site, target in unknown if target == address)
        print(f"OPEN native Bullet E8 {site:#010x} -> {address:#010x}: "
              f"whole {size}B {role}")

    for address, value in (
        (0x0045E590, 0), (0x0045E5B0, 1), (0x004865D0, 2)
    ):
        native = comparator["pe_bytes_at"](pe, address, 21)
        assert any(
            op.mnemonic == "mov"
            and "+ 0x499" in op.op_str
            and op.op_str.endswith(f", {value}")
            for op in dis.disasm(native, address)
        ), (hex(address), value)
    assert target_e8(pe, comparator, 0x0048633C) == 0x004388F0
    assert target_e8(pe, comparator, 0x0044FCE3) == 0x0044FCA0

    reloc = pe_highlow(pe)
    total = 0
    values = []
    for table, count, indirect in TABLES:
        assert indirect in by_va
        jmp = by_va[indirect]
        assert jmp.mnemonic == "jmp" and f"0x{table:x}" in jmp.op_str
        words = struct.unpack(
            "<" + str(count) + "I",
            comparator["pe_bytes_at"](pe, table, count * 4),
        )
        assert all(word in by_va for word in words)
        assert all(table + idx * 4 in reloc for idx in range(count))
        values.append(words)
        total += count
        print(f"PASS original native PE switch table {table:#010x}: "
              f"{count}/{count} real HIGHLOW code pointers")
    assert total == 53
    assert len(set(values[0])) == 32
    assert values[0][5] == values[0][14] == values[0][28]
    assert len(set(values[1])) == 7
    assert len(set(values[2])) == 11
    body_highlow = [a for a in reloc if HEAD <= a < HEAD + BYTES]
    assert len(body_highlow) == 38

    with (ROOT / "config/matches.csv").open(newline="", encoding="utf8") as file:
        authored = {int(row["address"], 16) for row in csv.DictReader(file)}
    assert HEAD not in authored
    with (ROOT / "config/functions.csv").open(newline="", encoding="utf8") as file:
        root = next(row for row in csv.DictReader(file) if row["address"] == "0x0047DCF0")
    assert root["source_file"] == "" and root["status"] == "unclassified"

    print(f"PASS entire original Bullet Boss {BYTES}B / {len(ops)} i386, "
          f"{len(calls)}/210 direct E8 mapped: "
          f"{len(known)} canonical, {len(unknown)} genuinely still unsourced")
    print("PASS 53/53 PE switch HIGHLOW and 38/38 original body HIGHLOW")
    print("Original game parent remains source-absent and NONEXACT; "
          "no original authored code credit for this parent.")


if __name__ == "__main__":
    main()
