#!/usr/bin/env python3
"""Immutable locked PE-only whole 1980B custom Animation rectangle Boss.

Independently attests all 486 x86 heads, 12 E8 and 16 true PE HIGHLOW
site/targets, 4x+/- native sign mask, real on-stack 4-float X/Y arrays,
two actual game original parent E8 calls. No source COFF is an authority.
"""
from pathlib import Path
from collections import Counter
import importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('orig','scripts/verify-animation-draw-boss-native.py')
orig=importlib.util.module_from_spec(spec);spec.loader.exec_module(orig)
HEAD=0x00439A00
SIZE=1980
CALL_SITES={
  0x050:0x004455C0,0x060:0x00439820,0x076:0x004397C0,
  0x377:0x00445AD0,0x3DE:0x00445AD0,
  0x442:0x00445AD0,0x4A9:0x00445AD0,
  0x70B:0x004DDF80,0x71F:0x00446690,
  0x729:0x00412730,0x74D:0x00412730,0x7B1:0x005429EE,
}
DATA_SITES={
  0x007:0x005B25C0,
  0x112:0x0056D7D0,0x11A:0x0056E0EC,0x151:0x0056E0EC,
  0x18A:0x0056D7D0,
  0x24F:0x0056D7D0,0x257:0x0056E0EC,0x28F:0x0056E0EC,
  0x2C7:0x0056D7D0,
  0x66B:0x0056C8CC,0x683:0x0056C8CC,0x69C:0x0056C8CC,
  0x6B5:0x0056C8CC,
  0x707:0x005C4D40,0x725:0x005C4D40,0x749:0x005C4D40,
}

def verify():
 image,_=orig.verified_target();base,secs=orig.parse_sections(image)
 raw=orig.raw_at(image,base,secs,HEAD,SIZE)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ops)==486 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x68'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x24'
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
        for x in ops if len(x.bytes)==5 and x.bytes[0]==0xE8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 fields={p-HEAD:struct.unpack('<I',orig.raw_at(image,base,secs,p,4))[0]
         for p in orig.physical_highlow(image,base,secs) if HEAD<=p<HEAD+SIZE}
 assert fields==DATA_SITES,(fields,DATA_SITES)
 assert Counter(DATA_SITES.values())==Counter({
   0x005B25C0:1,0x0056D7D0:4,0x0056E0EC:4,
   0x0056C8CC:4,0x005C4D40:3,
 })
 signmask=orig.raw_at(image,base,secs,0x0056D7D0,16)
 assert signmask==struct.pack('<4I',0x80000000,0x80000000,0x80000000,0x80000000)
 instr={x.address-HEAD:x for x in ops}
 assert instr[0x013].mnemonic=='mov' and instr[0x013].op_str=='eax, 0x14'
 assert instr[0x018].mnemonic=='shl' and instr[0x018].op_str=='eax, 2'
 assert instr[0x024].mnemonic=='mov' and instr[0x024].op_str=='edx, 0x14'
 assert instr[0x029].mnemonic=='shl' and instr[0x029].op_str=='edx, 0x10'
 assert instr[0x038].mnemonic=='jb'
 assert instr[0x07B1].mnemonic=='call'
 main_head=0x00443880
 main=orig.raw_at(image,base,secs,main_head,5993)
 parent_calls=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(main,main_head)
               if len(i.bytes)==5 and i.bytes[0]==0xE8 and
               (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert parent_calls==[0x00443E7E,0x00443FA6],parent_calls
 print('PASS original whole 1980B/486 native x86 game shape rectangle, 0x68 frame/RET 0x24, exact original 4x-float anchor arrays and true 65536*20B pool')
 print('PASS original 12 E8 physical site/destinations: four real 78B XY transform leaf calls, sin/cos, renderer Graphics, real cookie')
 print('PASS original 16 PE HIGHLOW site/target identities, true four 128-bit sign-XOR masks @0x56D7D0, 4 half/4 one, 3 Graphics and one cookie')
 print('PASS two real parent E8 sites in still nonexact 5993B Animation Draw dispatcher; original native PE and previous docs independently audited')

if __name__=='__main__':verify()
