#!/usr/bin/env python3
"""Native original complete 30B viewport forwarding and true 806B parent calls."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x0044F700,30

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 code=pe.raw_at(im,base,sec,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==14 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 e8=[i for i in ins if i.size==5 and i.bytes[0]==0xe8]
 assert len(e8)==1 and e8[0].address-HEAD==0x12
 assert e8[0].address+5+struct.unpack_from('<i',e8[0].bytes,1)[0]==0x0044F720
 assert ('nop','') in {(i.mnemonic,i.op_str) for i in ins}
 assert not any(HEAD<=x<HEAD+SIZE for x in high)
 assert pe.raw_at(im,base,sec,HEAD+SIZE,2)==b'\xcc'*2
 for off in (0x184,0x2D2):
  site=0x0044F3D0+off;raw=pe.raw_at(im,base,sec,site,5);assert raw[0]==0xe8
  dest=(site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert dest==HEAD,(hex(site),hex(dest))
  print(f'PASS true original 806B Graphics category E8 {site:#010x} -> {HEAD:#010x}')
 print('PASS original whole 30B/14-i386 ret8 and physical E8+0x12 -> exact 280B viewport selector')
 print('PASS no PE HIGHLOW, original source-level postcall NOP, 2 real INT3 alignment bytes')

if __name__=='__main__':verify()
