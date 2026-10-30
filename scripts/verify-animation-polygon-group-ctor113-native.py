#!/usr/bin/env python3
"""Independent locked-original-PE audit for polygon group 113B ctor and 49B scalar deleting destructor.

Compiler-source matching and original implementation origins are separate:
this original-only verifier never reads reconstructed C++/COFF bytes.
"""
from pathlib import Path
import importlib.util
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('locked',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
BODIES={
  0x0045F340:(113,{0x0E:0x00446B60,0x22:0x0045F2B0,0x3E:0x00422D90,0x59:0x00422E10},{0x18:0x0056EE50}),
  0x0045F5A0:(49,{0x0A:0x0045C2A0,0x20:0x0054278D},{}),
  0x0045C2A0:(20,{0x0A:0x00446BA0},{}),
}
VTABLE=(0x0045F5A0,0x0045F5E0,0x0045F9B0,0x00412540,0x00414B50,0x00414B50)

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    dec=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,(size,calls,direct) in BODIES.items():
        ops=list(dec.disasm(pe.raw_at(image,base,sections,head,size),head))
        assert ops and ops[-1].address+ops[-1].size==head+size and ops[-1].mnemonic=='ret'
        observed_calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                        for i in ops if i.size==5 and i.bytes[0]==0xE8}
        assert observed_calls==calls,(hex(head),observed_calls,calls)
        original_highlow={p-head:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
                          for p in highlow if head<=p<head+size}
        assert original_highlow==direct,(hex(head),original_highlow,direct)
        print(f'PASS original {head:#010x}: complete {size}B /{len(ops)} x86 /{len(calls)} E8 /{len(direct)} HIGHLOW')
    original_vtable=struct.unpack('<6I',pe.raw_at(image,base,sections,0x0056EE50,24))
    assert original_vtable==VTABLE,original_vtable
    print('PASS original vtable 0x0056EE50: scalar delete, 140B update, 233B draw and three inherited/folded slots')
    c=dec.disasm(pe.raw_at(image,base,sections,0x0045F0A0,156),0x0045F0A0)
    assert any(i.address==0x0045F0A0+0x6A and i.mnemonic=='call' and
               int(i.op_str,16)==0x0045F340 for i in c)
    print('PASS real 156B C++17 allocation factory directly invokes original 113B constructor')
    print('NOTE physical 20B ordinary destructor remains separate; exact 49B scalar-deleting wrapper does not imply its 20B child is exact')

if __name__=='__main__':verify()
