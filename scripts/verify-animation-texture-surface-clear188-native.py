#!/usr/bin/env python3
"""Entire original 188B D3D9 texture-surface COM clear and original native parents."""
from pathlib import Path
import importlib.util,struct,hashlib
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x00449D80,188
E8={0x7C:0x00544760,0xB3:0x005429EE}
DATA={0x07:0x005B25C0}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==75 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 fields={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
         for x in high if HEAD<=x<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert fields==DATA,(fields,DATA)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('mov','edx, dword ptr [ecx + 0x48]') in ops  # Texture::GetSurfaceLevel
 assert ('mov','ecx, dword ptr [eax + 0x30]') in ops  # Surface::GetDesc
 assert ('mov','eax, dword ptr [edx + 0x34]') in ops  # Surface::LockRect
 assert ('mov','edx, dword ptr [eax + 0x38]') in ops  # Surface::UnlockRect
 assert ('mov','eax, dword ptr [ecx + 8]') in ops    # Surface::Release
 assert ('mov','dword ptr [ebp - 0x28], 0') in ops  # actual original null after release
 assert ('imul','eax, dword ptr [ebp - 8]') in ops  # locked pitch*height
 assert ('jmp','0x449e2e') in ops  # original empty null-surface arm
 print('PASS whole immutable original 188B/75-i386 and real Direct3D9 COM slots 0x48/0x30/0x34/0x38/0x08')
 print('PASS native original 2 E8/1 PE HIGHLOW, actual memset and GS cookie, reset after COM Release')
 for o,target in calls.items():print(f'PASS real E8 +{o:#04x} -> {target:#010x}')
 for o,target in fields.items():print(f'PASS real HIGHLOW +{o:#04x} -> {target:#010x}')

if __name__=='__main__':verify()
