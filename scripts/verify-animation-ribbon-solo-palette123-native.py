#!/usr/bin/env python3
"""Independent PE proof of the entire solo ribbon 123B segment palette."""
from pathlib import Path
import importlib.util
import struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045DBF0,123
E8={0x1B:0x004142A0,0x27:0x0045DD20,0x42:0x00414580,0x49:0x0045D650,0x6F:0x0045DD00}
HIGHLOW={0x5F:0x0056CD94}
PARENT=0x0045DB30+0x52

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    reloc=pe.physical_highlow(image,base,sections);decoder=Cs(CS_ARCH_X86,CS_MODE_32)
    ins=list(decoder.disasm(pe.raw_at(image,base,sections,HEAD,SIZE),HEAD))
    assert len(ins)==39,(len(ins),39)
    assert ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
    calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xE8}
    fields={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
            for p in reloc if HEAD<=p<HEAD+SIZE}
    assert calls==E8,(calls,E8)
    assert fields==HIGHLOW,(fields,HIGHLOW)
    by_offset={i.address-HEAD:(i.mnemonic,i.op_str) for i in ins}
    assert by_offset[0x2C]==('nop','')
    assert by_offset[0x4E]==('nop','')
    assert by_offset[0x74]==('nop','')
    assert ('push','0x80ffff80') in by_offset.values()
    assert ('add','eax, 0x1e0') in by_offset.values()
    assert ('add','ecx, 0x2d0') in by_offset.values()
    assert struct.unpack('<f',pe.raw_at(image,base,sections,0x0056CD94,4))[0]==32.0
    parent=pe.raw_at(image,base,sections,PARENT,5)
    assert parent[0]==0xE8
    target=(PARENT+5+struct.unpack_from('<i',parent,1)[0])&0xFFFFFFFF
    assert target==HEAD,(hex(PARENT),hex(target))
    for off,dest in calls.items():print(f'PASS original 123B E8 +{off:#04x} -> {dest:#010x}')
    for off,dest in fields.items():print(f'PASS original 123B HIGHLOW +{off:#04x} -> {dest:#010x}')
    print('PASS original 123B/39-i386, three genuine NOPs, real 0x80FFFF80 override, 32.0f radius')
    print(f'PASS original 182B config parent E8 {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
