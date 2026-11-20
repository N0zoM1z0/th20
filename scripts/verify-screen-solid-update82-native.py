#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 82B solid-alpha callback."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_solid',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00424460
SIZE=82
SHA='ca1a295bd3efc7ec50fefcb052bb9bf76eae943c8d4908a8092f7ed5a7e99fb4'
CALLS={0x23:0x004235C0,0x44:0x00423540}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,ADDRESS,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDRESS))
 calls={i.address-ADDRESS:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in instructions if i.size==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 assert not any(ADDRESS<=site<ADDRESS+SIZE for site in pe.physical_highlow(image,base,sections))
 print('PASS ScreenInf solid-alpha update: immutable 82B body, two physical E8 targets, no PE HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
