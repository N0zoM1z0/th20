#!/usr/bin/env python3
"""Locked-original complete 47B particle grid creation and 31B timer reset."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(sp);sp.loader.exec_module(p)
BODIES={
 0x0045D000:(47,18,{0x13:0x0045C090,0x26:0x0045CFE0},{0x09:0x0056EC30,0x0F:0x005B8894},('ret','')),
 0x0045CFE0:(31,12,{0x12:0x00423520},{},('ret','8')),
}

def verify():
 im,_=p.verified_target();base,sections=p.parse_sections(im);hl=p.physical_highlow(im,base,sections)
 for head,(size,nins,expected_e8,expected_data,want_ret) in BODIES.items():
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sections,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==want_ret
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={q-head:struct.unpack('<I',p.raw_at(im,base,sections,q,4))[0] for q in hl if head<=q<head+size}
  assert calls==expected_e8,(hex(head),calls,expected_e8)
  assert data==expected_data,(hex(head),data,expected_data)
  ops={(i.mnemonic,i.op_str) for i in ins}
  if head==0x0045CFE0:
   assert ('add','ecx, 0x1930') in ops
   assert ('push','0') in ops
   assert ('xor','eax, eax') in ops
  else:assert ('push','0x56ec30') in ops
  for o,t in calls.items():print(f'PASS original {head:#010x} E8 +{o:#x} -> {t:#010x}')
  for o,t in data.items():print(f'PASS original {head:#010x} HIGHLOW +{o:#x} -> {t:#010x}')
  print(f'PASS complete original {size}B/{nins} i386 head {head:#010x} and true return')
 print('PASS authentic 47B factory/config graph, true 31B timer-reset with two unused stack args')

if __name__=='__main__':verify()
