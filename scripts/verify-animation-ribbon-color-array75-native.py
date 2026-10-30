#!/usr/bin/env python3
"""Locked-original complete 75B ribbon color-cell array constructor + 5 INT3."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86,CS_MODE_32,Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D4B0,75
E8={0x33:0x0040BC20}
HIGHLOW={0x06:0x00567600,0x13:0x005B25C0,0x27:0x00425CC0}
PARENT_CALL=0x0045D610+0x18

def verify():
    image,_=pe.verified_target();base,secs=pe.parse_sections(image)
    relocation=pe.physical_highlow(image,base,secs)
    code=pe.raw_at(image,base,secs,HEAD,SIZE)
    decoded=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(decoded)==27 and decoded[-1].address+decoded[-1].size==HEAD+SIZE
    assert (decoded[-1].mnemonic,decoded[-1].op_str)==('ret','')
    calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in decoded if i.size==5 and i.bytes[0]==0xe8}
    data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,secs,p,4))[0] for p in relocation if HEAD<=p<HEAD+SIZE}
    assert calls==E8,(calls,E8)
    assert data==HIGHLOW,(data,HIGHLOW)
    assert ('push','0x3c') in [(i.mnemonic,i.op_str) for i in decoded]
    assert ('push','4') in [(i.mnemonic,i.op_str) for i in decoded]
    assert pe.raw_at(image,base,secs,HEAD+SIZE,5)==b'\xcc'*5
    encoded=pe.raw_at(image,base,secs,PARENT_CALL,5)
    assert encoded[0]==0xe8
    dest=(PARENT_CALL+5+struct.unpack_from('<i',encoded,1)[0])&0xffffffff
    assert dest==HEAD,(hex(PARENT_CALL),hex(dest))
    print('PASS whole original 75B/27-i386 array, 60x4-byte cells, real five INT3')
    print('PASS original C++ EH/cookie/AnimationHandle HIGHLOW + genuine ehvec constructor E8')
    print(f'PASS original 60B ribbon segment ctor E8 {PARENT_CALL:#010x} -> {HEAD:#010x}')
    print('NOTE adjacent 0x45D500 Vector2[60] original is separately NONEXACT')

if __name__=='__main__':verify()
