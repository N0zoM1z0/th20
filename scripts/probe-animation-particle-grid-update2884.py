#!/usr/bin/env python3
"""Compile and report NONEXACT research source for 2884B particle Update.

Never declares or submits a canonical match. Original PE byte and call/data
roles are separately hash-attested by verify-animation-particle-grid-update2884-native.py.
"""
from __future__ import annotations
import importlib.util
import subprocess
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'probes/AnimationParticleGridUpdate2884Frontier.cpp'
OBJECT=ROOT/'build/gptweb-particle2884-probe/ParticleUpdate2884Research.obj'
SYMBOL='?update@NativeParticleGridGroup@th20@@UAEHXZ'
FLAGS=['/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc']

def main():
    subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-animation-particle-grid-update2884-native.py')],cwd=ROOT,check=True)
    OBJECT.parent.mkdir(parents=True,exist_ok=True)
    subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(OBJECT),*FLAGS],cwd=ROOT,check=True)
    spec=importlib.util.spec_from_file_location('cf',ROOT/'scripts/compare-coff-function.py')
    cf=importlib.util.module_from_spec(spec);spec.loader.exec_module(cf)
    try:
        cf.object_function(OBJECT,SYMBOL,2884)
    except ValueError as exc:
        import re
        match=re.search(r'complete COFF contribution is (\d+) bytes',str(exc))
        if not match:raise
        size=int(match.group(1))
    else:
        size=2884
    raw,relocations=cf.object_function(OBJECT,SYMBOL,size)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,0))
    calls=sum(q['type']=='REL32' for q in relocations)
    data=sum(q['type']=='DIR32' for q in relocations)
    print(f'RESEARCH ONLY: compiled {len(raw)}B/{len(instructions)} i386, {calls} REL32/{data} DIR32')
    print('ORIGINAL IMMUTABLE: 2884B/768 i386, 99 E8/25 PE HIGHLOW')
    if (len(raw)!=2884 or len(instructions)!=768):
        print('CORRECT STATUS: NONEXACT; no config/match-units.toml entry, no authored-game credit')
    else:
        print('SAME LENGTH IS NOT EXACT: verify every byte and native relocation target before acceptance')

if __name__=='__main__':main()
