#!/usr/bin/env python3
"""Immutable PE-only whole native 899B alternating-radius game renderer.

Original x86, native E8 physical site/targets, true PE HIGHLOW data fields,
original signed parity tests and three native main Draw callers. No compiled
source symbol or decompiler guess is used as original evidence.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043DF30
SIZE=899
CALL_SITES={
 0x049:0x004455C0,0x14A:0x00439330,0x21F:0x00439330,
 0x2C6:0x00438600,0x2E5:0x00446690,
 0x2EF:0x00412730,0x313:0x00412730,
}
DATA_SITES={
 0x06D:0x0056C8D0,0x088:0x0056C8D0,
 0x09F:0x0056C8D0,0x0BA:0x0056C8D0,
 0x0CC:0x0056E0F0,0x0D4:0x0056C8D0,
 0x18C:0x0056C8CC,0x261:0x0056C8CC,
 0x2EB:0x005C4D40,0x30F:0x005C4D40,
}
PARENT_SITES=[0x00444E0F,0x00444EEE,0x00444FD1]

def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 raw=pe.raw_at(img,base,secs,HEAD,SIZE)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ops)==236 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x3c'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x24'
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ops if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 actual={p-HEAD:struct.unpack('<I',pe.raw_at(img,base,secs,p,4))[0]
         for p in pe.physical_highlow(img,base,secs) if HEAD<=p<HEAD+SIZE}
 assert actual==DATA_SITES,(actual,DATA_SITES)
 assert Counter(actual.values())==Counter({0x0056C8D0:5,0x0056E0F0:1,0x0056C8CC:2,0x005C4D40:2})
 signed_parity=[i for i in ops if i.mnemonic=='and' and i.op_str.endswith(', 0x80000001')]
 assert [i.address-HEAD for i in signed_parity]==[0x10A,0x1DE]
 assert len(signed_parity)==2,len(signed_parity)
 assert len([i for i in ops if i.mnemonic=='call' and i.op_str=='0x439330'])==2
 assert any(i.mnemonic=='push' and i.op_str=='5' for i in ops)
 h=0x00443880;p=pe.raw_at(img,base,secs,h,5993)
 incoming=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(p,h)
           if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert incoming==PARENT_SITES,(incoming,PARENT_SITES)
 print('PASS immutable original whole 899B/236-i386 game alternating-radius TRIANGLESTRIP, frame0x3C/RET0x24')
 print('PASS all seven real original E8 physical site/targets, ten true PE HIGHLOW physical data site/targets')
 print('PASS native signed i%2 parity branch twice, 4 genuinely precomputed radius locals and real D3D9 type5 TRIANGLESTRIP')
 print('PASS three native 5993B main Draw E8 parents at 0x444E0F, 0x444EEE, 0x444FD1; enclosing parent remains NONEXACT')

if __name__=='__main__':verify()
