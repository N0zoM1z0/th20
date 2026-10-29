#!/usr/bin/env python3
"""Independent immutable original-PE audit of 5,993B Animation draw Boss.

Treat the target executable, its PE32 .reloc section and real instruction
boundaries as ground truth. This script verifies both of the *distinct* native
switch tables; it does not assert source-level exactness for the parent body.
"""
from collections import Counter
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
    print("PARENT remains SOURCE-ABSENT and NONEXACT; exact child coverage never implies boss byte exactness.")


if __name__ == "__main__":
    verify()
