#!/usr/bin/env python3
"""Pin the original 500B Bomb start and compare a natural 498B C++ candidate.

Role and NOP-stripped audits are DIAGNOSTIC. They never assert canonical exact.
"""
from __future__ import annotations
import argparse
import hashlib
import importlib.util
from pathlib import Path
import re
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def import_one(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/filename)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module
pe=import_one('pulse_pe','verify-animation-draw-boss-native.py')
cf=import_one('pulse_coff','compare-coff-function.py')
HEAD=0x00478C00
SIZE=500
SHA='dec0186ecedcfa5c45ac9391b6f264ccf7a9abd514a7c8a2a9c2330c721602f4'
SYMBOL='?start@NativeBombPulse@th20@@UAEHH@Z'
NOPS=(0x77,0xF2)
ORIGINAL_CALLS=[
(0x016,0x00422E10),(0x01D,0x00460830),(0x027,0x00460850),
(0x064,0x00452F20),(0x072,0x00426D70),(0x07A,0x00460830),
(0x084,0x00421810),(0x0B1,0x004790E0),(0x0D4,0x00450850),
(0x0ED,0x0044F100),(0x0F5,0x00460830),(0x0FF,0x00421810),
(0x12C,0x004790E0),(0x149,0x00450850),(0x15F,0x0044F100),
(0x17F,0x00478EA0),(0x189,0x00487BB0),(0x190,0x00460830),
(0x1A0,0x00479060),(0x1A7,0x00478060),(0x1B7,0x00477F40),
(0x1C9,0x00425090),(0x1D3,0x00460830),(0x1DD,0x004790A0),
(0x1E9,0x005429EE)]
ORIGINAL_DATA=[
(0x007,0x005B25C0),(0x049,0x0056E0F8),(0x051,0x0056C8D0),
(0x06E,0x005BA830),(0x0A6,0x0056FB24),(0x0E6,0x00478380),
(0x121,0x0056FB24),(0x158,0x00478380)]
CALL_ROLE={
    '??0Vector3@':0x00422E10,
    '?player@':0x00460830,
    '?position_ref@Player@':0x00460850,
    '??4Angle@':0x00452F20,
    '?request_effect@SoundInf@':0x00426D70,
    '?animation_file_ref@Player@':0x00421810,
    '?spawn@AnimationFile@':0x004790E0,
    '?bind_owner_450850@':0x00450850,
    '?set_entry_callback_forward_44f100@':0x0044F100,
    '?card@':0x00478EA0,
    '?refresh_487bb0@':0x00487BB0,
    '?set_invulnerability_479060@':0x00479060,
    '?enemy_controller@':0x00478060,
    '?advance_477f40@':0x00477F40,
    '?create_bomb_pulse_auxiliary_425090@':0x00425090,
    '?mark_bomb_used_4790a0@':0x004790A0,
    '@__security_check_cookie@':0x005429EE,
}
DATA_ROLE={
    '___security_cookie':0x005B25C0,
    '?native_negative_pi@':0x0056E0F8,
    '?native_two@':0x0056C8D0,
    '?process_sound@':0x005BA830,
    '$SG':0x0056FB24,
    '?bomb_pulse_animation_callback_478380@':0x00478380,
}
def mapped(symbol,roles):
    matches=[dest for prefix,dest in roles.items() if symbol.startswith(prefix)]
    assert len(matches)==1,(symbol,matches)
    return matches[0]

def verify(candidate_object:Path|None):
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    original=pe.raw_at(image,base,sections,HEAD,SIZE)
    assert hashlib.sha256(original).hexdigest()==SHA
    assert struct.unpack('<I',pe.raw_at(image,base,sections,0x0056FB10,4))[0]==HEAD
    assert pe.raw_at(image,base,sections,0x0056FB24,5)==b'pl01\0'
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,0))
    assert len(ins)==153 and ins[-1].address+ins[-1].size==SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
    calls=[(inst.address,(HEAD+inst.address+5+struct.unpack_from('<i',inst.bytes,1)[0])&0xffffffff)
         for inst in ins if inst.size==5 and inst.bytes[0]==0xE8]
    assert calls==ORIGINAL_CALLS
    real_highlow=pe.physical_highlow(image,base,sections)
    data=[(a-HEAD,struct.unpack('<I',pe.raw_at(image,base,sections,a,4))[0])
          for a in sorted(real_highlow) if HEAD<=a<HEAD+SIZE]
    assert data==ORIGINAL_DATA
    assert [i.address for i in ins if i.mnemonic=='nop']==list(NOPS)
    print('PASS independent original vtable 0x0056FB10 -> 0x00478C00, 500B/153-i386, ret 4')
    print('PASS SHA-pinned complete 25 native E8 sites/targets and 8 real HIGHLOW fields')
    print('PASS native pl01 string and two real compiler NOP instruction sites 0x77/0xF2')
    if candidate_object is None:
        print('ORIGINAL ONLY: no source exactness asserted')
        return
    try:
        body,rel=cf.object_function(candidate_object,SYMBOL,SIZE)
    except ValueError as exc:
        match=re.search(r'complete COFF contribution is (\d+) bytes',str(exc))
        if not match:raise
        body,rel=cf.object_function(candidate_object,SYMBOL,int(match.group(1)))
    candidate_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
    compiled_calls=[i.address for i in candidate_ins if i.size==5 and i.bytes[0]==0xE8]
    cr=sorted((r for r in rel if r['type']=='REL32'),key=lambda r:r['offset'])
    dr=sorted((r for r in rel if r['type']=='DIR32'),key=lambda r:r['offset'])
    assert len(candidate_ins)==151 and len(body)==498
    assert len(compiled_calls)==len(cr)==len(ORIGINAL_CALLS)==25
    assert len(dr)==len(ORIGINAL_DATA)==8
    assert [r['offset'] for r in cr]==[x+1 for x in compiled_calls]
    assert all(mapped(r['symbol'],CALL_ROLE)==dest for (_,dest),r in zip(ORIGINAL_CALLS,cr))
    assert all(mapped(r['symbol'],DATA_ROLE)==dest for (_,dest),r in zip(ORIGINAL_DATA,dr))
    assert candidate_ins[-1].mnemonic=='ret' and candidate_ins[-1].op_str=='4'
    stripped=bytes(value for i,value in enumerate(original) if i not in NOPS)
    assert len(stripped)==len(body)==498
    original_relocations=set()
    candidate_relocations=set()
    for off,_ in ORIGINAL_CALLS:original_relocations.update(range(off+1,off+5))
    for off,_ in ORIGINAL_DATA:original_relocations.update(range(off,off+4))
    for r in rel:candidate_relocations.update(range(r['offset'],r['offset']+4))
    preserved=[(new_off,old_off) for new_off,old_off in enumerate(i for i in range(SIZE) if i not in NOPS)
               if new_off not in candidate_relocations and old_off not in original_relocations]
    assert len(preserved)==366
    assert all(body[new_off]==original[old_off] for new_off,old_off in preserved)
    matching_call_sites=sum(a==b for (a,_),b in zip(ORIGINAL_CALLS,compiled_calls))
    print('PASS candidate native call-role sequence 25/25, native data-role sequence 8/8')
    print(f'PASS {len(preserved)}/{len(preserved)} ordinary bytes after ORIGINAL-only two NOP omissions')
    print(f'PASS source-generated candidate {len(body)}B/{len(candidate_ins)} i386, {matching_call_sites}/25 native E8 sites unchanged')
    print('SOURCE PRESENT NONEXACT: two original NOP bytes are absent. No unit, no exact credit.')

def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--candidate-object',type=Path)
    ns=ap.parse_args()
    verify(ns.candidate_object)
if __name__=='__main__':main()
