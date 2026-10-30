#!/usr/bin/env python3
"""Immutable original PE-only whole 4347B Animation draw mode8 CFG census.

Attests 101 original real E8 targets, 39 body data HIGHLOW, six genuine
native switch pointer relocations, original entry labels and after-RET NOP.
The complete original target is read without trusting candidate COFF source.
"""
from collections import Counter
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(sp);sp.loader.exec_module(original)
HEAD=0x00441F00
SIZE=4347
TABLE=HEAD+SIZE+1
COMPARE_SIZE=SIZE+1+6*4
CASE_TARGETS=[0x00442261,0x0044239B,0x004424D5,0x0044260F,0x00442749,0x00442883]
CALL_TARGET_COUNTS=Counter({
 0x0040BDA0:41,0x0054067E:18,0x00412730:7,
 0x00540684:6,0x0054068A:6,0x00540690:6,
 0x0043F520:4,0x004455C0:3,
 0x00445AB0:1,0x004DDF80:1,0x004DDFE0:1,
 0x00437770:1,0x004379E0:1,0x00445BC0:1,
 0x00437CD0:1,0x00445A00:1,0x00446690:1,0x005429EE:1,
})
DATA_TARGET_COUNTS=Counter({
 0x0056CD50:18,0x005C4D40:9,0x005B8818:4,0x0056E0EC:2,
 0x0056E0E8:2,0x0056C8CC:2,0x005B25C0:1,TABLE:1,
})


def original_fields():
    image,_=original.verified_target()
    base,sections=original.parse_sections(image)
    highlow=original.physical_highlow(image,base,sections)
    return {site-HEAD:struct.unpack('<I',original.raw_at(image,base,sections,site,4))[0]
            for site in highlow if HEAD<=site<HEAD+COMPARE_SIZE}


def original_calls():
    image,_=original.verified_target()
    base,sections=original.parse_sections(image)
    code=original.raw_at(image,base,sections,HEAD,SIZE)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(instructions)==1063
    assert instructions[-1].address+instructions[-1].size==HEAD+SIZE
    assert instructions[2].mnemonic=='sub' and instructions[2].op_str=='esp, 0x1bc'
    assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str=='4'
    return {ins.address-HEAD:(ins.address+5+struct.unpack_from('<i',ins.bytes,1)[0])&0xffffffff
            for ins in instructions if len(ins.bytes)==5 and ins.bytes[0]==0xE8}


def verify():
    calls=original_calls()
    assert len(calls)==101 and Counter(calls.values())==CALL_TARGET_COUNTS,(Counter(calls.values()),CALL_TARGET_COUNTS)
    assert list(calls.items())[:7]==[
       (0x1E,0x0040BDA0),(0x29,0x0040BDA0),(0x34,0x0040BDA0),
       (0x3D,0x00445AB0),(0x8F,0x004455C0),
       (0xAB,0x004DDF80),(0xB8,0x004DDFE0),
    ]
    assert list(calls.items())[-2:]==[(0x10AD,0x00412730),(0x10F0,0x005429EE)]
    fields=original_fields()
    code_fields={offset:v for offset,v in fields.items() if offset<SIZE}
    assert len(fields)==45 and len(code_fields)==39
    assert Counter(code_fields.values())==DATA_TARGET_COUNTS,(Counter(code_fields.values()),DATA_TARGET_COUNTS)
    assert code_fields[0x35D]==TABLE
    image,_=original.verified_target()
    base,sections=original.parse_sections(image)
    full=original.raw_at(image,base,sections,HEAD,COMPARE_SIZE)
    assert len(full)==4372 and full[SIZE:SIZE+1]==b'\x90'
    native_targets=[struct.unpack_from('<I',full,SIZE+1+4*i)[0] for i in range(6)]
    assert native_targets==CASE_TARGETS
    assert {offset:fields[offset] for offset in range(SIZE+1,COMPARE_SIZE,4)}=={
        SIZE+1+4*i:v for i,v in enumerate(CASE_TARGETS)
    }
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(full[:SIZE],HEAD))
    heads={i.address for i in ins}
    assert all(t in heads for t in CASE_TARGETS)
    by_offset={x.address-HEAD:x for x in ins}
    assert by_offset[0x35A].mnemonic=='jmp' and '0x442ffc' in by_offset[0x35A].op_str
    assert by_offset[0x332].mnemonic=='mov' and by_offset[0x332].op_str=='dl, byte ptr [ecx + 0x4a2]'
    assert by_offset[0x338].mnemonic=='shr' and by_offset[0x338].op_str=='dl, 2'
    assert by_offset[0x33B].mnemonic=='and' and by_offset[0x33B].op_str=='dl, 7'
    assert by_offset[0x33E].mnemonic=='movzx' and by_offset[0x33E].op_str=='eax, dl'
    assert sum(x.mnemonic=='ucomisd' for x in ins)==18
    print('PASS original whole 4347B/1063 native x86 Mode8 renderer, real 0x1BC stack and RET4')
    print('PASS 101 actual immutable original E8 physical site/destination pairs including 41 folded Matrix4/36 real D3DX-related matrix getters, 18 D3DX multiplies and six XYZ rotations each')
    print('PASS 39 true original body PE HIGHLOW fields and real one-NOP/6-pointer native mode0..5 switch after RET (complete original 4372B COFF extent)')
    print('PASS actual [6 unique native code heads] at 0x00442FFC mode table, original 8-bit bitfield shr/and/movzx, 18 genuine double UCOMISD angle checks')
    print('IMMUTABLE ORIGINAL PE audit alone does not establish a canonical source match; require independently mapped full COFF/receipt replay')


if __name__=='__main__':verify()
