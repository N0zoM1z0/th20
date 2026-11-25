#!/usr/bin/env python3
"""Rebuild and independently verify the exact 244B Animation corner dispatcher."""
from __future__ import annotations

import subprocess
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/AnimationCornerProjectionDispatch244.cpp"
OBJECT = ROOT / "build/gptweb-corner-dispatch/AnimationCornerProjectionDispatch244.obj"


def run(*arguments: str) -> None:
    subprocess.run(
        [str(ROOT / "scripts/repo-python"), *arguments],
        cwd=ROOT,
        check=True,
    )


def main() -> None:
    # The match-unit manifest owns the locked /GS /sdl /EHsc compiler profile,
    # complete 260B code+table contribution, and all 11 original relocations.
    run("scripts/verify-animation-corner-projection-dispatch244-native.py")
    run(
        "scripts/replay-exact-units.py",
        "--source",
        str(SOURCE.relative_to(ROOT)),
    )
    run(
        "scripts/verify-animation-corner-projection-dispatch244-native.py",
        "--candidate-object",
        str(OBJECT.relative_to(ROOT)),
    )


if __name__ == "__main__":
    main()
