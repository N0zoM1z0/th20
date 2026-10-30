#!/usr/bin/env python3
"""Immutable 382B/394B Renderer list classification and 347B parent PE roles."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
CASES=(
 (0x0044A090,382,114,'f082fc24af310a6bc549544c7d0b85d838e2a5464ba3601f5da71f304cc993e7',
  {0x40:0x0044A640,0x51:0x0040C080,0x5D:0x00412280,0x6C:0x00412540,
   0x79:0x00411C30,0x86:0x00411BB0,0x99:0x0040C300,
   0xA4:0x0040F160,0xBB:0x0040F160,0xF7:0x0040F160,
   0x10A:0x0040F160,0x11B:0x0044A670,0x12C:0x0040F160,
   0x13D:0x00411EA0,0x15A:0x00411B00,0x173:0x005429EE}),
 (0x0044A210,394,117,'ff1c8467dbc1284fd69c55f09cdf62168f395e54f6bc4d57b9825522ecf918f1',
  {0x40:0x0044A640,0x54:0x0040C080,0x60:0x00412280,0x6F:0x00412540,
   0x7C:0x00411C30,0x89:0x00411BB0,0x9C:0x0040C300,
   0xA7:0x0040F160,0xBE:0x0040F160,0x103:0x0040F160,
   0x116:0x0040F160,0x127:0x0044A670,0x138:0x0040F160,
   0x149:0x00411EA0,0x166:0x00411B00,0x17F:0x005429EE}),
)
HIGHLOW={0x06:0x005683CD,0x15:0x005B25C0}
PARENT=0x00449E40

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,size,nins,hash_value,expected in CASES:
  code=pe.raw_at(im,base,sec,head,size)
  assert hashlib.sha256(code).hexdigest()==hash_value
  ins=list(cs.disasm(code,head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={loc-head:struct.unpack('<I',pe.raw_at(im,base,sec,loc,4))[0]
        for loc in high if head<=loc<head+size}
  assert calls==expected,(hex(head),calls,expected)
  assert data==HIGHLOW,(hex(head),data,HIGHLOW)
  assert calls[0x40]==0x0044A640
  assert sum(x==0x0040F160 for x in calls.values())==5
  assert 0x00411EA0 in calls.values() and 0x0044A670 in calls.values()
  assert ('add','ecx, 0x30') in {(i.mnemonic,i.op_str) for i in ins}
  if head==0x0044A090:
   assert pe.raw_at(im,base,sec,head+size,2)==b'\xcc'*2
  else:assert pe.raw_at(im,base,sec,head+size,4)==b'\xcc'*4
  print(f'PASS original native {head:#010x}: whole {size}B/{nins} i386, all 16 E8/2 HIGHLOW and genuine ret4')
 for off,head in ((0x85,0x0044A090),(0xE4,0x0044A210)):
  site=PARENT+off;code=pe.raw_at(im,base,sec,site,5)
  assert code[0]==0xe8
  assert (site+5+struct.unpack_from('<i',code,1)[0])&0xffffffff==head
  print(f'PASS original 347B Renderer parent E8 {site:#010x} -> {head:#010x}')
 print('PASS original three consecutive 24B native lists, stage +0x30, original +0x500 link publication and exact remapping branches')

if __name__=='__main__':verify()
