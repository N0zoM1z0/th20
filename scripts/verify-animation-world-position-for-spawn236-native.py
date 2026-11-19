#!/usr/bin/env python3
"""Whole-original and canonical candidate proof for Animation world-position recursion."""
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

pe=load('world_position_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('world_position_coff','scripts/compare-coff-function.py')
HEAD=0x0044CB80
SIZE=236
SHA256='390a97772793da5a55b5398aa28a11db73e87c9c5af50fc2ba70e94c07eb6dc8'
SYMBOL='?world_position_for_spawn@Animation@th20@@QAEAAUVector3@2@AAU32@@Z'
EXPECTED_CALLS=(
    (0x02C,0x00429570),(0x044,0x00429570),(0x093,0x00437930),
    (0x0A4,0x00458FA0),(0x0AF,0x00422E10),(0x0C7,0x0044CB80),
    (0x0D3,0x004296E0),(0x0E1,0x005429EE),
)
EXPECTED_HIGHLOW=(0x007,)
EXPECTED_RELOCS=(
    (0x007,'DIR32','___security_cookie',0x005B25C0),
    (0x02D,'REL32','??HVector3@th20@@QBE?AU01@ABU01@@Z',0x00429570),
    (0x045,'REL32','??HVector3@th20@@QBE?AU01@ABU01@@Z',0x00429570),
    (0x094,'REL32','?rotation_z_value@Animation@th20@@QAEMXZ',0x00437930),
    (0x0A5,'REL32','??$rotate_xy@UVector3@th20@@@th20@@YAXAAUVector3@0@ABU10@M@Z',0x00458FA0),
    (0x0B0,'REL32','??0Vector3@th20@@QAE@XZ',0x00422E10),
    (0x0C8,'REL32',SYMBOL,0x0044CB80),
    (0x0D4,'REL32','??YVector3@th20@@QAEAAU01@ABU01@@Z',0x004296E0),
    (0x0E2,'REL32','@__security_check_cookie@4',0x005429EE),
)

def verify_original():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,SIZE)
    digest=hashlib.sha256(body).hexdigest()
    assert digest==SHA256,(digest,SHA256)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(instructions)==77,len(instructions)
    assert instructions[-1].address+instructions[-1].size==HEAD+SIZE
    assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str=='4'
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
    assert report['size']==SIZE and report['comparable_bytes']==200
    assert report['matched_comparable_bytes']==200 and report['relocation_field_bytes']==36
    assert not report['first_differences'],report['first_differences']
    solved=tuple(sorted((int(item['offset'],16),item['type'],item['symbol'],
                         int(item['solved_destination'],16)) for item in report['relocations']))
    assert solved==tuple(sorted(EXPECTED_RELOCS)),solved
    return report

def main():
    verify_original()
    print('PASS original whole 236B/77-i386 Animation world-position SHA, RET 4, eight E8 destinations and one physical HIGHLOW field')
    if len(sys.argv)==3 and sys.argv[1]=='--candidate-object':
        verify_candidate(Path(sys.argv[2]))
        print('PASS candidate whole 236/236: 200 ordinary bytes + 36 relocation bytes; all nine original relocation targets exact')
        print('PASS strict structural comparison: zero ordinary-byte differences; recursive parent position, optional inherited rotation and Vector3 composition exact')
    elif len(sys.argv)>1:
        raise SystemExit('usage: verify-animation-world-position-for-spawn236-native.py [--candidate-object OBJECT]')
    else:
        print('ORIGINAL ONLY: pass --candidate-object build/.../AnimationRawWorldPosition236.obj for candidate verification')

if __name__=='__main__':main()
