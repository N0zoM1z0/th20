#!/usr/bin/env python3
"""Original 1,896B Card start physical CFG versus unfinished typed C++ candidate.

This deliberately does NOT normalize gaps, shorten the native function, or
claim strict exactness for a complete-length experimental candidate.
"""
import argparse
import hashlib
import importlib.util
import re
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('start1896_native',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('start1896_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x00487C30
SIZE=1896
SHA='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
CHILDREN={
 0x0AB:0x004888C0,   # native Card bit7 clear
 0x1D6:0x00478130,  # native Bomb active predicate
 0x30D:0x00486B70,  # typed original Card text capture constructor
 0x325:0x00486800,  # original callable std::function construction
 0x330:0x00470180,  # original locked-by-value ASCII task queue
 0x33F:0x0046ADE0,  # original PMR capture destructor
 0x68D:0x00488960,  # original Card bit9 publication
}
def verify(candidate):
    image,_=pe.verified_target();base,sec=pe.parse_sections(image)
    native=pe.raw_at(image,base,sec,HEAD,SIZE)
    assert hashlib.sha256(native).hexdigest()==SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
    assert len(ins)==512 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x10')
    original_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                    for i in ins if i.size==5 and i.bytes[0]==0xe8}
    original_data={site-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,site,4))[0]
                   for site in pe.physical_highlow(image,base,sec) if HEAD<=site<HEAD+SIZE}
    assert len(original_calls)==62 and len(original_data)==26
    for off,target in CHILDREN.items():assert original_calls[off]==target,(hex(off),hex(original_calls[off]))
    print('PASS immutable original Card start: 1,896B/512 i386, 62 real E8/26 original PE HIGHLOW')
    print('PASS independently original Card bit7, Bomb active, typed text ctor/dtor and Card bit9 E8 locations')
    if candidate:
        # This is a semantic/ABI research probe, *not* a canonical exact unit.
        name='?start_spell@Card@th20@@QAEXHPBDHH@Z'
        for size in (SIZE,1750):
            try:
                source,relocs=coff.object_function(candidate,name,size)
                break
            except ValueError as error:
                if size==SIZE and 'complete COFF contribution is' in str(error):continue
                raise
        cs=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(source),0))
        assert len(source)==1750 and len(cs)==478
        assert len(relocs)==77
        assert sum(r['type']=='REL32' for r in relocs)==61
        assert sum(r['type']=='DIR32' for r in relocs)==16
        assert len(source)!=len(native)
        print('FRONTIER NONEXACT: maintained C++20 Card start 1,750B/478 i386, 61 REL32/16 DIR32 fields')
        print('Original 1,896B callable constructor/111B callback EH and live owner graph not yet reconciled; zero parent strict credit')
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
    a=p.parse_args();verify(a.candidate_object)
