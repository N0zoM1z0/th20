#!/usr/bin/env python3
"""Immutable original PE audit of 156B solo ribbon C++17 factory + parent E8."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D2C0,156
CALLS={0x2D:0x0054275D,0x4D:0x0040C080,0x56:0x0040B280,0x6A:0x0045D5B0}
DATA={0x06:0x005688D7,0x15:0x005B25C0}
PARENT=0x0045DC70+0x13

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==46 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xE8}
 data={loc-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,loc,4))[0] for loc in high if HEAD<=loc<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 assert sum((i.mnemonic,i.op_str)==('push','0x3e0') for i in ins)==2
 parent=pe.raw_at(im,base,sec,PARENT,5);assert parent[0]==0xE8
 target=(PARENT+5+struct.unpack_from('<i',parent,1)[0])&0xffffffff;assert target==HEAD
 for o,t in calls.items():print(f'PASS original factory E8 +{o:#04x} -> {t:#010x}')
 for o,t in data.items():print(f'PASS original factory HIGHLOW +{o:#04x} -> {t:#010x}')
 print('PASS original complete 156B/46-i386, real 0x3E0 new+automatic class zero+forward+89B ctor')
 print(f'PASS original 47B wrapper E8 {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
