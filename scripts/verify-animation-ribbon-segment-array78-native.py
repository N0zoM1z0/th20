#!/usr/bin/env python3
"""Original-PE-only whole 78B three-segment ribbon constructor and roles."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045E670,78
E8={0x36:0x0040BC20}
DIR={0x06:0x00567600,0x13:0x005B25C0,0x27:0x0045D610}
PARENT_E8=0x0045E6D0+0x22

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    ins=list(decoder.disasm(pe.raw_at(image,base,sections,HEAD,SIZE),HEAD))
    assert len(ins)==27,len(ins)
    assert ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
    calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xE8}
    absolute={address-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,address,4))[0]
              for address in highlow if HEAD<=address<HEAD+SIZE}
    assert calls==E8,(calls,E8)
    assert absolute==DIR,(absolute,DIR)
    assert ('push','3') in [(i.mnemonic,i.op_str) for i in ins]
    assert ('push','0x3c0') in [(i.mnemonic,i.op_str) for i in ins]
    tail=pe.raw_at(image,base,sections,HEAD+SIZE,5)
    assert tail==b'\xcc'*5,tail
    raw=pe.raw_at(image,base,sections,PARENT_E8,5)
    assert raw[0]==0xE8
    dest=(PARENT_E8+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
    assert dest==HEAD,(hex(PARENT_E8),hex(dest))
    print('PASS complete original 78B/27 i386, three 0x3C0 elements, genuine five INT3 tail')
    print('PASS exact original EH/cookie/60B segment callback HIGHLOW positions and targets')
    print('PASS original native 0x40BC20 EH-vector constructor call at +0x36')
    print(f'PASS original 89B group constructor E8 {PARENT_E8:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
