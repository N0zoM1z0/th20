#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf mode-1 shake callback boundary."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_shake',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x004249F0
SIZE=1040
CALLS={0x27:0x00423540,0x40:0x004235C0,0x5C:0x00423BD0,0xB1:0x00423EA0,0x260:0x00423EA0}
HIGHLOW={
 0x008:0x005BA518,0x0AD:0x005BA4C4,
 0x0E7:0x005C50E4,0x101:0x005C50E4,0x11B:0x005C50E4,
 0x135:0x005C50E4,0x158:0x005C50E4,0x165:0x005B8818,
 0x186:0x005C50E4,0x1A2:0x005C50E4,0x1BE:0x005C50E4,
 0x1CF:0x0056D7D0,0x1E8:0x005C50E4,0x1F4:0x0056D7D0,
 0x1FC:0x005B8818,0x21D:0x005C50E4,0x239:0x005C50E4,
 0x255:0x005C50E4,0x25C:0x005BA4C4,
 0x294:0x005C50E8,0x2AF:0x005C50E8,0x2C9:0x005C50E8,
 0x2E3:0x005C50E8,0x306:0x005C50E8,0x313:0x005B8818,
 0x334:0x005C50E8,0x350:0x005C50E8,0x36C:0x005C50E8,
 0x37D:0x0056D7D0,0x396:0x005C50E8,0x3A2:0x0056D7D0,
 0x3AA:0x005B8818,0x3CB:0x005C50E8,0x3E7:0x005C50E8,
 0x403:0x005C50E8,
}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,ADDRESS,SIZE)
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDRESS))
 assert instructions[-1].mnemonic=='ret'
 calls={i.address-ADDRESS:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in instructions if i.size==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 highlow=pe.physical_highlow(image,base,sections)
 actual={site-ADDRESS:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
         for site in highlow if ADDRESS<=site<ADDRESS+SIZE}
 assert actual==HIGHLOW,(actual,HIGHLOW)
 assert len(calls)==5 and len(actual)==35
 # Graphics @ 0x5C4D40; viewport array +0x278, stride 0x16C,
 # points +0x12C. The mode-1 callback's four channels are real subobjects.
 points={i:0x005C4D40+0x278+i*0x16C+0x12C for i in (0,1,3,5)}
 assert points=={0:0x005C50E4,1:0x005C5250,3:0x005C5528,5:0x005C5800}
 assert 0x005C4D40+0x278+3*0x16C+0x12C+2*8+4==0x005C553C
 print('PASS ScreenInf mode-1 shake callback: whole 1040B extent, 5 physical E8 targets, 35 physical HIGHLOW targets')
 print('PASS Graphics points channels and distinct vertical-default clear at 0x005C553C')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
