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
import re
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
COMMAND9_E8 = {
    0x0047F1B1: 0x004299D0,
    0x0047F1C2: 0x00412730,
    0x0047F1EF: 0x004AAE10,
    0x0047F232: 0x004383A0,
    0x0047F297: 0x00485700,
    0x0047F2F6: 0x004299D0,
    0x0047F315: 0x00438A30,
    0x0047F33B: 0x0040C300,
    0x0047F356: 0x004856C0,
    0x0047F387: 0x004383A0,
    0x0047F3CC: 0x0044FCD0,
    0x0047F3F4: 0x0040C300,
    0x0047F44B: 0x004790E0,
    0x0047F671: 0x00486330,
}
COMMAND13_E8 = {
    0x0047F701: 0x0040C080,
    0x0047F70E: 0x0047B290,
    0x0047F720: 0x0040C300,
    0x0047F72E: 0x0047BD20,
    0x0047F7C9: 0x004292E0,
    0x0047F821: 0x00485740,
    0x0047F8EC: 0x0040C300,
    0x0047F8FE: 0x0047C570,
    0x0047F910: 0x0040C300,
    0x0047F92A: 0x0040B280,
    0x0047F935: 0x0047B820,
    0x0047F944: 0x00481780,
    0x0047F970: 0x0047C8F0,
    0x0047F97F: 0x0047C300,
    0x0047F994: 0x0047C300,
}
COMMAND18_E8 = {
    0x004804B4: 0x0040FF90,
    0x004804CF: 0x004FF350,
    0x004804F6: 0x00438600,
    0x0048050D: 0x00452F20,
    0x00480544: 0x00452F20,
    0x0048058F: 0x004292E0,
    0x004805C0: 0x00439330,
}
COMMAND24_E8 = {
    0x00480A3D: 0x0047BB30,
    0x00480B16: 0x00412730,
    0x00480B46: 0x004A8920,
}

ORIGINAL_SEVEN = {
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


def primary_switch_case_ids(source: str) -> set[int]:
    start = source.index("switch (command.opcode)")
    opening = source.index("{", start)
    depth = 1
    position = opening + 1
    cases: set[int] = set()
    while depth:
        if depth == 1:
            match = re.match(r"\s*case\s+(\d+)\s*:", source[position:])
            if match:
                cases.add(int(match.group(1)))
                position += match.end()
                continue
        character = source[position]
        if character == "{":
            depth += 1
        elif character == "}":
            depth -= 1
        position += 1
    return cases


def verify_original_case_calls(calls: list[tuple[int, int]], label: str,
                               expected: dict[int, int]) -> None:
    actual = {site: target for site, target in calls if site in expected}
    assert actual == expected, (label, actual)
    print(f"PASS original command-{label} CFG: {len(expected)}/{len(expected)} E8 sites and targets")


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
    verify_original_case_calls(calls, "9", COMMAND9_E8)
    verify_original_case_calls(calls, "13", COMMAND13_E8)
    verify_original_case_calls(calls, "18", COMMAND18_E8)
    verify_original_case_calls(calls, "24", COMMAND24_E8)
    known = [r for r in calls if r[1] in owners]
    unknown = [r for r in calls if r[1] not in owners]
    # Preserve the independently decoded original seven E8 roles while
    # tracking which targets have gained strict canonical source units.
    seven = [(site, target) for site, target in calls if target in ORIGINAL_SEVEN]
    assert len(seven) == 7 and {target for _, target in seven} == set(ORIGINAL_SEVEN)
    expected_open = set(ORIGINAL_SEVEN) - set(owners)
    assert len(known) + len(unknown) == 210
    assert {target for _, target in unknown} == expected_open, unknown
    for address, (size, role) in sorted(ORIGINAL_SEVEN.items()):
        method = list(dis.disasm(comparator["pe_bytes_at"](pe, address, size), address))
        assert method and method[-1].address + method[-1].size == address + size
        site = next(site for site, target in seven if target == address)
        state = "CANONICAL" if address in owners else "OPEN"
        print(f"{state} native Bullet E8 {site:#010x} -> {address:#010x}: "
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
    assert root["source_file"] == "src/BulletRunExtendedCommands.cpp"
    assert root["status"] == "reconstructed"
    assert (ROOT / root["source_file"]).is_file()
    partial_source = (ROOT / root["source_file"]).read_text(encoding="utf8")
    primary_cases = primary_switch_case_ids(partial_source)
    assert primary_cases == set(range(34)), sorted(primary_cases)
    assert "std::allocate_shared<ShotMetadata>" in partial_source
    assert "context->bullet_controller()->fire(" in partial_source
    assert "EnemySpawn parameters;" in partial_source
    assert "context->enemy_controller()->create(command.script, parameters, nullptr)" in partial_source
    print("PASS maintained natural-C++ primary opcode switch: 34/34 IDs, 31 gameplay handlers + 3 shared no-op IDs")

    print(f"PASS entire original Bullet Boss {BYTES}B / {len(ops)} i386, "
          f"{len(calls)}/210 direct E8 mapped: "
          f"{len(known)} canonical, {len(unknown)} genuinely still unsourced")
    print("PASS 53/53 PE switch HIGHLOW and 38/38 original body HIGHLOW")
    print("Original game parent has natural-C++ source for all 34/34 primary opcode IDs, "
          "remains NONEXACT, and receives zero original parent byte credit.")


if __name__ == "__main__":
    main()
