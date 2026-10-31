#!/usr/bin/env python3
"""Independently attest native 35B glyph-vector insertion call frontier.

Natural C++20 std::pmr::vector<GlyphMaskOffset>::emplace_back(const&)
currently emits 33B/13 instructions and one E8, not this entire original
35B/15 instruction function with two physically distinct E8 targets.
"""
import hashlib
import importlib.util
import struct
import subprocess
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph35_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph35_cmp',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00416330
SHA='bd26f62ba6f30fe4d6e5845561e0cc2ecdd80da8bc771cdcdd260e25109343b4'
PARENT=0x00416420
PARENT_SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
CALLS={0x0B:0x0040B280,0x17:0x00413370}
PARENT_SITES=(0x165,0x4DD)
PREFIX='??$emplace_back@ABV?$array@H$01@'
def calls(ins,head):
    return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
            for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    data=pe.raw_at(image,base,sections,HEAD,35)
    assert hashlib.sha256(data).hexdigest()==SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(data,HEAD))
    assert len(ins)==15 and ins[-1].address+ins[-1].size==HEAD+35
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
    assert calls(ins,HEAD)==CALLS
    assert not any(HEAD<=pos<HEAD+35 for pos in pe.physical_highlow(image,base,sections))
    parent=pe.raw_at(image,base,sections,PARENT,2245)
    assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
    parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
    assert len(parent_ins)==612
    native_parent_calls=calls(parent_ins,PARENT)
    assert tuple(offset for offset,target in native_parent_calls.items() if target==HEAD)==PARENT_SITES
    print('PASS original complete 35B/15-i386 glyph offset-vector insertion, E8 +0x0B/+0x17 to 0x0040B280/0x00413370')
    print('PASS immutable original 2245B/612-i386 compositor E8 +0x165 and +0x4DD to original 35B head')
    obj=ROOT/'build/core1052-canonical/GlyphMaskComposite2245.obj'
    symbols=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
    symbol=next(sym for sym in symbols if sym.startswith(PREFIX))
    candidate,relocations=cm.object_function(obj,symbol,33)
    candidate_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(candidate),0))
    assert len(candidate_ins)==13 and candidate_ins[-1].mnemonic=='ret'
    assert len(relocations)==1
    assert relocations[0]['offset']==0x11 and relocations[0]['type']=='REL32'
    assert '_Emplace_one_at_back' in relocations[0]['symbol']
    print('NONEXACT: natural std::pmr::vector<GlyphMaskOffset>::emplace_back(const&) compiles 33B/13 i386,')
    print('one E8 to _Emplace_one_at_back rather than original two E8 /35B direct call chain')
    print('Original 35B helper SOURCE-PRESENT NONEXACT, no canonical strict or authored-game credit')
if __name__=='__main__': verify()
