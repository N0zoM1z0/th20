#!/usr/bin/env python3
"""Compile four affected i386 objects and verify eight Animation VM opcode leaves."""
from __future__ import annotations
import subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
PROFILES={
 'Color3.cpp':('/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc'),
 'Timer.cpp':('/nologo','/c','/std:c++20','/Od','/Ob0','/GS-','/Gy','/Zl','/arch:SSE2','/fp:precise'),
 'Interpolation.cpp':('/nologo','/c','/std:c++20','/Od','/Ob0','/GS-','/Gy','/Zl','/arch:SSE2','/fp:precise'),
 'AnimationParameters.cpp':('/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc'),
}
OBJECTS={'Color3.cpp':'Color3.obj','Timer.cpp':'Timer.obj','Interpolation.cpp':'Interpolation.obj','AnimationParameters.cpp':'AnimationParameters.obj'}
def main():
 subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-animation-vm-leaves-native.py'),'--original-only'],cwd=ROOT,check=True)
 out=ROOT/'build/gptweb-animation-vm-leaves';out.mkdir(parents=True,exist_ok=True)
 for source,flags in PROFILES.items():subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(ROOT/'src'/source),str(out/OBJECTS[source]),*flags],cwd=ROOT,check=True)
 subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-animation-vm-leaves-native.py')],cwd=ROOT,check=True)
if __name__=='__main__':main()
