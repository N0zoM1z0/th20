#!/usr/bin/env python3
"""Verify the shared 66B native intrusive-list prepend frontier without claiming exactness."""
from __future__ import annotations
import hashlib
import importlib.util
import struct
import subprocess
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module
pe=load('intrusive_prepend_pe','scripts/verify-animation-draw-boss-native.py')
coff=load('intrusive_prepend_coff','scripts/compare-coff-function.py')
ADDRESS=0x0044A6B0
SIZE=66
SHA256='773c78d2fa904d530e27b1f0fa76ab56a43e66454e1504d7259462f822399c2b'
SYMBOL='?prepend@?$IntrusiveList@UBullet@th20@@@th20@@QAEXPAV?$IntrusiveLink@UBullet@th20@@@2@@Z'
EXPECTED_CALLS={0x16:0x00411EE0,0x22:0x00412DC0}
EXPECTED_RELOCS=(
    (0x17,'REL32','?insert_after@?$IntrusiveLink@UBullet@th20@@@th20@@QAEXPAV12@@Z'),
    (0x23,'REL32','?set_owner@?$IntrusiveLink@UBullet@th20@@@th20@@QAEXPAU?$IntrusiveList@UBullet@th20@@@2@@Z'),
)
EXPECTED_CALLERS=(
    0x0044B867,0x0044B8BA,0x0047DA7E,0x004811DD,0x00481975,
    0x00483CA3,0x004A8998,0x004C1EEA,0x004C38BC,0x004C3E6B,
    0x004C40AF,0x004C9331,0x0050624A,0x005062B3,0x00506ADB,
)

def main():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    native=pe.raw_at(image,base,sections,ADDRESS,SIZE)
    assert hashlib.sha256(native).hexdigest()==SHA256
    decoded=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,ADDRESS))
    assert len(decoded)==25 and sum(i.size for i in decoded)==SIZE
    calls={i.address-ADDRESS:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in decoded if i.size==5 and i.bytes[0]==0xE8}
    assert calls==EXPECTED_CALLS,calls
    assert decoded[-1].mnemonic=='ret' and decoded[-1].op_str=='4'

    callers=[]
    import pefile
    original=pefile.PE(str(ROOT/'resources/th20.exe'),fast_load=True)
    for section in original.sections:
        if not section.Characteristics & 0x20000000:
            continue
        start=original.OPTIONAL_HEADER.ImageBase+section.VirtualAddress
        data=section.get_data()
        for offset in range(max(0,len(data)-4)):
            if data[offset]==0xE8:
                target=(start+offset+5+struct.unpack_from('<i',data,offset+1)[0])&0xffffffff
                if target==ADDRESS:
                    callers.append(start+offset)
    assert tuple(callers)==EXPECTED_CALLERS,(len(callers),[hex(x) for x in callers])

    obj=ROOT/'build/gptweb-intrusive-prepend/BulletEmitter.obj'
    obj.parent.mkdir(parents=True,exist_ok=True)
    flags=['/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc']
    subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/'src/BulletEmitter.cpp'),str(obj),*flags],cwd=ROOT,check=True)
    candidate,relocations=coff.object_function(obj,SYMBOL,SIZE)
    assert len(candidate)==SIZE
    observed=tuple((int(r['offset']),r['type'],r['symbol']) for r in relocations)
    assert observed==EXPECTED_RELOCS,observed
    relocated=set()
    for offset,kind,_ in EXPECTED_RELOCS:
        assert kind=='REL32'
        relocated.update(range(offset,offset+4))
    mismatches=[i for i in range(SIZE) if i not in relocated and candidate[i]!=native[i]]
    assert mismatches==[0x2C,0x2D,0x2E,0x2F,0x30],mismatches
    comparable=SIZE-len(relocated)
    matched=comparable-len(mismatches)
    assert (matched,comparable)==(53,58)

    source=(ROOT/'src/IntrusiveLink.hpp').read_text()
    assert 'head.insert_after(link);link->set_owner(this);' in source
    assert 'if(tail==static_cast<IntrusiveLink<T>*>(this))tail=link;' in source
    for forbidden in ('__asm','__declspec(naked)','_emit','__nop'):
        assert forbidden not in source
    print('PASS original 66B/25-i386 shared intrusive prepend body SHA-256')
    print('PASS two original E8 roles: IntrusiveLink::insert_after -> 0x411EE0; owner setter -> 0x412DC0')
    print('PASS 15 physical native callers, including BulletEmitter 0x481975 and Animation callers')
    print('PASS natural IntrusiveList<Bullet>::prepend candidate is 66B with both relocation roles')
    print('PARTIAL 53/58 ordinary bytes match; only +0x2C..+0x30 tail-sentinel compare encoding differs')
    print('NO strict exact unit or game-authored byte credit; no assembly, volatile, or padding workaround')

if __name__=='__main__':
    main()
