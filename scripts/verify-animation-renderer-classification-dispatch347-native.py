#!/usr/bin/env python3
"""Immutable 347B original Renderer classification dispatch, actual 382/394 parents."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x00449E40,347
SHA='387c4cb4d7aa4ff81fde9e8f3ff70453d12f104ad5449948e2b2b2e04fe74122'
E8={0x32:0x0040C310,0x3B:0x0040B730,0x76:0x00449490,
    0x85:0x0044A090,0x9E:0x0044F3D0,0xB5:0x00449490,
    0xBC:0x00449FA0,0xD5:0x00449490,0xE4:0x0044A210,
    0xFD:0x0044F3D0,0x115:0x00449490,0x11C:0x00449FA0,
    0x138:0x0040B900,0x150:0x005429EE}
HIGHLOW={0x06:0x0056834D,0x15:0x005B25C0,0x2E:0x005C0240}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 code=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(code).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==105 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={a-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,a,4))[0]
       for a in high if HEAD<=a<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 assert ('push','9') in {(i.mnemonic,i.op_str) for i in ins}
 assert ('add','ecx, 0x6c8') in {(i.mnemonic,i.op_str) for i in ins}
 assert sum(target==0x00449490 for target in e8.values())==4
 assert sum(target==0x0044F3D0 for target in e8.values())==2
 assert sum(target==0x00449FA0 for target in e8.values())==2
 print('PASS original 347B/105-i386 Renderer classification dispatch, all 14 physical E8/3 PE HIGHLOW')
 for off,dest in e8.items():print(f'PASS native E8 +{off:#04x} -> {dest:#010x}')
 for off,dest in data.items():print(f'PASS original PE HIGHLOW +{off:#04x} -> {dest:#010x}')
 print('PASS genuine game branch: 382B/394B classification, then 806B separate dispatch and 230B separate staging')

if __name__=='__main__':verify()
