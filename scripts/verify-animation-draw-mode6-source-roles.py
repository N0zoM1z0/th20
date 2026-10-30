#!/usr/bin/env python3
"""Independent whole 2792B Mode6 renderer source/COFF role verification.

Compile only the maintained natural C++ source under pinned MSVC. Verify
complete original 2769B/683-i386 body and after-RET NOP/table, all 28
original E8 physical sites, all 78 body PE HIGHLOW and five table pointers.
This isolated role verifier does not replace fresh canonical strict replay.
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
ORIG_PE=load('original_game',ROOT/'scripts/verify-animation-draw-boss-native.py')
OBJ=ROOT/'build/core844-probe/AnimationDrawMode6Roles.obj'
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
# Independent original case heads and after-RET table base, not byte-field
# relocation solutions. Source COFF label values must corroborate all four.
LOCAL_HEADS={
 '$LN32':0x00441384,'$LN7':0x004409FC,
 '$LN16':0x00440CFE,'$LN24':0x004410D2,
}


def original_coff_labels(obj):
    data=obj.read_bytes()
    _,_,_,symoff,count,_,_=struct.unpack_from('<HHIIIHH',data,0)
    strings_off=symoff+count*18
    strings=data[strings_off:strings_off+struct.unpack_from('<I',data,strings_off)[0]]
    out={};idx=0
    while idx<count:
        offset=symoff+idx*18
        raw,value,section,_,_,aux=struct.unpack_from('<8sIhHBB',data,offset)
        out[CMP.coff_name(raw,strings)]=(value,section)
        idx+=aux+1
    return out


def verify():
    NATIVE.verify()  # all physical original facts before source comparison
    source=(ROOT/'src/AnimationDrawMode6.cpp').read_text()
    assert 'AnimationDrawDetailedOwner::draw_complex_mode6(Animation* animation)' in source
    assert 'prepare_complex_mode6(animation)' in source
    assert 'animation_depth(camera_vector)' in source
    assert 'render_quad(animation,2)' in source
    assert all(f'case {i}:' in source for i in range(5))
    assert 'ANM6_TINT' in source and 'ANM6_BLEND_COLOR' in source
    assert source.index('default: break;')<source.index('case 0:')
    assert 'if ((animation->base.flags.word_04 >> 20) & 1u)' in source
    assert 'if (animation->base.field_4bc >= depth) return -1;' in source
    for channel in ('blue','green','red','alpha'):
        assert source.count('native_quad_vertices[0].channels.'+channel+'=')>=3
    command=['nice','-n','15',str(ROOT/'scripts/compile-probe.sh'),
             str(ROOT/'src/AnimationDrawMode6.cpp'),str(OBJ),
             '/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
             '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    subprocess.run(command,cwd=ROOT,check=True)
    generated,relocs=CMP.object_function(OBJ,SYM,NATIVE.COMPARE_SIZE)
    assert len(generated)==NATIVE.COMPARE_SIZE==2792
    assert generated[NATIVE.SIZE:NATIVE.SIZE+3]==b'\x0f\x1f\x00'
    original=CMP.pe_bytes_at(CMP.verified_target(),NATIVE.HEAD,NATIVE.COMPARE_SIZE)
    original_instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original[:NATIVE.SIZE],NATIVE.HEAD))
    compiler_instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(generated[:NATIVE.SIZE],NATIVE.HEAD))
    assert len(original_instr)==len(compiler_instr)==683
    assert compiler_instr[-1].address+compiler_instr[-1].size==NATIVE.HEAD+NATIVE.SIZE
    assert compiler_instr[-1].mnemonic=='ret' and compiler_instr[-1].op_str=='4'
    assert compiler_instr[2].mnemonic=='sub' and compiler_instr[2].op_str=='esp, 0x64'
    assert Counter(r['type'] for r in relocs)==Counter({'REL32':28,'DIR32':83})
    calls=[r for r in relocs if r['type']=='REL32']
    assert all(r['symbol'] in CALL_TARGETS and r['addend']==0 for r in calls)
    assert {r['offset']-1:CALL_TARGETS[r['symbol']] for r in calls}==NATIVE.CALL_SITES
    assert all(generated[r['offset']-1]==0xE8 for r in calls)
    defined=original_coff_labels(OBJ)
    section=defined[SYM][1]
    assert defined[SYM][0]==0
    assert all(defined.get(sym)==(address-NATIVE.HEAD,section)
               for sym,address in LOCAL_HEADS.items())
    pe,_=ORIG_PE.verified_target()
    base,sections=ORIG_PE.parse_sections(pe)
    native_fields={p-NATIVE.HEAD:struct.unpack('<I',ORIG_PE.raw_at(pe,base,sections,p,4))[0]
        for p in ORIG_PE.physical_highlow(pe,base,sections)
        if NATIVE.HEAD<=p<NATIVE.HEAD+NATIVE.COMPARE_SIZE}
    assert len(native_fields)==83
    compiler_fields={}
    for row in relocs:
        if row['type']!='DIR32':continue
        sym=row['symbol']
        assert sym in DATA_TARGETS or sym in LOCAL_HEADS,(hex(row['offset']),sym)
        target=DATA_TARGETS[sym] if sym in DATA_TARGETS else LOCAL_HEADS[sym]
        compiler_fields[row['offset']]=(target+row['addend'])&0xffffffff
    assert compiler_fields==native_fields
    assert len([offset for offset in compiler_fields if offset<NATIVE.SIZE])==78
    assert [r['offset'] for r in relocs if r['type']=='DIR32' and r['offset']>=NATIVE.SIZE]==[2772,2776,2780,2784,2788]
    ignored=set()
    for row in relocs:ignored.update(range(row['offset'],row['offset']+4))
    concordance=sum(generated[i]==original[i] for i in range(NATIVE.COMPARE_SIZE) if i not in ignored)
    assert concordance==NATIVE.COMPARE_SIZE-len(ignored)==2348
    print('PASS whole 2769B/683 original x86 +3B native NOP+five actual switch pointers (2792B compiler extent)')
    print('PASS 28/28 native E8 physical site/target identity; 78/78 native body and 5/5 actual after-RET PE HIGHLOW site/target identity')
    print('PASS four independently verified source-generated COFF local labels: table base plus three genuine in-body case instruction heads')
    print('PASS 2348/2348 entire non-relocation bytes; 111/111 COFF fields independently identified; strict canonical acceptance separately replayed')


if __name__=='__main__':verify()
