#!/usr/bin/env python3
"""Original-only native verification of 76B solo ribbon TRIANGLEFAN caller."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045DAE0,76
CALLS={0x19:0x00414580,0x24:0x0040BDA0,0x40:0x0043CB70}
HIGHLOW={0x3C:0x005C0028}
PARENT_CALL=0x0045DA40+0x84

def verify():
 image,_=pe.verified_target();base,secs=pe.parse_sections(image)
 cs=Cs(CS_ARCH_X86,CS_MODE_32);hi=pe.physical_highlow(image,base,secs)
 ins=list(cs.disasm(pe.raw_at(image,base,secs,HEAD,SIZE),HEAD))
 assert len(ins)==27 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,secs,p,4))[0] for p in hi if HEAD<=p<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==HIGHLOW,(data,HIGHLOW)
 assert ('add','eax, 0x1e0') in [(x.mnemonic,x.op_str) for x in ins]
 assert ('push','0x3c') in [(x.mnemonic,x.op_str) for x in ins]
 raw=pe.raw_at(image,base,secs,PARENT_CALL,5);assert raw[0]==0xe8
 dest=(PARENT_CALL+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert dest==HEAD,(hex(PARENT_CALL),hex(dest))
 for o,t in calls.items():print(f'PASS physical E8 +{o:#x} -> {t:#010x}')
 print(f'PASS physical DIR32 +0x3c -> 0x005c0028 and 156B parent E8 {PARENT_CALL:#010x}')
 print('PASS complete native 76B/27-i386, 60-vertex TRIANGLEFAN, color offset +0x1E0')

if __name__=='__main__':verify()
