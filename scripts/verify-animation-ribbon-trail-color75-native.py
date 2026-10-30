#!/usr/bin/env python3
"""Original PE proof of 75B 64-cell trail-ribbon color constructor plus real INT3."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
HEAD,SIZE=0x0045DE30,75
CALLS={0x33:0x0040BC20}
DATA={0x06:0x00567600,0x13:0x005B25C0,0x27:0x00425CC0}
PARENT=0x0045DED0+0x30

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==27 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={loc-HEAD:struct.unpack('<I',p.raw_at(im,base,sec,loc,4))[0] for loc in hi if HEAD<=loc<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 assert ('push','0x40') in {(x.mnemonic,x.op_str) for x in ins}
 assert ('push','4') in {(x.mnemonic,x.op_str) for x in ins}
 assert p.raw_at(im,base,sec,HEAD+SIZE,5)==b'\xcc'*5
 raw=p.raw_at(im,base,sec,PARENT,5);assert raw[0]==0xe8
 dest=(PARENT+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff;assert dest==HEAD
 print('PASS original complete 75B/27 i386, genuine 5 INT3, 64x4-byte color elements')
 for off,target in calls.items():print(f'PASS original E8 +{off:#x} -> {target:#010x}')
 for off,target in data.items():print(f'PASS original HIGHLOW +{off:#x} -> {target:#010x}')
 print(f'PASS original 103B trail group constructor E8 {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
