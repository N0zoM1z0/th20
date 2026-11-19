#!/usr/bin/env python3
"""Whole-original and canonical candidate proof for recursive AnimationFile child spawn."""
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

pe=load('spawn_update_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('spawn_update_coff','scripts/compare-coff-function.py')
HEAD=0x004512B0
SIZE=619
SHA256='63f83e94895260f13475b978a0d7d2b230b17c88a352aadd8b2a2a3751b7c3f1'
SYMBOL='?spawn_child_and_update@AnimationFile@th20@@QAE?AUAnimationHandle@2@HPAVAnimation@2@I@Z'
LOCKS='?process_locks@th20@@3VLockRegistry@1@A'
POOL='?current_animation_pool@th20@@3PAUAnimationPoolOwner@1@A'
EXPECTED_CALLS=(
    (0x032,0x0040C310),(0x03B,0x0040B730),(0x05C,0x0044C9B0),
    (0x07B,0x00438B70),(0x124,0x0044CB80),(0x16F,0x0042B5D0),
    (0x177,0x00425CC0),(0x1AD,0x0044B890),(0x1E3,0x0044B8E0),
    (0x219,0x0044B840),(0x232,0x0044B7F0),(0x248,0x0040B900),
    (0x260,0x005429EE),
)
EXPECTED_HIGHLOW=(0x006,0x015,0x02E,0x058)
EH='__ehhandler$'+SYMBOL
EXPECTED_RELOCS=(
    (0x006,'DIR32',EH,0x0056824D),
    (0x015,'DIR32','___security_cookie',0x005B25C0),
    (0x02E,'DIR32',LOCKS,0x005C0240),
    (0x033,'REL32','?slot@LockRegistry@th20@@QAEAAVrecursive_mutex@std@@I@Z',0x0040C310),
    (0x03C,'REL32','??0?$lock_guard@Vrecursive_mutex@std@@@std@@QAE@AAVrecursive_mutex@1@@Z',0x0040B730),
    (0x058,'DIR32',POOL,0x005C0028),
    (0x05D,'REL32','?allocate_animation@AnimationPoolOwner@th20@@QAEPAVAnimation@2@XZ',0x0044C9B0),
    (0x07C,'REL32','?apply_template@AnimationFile@th20@@QAEXPAVAnimation@2@H@Z',0x00438B70),
    (0x125,'REL32','?world_position_for_spawn@Animation@th20@@QAEAAUVector3@2@AAU32@@Z',0x0044CB80),
    (0x170,'REL32','?update@Animation@th20@@QAEHXZ',0x0042B5D0),
    (0x178,'REL32','??0AnimationHandle@th20@@QAE@XZ',0x00425CC0),
    (0x1AE,'REL32','?spawn_flag6_44b890@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B890),
    (0x1E4,'REL32','?spawn_flag4_44b8e0@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B8E0),
    (0x21A,'REL32','?spawn_flag2_44b840@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B840),
    (0x233,'REL32','?spawn_normal_44b7f0@NativeSpawnRendererView@th20@@QAE?AUAnimationHandle@2@PAVAnimation@2@@Z',0x0044B7F0),
    (0x249,'REL32','??1?$lock_guard@Vrecursive_mutex@std@@@std@@QAE@XZ',0x0040B900),
    (0x261,'REL32','@__security_check_cookie@4',0x005429EE),
)

def verify_original():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,SIZE)
    digest=hashlib.sha256(body).hexdigest()
    assert digest==SHA256,(digest,SHA256)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(instructions)==186,len(instructions)
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
    assert report['size']==SIZE and report['comparable_bytes']==551
    assert report['matched_comparable_bytes']==551 and report['relocation_field_bytes']==68
    assert not report['first_differences'],report['first_differences']
    solved=tuple(sorted((int(item['offset'],16),item['type'],item['symbol'],
                         int(item['solved_destination'],16)) for item in report['relocations']))
    assert solved==tuple(sorted(EXPECTED_RELOCS)),solved
    return report

def main():
    verify_original()
    print('PASS original whole 619B/186-i386 recursive child-spawn SHA, RET 0x10, 13 E8 destinations and four physical HIGHLOW fields')
    if len(sys.argv)==3 and sys.argv[1]=='--candidate-object':
        verify_candidate(Path(sys.argv[2]))
        print('PASS candidate whole 619/619: 551 ordinary bytes + 68 relocation bytes; all 17 original relocation targets exact')
        print('PASS strict structural comparison: zero ordinary-byte differences; template, recursive VM update, parent transform and four Renderer modes exact')
    elif len(sys.argv)>1:
        raise SystemExit('usage: verify-animation-file-spawn-child-update619-native.py [--candidate-object OBJECT]')
    else:
        print('ORIGINAL ONLY: pass --candidate-object build/.../AnimationFileSpawnChildUpdate619.obj for candidate verification')

if __name__=='__main__':
    main()
