#!/usr/bin/env python3
"""Immutable-original full 73B equality and 34B byte-comparison wrapper."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
CASES=((0x00447200,73,29,('ret',''),{0x26:0x0044BE00},0x0044B400+0x3F),
       (0x0044BE00,34,16,('ret',''),{0x10:0x00544D77},0x00447200+0x26))

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);high=p.physical_highlow(im,base,sec)
 for head,size,n,ret,expected,parent in CASES:
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,head,size),head))
  assert len(ins)==n and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  e8={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in ins if i.size==5 and i.bytes[0]==0xe8}
  assert e8==expected,(hex(head),e8,expected)
  assert not any(head<=site<head+size for site in high)
  raw=p.raw_at(im,base,sec,parent,5);assert raw[0]==0xe8
  dest=(parent+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert dest==head,(hex(parent),hex(dest))
  print(f'PASS original whole {head:#010x} {size}B/{n}-i386, E8 {expected}, zero PE HIGHLOW')
  print(f'PASS original parent E8 {parent:#010x} -> {head:#010x}')
 assert p.raw_at(im,base,sec,0x0044BE00+34,21)==b'\xcc'*21
 print('PASS real 21 INT3 bytes after original 34B wrapper, not executable function credit')

if __name__=='__main__':verify()
