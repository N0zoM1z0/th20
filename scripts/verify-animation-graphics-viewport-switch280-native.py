#!/usr/bin/env python3
"""Original full 280B viewport switching, genuine Direct3D9 and pool-global roles."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0044F720,280
SHA='a1b8abddc5be4d6aa2f0745d27bb8f1752f47c2644eafd364e0154aecbfa4d18'
E8={0x47:0x004DA1F0,0x59:0x004DA120}
HIGHLOW={0xA1:0x005C0028,0xBF:0x005C0028,0xDD:0x005C0028,0x101:0x005C0028}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hi=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==66 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={off-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,off,4))[0]
       for off in hi if HEAD<=off<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('imul','eax, dword ptr [ebp + 8], 0x16c') in ops
 assert ('mov','dword ptr [ebp + 0xc], 0') in ops
 assert ('mov','dword ptr [eax + 0xb00], edx') in ops
 assert ('mov','eax, dword ptr [edx + 0xbc]') in ops
 assert ('call','dword ptr [ebp - 0xc]') in ops
 assert ('movss','dword ptr [eax + 0xd0], xmm0') in ops
 assert ('movss','dword ptr [eax + 0xd4], xmm0') in ops
 assert ('imul','ecx, eax, 0') in ops
 assert ('imul','edx, ecx, 0') in ops
 for rel in (0x18,0xB5,0xFA,0x13F):
  pos=0x0044F3D0+rel;raw=pe.raw_at(im,base,sec,pos,5)
  assert raw[0]==0xe8
  dest=(pos+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert dest==HEAD,(hex(pos),hex(dest))
  print(f'PASS original 806B Graphics category Boss E8 {pos:#010x} -> {HEAD:#010x}')
 print('PASS immutable whole 280B/66-i386, native 0x16C ViewportState stride and Graphics+0xB00 pointer')
 print('PASS original 2 E8 to viewport preparation/update plus four pool-global HIGHLOW')
 print('PASS real Direct3D9 SetViewport virtual vtable+0xBC and exact 4 pool view/pixel values')

if __name__=='__main__':verify()
