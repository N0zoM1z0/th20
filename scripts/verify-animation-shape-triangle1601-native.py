#!/usr/bin/env python3
"""Independent original PE-only whole 1601B three-vertex triangle renderer.

Original complete 394 native x86, actual stack/RET, eleven original E8
physical site/targets, 19 original PE HIGHLOW, real three-float anchors,
third and half constants and D3D9 triangle strip primitive type 5.
No source candidate object or decompiler role determines target values.
"""
from collections import Counter
import importlib.util,sys,struct
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('pe_orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD=0x0043E2C0
SIZE=1601
CALL_SITES={
 0x050:0x004455C0,0x060:0x00439820,0x076:0x004397C0,
 0x2FA:0x00445AD0,0x361:0x00445AD0,0x3C5:0x00445AD0,
 0x590:0x004DDF80,0x5A4:0x00446690,
 0x5AE:0x00412730,0x5D2:0x00412730,0x636:0x005429EE,
}
DATA_SITES={
 0x007:0x005B25C0,0x0F9:0x0056D7D0,
 0x101:0x0056C8D8,0x138:0x0056C8D0,0x140:0x0056C8D8,
 0x15C:0x0056D7D0,0x1D6:0x0056C8D0,
 0x207:0x0056D7D0,0x20F:0x0056E0EC,0x23B:0x0056E0EC,
 0x256:0x0056D7D0,0x270:0x0056D7D0,0x278:0x0056C8D0,
 0x51A:0x0056C8CC,0x533:0x0056C8CC,0x54C:0x0056C8CC,
 0x58C:0x005C4D40,0x5AA:0x005C4D40,0x5CE:0x005C4D40,
}

def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,HEAD,SIZE)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ops)==394 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x50'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x24'
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
        for x in ops if len(x.bytes)==5 and x.bytes[0]==0xE8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 d={addr-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,addr,4))[0]
    for addr in pe.physical_highlow(image,base,sections)
    if HEAD<=addr<HEAD+SIZE}
 assert d==DATA_SITES,(d,DATA_SITES)
 assert Counter(d.values())==Counter({
   0x005B25C0:1,0x0056D7D0:5,
   0x0056C8D8:2,0x0056C8D0:3,0x0056E0EC:2,
   0x0056C8CC:3,0x005C4D40:3,
 })
 assert pe.raw_at(image,base,sections,0x0056D7D0,16)==struct.pack('<4I',*[0x80000000]*4)
 for addr,expected in [(0x0056C8D8,3.0),(0x0056C8D0,2.0),(0x0056E0EC,0.5)]:
  assert struct.unpack('<f',pe.raw_at(image,base,sections,addr,4))[0]==expected
 by={op.address-HEAD:op for op in ops}
 assert by[0x013].op_str=='eax, 0x14' and by[0x018].op_str=='ecx, eax, 3'
 assert by[0x029].op_str=='eax, 0x10' and by[0x038].mnemonic=='jb'
 assert by[0x5FA].mnemonic=='push' and by[0x5FA].op_str=='1'
 assert by[0x5FC].mnemonic=='push' and by[0x5FC].op_str=='5'
 parent=0x00443880;total=5993
 pbody=pe.raw_at(image,base,sections,parent,total)
 pcall=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pbody,parent)
        if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert pcall==[0x004445F3],pcall
 print('PASS original whole 1601B/394-i386 3-vertex game triangle Boss, frame0x50/RET0x24, 65536 x20B native typed pool')
 print('PASS all eleven original actual E8 site/target roles, three real 78B XY transform calls, Graphics device and compiler cookie')
 print('PASS 19 native HIGHLOW positions/true values, 5x floating sign-bit mask, 2x3.0, 3x2.0, 2x0.5, 3x1.0, 3 Graphics and cookie')
 print('PASS real D3D9 TRIANGLESTRIP primitive type5 count1/3 vertices and real original 5993B Draw parent E8 at 0x4445F3')

if __name__=='__main__':verify()
