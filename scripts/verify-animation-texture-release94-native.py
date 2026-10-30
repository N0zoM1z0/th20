#!/usr/bin/env python3
"""Full 94B original native texture COM Release/buffer retirement roles."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
HEAD,SIZE=0x0044C510,94
PARENT=0x0044AB00+0x56

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==33 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert e8=={0x49:0x0041F670},e8
 data={addr-HEAD:struct.unpack('<I',p.raw_at(im,base,sec,addr,4))[0]
       for addr in hi if HEAD<=addr<HEAD+SIZE}
 assert data=={0x45:0x005B8894},data
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('call','eax') in ops
 assert ('mov','eax, dword ptr [edx + 8]') in ops
 assert ('mov','dword ptr [ecx], 0') in ops
 assert ('mov','dword ptr [eax + 4], 0') in ops
 assert sum(i.mnemonic=='cmp' for i in ins)==3
 raw=p.raw_at(im,base,sec,PARENT,5);assert raw[0]==0xe8
 target=(PARENT+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert target==HEAD,(hex(PARENT),hex(target))
 print('PASS original whole 94B/33-i386 TextureRecord native cleanup and genuine ret4')
 print('PASS original COM vtable+8 Release call and both buffer pointer checks')
 print('PASS original E8 +0x49 -> 0x0041F670 and genuine PE HIGHLOW +0x45 -> 0x005B8894')
 print('PASS original 284B AnimationFile::clear E8 0x0044AB56 -> 0x0044C510')

if __name__=='__main__':verify()
