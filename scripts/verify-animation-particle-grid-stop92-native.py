#!/usr/bin/env python3
"""Original PE proof of complete 92B/32-i386 200-handle stop loop."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(sp);sp.loader.exec_module(p)
HEAD,SIZE=0x0045CEB0,92
E8={0x34:0x00414580,0x3B:0x0044CED0,0x4E:0x0044FD00}
VTABLE=0x0056EC14

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hl=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==32 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls==E8,(calls,E8)
 assert not any(HEAD<=q<HEAD+SIZE for q in hl)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('cmp','dword ptr [ebp - 4], 0xc8') in ops
 assert ('nop','') in ops
 v=struct.unpack('<6I',p.raw_at(im,base,sec,VTABLE,24));assert v[3]==HEAD
 assert VTABLE+12 in hl
 for off,t in calls.items():print(f'PASS native E8 +{off:#04x} -> {t:#010x}')
 print('PASS whole original 92B/32-i386 200-slot handle resolution and conditional Animation::stop')
 print('PASS actual virtual 0x56EC14 table slot index 3, no native in-body HIGHLOW')

if __name__=='__main__':verify()
