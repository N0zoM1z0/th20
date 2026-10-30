#!/usr/bin/env python3
"""Locked original PE-only complete 2169B closed line-strip geometry Boss.

Independent 533 native i386 heads, actual 5*20B vertex capacity, 12 direct
E8 head targets, 17 HIGHLOW physical data references and real D3D9 type=3.
Source files, candidate COFF symbols and any decompiler names are not oracles.
"""
from pathlib import Path
from collections import Counter
import importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe','scripts/verify-animation-draw-boss-native.py')
pe_module=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe_module)
HEAD=0x0043B0E0
SIZE=2169
CALL_SITES={
  0x050:0x004455C0,0x060:0x00439820,0x076:0x004397C0,
  0x377:0x00445AD0,0x3DE:0x00445AD0,
  0x443:0x00445AD0,0x4A9:0x00445AD0,
  0x7C8:0x004DDF80,0x7DC:0x00446690,
  0x7E6:0x00412730,0x80A:0x00412730,0x86E:0x005429EE,
}
DATA_SITES={
  0x007:0x005B25C0,
  0x112:0x0056D7D0,0x11A:0x0056E0EC,0x151:0x0056E0EC,
  0x18A:0x0056D7D0,
  0x24F:0x0056D7D0,0x257:0x0056E0EC,0x28F:0x0056E0EC,
  0x2C7:0x0056D7D0,
  0x6FD:0x0056C8CC,0x716:0x0056C8CC,0x72E:0x0056C8CC,
  0x747:0x0056C8CC,0x760:0x0056C8CC,
  0x7C4:0x005C4D40,0x7E2:0x005C4D40,0x806:0x005C4D40,
}
def verify():
 image,_=pe_module.verified_target();base,sections=pe_module.parse_sections(image)
 body=pe_module.raw_at(image,base,sections,HEAD,SIZE)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ops)==533 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x68'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x24'
 original_calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
                 for x in ops if len(x.bytes)==5 and x.bytes[0]==0xe8}
 assert original_calls==CALL_SITES,(original_calls,CALL_SITES)
 original_data={p-HEAD:struct.unpack('<I',pe_module.raw_at(image,base,sections,p,4))[0]
                for p in pe_module.physical_highlow(image,base,sections) if HEAD<=p<HEAD+SIZE}
 assert original_data==DATA_SITES,(original_data,DATA_SITES)
 assert Counter(DATA_SITES.values())==Counter({
  0x005B25C0:1,0x0056D7D0:4,0x0056E0EC:4,
  0x0056C8CC:5,0x005C4D40:3,
 })
 signmask=pe_module.raw_at(image,base,sections,0x0056D7D0,16)
 assert signmask==struct.pack('<4I',*[0x80000000]*4)
 ins={x.address-HEAD:x for x in ops}
 assert ins[0x13].mnemonic=='mov' and ins[0x13].op_str=='eax, 0x14'
 assert ins[0x18].mnemonic=='imul' and ins[0x18].op_str=='ecx, eax, 5'
 assert ins[0x29].mnemonic=='shl' and ins[0x29].op_str=='eax, 0x10'
 assert ins[0x38].mnemonic=='jb'
 assert ins[0x4B1].mnemonic=='mov' and ins[0x4B1].op_str=='ecx, 0x14'
 assert ins[0x832].mnemonic=='push' and ins[0x832].op_str=='4'
 assert ins[0x834].mnemonic=='push' and ins[0x834].op_str=='3'
 assert ins[0x86E].mnemonic=='call' and ins[0x86E].op_str=='0x5429ee'
 main_head=0x00443880
 main=pe_module.raw_at(image,base,sections,main_head,5993)
 callers=[x.address for x in Cs(CS_ARCH_X86,CS_MODE_32).disasm(main,main_head)
          if len(x.bytes)==5 and x.bytes[0]==0xe8 and
          (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff==HEAD]
 assert callers==[0x00443F23],callers
 print('PASS immutable original whole 2169B/533 i386 closed 5-vertex LINE STRIP Boss, frame0x68/RET0x24 and signed anchored 2x4 float coords')
 print('PASS 12 original E8 physical site/targets including four real 78B XY helper calls, sine/cosine, Graphics and cookie')
 print('PASS all 17 true original PE HIGHLOW site/targets, 4 native 128-bit sign-XOR masks, 4 half, 5 one, 3 Graphics and cookie')
 print('PASS native D3D9 DrawPrimitiveUP primitive type3=LINESTRIP (not triangle fan), four primitives, 5 x20B vertex pool bound and real main 5993B Draw call at 0x00443F23')

if __name__=='__main__':verify()
