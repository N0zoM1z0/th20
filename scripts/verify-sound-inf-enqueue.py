#!/usr/bin/env python3
"""Focused host semantics for the original SoundInf command-queue writer."""
from __future__ import annotations
import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def main() -> None:
    host = ROOT / 'build/gpt-web-sound-inf-enqueue-test'
    command = [
        'g++-13', '-std=c++20', '-O1', '-Wall', '-Wextra', '-Werror',
        '-fsanitize=address,undefined', '-fno-sanitize-recover=all',
        '-pthread', '-Isrc',
        'tests/sound_inf_enqueue.cpp',
        'src/SoundInfEnqueue323.cpp',
        'src/NativeSoundCommandArrayView.cpp',
        'src/LockRegistry.cpp',
        '-o', str(host),
    ]
    subprocess.run(command, cwd=ROOT, check=True)
    subprocess.run([str(host)], cwd=ROOT, check=True)
    print('PASS SoundInf::enqueue: first-free slot, 31-slot bound, command field order, safe name copy and range-check call')


if __name__ == '__main__':
    main()
