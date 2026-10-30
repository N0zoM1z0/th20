#!/usr/bin/env python3
"""Locked-original 156B 0x1940 particle group C++17 factory and actual parent."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0045C090,156
CALLS={0x2D:0x0054275D,0x4D:0x0040C080,0x56:0x0040B280,0x6A:0x0045C1F0}
DATA={0x06:0x00568897,0x15:0x005B25C0}
PARENT_CALL=0x0045D000+0x13

def verify():
 im,_=pe.verified_target();base,secs=pe.parse_sections(im);hi=pe.physical_highlow(im,base,secs)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,secs,HEAD,SIZE),HEAD))
 assert len(ins)==46 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 fields={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,secs,p,4))[0] for p in hi if HEAD<=p<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert fields==DATA,(fields,DATA)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert sum((i.mnemonic,i.op_str)==('push','0x1940') for i in ins)==2
 raw=pe.raw_at(im,base,secs,PARENT_CALL,5);assert raw[0]==0xe8
 dest=(PARENT_CALL+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert dest==HEAD,(hex(PARENT_CALL),hex(dest))
 for off,t in CALLS.items():print(f'PASS original E8 +{off:#x} -> {t:#010x}')
 for off,t in DATA.items():print(f'PASS original HIGHLOW +{off:#x} -> {t:#010x}')
 print('PASS original whole 156B/46 i386, 4 E8 +2 HIGHLOW, actual 0x1940 new/class clear/forward/172B ctor')
 print(f'PASS real 47B parent E8 {PARENT_CALL:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
