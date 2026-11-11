#!/usr/bin/env python3
"""Original-only evidence for the 51B particle-grid virtual event head.

The game's physical event method is independent of the separate, already
covered 26B folded += helper. Candidate comparison is a convenience; whole
strict admission remains the canonical unit's relocated COFF replay.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))

def module(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/filename)
    m=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m

pe=module('pe_particle_event','scripts/verify-animation-draw-boss-native.py')
cf=module('coff_particle_event','scripts/compare-coff-function.py')
HEAD=0x0045D060
SIZE=51
SHA='37e9d7d0695daa98eab8d5f10b120d932d7192c8727c03cf404fe0990a67e0e4'
SYMBOL='?interrupt@NativeParticleGridGroup@th20@@UAEHH@Z'
HELPER='??YNativeGridTimedDelta@th20@@QAEXH@Z'

def main():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,SIZE)
    assert hashlib.sha256(body).hexdigest()==SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(ins)==18 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
    calls={i.address-HEAD: (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xE8}
    assert calls=={0x25:0x0045C300},calls
    assert [x for x in pe.physical_highlow(image,base,sections) if HEAD<=x<HEAD+SIZE]==[]
    # 13 actual INT3 bytes precede the separate 25B Animation age getter.
    assert pe.raw_at(image,base,sections,HEAD+SIZE,13)==b'\xCC'*13
    assert pe.raw_at(image,base,sections,HEAD+SIZE+13,1)==b'\x55'
    # The native 6-entry polymorphic callback table (slot 4 == event).
    vtable=0x0056EC14
    assert struct.unpack('<I',pe.raw_at(image,base,sections,vtable+4*4,4))[0]==HEAD
    assert vtable+16 in pe.physical_highlow(image,base,sections)
    operations={(i.mnemonic,i.op_str) for i in ins}
    assert ('cmp','dword ptr [ebp - 4], 1') in operations
    assert ('push','0x12c') in operations
    assert ('add','ecx, 0x1930') in operations
    assert ('nop','') in operations
    # Don't credit the folded += as a new physical function.
    forwarded=pe.raw_at(image,base,sections,0x0045C300,26)
    assert hashlib.sha256(forwarded).hexdigest()=='4da6a6a9a426deaf7a07e4ee41dc8d4295d9ee2a296f78f7f022d79cf07a539d'
    f_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(forwarded,0x0045C300))
    assert (f_ins[-1].mnemonic,f_ins[-1].op_str)==('ret','4')
    f_calls={i.address-0x0045C300:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
             for i in f_ins if i.size==5 and i.bytes[0]==0xE8}
    assert f_calls=={0x0E:0x004297A0}
    assert ('nop','') in {(i.mnemonic,i.op_str) for i in f_ins}
    # Real group constructor must directly use the already exact Timer ctor;
    # derived-type source proposals changed this symbol and were rejected.
    ctor_address=0x0045C1F0
    ctor=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(
        pe.raw_at(image,base,sections,ctor_address,172),ctor_address))
    ctor_calls={i.address-ctor_address:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                for i in ctor if i.size==5 and i.bytes[0]==0xE8}
    assert ctor_calls[0x9D]==0x00422D90
    print('PASS original native whole 51B/18-i386 particle event, vtable slot4 and 13 INT3 separators')
    print('PASS original E8+0x25 -> 0x0045C300, zero original HIGHLOW; folded 26B E8 +0x0E -> 0x004297A0')
    print('PASS native 172B group constructor calls Timer ctor 0x00422D90 at E8 +0x9D')
    candidate=ROOT/'build/core1108-canonical/AnimationParticleGridEvent51.obj'
    if candidate.exists():
        result=cf.compare(candidate,SYMBOL,HEAD,SIZE)
        assert result['result']=='structural-exact' and result['matched_comparable_bytes']==47
        assert len(result['relocations'])==1
        assert result['relocations'][0]['solved_destination']=='0x0045C300'
        other=cf.compare(candidate,HELPER,0x0045C300,26)
        assert other['result']=='structural-exact' and other['matched_comparable_bytes']==22
        assert other['relocations'][0]['solved_destination']=='0x004297A0'
        print('PASS candidate 51B/18-i386, 47/47 nonreloc + 26B folded helper 22/22')
        print('NONCREDIT 26B helper: already mapped to native PlayerFeedback folded original head')
    print('Use compare-coff-function.py --unit animation_particle_grid_event_51 for whole strict replay')

if __name__=='__main__':main()
