#!/usr/bin/env python3
"""Whole 2769B original Mode6 game renderer vs maintained natural source.

This NONEXACT focused verifier compiles precisely one source under locked
MSVC and checks complete original call/data *roles*, true switch data and
original lengths. It DOES NOT create an accepted exact parent unit or claim
native byte equality; independent original PE census is authoritative.
"""
from collections import Counter
from pathlib import Path
import importlib.util
import struct
import subprocess
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod);return mod
CMP=load('mode6_cmp',ROOT/'scripts/compare-coff-function.py')
NATIVE=load('mode6_pe',ROOT/'scripts/verify-animation-draw-mode6-native.py')
OBJ=ROOT/'build/core843-probe/AnimationDrawMode6Roles.obj'
SYM='?draw_complex_mode6@AnimationDrawDetailedOwner@th20@@QAEHPAVAnimation@2@@Z'
CALL_TARGETS={
 '?multiply_color_128_saturating@th20@@YAEEE@Z':0x0043F520,
 '?multiply_color_255@th20@@YAEEE@Z':0x0043F4F0,
 '??HVector3@th20@@QBE?AU01@ABU01@@Z':0x00429570,
 '?prepare_complex_mode6@AnimationDrawDetailedOwner@th20@@QAEHPAVAnimation@2@@Z':0x00440340,
 '??0Vector3@th20@@QAE@XZ':0x00422E10,
 '??GVector3@th20@@QBE?AU01@ABU01@@Z':0x00429440,
 '?animation_depth@th20@@YAMABUVector3@1@@Z':0x00445700,
 '?render_quad@AnimationDrawModeOwner@th20@@QAEHPAVAnimation@2@H@Z':0x0043F6A0,
 '@__security_check_cookie@4':0x005429EE,
}
DATA_TARGETS={
 '___security_cookie':0x005B25C0,
 '?process_graphics@th20@@3UGraphics@1@A':0x005C4D40,
 '?native_one@th20@@3MB':0x0056C8CC,
 '?native_two@th20@@3MB':0x0056C8D0,
 '?native_quad_vertices@th20@@3PAUSpriteTexturedVertex@1@A':0x005AEF10,
 '?window_state@th20@@3UWindowState@1@A':0x005B6758,
 '?native_448@th20@@3MB':0x0056D7C0,
}


def verify():
    NATIVE.verify()
    source=(ROOT/'src/AnimationDrawMode6.cpp').read_text()
    assert 'AnimationDrawDetailedOwner::draw_complex_mode6(Animation* animation)' in source
    assert 'prepare_complex_mode6(animation)' in source
    assert 'animation_depth(camera_vector)' in source
    assert 'render_quad(animation,2)' in source
    assert 'case 0:' in source and 'case 1:' in source
    assert 'case 2:' in source and 'case 3:' in source and 'case 4:' in source
    assert 'ANM6_TINT' in source and 'ANM6_BLEND_COLOR' in source
    for ch in ('blue','green','red','alpha'):
        assert source.count('native_quad_vertices[0].channels.'+ch+'=')>=3
    # Isolated pinned production source, *no* preexisting canonical providers.
    argv=['nice','-n','15',str(ROOT/'scripts/compile-probe.sh'),
          str(ROOT/'src/AnimationDrawMode6.cpp'),str(OBJ),
          '/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
          '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    subprocess.run(argv,cwd=ROOT,check=True)
    code,relocs=CMP.object_function(OBJ,SYM,NATIVE.COMPARE_SIZE)
    assert len(code)==NATIVE.COMPARE_SIZE==2792
    assert code[NATIVE.SIZE:NATIVE.SIZE+3]==bytes.fromhex('0f1f00')
    nativecode=CMP.pe_bytes_at(CMP.verified_target(),NATIVE.HEAD,NATIVE.COMPARE_SIZE)
    asm=Cs(CS_ARCH_X86,CS_MODE_32)
    original_instr=list(asm.disasm(nativecode[:NATIVE.SIZE],NATIVE.HEAD))
    candidate_instr=list(asm.disasm(code[:NATIVE.SIZE],NATIVE.HEAD))
    assert len(original_instr)==683 and len(candidate_instr)==682
    assert candidate_instr[-1].address+candidate_instr[-1].size==NATIVE.HEAD+NATIVE.SIZE
    assert candidate_instr[-1].mnemonic=='ret' and candidate_instr[-1].op_str=='4'
    assert candidate_instr[2].mnemonic=='sub' and candidate_instr[2].op_str=='esp, 0x70'
    assert len([r for r in relocs if r['type']=='REL32'])==28
    assert len([r for r in relocs if r['type']=='DIR32' and r['offset']<NATIVE.SIZE])==78
    table_rels=sorted((r for r in relocs if r['type']=='DIR32' and r['offset']>=NATIVE.TABLE-NATIVE.HEAD),key=lambda r:r['offset'])
    assert len(table_rels)==5
    assert [r['offset'] for r in table_rels]==[NATIVE.TABLE-NATIVE.HEAD+i*4 for i in range(5)]
    assert all(r['symbol'].startswith('$LN') and r['addend']==0 for r in table_rels)
    assert all((NATIVE.TABLE_TARGETS[i]==NATIVE.TABLE_TARGETS[j])==
               (table_rels[i]['symbol']==table_rels[j]['symbol'])
               for i in range(5) for j in range(5))
    calls=[r for r in relocs if r['type']=='REL32']
    roles=[]
    for row in calls:
        assert row['symbol'] in CALL_TARGETS and row['addend']==0
        assert code[row['offset']-1]==0xE8
        roles.append(CALL_TARGETS[row['symbol']])
    assert roles==list(NATIVE.CALL_SITES.values())
    native_e8_offsets=list(NATIVE.CALL_SITES)
    match_calls=sum(native_e8_offsets[i]==calls[i]['offset']-1 for i in range(len(calls)))
    assert match_calls>=6 and native_e8_offsets[:6]==[r['offset']-1 for r in calls[:6]]
    body_roles=[]
    body_pairs=set()
    orig=load('source_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
    pe,_=orig.verified_target()
    base,sections=orig.parse_sections(pe)
    original_data={p-NATIVE.HEAD:struct.unpack('<I',orig.raw_at(pe,base,sections,p,4))[0]
        for p in orig.physical_highlow(pe,base,sections)
        if NATIVE.HEAD<=p<NATIVE.HEAD+NATIVE.SIZE}
    assert len(original_data)==78
    for row in relocs:
        if row['type']!='DIR32' or row['offset']>=NATIVE.SIZE:continue
        sym=row['symbol'];offset=row['offset']
        if sym.startswith('$LN'):
            target=NATIVE.TABLE
        else:
            assert sym in DATA_TARGETS,(hex(offset),sym)
            target=(DATA_TARGETS[sym]+row['addend'])&0xffffffff
        body_roles.append(target)
        body_pairs.add((offset,target))
    assert Counter(body_roles)==NATIVE.DATA_TARGETS
    matched_physical=len(body_pairs&set(original_data.items()))
    assert matched_physical>=8
    # Structural and role convergence is not whole-byte exact: the source
    # still has different stack lifetime, opcodes and relocation locations.
    ignored=set()
    for r in relocs:
        ignored.update(range(r['offset'],r['offset']+4))
    nonreloc_equal=sum(code[i]==nativecode[i] for i in range(NATIVE.COMPARE_SIZE)
                       if i not in ignored)
    assert nonreloc_equal<NATIVE.COMPARE_SIZE-len(ignored)
    print(f'PASS complete original-sized source contribution {len(code)}B: {NATIVE.SIZE}B executable +3B NOP +5 real mode pointers, original five-case alias partitions')
    print('PASS all 28 E8 target identities/multiplicities in original native call order (first six sites exact)')
    print(f'PASS 78/78 original in-body HIGHLOW destination-role multiplicities, {matched_physical}/78 exact site-and-target pairs; 5/5 table pointer offset positions')
    print(f'NONEXACT whole C++ game parent: candidate {len(candidate_instr)} x86, frame 0x70 vs original 683 x86/frame 0x64; {nonreloc_equal}/{NATIVE.COMPARE_SIZE-len(ignored)} nonrelocation bytes concordant')
    print('NO original 2769B game parent exact credit; no all-graph cold replay')


if __name__=='__main__':verify()
