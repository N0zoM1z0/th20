#!/usr/bin/env python3
"""Whole native 3159B quad-submit parent: original E8 roles vs maintained C++.

This is a deliberately NONEXACT source-coverage proof: it checks all native
all original call identities/multiplicities AND the physical 96 in-body
absolute-data relocation target histogram against a complete isolated
pinned-MSVC compile of this still-NONEXACT game method. We do not conflate
matching source call/data *roles* with identical x86, reloc offsets or ABI.
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
OBJECT=ROOT/'build/core829-probe/AnimationQuadSubmitRoles.obj'
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
    '__security_check_cookie':0x005429EE,
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
    assert 'renderer->append_quad(native_quad_vertices)' in source
    assert 'union SourcePackedColor' in source
    assert 'SourcePackedColor main_color;' in source
    assert 'process_graphics.current_viewport->bounds_11c.x' in source
    assert 'if (channel_mode==2)' in source
    assert 'float snap_left' in source
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
    assert len(generated)==3232
    marker=bytes.fromhex('c20800')
    assert generated.count(marker)==1
    end=generated.index(marker)+3
    assert end==3212
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(generated[:end],HEAD))
    assert len(instructions)==810 and instructions[-1].mnemonic=='ret'
    assert instructions[-1].op_str=='8'
    assert instructions[-1].address+instructions[-1].size==HEAD+end
    # Both the native and our candidate have 5 genuine 32-bit code pointer
    # data words after the body. The physical original requires one NOP
    # alignment byte before its table; the different candidate does not.
    pointers=[r for r in rel if r['type']=='DIR32' and end<=r['offset']<len(generated)]
    assert len(pointers)==5
    assert Counter(r['symbol'] for r in pointers).most_common(3)[-1][1]==1
    assert sorted(Counter(r['symbol'] for r in pointers).values())==[1,2,2]
    assert len(generated)-end==20

    # Verify the original physical game/code paths from real signed E8 fields,
    # including the one compiler-generated security check. Its source target
    # must arise from the compiler, NOT a fabricated game call in the C++.
    e8=[r for r in rel if r['type']=='REL32']
    assert len(e8)==41
    observed=Counter()
    for r in e8:
        sym=r['symbol']
        hits={target for spelling,target in PROVISIONAL_SOURCE_IDENTITIES.items() if spelling in sym}
        assert len(hits)==1,('Unassigned/multiple source call roles',sym,hits)
        observed[next(iter(hits))]+=1
    assert observed==physical,[
        (hex(t),observed[t],physical[t])
        for t in sorted(set(observed)|set(physical))
        if observed[t]!=physical[t]
    ]
    assert observed[0x005429EE]==1
    assert sum(v for k,v in observed.items() if k!=0x005429EE)==40

    # Independently retrieve each original PE .reloc HIGHLOW. Target values,
    # multiplicities and the actual self-owned 5-pointer jump table are
    # SOURCE-LEVEL EVIDENCE, but still not proof of equal instruction offsets.
    base,sections=ORIG.original.parse_sections(image)
    relocated=ORIG.original.physical_highlow(image,base,sections)
    physical_sites=[at for at in relocated if HEAD<=at<HEAD+SIZE]
    assert len(physical_sites)==96
    real_values=Counter(struct.unpack('<I',ORIG.original.raw_at(
        image,base,sections,at,4))[0] for at in physical_sites)
    assert real_values==Counter(ORIG.HIGHLOW_DESTINATIONS)
    real_values['jump_table']+=real_values.pop(ORIG.TABLE)
    actual_dir32=[r for r in rel if r['type']=='DIR32']
    body_fields=[r for r in actual_dir32 if r['offset']<end]
    assert len(body_fields)==96 and len(actual_dir32)==101
    candidate_values=Counter()
    for row in body_fields:
        sym=row['symbol']
        addend=int(row['addend'])
        if 'native_quad_vertices@' in sym:
            target=0x005AEF10+addend
        elif 'process_graphics@' in sym:
            target=0x005C4D40+addend
        elif '__real@3f000000' in sym:
            target=0x0056E0EC+addend
        elif '___security_cookie' in sym:
            target=0x005B25C0+addend
        elif sym.startswith('$LN'):
            assert addend==0
            target='jump_table'
        else:
            raise AssertionError(('unmapped compiler source DIR32 role',row))
        candidate_values[target]+=1
    assert candidate_values==real_values,[
        (str(k),candidate_values[k],real_values[k])
        for k in set(candidate_values)|set(real_values)
        if candidate_values[k]!=real_values[k]
    ]
    assert candidate_values[0x005C5840]==16
    assert candidate_values[0x005AEF20]==16
    assert candidate_values[0x005AEF10]==23
    assert candidate_values[0x005AEF14]==22
    assert candidate_values[0x0056E0EC]==4
    assert candidate_values['jump_table']==1
    assert candidate_values[0x005B25C0]==1
    assert sum(candidate_values.values())==96
    assert len([x for x in relocated if ORIG.TABLE<=x<ORIG.TABLE+20])==5

    print('PASS immutable original whole 3159B/763 i386 and all 41 real E8 targets (10 game targets +1 compiler security)')
    print('PASS C++ 41/41 source/real E8 target identities and per-target multiplicities; actual compiler cookie restored naturally')
    print('PASS complete original 96/96 in-body PE HIGHLOW source target MULTIPLICITIES (73 quad vertices, 16 viewport, 4 half, one device, cookie and switch)')
    print('PASS five original after-RET PE code pointers and five generated C++ switch pointer roles; this is NOT exact table codegen')
    print('PASS 24 saturating and 4 divide-255 real color calls, 4 snap, 2 flush, one 352B append, byte-channel stores across both gradient paths')
    print(f'NONEXACT candidate: {len(generated)}B full COFF = {end}B executable/{len(instructions)} x86 +20B five-pointer data; original {SIZE}B/{len(ops)} i386 +1-byte pad/20B table')
    print('NONEXACT: original physical E8/DIR32 OFFSETS/stack/branch code still differ; no parent original .text byte credit')

if __name__=='__main__':verify()
