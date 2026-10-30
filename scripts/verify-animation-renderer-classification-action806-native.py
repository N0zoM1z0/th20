#!/usr/bin/env python3
"""Whole immutable 806B Renderer classification action: every original E8/PE HIGHLOW."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x0044F3D0,806
ORIG_SHA='3163fb22930062a9c9f47de053878fd1a6da02af53ad5c8e393d6350e01f9019'
CALLS={
 0x018:0x0044F720,0x022:0x004DDA60,0x04E:0x0041DCE0,0x058:0x004DDA60,
 0x0B5:0x0044F720,0x0BF:0x004DDA60,0x0FA:0x0044F720,0x104:0x004DDA60,
 0x13F:0x0044F720,0x149:0x004DDA60,0x184:0x0044F700,0x18E:0x004DDF80,
 0x19C:0x004D9DB0,0x1C0:0x0041DCE0,0x1CA:0x004DDF80,0x1D8:0x004D9DB0,
 0x24D:0x0041DCE0,0x257:0x004DDF80,0x265:0x004D9DB0,
 0x2D2:0x0044F700,0x2DC:0x004DDF80,0x2EA:0x004D9DB0,
}
GRAPHICS=(0x014,0x01E,0x04A,0x054,0x0B1,0x0BB,0x0F6,0x100,
          0x13B,0x145,0x180,0x18A,0x198,0x1BC,0x1C6,0x1D4,
          0x249,0x253,0x261,0x2CE,0x2D8,0x2E6)
POOL=(0x1DE,0x1EF,0x26C,0x27D,0x2F1,0x302)
RELOC={**{off:0x005C4D40 for off in GRAPHICS},
       **{off:0x005C0028 for off in POOL}}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 code=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(code).hexdigest()==ORIG_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==211 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 reloc={addr-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,addr,4))[0]
        for addr in high if HEAD<=addr<HEAD+SIZE}
 assert len(e8)==22 and e8==CALLS,(e8,CALLS)
 assert len(reloc)==28 and reloc==RELOC,(reloc,RELOC)
 assert pe.raw_at(im,base,sec,HEAD+SIZE,8)==b'\xcc'*8
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('cmp','dword ptr [ebp + 8], 0x29') in ops
 assert ('cmp','dword ptr [ebp + 8], 0x2b') in ops
 assert ('cmp','dword ptr [ebp + 8], 0x2c') in ops
 assert ('cmp','dword ptr [ebp + 8], 0x35') in ops
 assert ('mov','dword ptr [ecx + 0x6c0], 0') in ops
 assert ('mov','dword ptr [eax + 0x6c0], 0xd') in ops
 assert ('mov','dword ptr [edx + 0x6c0], 9') in ops
 assert ('mov','dword ptr [eax + 0x6c0], 0xa') in ops
 assert sum(i.mnemonic=='xorps' for i in ins)==6
 assert sum(i.mnemonic=='movss' for i in ins)==6
 for rel in (0x9E,0xFD):
  caller=0x00449E40+rel;raw=pe.raw_at(im,base,sec,caller,5)
  assert raw[0]==0xe8
  dest=(caller+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert dest==HEAD,(hex(caller),hex(dest))
  print(f'PASS original 347B dispatcher E8 {caller:#010x} -> {HEAD:#010x}')
 print('PASS original entire 806B/211 i386, original real ret8, eight INT3 following body')
 print('PASS all 22 E8 original physical sites/targets; 28 PE HIGHLOW: 22 Graphics+6 Pool')
 print('PASS all native 0x6C0 state transitions and six xorps/movss float resets at Pool+0xC8/CC')

if __name__=='__main__':verify()
