#!/usr/bin/env python3
"""Attest full-source/provisional 5,993B Animation draw Boss native call-role coverage.

This is NOT a native-exact comparator. It compiles the maintained typed 49-mode
source in one isolated probe object, proves that all 123 original native E8
call destination identities and *multiplicities* are represented by its
actual x86 COFF call relocations, and explicitly records the still-NONEXACT
5,993-byte whole-body status. It never promotes the source to a strict unit.
"""
from collections import Counter
import csv
import importlib.util
from pathlib import Path
import re
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module


COFF = load_module("native_compare", ROOT / "scripts/compare-coff-function.py")
ORIGINAL = load_module("native_draw_boss", ROOT / "scripts/verify-animation-draw-boss-native.py")
SOURCE = ROOT / "src/AnimationDrawBoss.cpp"
OUTPUT = ROOT / "build/core797-probe/AnimationDrawBoss.obj"
SYMBOL = "?draw@AnimationPoolOwner@th20@@QAEHPAVAnimation@2@@Z"
HEAD = 0x00443880
SIZE = 5993

# These are *original physical* E8 targets. Their C++ member spellings are
# provisional where no separately accepted source declaration already exists.
# No unknown call is allowed a made-up native address or invented exactness.
NAME_TARGETS = {
    "draw_quad_mode0": 0x0043F550,
    "draw_quad_mode1": 0x0043F630,
    "draw_quad_mode2": 0x0043F5C0,
    "draw_quad_mode4": 0x00440310,
    "draw_quad_mode5": 0x004413A0,
    "animation_draw_mode6": 0x004408B0,
    "draw_simple_mode7": 0x00441C00,
    "draw_simple_mode8": 0x00441F00,
    "draw_strip_mode9": 0x00445350,
    "draw_strip_mode11": 0x00445130,
    "draw_mesh_2425": 0x00443020,
    "animation_draw_color_490": 0x004456E0,
    "animation_draw_color_494": 0x004456C0,
    "animation_draw_enabled": 0x00445AB0,
    "animation_inherited_aux_scale_x": 0x00445880,
    "graphics_enable_fog": 0x004DDAC0,
    "graphics_disable_fog": 0x004DDA60,
    "graphics_disable_depth_writes": 0x004DDF80,
    "rotation_z_value": 0x00437930,
    "width@Animation": 0x004459D0,
    "height@Animation": 0x004459A0,
    "position@Animation": 0x004376E0,
    "prepare_render_geometry": 0x00445BC0,
    "??0Vector3": 0x00422E10,
    "@__security_check_cookie": 0x005429EE,
}


def source_call_target(symbol: str) -> int:
    renderer = re.match(r"\?draw_(?:shape|rect)_(43[0-9a-fA-F]{4})@", symbol)
    if renderer:
        return int(renderer.group(1), 16)
    found = {value for spelling, value in NAME_TARGETS.items() if spelling in symbol}
    assert len(found) == 1, ("missing or ambiguous original E8 role", symbol, found)
    return found.pop()


def main():
    exe = COFF.verified_target()
    original = COFF.pe_bytes_at(exe, HEAD, SIZE)
    native = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(original, HEAD))
    assert len(native) == 1501 and native[-1].address + native[-1].size == HEAD + SIZE
    native_calls = Counter(
        (inst.address + 5 + struct.unpack_from("<i", inst.bytes, 1)[0]) & 0xFFFFFFFF
        for inst in native if len(inst.bytes) == 5 and inst.bytes[0] == 0xE8
    )
    assert sum(native_calls.values()) == 123 and len(native_calls) == 43

    text = SOURCE.read_text()
    case_labels = [int(value) for value in re.findall(r"\bcase\s+(\d+)\s*:", text)]
    assert len(case_labels) == 49 and sorted(case_labels) == list(range(49)), case_labels
    assert "std::int32_t AnimationPoolOwner::draw(Animation* animation)" in text
    assert "graphics_disable_depth_writes(&process_graphics)" in text
    assert "animation->callback->draw()" in text
    assert "animation->field_570 != 0" in text

    with (ROOT / "config/animation-draw-boss-mode-e8.csv").open(newline="") as f:
        routes = list(csv.DictReader(f))
    assert len(routes) == 49
    chosen_render_targets = {int(row["render_target"], 16)
                             for row in routes if row["render_target"]}
    assert len(chosen_render_targets) == 29
    assert len([r for r in routes if not r["render_target"]]) == 2

    # Standalone one-object compiler probe, not a canonical replay and not an
    # all-target cold build. Only SOURCE is compiled; existing exact headers
    # are inputs but no existing provider is touched or recompiled.
    command = [str(ROOT / "scripts/compile-probe.sh"), str(SOURCE), str(OUTPUT),
               "/nologo", "/c", "/std:c++20", "/Od", "/Ob0", "/GS",
               "/Gy", "/Zl", "/arch:SSE2", "/fp:precise", "/sdl", "/EHsc"]
    subprocess.run(command, cwd=ROOT, check=True)
    # For a NONEXACT candidate, read its entire real COFF function extent;
    # never request just a 5,993-byte prefix from a differently sized object.
    try:
        compiled, relocations = COFF.object_function(OUTPUT, SYMBOL, SIZE)
    except ValueError as exc:
        match = re.search(r"complete COFF contribution is (\d+) bytes", str(exc))
        if not match:
            raise
        compiled, relocations = COFF.object_function(OUTPUT, SYMBOL, int(match.group(1)))
    # MSVC places jump tables AFTER the candidate executable RET in the
    # very same COFF function contribution. Never disassemble that data as
    # x86 instructions and count phantom opcodes (a past probe did this).
    marker = bytes.fromhex("c204000f1f00")
    assert compiled.count(marker) == 1
    marker_offset = compiled.index(marker)
    code_end = marker_offset + 3
    assert code_end == 0x1415
    assert compiled[code_end:code_end + 3] == bytes.fromhex("0f1f00")
    assert len(compiled) == 0x150C
    body = compiled[:code_end]
    code = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(body, HEAD))
    assert code[-1].address + code[-1].size == HEAD + code_end
    assert code[-1].mnemonic == "ret" and code[-1].op_str == "4"
    assert len(code) == 1358, len(code)
    # Candidate primary dispatch uses a compressed 17-pointer table and a
    # distinct 49-byte index table, unlike the original direct 49-pointer
    # table. Its inner switch uses a separate 31-pointer table. No table
    # data receives original x86 instruction credit.
    start = code_end + 3
    after_primary = start + 17 * 4
    after_indexes = after_primary + 49
    after_alignment = after_indexes + 3
    assert all(r["type"] == "DIR32" for r in relocations
               if start <= r["offset"] < after_primary)
    assert len([r for r in relocations if r["type"] == "DIR32"
                and start <= r["offset"] < after_primary]) == 17
    assert compiled[after_indexes:after_alignment] == bytes.fromhex("0f1f00")
    assert len([r for r in relocations if r["type"] == "DIR32"
                and after_alignment <= r["offset"] < len(compiled)]) == 31
    assert len(compiled[after_primary:after_indexes]) == 49
    assert after_alignment + 31 * 4 == len(compiled)
    actual_rels = [row for row in relocations if row["type"] == "REL32"]
    assert len(actual_rels) == 123, len(actual_rels)
    source_calls = Counter(source_call_target(str(row["symbol"])) for row in actual_rels)
    assert source_calls == native_calls, [
        (f"0x{address:08X}", native_calls[address], source_calls[address])
        for address in sorted(set(native_calls) | set(source_calls))
        if native_calls[address] != source_calls[address]
    ]
    assert chosen_render_targets <= set(source_calls), chosen_render_targets - set(source_calls)

    # Retain crucial source-level ABI/data distinctions that Ghidra formerly
    # typed incorrectly (the original 20B color getters return a raw 32-bit
    # color in EAX; the original native scale resolves to WindowState+20C0).
    for address, count in ((0x004456E0, 32), (0x004456C0, 22),
                           (0x00445880, 12), (0x0043F630, 2),
                           (0x00443020, 3)):
        assert native_calls[address] == source_calls[address] == count
    base, sections = ORIGINAL.parse_sections(exe)
    reloc_sites = ORIGINAL.physical_highlow(exe, base, sections)
    assert len([r for r in reloc_sites if HEAD <= r < HEAD + SIZE]) == 32
    assert all(addr in reloc_sites for t,n in ((ORIGINAL.MAIN_TABLE, 49),
                                             (ORIGINAL.SUB_TABLE, 31))
               for addr in range(t, t + n * 4, 4))

    print("PASS original entire 5,993B/1,501-i386 Animation draw Boss native census")
    print("PASS typed whole 49-mode main/nested C++ source compiles as ONE original-method candidate")
    print("PASS exact all 123/123 E8 source call roles including each original native target's multiplicity (43/43 distinct)")
    print("PASS all 29/29 physically selected renderer helper target roles from the original 49-mode CFG")
    print("PASS original 49+31 PE jump entries, 32 original in-body HIGHLOW roles and color/scale call distinctions")
    print(f"NONEXACT: proposed C++ executable body {len(body)}B/{len(code)} real x86, "
          f"original {SIZE}B/{len(native)} real x86; no parent original code byte credit")
    print("NONEXACT: compiler COFF function contribution 5,388B includes 247B "
          "jump-table/index/alignment DATA, not 247B additional x86 instructions")
    print("NONEXACT: compiler primary switch uses 17 pointer entries +49 index bytes, "
          "original uses direct 49 real PE HIGHLOW pointer entries")


if __name__ == "__main__":
    main()
