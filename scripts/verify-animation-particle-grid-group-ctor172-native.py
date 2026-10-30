#!/usr/bin/env python3
"""Immutable-original PE proof of 172B particle grid ctor and 49B delete."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(sp);sp.loader.exec_module(p)
BODIES={
 0x0045C1F0:(172,46,{0x0E:0x00446B60,0x22:0x0045C190,0x30:0x0045C130,0x3E:0x0045C130,
                    0x54:0x00544760,0x65:0x00422E10,0x73:0x00422E10,0x81:0x00422E10,0x9D:0x00422D90},
             {0x18:0x0056EC14},('ret','4')),
 0x0045C320:(49,18,{0x0A:0x0045C2A0,0x20:0x0054278D},{},('ret','4')),
}
VTABLE=(0x0045C320,0x0045C360,0x00412540,0x0045CEB0,0x0045D060,0x00414B50)
CALLER=0x0045C090+0x6A

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,(size,nins,expected_calls,expected_fields,ret) in BODIES.items():
  ins=list(cs.disasm(p.raw_at(im,base,sec,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  fields={loc-head:struct.unpack('<I',p.raw_at(im,base,sec,loc,4))[0] for loc in hi if head<=loc<head+size}
  assert calls==expected_calls,(hex(head),calls,expected_calls)
  assert fields==expected_fields,(hex(head),fields,expected_fields)
  ops={(i.mnemonic,i.op_str) for i in ins}
  if head==0x0045C1F0:
   assert ('push','0x320') in ops
   assert ('add','ecx, 0x328') in ops and ('add','ecx, 0xc88') in ops
   assert ('add','ecx, 0x1908') in ops and ('add','ecx, 0x1914') in ops and ('add','ecx, 0x1920') in ops
   assert ('nop','') in ops
   assert ('movss','dword ptr [eax + 0x192c], xmm0') in ops
  else:assert ('push','0x1940') in ops
  print(f'PASS original {head:#010x}: {size}B/{nins} i386, {len(calls)} E8, {len(fields)} HIGHLOW')
  for off,t in calls.items():print(f'PASS E8 +{off:#x} -> {t:#010x}')
 vaddr=0x0056EC14;v=struct.unpack('<6I',p.raw_at(im,base,sec,vaddr,24));assert v==VTABLE,(v,VTABLE)
 assert all(vaddr+4*i in hi for i in range(6))
 raw=p.raw_at(im,base,sec,CALLER,5);assert raw[0]==0xe8
 target=(CALLER+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff;assert target==0x0045C1F0
 print(f'PASS real original six-entry 0x56EC14 vtable and factory E8 {CALLER:#010x} to original 172B ctor')
 print('NOTE shared original 20B folded destructor already strict exact, no duplicate code credit')

if __name__=='__main__':verify()
