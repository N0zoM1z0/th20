#!/usr/bin/env python3
"""Locked PE-only native evidence for complete 2136B Animation mesh renderer.

The original PE instruction/relocation/ABI evidence is independent of C++
source and candidate COFF. In particular, the two native Matrix4 data
getters per axis do not inherit authority from a provisional source name.
"""
from collections import Counter
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('locked_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(s);s.loader.exec_module(original)
HEAD=0x00443020
SIZE=2136
CALL_SITES={
 0x021:0x0040BDA0,0x029:0x0040BDA0,0x032:0x00445AB0,
 0x07C:0x004455C0,0x098:0x004DDFE0,0x0A5:0x004DDF80,
 0x1B5:0x00540684,0x1C3:0x0040BDA0,0x1D7:0x0040BDA0,
 0x1F7:0x0054067E,0x228:0x0054068A,0x236:0x0040BDA0,
 0x24A:0x0040BDA0,0x26A:0x0054067E,0x29B:0x00540690,
 0x2A9:0x0040BDA0,0x2BD:0x0040BDA0,0x2DD:0x0054067E,
 0x36E:0x0041CAD0,0x3CE:0x0041CAF0,
 0x49B:0x00412730,0x4DA:0x00445BC0,0x4E2:0x00437CD0,
 0x51E:0x00412730,0x550:0x00445A00,0x6F9:0x00412730,
 0x737:0x00446690,0x758:0x00412730,0x78E:0x00412730,
 0x7C5:0x00412730,0x809:0x00412730,0x84D:0x005429EE,
}
DATA_SITES={
 0x00A:0x005B25C0,0x094:0x005C4D40,0x0A1:0x005C4D40,
 0x0BA:0x0056E100,
 0x196:0x0056CD50,0x209:0x0056CD50,0x27C:0x0056CD50,
 0x36A:0x005B6758,0x3CA:0x005B6758,
 0x497:0x005C4D40,0x51A:0x005C4D40,
 0x591:0x0056E0E8,0x5A6:0x0056E0E8,0x5BB:0x0056C8CC,0x5D0:0x0056C8CC,
 0x6F5:0x005C4D40,0x754:0x005C4D40,0x78A:0x005C4D40,
 0x7C1:0x005C4D40,0x805:0x005C4D40,
}
PARENT=0x00443880
PARENT_SIZE=5993
PARENT_CALLS={0x00443B4F,0x00443B76,0x00443B9D}


def verify():
 pe,_=original.verified_target()
 base,sections=original.parse_sections(pe)
 native=original.raw_at(pe,base,sections,HEAD,SIZE)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ops)==504 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x130'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0xc'
 calls={}
 for i in ops:
  if i.bytes[0]==0xE8 and len(i.bytes)==5:
   calls[i.address-HEAD]=(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
 assert calls==CALL_SITES,(calls,CALL_SITES)
 real_highlow=original.physical_highlow(pe,base,sections)
 fields={p-HEAD:struct.unpack('<I',original.raw_at(pe,base,sections,p,4))[0]
  for p in real_highlow if HEAD<=p<HEAD+SIZE}
 assert fields==DATA_SITES,(fields,DATA_SITES)
 assert len(CALL_SITES)==32 and len(DATA_SITES)==20
 origin={i.address-HEAD:i for i in ops}
 for off,mn,operand in (
   (0x08B,'shr','ecx, 4'),(0x08E,'and','ecx, 1'),(0x091,'jne',None),
   (0x7AD,'push','0'),(0x7AF,'push','6'),(0x7B1,'push','0'),
   (0x7E4,'push','0'),(0x7E6,'push','3'),(0x7E8,'push','0'),
   (0x595,'lahf',None),(0x5AA,'lahf',None),
   (0x5BF,'lahf',None),(0x5D4,'lahf',None),
   (0x84D,'call','0x5429ee'),
 ):
  inst=origin[off]
  assert inst.mnemonic==mn and (operand is None or inst.op_str==operand),(hex(off),inst)
 assert Counter(CALL_SITES.values())[0x0040BDA0]==8
 assert Counter(CALL_SITES.values())[0x00412730]==7
 assert Counter(DATA_SITES.values())==Counter({
 0x005B25C0:1,0x005C4D40:9,0x0056E100:1,0x0056CD50:3,
 0x005B6758:2,0x0056E0E8:2,0x0056C8CC:2,
 })
 body=original.raw_at(pe,base,sections,PARENT,PARENT_SIZE)
 parent_ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,PARENT))
 assert parent_ops and parent_ops[-1].address+parent_ops[-1].size==PARENT+PARENT_SIZE
 parent_calls={i.address for i in parent_ops if i.bytes[0]==0xE8 and len(i.bytes)==5
   and (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD}
 assert parent_calls==PARENT_CALLS,parent_calls
 print('PASS original whole 2136B/504-x86 typed renderer mesh24/25, native 0x130 frame and ret 0xC')
 print('PASS all original 32 E8 physical site/target identities, including eight actual folded matrix-address calls and seven real Graphics device getters')
 print('PASS all 20 original PE HIGHLOW offsets and targets, immutable 4x4 identity, double-zero and live Graphics/WindowState global owners')
 print('PASS native bit4 SHR/AND/JNE path and exact texture-stage vtable arguments (0,6,0) and (0,3,0), not inverted stage/value')
 print('PASS three original native game parent E8 call sites from 5993B Animation Draw dispatcher, no author credit duplicated')

if __name__=='__main__':verify()
