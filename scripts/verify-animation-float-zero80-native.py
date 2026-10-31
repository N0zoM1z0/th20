#!/usr/bin/env python3
"""Attest native 80B float zero-byte test and its exact 202B caller."""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('original_pe_zero80',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('native_zero80_compare',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)

ADDR=0x0045D270
SIZE=80
NATIVE_SHA='5dec067b58b2da92ce0e6da0ce707ece83c1c5f0b94e0ad4db4bf26fba11372b'
PARENT=0x0045D360
PARENT_SIZE=202
PARENT_SHA='a3ed3431101d77c98e7a2868e63e9b40c1ed37da2077dc649190c67ed0d11190'
SYMBOL='?particle_float_is_zero@th20@@YA_NPBM@Z'
EXPECTED_FIELDS={0x07:('DIR32',0x005B25C0),
                 0x23:('REL32',0x00544D77),
                 0x48:('REL32',0x005429EE)}

def original_calls(body,addr):
    return {i.address-addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,addr)
            if i.size==5 and i.bytes[0]==0xe8}

def verify(obj):
    image,_=pe.verified_target()
    base,secs=pe.parse_sections(image)
    body=pe.raw_at(image,base,secs,ADDR,SIZE)
    assert hashlib.sha256(body).hexdigest()==NATIVE_SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDR))
    assert len(ins)==27 and ins[-1].address+ins[-1].size==ADDR+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
    assert original_calls(body,ADDR)=={0x22:0x00544D77,0x47:0x005429EE}
    reloc=pe.physical_highlow(image,base,secs)
    original_dir={a-ADDR:struct.unpack('<I',pe.raw_at(image,base,secs,a,4))[0]
                  for a in reloc if ADDR<=a<ADDR+SIZE}
    assert original_dir=={0x07:0x005B25C0}
    parent=pe.raw_at(image,base,secs,PARENT,PARENT_SIZE)
    assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
    calls=original_calls(parent,PARENT)
    assert calls[0x43]==ADDR and len(calls)==7
    print('PASS immutable original 80B/27-i386 memcmp positive-zero helper; 2 native E8/1 PE HIGHLOW')
    print('PASS immutable original 202B/73-i386 std::fill_n<float> parent; physical +0x43 E8 into exact 80B helper')
    if not obj:return
    result=coff.compare(obj,SYMBOL,ADDR,SIZE)
    assert result['result']=='structural-exact'
    assert result['matched_comparable_bytes']==result['comparable_bytes']==68
    roles={int(r['offset'],16):(r['type'],int(r['solved_destination'],16)) for r in result['relocations']}
    assert roles==EXPECTED_FIELDS,(roles,EXPECTED_FIELDS)
    assert result['first_differences']==[]
    print('PASS complete 80/80 natural C++20: 68/68 nonreloc bytes and all 3 original relocation roles')
    print('Origin likely compiler/library; no new game-authored exact-byte credit')

if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument('--candidate-object',type=Path)
    args=parser.parse_args()
    verify(args.candidate_object)
