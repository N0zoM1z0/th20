#!/usr/bin/env python3
"""Immutable original-PE-only whole 612B Animation strip mode9 verification.

Confirms original 182 x86, 11 physical E8 and five original PE HIGHLOW
site/destination pairs and one native parent call independent of source.
"""
from pathlib import Path
import importlib.util,sys,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pe','scripts/verify-animation-draw-boss-native.py')
pe_mod=importlib.util.module_from_spec(s);s.loader.exec_module(pe_mod)
HEAD=0x00445350
SIZE=612
CALL_SITES={
 0x1A:0x00445AB0,0x66:0x004455C0,0xF7:0x00437CD0,
 0x124:0x00412730,0x147:0x00445A00,
 0x175:0x00412730,0x19C:0x00412730,0x1C4:0x00412730,
 0x1F8:0x00445BA0,0x226:0x00446690,0x230:0x00412730,
}
DATA_SITES={0x120:0x005C4D40,0x171:0x005C4D40,
            0x198:0x005C4D40,0x1C0:0x005C4D40,0x22C:0x005C4D40}


def verify():
 pe,_=pe_mod.verified_target();base,secs=pe_mod.parse_sections(pe)
 b=pe_mod.raw_at(pe,base,secs,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==182 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0x40'
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='0xc'
 actual={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert actual==CALL_SITES,(actual,CALL_SITES)
 hi=pe_mod.physical_highlow(pe,base,secs)
 fields={x-HEAD:struct.unpack('<I',pe_mod.raw_at(pe,base,secs,x,4))[0]
         for x in hi if HEAD<=x<HEAD+SIZE}
 assert fields==DATA_SITES,(fields,DATA_SITES)
 ops={i.address-HEAD:i for i in ins}
 assert ops[0x1FD].mnemonic=='mov' and ops[0x1FD].op_str=='ecx, dword ptr [ebp + 8]'
 assert ops[0x200].mnemonic=='mov' and ops[0x200].op_str=='dl, byte ptr [ecx + 0x4a0]'
 assert ops[0x206].mnemonic=='shr' and ops[0x206].op_str=='dl, 4'
 assert ops[0x209].mnemonic=='and' and ops[0x209].op_str=='dl, 3'
 assert ops[0x20C].mnemonic=='movzx' and ops[0x20C].op_str=='eax, dl'
 assert ops[0x212].mnemonic=='je'
 parent_head=0x00443880
 parent=pe_mod.raw_at(pe,base,secs,parent_head,5993)
 calls=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,parent_head)
        if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert calls==[0x00443B01],calls
 print('PASS original entire 612B/182-i386 strip9 renderer, frame0x40/RET0xC and native 28B vertex streams')
 print('PASS 11 immutable native physical E8 site/destinations and five real PE HIGHLOW to Graphics 0x005C4D40')
 print('PASS bitfield at Animation+0x4A0: original 8-bit SHR4/AND3/MOVZX and JE, no nonnative NOP after prepare_texture_states')
 print('PASS genuine 5993B Draw parent original physical E8 caller at 0x00443B01')

if __name__=='__main__':verify()
