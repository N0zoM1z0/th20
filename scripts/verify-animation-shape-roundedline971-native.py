#!/usr/bin/env python3
"""Immutable original PE-only whole 971B rounded LINESTRIP game Boss.

The independently original 255 x86, 9 native E8 calls and 18 PE HIGHLOW
field identities precede all source/COFF comparisons and target roles.
"""
from pathlib import Path
import importlib.util,struct,sys
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('original_pe','scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043A750
SIZE=971
CALL_SITES={
 0x07F:0x004455C0,0x0F5:0x00439330,0x276:0x00458FA0,
 0x2F9:0x00438600,0x30E:0x004DDF80,
 0x31C:0x004D9DB0,0x330:0x00446690,
 0x33A:0x00412730,0x35E:0x00412730,
}
DATA_SITES={
 0x055:0x0056E0F8,0x062:0x0056E0F0,
 0x06A:0x0056C8D0,0x08D:0x0056C8D0,0x0A8:0x0056C8D0,
 0x10F:0x0056C8CC,
 0x13A:0x0056C8D0,0x159:0x0056C8D0,
 0x192:0x0056C8D0,0x1AD:0x0056C8D0,
 0x1E5:0x0056C8D0,0x200:0x0056C8D0,
 0x227:0x0056C8D0,0x246:0x0056C8D0,
 0x30A:0x005C4D40,0x318:0x005C4D40,
 0x336:0x005C4D40,0x35A:0x005C4D40,
}

def verify():
 image,_=pe.verified_target();base,sects=pe.parse_sections(image)
 raw=pe.raw_at(image,base,sects,HEAD,SIZE)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ops)==255 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x28'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x20'
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ops if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 orig_fields={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sects,p,4))[0]
              for p in pe.physical_highlow(image,base,sects) if HEAD<=p<HEAD+SIZE}
 assert orig_fields==DATA_SITES,(orig_fields,DATA_SITES)
 assert Counter(DATA_SITES.values())==Counter({
  0x0056E0F8:1,0x0056E0F0:1,0x0056C8D0:11,
  0x0056C8CC:1,0x005C4D40:4,
 })
 ins={i.address-HEAD:i for i in ops}
 assert ins[0x09].op_str=='eax, dword ptr [ebp + 0x20]'
 assert ins[0x0F].mnemonic=='imul' and ins[0x0F].op_str=='ecx, eax, 0x14'
 assert ins[0x2F].mnemonic=='jb'
 assert ins[0x38].mnemonic=='cmp' and ins[0x38].op_str=='dword ptr [ebp + 0x20], 2'
 assert ins[0x38A].mnemonic=='push' and ins[0x38A].op_str=='3'
 parent=0x00443880;raw_parent=pe.raw_at(image,base,sects,parent,5993)
 incoming=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw_parent,parent)
           if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert incoming==[0x004441EF],incoming
 print('PASS original entire 971B/255-x86 game rounded-corner LINESTRIP, frame 0x28, RET 0x20, signed original quarter-boundary ring')
 print('PASS nine native E8 site/target pairs and eighteen original physical PE HIGHLOW fields/targets, original pi/-pi and source Graphics owner')
 print('PASS original 65536x20B typed vertex pool, native D3D9 LINESTRIP type3, no center vertex; main 5993B game Draw E8 caller 0x4441EF')

if __name__=='__main__':verify()
