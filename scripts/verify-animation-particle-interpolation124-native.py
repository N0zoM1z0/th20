#!/usr/bin/env python3
"""Locked original 124B/45-i386 VectorInterpolation 6-arg configure source audit."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(sp);sp.loader.exec_module(p)
HEAD,SIZE=0x0045D190,124
CALLS={0x0E:0x00438E70,0x1A:0x004394F0,0x26:0x004393F0,0x32:0x00438A90,
       0x3E:0x00439480,0x4A:0x00438B20,0x70:0x00423520}
PARENT=0x0045D150+0x2D

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hl=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==45 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x18')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls==CALLS,(calls,CALLS)
 assert not any(HEAD<=loc<HEAD+SIZE for loc in hl)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','eax, 0x30') in ops
 assert ('add','ecx, 0x3c') in ops
 assert ('push','0') in ops
 assert ('nop','') in ops
 raw=p.raw_at(im,base,sec,PARENT,5);assert raw[0]==0xe8
 dest=(PARENT+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert dest==HEAD
 for off,t in calls.items():print(f'PASS original E8 +{off:#04x} -> {t:#010x}')
 print('PASS whole 124B/45 x86: six typed setters, current Vector3+0x30, Timer+0x3C, ret24')
 print(f'PASS real 57B animation caller E8 {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
