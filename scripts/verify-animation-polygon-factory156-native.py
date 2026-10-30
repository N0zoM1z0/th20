#!/usr/bin/env python3
"""Original-PE-only polygon diagnostic factory and 47B caller evidence.

Reads immutable original executable .text/.reloc; does not read candidate COFF
or claim authored source provenance for a C++ allocator template.
"""
from pathlib import Path
import importlib.util
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp); sp.loader.exec_module(pe)
HEAD=0x0045F0A0
SIZE=156
CALLS={0x2D:0x0054275D,0x4D:0x0040C080,0x56:0x0040B280,0x6A:0x0045F340}
HIGHLOW={0x6:0x00568997,0x15:0x005B25C0}
CALLER=0x0045FD10

def decode(image,base,sections,address,length):
    raw=pe.raw_at(image,base,sections,address,length)
    ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,address))
    assert ops and ops[-1].address+ops[-1].size==address+length
    return ops

def calls_at(ops,head):
    return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in ops if i.size==5 and i.bytes[0]==0xE8}

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    reloc=pe.physical_highlow(image,base,sections)
    ops=decode(image,base,sections,HEAD,SIZE)
    assert len(ops)==46 and ops[-1].mnemonic=='ret' and ops[-1].op_str=='8'
    assert calls_at(ops,HEAD)==CALLS
    data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
          for p in reloc if HEAD<=p<HEAD+SIZE}
    assert data==HIGHLOW
    assert ops[0].mnemonic=='push' and ops[2].mnemonic=='push' and ops[2].op_str=='-1'
    assert any(i.mnemonic=='push' and i.op_str=='0xbac' for i in ops)
    assert any(i.mnemonic=='mov' and i.op_str=='dword ptr [ebp - 4], 0' for i in ops)
    caller=decode(image,base,sections,CALLER,47)
    assert calls_at(caller,CALLER)=={0x13:HEAD,0x26:0x0045FB60}
    raw_data={p-CALLER:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
              for p in reloc if CALLER<=p<CALLER+47}
    assert raw_data=={0x9:0x0056EE68,0xF:0x005B8894}
    print('PASS original 156B/46-x86 C++17 polygon diagnostic factory at 0x0045F0A0')
    print('PASS original 4 E8 physical call/destination pairs: operator new, class auto-init, forward, typed ctor')
    print('PASS 2 PE HIGHLOW: original EH handler and compiler security cookie')
    print('PASS original 47B caller E8 to this factory plus 296B group config, genuine marker/global data')
    print('NOTE candidate compiler exactness and template provenance are separate checks')

if __name__=='__main__':verify()
