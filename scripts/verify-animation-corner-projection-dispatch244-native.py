#!/usr/bin/env python3
"""Original-only role audit for Animation's 244B corner projection dispatcher."""
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

pe=load('corner_dispatch_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('corner_dispatch_coff','scripts/compare-coff-function.py')
HEAD=0x00445770
NATIVE_SIZE=244
NATIVE_SHA256='16c02538c572c3e989500be8e565718ad06648de0ddf07436d07aa95267785c4'
SYMBOL='?project_corners@Animation@th20@@QAEXPAUVector3@2@@Z'
PROJECTOR='?project_corners_43eb40@NativeAnimationCornerProjector@th20@@QAEXPAVAnimation@2@PAUVector3@2@111@Z'
ROTATED='?project_rotated_corners_43ef20@NativeAnimationCornerProjector@th20@@QAEXPAVAnimation@2@PAUVector3@2@111@Z'
OWNER='?current_animation_pool@th20@@3PAUAnimationPoolOwner@1@A'
EXPECTED_CALLS=((0x63,0x0043EB40),(0xA7,0x0043EF20),(0xE8,0x0043EB40))
EXPECTED_HIGHLOW=(0x26,0x5F,0xA3,0xE4)
EXPECTED_CANDIDATE_RELOCS=(
    (0x5E,'DIR32',OWNER),
    (0x63,'REL32',PROJECTOR),
    (0x98,'DIR32',OWNER),
    (0x9D,'REL32',ROTATED),
    (0xD2,'DIR32',OWNER),
    (0xD7,'REL32',PROJECTOR),
)

def verify_original():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,NATIVE_SIZE)
    digest=hashlib.sha256(body).hexdigest()
    assert digest==NATIVE_SHA256,(digest,NATIVE_SHA256)
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(ins)==79,len(ins)
    assert ins[-1].address+ins[-1].size==HEAD+NATIVE_SIZE
    assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='4'
    calls=[]
    for item in ins:
        if item.size==5 and item.bytes[0]==0xE8:
            destination=(item.address+5+struct.unpack_from('<i',item.bytes,1)[0])&0xffffffff
            calls.append((item.address-HEAD,destination))
    assert tuple(calls)==EXPECTED_CALLS,calls
    highlow=tuple(sorted(address-HEAD for address in pe.physical_highlow(image,base,sections)
                         if HEAD<=address<HEAD+NATIVE_SIZE))
    assert highlow==EXPECTED_HIGHLOW,highlow
    return body

def verify_candidate(path:Path):
    body,relocations=cf.object_function(path,SYMBOL,244)
    assert len(body)==244,len(body)
    actual=tuple(sorted((int(item['offset']),item['type'],str(item['symbol']))
                        for item in relocations
                        if item['symbol'] in (OWNER,PROJECTOR,ROTATED)))
    assert actual==tuple(sorted(EXPECTED_CANDIDATE_RELOCS)),actual
    switch_table=tuple(sorted((int(item['offset']),str(item['symbol']))
                              for item in relocations if str(item['symbol']).startswith('$LN')))
    assert switch_table==((0x2C,'$LN9'),(0xE4,'$LN4'),(0xE8,'$LN5'),
                          (0xEC,'$LN6'),(0xF0,'$LN6')),switch_table
    code=body[:0xE4]
    dis=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,0))
    assert len(dis)==76,(len(dis),len(code))
    assert sum(item.size for item in dis)==len(code)
    calls=[item.address for item in dis if item.size==5 and item.bytes[0]==0xE8]
    assert calls==[0x62,0x9C,0xD6],calls
    ret=next(item for item in dis if item.mnemonic=='ret')
    assert ret.op_str=='4' and ret.address==0xDF,(ret.address,ret.op_str)
    assert len(body)==0xE4+16 and len(body[0xE4:])==16
    return body,dis,relocations

def main():
    verify_original()
    print('PASS original whole 244B/79-i386 dispatcher SHA, RET 4, three E8 call targets and four physical HIGHLOW fields')
    if len(sys.argv)==3 and sys.argv[1]=='--candidate-object':
        candidate,ins,relocs=verify_candidate(Path(sys.argv[2]))
        print(f'PASS candidate whole {len(candidate)}B: 228B/76-i386 code + 16B compiler switch table; three original projector callee roles and three current_animation_pool DIR32 roles preserved')
        print('NONEXACT: original is 244B/79-i386 code with an external switch table; candidate code is 16B shorter, with E8 sites at +0x62/+0x9C/+0xD6 versus +0x63/+0xA7/+0xE8. No match-unit and no authored-byte credit.')
    elif len(sys.argv)>1:
        raise SystemExit('usage: verify-animation-corner-projection-dispatch244-native.py [--candidate-object OBJECT]')
    else:
        print('ORIGINAL ONLY: pass --candidate-object build/...obj for candidate role verification')

if __name__=='__main__':
    main()
