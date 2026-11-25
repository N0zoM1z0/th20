#!/usr/bin/env python3
"""Report native-vs-COFF metrics for a 5,993B Animation Draw Boss candidate.

Unlike the older grep-based probe snippets, every instruction-form result in
this report is extracted from the candidate COFF body only. The original PE
and candidate sections are decoded independently to prevent accidentally
reporting native instructions as candidate progress.
"""
from __future__ import annotations

import argparse
import importlib.util
from pathlib import Path
import re
import sys

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))


def load_module(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module


COFF = load_module("draw_boss_candidate_coff", ROOT / "scripts/compare-coff-function.py")
ORIGINAL = load_module("draw_boss_candidate_native", ROOT / "scripts/verify-animation-draw-boss-native.py")
SYMBOL = "?draw@AnimationPoolOwner@th20@@QAEHPAVAnimation@2@@Z"
HEAD = 0x00443880
SIZE = 5993
END_MARKER = bytes.fromhex("c204000f1f00")


def candidate_body(path: Path):
    try:
        return COFF.object_function(path, SYMBOL, 6316)
    except ValueError as exc:
        match = re.search(r"complete COFF contribution is (\d+) bytes", str(exc))
        if not match:
            raise
        return COFF.object_function(path, SYMBOL, int(match.group(1)))


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("objects", nargs="+", type=Path)
    args = parser.parse_args()

    image = COFF.verified_target()
    native = COFF.pe_bytes_at(image, HEAD, SIZE)
    native_instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(native, HEAD))
    native_calls = [ins.address - HEAD for ins in native_instructions
                    if len(ins.bytes) == 5 and ins.bytes[0] == 0xE8]
    base, sections = ORIGINAL.parse_sections(image)
    native_highlow = {address - HEAD for address in ORIGINAL.physical_highlow(image, base, sections)
                      if HEAD <= address < HEAD + SIZE}

    for path in args.objects:
        body, relocs = candidate_body(path)
        decoded_body = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(bytes(body), HEAD))
        ret4 = next((ins for ins in decoded_body
                     if ins.bytes[:3] == bytes.fromhex("c20400")), None)
        if ret4 is None:
            raise ValueError(f"{path}: no complete ret 4 function boundary")
        code_end = ret4.address - HEAD + ret4.size
        if code_end > SIZE + 512:
            raise ValueError(f"{path}: implausible code boundary {code_end}")

        # The established ordinary-byte metric compares the complete native
        # COFF contribution: 5,993B code plus 3B alignment and 80 real switch
        # table pointers (6,316B total). Longer experimental contributions are
        # decoded/reported, but scoring remains capped at that same boundary.
        contribution_extent = 6316
        score_extent = min(len(body), contribution_extent)
        ignored = set()
        for relocation in relocs:
            offset = int(relocation["offset"])
            if offset < score_extent:
                ignored.update(range(offset, min(score_extent, offset + 4)))
        original_contribution = COFF.pe_bytes_at(image, HEAD, score_extent)
        comparable = score_extent - len(ignored)
        ordinary = sum(original_contribution[i] == body[i]
                       for i in range(score_extent) if i not in ignored)

        code = bytes(body[:code_end])
        instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, HEAD))
        candidate_calls = [ins.address - HEAD for ins in instructions
                           if len(ins.bytes) == 5 and ins.bytes[0] == 0xE8]
        deltas = [candidate - original for original, candidate
                  in zip(native_calls, candidate_calls)]
        aligned = sum(delta == 0 for delta in deltas)
        abs_delta = sum(abs(delta) for delta in deltas)
        candidate_highlow = {int(relocation["offset"]) for relocation in relocs
                             if relocation["type"] == "DIR32" and int(relocation["offset"]) < code_end}
        exact_highlow_sites = len(native_highlow & candidate_highlow)

        first_spills = [ins.address - HEAD for ins in instructions
                        if ins.mnemonic == "fstp" and ins.op_str == "dword ptr [ebp - 0x160]"]
        mode35_add = [ins.address - HEAD for ins in instructions
                      if 0x0F00 <= ins.address - HEAD < 0x10B2
                      and ins.mnemonic == "addss" and ins.op_str == "xmm0, xmm1"]
        mode36_sub = [ins.address - HEAD for ins in instructions
                      if 0x10B2 <= ins.address - HEAD < 0x1198
                      and ins.mnemonic == "subss" and ins.op_str == "xmm0, xmm1"]
        mode35_memory_add = [ins.address - HEAD for ins in instructions
                             if 0x0F00 <= ins.address - HEAD < 0x10B2
                             and ins.mnemonic == "addss" and ins.op_str.startswith("xmm0, dword ptr")]
        mode36_memory_sub = [ins.address - HEAD for ins in instructions
                             if 0x10B2 <= ins.address - HEAD < 0x1198
                             and ins.mnemonic == "subss" and ins.op_str.startswith("xmm0, dword ptr")]
        # Native mode45/46 are separate later cases in the same large switch.
        # Keep these ranges distinct from mode35/36: mode45 uses ADDSS and
        # mode46 uses SUBSS, each with a separately recomputed width half.
        mode45_add = [ins.address - HEAD for ins in instructions
                      if 0x15D5 <= ins.address - HEAD < 0x1604
                      and ins.mnemonic == "addss" and ins.op_str == "xmm0, xmm1"]
        mode46_sub = [ins.address - HEAD for ins in instructions
                      if 0x16BC <= ins.address - HEAD < 0x16E3
                      and ins.mnemonic == "subss" and ins.op_str == "xmm0, xmm1"]
        mode46_reverse_sub = [ins.address - HEAD for ins in instructions
                              if 0x16BC <= ins.address - HEAD < 0x16E3
                              and ins.mnemonic == "subss" and ins.op_str == "xmm1, xmm0"]
        mode45_memory_add = [ins.address - HEAD for ins in instructions
                             if 0x15D5 <= ins.address - HEAD < 0x1604
                             and ins.mnemonic == "addss" and ins.op_str.startswith("xmm0, dword ptr")]
        mode46_memory_sub = [ins.address - HEAD for ins in instructions
                             if 0x16BC <= ins.address - HEAD < 0x16E3
                             and ins.mnemonic == "subss" and ins.op_str.startswith("xmm0, dword ptr")]
        mode35_width_add = [ins.address - HEAD for ins in instructions
                            if 0x1068 <= ins.address - HEAD < 0x107A
                            and ins.mnemonic == "addss" and ins.op_str.startswith("xmm0, dword ptr")]
        mode36_width_sub = [ins.address - HEAD for ins in instructions
                            if 0x1155 <= ins.address - HEAD < 0x116B
                            and ins.mnemonic == "subss" and ins.op_str == "xmm1, xmm0"]
        mode45_width_add = [ins.address - HEAD for ins in instructions
                            if 0x163D <= ins.address - HEAD < 0x1650
                            and ins.mnemonic == "addss" and ins.op_str.startswith("xmm0, dword ptr")]
        mode46_width_sub = [ins.address - HEAD for ins in instructions
                            if 0x171C <= ins.address - HEAD < 0x1732
                            and ins.mnemonic == "subss" and ins.op_str == "xmm1, xmm0"]

        print(f"{path.name}: contribution={len(body)}B code={code_end}B "
              f"x86={len(instructions)} ordinary={ordinary}/{comparable} "
              f"E8={aligned}/{len(native_calls)} abs-E8-delta={abs_delta} "
              f"HIGHLOW-sites={exact_highlow_sites}/{len(native_highlow)}")
        print(f"  candidate-only mode35/36: first-result-spills={len(first_spills)} {first_spills}; "
              f"register-add={mode35_add}; register-sub={mode36_sub}; "
              f"memory-add={mode35_memory_add}; memory-sub={mode36_memory_sub}")
        print(f"  candidate-only mode35/36/45/46: "
              f"mode35-width-add={mode35_width_add}; mode36-width-sub={mode36_width_sub}; "
              f"mode45-width-add={mode45_width_add}; mode46-width-sub={mode46_width_sub}")
        print(f"  candidate-only mode45/46 scale: mode45-register-add={mode45_add}; "
              f"mode46-native-order-register-sub={mode46_sub}; "
              f"mode46-reversed-register-sub={mode46_reverse_sub}; "
              f"memory-add={mode45_memory_add}; memory-sub={mode46_memory_sub}")
        if len(candidate_calls) != len(native_calls):
            print(f"  WARNING: candidate E8 instruction count {len(candidate_calls)} != native {len(native_calls)}")
        if code_end != SIZE:
            print(f"  WARNING: candidate code extent {code_end} != native {SIZE}")
    return 0


if __name__ == "__main__":
    try:
        raise SystemExit(main())
    except (OSError, ValueError, KeyError) as exc:
        print(f"error: {exc}", file=sys.stderr)
        raise SystemExit(1)
