#!/usr/bin/env python3
"""Independent locked PE proof of the 23B/3x0x3C0 ribbon segment index."""
from pathlib import Path
import importlib.util
import struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D690,23
PARENT=0x0045EB10
PARENT_CALL_OFFSETS=(0x42,0x65,0x88)

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    decoder=Cs(CS_ARCH_X86,CS_MODE_32);hl=pe.physical_highlow(image,base,sections)
    code=pe.raw_at(image,base,sections,HEAD,SIZE)
    insns=list(decoder.disasm(code,HEAD))
    assert len(insns)==9 and insns[-1].address+insns[-1].size==HEAD+SIZE
    assert (insns[-1].mnemonic,insns[-1].op_str)==('ret','4')
    assert ('imul','eax, dword ptr [ebp + 8], 0x3c0') in [(x.mnemonic,x.op_str) for x in insns]
    assert not any(HEAD<=x<HEAD+SIZE for x in hl)
    assert not any(x.bytes[0]==0xe8 for x in insns)
    for offset in PARENT_CALL_OFFSETS:
        site=PARENT+offset;encoded=pe.raw_at(image,base,sections,site,5)
        assert encoded[0]==0xe8
        target=(site+5+struct.unpack_from('<i',encoded,1)[0])&0xffffffff
        assert target==HEAD,(hex(site),hex(target))
        print(f'PASS original 252B parent call {site:#010x} -> {HEAD:#010x}')
    print('PASS whole original 23B/9-i386 index, stride 0x3C0, RET 4, no native relocations')

if __name__=='__main__':verify()
