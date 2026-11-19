#!/usr/bin/env python3
"""Compile and prove the complete native Animation child-spawn world position."""
from __future__ import annotations
import subprocess
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
SOURCE=ROOT/'src/AnimationWorldPositionForSpawn236.cpp'
OBJECT=ROOT/'build/core965-canonical/AnimationRawWorldPosition236.obj'
FLAGS=['/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc']

def main():
    subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-animation-world-position-for-spawn236-native.py')],cwd=ROOT,check=True)
    OBJECT.parent.mkdir(parents=True,exist_ok=True)
    subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(SOURCE),str(OBJECT),*FLAGS],cwd=ROOT,check=True)
    subprocess.run([str(ROOT/'scripts/repo-python'),str(ROOT/'scripts/verify-animation-world-position-for-spawn236-native.py'),
                    '--candidate-object',str(OBJECT)],cwd=ROOT,check=True)

if __name__=='__main__':main()
