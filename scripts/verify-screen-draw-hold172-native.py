#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 172B hold draw callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_draw_hold',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424E80
SIZE=172
SHA='2d1e6d72279333041926e6a5cc770aa70d3ea3e4182ea33b810950730e3a94cc'
CALLS={0x91:0x00423650,0xA3:0x005429EE}
HIGHLOW={0x07:0x005B25C0,0x1D:0x0056CDAC,0x25:0x0056CDA4,0x2D:0x0056C8D0,0x3A:0x0056CD90,0x47:0x0056CDAC,0x4F:0x0056CDA4,0x57:0x0056C8D0,0x5F:0x0056CDA4,0x6C:0x0056CD90,0x74:0x0056D7C0}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,ADDRESS,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDRESS))
 calls={i.address-ADDRESS:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in instructions if i.size==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 highlow=pe.physical_highlow(image,base,sections)
 actual={site-ADDRESS:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0] for site in highlow if ADDRESS<=site<ADDRESS+SIZE}
 assert actual==HIGHLOW,(actual,HIGHLOW)
 print('PASS ScreenInf hold draw: immutable 172B body, two physical E8 targets, eleven physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
