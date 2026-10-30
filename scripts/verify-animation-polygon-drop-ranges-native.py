#!/usr/bin/env python3
"""Independently check original TH20 polygon drop-view array bounds and ABI.

This is original PE evidence, not a codegen comparison. The native 62/61
std::array sizes are derived from actual method bodies (not the previous
60-item source hypothesis) and must not be inferred from decompiler names.
"""
from pathlib import Path
import importlib.util
import struct
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location('locked_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD=0x0045F670
SIZE=827
BEGIN={
    0x0045FDA0:(0x0045EF50,0x0045F140,0x0045EEF0,0x0045F4C0),
    0x0045FE00:(0x0045EFD0,0x0045F140,0x0045EF70,0x0045F4F0),
}
SIZES={0x0045FFE0:62,0x0045FFF0:61}

def get_calls(ops):
    return {i.address+1:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in ops if i.size==5 and i.bytes[0]==0xe8}

def verify():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    reloc=pe.physical_highlow(image,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,size_value in SIZES.items():
        code=pe.raw_at(image,base,sections,head,16)
        ops=list(cs.disasm(code,head))
        assert len(ops)==8 and ops[-1].address+ops[-1].size==head+16
        assert ops[4].mnemonic=='mov' and ops[4].op_str==f'eax, {hex(size_value)}'
        assert not get_calls(ops)
        assert not (set(range(head,head+16)) & reloc)
        assert code[-1]==0xc3
        print(f'size: {head:#010x} => {size_value} elements, complete 16B, zero E8/HIGHLOW')
    for head,destinations in BEGIN.items():
        ops=list(cs.disasm(pe.raw_at(image,base,sections,head,93),head))
        assert ops[-1].address+ops[-1].size==head+93 and ops[-1].mnemonic=='ret'
        calls=get_calls(ops)
        assert calls=={head+site:target for site,target in zip((0xE,0x24,0x39,0x4F),destinations)},calls
        assert not (set(range(head,head+93)) & reloc)
        print(f'drop begin: {head:#010x}, original 93B, four independently checked E8')
    original=list(cs.disasm(pe.raw_at(image,base,sections,HEAD,SIZE),HEAD))
    assert len(original)==237 and original[-1].address+original[-1].size==HEAD+SIZE
    calls=get_calls(original)
    assert len(calls)==31
    assert calls[HEAD+0xDF]==0x0045FDA0
    assert calls[HEAD+0x21C]==0x0045FE00
    assert calls[HEAD+0x278]==0x00414580
    assert calls[HEAD+0x2F2]==calls[HEAD+0x313]==0x0045D670
    assert len({pos for pos in reloc if HEAD<=pos<HEAD+SIZE})==10
    # 61 points * 8B + 61 packed colors * 4B + 62 radii * 4B.
    assert 61*8==0x1e8 and 61*(8+4)==0x2dc and 61*(8+4)+62*4==0x3d4
    print('boss: 827B/237 i386, 31 E8, 10 HIGHLOW; storage: 61 points, 61 colors, 62 radii, total 0x3D4')

if __name__=='__main__':verify()
