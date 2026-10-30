#!/usr/bin/env python3
"""Immutable original 92B/30-i386 Renderer locked RandomState next/byte read."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x00449D20,92
E8={0x1A:0x0040C310,0x23:0x0040B730,0x2E:0x004235F0,
    0x45:0x0040B900,0x53:0x005429EE}
DATA={0x07:0x005B25C0,0x16:0x005C0240}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==30 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={loc-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,loc,4))[0]
       for loc in high if HEAD<=loc<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert data==DATA,(data,DATA)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('push','0xa') in ops
 assert ('add','ecx, 4') in ops
 assert ('mov','dword ptr [ecx + 0x14], eax') in ops
 assert ('movzx','eax, byte ptr [ebp - 9]') in ops
 assert not any(i.mnemonic=='push' and i.op_str=='-1' for i in ins)
 for off,dest in e8.items():print(f'PASS original E8 +{off:#04x} -> {dest:#010x}')
 for off,dest in data.items():print(f'PASS native PE HIGHLOW +{off:#04x} -> {dest:#010x}')
 print('PASS entire 92B/30-i386, lock slot 10, no EH handler, real RandomState::next() folded library callee')
 print('PASS native 0x04 RNG state, +0x14 last word and byte-return, genuine /GS cookie')

if __name__=='__main__':verify()
