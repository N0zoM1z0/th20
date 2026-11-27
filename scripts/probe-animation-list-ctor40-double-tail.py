#!/usr/bin/env python3
"""Compile and verify the maintained two-phase 40B Animation list constructor.

The constructor expresses a natural member initializer plus a constructor-body
invariant assignment. The verifier requires the original two tail stores and
reports the two remaining ModRM differences; it never grants exactness credit.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import subprocess
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
SYMBOL='??0?$IntrusiveList@VAnimation@th20@@@th20@@QAE@XZ'
HEAD=0x00418A50
SIZE=40
FLAGS=['/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl',
       '/arch:SSE2','/fp:precise','/sdl','/EHsc']


def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    assert spec.loader
    spec.loader.exec_module(module)
    return module


pe=load('ctor_native_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('ctor_native_coff','scripts/compare-coff-function.py')
original_helpers=load('ctor_original_helpers','scripts/verify-animation-renderer-link-frontier-native.py')


def main():
    original_helpers.verify(None)
    image,_=pe.verified_target()
    base,secs=pe.parse_sections(image)
    original=pe.raw_at(image,base,secs,HEAD,SIZE)
    assert hashlib.sha256(original).hexdigest()=='2ff50d0ce1b86ffa1cf0150cfe4b8edbc22c858913354421c9ac2442c048f830'
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
    assert len(ins)==16
    # These two genuine native writes target the SAME semantic 24B list's
    # tail pointer, and are the only basis for the C++ body hypothesis.
    stores=[i for i in ins if i.mnemonic=='mov' and '+ 0x14]' in i.op_str]
    assert len(stores)==2 and stores[0].op_str=='dword ptr [ecx + 0x14], eax'
    assert stores[1].op_str=='dword ptr [eax + 0x14], edx'
    original_calls=[i for i in ins if i.size==5 and i.bytes[0]==0xe8]
    assert len(original_calls)==1
    assert original_calls[0].address-HEAD==0x0A
    assert HEAD+0x0A+5+struct.unpack_from('<i',original_calls[0].bytes,1)[0]==0x00418A10

    header=(ROOT/'src/IntrusiveListAnimation.hpp').read_text()
    assert 'tail(this) { tail=this; }' in header, 'maintained two-phase constructor source changed'
    output=ROOT/'build/gptweb-list-ctor40/DoubleTailResearch.obj'
    output.parent.mkdir(parents=True,exist_ok=True)
    subprocess.run([str(ROOT/'scripts/repo-python'),
        str(ROOT/'scripts/compile-probe.py'),
        str(ROOT/'probes/AnimationRendererLinkFrontier.cpp'),str(output),*FLAGS],cwd=ROOT,check=True)
    original_helpers.verify(output)
    body,rels=cf.object_function(output,SYMBOL,SIZE)
    assert len(rels)==1 and rels[0]['offset']==0x0B and rels[0]['type']=='REL32'
    actual=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
    assert len(actual)==16
    assert [i.mnemonic for i in actual]==[i.mnemonic for i in ins]
    print('PASS maintained natural C++ constructor: original 40B/16-instruction extent and two tail stores')
    print('NONEXACT: two ModRM register-direction differences remain; no strict head/byte credit')


if __name__=='__main__':main()
