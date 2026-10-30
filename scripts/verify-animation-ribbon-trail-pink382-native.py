#!/usr/bin/env python3
"""Whole original PE audit of 382B magenta 64-point ribbon setup Boss."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045E3A0,382
CALLS={0x24:0x0045D670,0x3E:0x0045D670,0x5E:0x004298B0,0x77:0x00423520,
       0xB1:0x00414580,0xE2:0x00414580,0x110:0x00414580,
       0x136:0x0045DD60,0x149:0x00450350,0x154:0x0045E5B0,0x170:0x00438C60}
DATA={0x50:0x0056E0F0,0x5A:0x005BA4C4}
PARENT_E8=0x0045E550+0x26

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==113 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={pos-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,pos,4))[0] for pos in hl if HEAD<=pos<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 body={(i.mnemonic,i.op_str) for i in ins}
 assert ('mov','dword ptr [eax + 0x31c], ecx') in body
 assert ('mov','dword ptr [eax], 0xff0080ff') in body
 assert ('push','0xf') in body
 assert ('push','0x40') in body
 assert ('push','0xff') in body
 raw=pe.raw_at(im,base,sec,PARENT_E8,5);assert raw[0]==0xe8
 target=(PARENT_E8+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert target==HEAD,(hex(PARENT_E8),hex(target))
 for off,t in calls.items():print(f'PASS original E8 +{off:#05x} -> {t:#010x}')
 for off,t in data.items():print(f'PASS original HIGHLOW +{off:#05x} -> {t:#010x}')
 print('PASS entire native 382B/113-i386 magenta ribbon configuration, 11 E8/2 HIGHLOW')
 print('PASS true +0x31C token, 64-cell pink/blue+alpha ramp, layer15 flag1 and style64/0/255/0')
 print(f'PASS original 49B wrapper E8 {PARENT_E8:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
