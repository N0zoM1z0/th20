#!/usr/bin/env python3
"""Whole original 164B/46-i386 secondary Renderer update lock and E8 roles."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x00449A70,164
E8={0x32:0x0040C310,0x3B:0x0040B730,0x65:0x00449490,
    0x6C:0x00449B20,0x83:0x0040B900,0x9B:0x005429EE}
HIGHLOW={0x06:0x0056808D,0x15:0x005B25C0,0x2E:0x005C0240}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(instructions)==46 and instructions[-1].address+instructions[-1].size==HEAD+SIZE
 assert (instructions[-1].mnemonic,instructions[-1].op_str)==('ret','')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in instructions if i.size==5 and i.bytes[0]==0xE8}
 data={addr-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,addr,4))[0]
       for addr in high if HEAD<=addr<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 ops={(i.mnemonic,i.op_str) for i in instructions}
 assert ('push','9') in ops and ('add','ecx, 0x6c8') in ops
 assert any(i.mnemonic=='mov' and '0xd8' in i.op_str for i in instructions)
 assert pe.raw_at(im,base,sec,HEAD+SIZE,7)==b'\xcc'*7
 for offset,target in e8.items():print(f'PASS native E8 +{offset:#04x} -> {target:#010x}')
 for offset,target in data.items():print(f'PASS native PE HIGHLOW +{offset:#04x} -> {target:#010x}')
 print('PASS whole original 164B/46 i386, lock9, pool flag+0xD8 reset and native 511B renderer second-list E8')

if __name__=='__main__':verify()
