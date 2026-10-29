#!/usr/bin/env python3
"""Independently attest original 3159-byte Animation quad renderer Boss.

Reads ONLY the locked PE, its real IMAGE_REL_BASED_HIGHLOW directory and x86
instructions. This does not accept the still-source-absent 3159B parent as
matched code. Strict whole-native acceptance is handled separately.
"""
from collections import Counter
from pathlib import Path
import importlib.util
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('orig_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
assert spec and spec.loader
DRAW=importlib.util.module_from_spec(spec)
spec.loader.exec_module(DRAW)
HEAD=0x0043F6A0
SIZE=3159
COLOR_MATH={0x0043F520:(45,24),0x0043F4F0:(35,4)}
CALLS={
 0x00445B80:4, 0x00437CD0:1, 0x004455C0:2, 0x00412730:1,
 0x00445A00:1, 0x0043F520:24, 0x0043F4F0:4, 0x00445BA0:1,
 0x00446690:1, 0x0043E9B0:1, 0x005429EE:1,
}
HIGHLOW_TARGETS={
 0x005AEF10:23,0x005AEF14:22,0x005C5840:16,0x005AEF20:16,
 0x005AEF24:6,0x005AEF28:6,0x0056E0EC:4,0x005B25C0:1,
 0x005C4D40:1,0x004402F8:1,
}

def verify():
    image,_=DRAW.verified_target()
    base,sections=DRAW.parse_sections(image)
    pe_highlow=DRAW.physical_highlow(image,base,sections)
    body=DRAW.decoded(image,base,sections,HEAD,SIZE)
    assert len(body)==763 and body[-1].mnemonic=='ret' and body[-1].op_str=='8'
    assert body[-1].address+body[-1].size==HEAD+SIZE
    calls=Counter(
        (inst.address+5+struct.unpack_from('<i',inst.bytes,1)[0])&0xffffffff
        for inst in body if len(inst.bytes)==5 and inst.bytes[0]==0xE8
    )
    assert calls==CALLS,('original call histogram changed',calls)
    addresses=sorted(at for at in pe_highlow if HEAD<=at<HEAD+SIZE)
    assert len(addresses)==96
    targets=Counter(struct.unpack('<I',DRAW.raw_at(image,base,sections,at,4))[0]
                    for at in addresses)
    assert targets==HIGHLOW_TARGETS,('original .reloc fields changed',targets)
    assert HEAD+SIZE==0x004402F7
    assert 0x004402F8 in targets # Real original exception / unwind pointer
    for head,(size,count) in COLOR_MATH.items():
        assert calls[head]==count
        child=DRAW.decoded(image,base,sections,head,size)
        assert child[-1].mnemonic=='ret' and child[-1].op_str==''
        assert child[-1].address+child[-1].size==head+size
        assert not any(head<=at<head+size for at in pe_highlow)
        print(f'PASS original {head:#010x} complete {size}B color arithmetic, '
              f'{len(child)} i386, {count} actual parent E8 sites, zero PE relocations')
    # Confirm actual original vertex buffer and 0.5f scene constant, without
    # relying on C++ source names or Ghidra guessed floats.
    assert struct.unpack('<f',DRAW.raw_at(image,base,sections,0x0056E0EC,4))[0]==0.5
    assert len(DRAW.raw_at(image,base,sections,0x005AEF10,112))==112
    print(f'PASS original quad renderer {SIZE}/{SIZE}B, 763/763 x86, '
          '41/41 native E8 and all 11 distinct native targets')
    print('PASS original renderer exactly 96 genuine PE HIGHLOW fields and '
          'all 10 original target address multiplicities')
    print('PARENT NONEXACT unless a separately verified complete pinned-MSVC '
          'C++ source + original relocation replay is accepted')

if __name__=='__main__':
    verify()
