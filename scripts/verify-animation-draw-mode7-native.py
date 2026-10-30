#!/usr/bin/env python3
"""Immutable-PE-only full audit of original 753B Mode7 fog/quad renderer.

The original x86 and PE .reloc records are independent of candidate COFF.
Call targets and absolute-data identities are checked at actual native sites.
"""
from pathlib import Path
from collections import Counter
import importlib.util
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('draw_native',ROOT/'scripts/verify-animation-draw-boss-native.py')
orig=importlib.util.module_from_spec(spec);spec.loader.exec_module(orig)

HEAD=0x00441C00
SIZE=753
# Independent original PE observations: physical E8 instruction site/target.
CALL_SITES={
    0x1A:0x00441430,     # renderer setup of this original mode
    0x2C:0x0040BC20,     # real _eh vector-constructor iterator (library)
    0x34:0x00422E10,     # native Vector3 zero constructor
    0xCF:0x00540672,     # original D3DXVec3Transform import thunk
    0x12A:0x00445700,    # now exact full 25B depth/math wrapper
    0x277:0x0043F6A0,   # whole strict exact 3159B quad submit Boss
    0x2E6:0x005429EE,   # compiler security cookie verifier
}
# Physical HIGHLOW fields, not unrelated Ghidra decompiler assumptions.
DATA_SITES={
  0x7:0x005B25C0,0x20:0x004398D0,
  0x3B:0x005C5840,0x40:0x005C5840,0xDC:0x005C5840,
  0xF7:0x005C5840,0x112:0x005C5840,0x137:0x005C5840,
  0x14E:0x005C5840,0x171:0x0056C8CC,0x17D:0x005C5840,
  0x189:0x005AEF20,0x196:0x005AEF23,0x1B5:0x005C5840,
  0x1D6:0x005AEF20,0x1EF:0x005C5840,0x210:0x005AEF21,
  0x228:0x005C5840,0x249:0x005AEF22,0x256:0x005AEF23,
  0x265:0x005AEF20,0x28B:0x0056C8CC,0x293:0x005AEF1C,
  0x2A2:0x0056C8CC,0x2AA:0x005AEF1C,0x2BA:0x0056C8CC,
  0x2C2:0x005AEF1C,0x2D2:0x0056C8CC,0x2DA:0x005AEF1C,
}


def verify():
    image,_=orig.verified_target()
    base,sections=orig.parse_sections(image)
    code=orig.raw_at(image,base,sections,HEAD,SIZE)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(instructions)==178 and instructions[-1].address+instructions[-1].size==HEAD+SIZE
    assert instructions[2].mnemonic=='sub' and instructions[2].op_str=='esp, 0x6c'
    assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str=='4'
    call_sites={}
    for ins in instructions:
        if len(ins.bytes)==5 and ins.bytes[0]==0xE8:
            call_sites[ins.address-HEAD]=(ins.address+5+struct.unpack_from('<i',ins.bytes,1)[0])&0xFFFFFFFF
    assert call_sites==CALL_SITES,(call_sites,CALL_SITES)
    highlow=orig.physical_highlow(image,base,sections)
    reloc_sites={site-HEAD:struct.unpack('<I',orig.raw_at(image,base,sections,site,4))[0]
                 for site in highlow if HEAD<=site<HEAD+SIZE}
    assert reloc_sites==DATA_SITES,(reloc_sites,DATA_SITES)
    assert len(CALL_SITES)==7 and len(DATA_SITES)==29
    assert sum(target==0x005C5840 for target in DATA_SITES.values())==11
    assert sum(target==0x0056C8CC for target in DATA_SITES.values())==5
    assert Counter(target for target in DATA_SITES.values() if 0x005AEF10<=target<=0x005AEF90)==Counter({
        0x005AEF20:3,0x005AEF23:2,0x005AEF21:1,0x005AEF22:1,0x005AEF1C:4,
    })
    by_offset={i.address-HEAD:i for i in instructions}
    for offset,mnemonic,operand in (
        (0x140,'comiss','xmm0, dword ptr [edx + 0x150]'),
        (0x147,'jbe',None),
        (0x16E,'comiss','xmm0, dword ptr [0x56c8cc]'),
        (0x175,'jb',None),
        (0x1C7,'cvttss2si','ecx, xmm0'),
        (0x1CB,'movzx','edx, cl'),
        (0x201,'cvttss2si','ecx, xmm0'),
        (0x205,'movzx','eax, cl'),
        (0x23A,'cvttss2si','ecx, xmm0'),
        (0x23E,'movzx','eax, cl'),
    ):
        ins=by_offset[offset]
        assert ins.mnemonic==mnemonic and (operand is None or ins.op_str==operand),(hex(offset),ins)
    print('PASS native whole 753B/178 i386, frame 0x6C, all 7 E8 physical call sites and original targets')
    print('PASS exactly 29 independent PE HIGHLOW site/target values: 11 live viewport pointers, 5 one-floats, 11 quad color/RHW fields, array ctor and security cookie')
    print('PASS original COMISS/JBE, COMISS/JB NaN behavior; three native SSE truncations followed by 8-bit MOVZX, not signed 32-bit subtraction')
    print('PASS genuine D3DXVec3Transform thunk and original _eh array ctor, 25B depth helper and whole 3159B quad Boss dependencies')


if __name__=='__main__':verify()
