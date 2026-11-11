#!/usr/bin/env python3
"""Two whole Renderer list-update class-key probes and exact-consumer compatibility.

Builds ONLY three isolated probe objects. The original 508B/511B are
complete, relocation-role-resolved, but must NOT be canonically admitted:
a migrated class specialization must preserve every preexisting exact
consumer and class-versus-struct MSVC symbol identity.
"""
from __future__ import annotations

import importlib.util
from pathlib import Path
import re
import struct
import subprocess
import sys
import tomllib

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
FLAGS=['/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc']
OUT=ROOT/'build/gptweb-renderer-class-frontier'


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    assert spec.loader
    spec.loader.exec_module(module)
    return module


cf=load('class_coff','scripts/compare-coff-function.py')
pe=load('class_pe','scripts/verify-animation-draw-boss-native.py')

# These are names of independently identified physical original callees/data;
# never derive a guessed original address by trusting a COFF symbol alone.
ROLE_TARGETS={
    '__ehhandler$':0x00568315,
    '___security_cookie':0x005B25C0,
    '?__autoclassinit2@':0x0040C080,
    '??0?$IntrusiveList@':0x00418A50,
    '?reset@?$IntrusiveList@':0x0044A640,
    '?begin@?$IntrusiveList@':0x00412280,
    '?end@?$IntrusiveList@':0x00412540,
    '?advance@?$IntrusiveIterator@':0x00411C30,
    '?differs@?$IntrusiveIterator@':0x00411BB0,
    '?get@?$IntrusiveIterator@':0x0040C300,
    '?node_access@?$IntrusiveLink@':0x0040F160,
    '?current_animation_pool@':0x005C0028,
    '?queue_retired_animation_44f840@':0x0044F840,
    '?update@Animation@':0x0042B5D0,
    '??1?$IntrusiveIterator@':0x00411B00,
    '?release_animation@AnimationPoolOwner@':0x0044C2F0,
    '@__security_check_cookie@':0x005429EE,
}

PROBES={
    508:{'head':0x00449870,'instructions':152,'ordinary':368,
         'source':'probes/AnimationRendererListUpdate508ClassProbe.cpp',
         'symbol':'?animation_list_update_449870@th20@@YIXPAV?$IntrusiveList@VAnimation@th20@@@1@@Z'},
    511:{'head':0x00449B20,'instructions':153,'ordinary':371,
         'source':'probes/AnimationRendererListUpdate511ClassProbe.cpp',
         'symbol':'?animation_list_update_secondary_449b20@th20@@YIXPAUNativeSpawnRendererView@1@@Z'},
}


def compile_source(source,output):
    output.parent.mkdir(parents=True,exist_ok=True)
    subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/source),str(output),*FLAGS],cwd=ROOT,check=True)


def role_address(symbol):
    matches=[value for prefix,value in ROLE_TARGETS.items() if symbol.startswith(prefix)]
    if len(matches)!=1:
        raise AssertionError(f'unmapped or ambiguous original role: {symbol}: {matches}')
    return matches[0]


def prove_one(n,data,image,base,sections,physical_highlow):
    obj=OUT/f'AnimationList{n}.obj'
    compile_source(data['source'],obj)
    code,relocs=cf.object_function(obj,data['symbol'],n)
    native=pe.raw_at(image,base,sections,data['head'],n)
    original=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,data['head']))
    assert len(original)==data['instructions'] and original[-1].address+original[-1].size==data['head']+n
    calls={i.address-data['head']:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in original if i.size==5 and i.bytes[0]==0xE8}
    assert len(calls)==30
    highlow={addr-data['head']:struct.unpack('<I',pe.raw_at(image,base,sections,addr,4))[0]
             for addr in physical_highlow if data['head']<=addr<data['head']+n}
    assert len(highlow)==5
    expected_fields={(i+1,'REL32',address) for i,address in calls.items()}
    expected_fields.update((i,'DIR32',address) for i,address in highlow.items())
    actual_fields={(int(r['offset']),r['type'],role_address(r['symbol'])) for r in relocs}
    assert len(actual_fields)==len(expected_fields)==35
    assert actual_fields==expected_fields,(actual_fields^expected_fields)
    assert calls[0x30]==0x0040C080  # original missing /sdl class preclear now present
    result=cf.compare(obj,data['symbol'],data['head'],n)
    assert result['result']=='structural-exact'
    assert result['matched_comparable_bytes']==result['comparable_bytes']==data['ordinary']
    assert len(result['first_differences'])==0
    print(f'PASS isolated {n}B/{len(original)}-i386 Renderer Boss: {data["ordinary"]}/{data["ordinary"]} ordinary bytes, 30 independently role-bound E8 and 5 original PE HIGHLOW')


def compatibility():
    """Prove ALL 38 Animation.cpp exact contributions, including true padding."""
    obj=OUT/'AnimationExactCompatibility.obj'
    compile_source('probes/AnimationRendererClassTagExactCompatibilityProbe.cpp',obj)
    with (ROOT/'config/match-units.toml').open('rb') as f:
        units=tomllib.load(f)['units']
    chosen=[(name,unit) for name,unit in units.items()
            if unit['source']=='src/Animation.cpp']
    assert len(chosen)==38,('changed exact scope',len(chosen))
    for name,unit in chosen:
        size=int(unit.get('compare_size',unit['size']))
        result=cf.compare(obj,unit['symbol'],int(unit['target_address']),size)
        assert result['result']=='structural-exact' and result['matched_comparable_bytes']==result['comparable_bytes'],(name,result)
    print('PASS positive compatibility: 38/38 canonical Animation.cpp bodies, including original 5B after-ret padding for ctor/dtor units')
    print('Class-vs-struct mangled parameter symbols in queue retirement and other list consumers still need coherent migration')


def main():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    reloc=pe.physical_highlow(image,base,sections)
    for n,data in PROBES.items():prove_one(n,data,image,base,sections,reloc)
    compatibility()
    print('Only 3 isolated compile-probes: no public template change, no full cold replay')


if __name__=='__main__':main()
