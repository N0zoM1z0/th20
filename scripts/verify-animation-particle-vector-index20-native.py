#!/usr/bin/env python3
"""Independently PE-check the complete 20B 200-Vector3 index and parent E8s."""
from pathlib import Path
import importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
HEAD,SIZE=0x0045C2C0,20
PARENT=0x0045C360
SITES=(0x87F,0x8D2,0xA73,0xA96)

def verify():
 im,_=p.verified_target();base,secs=p.parse_sections(im);hl=p.physical_highlow(im,base,secs)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,secs,HEAD,SIZE),HEAD))
 assert len(ins)==9 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert any((x.mnemonic,x.op_str)==('imul','eax, dword ptr [ebp + 8], 0xc') for x in ins)
 assert not any(HEAD<=off<HEAD+SIZE for off in hl)
 for off in SITES:
  raw=p.raw_at(im,base,secs,PARENT+off,5)
  assert raw[0]==0xE8
  dest=(PARENT+off+5+int.from_bytes(raw[1:5],'little',signed=True))&0xFFFFFFFF
  assert dest==HEAD,(hex(PARENT+off),hex(dest))
  print(f'PASS original 2884B parent E8 {PARENT+off:#010x} -> {HEAD:#010x}')
 print('PASS original 20B/9-i386 index of 12-byte Vector3, complete RET4, no HIGHLOW')

if __name__=='__main__':verify()
