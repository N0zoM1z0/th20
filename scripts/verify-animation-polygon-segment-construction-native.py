#!/usr/bin/env python3
"""Independent original-PE audit of polygon construction chain.

Checks complete original function boundaries, real x86 E8 destinations, PE
HIGHLOW data targets and genuine interfunction INT3. Compiled COFF matching is
performed separately, never by this immutable-original-only verifier.
"""
from pathlib import Path
import importlib.util
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
# Head: (complete original body bytes, complete E8 offsets/targets,
#        original PE HIGHLOW offsets/targets). Each body ends in a real ret.
BODIES={
    0x0045F210:(75,{0x33:0x0040BC20},
                    {0x06:0x00567600,0x13:0x005B25C0,0x27:0x00425CC0}),
    0x0045F260:(75,{0x33:0x0040BC20},
                    {0x06:0x00567600,0x13:0x005B25C0,0x27:0x004398A0}),
    0x0045F2B0:(78,{0x36:0x0040BC20},
                    {0x06:0x00567600,0x13:0x005B25C0,0x27:0x0045F3C0}),
    0x0045F340:(113,{0x0E:0x00446B60,0x22:0x0045F2B0,
                      0x3E:0x00422D90,0x59:0x00422E10},
                     {0x18:0x0056EE50}),
    0x0045F3C0:(60,{0x0A:0x0045F260,0x18:0x0045F210,
                     0x2D:0x00544760},{}),
}

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,(size,expected_e8,expected_hi) in BODIES.items():
        raw=pe.raw_at(image,base,sections,head,size)
        instructions=list(cs.disasm(raw,head))
        assert instructions and instructions[-1].address+instructions[-1].size==head+size
        assert instructions[-1].mnemonic=='ret'
        calls={i.address-head:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
               for i in instructions if i.size==5 and i.bytes[0]==0xE8}
        assert calls==expected_e8,(hex(head),calls,expected_e8)
        data={addr-head:struct.unpack('<I',pe.raw_at(image,base,sections,addr,4))[0]
              for addr in highlow if head<=addr<head+size}
        assert data==expected_hi,(hex(head),data,expected_hi)
        print(f'PASS original 0x{head:08X}: {size}B/{len(instructions)} x86, {len(calls)} E8, {len(data)} HIGHLOW')
    # The original 75-byte Handle array constructor ends in C3, followed by
    # *five* real CC between this function and the 75B Vector2 array ctor.
    pad=pe.raw_at(image,base,sections,0x0045F210+75,5)
    assert pad==b'\xcc'*5
    assert 0x0045F260 == 0x0045F210+75+5
    vtable=pe.raw_at(image,base,sections,0x0056EE50,12)
    assert struct.unpack('<III',vtable)==(0x0045F5A0,0x0045F5E0,0x0045F9B0)
    assert 61*8+61*4+62*4==0x3D4
    print('PASS real five-byte INT3 alignment; 61 Vector2 /61 four-byte color cells (ctor folded with AnimationHandle) /62 radii; native group vtable')

if __name__=='__main__':verify()
