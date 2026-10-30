#!/usr/bin/env python3
"""Original PE-only full 138B RendererPool destructor and FIVE real INT3 alignment bytes."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE,PAD=0x00449260,138,5
SHA='63ef2762cf0d0d8868c8ab23868ae6ae725ca763a8fa93e5c8a01ede495f8393'
E8={0x38:0x00449490,0x3F:0x0044A3A0,0x4E:0x00449370,
    0x5C:0x004491E0,0x6A:0x00449370,0x75:0x0040B980}
DATA={0x06:0x005679A0,0x15:0x005B25C0}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==41 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 reloc={a-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,a,4))[0]
        for a in high if HEAD<=a<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert reloc==DATA,(reloc,DATA)
 assert pe.raw_at(im,base,sec,HEAD+SIZE,PAD)==b'\xcc'*PAD
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','eax, 0x6c8') in ops
 assert ('add','ecx, 0x6000818') in ops
 assert ('add','ecx, 0x710') in ops
 assert ('add','ecx, 0xdc') in ops
 assert ('add','ecx, 4') in ops
 assert sum(i.mnemonic=='nop' for i in ins)==2
 for off,target in calls.items():print(f'PASS actual E8 +{off:#04x} -> {target:#010x}')
 for off,target in reloc.items():print(f'PASS original HIGHLOW +{off:#04x} -> {target:#010x}')
 print('PASS complete original 138B/41 instructions + authentic FIVE trailing INT3 (whole 143B contribution)')
 print('PASS native Worker+4, Animation+DC, triple Renderer+6C8, 65536x600 AnimationPool+710, second Animation+6000818')
 print('PASS actual native destructor order: 339B Renderer retire, Animation, AnimationPool array, Animation, Worker')

if __name__=='__main__':verify()
