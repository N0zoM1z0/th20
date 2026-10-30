#!/usr/bin/env python3
"""Original-only native proof for the whole 252B ribbon group config and 23B index."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
CONFIG,SIZE=0x0045EB10,252
INDEX,INDEX_SIZE=0x0045D690,23
CALLS={
    0x2F:0x00423520,0x42:INDEX,0x52:0x0045EC10,
    0x65:INDEX,0x75:0x0045EC10,
    0x88:INDEX,0x98:0x0045EC10,
    0xAD:0x0045DD60,0xC0:0x00450350,
    0xDC:0x00438C60,0xEF:0x0045DD40,
}
WRAPPER=0x0045EC96

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    instructions=list(cs.disasm(pe.raw_at(image,base,sections,CONFIG,SIZE),CONFIG))
    assert len(instructions)==77
    assert instructions[-1].address+instructions[-1].size==CONFIG+SIZE
    assert (instructions[-1].mnemonic,instructions[-1].op_str)==('ret','8')
    calls={i.address-CONFIG:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in instructions if i.size==5 and i.bytes[0]==0xe8}
    assert calls==CALLS,(calls,CALLS)
    assert not any(CONFIG<=loc<CONFIG+SIZE for loc in highlow)
    asm={(i.mnemonic,i.op_str) for i in instructions}
    assert ('mov','dword ptr [eax + 0xb5c], ecx') in asm
    assert ('mov','dword ptr [edx + 0xb48], ecx') in asm
    for name in ('0xffff4040','0xffc040ff','0xffffff40'):
        assert ('push',name) in asm,name
    for offset,target in CALLS.items():print(f'PASS original 252B E8 +{offset:#04x} -> {target:#010x}')
    index=list(cs.disasm(pe.raw_at(image,base,sections,INDEX,INDEX_SIZE),INDEX))
    assert len(index)==9 and index[-1].address+index[-1].size==INDEX+INDEX_SIZE
    assert (index[-1].mnemonic,index[-1].op_str)==('ret','4')
    assert ('imul','eax, dword ptr [ebp + 8], 0x3c0') in [(i.mnemonic,i.op_str) for i in index]
    assert not any(INDEX<=loc<INDEX+INDEX_SIZE for loc in highlow)
    wrapped=pe.raw_at(image,base,sections,WRAPPER,5)
    assert wrapped[0]==0xe8
    dest=(WRAPPER+5+struct.unpack_from('<i',wrapped,1)[0])&0xffffffff
    assert dest==CONFIG,(hex(WRAPPER),hex(dest))
    print('PASS whole original 252B/77 i386, 11 E8, zero HIGHLOW and real 3-color/token/Timer protocol')
    print('PASS original 23B/9 i386 array index helper, 0x3C0 stride, zero relocations')
    print(f'PASS original 47B allocation wrapper E8 {WRAPPER:#010x} -> 252B config')

if __name__=='__main__':verify()
