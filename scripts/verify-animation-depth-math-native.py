#!/usr/bin/env python3
"""Original-PE-only full animation depth and depth-squared ABI/provenance.

The locked PE provides genuine original 25B/70B x86 boundaries and E8
sites. No source or manifest target is inferred from the candidate COFF.
"""
from collections import defaultdict
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
native=importlib.util.module_from_spec(sp)
sp.loader.exec_module(native)

HEADS={0x00445700:25,0x00445720:70}
CALLERS={0x004408B0:2769,0x00441C00:753}


def verify():
    image,_=native.verified_target()
    base,sections=native.parse_sections(image)
    reloc_sites=native.physical_highlow(image,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    bodies={}
    for head,size in HEADS.items():
        data=native.raw_at(image,base,sections,head,size)
        ins=list(cs.disasm(data,head))
        assert ins and ins[-1].address+ins[-1].size==head+size
        assert ins[-1].mnemonic=='ret' and ins[-1].op_str==''
        assert not any(head<=site<head+size for site in reloc_sites)
        bodies[head]=ins
    squared=bodies[0x00445720]
    assert len(squared)==22
    assert squared[0].mnemonic=='push' and squared[-1].mnemonic=='ret'
    assert [(x.mnemonic,x.op_str) for x in squared if x.mnemonic in ('mulss','addss')]==[
        ('mulss','xmm0, dword ptr [ecx]'),
        ('mulss','xmm1, dword ptr [eax + 4]'),
        ('addss','xmm0, xmm1'),
        ('mulss','xmm1, dword ptr [edx + 8]'),
        ('addss','xmm0, xmm1'),
    ]
    assert squared[-4].mnemonic=='fld' and squared[-4].op_str=='dword ptr [ebp - 4]'
    wrapper=bodies[0x00445700]
    assert len(wrapper)==10
    calls=[]
    for x in wrapper:
        if x.mnemonic=='call' and x.bytes[0]==0xe8 and len(x.bytes)==5:
            target=(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
            calls.append((x.address-0x00445700,target))
    assert calls==[(0x7,0x00445720),(0xF,0x00446B30)]
    assert [(x.mnemonic,x.op_str) for x in wrapper if x.mnemonic=='fstp']==[
        ('fstp','dword ptr [esp]')]
    print('PASS original depth_squared: complete 70B/22 i386, 3 original SSE squares +2 adds, x87 FLD ST0, no native PE HIGHLOW')
    print('PASS original depth wrapper: complete 25B/10 i386, real E8 +0x7 to 0x00445720 and +0xF to 0x00446B30, no native PE HIGHLOW')
    source_sites=defaultdict(set)
    for head,size in CALLERS.items():
        code=native.raw_at(image,base,sections,head,size)
        ins=list(cs.disasm(code,head))
        assert ins and ins[-1].address+ins[-1].size==head+size
        for x in ins:
            if x.bytes[0]==0xe8 and len(x.bytes)==5:
                target=(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
                if target==0x00445700:
                    source_sites[head].add(x.address)
    assert dict(source_sites)=={
        0x004408B0:{0x004409C8},
        0x00441C00:{0x00441D2A},
    }
    print('PASS original game-specific consumers: physical E8 at 0x004409C8 in 2769B mode6 and 0x00441D2A in 753B mode7; other caller source is not assumed exact')
    print('Native evidence is independent of C++ source; exact acceptance requires both complete canonical units with independently mapped REL32 roles')


if __name__=='__main__':verify()
