#!/usr/bin/env python3
"""Attest five full Card start / HUD originals and their true parent call graph.

The 1,896-byte Card::start_spell parent remains separate, source-absent and
uncredited. Never derive a native relocation role from a compared COFF field.
"""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('card_start_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('card_start_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
PARENT=0x00487C30
PARENT_SIZE=1896
PARENT_SHA='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
SPECS={
 'flags_clear':(0x004888C0,29,12,'856abb234189b67f519618adc42a488d98ef1ed0836952a75ca94c25d92c801b',
                '?clear_capture_effect_flag_4888c0@NativeCardStartFlagsView@th20@@QAEXXZ',{},[0xAB]),
 'bit9':(0x00488960,42,16,'b969b9e7121dcdb2b15423a5b3c41b3e8f7b4be3c9f8f558972142af82615e4a',
          '?set_spell_flag9_488960@NativeCardStartFlagsView@th20@@QAEXI@Z',{},[0x68D]),
 'attempt_counter':(0x00488590,61,18,'45c493c9cd81097189b52c9b6fea4f7487c0514646e9c3544bbb011672b360d1',
                    '?increment_attempt_488590@NativeSpellRecordView@th20@@QAEXH@Z',{},[0x14B,0x1AA]),
 'vm_start':(0x004888E0,22,11,'07a6d1f91b46c744862361711aabef50de01add96055ea644505049bb62a4752',
              '?start_stage_4888e0@NativeHudAnimationView@th20@@QAEXXZ',{0x0C:0x00477450},[]),
 'hud_start':(0x00488A60,71,24,'5e8c2f0a39aee9ff508f780a945b2a22689cbc2ec92652ada1b5c653cef0c587',
                '?start_spell_effects_488a60@NativeCardHudView@th20@@QAEXXZ',
                {0x19:0x00414580,0x20:0x004888E0,0x36:0x00414580,0x3D:0x004888E0},[0x1B6]),
}
def calls(instructions,head):
    return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in instructions if i.size==5 and i.bytes[0]==0xe8}
def verify(obj):
    image,_=pe.verified_target()
    base,secs=pe.parse_sections(image)
    hl=pe.physical_highlow(image,base,secs)
    parent=pe.raw_at(image,base,secs,PARENT,PARENT_SIZE)
    assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
    parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
    assert len(parent_ins)==512 and parent_ins[-1].address+parent_ins[-1].size==PARENT+PARENT_SIZE
    assert (parent_ins[-1].mnemonic,parent_ins[-1].op_str)==('ret','0x10')
    parent_calls=calls(parent_ins,PARENT)
    assert len(parent_calls)==62
    assert len([x for x in hl if PARENT<=x<PARENT+PARENT_SIZE])==26
    print('PASS original Card start 1,896B /512 i386, 62 true E8, 26 PE HIGHLOW (parent still SOURCE-ABSENT)')
    for name,(head,size,count,sha,symbol,e8,parents) in SPECS.items():
        body=pe.raw_at(image,base,secs,head,size)
        assert hashlib.sha256(body).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
        assert len(ins)==count and ins[-1].address+ins[-1].size==head+size
        assert ins[-1].mnemonic=='ret'
        assert calls(ins,head)==e8,(name,calls(ins,head),e8)
        assert not any(head<=x<head+size for x in hl)
        assert [offset for offset,target in parent_calls.items() if target==head]==parents
        if name=='vm_start':
            assert pe.raw_at(image,base,secs,head+size,10)==b'\xCC'*10
        print(f'PASS immutable original {name} {size}B/{count} i386, {len(e8)} E8 and {len(parents)} real Card parent calls')
        if obj:
            report=coff.compare(obj,symbol,head,size)
            assert report['result']=='structural-exact'
            assert report['matched_comparable_bytes']==size-4*len(e8)
            assert {(int(r['offset'],16)-1,int(r['solved_destination'],16)) for r in report['relocations']}==set(e8.items())
            print(f'PASS natural C++20 {name}: full {size}/{size} native body and {len(e8)} independently original relocation roles')
    print('The enclosing Card start 1,896B is not accepted merely because five children are exact')
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
    a=p.parse_args();verify(a.candidate_object)
