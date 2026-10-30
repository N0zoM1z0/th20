#!/usr/bin/env python3
"""Immutable-original PE proof of 77B stem comparison and 17B forwarding."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
CASES=((0x0044B400,77,29,('ret','4'),{0x0D:0x00411180,0x27:0x0040F2C0,0x3F:0x00447200}),
       (0x00446DE0,17,8,('ret',''),{0x0A:0x0044B400}))

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);high=p.physical_highlow(im,base,sec)
 for head,size,n,ret,expected in CASES:
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,head,size),head))
  assert len(ins)==n and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
  assert calls==expected,(hex(head),calls,expected)
  assert not any(head<=loc<head+size for loc in high)
  for off,target in calls.items():print(f'PASS original {head:#010x} E8 +{off:#x} -> {target:#010x}')
  print(f'PASS whole {size}B/{n} i386 at {head:#010x}, genuine return, zero HIGHLOW')
 site=0x00450CB0+0x83;raw=p.raw_at(im,base,sec,site,5)
 assert raw[0]==0xe8
 dest=(site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert dest==0x00446DE0
 print(f'PASS original 922B AnimationFile::spawn Boss E8 {site:#010x} -> 0x00446DE0')

if __name__=='__main__':verify()
