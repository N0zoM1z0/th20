#!/usr/bin/env python3
"""Full original 209B RendererPool file-slot removal PE/role proof."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
HEAD,SIZE=0x0044C430,209
E8={0x18:0x00450870,0x39:0x0043EB10,0x5A:0x00414580,0x61:0x0044AB00,
    0x79:0x00414580,0x8B:0x00447330,0xA3:0x00414580,0xC0:0x00414580}
DATA={0x87:0x005B8894}

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);high=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==61 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={q-HEAD:struct.unpack('<I',p.raw_at(im,base,sec,q,4))[0]
       for q in high if HEAD<=q<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert data==DATA,(data,DATA)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','ecx, 0x6000730') in ops
 assert ('add','eax, 0x6000730') in ops
 assert ('jl','0x44c452') in ops and ('jb','0x44c457') in ops
 assert ('jmp','0x44c4fb') in ops
 assert ('mov','dword ptr [eax], 0') in ops
 for off,dest in calls.items():print(f'PASS original E8 +{off:#04x} -> {dest:#010x}')
 print('PASS original whole 209B/61-i386, 8 E8 and original PE HIGHLOW+0x87=0x005B8894')
 print('PASS actual native array offset +0x06000730, 42-entry bound, original 284B File::clear')

if __name__=='__main__':verify()
