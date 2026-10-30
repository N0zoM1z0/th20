#!/usr/bin/env python3
"""Original-only native 140B solo ribbon group update, 19B end and vtable."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D6F0,140
E8={0x12:0x0045D030,0x27:0x0040BDA0,0x32:0x0045DCE0,0x5C:0x004379C0,0x68:0x0045D780,0x81:0x00423540}
VTABLE=0x0056ECA4
VTABLE_ENTRIES=(0x0045D6B0,HEAD,0x0045DA40,0x00412540,0x00414B50,0x00414B50)
END=0x0045DCE0
END_PARENT_CALLS=(HEAD+0x32,0x0045DA40+0x5A)

def verify():
 im,_=pe.verified_target();base,secs=pe.parse_sections(im);hl=pe.physical_highlow(im,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 body=list(cs.disasm(pe.raw_at(im,base,secs,HEAD,SIZE),HEAD))
 assert len(body)==46 and body[-1].address+body[-1].size==HEAD+SIZE
 assert (body[-1].mnemonic,body[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in body if i.size==5 and i.bytes[0]==0xe8}
 assert calls==E8,(calls,E8)
 assert not any(HEAD<=p<HEAD+SIZE for p in hl)
 code={(i.mnemonic,i.op_str) for i in body}
 assert ('add','ecx, 0x3c0') in code
 assert sum('0x3cc' in x.op_str and x.mnemonic=='add' for x in body)==2
 original_end=list(cs.disasm(pe.raw_at(im,base,secs,END,19),END))
 assert len(original_end)==9 and original_end[-1].address+original_end[-1].size==END+19
 assert (original_end[-1].mnemonic,original_end[-1].op_str)==('ret','')
 assert ('add','eax, 0x3c0') in [(i.mnemonic,i.op_str) for i in original_end]
 assert not any(END<=p<END+19 for p in hl)
 for loc in END_PARENT_CALLS:
  encoded=pe.raw_at(im,base,secs,loc,5);assert encoded[0]==0xe8
  target=(loc+5+struct.unpack_from('<i',encoded,1)[0])&0xffffffff
  assert target==END,(hex(loc),hex(target))
 v=struct.unpack('<6I',pe.raw_at(im,base,secs,VTABLE,24));assert v==VTABLE_ENTRIES
 assert all(VTABLE+4*i in hl for i in range(6))
 for off,dest in E8.items():print(f'PASS original 140B E8 +{off:#x} -> {dest:#010x}')
 print('PASS whole original 140B/46-i386 update, six E8/zero HIGHLOW, Timer+0x3CC')
 print('PASS complete 19B/9-x86 one-segment array end +0x3C0 and two native parents')
 print('PASS real independent 0x56ECA4 six-slot ribbon vtable, update/draw not the three-segment group')

if __name__=='__main__':verify()
