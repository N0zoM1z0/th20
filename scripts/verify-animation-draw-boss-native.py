#!/usr/bin/env python3
"""Independent immutable original-PE audit of 5,993B Animation draw Boss.

Treat the target executable, its PE32 .reloc section and real instruction
boundaries as ground truth. This script verifies both of the *distinct* native
switch tables; it does not assert source-level exactness for the parent body.
"""
from collections import Counter
import csv
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32
from project import verified_target

HEAD = 0x00443880
BODY_SIZE = 5993
MAIN_TABLE = 0x00444FEC
MAIN_COUNT = 49
SUB_TABLE = 0x004450B0
SUB_COUNT = 31
# Exact game Graphics cache transitions called by the 5,993B renderer;
# each is a separate 92B native method with two real original PE fields.
# Three whole game-owned 97B quad wrappers called by four original modes.
# The data target is the original 4*28B shared SpriteTexturedVertex array.
QUAD_WRAPPERS = {
    0x0043F550: (0x0043EB40, 1, (0,)),
    0x0043F630: (0x0043EF20, 0, (1, 3)),
    0x0043F5C0: (0x0043EB40, 0, (2,)),
}
GRAPHICS_TRANSITIONS = {
    0x004DDAC0: (2, 0xDB8, 1, 0x1C, "enable fog"),
    0x004DDA60: (2, 0xDB8, 0, 0x1C, "disable fog"),
    0x004DDF80: (1, 0xDBC, 0, 0x0E, "disable depth writes"),
}
CHILDREN = {
    0x004456E0: (20, 32, "Animation packed color +0x490"),
    0x004456C0: (20, 22, "Animation packed color +0x494"),
    0x00445AB0: (26, 1, "Animation flag +0x49A bit zero"),
    0x00445880: (93, 12, "recursive parent scale +0x58"),
}


def parse_sections(image: bytes):
    nt = struct.unpack_from("<I", image, 0x3C)[0]
    assert image[nt:nt + 4] == b"PE\0\0"
    sections = struct.unpack_from("<H", image, nt + 6)[0]
    opt_size = struct.unpack_from("<H", image, nt + 20)[0]
    image_base = struct.unpack_from("<I", image, nt + 24 + 28)[0]
    table = nt + 24 + opt_size
    result = []
    for index in range(sections):
        offset = table + 40 * index
        name, virtual, rva, raw_len, raw_offset = struct.unpack_from("<8sIIII", image, offset)
        result.append((name.rstrip(b"\0"), virtual, rva, raw_len, raw_offset))
    return image_base, result


def raw_at(image: bytes, base: int, sections, address: int, size: int):
    rva = address - base
    for _, virtual, section_rva, raw_len, raw_offset in sections:
        if section_rva <= rva and rva + size <= section_rva + max(virtual, raw_len):
            local = rva - section_rva
            assert local + size <= raw_len
            return image[raw_offset + local:raw_offset + local + size]
    raise AssertionError(f"original PE address outside raw file {address:#x}")


def physical_highlow(image: bytes, base: int, sections):
    reloc_sections = [s for s in sections if s[0] == b".reloc"]
    assert len(reloc_sections) == 1
    _, _, _, raw_len, raw_offset = reloc_sections[0]
    data = image[raw_offset:raw_offset + raw_len]
    out = set()
    at = 0
    while at + 8 <= len(data):
        page, length = struct.unpack_from("<II", data, at)
        if length == 0:
            break
        assert length >= 8 and at + length <= len(data)
        for pos in range(at + 8, at + length, 2):
            entry = struct.unpack_from("<H", data, pos)[0]
            if entry >> 12 == 3:
                out.add(base + page + (entry & 0xFFF))
        at += length
    assert len(out) > 1000
    return out


def decoded(image, base, sections, address, length):
    insns = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(raw_at(image, base, sections, address, length), address))
    assert insns and insns[-1].address + insns[-1].size == address + length
    return insns


def verify_mode_dispatch_paths(instructions, main, nested) -> None:
    """Check all 49 original main modes against the original-PE-only CFG.

    This does not assume the Ghidra decompiler's guessed C++ switch or any
    original source method names. Branches and E8 destinations come directly
    from the same locked 5,993-byte x86 body as the real jump-table targets.
    """
    path = Path(__file__).resolve().parents[1] / "config/animation-draw-boss-mode-e8.csv"
    with path.open(newline="") as f:
        rows = list(csv.DictReader(f))
    required = ("mode", "main_entry", "nested_entry", "render_e8_site",
                "render_target", "reachable_x86_heads")
    assert len(rows) == 49
    assert tuple(rows[0]) == required
    modes = [int(row["mode"]) for row in rows]
    assert modes == list(range(49))
    heads = {ins.address: ins for ins in instructions}
    render_callees = {int(row["render_target"], 16)
                      for row in rows if row["render_target"]}
    assert len(render_callees) == 29, len(render_callees)

    confirmed_render_modes = []
    covered_modes_using_nested_switch = []
    confirmed_call_sites = set()
    for mode, row in enumerate(rows):
        target_main = int(row["main_entry"], 16)
        assert target_main == main[mode], (mode, hex(target_main), hex(main[mode]))
        target_nested = int(row["nested_entry"], 16) if row["nested_entry"] else None
        assert target_nested == (nested[mode - 16] if target_main == 0x00443C1D else None)
        if target_nested is not None:
            assert 16 <= mode <= 46
            covered_modes_using_nested_switch.append(mode)
        visited = set()
        stack = [target_main]
        actual_mode_draw_e8 = []
        encountered_nested_dispatch = False
        while stack:
            address = stack.pop()
            if address in visited:
                continue
            assert address in heads, (mode, hex(address), "branch outside original function")
            visited.add(address)
            ins = heads[address]
            end = address + ins.size
            if len(ins.bytes) == 5 and ins.bytes[0] == 0xE8:
                destination = (end + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
                if destination in render_callees:
                    actual_mode_draw_e8.append((address, destination))
            if ins.mnemonic in ("ret", "retn", "iret"):
                continue
            if ins.mnemonic == "jmp":
                if address == 0x00443D64:
                    assert target_nested is not None
                    encountered_nested_dispatch = True
                    stack.append(target_nested)
                elif address == 0x0044391F:
                    # Kept for completeness if the initial entry changes.
                    stack.append(target_main)
                elif ins.op_str.startswith("0x"):
                    stack.append(int(ins.op_str, 16))
                else:
                    raise AssertionError((mode, hex(address), ins.op_str))
            elif ins.mnemonic.startswith("j") and ins.op_str.startswith("0x"):
                stack.extend((end, int(ins.op_str, 16)))
            else:
                stack.append(end)
        assert encountered_nested_dispatch == (target_nested is not None)
        assert len(visited) == int(row["reachable_x86_heads"]), (mode, len(visited))
        expected = ([] if not row["render_e8_site"] and not row["render_target"]
                    else [(int(row["render_e8_site"], 16), int(row["render_target"], 16))])
        assert sorted(actual_mode_draw_e8) == expected, (mode, actual_mode_draw_e8, expected)
        if expected:
            assert expected[0][0] in heads and heads[expected[0][0]].mnemonic == "call"
            confirmed_render_modes.append(mode)
            confirmed_call_sites.add(expected[0][0])
    assert len(covered_modes_using_nested_switch) == 28
    assert all(mode not in covered_modes_using_nested_switch for mode in (23, 24, 25))
    assert len(confirmed_render_modes) == 47
    # Several original main switch cases intentionally share exactly the
    # SAME compiled E8 site: modes 9/12/13/14 and 24/25.
    assert len(confirmed_call_sites) == 43
    assert [mode for mode in range(49) if mode not in confirmed_render_modes] == [10, 23]
    print("PASS original full 49-mode draw Boss CFG: 47 dispatched modes, "
          "43 physically distinct original E8 call sites, 29 renderer callee heads")
    print("PASS original shared call sites: mode 9/12/13/14, mode 24/25; "
          "modes 10/23 have no renderer E8")
    print("PASS 28 actual main-to-nested switch traversals; mode 24/25 use their main table directly")


def verify() -> None:
    image, _ = verified_target()
    base, sections = parse_sections(image)
    relocs = physical_highlow(image, base, sections)
    instructions = decoded(image, base, sections, HEAD, BODY_SIZE)
    heads = {ins.address: ins for ins in instructions}
    assert len(instructions) == 1501, len(instructions)
    assert instructions[-1].address == 0x00444FE6
    assert instructions[-1].mnemonic == "ret" and instructions[-1].op_str == "4"
    assert raw_at(image, base, sections, HEAD + BODY_SIZE, 3) == bytes.fromhex("0f1f00")
    native_calls = [ins for ins in instructions if len(ins.bytes) == 5 and ins.bytes[0] == 0xE8]
    called = Counter((ins.address + 5 + struct.unpack_from("<i", ins.bytes, 1)[0]) & 0xFFFFFFFF
                     for ins in native_calls)
    assert len(native_calls) == 123 and len(called) == 43

    original_body_relocs = {address for address in relocs if HEAD <= address < HEAD + BODY_SIZE}
    assert len(original_body_relocs) == 32
    # The main and nested jump operands themselves are two separate original
    # body HIGHLOW fields (in addition to the table element HIGHLOW entries).
    assert heads[0x0044391F].mnemonic == "jmp"
    assert heads[0x0044391F].op_str == "dword ptr [eax*4 + 0x444fec]"
    assert heads[0x00443D64].mnemonic == "jmp"
    assert heads[0x00443D64].op_str == "dword ptr [edx*4 + 0x4450b0]"
    for address, target in ((0x00443922, MAIN_TABLE), (0x00443D67, SUB_TABLE)):
        assert address in original_body_relocs
        assert struct.unpack("<I", raw_at(image, base, sections, address, 4))[0] == target

    tables = []
    for title, start, count, distinct in (("main animation mode", MAIN_TABLE, MAIN_COUNT, 17),
                                          ("nested animation mode", SUB_TABLE, SUB_COUNT, 29)):
        destinations = []
        for idx in range(count):
            physical = start + idx * 4
            assert physical in relocs, (title, hex(physical), "missing real PE HIGHLOW")
            destination = struct.unpack("<I", raw_at(image, base, sections, physical, 4))[0]
            assert destination in heads, (title, idx, hex(destination), "not an original instruction head")
            destinations.append(destination)
        assert len(set(destinations)) == distinct, (title, len(set(destinations)))
        tables.append(destinations)
        print(f"PASS original {title}: {count}/{count} real HIGHLOW code pointers, "
              f"{distinct} distinct instruction entry heads")
    main, nested = tables
    assert main[0] == 0x00443926 and main[48] == 0x00443B80
    assert all(main[index] == 0x00443C1D for index in list(range(16, 23)) + list(range(26, 47)))
    assert main[24] == main[25] == 0x00443B32
    assert main[47] == 0x00443B59
    assert nested[0] == 0x00443E06 and nested[30] == 0x00444EF9
    assert all(nested[index] == 0x00444FD7 for index in (7, 8, 9))
    verify_mode_dispatch_paths(instructions, main, nested)
    assert heads[0x00443912].mnemonic == "cmp" and heads[0x00443912].op_str == "dword ptr [ebp - 0x28], 0x30"
    assert heads[0x00443D57].mnemonic == "cmp" and heads[0x00443D57].op_str == "dword ptr [ebp - 0x24], 0x1e"
    assert heads[0x00443D51].mnemonic == "sub" and heads[0x00443D51].op_str == "ecx, 0x10"

    # Original live Animation gate before any of the 49 dispatch entries.
    for site, mnemonic, operand in (
        (0x00443899, "mov", "ecx, dword ptr [eax + 0x49c]"),
        (0x0044389F, "and", "ecx, 1"),
        (0x004438AF, "cmp", "dword ptr [edx + 0x568], 0"),
        (0x004438E9, "cmp", "dword ptr [eax + 0x570], 0"),
        (0x00443908, "movzx", "edx, byte ptr [ecx + 0x498]"),
    ):
        assert heads[site].mnemonic == mnemonic and heads[site].op_str == operand, (hex(site), heads[site])
    assert heads[0x004438CF].mnemonic == "call" and heads[0x004438CF].op_str == "edx"
    assert heads[0x004438D5].mnemonic == "call" and heads[0x004438D5].op_str == "0x445ab0"

    for address, (size, count, role) in CHILDREN.items():
        assert called[address] == count, (hex(address), called[address])
        child = decoded(image, base, sections, address, size)
        assert child[-1].mnemonic == "ret" and child[-1].op_str == ""
        assert child[-1].address + child[-1].size == address + size
        print(f"PASS native draw Boss {role}: {count} actual E8 sites to one complete {size}B original child at {address:#010x}")
    # Three real game-owned 97-byte quad mode functions, 4*28B array
    # operands and two true native E8 setup/submit calls each.
    for head, (setup_target, submit_mode, main_modes) in QUAD_WRAPPERS.items():
        native_quad = decoded(image, base, sections, head, 97)
        assert len(native_quad) == 32 and native_quad[-1].mnemonic == "ret"
        assert native_quad[-1].op_str == "4"
        expected_fields = {0x11, 0x1F, 0x2D, 0x3C}
        for off in expected_fields:
            assert head + off in relocs
            assert struct.unpack("<I", raw_at(image, base, sections, head + off, 4))[0] == 0x005AEF10
        assert len(raw_at(image, base, sections, 0x005AEF10, 4 * 28)) == 112
        for off, target in ((0x48, setup_target), (0x56, 0x0043F6A0)):
            insn = next(ins for ins in native_quad if ins.address == head + off)
            assert insn.mnemonic == "call" and insn.bytes[0] == 0xE8
            assert (insn.address + 5 + struct.unpack_from("<i", insn.bytes, 1)[0]) & 0xFFFFFFFF == target
        assert any(i.mnemonic == "push" and i.op_str == str(submit_mode) for i in native_quad)
        sites = [i.address for i in instructions if i.mnemonic == "call" and i.op_str == f"{head:#x}"]
        assert len(sites) == len(main_modes), (hex(head), sites)
        selected_modes = [int(r["mode"]) for r in csv.DictReader((Path(__file__).resolve().parents[1] /
                "config/animation-draw-boss-mode-e8.csv").open()) if r["render_target"] == f"0x{head:08X}"]
        assert tuple(selected_modes) == main_modes, (hex(head), selected_modes)
        print(f"PASS original 97B quad draw {head:#010x}: complete 32 x86, "
              "4 real PE HIGHLOW to shared native 4x28B vertex data, 2 original setup/submit E8")

    # More original whole renderer mode wrappers: 48B integer-return guard
    # and 142B quad reset after drawing. This is checked from original PE,
    # not inferred from the C++ target or physical base symbol value.
    for head, size, mode, setup, expected_data in (
        (0x00440310, 48, 4, 0x00440340, {}),
        (0x004413A0, 142, 5, 0x00441430,
         {0x32: 0x0056C8CC, 0x3A: 0x005AEF1C,
          0x49: 0x0056C8CC, 0x51: 0x005AEF1C,
          0x61: 0x0056C8CC, 0x69: 0x005AEF1C,
          0x79: 0x0056C8CC, 0x81: 0x005AEF1C}),
    ):
        body = decoded(image, base, sections, head, size)
        assert body[-1].mnemonic == "ret" and body[-1].op_str == "4"
        assert len(body) == (20 if size == 48 else 34)
        assert {location for location in relocs if head <= location < head + size} == {
            head + off for off in expected_data}
        for offset, physical in expected_data.items():
            assert struct.unpack("<I", raw_at(image, base, sections, head + offset, 4))[0] == physical
        for offset, destination in ((0x0E if size==48 else 0x10, setup),
                                    (0x25 if size==48 else 0x1E, 0x0043F6A0)):
            insn = next(x for x in body if x.address == head + offset)
            assert insn.mnemonic == "call" and insn.bytes[0] == 0xE8
            assert insn.address + 5 + struct.unpack_from("<i", insn.bytes, 1)[0] == destination
        original_modes = list(csv.DictReader((Path(__file__).resolve().parents[1] /
            "config/animation-draw-boss-mode-e8.csv").open()))
        assert next(r for r in original_modes if int(r["mode"])==mode)["render_target"] == f"0x{head:08X}"
        if size == 142:
            assert len([x for x in body if x.mnemonic == "movss" and "0x5aef1c" in x.op_str]) == 4
            assert all(struct.unpack("<f", raw_at(image, base, sections, 0x0056C8CC, 4))[0] == 1.0 for _ in range(4))
        else:
            assert any(x.mnemonic == "test" and x.op_str == "eax, eax" for x in body)
        print(f"PASS original 0x{head:08X} mode {mode} whole {size}B native: "
              f"two original E8, {len(expected_data)} real original HIGHLOW, "
              "full return and x86 boundary")

    # Three native Graphics D3D9 state transitions: compare the original
    # complete 92B /30 x86 shape, real original HIGHLOW global reference,
    # the original E8 to Renderer flush, and the real virtual API slot.
    for address, (frequency, cache_offset, value, render_state, role) in GRAPHICS_TRANSITIONS.items():
        assert called[address] == frequency, (hex(address), called[address])
        native = decoded(image, base, sections, address, 92)
        by_site = {ins.address: ins for ins in native}
        assert len(native) == 30 and native[-1].address + native[-1].size == address + 92
        assert native[-1].mnemonic == "ret" and native[-1].op_str == ""
        assert address + 0x17 in relocs, hex(address + 0x17)
        global_value = struct.unpack("<I", raw_at(image, base, sections, address + 0x17, 4))[0]
        assert global_value == 0x005C0028
        native_call = by_site[address + 0x1B]
        assert native_call.bytes[0] == 0xE8 and len(native_call.bytes) == 5
        direct_target = (native_call.address + 5 + struct.unpack_from("<i", native_call.bytes, 1)[0]) & 0xFFFFFFFF
        assert direct_target == 0x004455C0, (hex(address), hex(direct_target))
        assert by_site[address + 0x0C].mnemonic == "cmp"
        assert by_site[address + 0x0C].op_str == f"dword ptr [eax + {cache_offset:#x}], {value}"
        assert any(ins.mnemonic == "mov" and
                   ins.op_str == f"dword ptr [ecx + {cache_offset:#x}], {value}" for ins in native)
        assert any(ins.mnemonic == "mov" and ins.op_str == "ecx, dword ptr [eax + 0xe4]" for ins in native)
        assert any(ins.mnemonic == "push" and ins.op_str == f"{render_state:#x}" for ins in native)
        assert any(ins.mnemonic == "call" and ins.op_str == "dword ptr [ebp - 0xc]" for ins in native)
        print(f"PASS original Graphics {role}: complete 92/92B, 30/30 x86, "
              f"{frequency} actual draw-Boss calls, real PE HIGHLOW and E8 flush")

    # Separate original 192B /55-x86 renderer submission-queue flush.
    # Its body is now maintained C++ but still NONEXACT. The original device
    # uses real D3D9 vtable methods SetFVF(+0x164) and DrawPrimitiveUP(+0x14C).
    flush_head = 0x004455C0
    flush = decoded(image, base, sections, flush_head, 192)
    assert len(flush) == 55 and flush[-1].mnemonic == "ret"
    assert flush[-1].op_str == ""
    by_offset = {i.address - flush_head: i for i in flush}
    for offset, global_target in ((0x1A, 0x005C4D40), (0x41, 0x005C4D40)):
        field = flush_head + offset
        assert field in relocs
        assert struct.unpack("<I", raw_at(image, base, sections, field, 4))[0] == global_target
    for opcode, target in ((0x1E, 0x00412730), (0x45, 0x00412730)):
        insn = by_offset[opcode]
        assert insn.mnemonic == "call" and insn.bytes[0] == 0xE8
        resolved = (insn.address + 5 + struct.unpack_from("<i", insn.bytes, 1)[0]) & 0xFFFFFFFF
        assert resolved == target
    for offset, mn, text in ((0x0C, "cmp", "dword ptr [eax + 0x6000e70], 0"),
                             (0x2B, "mov", "eax, dword ptr [edx + 0x164]"),
                             (0x52, "mov", "ecx, dword ptr [eax + 0x14c]"),
                             (0x5E, "mov", "eax, dword ptr [edx + 0x7c00e78]"),
                             (0x6A, "mov", "edx, dword ptr [ecx + 0x6000e70]"),
                             (0x9D, "mov", "dword ptr [eax + 0x6000e70], 0"),
                             (0xAA, "mov", "edx, dword ptr [ecx + 0xc4]")):
        assert by_offset[offset].mnemonic == mn and by_offset[offset].op_str == text
    assert by_offset[0x34].mnemonic == "push" and by_offset[0x34].op_str == "0x144"
    assert by_offset[0x75].mnemonic == "push" and by_offset[0x75].op_str == "0x1c"
    assert by_offset[0x7F].mnemonic == "push" and by_offset[0x7F].op_str == "4"
    assert by_offset[0x88].mnemonic == "mov" and by_offset[0x88].op_str == "eax, dword ptr [ebp - 4]"
    assert by_offset[0x8E].mnemonic == "mov" and by_offset[0x8E].op_str == "edx, dword ptr [ecx + 0x7c00e74]"
    assert by_offset[0x94].mnemonic == "mov" and by_offset[0x94].op_str == "dword ptr [eax + 0x7c00e78], edx"
    print("PASS original 192B renderer flush: 55 x86, two PE HIGHLOW to 0x005C4D40, "
          "two original E8 device getters, native FVF 0x144 and DrawPrimitiveUP vtable slots")
    print("Original 192B flush now has whole-native strict canonical source; "
          "independent pinned-compiler byte/relocation proof is animation_draw_queue_flush_192")

    # Original 93B recursive scale uses the *same 1.0f literal source* as
    # the already strict 93B x/y parent-scale game methods. Its self call
    # remains the original native E8, not a fabricated recursion symbol.
    assert 0x0044588D in relocs
    assert struct.unpack("<I", raw_at(image, base, sections, 0x0044588D, 4))[0] == 0x0056C8CC
    assert any(x.address == 0x004458BC and x.mnemonic == "call" and x.op_str == "0x445880"
               for x in decoded(image, base, sections, 0x00445880, 93))
    assert struct.unpack("<f", raw_at(image, base, sections, 0x0056C8CC, 4))[0] == 1.0

    # The color helpers are native integer color-word getters, NOT float
    # conversions as an untyped Ghidra decompile may print. Their caller
    # keeps the original EAX value and writes it as a 32-bit word.
    assert heads[0x00443DA9].mnemonic == "call" and heads[0x00443DA9].op_str == "0x4456e0"
    assert heads[0x00443DAE].mnemonic == "mov" and heads[0x00443DAE].op_str == "dword ptr [ebp - 0x2c], eax"

    print(f"PASS entire original Renderer/Animation draw Boss {BODY_SIZE}B / {len(instructions)} i386, "
          f"{len(native_calls)} E8 / {len(called)} callees, {len(original_body_relocs)} body HIGHLOW")
    print("PASS combined original dispatch tables: 80/80 .reloc pointers, "
          "main 49 and nested 31; return/padding and mode guards verified")
    print("PARENT SOURCE-PRESENT but NONEXACT; native PE evidence and exact children never imply parent byte equality.")


if __name__ == "__main__":
    verify()
