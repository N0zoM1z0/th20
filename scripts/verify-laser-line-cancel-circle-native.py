#!/usr/bin/env python3
"""Cold-build and strictly replay the complete native Line circle-cancel body."""
from __future__ import annotations

from pathlib import Path
import runpy
import subprocess

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/LaserLineCancelCircle.cpp"
OBJECT = ROOT / "build/laser-line-cancel-circle-canonical/LaserLineCancelCircle.obj"
UNIT = "laser_line_cancel_circle"
FLAGS = [
    "/std:c++20", "/Od", "/Ob0", "/GS", "/Gy", "/Zl",
    "/arch:SSE2", "/fp:precise", "/sdl", "/EHsc",
]


def main() -> int:
    subprocess.run(
        [str(ROOT / "scripts/compile-probe.sh"), str(SOURCE), str(OBJECT), *FLAGS],
        cwd=ROOT,
        check=True,
    )
    compare = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    report = compare["compare_unit"](UNIT)
    if report["result"] != "exact":
        raise SystemExit(f"FAIL: canonical Line circle-cancel replay: {report!r}")
    if report["matched_bytes"] != 1170 or len(report["relocations"]) != 30:
        raise SystemExit(f"FAIL: unexpected Line circle-cancel coverage: {report!r}")
    print("EXACT: 1,170/1,170 native bytes and 30/30 relocation destinations.")
    print("Natural C++ forward miss edge; no assembly, NOP, or padding.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
