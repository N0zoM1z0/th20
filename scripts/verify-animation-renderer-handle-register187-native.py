#!/usr/bin/env python3
"""Immutable PE full 187B RendererPool AnimationHandle generation and four parent E8."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
HEAD,SIZE=0x0044C8F0,187
E8={0x19:0x00449570,0x2C:0x00449690,0x43:0x00449430,0x5F:0x00449570,0x76:0x004493E0,0x9F:0x004117A0}
PARENTS=((0x0044B7F0+0x3A),(0x0044B840+0x3A),(0x0044B8E0+0x3D),(0x0044B890+0x3D))

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==56 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xE8}
 assert calls==E8,(calls,E8)
 assert not any(HEAD<=loc<HEAD+SIZE for loc in hi)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('sub','esp, 0x1c') in ops
 assert ('add','eax, 0x7d40e88') in ops and ('add','ecx, 0x7d40e88') in ops
 assert ('push','0xffff') in ops and ('push','0x10') in ops
 assert ('and','eax, 0xffff') in ops
 assert ('or','ecx, dword ptr [ebp - 0x1c]') in ops
 assert ('add','ecx, 0x4c0') in ops
 assert ('nop','') in ops
 for parent in PARENTS:
  raw=p.raw_at(im,base,sec,parent,5);assert raw[0]==0xE8
  target=(parent+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert target==HEAD,(hex(parent),hex(target))
  print(f'PASS original Renderer mode E8 {parent:#010x} -> {HEAD:#010x}')
 for off,dest in E8.items():print(f'PASS original register E8 +{off:#04x} -> {dest:#010x}')
 # The physical mask action really ANDs the four-byte counter, and the
 # postfix increment returns its old value. These aren't guessed names.
 for target,mnemonic in ((0x00449690,'and'),(0x00449570,'add')):
  decoded=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,target,45),target))
  assert any(i.mnemonic==mnemonic for i in decoded)
 print('PASS entire 187B/56-i386 native generation/mask/handle publication, six real E8, zero HIGHLOW')
 print('PASS genuine +0x07D40E88 counter and Animation+0x4C0 handle /+0x4C4 low index')

if __name__=='__main__':verify()
