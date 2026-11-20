#!/usr/bin/env python3
"""Attest the immutable TH20 1407B Graphics rectangle submission routine."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_draw_rectangle',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x00423650
SIZE=1407
SHA='b984d181492439c5588509db61783043e6d850a6d68b980a0f8d93108c959760'
CALLS={
 0x019:0x004455C0,0x02B:0x0040BC20,
 0x05B:0x00422DD0,0x0A7:0x00422DD0,0x0F2:0x00422DD0,0x13D:0x00422DD0,
 0x33B:0x00412730,0x369:0x00412730,0x397:0x00412730,0x3C5:0x00412730,
 0x3F3:0x00412730,0x41F:0x00412730,0x449:0x00412730,
 0x47C:0x0041DB80,0x487:0x00424080,0x492:0x0041DBA0,
 0x49D:0x0041DB60,0x4A8:0x0041DB40,0x4B3:0x004240A0,
 0x4BD:0x00412730,0x4EB:0x00412730,0x519:0x00412730,0x547:0x00412730,
 0x576:0x005429EE,
}
HIGHLOW={
 0x00A:0x005B25C0,0x015:0x005C0028,0x01F:0x00423470,
 0x167:0x005C0028,0x191:0x005C0028,0x1BA:0x005C0028,
 0x1E3:0x005C0028,0x20B:0x005C0028,0x232:0x005C0028,
 0x25B:0x005C0028,0x284:0x005C0028,
 0x2B0:0x0056C8CC,0x2C5:0x0056C8CC,0x2DB:0x0056C8CC,0x2F1:0x0056C8CC,
 0x337:0x005C4D40,0x365:0x005C4D40,0x393:0x005C4D40,
 0x3C1:0x005C4D40,0x3EF:0x005C4D40,0x41B:0x005C4D40,0x445:0x005C4D40,
 0x478:0x005C0028,0x483:0x005C0028,0x48E:0x005C0028,
 0x499:0x005C0028,0x4A4:0x005C0028,0x4AF:0x005C0028,
 0x4B9:0x005C4D40,0x4E7:0x005C4D40,0x515:0x005C4D40,0x543:0x005C4D40,
}
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
 assert len(calls)==24 and len(actual)==32
 print('PASS Graphics rectangle submission: immutable 1407B body, 24 physical E8 targets, 32 physical HIGHLOW fields')
 print('SHA-256',hashlib.sha256(body).hexdigest())
if __name__=='__main__':verify()
