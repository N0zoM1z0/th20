#!/usr/bin/env python3
"""Whole-original and canonical candidate proof for AnimationFile::apply_sprite."""
from __future__ import annotations
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

pe=load('sprite_apply_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('sprite_apply_coff','scripts/compare-coff-function.py')
HEAD=0x00438620
SIZE=716
SHA256='588b789deec72290b8fd75c577751531b00f231ad30f890a8d8c032ca69bf860'
SYMBOL='?apply_sprite@AnimationFile@th20@@QAEHPAVAnimation@2@H@Z'
SPRITE_SYMBOL='?sprite@AnimationFile@th20@@QAEPAUSpriteData@2@H@Z'
IDENTITY_SYMBOL='?identity_matrix@th20@@3UMatrix4@1@B'
NATIVE_256_SYMBOL='?native_256@th20@@3MB'
EXPECTED_CALLS=((0x2C,0x00437C80),)
EXPECTED_HIGHLOW=(0x17E,0x193,0x1A5,0x1D4)
EXPECTED_RELOCS=(
    (0x02D,'REL32',SPRITE_SYMBOL,0x00437C80),
    (0x17E,'DIR32',IDENTITY_SYMBOL,0x0056E068),
    (0x193,'DIR32',IDENTITY_SYMBOL,0x0056E068),
    (0x1A5,'DIR32',NATIVE_256_SYMBOL,0x0056CDA0),
    (0x1D4,'DIR32',NATIVE_256_SYMBOL,0x0056CDA0),
)

def verify_original():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,SIZE)
    digest=hashlib.sha256(body).hexdigest()
    assert digest==SHA256,(digest,SHA256)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(instructions)==179,len(instructions)
    assert instructions[-1].address+instructions[-1].size==HEAD+SIZE
    assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str=='8'
    calls=[]
    for item in instructions:
        if item.size==5 and item.bytes[0]==0xE8:
            target=(item.address+5+struct.unpack_from('<i',item.bytes,1)[0])&0xffffffff
            calls.append((item.address-HEAD,target))
    assert tuple(calls)==EXPECTED_CALLS,calls
    highlow=tuple(sorted(address-HEAD for address in pe.physical_highlow(image,base,sections)
                         if HEAD<=address<HEAD+SIZE))
    assert highlow==EXPECTED_HIGHLOW,highlow
    return body

def verify_candidate(path:Path):
    body,relocations=cf.object_function(path,SYMBOL,SIZE)
    assert len(body)==SIZE,len(body)
    actual=tuple(sorted((int(item['offset']),item['type'],str(item['symbol']))
                        for item in relocations))
    expected=tuple(sorted((offset,kind,symbol) for offset,kind,symbol,_ in EXPECTED_RELOCS))
    assert actual==expected,actual
    report=cf.compare(path,SYMBOL,HEAD,SIZE)
    assert report['result']=='structural-exact',report
    assert report['size']==SIZE and report['comparable_bytes']==696
    assert report['matched_comparable_bytes']==696 and report['relocation_field_bytes']==20
    assert not report['first_differences'],report['first_differences']
    solved=tuple(sorted((int(item['offset'],16),item['type'],item['symbol'],
                         int(item['solved_destination'],16)) for item in report['relocations']))
    assert solved==tuple(sorted(EXPECTED_RELOCS)),solved
    return report

def main():
    verify_original()
    print('PASS original whole 716B/179-i386 AnimationFile::apply_sprite SHA, RET 8, E8 +0x2C -> 0x00437C80 and four physical HIGHLOW fields')
    if len(sys.argv)==3 and sys.argv[1]=='--candidate-object':
        report=verify_candidate(Path(sys.argv[2]))
        print('PASS candidate whole 716/716: 696 ordinary bytes + 20 relocation bytes; all five original relocation destinations exact')
        print('PASS strict structural comparison: zero ordinary-byte differences; one native SpriteData accessor and four original data references')
    elif len(sys.argv)>1:
        raise SystemExit('usage: verify-animation-file-sprite-apply716-native.py [--candidate-object OBJECT]')
    else:
        print('ORIGINAL ONLY: pass --candidate-object build/.../AnimationFileSpriteApply.obj for candidate verification')

if __name__=='__main__':
    main()
