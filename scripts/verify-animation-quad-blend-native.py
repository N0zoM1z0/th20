#!/usr/bin/env python3
"""Independent immutable original PE proof: complete 1163B quad blend boss.

This is NOT the C++-to-target strict comparator. It verifies all 54 physical
original relocation operand roles (25 actual E8, 29 original PE HIGHLOW),
and all four real native D3D9 texture-stage switch targets.
"""
from collections import Counter
from pathlib import Path
import importlib.util
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('native_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
assert spec and spec.loader
NATIVE=importlib.util.module_from_spec(spec)
spec.loader.exec_module(NATIVE)
HEAD=0x00446690
CODE_SIZE=1163
FULL_SIZE=1180
CASE_TABLE=0x00446B1C
ORIGINAL_CASE_HEADS=(0x004466CE,0x004467C4,0x004468DE,0x004469F8)

def verify():
    image,_=NATIVE.verified_target()
    base,sections=NATIVE.parse_sections(image)
    highlow=NATIVE.physical_highlow(image,base,sections)
    code=NATIVE.raw_at(image,base,sections,HEAD,CODE_SIZE)
    ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(ops)==343
    assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='4'
    assert ops[-1].address+ops[-1].size==HEAD+CODE_SIZE
    heads={inst.address:inst for inst in ops}
    assert heads[0x0044669C].mnemonic=='movzx'
    assert heads[0x004466A3].mnemonic=='movzx'
    assert heads[0x004466B7].mnemonic=='movzx'
    assert heads[0x004466C7].mnemonic=='jmp'
    assert heads[0x004466C7].op_str=='dword ptr [ecx*4 + 0x446b1c]'
    assert heads[0x004466BE].mnemonic=='cmp' and heads[0x004466BE].op_str=='dword ptr [ebp - 8], 3'
    # Direct original E8 histogram counts game queue flush once, genuine
    # Graphics getter 24 times, no guessed virtual static call destinations.
    e8=Counter((ins.address+5+struct.unpack_from('<i',ins.bytes,1)[0]) & 0xFFFFFFFF
               for ins in ops if len(ins.bytes)==5 and ins.bytes[0]==0xE8)
    assert e8=={0x004455C0:1,0x00412730:24}
    assert heads[0x004466B1].mnemonic=='call' and heads[0x004466B1].op_str=='0x4455c0'
    indirect=[ins for ins in ops if ins.mnemonic=='call' and ins.bytes[0]==0xFF]
    assert len(indirect)==24 and all('dword ptr [ebp - ' in i.op_str for i in indirect)
    assert sum(i.mnemonic=='mov' and '0x10c' in i.op_str for i in ops)==24
    physical=sorted(h for h in highlow if HEAD<=h<HEAD+FULL_SIZE)
    assert len(physical)==29,(len(physical),physical)
    assert HEAD+0x3A in physical
    assert struct.unpack('<I',NATIVE.raw_at(image,base,sections,HEAD+0x3A,4))[0]==CASE_TABLE
    table=NATIVE.raw_at(image,base,sections,CASE_TABLE,16)
    targets=struct.unpack('<4I',table)
    assert targets==ORIGINAL_CASE_HEADS
    for i in range(4):
        assert CASE_TABLE+4*i in physical
        assert targets[i] in heads
    globals_=[at for at in physical if at<HEAD+CODE_SIZE and at!=HEAD+0x3A]
    assert len(globals_)==24
    for at in globals_:
        assert struct.unpack('<I',NATIVE.raw_at(image,base,sections,at,4))[0]==0x005C4D40
    assert NATIVE.raw_at(image,base,sections,HEAD+CODE_SIZE,1)==b'\x90'
    assert CASE_TABLE==HEAD+CODE_SIZE+1
    # Parent 3159B renderer source itself still NONEXACT; original calls
    # the state machine once at its own physical E8 site.
    parent=NATIVE.decoded(image,base,sections,0x0043F6A0,3159)
    callers=[ins for ins in parent if ins.mnemonic=='call' and ins.op_str=='0x446690']
    assert [ins.address for ins in callers]==[0x0044015B]
    print('PASS original 1163B/343 i386 game quad blend state, complete RET4 and 24 real D3D9 vtable +0x10C calls')
    print('PASS original exactly 25 real direct E8 (24 Graphics get_device, one flush), 29 true original PE HIGHLOW')
    print('PASS original full 1180B contribution: 1163B code +1 NOP + 16B original four-pointer HIGHLOW switch')
    print('PASS original 0..3 case physical heads and original 0x0044015B parent E8 role; parent 3159B remains NONEXACT')

if __name__=='__main__':
    verify()
