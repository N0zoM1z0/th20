#!/usr/bin/env python3
"""Independently prove immutable PE 156B solo ribbon draw and vtable."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86,CS_MODE_32,Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045DA40,156
CALLS={0x20:0x00445BC0,0x28:0x00422E10,0x3D:0x004376E0,
       0x4F:0x0040BDA0,0x5A:0x0045DCE0,0x84:0x0045DAE0,0x93:0x005429EE}
DATA={0x07:0x005B25C0,0x1C:0x005C0028}
VTABLE=0x0056ECA4
SLOTS=(0x0045D6B0,0x0045D6F0,HEAD,0x00412540,0x00414B50,0x00414B50)

def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);hi=pe.physical_highlow(image,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==53 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0] for p in hi if HEAD<=p<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 assert (ins[21].address-HEAD,ins[21].mnemonic)==(0x42,'nop')
 assert ('add','eax, 0x3c0') in [(i.mnemonic,i.op_str) for i in ins]
 v=struct.unpack('<6I',pe.raw_at(image,base,sec,VTABLE,24));assert v==SLOTS,(v,SLOTS)
 assert all(VTABLE+4*i in hi for i in range(6))
 for off,target in CALLS.items():print(f'PASS original 156B E8 +{off:#04x} -> {target:#010x}')
 for off,target in DATA.items():print(f'PASS original 156B HIGHLOW +{off:#04x} -> {target:#010x}')
 print('PASS original 156B/53-x86, scope NOP+0x42, single 0x3C0 step and true 0x56ECA4 vtable')
 print('NOTE distinct 76B solo fan renderer child requires separate strict acceptance')

if __name__=='__main__':verify()
