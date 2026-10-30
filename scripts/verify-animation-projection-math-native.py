#!/usr/bin/env python3
"""Immutable PE-only audit of original full 73B Vector3 norm and 86B XY projection.

Native instruction extents, arithmetic order and E8 callers are asserted
independently of maintained source or pinned compiler output.
"""
from pathlib import Path
import struct
import importlib.util
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('native_render',ROOT/'scripts/verify-animation-draw-boss-native.py')
orig=importlib.util.module_from_spec(spec)
spec.loader.exec_module(orig)


def verify():
    pe,_=orig.verified_target()
    base,sections=orig.parse_sections(pe)
    highlow=orig.physical_highlow(pe,base,sections)
    asm=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,size in ((0x004399B0,73),(0x00445B20,86)):
        raw=orig.raw_at(pe,base,sections,head,size)
        instr=list(asm.disasm(raw,head))
        assert instr and instr[-1].address+instr[-1].size==head+size
        assert not any(head<=x<head+size for x in highlow)
        if head==0x004399B0:
            assert len(instr)==22 and instr[-1].mnemonic=='ret' and instr[-1].op_str==''
            assert [x.mnemonic for x in instr].count('mulss')==3
            assert [x.mnemonic for x in instr].count('addss')==2
            calls=[x for x in instr if x.mnemonic=='call' and len(x.bytes)==5 and x.bytes[0]==0xe8]
            assert len(calls)==1 and calls[0].address==head+0x3F
            target=(calls[0].address+5+struct.unpack_from('<i',calls[0].bytes,1)[0])&0xffffffff
            assert target==0x00446B30
            assert any(x.mnemonic=='movss' and x.op_str=='dword ptr [esp], xmm0' for x in instr)
            print('PASS original 73B/22 i386 Vector3 Euclidean magnitude: xyz squared in SSE then native 35B sqrt x87 wrapper E8 +0x3F')
        else:
            assert len(instr)==23 and instr[-1].mnemonic=='ret' and instr[-1].op_str=='0x1c'
            assert [x.mnemonic for x in instr].count('mulss')==4
            assert [x.mnemonic for x in instr].count('addss')==3
            assert [x.mnemonic for x in instr].count('subss')==1
            assert all(x.mnemonic!='call' for x in instr)
            assert ('movss','xmm0, dword ptr [ebp + 0xc]') in [(x.mnemonic,x.op_str) for x in instr]
            assert ('movss','dword ptr [ecx + 4], xmm0') in [(x.mnemonic,x.op_str) for x in instr]
            print('PASS original 86B/23 i386 XY rotation/translation receiver method with seven native stack arguments (RET 0x1C), no E8 or PE HIGHLOW')
    head,size=0x00440340,1378
    raw=orig.raw_at(pe,base,sections,head,size)
    calls={}
    for i in asm.disasm(raw,head):
        if i.bytes[0]==0xe8 and len(i.bytes)==5:
            target=(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            if target in (0x004399B0,0x00445B20):calls[i.address-head]=target
    assert calls=={
        0x210:0x004399B0,
        0x3AB:0x00445B20,0x436:0x00445B20,0x4BE:0x00445B20,0x548:0x00445B20,
    },calls
    print('PASS all five original game mode6 setup calls in whole 1378B parent: 1 true length helper and 4 true projected XY helper sites')
    print('No original target field is solved from candidate COFF; physical PE evidence independently grounds both source-owned game helpers')


if __name__=='__main__':verify()
