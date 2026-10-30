#!/usr/bin/env python3
"""Original-only complete 339B/106-i386 Renderer primary/secondary list retirement."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0044A3A0,339
SHA='e09b297f6d6283afe82af02d6748e0d95449c3dd9f833d57c9979e2d31b6361a'
E8={0x36:0x0040C080,0x42:0x00412280,0x51:0x00412540,0x5E:0x00411C30,
    0x6B:0x00411BB0,0x7A:0x0040C300,0x85:0x0040F160,0x99:0x0044C2F0,
    0xAB:0x00411B00,0xBF:0x0040C080,0xCB:0x00412280,0xDA:0x00412540,
    0xE7:0x00411C30,0xF4:0x00411BB0,0x103:0x0040C300,0x10E:0x0040F160,
    0x122:0x0044C2F0,0x134:0x00411B00,0x14A:0x005429EE}
DIR={0x06:0x00568415,0x15:0x005B25C0,0x95:0x005C0028,0x11E:0x005C0028}

def verify():
 im,_=pe.verified_target();base,secs=pe.parse_sections(im);high=pe.physical_highlow(im,base,secs)
 raw=pe.raw_at(im,base,secs,HEAD,SIZE)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==106 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 dirs={loc-HEAD:struct.unpack('<I',pe.raw_at(im,base,secs,loc,4))[0]
       for loc in high if HEAD<=loc<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert dirs==DIR,(dirs,DIR)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','eax, 0x18') in ops
 assert sum(x==0x0044C2F0 for x in e8.values())==2
 assert sum(i.mnemonic=='nop' for i in ins)==6
 assert pe.raw_at(im,base,secs,HEAD+SIZE,5)==b'\xcc'*5
 print('PASS original whole 339B/106-i386 Renderer primary+secondary list staged release')
 print('PASS genuine 19 E8/4 HIGHLOW roles, 2 original native pool globals and 2 whole-exact 308B calls')
 for off,dest in e8.items():print(f'PASS original E8 +{off:#04x} -> {dest:#010x}')
 for off,dest in dirs.items():print(f'PASS original HIGHLOW +{off:#04x} -> {dest:#010x}')

if __name__=='__main__':verify()
