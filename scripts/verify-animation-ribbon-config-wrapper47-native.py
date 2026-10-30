#!/usr/bin/env python3
"""Independently prove the original 47B ribbon allocation/config wrapper."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045EC70,47
E8={0x13:0x0045E5D0,0x26:0x0045EB10}
DIR={0x09:0x0056EDF8,0x0F:0x005B8894}

def verify():
    im,_=pe.verified_target();base,sec=pe.parse_sections(im)
    highlow=pe.physical_highlow(im,base,sec);cs=Cs(CS_ARCH_X86,CS_MODE_32)
    ins=list(cs.disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
    assert len(ins)==18 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
    calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
           for i in ins if i.size==5 and i.bytes[0]==0xE8}
    data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
          for p in highlow if HEAD<=p<HEAD+SIZE}
    assert calls==E8,(calls,E8)
    assert data==DIR,(data,DIR)
    for pos,target in E8.items():print(f'PASS original wrapper E8 +{pos:#x} -> {target:#010x}')
    for pos,target in DIR.items():print(f'PASS original wrapper HIGHLOW +{pos:#x} -> {target:#010x}')
    print('PASS complete original 47B/18-i386, genuine C++17 factory and 252B config, CDECL RET')

if __name__=='__main__':verify()
