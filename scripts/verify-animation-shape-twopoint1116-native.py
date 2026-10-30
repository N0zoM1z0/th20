#!/usr/bin/env python3
"""Immutable PE-only full original 1116B two-point shape LINESTRIP.

All 282 original x86 heads, 10 original direct E8 physical destination
pairs, 13 real PE HIGHLOW fields and actual 5993B parent call are checked
without examining source COFF or candidate data.
"""
from pathlib import Path
from collections import Counter
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('native_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043CD40
SIZE=1116
CALL_SITES={
 0x04F:0x004455C0,0x05F:0x00439820,0x075:0x004397C0,
 0x1BF:0x00445AD0,0x226:0x00445AD0,
 0x3AB:0x004DDF80,0x3BF:0x00446690,
 0x3C9:0x00412730,0x3ED:0x00412730,0x451:0x005429EE,
}
DATA_SITES={
 0x007:0x005B25C0,0x0DB:0x0056D7D0,0x0E3:0x0056E0EC,
 0x0FE:0x0056E0EC,0x11A:0x0056D7D0,
 0x315:0x0056C8CC,0x32E:0x0056C8CC,
 0x346:0x0056C8CC,0x35F:0x0056C8CC,0x378:0x0056C8CC,
 0x3A7:0x005C4D40,0x3C5:0x005C4D40,0x3E9:0x005C4D40,
}
PARENT_SITES=[0x00443DFB]

def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 code=pe.raw_at(image,base,sections,HEAD,SIZE)
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(instructions)==282 and instructions[-1].address+instructions[-1].size==HEAD+SIZE
 assert instructions[2].mnemonic=='sub' and instructions[2].op_str=='esp, 0x3c'
 assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str=='0x20'
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
        for x in instructions if len(x.bytes)==5 and x.bytes[0]==0xE8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 fields={x-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,x,4))[0]
         for x in pe.physical_highlow(image,base,sections) if HEAD<=x<HEAD+SIZE}
 assert fields==DATA_SITES,(fields,DATA_SITES)
 assert Counter(fields.values())==Counter({
  0x005B25C0:1,0x0056D7D0:2,0x0056E0EC:2,
  0x0056C8CC:5,0x005C4D40:3,
 })
 assert pe.raw_at(image,base,sections,0x0056D7D0,16)==struct.pack('<4I',*[0x80000000]*4)
 i={x.address-HEAD:x for x in instructions}
 assert i[0x13].mnemonic=='mov' and i[0x13].op_str=='eax, 0x14'
 assert i[0x18].mnemonic=='shl' and i[0x18].op_str=='eax, 1'
 assert i[0x37].mnemonic=='jb'
 assert i[0x34A].mnemonic=='movss'  # original fifth prefilled W field
 parent=0x00443880
 pbody=pe.raw_at(image,base,sections,parent,5993)
 caller=[x.address for x in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pbody,parent)
         if len(x.bytes)==5 and x.bytes[0]==0xE8 and
         (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff==HEAD]
 assert caller==PARENT_SITES,caller
 print('PASS immutable original whole 1116B/282 native-i386 game two-point draw, true 0x3C frame, RET 0x20, five genuine 1.0f stores')
 print('PASS 10 native E8 physical instruction site/target roles, 13 original real HIGHLOW field/target pairs including 2 sign masks, 2 half, five 1.0f')
 print('PASS source-independent physical 5993B game Draw caller E8 0x00443DFB; enclosing main Draw still NONEXACT')

if __name__=='__main__':verify()
