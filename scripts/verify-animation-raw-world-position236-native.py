#!/usr/bin/env python3
"""Complete original 236B recursive Animation raw world position native audit."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
HEAD,SIZE=0x0044CB80,236
E8={0x2C:0x00429570,0x44:0x00429570,0x93:0x00437930,0xA4:0x00458FA0,
    0xAF:0x00422E10,0xC7:HEAD,0xD3:0x004296E0,0xE1:0x005429EE}
HIGHLOW={0x07:0x005B25C0}

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==77 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={loc-HEAD:struct.unpack('<I',p.raw_at(im,base,sec,loc,4))[0]
       for loc in hi if HEAD<=loc<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('sub','esp, 0x38') in ops
 assert ('cmp','dword ptr [ecx + 0x558], 0') in ops
 assert ('shr','eax, 0xc') in ops and ('shr','edx, 5') in ops
 assert ('and','eax, 1') in ops and ('and','edx, 1') in ops
 assert ('nop','') in ops
 assert p.raw_at(im,base,sec,HEAD+SIZE,4)==b'\xcc'*4
 for off,target in calls.items():print(f'PASS original E8 +{off:#04x} -> {target:#010x}')
 print('PASS full original 236B/77-i386 world position, parent rotation and recursive E8')
 print('PASS genuine single PE HIGHLOW security cookie +0x07 -> 0x005B25C0 and four INT3')

if __name__=='__main__':verify()
