#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 105B fade draw callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_draw_fade',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424F30
SIZE=105
SHA='9144df384464c48c3467689a33e90470205319dab722f0cb36fc0c7bfdb0d66c'
CALLS={0x4E:0x00423650,0x60:0x005429EE}
HIGHLOW={0x07:0x005B25C0,0x24:0x005B87F8,0x31:0x005B87FC}
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
 print('PASS ScreenInf fade draw: immutable 105B body, two physical E8 targets, three physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
