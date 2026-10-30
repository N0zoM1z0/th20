#!/usr/bin/env python3
"""Original-target 156B trail ribbon C++17 factory plus two native parent callers."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
HEAD,SIZE=0x0045DD90,156
CALLS={0x2D:0x0054275D,0x4D:0x0040C080,0x56:0x0040B280,0x6A:0x0045DED0}
DATA={0x06:0x00568917,0x15:0x005B25C0}
PARENTS=(0x0045E520+0x13,0x0045E550+0x13)

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==46 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={q-HEAD:struct.unpack('<I',p.raw_at(im,base,sec,q,4))[0] for q in hi if HEAD<=q<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 assert sum((i.mnemonic,i.op_str)==('push','0x320') for i in ins)==2
 for address in PARENTS:
  raw=p.raw_at(im,base,sec,address,5);assert raw[0]==0xe8
  target=(address+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert target==HEAD,(hex(address),hex(target))
  print(f'PASS independent original wrapper E8 {address:#010x} -> {HEAD:#010x}')
 for q,t in CALLS.items():print(f'PASS original E8 +{q:#x} -> {t:#010x}')
 for q,t in DATA.items():print(f'PASS original HIGHLOW +{q:#x} -> {t:#010x}')
 print('PASS full native 156B/46 i386, original 0x320 new/autozero/forward/103B constructor')

if __name__=='__main__':verify()
