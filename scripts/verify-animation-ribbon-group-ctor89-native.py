#!/usr/bin/env python3
"""Immutable-PE proof of the original 89B ribbon polymorphic constructor.

Whole function and real vtable/relocation roles; original evidence is
independent from the MSVC canonical COFF exactness check.
"""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "original", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD, SIZE = 0x0045E6D0, 89
CALLS = {0x0E: 0x00446B60, 0x22: 0x0045E670, 0x3E: 0x00422D90}
HIGHLOW = {0x18: 0x0056EDDC}
VTABLE = 0x0056EDDC
VTABLE_CONTENTS = (0x0045E730, 0x0045E770, 0x0045EA20,
                   0x00412540, 0x00414B50, 0x00414B50)


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    highlow = pe.physical_highlow(image, base, sections)
    instructions = list(decoder.disasm(pe.raw_at(image, base, sections, HEAD, SIZE), HEAD))
    assert len(instructions) == 25, len(instructions)
    assert instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert (instructions[-1].mnemonic, instructions[-1].op_str) == ("ret", "4")
    observed = {
        i.address - HEAD: (i.address + i.size + struct.unpack_from("<i", i.bytes, 1)[0]) & 0xFFFFFFFF
        for i in instructions if i.size == 5 and i.bytes[0] == 0xE8
    }
    assert observed == CALLS, (observed, CALLS)
    actual = {
        loc - HEAD: struct.unpack("<I", pe.raw_at(image, base, sections, loc, 4))[0]
        for loc in highlow if HEAD <= loc < HEAD + SIZE
    }
    assert actual == HIGHLOW, (actual, HIGHLOW)
    pairs = [(i.mnemonic, i.op_str) for i in instructions]
    assert ("movss", "dword ptr [edx + 0xb48], xmm0") in pairs
    assert ("add", "ecx, 0xb4c") in pairs
    assert ("mov", "dword ptr [eax + 0xb5c], 0") in pairs
    contents = struct.unpack("<6I", pe.raw_at(image, base, sections, VTABLE, 24))
    assert contents == VTABLE_CONTENTS, contents
    assert all(VTABLE + i * 4 in highlow for i in range(6))
    # Original 20B folded virtual destructor is shared by ribbon and polygon
    # scalar deleting wrappers. It has a genuine base-dtor E8 and no vptr write.
    for dtor, dsize, nins, expected, ret_op in (
        (0x0045C2A0, 20, 10, {0x0A: 0x00446BA0}, ""),
        (0x0045E730, 49, 18,
         {0x0A: 0x0045C2A0, 0x20: 0x0054278D}, "4"),
    ):
        body = list(decoder.disasm(pe.raw_at(image, base, sections, dtor, dsize), dtor))
        assert len(body) == nins and body[-1].address + body[-1].size == dtor + dsize
        assert (body[-1].mnemonic, body[-1].op_str) == ("ret", ret_op)
        native_calls = {
            i.address - dtor: (i.address + i.size + struct.unpack_from("<i", i.bytes, 1)[0]) & 0xFFFFFFFF
            for i in body if i.size == 5 and i.bytes[0] == 0xE8
        }
        assert native_calls == expected, (hex(dtor), native_calls, expected)
        assert not any(dtor <= loc < dtor + dsize for loc in highlow)
        if dtor == 0x0045E730:
            assert ("push", "0xb60") in [(i.mnemonic, i.op_str) for i in body]
        print(f"PASS original 0x{dtor:08X}: {dsize}B/{nins} i386, real E8={len(expected)}, zero HIGHLOW")
    for pos, target in CALLS.items():
        print(f"PASS native 89B E8 +{pos:#04x} -> {target:#010x}")
    print("PASS original 89B/25 i386, real derived vptr and one complete HIGHLOW")
    print("PASS original float+0xB48, Timer+0xB4C and zero word+0xB5C")
    print("PASS original six-slot vtable 0x56EDDC: delete/update/draw/inherited x3")
    # Both generated destructors have independent physical original bodies.
    for head,size,nins,expected,final_ret in (
        (0x0045C2A0,20,10,{0x0A:0x00446BA0},("ret","")),
        (0x0045E730,49,18,{0x0A:0x0045C2A0,0x20:0x0054278D},("ret","4")),
    ):
        code=pe.raw_at(image,base,sections,head,size)
        ins=list(decoder.disasm(code,head))
        assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
        assert (ins[-1].mnemonic,ins[-1].op_str)==final_ret
        calls={x.address-head:(x.address+5+struct.unpack_from("<i",x.bytes,1)[0])&0xFFFFFFFF
               for x in ins if x.size==5 and x.bytes[0]==0xE8}
        assert calls==expected,(hex(head),calls,expected)
        assert not any(head<=loc<head+size for loc in highlow)
        if head==0x0045C2A0:
            assert ("nop","") in [(x.mnemonic,x.op_str) for x in ins]
        else:
            assert ("push","0xb60") in [(x.mnemonic,x.op_str) for x in ins]
        print(f"PASS original {head:#010x}: complete {size}B/{nins} i386, {len(calls)} E8, zero HIGHLOW")
    print("NOTE original 20B destructor is a folded physical head, unique historical type remains unknown")



if __name__ == "__main__":
    verify()
