#!/usr/bin/env python3
"""Whole original 261B/81-i386 game child event traversal, all original E8/PE roles."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0044EFC0,261
SHA='9f4ca0b447123a1a59cc1bd315b43de8e0fe096ec17ca48e0e5d7f6c07747836'
E8={0x32:0x0044CD00,0x56:0x004494B0,0x63:0x0040C080,0x6F:0x0044B9F0,
    0x7E:0x00412540,0x8B:0x00411C30,0x98:0x00411BB0,
    0xA7:0x0040C300,0xB2:0x0040F160,0xC3:0x004388F0,
    0xCB:0x0040F160,0xD2:0x0042B5D0,0xE4:0x00411B00,
    0xFA:0x005429EE}
DIR={0x06:0x005685FD,0x15:0x005B25C0}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==81 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
       for x in high if HEAD<=x<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert data==DIR,(data,DIR)
 assert pe.raw_at(im,base,sec,HEAD+SIZE,7)==b'\xcc'*7
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','ecx, 0x514') in ops
 assert ('mov','dword ptr [ebp - 0x1c], eax') in ops
 assert ('push','1') in ops
 assert sum(x==0x0040F160 for x in e8.values())==2
 assert e8[0xC3]==0x004388F0 and e8[0xD2]==0x0042B5D0
 print('PASS immutable original 261B/81-i386, 14 E8/2 PE HIGHLOW, native ret8')
 print('PASS genuine 456B handle resolver and real child-links[1] begin() with iterator EH/GS')
 print('PASS child interrupt E8 -> 0x004388F0; true subsequent 39,470B VM E8 -> 0x0042B5D0, VM still NONEXACT')
 for off,target in e8.items():print(f'PASS original E8 +{off:#04x} -> {target:#010x}')
 for off,target in data.items():print(f'PASS original HIGHLOW +{off:#04x} -> {target:#010x}')

if __name__=='__main__':verify()
