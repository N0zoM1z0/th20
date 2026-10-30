#!/usr/bin/env python3
"""Independent original PE proof of solo ribbon 89B constructor/49B deleting wrapper."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
BODIES={
 0x0045D5B0:(89,25,{0x0E:0x00446B60,0x22:0x0045D550,0x3E:0x00422D90},{0x18:0x0056ECA4},('ret','4')),
 0x0045D6B0:(49,18,{0x0A:0x0045C2A0,0x20:0x0054278D},{},('ret','4')),
}
VTABLE=0x0056ECA4
VTABLE_ENTRIES=(0x0045D6B0,0x0045D6F0,0x0045DA40,0x00412540,0x00414B50,0x00414B50)

def verify():
 image,_=pe.verified_target();base,secs=pe.parse_sections(image);hi=pe.physical_highlow(image,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,(size,nins,want_calls,want_data,want_ret) in BODIES.items():
  ins=list(cs.disasm(pe.raw_at(image,base,secs,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==want_ret
  calls={i.address-head:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={p-head:struct.unpack('<I',pe.raw_at(image,base,secs,p,4))[0] for p in hi if head<=p<head+size}
  assert calls==want_calls,(hex(head),calls,want_calls)
  assert data==want_data,(hex(head),data,want_data)
  body={(i.mnemonic,i.op_str) for i in ins}
  if head==0x0045D5B0:
   assert ('movss','dword ptr [edx + 0x3c8], xmm0') in body
   assert ('add','ecx, 0x3cc') in body
   assert ('mov','dword ptr [eax + 0x3dc], 0') in body
  else:
   assert ('push','0x3e0') in body
  print(f'PASS original {head:#010x}: entire {size}B/{nins} x86, {len(calls)} E8, {len(data)} HIGHLOW')
  for o,t in calls.items():print(f'PASS native E8 +{o:#04x} -> {t:#010x}')
 v=struct.unpack('<6I',pe.raw_at(image,base,secs,VTABLE,24));assert v==VTABLE_ENTRIES,(v,VTABLE_ENTRIES)
 assert all(VTABLE+i*4 in hi for i in range(6))
 shared=list(cs.disasm(pe.raw_at(image,base,secs,0x0045C2A0,20),0x0045C2A0))
 assert len(shared)==10 and shared[-1].address+shared[-1].size==0x0045C2B4
 print('PASS original 0x56ECA4 six-slot vtable, real 0x3E0 object and folded shared 20B destructor')
 print('NOTE 20B destructor physical head already credited by prior strict unit, no duplicate unit')

if __name__=='__main__':verify()
