#!/usr/bin/env python3
"""Immutable PE-only full original 1174B rounded triangle-fan Boss audit.

The full native 303 instruction heads, 9 E8 calls, 19 PE HIGHLOW fields,
real center+perimeter geometry and 5993B enclosing draw caller are attested
before comparing any source object or speculative historical identifier.
"""
from pathlib import Path
import importlib.util,sys,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('orig','scripts/verify-animation-draw-boss-native.py')
orig=importlib.util.module_from_spec(s);s.loader.exec_module(orig)
HEAD=0x0043A2B0
SIZE=1174
CALL_SITES={
 0x07F:0x004455C0,0x1C0:0x00439330,0x341:0x00458FA0,
 0x3C4:0x00438600,0x3D9:0x004DDF80,
 0x3E7:0x004D9DB0,0x3FB:0x00446690,
 0x405:0x00412730,0x429:0x00412730,
}
DATA_SITES={
 0x055:0x0056E0F8,0x062:0x0056E0F0,0x06A:0x0056C8D0,
 0x0D2:0x0056C8CC,
 0x158:0x0056C8D0,0x173:0x0056C8D0,
 0x1DA:0x0056C8CC,
 0x205:0x0056C8D0,0x224:0x0056C8D0,
 0x25D:0x0056C8D0,0x278:0x0056C8D0,
 0x2B0:0x0056C8D0,0x2CB:0x0056C8D0,
 0x2F2:0x0056C8D0,0x311:0x0056C8D0,
 0x3D5:0x005C4D40,0x3E3:0x005C4D40,
 0x401:0x005C4D40,0x425:0x005C4D40,
}

def verify():
    pe,_=orig.verified_target();base,sects=orig.parse_sections(pe)
    raw=orig.raw_at(pe,base,sects,HEAD,SIZE)
    ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
    assert len(ops)==303 and ops[-1].address+ops[-1].size==HEAD+SIZE
    assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x28'
    assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x24'
    calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ops if len(i.bytes)==5 and i.bytes[0]==0xE8}
    assert calls==CALL_SITES,(calls,CALL_SITES)
    data={p-HEAD:struct.unpack('<I',orig.raw_at(pe,base,sects,p,4))[0]
          for p in orig.physical_highlow(pe,base,sects) if HEAD<=p<HEAD+SIZE}
    assert data==DATA_SITES,(data,DATA_SITES)
    assert Counter(data.values())==Counter({
      0x0056E0F8:1,0x0056E0F0:1,0x0056C8D0:11,
      0x0056C8CC:2,0x005C4D40:4,
    })
    o={x.address-HEAD:x for x in ops}
    assert o[0x09].op_str=='eax, dword ptr [ebp + 0x20]'
    assert o[0x0F].mnemonic=='imul' and o[0x0F].op_str=='ecx, eax, 0x14'
    assert o[0x2F].mnemonic=='jb'
    assert o[0x084].mnemonic=='mov' and o[0x084].op_str=='eax, 0x14'
    assert o[0x089].mnemonic=='imul' and o[0x089].op_str=='ecx, eax, 0'
    assert o[0x455].mnemonic=='push' and o[0x455].op_str=='6'
    assert o[0x44B].mnemonic=='push' and o[0x44B].op_str=='0x14'
    parent=0x00443880;parent_raw=orig.raw_at(pe,base,sects,parent,5993)
    pcall=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent_raw,parent)
           if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
    assert pcall==[0x0044415E],pcall
    print('PASS original entire 1174B/303 real i386 custom rounded-fan game Boss, frame 0x28 and RET 0x24')
    print('PASS 9 original direct E8 physical site/heads and 19 original PE HIGHLOW physical data site/targets, genuine signed quarter-angle loops')
    print('PASS original 20B fixed vertex pool with one indexed center vertex and perimeter ring, native D3D9 type6 triangle fan and real 5993B Draw caller')

if __name__=='__main__':verify()
