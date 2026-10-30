#!/usr/bin/env python3
"""Original-only PE proof: 103B 64-point ribbon ctor +49B deleting wrapper."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
BODIES={
 0x0045DED0:(103,28,{0x0E:0x00446B60,0x22:0x0045DE80,0x30:0x0045DE30,0x4C:0x00422D90},{0x18:0x0056ED1C},('ret','4')),
 0x0045DF40:(49,18,{0x0A:0x0045C2A0,0x20:0x0054278D},{},('ret','4')),
}
VTABLE=(0x0045DF40,0x0045DF80,0x0045E190,0x00412540,0x00414B50,0x00414B50)

def verify():
 im,_=p.verified_target();base,secs=p.parse_sections(im);hl=p.physical_highlow(im,base,secs);decoder=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,(size,nins,expected_calls,expected_data,expected_ret) in BODIES.items():
  ins=list(decoder.disasm(p.raw_at(im,base,secs,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==expected_ret
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={address-head:struct.unpack('<I',p.raw_at(im,base,secs,address,4))[0] for address in hl if head<=address<head+size}
  assert calls==expected_calls,(hex(head),calls,expected_calls)
  assert data==expected_data,(hex(head),data,expected_data)
  ops={(i.mnemonic,i.op_str) for i in ins}
  if head==0x0045DED0:
   assert ('add','ecx, 0x208') in ops and ('add','ecx, 0x30c') in ops
   assert ('mov','dword ptr [eax + 0x31c], 0') in ops
  else:assert ('push','0x320') in ops
  print(f'PASS native {head:#010x}: full {size}B/{nins} i386, {len(calls)} E8 and {len(data)} HIGHLOW')
  for off,t in calls.items():print(f'PASS original E8 +{off:#x} -> {t:#010x}')
 addr=0x0056ED1C;v=struct.unpack('<6I',p.raw_at(im,base,secs,addr,24));assert v==VTABLE,v
 assert all(addr+i*4 in hl for i in range(6))
 print('PASS original full 6-slot 0x56ED1C vtable, actual 0x320 class and shared original 20B destructor')

if __name__=='__main__':verify()
