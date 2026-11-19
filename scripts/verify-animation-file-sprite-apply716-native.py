#!/usr/bin/env python3
"""Whole-native proof for the 716B AnimationFile SpriteData application method."""
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
SYMBOL='?apply_sprite@NativeAnimationFileSpriteApplyView@th20@@QAEHPAVAnimation@2@H@Z'
SPRITE='?sprite@AnimationFile@th20@@QAEPAUSpriteData@2@H@Z'
IDENTITY='?identity_matrix@th20@@3UMatrix4@1@B'
SCALE256='?native_256@th20@@3MB'
EXPECTED_RELOCS=(
    (0x2D,'REL32',SPRITE,0x00437C80),
    (0x17E,'DIR32',IDENTITY,0x0056E068),
    (0x193,'DIR32',IDENTITY,0x0056E068),
    (0x1A5,'DIR32',SCALE256,0x0056CDA0),
    (0x1D4,'DIR32',SCALE256,0x0056CDA0),
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
    assert calls==[(0x2C,0x00437C80)],calls
    highlow=tuple(sorted(address-HEAD for address in pe.physical_highlow(image,base,sections)
                         if HEAD<=address<HEAD+SIZE))
    assert highlow==(0x17E,0x193,0x1A5,0x1D4),highlow
    scale=pe.raw_at(image,base,sections,0x0056CDA0,4)
    assert struct.unpack('<f',scale)[0]==256.0
    identity=struct.unpack('<16f',pe.raw_at(image,base,sections,0x0056E068,64))
    assert identity==(1.0,0.0,0.0,0.0,0.0,1.0,0.0,0.0,
                      0.0,0.0,1.0,0.0,0.0,0.0,0.0,1.0),identity
    return body

def verify_candidate(path:Path):
    result=cf.compare(path,SYMBOL,HEAD,SIZE)
    assert result['result']=='structural-exact',result
    assert result['size']==SIZE
    assert result['comparable_bytes']==696
    assert result['matched_comparable_bytes']==696
    actual=tuple((int(item['offset'],16),item['type'],item['symbol'],
                  int(item['solved_destination'],16)) for item in result['relocations'])
    assert actual==EXPECTED_RELOCS,actual
    return result

def main():
    verify_original()
    print('PASS original whole 716B/179-i386 AnimationFile sprite application: SHA, RET 8, one SpriteData accessor E8, four physical HIGHLOW fields')
    print('PASS original identity_matrix at 0x0056E068 and native_256=256.0 at 0x0056CDA0')
    if len(sys.argv)==3 and sys.argv[1]=='--candidate-object':
        result=verify_candidate(Path(sys.argv[2]))
        print('PASS candidate 716B: 696/696 ordinary bytes and all five relocation roles/targets exact')
    elif len(sys.argv)>1:
        raise SystemExit('usage: verify-animation-file-sprite-apply716-native.py [--candidate-object OBJECT]')
    else:
        print('ORIGINAL ONLY: pass --candidate-object build/...obj for candidate verification')

if __name__=='__main__':
    main()
