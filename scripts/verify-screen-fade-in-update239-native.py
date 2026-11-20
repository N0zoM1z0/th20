#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 239B fade-in callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_fade_in',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424260
SIZE=239
SHA='b86bd0b012c10549096753b86f0e117e3aed8e372a66fdf44c9c1bb5b9cbe3fa'
CALLS={0x35:0x00423560,0x47:0x00423BD0,0xA7:0x004235C0,0xC9:0x00424030,0xE0:0x00423540}
HIGHLOW={0x08:0x005BA518,0x58:0x0056CD9C,0xBC:0x005BA828,0xC5:0x005BA828}
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
 print('PASS ScreenInf fade-in update: immutable 239B body, five physical E8 targets, four physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
