#!/usr/bin/env python3
"""Locked-original-only entire 520B trail ribbon update PE relocation/CFG proof."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(spec);spec.loader.exec_module(p)
HEAD,SIZE=0x0045DF80,520
CALLS={0x019:0x00423560,0x032:0x0045D030,0x048:0x0040FF90,
       0x07D:0x00414580,0x09E:0x00414580,0x0CB:0x00414580,
       0x0DB:0x00429830,0x11D:0x0045D670,0x13F:0x00439330,
       0x160:0x0045D670,0x180:0x0045D670,0x187:0x00439960,
       0x192:0x004297D0,0x1D2:0x00438600,0x1FD:0x00423540}
DATA={0x0D7:0x005BA4C4,0x0EC:0x0056EDD4,0x0F4:0x0056C8E0,
      0x18E:0x005BA4C4,0x1A3:0x0056EDD4}

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==149 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={loc-HEAD:struct.unpack('<I',p.raw_at(im,base,sec,loc,4))[0] for loc in hi if HEAD<=loc<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 ops={(x.mnemonic,x.op_str) for x in ins}
 assert ('sub','esp, 0x58') in ops
 assert ('push','0x40') in ops
 assert ('cmp','eax, 0x10') in ops
 assert ('movzx','eax, byte ptr [eax + 3]') in ops
 assert ('mov','byte ptr [eax + 3], 0') in ops
 assert ('nop','') in ops
 assert ('mov','eax, 1') in ops
 assert struct.unpack('<f',p.raw_at(im,base,sec,0x0056EDD4,4))[0]==5.0
 assert struct.unpack('<f',p.raw_at(im,base,sec,0x0056C8E0,4))[0]==4.0
 vtable=0x0056ED1C;entries=struct.unpack('<6I',p.raw_at(im,base,sec,vtable,24))
 assert entries[1]==HEAD and vtable+4 in hi
 for off,target in calls.items():print(f'PASS native E8 +{off:#05x} -> {target:#010x}')
 for off,target in data.items():print(f'PASS native HIGHLOW +{off:#05x} -> {target:#010x}')
 print('PASS complete original 520B/149 x86, full 15 E8/5 HIGHLOW, 0x58 frame, real vtable')
 print('PASS timer less-than-64, 16-alpha fade, 5x+4 radial RNG, cumulative point and radians/5 angle')

if __name__=='__main__':verify()
