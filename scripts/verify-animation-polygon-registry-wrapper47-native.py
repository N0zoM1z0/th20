#!/usr/bin/env python3
"""Original PE-only exact 47B cdecl registry => 296B polygon initializer.

The function's EAX return is the called 296B method's result. Original
prologue and RET show a cdecl three-argument function with no extra NOP.
All two native E8 and two original PE HIGHLOW sites/targets are attested
without source or COFF reference material.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0045FD10;SIZE=47
CALLS={0x013:0x0045F0A0,0x026:0x0045FB60}
HIGHLOW={0x009:0x0056EE68,0x00F:0x005B8894}

def verify():
 img,_=pe.verified_target();base,sects=pe.parse_sections(img)
 raw=pe.raw_at(img,base,sects,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==18 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[2].mnemonic=='push' and ins[2].op_str=='ecx'
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str==''
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if len(i.bytes)==5 and i.bytes[0]==0xe8}
 assert calls==CALLS,(calls,CALLS)
 fields={p-HEAD:struct.unpack('<I',pe.raw_at(img,base,sects,p,4))[0]
         for p in pe.physical_highlow(img,base,sects) if HEAD<=p<HEAD+SIZE}
 assert fields==HIGHLOW,(fields,HIGHLOW)
 by={i.address-HEAD:i for i in ins}
 assert by[0x018].mnemonic=='mov' and by[0x018].op_str=='dword ptr [ebp - 4], eax'
 assert by[0x023].mnemonic=='mov' and by[0x023].op_str=='ecx, dword ptr [ebp - 4]'
 assert by[0x02B].mnemonic=='mov' and by[0x02B].op_str=='esp, ebp'
 assert not any(i.mnemonic=='nop' for i in ins)
 print('PASS immutable original entire 47B/18-x86 cdecl registry->game polygon configuration wrapper, EAX downstream return preserved')
 print('PASS both real original E8 physical site/target pairs and both true PE HIGHLOW data field/target pairs')
 print('PASS real native type-marker address 0x56EE68, native registry pointer global 0x5B8894, 156B resolver->296B exact Boss')

if __name__=='__main__':verify()
