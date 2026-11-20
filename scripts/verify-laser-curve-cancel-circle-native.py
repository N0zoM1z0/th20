#!/usr/bin/env python3
"""Cold-build and strictly replay the complete native Curve cancel handler."""
from __future__ import annotations

from pathlib import Path
import runpy
import subprocess

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/LaserCurveCancelCircle.cpp"
OBJECT = ROOT / "build/laser-curve-cancel-circle-canonical/LaserCurveCancelCircle.obj"
UNIT = "laser_curve_cancel_circle"
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
        raise SystemExit(f"FAIL: canonical Curve circle-cancel replay: {report!r}")
    if report["matched_bytes"] != 647 or len(report["relocations"]) != 10:
        raise SystemExit(f"FAIL: unexpected Curve circle-cancel coverage: {report!r}")
    print("EXACT: 647/647 native bytes and 10/10 relocation destinations.")
    print("Natural C++ forward miss edge; no assembly, NOP, or padding.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
