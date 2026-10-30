#!/usr/bin/env python3
"""Original PE-only audit of entire native 1378B Mode6 screen projection.

All source-independent E8 / HIGHLOW physical target fields are fixed first;
matching source or canonical manifest is verified separately, never used as
an authority to solve this PE's original target identities.
"""
from pathlib import Path
import importlib.util
import sys
import struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('draw_native',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(s);s.loader.exec_module(original)
HEAD=0x00440340
SIZE=1378
CALL_SITES={
  0x1E:0x00437770,0x3E:0x00439820,0x5A:0x004397C0,
  0x68:0x0040BDA0,0x70:0x0040BDA0,0x78:0x0040BDA0,0x80:0x0040BDA0,
  0xA3:0x00422DD0,0x189:0x00540678,0x1E2:0x00540678,
  0x1F6:0x00429440,0x210:0x004399B0,
  0x3AB:0x00445B20,0x436:0x00445B20,0x4BE:0x00445B20,0x548:0x00445B20,
  0x557:0x005429EE,
}
DATA_SITES={
  0xA:0x005B25C0,0xAE:0x0056E100,
  0x161:0x005C5840,0x16A:0x005C5840,0x176:0x005C5840,
  0x1A0:0x0056C8CC,0x1B4:0x005C5840,0x1BD:0x005C5840,
  0x1C9:0x005C5840,0x1D6:0x005C5840,
  0x22A:0x0056E0EC,
  0x2A2:0x005AEF18,0x2B6:0x005AEF18,0x2CB:0x005AEF18,0x2E0:0x005AEF18,
  0x2FB:0x0056E140,0x31C:0x0056E140,
  0x3A0:0x005AEF10,0x42B:0x005AEF10,0x4B3:0x005AEF10,0x53D:0x005AEF10,
}


def verify():
    image,_=original.verified_target()
    base,sections=original.parse_sections(image)
    src=original.raw_at(image,base,sections,HEAD,SIZE)
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(src,HEAD))
    assert len(ins)==335 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0xac'
    assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='4'
    callsites={}
    for row in ins:
        if row.bytes[0]==0xe8 and len(row.bytes)==5:
            callsites[row.address-HEAD]=(row.address+5+struct.unpack_from('<i',row.bytes,1)[0])&0xffffffff
    assert callsites==CALL_SITES,(callsites,CALL_SITES)
    highlow=original.physical_highlow(image,base,sections)
    fields={p-HEAD:struct.unpack('<I',original.raw_at(image,base,sections,p,4))[0]
            for p in highlow if HEAD<=p<HEAD+SIZE}
    assert fields==DATA_SITES,(fields,DATA_SITES)
    by_offset={row.address-HEAD:row for row in ins}
    assert by_offset[0x18E].mnemonic=='nop' and by_offset[0x1E7].mnemonic=='nop'
    assert by_offset[0x54D].mnemonic=='nop' and by_offset[0x54E].mnemonic=='xor'
    assert by_offset[0x54E].op_str=='eax, eax'
    assert by_offset[0x1A6].mnemonic=='or' and by_offset[0x1A6].op_str=='eax, 0xffffffff'
    assert by_offset[0x196].mnemonic=='ja' and by_offset[0x1A4].mnemonic=='jbe'
    identity=original.raw_at(image,base,sections,0x0056E100,64)
    matrix=[struct.unpack_from('<f',identity,i*4)[0] for i in range(16)]
    assert matrix==[1.0 if i in (0,5,10,15) else 0.0 for i in range(16)]
    offsets=original.raw_at(image,base,sections,0x0056E140,2*3*4*4)
    six_four=[[struct.unpack_from('<f',offsets,4*(i*4+j))[0] for j in range(4)] for i in range(6)]
    assert six_four==[
        [-0.5,0.5,-0.5,0.5], [0.0,1.0,0.0,1.0],[-1.0,0.0,-1.0,0.0],
        [-0.5,-0.5,0.5,0.5],[0.0,0.0,1.0,1.0],[-1.0,-1.0,0.0,0.0],
    ],six_four
    assert Counter(DATA_SITES.values())==Counter({
      0x005B25C0:1,0x0056E100:1,0x005C5840:7,0x0056C8CC:1,
      0x0056E0EC:1,0x005AEF18:4,0x0056E140:2,0x005AEF10:4,
    })
    print('PASS complete native 1378B/335 i386 screen-projection setup at 0x00440340, frame 0xAC and natural RET4')
    print('PASS exactly 17 original physical E8 sites/targets including two D3DXVec3Project calls, Vector3 subtraction/length, four projected XY methods and cookie')
    print('PASS all 21 original PE HIGHLOW site/target pairs; independent 4x4 float identity matrix and physically native [2][3][4] projection coordinate tensor')
    print('PASS original unordered-aware depth COMISS/JA/JBE guards and three genuine compiler NOPs, including final block-boundary NOP')


if __name__=='__main__':verify()
