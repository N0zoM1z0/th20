#!/usr/bin/env python3
"""Whole original 691B Renderer File detachment and real iterator/PE roles."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0044FD30,691
BODY_SHA256='0b30f104f40e2e7790066ef155a9f1a6fc66ff907fc3e702c91d1ec587591d11'
ROLES=[
 (0x65,0x00449490),(0x72,0x0040C080),(0x7E,0x00412280),
 (0x8D,0x00412540),(0x9A,0x00411C30),(0xA7,0x00411BB0),
 (0xBA,0x0040C300),(0xC5,0x0040F160),(0xE1,0x0040F160),
 (0xFD,0x0040F160),(0x113,0x0040F160),(0x12F,0x0040F160),
 (0x14B,0x0040F160),(0x16B,0x00411B00),
 (0x184,0x00449490),(0x194,0x0040C080),(0x1A0,0x00412280),
 (0x1AF,0x00412540),(0x1BC,0x00411C30),(0x1C9,0x00411BB0),
 (0x1DC,0x0040C300),(0x1E7,0x0040F160),(0x203,0x0040F160),
 (0x21F,0x0040F160),(0x235,0x0040F160),(0x251,0x0040F160),
 (0x26D,0x0040F160),(0x28D,0x00411B00),(0x2A8,0x005429EE),
]
DATA={0x06:0x005686C5,0x15:0x005B25C0}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 raw=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(raw).hexdigest()==BODY_SHA256
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==205 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls=[(i.address-HEAD,(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff)
         for i in ins if i.size==5 and i.bytes[0]==0xe8]
 assert calls==ROLES,(calls,ROLES)
 data={q-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,q,4))[0]
       for q in high if HEAD<=q<HEAD+SIZE}
 assert data==DATA,(data,DATA)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','ecx, 0x6c8') in ops
 assert ('add','eax, 0x18') in ops
 assert ('mov','dword ptr [ecx + 0x570], 1') in ops
 assert ('movzx','eax, byte ptr [ebp + 0xc]') in ops
 assert sum(i.mnemonic=='nop' for i in ins)==4
 # An original game-owned parent actually calls this entire Boss.
 caller=0x0044AB00+0x22;five=pe.raw_at(im,base,sec,caller,5)
 assert five[0]==0xe8
 assert (caller+5+struct.unpack_from('<i',five,1)[0])&0xffffffff==HEAD
 print('PASS original whole 691B/205-i386, all 29 genuine E8 site/destination pairs')
 print('PASS two actual physical HIGHLOW: EH handler +0x06, cookie +0x15')
 print('PASS two original intrusive Animation lists and 72-byte Render slot, native mark field +0x570')
 print(f'PASS original AnimationFile::clear E8 {caller:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
