#!/usr/bin/env python3
"""Whole-original and canonical candidate proof for AnimationFile::spawn_child."""
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

pe=load('spawn_child_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('spawn_child_coff','scripts/compare-coff-function.py')
HEAD=0x00451050
SIZE=604
SHA256='7ae6f4a1803e1bc53636ad8dd08447e45071364ccee71f8cc037ef7f30e4c650'
SYMBOL='?spawn_child@AnimationFile@th20@@QAE?AUAnimationHandle@2@HPAVAnimation@2@I@Z'
LOCKS='?process_locks@th20@@3VLockRegistry@1@A'
POOL='?current_animation_pool@th20@@3PAUAnimationPoolOwner@1@A'
EXPECTED_CALLS=(
    (0x032,0x0040C310),(0x03B,0x0040B730),(0x05C,0x0044C9B0),
    (0x0B1,0x00422DD0),(0x124,0x004382B0),(0x12C,0x00425CC0),
    (0x162,0x0044B890),(0x198,0x0044B8E0),(0x1CD,0x0044B840),
    (0x1E6,0x0044B7F0),(0x203,0x004494B0),(0x21B,0x004494B0),
    (0x22A,0x00411EE0),(0x239,0x0040B900),(0x251,0x005429EE),
)
EXPECTED_HIGHLOW=(0x006,0x015,0x02E,0x058)
EH='__ehhandler$'+SYMBOL
EXPECTED_RELOCS=(
    (0x006,'DIR32',EH,0x0056872D),
    (0x015,'DIR32','___security_cookie',0x005B25C0),
    (0x02E,'DIR32',LOCKS,0x005C0240),
    (0x033,'REL32','?slot@LockRegistry@th20@@QAEAAVrecursive_mutex@std@@I@Z',0x0040C310),
    (0x03C,'REL32','??0?$lock_guard@Vrecursive_mutex@std@@@std@@QAE@AAVrecursive_mutex@1@@Z',0x0040B730),
    (0x058,'DIR32',POOL,0x005C0028),
    (0x05D,'REL32','?allocate_animation@AnimationPoolOwner@th20@@QAEPAVAnimation@2@XZ',0x0044C9B0),
    (0x0B2,'REL32','??0Vector3@th20@@QAE@MMM@Z',0x00422DD0),
    (0x125,'REL32','?bind_animation@AnimationFile@th20@@QAEXPAVAnimation@2@H0@Z',0x004382B0),
    (0x12D,'REL32','??0AnimationHandle@th20@@QAE@XZ',0x00425CC0),
    (0x163,'REL32','?spawn_flag6_44b890@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B890),
    (0x199,'REL32','?spawn_flag4_44b8e0@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B8E0),
    (0x1CE,'REL32','?spawn_flag2_44b840@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B840),
    (0x1E7,'REL32','?spawn_normal_44b7f0@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B7F0),
    (0x204,'REL32','??AAnimationChildLinks@th20@@QAEAAV?$IntrusiveLink@VAnimation@th20@@@1@H@Z',0x004494B0),
    (0x21C,'REL32','??AAnimationChildLinks@th20@@QAEAAV?$IntrusiveLink@VAnimation@th20@@@1@H@Z',0x004494B0),
    (0x22B,'REL32','?insert_after@?$IntrusiveLink@VAnimation@th20@@@th20@@QAEXPAV12@@Z',0x00411EE0),
    (0x23A,'REL32','??1?$lock_guard@Vrecursive_mutex@std@@@std@@QAE@XZ',0x0040B900),
    (0x252,'REL32','@__security_check_cookie@4',0x005429EE),
)

def verify_original():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,SIZE)
    digest=hashlib.sha256(body).hexdigest()
    assert digest==SHA256,(digest,SHA256)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(instructions)==184,len(instructions)
    assert instructions[-1].address+instructions[-1].size==HEAD+SIZE
    assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str=='0x10'
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
    assert report['size']==SIZE and report['comparable_bytes']==528
    assert report['matched_comparable_bytes']==528 and report['relocation_field_bytes']==76
    assert not report['first_differences'],report['first_differences']
    solved=tuple(sorted((int(item['offset'],16),item['type'],item['symbol'],
                         int(item['solved_destination'],16)) for item in report['relocations']))
    assert solved==tuple(sorted(EXPECTED_RELOCS)),solved
    return report

def main():
    verify_original()
    print('PASS original whole 604B/184-i386 AnimationFile child-spawn SHA, RET 0x10, 15 E8 destinations and four physical HIGHLOW fields')
    if len(sys.argv)==3 and sys.argv[1]=='--candidate-object':
        verify_candidate(Path(sys.argv[2]))
        print('PASS candidate whole 604/604: 528 ordinary bytes + 76 relocation bytes; all 19 original relocation targets exact')
        print('PASS strict structural comparison: zero ordinary-byte differences; four Renderer modes, Animation pool, parent child-list and lock/EH ABI preserved')
    elif len(sys.argv)>1:
        raise SystemExit('usage: verify-animation-file-spawn-child604-native.py [--candidate-object OBJECT]')
    else:
        print('ORIGINAL ONLY: pass --candidate-object build/.../AnimationFileSpawnChild604.obj for candidate verification')

if __name__=='__main__':
    main()
