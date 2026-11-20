#!/usr/bin/env python3
"""Focused structural audit for the nonexact Infinite-laser cancellation body."""
from __future__ import annotations

from pathlib import Path
import runpy
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/LaserInfiniteCancelCircle.cpp"
OBJECT = ROOT / "build/probe-laser-infinite-cancel-circle/LaserInfiniteCancelCircle.obj"
SYMBOL = "?cancel_circle@LaserInfiniteInf@th20@@UAEHABUVector3@2@MHH@Z"
ADDRESS = 0x004CABF0
CANDIDATE_SIZE = 1117
NATIVE_SIZE = 1123
BRANCH_START = 0x1B0
CANDIDATE_BRANCH_END = 0x1B6
NATIVE_BRANCH_END = 0x1BC
BRANCH_DELTA = 6
FLAGS = [
    "/std:c++20", "/Od", "/Ob0", "/GS", "/Gy", "/Zl",
    "/arch:SSE2", "/fp:precise", "/sdl", "/EHsc",
]


def fail(message: str) -> None:
    raise SystemExit(f"FAIL: {message}")


def rel32_target(code: bytes, offset: int) -> int:
    return offset + 5 + struct.unpack_from("<i", code, offset + 1)[0]


def cond32_target(code: bytes, offset: int) -> int:
    return offset + 6 + struct.unpack_from("<i", code, offset + 2)[0]


def main() -> int:
    subprocess.run(
        [str(ROOT / "scripts/compile-probe.sh"), str(SOURCE), str(OBJECT), *FLAGS],
        cwd=ROOT,
        check=True,
    )
    sys.path.insert(0, str(ROOT / "scripts"))
    compare = runpy.run_path(str(ROOT / "scripts/compare-coff-function.py"))
    code, relocations = compare["object_function"](OBJECT, SYMBOL, CANDIDATE_SIZE)
    image = compare["verified_target"]()
    native = compare["pe_bytes_at"](image, ADDRESS, NATIVE_SIZE)
    if len(code) != CANDIDATE_SIZE or len(native) != NATIVE_SIZE:
        fail(f"unexpected extents: candidate={len(code)} native={len(native)}")

    # Native uses JBE-to-hit plus two jumps to the sample-advance block. The
    # natural candidate uses one equivalent unordered-aware JA exit. Do not
    # synthesize the native six-byte layout difference.
    if code[BRANCH_START:CANDIDATE_BRANCH_END] != bytes.fromhex("0f871e020000"):
        fail("candidate hit-test branch changed")
    if native[BRANCH_START:NATIVE_BRANCH_END] != bytes.fromhex(
        "760ae923020000e91e020000"
    ):
        fail("native hit-test branch changed")
    candidate_skip = cond32_target(code, BRANCH_START)
    native_hit = BRANCH_START + 2 + struct.unpack_from("<b", native, BRANCH_START + 1)[0]
    native_skip_a = rel32_target(native, BRANCH_START + 2)
    native_skip_b = rel32_target(native, BRANCH_START + 7)
    if native_hit != CANDIDATE_BRANCH_END + BRANCH_DELTA:
        fail("native hit edge does not align with candidate fallthrough")
    if candidate_skip + BRANCH_DELTA != native_skip_a or native_skip_a != native_skip_b:
        fail("candidate/native miss edges do not reach the same sample-advance block")

    # Early return and loop exit move by six bytes with the function extent;
    # the back-edge instruction moves, but continues to target the same loop.
    if rel32_target(code, 0x30) + BRANCH_DELTA != rel32_target(native, 0x30):
        fail("early-return branch target diverged")
    if cond32_target(code, 0x185) + BRANCH_DELTA != cond32_target(native, 0x185):
        fail("loop-exit branch target diverged")
    if rel32_target(code, 0x40D) != rel32_target(native, 0x413):
        fail("loop-back branch target diverged")

    relocation_offsets = {int(row["offset"]) for row in relocations}
    relocation_bytes = {
        offset + byte for offset in relocation_offsets for byte in range(4)
    }
    branch_fields = (
        set(range(0x31, 0x35))
        | set(range(0x187, 0x18B))
        | set(range(0x40E, 0x412))
    )
    branch_region = set(range(BRANCH_START, CANDIDATE_BRANCH_END))
    ignored = relocation_bytes | branch_fields | branch_region
    mismatches = []
    for offset, value in enumerate(code):
        if offset in ignored:
            continue
        target_offset = offset if offset < BRANCH_START else offset + BRANCH_DELTA
        if value != native[target_offset]:
            mismatches.append((offset, target_offset, value, native[target_offset]))
    ordinary_bytes = len(code) - len(relocation_bytes) - len(branch_fields) - len(branch_region)
    if mismatches:
        fail(f"ordinary-byte mismatches after branch alignment: {mismatches[:8]!r}")

    expected_targets = {
        "___security_cookie": 0x005B25C0,
        "??0Vector3@th20@@QAE@XZ": 0x00422E10,
        "?native_screen_top_16_56cd90@th20@@3MB": 0x0056CD90,
        "?native_screen_half_2_56c8d0@th20@@3MB": 0x0056C8D0,
        "_memset": 0x00544760,
        "?polar@th20@@YAXAAUVector3@1@MM@Z": 0x00439330,
        "??HVector3@th20@@QBE?AU01@ABU01@@Z": 0x00429570,
        "??YVector3@th20@@QAEAAU01@ABU01@@Z": 0x004296E0,
        "?squared_distance_xy@geometry@th20@@YAMABUVector3@2@0@Z": 0x004560D0,
        "?bullet_controller@Context@th20@@QAEPAUBulletController@2@XZ": 0x0040C300,
        "?native_polygon_radius32@th20@@3MB": 0x0056CD94,
        "?bullet_position_outside_screen@th20@@YAHABUVector3@1@MM@Z": 0x00485390,
        "?animation_file@BulletController@th20@@QBEPAVAnimationFile@2@XZ": 0x004859B0,
        "?spawn@AnimationFile@th20@@QAE?AUAnimationHandle@2@PBDHABUVector3@2@MHPAPAVAnimation@2@@Z": 0x004790E0,
        "@__security_check_cookie@4": 0x005429EE,
    }
    if len(relocations) != 33:
        fail(f"expected 33 native relocations, found {len(relocations)}")
    for row in relocations:
        object_offset = int(row["offset"])
        target_offset = object_offset if object_offset < BRANCH_START else object_offset + BRANCH_DELTA
        word = struct.unpack_from("<I", native, target_offset)[0]
        if row["type"] == "DIR32":
            destination = word
        elif row["type"] == "REL32":
            destination = (ADDRESS + target_offset + 4 + struct.unpack(
                "<i", struct.pack("<I", word)
            )[0]) & 0xFFFFFFFF
        else:
            fail(f"unsupported relocation type {row['type']!r}")
        symbol = str(row["symbol"])
        if symbol.startswith("$SG"):
            valid = destination == 0x0056FD14 and compare["pe_bytes_at"](
                image, destination, 7
            ) == b"bullet\0"
        else:
            valid = expected_targets.get(symbol) == destination
        if not valid:
            fail(f"relocation {symbol!r} resolved to {destination:#010x}")

    print(
        f"NONEXACT: {ordinary_bytes}/{ordinary_bytes} ordinary bytes align; "
        f"33/33 relocation targets resolve; native branch layout is +{BRANCH_DELTA} bytes."
    )
    print("No exact credit, assembly, NOP, or padding is claimed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
