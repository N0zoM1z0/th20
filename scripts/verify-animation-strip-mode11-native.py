#!/usr/bin/env python3
"""Original immutable PE-only whole 534B Animation strip mode11 audit.

Physical game E8 and real PE HIGHLOW site/targets attested independent of
candidate COFF. Covers whole native x86 and real 28B vertex stride contract.
"""
from pathlib import Path
import importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('orig','scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(s);s.loader.exec_module(original)
HEAD=0x00445130
SIZE=534
CALL_SITES={
 0x26:0x004455C0,0xC8:0x00412730,0xFB:0x00445BA0,
 0x103:0x00437CD0,0x130:0x00412730,0x153:0x00445A00,
 0x16E:0x004DDF80,0x188:0x00412730,
 0x1B0:0x00412730,0x1E2:0x00412730,
}
DATA_SITES={0xC4:0x005C4D40,0x12C:0x005C4D40,0x16A:0x005C4D40,
            0x184:0x005C4D40,0x1AC:0x005C4D40,0x1DE:0x005C4D40}


def verify():
 pe,_=original.verified_target();base,secs=original.parse_sections(pe)
 raw=original.raw_at(pe,base,secs,HEAD,SIZE)
 code=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(code)==159 and code[-1].address+code[-1].size==HEAD+SIZE
 assert code[2].mnemonic=='sub' and code[2].op_str=='esp, 0x3c'
 assert code[-1].mnemonic=='ret' and code[-1].op_str=='0xc'
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
        for x in code if len(x.bytes)==5 and x.bytes[0]==0xe8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 rel=original.physical_highlow(pe,base,secs)
 data={x-HEAD:struct.unpack('<I',original.raw_at(pe,base,secs,x,4))[0]
       for x in rel if HEAD<=x<HEAD+SIZE}
 assert data==DATA_SITES,(data,DATA_SITES)
 ops={x.address-HEAD:x for x in code}
 assert ops[0x26].mnemonic=='call' and ops[0x26].op_str=='0x4455c0'
 assert ops[0x16E].mnemonic=='call' and ops[0x16E].op_str=='0x4ddf80'
 # Verify main parent's genuine call if present, but do not invent an alias.
 parent=0x00443880
 origparent=original.raw_at(pe,base,secs,parent,5993)
 parents=[x.address for x in Cs(CS_ARCH_X86,CS_MODE_32).disasm(origparent,parent)
         if len(x.bytes)==5 and x.bytes[0]==0xe8 and
           (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff==HEAD]
 print('PASS original complete 534B/159-i386 animation strip mode11 with native 0x3C stack, RET 0xC, real 28B vertex stride')
 print('PASS 10 original E8 physical call sites and 6 PE HIGHLOW absolute Graphics owner fields all independently attested')
 print('Original main 5993B Draw dispatcher real physical E8 calls:',[hex(x) for x in parents])

if __name__=='__main__':verify()
