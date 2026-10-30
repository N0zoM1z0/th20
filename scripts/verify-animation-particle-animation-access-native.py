#!/usr/bin/env python3
"""Original-only full 25B Timer and 19B color access of particle Animation."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
PARENT=0x0045C360
CASES=((0x0045D0A0,25,10,0x91D,{0x10:0x0040FF90},0x4D8),
       (0x0045D0E0,19,9,0x3B3,{},0x490))

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 for head,size,nins,parent_offset,expected,member_offset in CASES:
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
  assert calls==expected,(hex(head),calls,expected)
  assert not any(head<=loc<head+size for loc in hi)
  ops={(i.mnemonic,i.op_str) for i in ins}
  assert any(i.mnemonic=='add' and f'{member_offset:#x}' in i.op_str for i in ins)
  callsite=PARENT+parent_offset;raw=p.raw_at(im,base,sec,callsite,5);assert raw[0]==0xe8
  dest=(callsite+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert dest==head,(hex(callsite),hex(dest),hex(head))
  print(f'PASS native original {head:#010x}: full {size}B/{nins}-i386, Animation+{member_offset:#x}, {len(calls)} true E8, zero HIGHLOW')
  print(f'PASS real 2,884B Update Boss E8 {callsite:#010x} -> {head:#010x}')
 print('PASS Timer+0x4D8 integer getter E8 targets original folded 0x0040FF90')

if __name__=='__main__':verify()
