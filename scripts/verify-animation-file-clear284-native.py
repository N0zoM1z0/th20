#!/usr/bin/env python3
"""Original-only whole 284B AnimationFile::clear() 8 E8/8 HIGHLOW audit."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0044AB00,284
E8={0x22:0x0044FD30,0x56:0x0044C510,0x6B:0x0040D840,0x87:0x0040D840,
    0xA3:0x0040D840,0xC8:0x0041F670,0xED:0x0041F670,0x109:0x004472C0}
HIGHLOW={0x1E:0x005C0028,0x52:0x005C0028,0x67:0x005B8894,0x83:0x005B8894,
         0x9F:0x005B8894,0xC4:0x005B8894,0xE9:0x005B8894,0x105:0x005B8894}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==81 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
     for i in ins if i.bytes[0]==0xe8 and i.size==5}
 dirs={q-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,q,4))[0]
       for q in high if HEAD<=q<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert dirs==HIGHLOW,(dirs,HIGHLOW)
 code={(i.mnemonic,i.op_str) for i in ins}
 assert ('cmp','dword ptr [eax + 0x3c], 0') in code
 assert ('cmp','ecx, dword ptr [eax + 0x44]') in code
 assert ('imul','edx, dword ptr [ebp - 8], 0x18') in code
 assert pe.raw_at(im,base,sec,HEAD+SIZE,4)==b'\xcc'*4
 for caller,length in [(0x00449310,85),(0x0044C430,209)]:
  hits=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,caller,length),caller)
        if i.bytes[0]==0xe8 and i.size==5 and int(i.op_str,16)==HEAD]
  assert len(hits)==1,(hex(caller),hits)
  print(f'PASS original native caller {hits[0]:#010x} -> {HEAD:#010x}')
 print('PASS original whole 284B/81-i386, 8 genuine E8 and 8 PE HIGHLOW roles')
 print('PASS actual texture stride 0x18/count +0x44 and actual pool/allocator release family')
 print('PASS four original INT3 alignment bytes beyond function boundary')

if __name__=='__main__':verify()
