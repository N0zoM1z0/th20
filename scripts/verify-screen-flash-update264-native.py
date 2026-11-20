#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 264B flash-update boundary."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_flash',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424350
SIZE=264
SHA='7add5c377a2f3a13ba43d959ebf4fc5aa0ee56f4947aefac10f3a7a8645ca77e'
CALLS={0x3E:0x00423560,0x50:0x00423BD0,0xE6:0x00423520,0xFA:0x00423540}
HIGHLOW={0x1A:0x005BA518,0x73:0x0056CDD0}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,ADDRESS,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDRESS))
 calls={i.address-ADDRESS:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in instructions if i.size==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 highlow=pe.physical_highlow(image,base,sections)
 actual={site-ADDRESS:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
         for site in highlow if ADDRESS<=site<ADDRESS+SIZE}
 assert actual==HIGHLOW,(actual,HIGHLOW)
 print('PASS ScreenInf flash update: immutable 264B body, four physical E8 targets, two physical HIGHLOW targets')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
