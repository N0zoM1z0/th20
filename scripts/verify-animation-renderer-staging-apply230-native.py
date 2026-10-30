#!/usr/bin/env python3
"""Immutable 230B/69-i386 Renderer staging draw pass and true physical roles."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x00449FA0,230
E8={0x39:0x0040C080,0x45:0x00412280,0x54:0x00412540,
    0x61:0x00411C30,0x6E:0x00411BB0,0x7D:0x0040C300,
    0x88:0x0040F160,0x9C:0x00443880,0xC7:0x00411B00,
    0xDD:0x005429EE}
DATA={0x06:0x0056838D,0x15:0x005B25C0,
      0x98:0x005C0028,0xA2:0x005C0028,0xB1:0x005C0028}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==69 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={loc-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,loc,4))[0]
       for loc in hl if HEAD<=loc<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert data==DATA,(data,DATA)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','eax, 0x30') in ops
 assert ('add','ecx, 1') in ops and ('mov','dword ptr [edx + 0xd8], ecx') in ops
 assert pe.raw_at(im,base,sec,HEAD+SIZE,6)==b'\xcc'*6
 for off in (0xBC,0x11C):
  site=0x00449E40+off;raw=pe.raw_at(im,base,sec,site,5)
  assert raw[0]==0xe8
  assert (site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff==HEAD
  print(f'PASS original 347B Renderer dispatcher E8 {site:#010x} -> {HEAD:#010x}')
 print('PASS original entire 230B/69-i386, 10 true E8/5 HIGHLOW; 3 native owner global loads')
 print('PASS physical draw E8 +0x9C -> original separate still-NONEXACT 5993B draw at 0x00443880')
 print('PASS native staging list +0x30, owner counter+0xD8 and genuine iterator lifetime')

if __name__=='__main__':verify()
