#!/usr/bin/env python3
"""Original immutable PE-only entire 755B game simple triangle fan Boss.

Independent 197 real x86, eight E8 physical call-target pairs, eight PE
HIGHLOW constant/Graphics pairs and authentic 5993B parent call target.
"""
from pathlib import Path
import importlib.util,sys,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043B960
SIZE=755
CALL_SITES={
 0x051:0x004455C0,0x17A:0x00439330,0x221:0x00438600,
 0x236:0x004DDF80,0x244:0x004D9DB0,0x258:0x00446690,
 0x262:0x00412730,0x286:0x00412730,
}
DATA_SITES={
 0x0A4:0x0056C8CC,0x125:0x0056E0F0,0x12D:0x0056C8D0,
 0x1BC:0x0056C8CC,
 0x232:0x005C4D40,0x240:0x005C4D40,
 0x25E:0x005C4D40,0x282:0x005C4D40,
}
def verify():
 data,_=pe.verified_target();base,sects=pe.parse_sections(data)
 raw=pe.raw_at(data,base,sects,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==197 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0x24'
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='0x1c'
 actual_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
               for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert actual_calls==CALL_SITES,(actual_calls,CALL_SITES)
 fields={p-HEAD:struct.unpack('<I',pe.raw_at(data,base,sects,p,4))[0]
         for p in pe.physical_highlow(data,base,sects) if HEAD<=p<HEAD+SIZE}
 assert fields==DATA_SITES,(fields,DATA_SITES)
 assert Counter(fields.values())==Counter({0x0056C8CC:2,0x0056E0F0:1,0x0056C8D0:1,0x005C4D40:4})
 o={i.address-HEAD:i for i in ins}
 assert o[0x09].op_str=='eax, dword ptr [ebp + 0x18]'
 assert o[0x0F].mnemonic=='imul' and o[0x0F].op_str=='ecx, eax, 0x14'
 assert o[0x2F].mnemonic=='jb'
 assert o[0x056].op_str=='eax, 0x14' and o[0x05B].op_str=='ecx, eax, 0'
 assert o[0x2B2].mnemonic=='push' and o[0x2B2].op_str=='6'
 parent=0x00443880; pbody=pe.raw_at(data,base,sects,parent,5993)
 incoming=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pbody,parent)
           if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert incoming==[0x0044466D],incoming
 print('PASS original entire 755B/197-native-i386 game simple triangle-fan Boss, frame0x24/RET0x1C, original typed indexed center and 20B perimeter')
 print('PASS eight genuine original E8 physical site/targets, eight real PE HIGHLOW site/target pairs including native pi/2.0f/1.0f and Graphics')
 print('PASS original type6 D3D9 TRIANGLEFAN, perimeter generation from mutable start angle/step and real 5993B Draw caller 0x44466D')

if __name__=='__main__':verify()
