#!/usr/bin/env python3
"""Actual TH20 PE 30B wide-format wrapper and 417B text-Boss E8 audit."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x00447940,30

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hi=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==13 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x14:0x00439880},calls
 assert ('push','0x500') in {(i.mnemonic,i.op_str) for i in ins}
 assert not any(HEAD<=q<HEAD+SIZE for q in hi)
 caller=0x0044AC20+0x69;raw=pe.raw_at(im,base,sec,caller,5);assert raw[0]==0xe8
 dest=(caller+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert dest==HEAD,(hex(caller),hex(dest))
 print(f'PASS native entire 30B/13-i386 wide-format helper: fixed 0x500 count, E8 +0x14 -> 0x00439880')
 print(f'PASS actual 417B Animation text-Boss E8 {caller:#010x} -> {HEAD:#010x}, zero HIGHLOW')

if __name__=='__main__':verify()
