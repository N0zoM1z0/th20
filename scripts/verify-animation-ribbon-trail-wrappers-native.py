#!/usr/bin/env python3
"""Original-only full 47B/49B 64-point ribbon trail creation wrappers."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
BODIES={
 0x0045E520:(47,18,{0x13:0x0045DD90,0x26:0x0045E240},{0x09:0x0056ED88,0x0F:0x005B8894},False),
 0x0045E550:(49,19,{0x13:0x0045DD90,0x26:0x0045E3A0},{0x09:0x0056ED38,0x0F:0x005B8894},True),
}

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hl=p.physical_highlow(im,base,sec)
 for head,(size,nins,expected_calls,expected_data,returns_zero) in BODIES.items():
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={loc-head:struct.unpack('<I',p.raw_at(im,base,sec,loc,4))[0] for loc in hl if head<=loc<head+size}
  assert calls==expected_calls,(hex(head),calls,expected_calls)
  assert data==expected_data,(hex(head),data,expected_data)
  ops={(i.mnemonic,i.op_str) for i in ins}
  assert (('xor','eax, eax') in ops)==returns_zero
  for off,t in calls.items():print(f'PASS original {head:#010x} E8 +{off:#x} -> {t:#010x}')
  for off,t in data.items():print(f'PASS original {head:#010x} HIGHLOW +{off:#x} -> {t:#010x}')
  print(f'PASS original {head:#010x}: whole {size}B/{nins} i386, factory and genuine configuration')
 print('PASS gray wrapper returns gray configuration result; pink wrapper explicitly returns 0')

if __name__=='__main__':verify()
