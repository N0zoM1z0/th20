#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 221B hold callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_hold',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424180
SIZE=221
SHA='1d23dda305aa42822c0caa729ec7441f961aece14da76d6b8768c4c34bf0f747'
CALLS={0x2B:0x00423590,0x3D:0x00423BD0,0x78:0x00423590,0x8A:0x00423BD0,0xCF:0x00423540}
HIGHLOW={0x4E:0x0056CD98,0x9B:0x0056CD98,0xA3:0x0056D7BC}
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
 print('PASS ScreenInf hold update: immutable 221B body, five physical E8 targets, three physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
