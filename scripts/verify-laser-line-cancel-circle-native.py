#!/usr/bin/env python3
"""Focused structural audit for the 1,170-byte nonexact Line cancel handler."""
from __future__ import annotations

from pathlib import Path
import runpy
import struct
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[1]
SOURCE = ROOT / "src/LaserLineCancelCircle.cpp"
OBJECT = ROOT / "build/probe-laser-line-cancel-circle/LaserLineCancelCircle.obj"
SYMBOL = "?cancel_circle@LaserLineInf@th20@@UAEHABUVector3@2@MHH@Z"
ADDRESS = 0x004CB060
CANDIDATE_SIZE = 1164
NATIVE_SIZE = 1170
BRANCH_START = 0x1BA
CANDIDATE_BRANCH_END = 0x1C0
NATIVE_BRANCH_END = 0x1C6
BRANCH_DELTA = 6

FLAGS = [
    "/std:c++20", "/Od", "/Ob0", "/GS", "/Gy", "/Zl",
    "/arch:SSE2", "/fp:precise", "/sdl", "/EHsc",
]


def fail(message: str) -> None:
    raise SystemExit(f"FAIL: {message}")


def rel32_target(code: bytes, offset: int) -> int:
    displacement = struct.unpack_from("<i", code, offset + 1)[0]
    return offset + 5 + displacement


def rel32_0f_target(code: bytes, offset: int) -> int:
    displacement = struct.unpack_from("<i", code, offset + 2)[0]
    return offset + 6 + displacement


def rel8_target(code: bytes, offset: int) -> int:
    displacement = struct.unpack_from("<b", code, offset + 1)[0]
    return offset + 2 + displacement


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

    # Native code tests the hit edge with JBE and retains two jumps to the
    # shared loop tail. Natural C++ emits the equivalent unordered-aware JA
    # exit. The extra six native bytes are preserved as a visible NONEXACT
    # compiler-layout difference, never recreated as padding or assembly.
    if code[BRANCH_START:CANDIDATE_BRANCH_END] != bytes.fromhex("0f8715020000"):
        fail("candidate hit-test branch layout changed")
    if native[BRANCH_START:NATIVE_BRANCH_END] != bytes.fromhex(
        "760ae91a020000e915020000"
    ):
        fail("native hit-test branch layout changed")
    candidate_miss = BRANCH_START + 6 + struct.unpack_from("<i", code, BRANCH_START + 2)[0]
    native_hit = rel8_target(native, BRANCH_START)
    native_miss_a = rel32_target(native, BRANCH_START + 2)
    native_miss_b = rel32_target(native, BRANCH_START + 7)
    if native_hit != CANDIDATE_BRANCH_END + BRANCH_DELTA:
        fail("native hit edge no longer aligns with candidate fallthrough")
    if candidate_miss + BRANCH_DELTA != native_miss_a or native_miss_a != native_miss_b:
        fail("candidate/native miss edges do not reach the same loop tail")

    # The early return and loop-exit branches target code after the shifted
    # hit block; the loop back-edge moves with its source but retains its
    # original loop-head destination.
    branch_fields = (
        range(0x31, 0x35),       # early-return E9 displacement
        range(0x191, 0x195),     # outer loop-exit 0F 82 displacement
        range(0x40F, 0x413),     # candidate loop-back E9 displacement
    )
    candidate_early = rel32_target(code, 0x30)
    native_early = rel32_target(native, 0x30)
    candidate_exit = rel32_0f_target(code, 0x18F)
    native_exit = rel32_0f_target(native, 0x18F)
    candidate_back = rel32_target(code, 0x40E)
    native_back = rel32_target(native, 0x414)
    if candidate_early + BRANCH_DELTA != native_early:
        fail("early-return branch targets diverged")
    if candidate_exit + BRANCH_DELTA != native_exit:
        fail("loop-exit branch targets diverged")
    if candidate_back != native_back:
        fail("loop-back branch targets diverged")

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
        "?animation_file@BulletController@th20@@QBEPAVAnimationFile@2@XZ": 0x004859B0,
        "?spawn@AnimationFile@th20@@QAE?AUAnimationHandle@2@PBDHABUVector3@2@MHPAPAVAnimation@2@@Z": 0x004790E0,
        "@__security_check_cookie@4": 0x005429EE,
    }
    if len(relocations) != 30:
        fail(f"expected thirty native relocations, found {len(relocations)}")

    relocation_bytes = {
        int(row["offset"]) + byte
        for row in relocations
        for byte in range(4)
    }
    ignored_branch_bytes = {byte for span in branch_fields for byte in span}
    ignored = relocation_bytes | ignored_branch_bytes | set(
        range(BRANCH_START, CANDIDATE_BRANCH_END)
    )
    mismatches = []
    for offset, value in enumerate(code):
        if offset in ignored:
            continue
        target_offset = offset if offset < BRANCH_START else offset + BRANCH_DELTA
        if value != native[target_offset]:
            mismatches.append((offset, target_offset, value, native[target_offset]))
    ordinary_bytes = len(code) - len(relocation_bytes) - len(ignored_branch_bytes) - (
        CANDIDATE_BRANCH_END - BRANCH_START
    )
    if mismatches:
        fail(f"ordinary-byte mismatches after branch alignment: {mismatches[:8]!r}")

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
            if destination != 0x0056FD14 or compare["pe_bytes_at"](image, destination, 7) != b"bullet\0":
                fail(f"string literal relocation changed: {destination:#010x}")
        elif expected_targets.get(symbol) != destination:
            fail(f"relocation {symbol!r} resolved to {destination:#010x}")

    print(
        f"NONEXACT: {ordinary_bytes}/{ordinary_bytes} ordinary bytes align; "
        f"30/30 relocation targets resolve; native branch layout is +{BRANCH_DELTA} bytes."
    )
    print("No exact credit, assembly, NOP, or padding is claimed.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
