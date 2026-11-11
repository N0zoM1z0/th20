#!/usr/bin/env python3
"""Evidence-only complete 40B list constructor dual-tail-write C++ hypothesis.

Original TH20 binary performs two same-address tail writes, as independently
observed in original PE and Ghidra. Do NOT put this duplicate in canonical
source without genuine source-ownership evidence and strict native match.
Compiles only one temporary translation unit, never any accepted exact unit.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import subprocess
import sys
import tempfile

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
    old='inline IntrusiveList<Animation>::IntrusiveList() : IntrusiveLink<Animation>(),tail(this) {}'
    assert header.count(old)==1,'owner constructor source changed: rerun source audit'
    candidate=header.replace(old,
        'inline IntrusiveList<Animation>::IntrusiveList() : IntrusiveLink<Animation>(),tail(this) { tail=this; }')
    with tempfile.TemporaryDirectory(prefix='list-ctor40-',dir=ROOT/'.analysis') as directory:
        folder=Path(directory)
        (folder/'IntrusiveListAnimation.hpp').write_text(candidate)
        (folder/'CtorProbe.cpp').write_text('''#include "IntrusiveListAnimation.hpp"
#include "../../src/Animation.hpp"
namespace th20 {
void trigger_ctor_probe() {
    IntrusiveList<Animation> list;
    list.reset(nullptr);
}
}
''')
        output=ROOT/'build/gptweb-list-ctor40/DoubleTailResearch.obj'
        output.parent.mkdir(parents=True,exist_ok=True)
        subprocess.run([str(ROOT/'scripts/repo-python'),
            str(ROOT/'scripts/compile-probe.py'),
            str(folder/'CtorProbe.cpp'),str(output),*FLAGS],cwd=ROOT,check=True)
        body,rels=cf.object_function(output,SYMBOL,SIZE)
        assert len(rels)==1 and rels[0]['offset']==0x0B and rels[0]['type']=='REL32'
        result=cf.compare(output,SYMBOL,HEAD,SIZE)
        assert result['result']=='mismatch'
        assert (result['matched_comparable_bytes'],result['comparable_bytes'])==(34,36)
        assert result['first_differences']==[
            {'offset':'0x16','object':0x48,'target':0x41},
            {'offset':'0x1F','object':0x42,'target':0x50},
        ]
        assert result['relocations'][0]['solved_destination']=='0x00418A10'
        actual=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
        assert len(actual)==16
        assert [i.mnemonic for i in actual]==[i.mnemonic for i in ins]
        print('PASS evidence-only 40B/16-i386 dual-tail C++ hypothesis against full original 40B/16-i386')
        print('PASS 34/36 ordinary bytes, exactly two ModRM register-direction differences +0x16 and +0x1F')
        print('PASS true only E8 at +0x0A -> original folded 63B base constructor 0x00418A10')
        print('NONEXACT, no canonical constructor code change and no authored/duplicate credit')


if __name__=='__main__':main()
