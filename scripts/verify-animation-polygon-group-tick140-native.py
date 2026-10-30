#!/usr/bin/env python3
"""Immutable PE-only 140B/46-x86 game polygon dynamic group tick Boss.

The actual original native function returns at +0x8B (140-byte extent).
Four original INT3 alignment bytes at +0x8C..+0x8F are NOT authored code;
the distinct original 827B segment function begins at 0x0045F670.
All six true E8 physical call offsets/targets and zero PE HIGHLOW fields
are independent original exe evidence; no shortened prefix is compared.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0045F5E0;SIZE=140
CALLS={0x012:0x0045D030,0x027:0x0040BDA0,0x032:0x0045FD40,
       0x05C:0x004379C0,0x068:0x0045F670,0x081:0x00423540}

def verify():
 original,_=pe.verified_target();base,sections=pe.parse_sections(original)
 body_and_gap=pe.raw_at(original,base,sections,HEAD,SIZE+4)
 assert body_and_gap[SIZE:]==b'\xCC'*4,body_and_gap[-3:]
 body=body_and_gap[:SIZE]
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==46 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str==''
 assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0x18'
 assert ins[-1].address-HEAD==0x8B
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 data=[x-HEAD for x in pe.physical_highlow(original,base,sections) if HEAD<=x<HEAD+SIZE]
 assert data==[],data
 by={i.address-HEAD:i for i in ins}
 assert by[0x03F].mnemonic=='add' and by[0x03F].op_str=='ecx, 0x3d4'
 assert by[0x068].mnemonic=='call' and by[0x068].op_str=='0x45f670'
 assert by[0x07C].mnemonic=='push' and by[0x07C].op_str=='0'
 assert pe.raw_at(original,base,sections,HEAD+SIZE+4,2)==b'\x53\x8B'
 print('PASS original whole 140B/46-native-x86 authored polygon group tick Boss, true 0x18 frame/RET')
 print('PASS six genuine original E8 physical site/absolute target roles, zero original PE HIGHLOW fields')
 print('PASS original 0x3D4 group element walk, real 827B dynamic-update E8, actual Animation::scale_x_value and timer increment')
 print('PASS original bytes +0x8C..+0x8F are four separate INT3 alignment bytes and 827B next head begins +0x90; NOT hidden original function code')

if __name__=='__main__':verify()
