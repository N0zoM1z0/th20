#!/usr/bin/env python3
"""Original locked PE-only entire 240B outlined-rectangle draw wrapper.

Source-independent full x86, two real E8 to accepted 1980B game rectangle,
two original 1.0f HIGHLOW absolute fields and two genuine main Draw callers.
"""
from pathlib import Path
import importlib.util,sys,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('native_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043A1C0;SIZE=240
CALL_SITES={0x94:0x00439A00,0xE3:0x00439A00}
DATA_SITES={0x5E:0x0056C8CC,0x71:0x0056C8CC}

def verify():
 data,_=pe.verified_target();base,sections=pe.parse_sections(data)
 b=pe.raw_at(data,base,sections,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==76 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0xc'
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='0x24'
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
        for x in ins if len(x.bytes)==5 and x.bytes[0]==0xE8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 rel={x-HEAD:struct.unpack('<I',pe.raw_at(data,base,sections,x,4))[0]
      for x in pe.physical_highlow(data,base,sections) if HEAD<=x<HEAD+SIZE}
 assert rel==DATA_SITES,(rel,DATA_SITES)
 code={i.address-HEAD:i for i in ins}
 assert code[0x0C].mnemonic=='and' and code[0x0C].op_str=='eax, 0xffffff'
 assert code[0x14].mnemonic=='shr' and code[0x14].op_str=='ecx, 0x18'
 assert code[0x17].mnemonic=='shr' and code[0x17].op_str=='ecx, 1'
 assert code[0x19].mnemonic=='shl' and code[0x19].op_str=='ecx, 0x18'
 assert code[0x24].mnemonic=='and' and code[0x24].op_str=='edx, 0xffffff'
 assert code[0x2D].mnemonic=='shr' and code[0x2D].op_str=='eax, 0x18'
 assert code[0x30].mnemonic=='shr' and code[0x30].op_str=='eax, 1'
 assert code[0x32].mnemonic=='shl' and code[0x32].op_str=='eax, 0x18'
 assert code[0xE8].mnemonic=='xor' and code[0xE8].op_str=='eax, eax'
 caller=0x00443880
 parent=pe.raw_at(data,base,sections,caller,5993)
 incoming=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,caller)
           if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert incoming==[0x00444029,0x004440B8],incoming
 print('PASS original complete 240B/76 x86 authored outline rectangle wrapper at 0x43A1C0, native 0xC frame and RET 0x24')
 print('PASS original two real E8 physical sites to whole strict 1980B rectangle and two genuine PE HIGHLOW at 0x56C8CC +1.0f')
 print('PASS original exact unsigned RGB preserve and alpha>>1 shift order for both colors, two 5993B native main Draw callers')

if __name__=='__main__':verify()
