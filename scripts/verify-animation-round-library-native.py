#!/usr/bin/env python3
"""Immutable PE-only checks for the 20-byte global round(float) wrapper.

This is C++ library/header code, not authored game code. The CRT function to
which it forwards is independently validated by original PE control flow.
"""
from collections import Counter
import importlib.util
from pathlib import Path
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT/'scripts'))
sp = importlib.util.spec_from_file_location('round_original', ROOT/'scripts/verify-animation-quad-submit-native.py')
original = importlib.util.module_from_spec(sp)
sp.loader.exec_module(original)


def verify():
    image,_ = original.original.verified_target()
    base,sections = original.original.parse_sections(image)
    relocated = original.original.physical_highlow(image,base,sections)
    wrapper_addr = 0x00445B80
    wrapper_bytes = original.original.raw_at(image,base,sections,wrapper_addr,20)
    ins = list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(wrapper_bytes,wrapper_addr))
    assert len(wrapper_bytes)==20 and len(ins)==9
    assert [x.mnemonic for x in ins]==['push','mov','push','mov','mov','call','add','pop','ret']
    assert ins[3].op_str=='eax, dword ptr [ebp + 8]'
    assert ins[4].op_str=='dword ptr [esp], eax'
    call=ins[5]
    assert call.address==wrapper_addr+0xA and call.size==5 and call.bytes[0]==0xE8
    target=(call.address+5+struct.unpack_from('<i',call.bytes,1)[0])&0xffffffff
    assert target==0x00550060
    assert ins[-1].address+ins[-1].size==wrapper_addr+20
    assert not any(wrapper_addr<=r<wrapper_addr+20 for r in relocated)

    crt_addr=0x00550060
    crt_size=123
    crt=original.original.raw_at(image,base,sections,crt_addr,crt_size)
    instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(crt,crt_addr))
    assert instr[0].bytes==b'\x8b\xff' and instr[0].op_str=='edi, edi'
    assert instr[-1].address+instr[-1].size==crt_addr+crt_size
    assert instr[-1].mnemonic=='ret'
    assert len([x for x in instr if x.mnemonic=='ret'])==4
    assert {0x4B000000,0x3F800000,0x3F000000}.issubset(
        {int(x.op_str.split(', ')[1],16) for x in instr
         if x.mnemonic=='cmp' and x.op_str.startswith('eax, 0x')})
    assert not any(crt_addr<=r<crt_addr+crt_size for r in relocated)
    # No global copied bytes, invented trampoline or solved call destination:
    # these are the native control-flow and bit-domain facts of this PE.
    print('PASS original 20B/9-x86 round(float) wrapper with real E8 +0xA -> 0x00550060')
    print('PASS original 123B CRT roundf body, three IEEE754 thresholds and four physical RET paths')
    print('PASS no original HIGHLOW in wrapper or 123B CRT; C++ standard-library wrapper is non-authored')


if __name__=='__main__':
    verify()
