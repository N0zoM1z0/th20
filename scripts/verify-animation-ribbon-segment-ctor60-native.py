#!/usr/bin/env python3
"""Original-only 60B ribbon segment constructor physical boundary and calls."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D610,60
CALLS={0x0A:0x0045D500,0x18:0x0045D4B0,0x2D:0x00544760}
ARRAY_CALLBACK=0x0045E670+0x27

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    raw=pe.raw_at(image,base,sections,HEAD,SIZE)
    decoded=list(cs.disasm(raw,HEAD))
    assert len(decoded)==20
    assert decoded[-1].address+decoded[-1].size==HEAD+SIZE
    assert (decoded[-1].mnemonic,decoded[-1].op_str)==('ret','')
    calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in decoded if i.size==5 and i.bytes[0]==0xE8}
    assert calls==CALLS,(calls,CALLS)
    assert not any(HEAD<=loc<HEAD+SIZE for loc in highlow)
    assert ('push','0xf0') in [(i.mnemonic,i.op_str) for i in decoded]
    assert ('add','ecx, 0x1e0') in [(i.mnemonic,i.op_str) for i in decoded]
    callback=struct.unpack('<I',pe.raw_at(image,base,sections,ARRAY_CALLBACK,4))[0]
    assert callback==HEAD and ARRAY_CALLBACK in highlow
    print('PASS complete original 60B/20 i386, no HIGHLOW, three full native E8')
    for site,destination in calls.items():print(f'PASS original E8 +{site:#x} -> {destination:#010x}')
    print('PASS 60x8 Vector2, 60x4 color cells, 0xF0 float clear')
    print(f'PASS original group segment array DIR32 callback {ARRAY_CALLBACK:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
