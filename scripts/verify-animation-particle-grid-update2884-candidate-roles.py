#!/usr/bin/env python3
"""Compare the real 2,884B particle Update's 99 call roles with a NONEXACT COFF.

Source-independent original targets are locked by the PE/native verifier.
Candidate C++ symbols are mapped to original physical callees/data; offsets
may differ while the source is NONEXACT. This never grants whole-game credit.
"""
from __future__ import annotations

import argparse
from collections import Counter
import hashlib
import importlib.util
from pathlib import Path
import re
import struct
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
HEAD=0x0045C360
ORIGINAL_SIZE=2884
SYMBOL='?update@NativeParticleGridGroup@th20@@UAEHXZ'


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


pe=load('grid_update_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('grid_update_coff','scripts/compare-coff-function.py')
original_rules=load('grid_update_original','scripts/verify-animation-particle-grid-update2884-native.py')

# Independent original-PE call destinations (not computed from the candidate).
# These suffixes identify actual source member/signature roles and keep
# collisions such as both folded four-byte array operators distinguishable.
CALL_ROLES={
 '??0Vector3@':0x00422E10,
 '?vector_5bc_ref@':0x0044CB20,
 '?rotation_z_value@':0x00437930,
 '?polar@':0x00439330,
 '??YVector3@':0x004296E0,
 '?variables@Animation@':0x0045D0C0,
 '?changed@Timer@':0x0045D030,
 '?less_than@Timer@':0x00423560,
 '??DTimer@':0x0045C2E0,
 '?particle_effect_info_for_session_437520@':0x00437520,
 '?animation_file@EffectInfo@':0x0045D100,
 '?spawn_45d210@':0x0045D210,
 '??A?$array@UAnimationHandle@':0x00414580,
 '?color_ref_45d0e0@':0x0045D0E0,
 '?resolve@AnimationHandle@':0x0044CED0,
 '?set_packed_color@':0x0044FA10,
 '?slowdown@Animation@':0x004374B0,
 '?set_slowdown@Animation@':0x0045D130,
 '??A?$array@H$0MI':0x00414580,
 '?unit@GameRandom@':0x00429830,
 '?radians@GameRandom@':0x004297D0,
 '??GVector3@':0x00429440,
 '?normalize_vector3_45cf10@':0x0045CF10,
 '?normalize_to_length@':0x004532C0,
 '?configure_45d150@':0x0045D150,
 '??A?$array@UVector3@':0x0045C2C0,
 '?age_45d0a0@':0x0045D0A0,
 '??ETimer@':0x00423540,
 '@__security_check_cookie@':0x005429EE,
}
DATA_ROLES={
 '___security_cookie':0x005B25C0,
 '?native_particle_radius_300@':0x0056EC9C,
 '?native_particle_radius_150@':0x0056EC94,
 '$SG':0x0056EC84, # four original literal "effect" string references
 '?native_polygon_random_5ba4c4@':0x005BA4C4,
 '?native_particle_radius_50@':0x0056EC90,
 '?native_particle_radius_200@':0x0056EC98,
 '?native_particle_radius_100@':0x0056E04C,
 '?native_particle_radius_20@':0x0056EC8C,
}


def map_one(symbol,table):
    matches=[address for prefix,address in table.items() if symbol.startswith(prefix)]
    if len(matches)!=1:
        raise AssertionError(f'unmapped or ambiguous C++ symbol {symbol!r}: {matches}')
    return matches[0]


def candidate_function(object_path):
    # The canonical comparator intentionally refuses a partial 2,884B prefix.
    try:
        return cf.object_function(object_path,SYMBOL,ORIGINAL_SIZE)
    except ValueError as error:
        result=re.search(r'complete COFF contribution is (\d+) bytes',str(error))
        if result is None:raise
        return cf.object_function(object_path,SYMBOL,int(result.group(1)))


def main():
    args=argparse.ArgumentParser(description=__doc__)
    args.add_argument('--candidate-object',type=Path,
        default=Path('build/gptweb-particle2884-probe/ParticleUpdate2884Research.obj'))
    ns=args.parse_args()
    original_rules.verify()
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    original=pe.raw_at(image,base,sections,HEAD,ORIGINAL_SIZE)
    assert hashlib.sha256(original).hexdigest()==original_rules.BODY_SHA256
    old_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
    old_calls=[(i.address-HEAD,(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff)
        for i in old_ins if i.size==5 and i.bytes[0]==0xE8]
    hl=pe.physical_highlow(image,base,sections)
    old_data=[(site-HEAD,struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0])
        for site in sorted(hl) if HEAD<=site<HEAD+ORIGINAL_SIZE]
    assert len(old_calls)==99 and len(old_data)==25
    body,relocs=candidate_function(ROOT/ns.candidate_object)
    instruction_list=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
    candidate_calls=[i.address for i in instruction_list if i.size==5 and i.bytes[0]==0xE8]
    call_reloc=sorted((r for r in relocs if r['type']=='REL32'),key=lambda r:r['offset'])
    data_reloc=sorted((r for r in relocs if r['type']=='DIR32'),key=lambda r:r['offset'])
    assert len(call_reloc)==len(candidate_calls)==len(old_calls)==99
    assert len(data_reloc)==len(old_data)==25
    assert [int(r['offset']) for r in call_reloc]==[i+1 for i in candidate_calls],\
        'all 99 compiler REL32 fields must be real E8 operands'
    for i,(old,ref) in enumerate(zip(old_calls,call_reloc)):
        role=map_one(ref['symbol'],CALL_ROLES)
        assert role==old[1],(i,hex(old[1]),hex(role),ref['symbol'])
    for i,(old,ref) in enumerate(zip(old_data,data_reloc)):
        role=map_one(ref['symbol'],DATA_ROLES)
        assert role==old[1],(i,hex(old[1]),hex(role),ref['symbol'])
    assert pe.raw_at(image,base,sections,0x0056EC84,7).startswith(b'effect\0')
    call_delta=[actual-old[0] for actual,old in zip(candidate_calls,old_calls)]
    same=sum(delta==0 for delta in call_delta)
    assert instruction_list[-1].mnemonic=='ret' and instruction_list[-1].address+instruction_list[-1].size==len(body)
    assert any(i.address==0x26 and i.mnemonic=='push' and i.op_str=='esi'
               for i in instruction_list), 'native ESI lifetime still missing'
    assert any(i.mnemonic=='mov' and i.op_str=='esi, eax'
               for i in instruction_list), 'native age return cross-call register lifetime missing'
    print(f'PASS whole candidate {len(body)}B/{len(instruction_list)}-i386, source-present NONEXACT vs original 2884B/768-i386')
    print('PASS all 99 candidate E8 REL32 symbols and source roles match all original native E8 destinations IN ORDER')
    print('PASS all 25 candidate DIR32 symbols match original PE HIGHLOW role order and physical destinations')
    print(f'PASS native ESI callee-saved lifetime, {same}/99 E8 instruction addresses exactly aligned; abs-delta={sum(abs(x) for x in call_delta)}')
    print('NONCANONICAL: whole strict exactness requires a separate unit, independent of this structural role audit')


if __name__=='__main__':main()
