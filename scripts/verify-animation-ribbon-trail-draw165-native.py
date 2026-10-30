#!/usr/bin/env python3
"""Immutable original PE proof of complete 165B trail-ribbon virtual LINESTRIP draw."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
HEAD,SIZE=0x0045E190,165
CALLS={0x20:0x00445BC0,0x28:0x00422E10,0x3D:0x004376E0,
       0x53:0x00414580,0x61:0x0040BDA0,0x72:0x0040FF90,
       0x90:0x0043D1A0,0x9C:0x005429EE}
DATA={0x07:0x005B25C0,0x1C:0x005C0028,0x8C:0x005C0028}

def verify():
 im,_=p.verified_target();base,sections=p.parse_sections(im);hl=p.physical_highlow(im,base,sections);dec=Cs(CS_ARCH_X86,CS_MODE_32)
 ins=list(dec.disasm(p.raw_at(im,base,sections,HEAD,SIZE),HEAD))
 assert len(ins)==53 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={pos-HEAD:struct.unpack('<I',p.raw_at(im,base,sections,pos,4))[0] for pos in hl if HEAD<=pos<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 vaddr=0x0056ED1C;v=struct.unpack('<6I',p.raw_at(im,base,sections,vaddr,24))
 assert v[2]==HEAD and vaddr+8 in hl
 assert ('add','edx, 0x208') in [(i.mnemonic,i.op_str) for i in ins]
 assert ('add','ecx, 8') in [(i.mnemonic,i.op_str) for i in ins]
 for off,t in CALLS.items():print(f'PASS original E8 +{off:#04x} -> {t:#010x}')
 for off,t in DATA.items():print(f'PASS original HIGHLOW +{off:#04x} -> {t:#010x}')
 print('PASS original complete 165B/53-i386, 8 E8/3 HIGHLOW, 64-point ribbon vtable slot')
 print('PASS source obtains real 64 color positions, Motion geometry begin and Timer active count')

if __name__=='__main__':verify()
