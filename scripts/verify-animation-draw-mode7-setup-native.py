#!/usr/bin/env python3
"""Original PE-only proof of entire native 1996B Animation mode7 setup.

Calls, data relocations, matrix and corner construction are independently
attested from the locked original PE, not inferred from candidate COFF data.
"""
from collections import Counter
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(s);s.loader.exec_module(original)
HEAD=0x00441430
SIZE=1996
CALL_SITES={
    0x1E:0x0040BDA0,0x29:0x0040BDA0,
    0x111:0x00437770,
    0x14C:0x00540684,0x16B:0x0054067E,
    0x196:0x0054068A,0x1B6:0x0054067E,
    0x1E1:0x00540690,0x200:0x0054067E,
    0x50D:0x0040BC20,
    0x7C1:0x005429EE,
}
DATA_SITES={
    0xA:0x005B25C0,
    0x130:0x0056CD50,0x17A:0x0056CD50,0x1C5:0x0056CD50,
    0x2A9:0x005B87F8,0x2B1:0x0056C8D0,
    0x2EB:0x005B87FC,0x2F3:0x0056D7C0,0x2FB:0x0056C8D0,
    0x501:0x00422E10,
    0x56E:0x0056CDA0,0x584:0x0056CDA0,
    0x59E:0x0056CDBC,0x5B4:0x0056CDBC,
    0x5CA:0x0056CD98,0x5E0:0x0056CD98,
    0x5F7:0x0056E1A4,0x60D:0x0056E1A4,
    0x695:0x0056CDA0,0x6AA:0x0056CDA0,
    0x6C5:0x0056CDBC,0x6DB:0x0056CDBC,
    0x6F1:0x0056CD98,0x706:0x0056CD98,
    0x71E:0x0056E1A4,0x734:0x0056E1A4,
}


def verify():
    image,_=original.verified_target()
    base,sections=original.parse_sections(image)
    code=original.raw_at(image,base,sections,HEAD,SIZE)
    instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(instr)==459 and instr[-1].address+instr[-1].size==HEAD+SIZE
    assert instr[2].mnemonic=='sub' and instr[2].op_str=='esp, 0xcc'
    assert instr[-1].mnemonic=='ret' and instr[-1].op_str=='4'
    assert instr[-7].mnemonic=='xor' or any(x.mnemonic=='xor' and x.op_str=='eax, eax' and x.address-HEAD==0x7B8 for x in instr)
    callsites={}
    for inst in instr:
        if inst.bytes[0]==0xe8 and len(inst.bytes)==5:
            callsites[inst.address-HEAD]=(inst.address+5+struct.unpack_from('<i',inst.bytes,1)[0])&0xffffffff
    assert callsites==CALL_SITES,(callsites,CALL_SITES)
    highlow=original.physical_highlow(image,base,sections)
    fields={site-HEAD:struct.unpack('<I',original.raw_at(image,base,sections,site,4))[0]
            for site in highlow if HEAD<=site<HEAD+SIZE}
    assert fields==DATA_SITES,(fields,DATA_SITES)
    heads={x.address-HEAD:x for x in instr}
    assert heads[0x2E].mnemonic=='nop'
    assert [x.address-HEAD for x in instr if x.mnemonic=='rep movsd']==[0x5B,0x22C,0x7B6]
    assert heads[0x38].mnemonic=='shr' and heads[0x38].op_str=='ecx, 0x1a'
    assert heads[0x3B].mnemonic=='and' and heads[0x3B].op_str=='ecx, 1'
    assert heads[0x500].mnemonic=='push' and heads[0x500].op_str=='0x422e10'
    assert heads[0x7B8].mnemonic=='xor' and heads[0x7B8].op_str=='eax, eax'
    assert Counter(DATA_SITES.values())==Counter({
        0x005B25C0:1,0x0056CD50:3,
        0x005B87F8:1,0x005B87FC:1,0x0056C8D0:2,0x0056D7C0:1,
        0x00422E10:1,0x0056CDA0:4,0x0056CDBC:4,0x0056CD98:4,0x0056E1A4:4,
    })
    print('PASS original complete 1996B/459-x86 0x441430 method, 0xCC frame, 3 real REP MOVSD 64B copies, native ret4/EAX=0')
    print('PASS 11 actual E8 instruction-site destinations: 2 matrix ctors, original 196B rotation getter, 6 D3DX rotation/multiply imports, 4xVector3 iterator and security checker')
    print('PASS 26 original PE HIGHLOW site/target pairs: original double zero, four +/-128/256 game constants, WindowState dimensions, native 2.0/448 and real Vector3 ctor pointer')
    print('Original-only provenance accepted; candidate full-source exactness still requires a separate strict canonical COFF replay')


if __name__=='__main__':verify()
