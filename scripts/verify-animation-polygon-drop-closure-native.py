#!/usr/bin/env python3
"""Original-PE-only 27-function counted-range closure evidence.

Addresses, instruction boundaries and E8 site/destination pairs were
frozen from the locked original executable, not from comparison COFF.
No source or COFF object is read or modified by this verifier.
The separate canonical comparator establishes compiled-source exactness.
"""
from pathlib import Path
import importlib.util, struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location("locked_pe",ROOT/"scripts/verify-animation-draw-boss-native.py")
pe=importlib.util.module_from_spec(sp); sp.loader.exec_module(pe)

# Entire original function bodies, native instruction counts, E8 sites/targets.
# All 27 have ZERO original PE HIGHLOW data relocation fields.
ORIGINAL = {
    0x0045EDF0: (30, 12, {0x12:0x0045FD60}),
    0x0045EE30: (23, 9, {0xE:0x0045FFE0}),
    0x0045EE90: (30, 12, {0x12:0x0045FD80}),
    0x0045EED0: (23, 9, {0xE:0x0045FFF0}),
    0x0045EEF0: (30, 12, {0x12:0x0045FE60}),
    0x0045EF30: (23, 9, {0xE:0x00460000}),
    0x0045EF50: (17, 8, {0x7:0x0045EF30}),
    0x0045EF70: (30, 12, {0x12:0x0045FE90}),
    0x0045EFB0: (23, 9, {0xE:0x00460020}),
    0x0045EFD0: (17, 8, {0x7:0x0045EFB0}),
    0x0045F140: (45, 19, {}),
    0x0045F170: (30, 13, {}),
    0x0045F190: (30, 13, {}),
    0x0045F1B0: (33, 15, {0x12:0x0045F170}),
    0x0045F1E0: (33, 15, {0x12:0x0045F190}),
    0x0045F4C0: (48, 19, {0xC:0x0040C080, 0x22:0x0045F560}),
    0x0045F4F0: (48, 19, {0xC:0x0040C080, 0x22:0x0045F580}),
    0x0045F520: (32, 14, {}),
    0x0045F540: (32, 14, {}),
    0x0045F560: (28, 12, {0xE:0x0045F520}),
    0x0045F580: (28, 12, {0xE:0x0045F540}),
    0x0045FD60: (30, 13, {0x10:0x0045F1B0}),
    0x0045FD80: (30, 13, {0x10:0x0045F1E0}),
    0x0045FE60: (34, 15, {0x11:0x0045EDF0}),
    0x0045FE90: (34, 15, {0x11:0x0045EE90}),
    0x00460000: (25, 12, {0xD:0x0045EE30}),
    0x00460020: (25, 12, {0xD:0x0045EED0}),
}

def verify():
    assert len(ORIGINAL)==27
    assert sum(row[0] for row in ORIGINAL.values())==811
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,(size,count,expected_calls) in ORIGINAL.items():
        code=pe.raw_at(image,base,sections,head,size)
        ops=list(decoder.disasm(code,head))
        assert len(ops)==count and ops[-1].address+ops[-1].size==head+size
        assert ops[-1].mnemonic=="ret"
        calls={i.address-head:(i.address+i.size+struct.unpack_from("<i",i.bytes,1)[0])&0xffffffff
               for i in ops if i.size==5 and i.bytes[0]==0xe8}
        assert calls==expected_calls,(hex(head),calls,expected_calls)
        assert not any(head<=p<head+size for p in highlow)
        print(f"PASS original {head:#010x}: {size}B/{count} x86, {len(calls)} immutable E8 targets, zero HIGHLOW")
    print("PASS 27 original function extents, 811 original code bytes, 24 E8 roles, zero HIGHLOW")

if __name__=="__main__":verify()
