#!/usr/bin/env python3
"""Original PE independent audit of three complete generation-counter operations."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
PARENT=0x0044C8F0
CASES=((0x00449570,39,16,('ret','4'),(0x19,0x5F),'add'),
       (0x00449690,26,12,('ret','4'),(0x2C,),'and'),
       (0x004493E0,23,11,('ret','4'),(0x76,),'shl'))

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,n,count,ret,parents,opcode in CASES:
  ins=list(cs.disasm(p.raw_at(im,base,sec,head,n),head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+n
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  assert not any(head<=site<head+n for site in hi)
  assert any(i.mnemonic==opcode for i in ins)
  assert not any(i.mnemonic=='call' for i in ins)
  for off in parents:
   site=PARENT+off;raw=p.raw_at(im,base,sec,site,5);assert raw[0]==0xe8
   target=(site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
   assert target==head,(hex(site),hex(target))
   print(f'PASS original 187B RendererPool register parent E8 {site:#010x} -> {head:#010x}')
  print(f'PASS entire original {head:#010x}: {n}B/{count} x86, native {opcode}, no E8/HIGHLOW')
 print('PASS actual original generation counter postfix old-value +1, &=0xFFFF and high16 shift')

if __name__=='__main__':verify()
