#!/usr/bin/env python3
"""Whole native 3159B quad-submit parent: original E8 roles vs maintained C++.

This is a deliberately NONEXACT source-coverage proof: it checks all native
original game call identities/multiplicities against a complete isolated
pinned-MSVC compile of the real candidate, without claiming original byte
identity or inventing the compiler-generated security-cookie call.
"""
from collections import Counter
import importlib.util
from pathlib import Path
import re
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))

def module(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    assert spec and spec.loader
    m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m)
    return m

COFF=module('original_compare',ROOT/'scripts/compare-coff-function.py')
ORIG=module('original_quad',ROOT/'scripts/verify-animation-quad-submit-native.py')
HEAD=0x0043F6A0
SIZE=3159
SOURCE=ROOT/'src/AnimationQuadSubmit.cpp'
OBJECT=ROOT/'build/core808-probe/AnimationQuadSubmit.obj'
SYMBOL='?render_quad@AnimationDrawModeOwner@th20@@QAEHPAVAnimation@2@H@Z'
ORIGINAL_CALLS={
    0x00445B80:4, 0x00437CD0:1, 0x004455C0:2, 0x00412730:1,
    0x00445A00:1, 0x0043F520:24, 0x0043F4F0:4, 0x00445BA0:1,
    0x00446690:1, 0x0043E9B0:1, 0x005429EE:1,
}
PROVISIONAL_SOURCE_IDENTITIES={
    'animation_snap_round':0x00445B80,
    'sprite_data@Animation':0x00437CD0,
    'flush_draws@AnimationPoolOwner':0x004455C0,
    'get_device@Graphics':0x00412730,
    'texture_for_sprite@AnimationQuadSubmitOwner':0x00445A00,
    'multiply_color_128_saturating':0x0043F520,
    'multiply_color_255':0x0043F4F0,
    'prepare_texture_states@AnimationQuadSubmitOwner':0x00445BA0,
    'select_render_color_mode@AnimationQuadSubmitOwner':0x00446690,
    'append_quad@AnimationQuadSubmitOwner':0x0043E9B0,
}

def verify():
    image=COFF.verified_target()
    original=COFF.pe_bytes_at(image,HEAD,SIZE)
    ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
    assert len(ops)==763 and ops[-1].mnemonic=='ret' and ops[-1].op_str=='8'
    physical=Counter((i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                     for i in ops if len(i.bytes)==5 and i.bytes[0]==0xe8)
    assert physical==Counter(ORIGINAL_CALLS) and sum(physical.values())==41
    assert all(SOURCE.exists() for _ in range(1))
    # Exactly one original game method C++ body. The five mode cases are
    # physically source-present even though generated data tables differ.
    source=SOURCE.read_text()
    assert 'AnimationDrawModeOwner::render_quad' in source
    assert all(f'case {i}:' in source for i in range(5))
    assert 'ANM_MUL4_COLOR_INTO' in source
    assert 'renderer->append_quad(quad)' in source
    command=[str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(OBJECT),
             '/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
             '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    subprocess.run(command,cwd=ROOT,check=True)
    try:
        generated,rel=COFF.object_function(OBJECT,SYMBOL,SIZE)
    except ValueError as exc:
        m=re.search(r'complete COFF contribution is (\d+) bytes',str(exc))
        assert m,exc
        generated,rel=COFF.object_function(OBJECT,SYMBOL,int(m.group(1)))
    assert len(generated)==3816
    marker=bytes.fromhex('c20800')
    assert generated.count(marker)==1
    end=generated.index(marker)+3
    assert end==3796
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(generated[:end],HEAD))
    assert len(instructions)==973 and instructions[-1].mnemonic=='ret'
    assert instructions[-1].address+instructions[-1].size==HEAD+end
    # Original switch is an after-body, .reloc-backed five pointer table.
    # Candidate likewise stores five compiler DIR32 jump-table pointers but
    # not the original instruction/table layout.
    pointers=[r for r in rel if r['type']=='DIR32' and end<=r['offset']<len(generated)]
    assert len(pointers)==5
    assert [r['symbol'] for r in pointers]==['$LN43','$LN43','$LN47','$LN47','$LN50']
    assert len(generated)-end==20
    e8=[r for r in rel if r['type']=='REL32']
    assert len(e8)==40
    observed=Counter()
    for r in e8:
        sym=r['symbol']
        hits={target for spelling,target in PROVISIONAL_SOURCE_IDENTITIES.items() if spelling in sym}
        assert len(hits)==1,('Unassigned/multiple source call roles',sym,hits)
        observed[next(iter(hits))]+=1
    original_game=Counter(physical)
    del original_game[0x005429EE]
    assert sum(original_game.values())==40 and len(original_game)==10
    assert observed==original_game,[(hex(t),observed[t],original_game[t])
                                      for t in sorted(set(observed)|set(original_game))
                                      if observed[t]!=original_game[t]]
    print('PASS original complete quad Boss 3159B/763 true x86 and 41 original E8 roles (including 1 compiler security call)')
    print('PASS maintained native C++ method exactly 40/40 original GAME E8 call roles across all 10 physical game target heads')
    print('PASS original per-channel helper counts 24/24 saturation and 4/4 divide-255, 4/4 snap, 2/2 flush, 1/1 six-vertex append')
    print('PASS candidate 5 C++ color-mode jump entry refs distinct from original true PE table, no false instruction counting')
    print(f'NONEXACT candidate: {len(generated)}B COFF, {end}B executable/{len(instructions)} i386 +20B table; original {SIZE}B/{len(ops)} i386')
    print('NONEXACT: original 96 original PE HIGHLOW body references vs different candidate relocations; missing true compiler cookie call')

if __name__=='__main__':verify()
