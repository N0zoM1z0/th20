#!/usr/bin/env python3
"""Original-only audit of entire 47B solo ribbon factory+configure cdecl wrapper."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045DC70,47
CALLS={0x13:0x0045D2C0,0x26:0x0045DB30}
HIGHLOW={0x09:0x0056ECC0,0x0F:0x005B8894}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==18 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0] for p in hl if HEAD<=p<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==HIGHLOW,(data,HIGHLOW)
 for o,t in calls.items():print(f'PASS original E8 +{o:#04x} -> {t:#010x}')
 for o,t in data.items():print(f'PASS original HIGHLOW +{o:#04x} -> {t:#010x}')
 print('PASS whole original 47B/18 i386 cdecl, authentic solo ribbon diagnostic allocator and separate 182B configuration')

if __name__=='__main__':verify()
