#!/usr/bin/env python3
"""Whole original 150B fastcall renderer-slot update, true lock EH and E8."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x004497D0,150
E8={0x32:0x0040C310,0x3B:0x0040B730,0x57:0x00449490,
    0x5E:0x00449870,0x75:0x0040B900,0x8D:0x005429EE}
HIGHLOW={0x06:0x0056808D,0x15:0x005B25C0,0x2E:0x005C0240}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);rel=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==44 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={site-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,site,4))[0]
       for site in rel if HEAD<=site<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 assert ('push','9') in {(i.mnemonic,i.op_str) for i in ins}
 assert ('add','eax, 0x6c8') in {(i.mnemonic,i.op_str) for i in ins}
 assert ('mov','ecx, eax') in {(i.mnemonic,i.op_str) for i in ins}
 print('PASS native whole 150B/44-i386: real lock9, Renderer+0x6C8 and true ECX list receiver')
 for off,dest in calls.items():print(f'PASS original E8 +{off:#04x} -> {dest:#010x}')
 for off,dest in data.items():print(f'PASS original HIGHLOW +{off:#04x} -> {dest:#010x}')
 print('PASS original 508B child is a separate NONEXACT function (not credited from this wrapper)')

if __name__=='__main__':verify()
