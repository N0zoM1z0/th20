#!/usr/bin/env python3
"""Attest immutable native ScreenInf constructor, allocator and shutdown bodies."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_lifecycle',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
EXPECTED={
 0x00422D40:{
  'body':67,'sha':'0b5cfc409e5109068a67dad410fdee6b86e18cb12099590dabfaa8ea434c34bd',
  'calls':{0x0C:0x0054275D,0x22:0x0040C080,0x2A:0x004233B0},'data':{}},
 0x004233B0:{
  'body':187,'sha':'e138ded0bce0878b0c3d80ef12aadbefa3180eb43e81ef46d1edf71b8e88dae0',
  'calls':{0x2A:0x0041FD20,0x8E:0x00422D90,0xA2:0x0040C6B0},
  'data':{0x06:0x00567600,0x13:0x005B25C0,0x33:0x0056D744,0x9D:0x0056D750},
  'compare':192,'compare_sha':'38bb8cfc3bbf817acaca2d035fde5f84aeb8a7a9d002cfbdb8506c149ca14479'},
 0x00425070:{
  'body':29,'sha':'d5ecb91fb405d49d002c5df909a290901260bf0212969504825f58ddb4dd656c',
  'calls':{0x0E:0x0041F7C0},'data':{0x09:0x005B8894}},
}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 highlow=pe.physical_highlow(image,base,sections)
 for address,expected in EXPECTED.items():
  size=expected['body'];body=pe.raw_at(image,base,sections,address,size)
  assert hashlib.sha256(body).hexdigest()==expected['sha'],hex(address)
  instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,address))
  calls={i.address-address+1:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in instructions if i.size==5 and i.bytes[0]==0xE8}
  assert calls==expected['calls'],(hex(address),calls)
  data={site-address:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
        for site in highlow if address<=site<address+size}
  assert data==expected['data'],(hex(address),data)
  if 'compare' in expected:
   complete=pe.raw_at(image,base,sections,address,expected['compare'])
   assert hashlib.sha256(complete).hexdigest()==expected['compare_sha']
   assert complete[size:]==b'\xCC'*5
   assert instructions[-1].mnemonic=='ret'
   print('PASS ScreenInf constructor: 187B/complete 192B, five genuine INT3 alignment bytes, 3 E8 + 4 HIGHLOW')
  elif address==0x00422D40:
   print('PASS ScreenInf allocator: whole 67B, operator new + native zero helper + constructor, 3 E8')
  else:
   print('PASS ScreenInf shutdown: whole 29B, generic virtual release + process allocator, 1 E8 + 1 HIGHLOW')
 print('PASS all three native function extents, immutable SHA-256, physical call targets and data relocation targets')
if __name__=='__main__':verify()
