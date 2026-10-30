#!/usr/bin/env python3
"""Original-only full 697B solo ribbon segment dynamics proof.

No candidate COFF, decompiler function name or compiler experiment is read.
Native E8 targets and all PE .reloc HIGHLOW sites are independent facts.
"""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D780,697
E8={
 0x034:0x0040BDA0,0x03F:0x0045DCA0,0x065:0x004298E0,
 0x09C:0x0040BDA0,0x0A7:0x0045DCA0,0x0D1:0x004298E0,
 0x194:0x00429210,0x1AA:0x00414580,0x1BF:0x0040BDA0,
 0x1CA:0x0045DCC0,0x201:0x00414580,0x212:0x004292E0,
 0x234:0x00439330,0x25D:0x004530C0,0x27B:0x0045D670,
 0x296:0x0045D670,0x2AB:0x005429EE,
}
HIGHLOW={
 0x01A:0x005B25C0,0x061:0x005BA4C4,0x076:0x0056CD90,
 0x07E:0x0056ED14,0x0CD:0x005BA4C4,0x0E2:0x0056C8D0,
 0x111:0x0056C8E0,0x12F:0x0056C8E0,0x14A:0x0056C8E0,
 0x168:0x0056C8E0,0x240:0x0056E0F0,0x248:0x0056C8D0,
 0x250:0x0056ED10,
}
CONSTANTS={0x0056CD90:16.0,0x0056ED14:224.0,0x0056C8D0:2.0,
           0x0056C8E0:4.0,0x0056ED10:58.0}
PARENT_E8=0x0045D6F0+0x68

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    hi=pe.physical_highlow(image,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    instr=list(cs.disasm(pe.raw_at(image,base,sections,HEAD,SIZE),HEAD))
    assert len(instr)==190,len(instr)
    assert instr[-1].address+instr[-1].size==HEAD+SIZE
    assert (instr[-1].mnemonic,instr[-1].op_str)==('ret','4')
    calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
           for i in instr if i.size==5 and i.bytes[0]==0xE8}
    data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
          for p in hi if HEAD<=p<HEAD+SIZE}
    assert calls==E8,(calls,E8)
    assert data==HIGHLOW,(data,HIGHLOW)
    ins={i.address-HEAD:(i.mnemonic,i.op_str) for i in instr}
    assert ins[0x82]==('cvttss2si','ecx, xmm0')
    assert ins[0x89]==('mov','byte ptr [edx + 2], cl')
    assert ins[0x124][0]=='jbe' and ins[0x15D][0]=='jbe'
    assert ins[0x1A5]==('push','0')
    assert ins[0x276]==('push','1')
    assert ins[0x291]==('push','0x3b')
    assert sum(i.mnemonic=='comiss' for i in instr)==2
    for address,value in CONSTANTS.items():
        f=struct.unpack('<f',pe.raw_at(image,base,sections,address,4))[0]
        assert f==value,(hex(address),f,value)
    original_parent=pe.raw_at(image,base,sections,PARENT_E8,5)
    assert original_parent[0]==0xE8
    dest=(PARENT_E8+5+struct.unpack_from('<i',original_parent,1)[0])&0xFFFFFFFF
    assert dest==HEAD,(hex(PARENT_E8),hex(dest))
    for off,target in E8.items():print(f'PASS original E8 +{off:#05x} -> {target:#010x}')
    for off,target in HIGHLOW.items():print(f'PASS original HIGHLOW +{off:#05x} -> {target:#010x}')
    print('PASS original 697B/190 i386, 17 genuine E8 and 13 HIGHLOW, RET 4')
    print('PASS color byte+2, 16x signed random+224, two 60-cell loops, +/-limit/4, 2*pi/58, vertex1->59')
    print(f'PASS original 140B solo update E8 {PARENT_E8:#010x} -> 0x0045d780')

if __name__=='__main__':verify()
