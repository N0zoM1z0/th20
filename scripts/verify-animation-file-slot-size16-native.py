#!/usr/bin/env python3
"""Actual file-backed 16B 42-entry STL array capacity and real 209B parent E8."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x00450870,16
PARENT=0x0044C430+0x18

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hi=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==8 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert ('mov','eax, 0x2a') in {(i.mnemonic,i.op_str) for i in ins}
 assert not any(HEAD<=site<HEAD+SIZE for site in hi)
 code=pe.raw_at(im,base,sec,PARENT,5)
 assert code[0]==0xe8
 dest=(PARENT+5+struct.unpack_from('<i',code,1)[0])&0xffffffff
 assert dest==HEAD,(hex(PARENT),hex(dest))
 print('PASS original whole 16B/8-i386 native constant size() returns 42, no PE HIGHLOW')
 print(f'PASS native 209B file-slot release E8 {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
