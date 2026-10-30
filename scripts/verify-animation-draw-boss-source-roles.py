#!/usr/bin/env python3
"""Independently attest full 5,993B Animation Draw Boss source/PE roles.

The pinned-MSVC C++ emits a full 5993B/1501-x86 executable body and two
original 49+31-pointer switch tables, preserving native case aliasing and
exact physical table alignment. All 123 E8 call roles agree in native order;
86 physical call positions match (81 consecutive), and 23/32 original PE
body data relocation offsets/targets coincide. The native 0x204 frame is
matched, but real instruction/branch/relocation bytes still differ:
this remains SOURCE-PRESENT, NONEXACT, not a canonical match unit.
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
OUTPUT = ROOT / "build/core835-probe/AnimationDrawBoss.obj"
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
    "draw_complex_mode6": 0x004408B0,
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
    "bind_native_texture_state": 0x00445BC0,
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
    expected_case_labels = Counter(range(49))
    for mode in list(range(16,23)) + list(range(26,47)):
        expected_case_labels[mode] += 1
    assert Counter(case_labels) == expected_case_labels, Counter(case_labels)-expected_case_labels
    assert text.count("switch (animation->base.flags.bytes_00.field_00)") == 2
    assert "draw_complex_mode6(animation)" in text
    assert "->bind_native_texture_state(animation)" in text
    # One real renderer ABI declaration is now shared with the independently
    # strict 753B mode7 child, not duplicated in this noncanonical parent.
    shared_abi=(ROOT / "src/AnimationDrawDetailedOwner.hpp").read_text()
    assert '#include "AnimationDrawDetailedOwner.hpp"' in text
    assert "draw_shape_43cd40(float, float, float, float," in shared_abi
    assert "std::uint32_t, std::uint32_t, int, int);" in shared_abi
    assert "draw_shape_43c4e0(float, float, float, float, float, int," in shared_abi
    assert "void prepare_simple_mode7(Animation*);" in shared_abi
    assert "std::int32_t draw_simple_mode7(Animation*);" in shared_abi
    assert "ANIMATION_DRAW_BOSS" not in text  # no separate exactness branch
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
    # A real C++ source produces one entire function and TWO genuine direct
    # pointer tables after RET: 49 main cases +31 nested, *no* compressed
    # index bytes. The 3B alignment is true compiler data, never x86.
    marker = bytes.fromhex("c204000f1f00")
    assert compiled.count(marker) == 1
    code_end = compiled.index(marker) + 3
    assert code_end == SIZE == 5993
    assert compiled[code_end:code_end+3] == bytes.fromhex("0f1f00")
    assert len(compiled) == 6316
    code = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(compiled[:code_end], HEAD))
    assert len(code)==len(native)==1501
    assert code[2].mnemonic=="sub" and code[2].op_str=="esp, 0x204"
    assert native[2].mnemonic=="sub" and native[2].op_str=="esp, 0x204"
    assert code[-1].address+code[-1].size == HEAD+code_end
    assert code[-1].mnemonic=="ret" and code[-1].op_str=="4"
    assert len(compiled)-code_end == 3+49*4+31*4
    assert ORIGINAL.MAIN_TABLE-HEAD == code_end+3
    assert ORIGINAL.SUB_TABLE-HEAD == code_end+3+49*4
    table_relocs=sorted((r for r in relocations if r["type"]=="DIR32" and
                        r["offset"]>=code_end), key=lambda r:r["offset"])
    assert len(table_relocs)==80
    assert compiled[code_end+3:] == bytes(80*4)
    assert [r["offset"] for r in table_relocs] == list(range(code_end+3,len(compiled),4))

    # Original physical table values are independent original-PE evidence.
    # The exact case entry positions may still differ, but the source's
    # pointer alias partition for ALL 49+31 entries must match the original.
    native_main=[struct.unpack("<I", COFF.pe_bytes_at(exe,ORIGINAL.MAIN_TABLE+4*i,4))[0]
                 for i in range(49)]
    native_nested=[struct.unpack("<I", COFF.pe_bytes_at(exe,ORIGINAL.SUB_TABLE+4*i,4))[0]
                   for i in range(31)]
    for native_table,candidate_table,distinct in (
        (native_main,table_relocs[:49],17),
        (native_nested,table_relocs[49:],29),
    ):
        assert len(set(native_table))==len({r["symbol"] for r in candidate_table})==distinct
        assert all((native_table[i]==native_table[j]) ==
                   (candidate_table[i]["symbol"]==candidate_table[j]["symbol"])
                   for i in range(len(native_table)) for j in range(len(native_table)))
    actual_rels = [row for row in relocations if row["type"] == "REL32"]
    assert len(actual_rels) == 123, len(actual_rels)
    source_calls = Counter(source_call_target(str(row["symbol"])) for row in actual_rels)
    assert source_calls == native_calls, [
        (f"0x{address:08X}", native_calls[address], source_calls[address])
        for address in sorted(set(native_calls) | set(source_calls))
        if native_calls[address] != source_calls[address]
    ]
    # The first 81 E8 instruction offsets and all 123 physical target roles
    # agree; 86 of the 123 physical E8 positions agree across the entire
    # original code, including the compiler cookie. This is NOT full exact.
    physical_calls=[(inst.address-HEAD,
           (inst.address+5+struct.unpack_from('<i',inst.bytes,1)[0])&0xffffffff)
           for inst in native if len(inst.bytes)==5 and inst.bytes[0]==0xE8]
    candidate_calls=[(int(r["offset"])-1,source_call_target(str(r["symbol"])))
                     for r in actual_rels]
    assert len(physical_calls)==len(candidate_calls)==123
    assert [value for _,value in physical_calls] == [value for _,value in candidate_calls]
    assert physical_calls[:81]==candidate_calls[:81]
    assert physical_calls!=candidate_calls
    matched_call_sites=sum(a==b for a,b in zip(physical_calls,candidate_calls))
    assert matched_call_sites==86
    assert physical_calls[-1]==candidate_calls[-1]  # real compiler cookie


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
    # In-body native PE data-role histogram, independent of source
    # declarations: 18 original 2.0f, five Graphics, four window-scale,
    # two 0.5f, cookie and both true dispatch table references.
    pe_data=Counter(struct.unpack('<I',ORIGINAL.raw_at(exe,base,sections,site,4))[0]
                    for site in reloc_sites if HEAD<=site<HEAD+SIZE)
    assert pe_data==Counter({
        0x0056C8D0:18,0x005C4D40:5,0x005B8818:4,0x0056E0EC:2,
        0x005B25C0:1,0x00444FEC:1,0x004450B0:1,
    })
    body_dirs=[r for r in relocations if r["type"]=="DIR32" and r["offset"]<code_end]
    assert len(body_dirs)==32
    observed_data=Counter()
    for row in body_dirs:
        sym=str(row["symbol"]);addend=int(row["addend"]);offset=int(row["offset"])
        if "?native_two@" in sym:target=0x0056C8D0+addend
        elif "?process_graphics@" in sym:target=0x005C4D40+addend
        elif "?window_state@" in sym:target=0x005B6758+addend
        elif sym=="__real@3f000000":target=0x0056E0EC+addend
        elif sym=="___security_cookie":target=0x005B25C0+addend
        else:
            assert sym.startswith("$LN"),(hex(offset),sym)
            target="table_main" if offset<0x400 else "table_nested"
        observed_data[target]+=1
    expected_data=pe_data.copy()
    expected_data["table_main"]=expected_data.pop(0x00444FEC)
    expected_data["table_nested"]=expected_data.pop(0x004450B0)
    assert observed_data==expected_data,(observed_data,expected_data)
    assert [row["offset"] for row in body_dirs[:14]]==[
        0xA,0x7B,0xA2,0x23E,0x254,0x301,0x323,0x44E,
        0x460,0x491,0x499,0x4AB,0x4B3,0x4E7,
    ]
    original_data_sites={
        site-HEAD:struct.unpack('<I',ORIGINAL.raw_at(exe,base,sections,site,4))[0]
        for site in reloc_sites if HEAD<=site<HEAD+SIZE
    }
    native_site_roles={
        offset:('table_main' if value==ORIGINAL.MAIN_TABLE else
                'table_nested' if value==ORIGINAL.SUB_TABLE else value)
        for offset,value in original_data_sites.items()
    }
    current_site_roles={}
    for row in body_dirs:
        sym=row['symbol'];addend=int(row['addend'])
        if '?native_two@' in sym:target=0x0056C8D0+addend
        elif '?process_graphics@' in sym:target=0x005C4D40+addend
        elif '?window_state@' in sym:target=0x005B6758+addend
        elif sym=='__real@3f000000':target=0x0056E0EC+addend
        elif sym=='___security_cookie':target=0x005B25C0+addend
        else:
            assert sym.startswith('$LN')
            target='table_main' if row['offset']<0x400 else 'table_nested'
        current_site_roles[row['offset']]=target
    matched_data_sites=len(set(native_site_roles.items())&set(current_site_roles.items()))
    assert matched_data_sites==23 and len(native_site_roles)==len(current_site_roles)==32

    # Compare code and after-RET data as a provisional strict-replay
    # diagnostic: no relocation targets are solved from original bytes.
    # Structural agreement alone is not canonical exact acceptance.
    original_extent=COFF.pe_bytes_at(exe,HEAD,len(compiled))
    ignored=set()
    for row in relocations:
        ignored.update(range(int(row['offset']),int(row['offset'])+4))
    comparable_bytes=sum(original_extent[i]==compiled[i]
                         for i in range(len(compiled)) if i not in ignored)
    assert comparable_bytes==3819 and len(compiled)-len(ignored)==5376


    assert all(addr in reloc_sites for t,n in ((ORIGINAL.MAIN_TABLE, 49),
                                             (ORIGINAL.SUB_TABLE, 31))
               for addr in range(t, t + n * 4, 4))

    print("PASS original complete 5,993B/1,501-i386 draw Boss native PE census")
    print("PASS full 49-main +31-nested pointer alias partitions, all 80/80 true direct COFF entries (no 49-byte compression index)")
    print("PASS all 123 original E8 target roles in original physical sequence, 43 distinct target addresses")
    print(f"PASS first 81 consecutive E8 instruction sites and {matched_call_sites}/123 complete original E8 physical positions (all 123 targets in order)")
    print(f"PASS 32/32 native PE in-body HIGHLOW roles, {matched_data_sites}/32 exact site/target pairs")
    print("PASS mode6 native thiscall and two original eight-parameter draw helper receiver/stack roles are in source")
    print(f"PASS candidate code {code_end}B/{len(code)} x86 with native stack frame 0x204; complete COFF {len(compiled)}B including 3B alignment+80 true pointer fields")
    print(f"NONEXACT parent: only {comparable_bytes}/5376 nonrelocation bytes equal; remaining nested-case local life and relocation offsets differ; zero game exact credit")


if __name__ == "__main__":
    main()
