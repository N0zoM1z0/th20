#!/usr/bin/env python3
"""Original-only 202B Vector3 normalization: complete native PE body/roles."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0045CF10,202
E8={0x42:0x00446B30,0x58:0x00445680}
HIGHLOW={0x67:0x0056E1A0}
CALLERS=((0x00472100,0x004D9F60),)

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==58 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={pos-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,pos,4))[0] for pos in hl if HEAD<=pos<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('sub','esp, 8') in ops
 assert ('comiss','xmm0, dword ptr [ebp - 8]') in ops
 assert ('jbe','0x45cf99') in {(i.mnemonic,i.op_str) for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD)}
 assert sum(i.mnemonic=='divss' for i in ins)==3
 value=struct.unpack('<f',pe.raw_at(im,base,sec,0x0056E1A0,4))[0]
 assert abs(value-0.01)<1e-8
 for off,t in E8.items():print(f'PASS original E8 +{off:#x} -> {t:#010x}')
 for off,t in HIGHLOW.items():print(f'PASS original HIGHLOW +{off:#x} -> {t:#010x} (epsilon {value:.8g})')
 print('PASS whole original 202B/58 i386, 3 SSE vector lanes, epsilon copy/normalize branch')

if __name__=='__main__':verify()
