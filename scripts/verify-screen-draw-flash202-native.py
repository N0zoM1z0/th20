#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 202B flash draw callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_draw_flash',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424FA0
SIZE=202
SHA='c773e89c092fa29689eec416571e5c8f185236a2ebac3bc47ff38afb8e30b397'
CALLS={0x15:0x0041CAD0,0x28:0x0041CAF0,0x3B:0x0041CAD0,0x4E:0x00424010,0x6A:0x0041CAF0,0x7D:0x00421810,0xAF:0x00423650,0xC1:0x005429EE}
HIGHLOW={0x07:0x005B25C0,0x11:0x005B6758,0x24:0x005B6758,0x37:0x005B6758,0x45:0x005B6758,0x66:0x005B6758,0x74:0x005B6758}
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
 print('PASS ScreenInf flash draw: immutable 202B body, eight physical E8 targets, seven physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
