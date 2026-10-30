#!/usr/bin/env python3
"""Original-only audit for three source-absent 75B std::array<Vector2,N> ctors.

This script is evidence, not a canonical COFF acceptance. Reproducing the
C++20 80B EH-aware body currently requires an isolated noexcept declaration
of globally shared Vector2(), whose ODR/affected-unit reconciliation is open.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
CASES=(
 (0x0045D500,60,0x0045D610+0x0A),
 (0x0045DE80,64,0x0045DED0+0x22),
 (0x0045F260,61,0x0045F3C0+0x0A),
)
E8={0x33:0x0040BC20}
DATA={0x06:0x00567600,0x13:0x005B25C0,0x27:0x004398A0}

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec);dec=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,count,parent_e8 in CASES:
  ins=list(dec.disasm(p.raw_at(im,base,sec,head,75),head))
  assert len(ins)==27 and ins[-1].address+ins[-1].size==head+75
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={pos-head:struct.unpack('<I',p.raw_at(im,base,sec,pos,4))[0] for pos in hi if head<=pos<head+75}
  assert calls==E8,(hex(head),calls,E8)
  assert data==DATA,(hex(head),data,DATA)
  ops={(i.mnemonic,i.op_str) for i in ins}
  assert ('push',f'{count:#x}') in ops
  assert ('push','8') in ops
  assert p.raw_at(im,base,sec,head+75,5)==b'\xcc'*5
  raw=p.raw_at(im,base,sec,parent_e8,5);assert raw[0]==0xe8
  target=(parent_e8+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert target==head,(hex(parent_e8),hex(target),hex(head))
  print(f'PASS original {head:#010x}: 75B/27 x86 Vector2[{count}], 5 INT3, 1 E8+3 HIGHLOW, parent E8 {parent_e8:#010x}')
 print('NOTE all three bodies remain NONEXACT in canonical tracking until global Vector2 noexcept ODR and affected closure are reconciled')

if __name__=='__main__':verify()
