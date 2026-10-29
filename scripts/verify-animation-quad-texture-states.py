#!/usr/bin/env python3
"""Independent original 2,725B D3D9 texture-state boss evidence + 50-call C++ role census.

Never credit the 2,725B original game function as strict until the *entire*
original x86 body, all real PE relocation fields and the 10-entry afterbody
switch table exactly match pinned MSVC. Only the one candidate source compiles.
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

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,path)
    assert spec and spec.loader
    mod=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod

NATIVE=load('texture_state_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
COFF=load('texture_state_coff',ROOT/'scripts/compare-coff-function.py')
HEAD=0x00445BC0
BODY=2725
COMPLETE=2768
TABLE=0x00446668
ORIGINAL_TABLE=(0x00445D08,0x00445D95,0x00445E22,0x00445EAF,0x00445F68,
                0x00446082,0x00445FF5,0x0044610F,0x004461AE,0x00446256)
E8={0x00412730:46,0x004455C0:4}
SOURCE=ROOT/'src/AnimationQuadTextureStates.cpp'
OBJECT=ROOT/'build/core818-probe/AnimationQuadTextureStates.obj'
SYMBOL='?bind_native_texture_state@AnimationQuadSubmitOwner@th20@@QAEXPAVAnimation@2@@Z'

def verify():
    target,_=NATIVE.verified_target()
    base,sections=NATIVE.parse_sections(target)
    highlow=NATIVE.physical_highlow(target,base,sections)
    original=NATIVE.raw_at(target,base,sections,HEAD,COMPLETE)
    native=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original[:BODY],HEAD))
    assert len(native)==699 and native[-1].address==0x00446662
    assert native[-1].mnemonic=='ret' and native[-1].op_str=='4'
    assert native[-1].address+native[-1].size==HEAD+BODY
    assert original[BODY:BODY+3]==bytes.fromhex('0f1f00')
    assert HEAD+BODY+3==TABLE
    actual_table=tuple(struct.unpack_from('<I',original,BODY+3+4*i)[0] for i in range(10))
    assert actual_table==ORIGINAL_TABLE
    heads={x.address:x for x in native}
    assert all(addr in heads for addr in ORIGINAL_TABLE)
    body_highlow={at for at in highlow if HEAD<=at<HEAD+BODY}
    table_highlow={at for at in highlow if TABLE<=at<TABLE+40}
    assert len(body_highlow)==47
    assert table_highlow=={TABLE+4*i for i in range(10)}
    source_global={at for at in body_highlow if
                   struct.unpack('<I',NATIVE.raw_at(target,base,sections,at,4))[0]==0x005C4D40}
    assert len(source_global)==46
    assert body_highlow-source_global=={0x00445D04}
    assert struct.unpack('<I',NATIVE.raw_at(target,base,sections,0x00445D04,4))[0]==TABLE
    calls=Counter((i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                  for i in native if len(i.bytes)==5 and i.bytes[0]==0xE8)
    assert calls==E8
    assert sum(i.mnemonic=='call' and i.op_str.startswith('dword ptr [ebp -') for i in native)==46
    state_virtual=Counter('SetRenderState' if '+ 0xe4' in i.op_str else 'SetSamplerState'
                          for i in native if i.mnemonic=='mov' and
                          ('+ 0xe4' in i.op_str or '+ 0x114' in i.op_str))
    assert state_virtual=={'SetRenderState':36,'SetSamplerState':10},state_virtual
    assert any(i.mnemonic=='jmp' and '[edx*4 + 0x446668]' in i.op_str for i in native)
    # Genuine original 26B texture preparation wrapper calls this entire
    # 2,725B parent at one original physical E8, not an invented entry.
    wrapper=NATIVE.decoded(target,base,sections,0x00445BA0,26)
    assert len(wrapper)==12 and any(i.address==0x00445BAE and i.mnemonic=='call' and
        i.op_str=='0x445bc0' for i in wrapper)
    for offset in (0x6000E0C,0x6000E12,0x6000E13,0x6000E14):
        assert any(f'+ {offset:#x}' in i.op_str for i in native),hex(offset)
    print('PASS immutable original 2,725B/699 x86 texture-state Boss and physical original complete RET4')
    print('PASS actual 50 native E8: 46 genuine Graphics getter +4 previously strict 192B queue flush')
    print('PASS 47 actual in-body PE HIGHLOW (46 Graphics +one indexed-jump operand), 10 actual after-RET PE HIGHLOW switch entries')
    print('PASS original 36 D3D9 SetRenderState(+0xE4) plus 10 SetSamplerState(+0x114) indirect calls')
    print('PASS 2,768B original total code+three-byte align+ten-entry table, independently real x86 code/data split')

    assert SOURCE.exists()
    source=SOURCE.read_text()
    assert 'void AnimationQuadSubmitOwner::bind_native_texture_state(Animation* animation)' in source
    assert set(int(n) for n in re.findall(r'\bcase (\d+):',source)) == set(range(10))
    assert source.count('D3D_SET_RENDER(')==37 # one macro and 36 real SDK calls
    assert source.count('D3D_SET_SAMPLER(')==11 # one macro and ten real SDK calls
    assert source.count('flush_draws();')==4
    # Crucial source-order original: mode 6 body lies BEFORE mode 5 in .text.
    assert source.index('        case 6:') < source.index('        case 5:')
    assert 'animation->base.flags.bits_08.other_2_3' in source
    assert 'NativeRenderByteA2' in source and 'NativeRenderByteA1' in source
    command=[str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(OBJECT),
             '/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
             '/arch:SSE2','/fp:precise','/sdl','/EHsc']
    subprocess.run(command,cwd=ROOT,check=True)
    candidate,rels=COFF.object_function(OBJECT,SYMBOL,COMPLETE)
    assert len(candidate)==COMPLETE
    code=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(candidate[:BODY],HEAD))
    assert len(code)==699 and code[-1].mnemonic=='ret' and code[-1].op_str=='4'
    assert code[-1].address+code[-1].size==HEAD+BODY
    assert candidate[BODY:BODY+3]==bytes.fromhex('0f1f00')
    assert len(candidate)-BODY==43
    rel_call=[r for r in rels if r['type']=='REL32']
    rel_data=[r for r in rels if r['type']=='DIR32']
    assert len(rels)==107 and len(rel_call)==50 and len(rel_data)==57
    source_calls=Counter()
    for r in rel_call:
        if 'get_device@Graphics' in r['symbol']:
            source_calls[0x00412730]+=1
        elif 'flush_draws@AnimationPoolOwner' in r['symbol']:
            source_calls[0x004455C0]+=1
        else:
            raise AssertionError(('unmapped original game E8',r))
    assert source_calls==calls
    assert len([r for r in rel_data if 'process_graphics@' in r['symbol']])==46
    assert len([r for r in rel_data if r['symbol'].startswith('$LN')])==11
    assert len([r for r in rel_data if TABLE<=HEAD+r['offset']<TABLE+40])==10
    ignored={byte for r in rels for byte in range(r['offset'],r['offset']+4)}
    assert all(candidate[i]==original[i] for i in range(COMPLETE) if i not in ignored)
    patched=bytearray(candidate)
    for r in rels:
        off=int(r['offset']);site=HEAD+off
        assert r['addend']==0
        if r['type']=='REL32':
            assert original[off-1]==0xE8
            destination=(site+4+struct.unpack_from('<i',original,off)[0])&0xffffffff
            assert destination in E8
            value=(destination-(site+4)) & 0xffffffff
        else:
            assert site in highlow
            destination=struct.unpack_from('<I',original,off)[0]
            if off<BODY:
                assert destination in (0x005C4D40,TABLE)
            else:
                assert destination in ORIGINAL_TABLE
            value=destination
        struct.pack_into('<I',patched,off,value)
    assert bytes(patched)==original
    print('PASS original complete renderer source: 2,725/2,725B, 699/699 i386, 50 original E8 +57 real PE HIGHLOW')
    print('PASS all 2,768/2,768 original native code+3 alignment+10 table DWORDs exactly replay after PE-anchored 107 genuine relocations')
    print('SOURCE/PARENT: this 2,725B original game Boss is strict exact; the distinct 3,159B quad submit parent remains NONEXACT')

if __name__=='__main__':verify()
