#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 180B fade-out callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_fade_out',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x004240C0
SIZE=180
SHA='164161176b12d19bf0648c713e04f60ac7f5b35e48fe966be1da6a4664ec997e'
CALLS={0x28:0x00423BD0,0x85:0x004235C0,0xA6:0x00423540}
HIGHLOW={0x08:0x005BA518,0x39:0x0056CD9C,0x4D:0x0056CD9C}
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
 print('PASS ScreenInf fade-out update: immutable 180B body, three physical E8 targets, three physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
