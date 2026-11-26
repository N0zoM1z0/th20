#!/usr/bin/env python3
"""Report native-vs-COFF metrics for a 5,993B Animation Draw Boss candidate.

Unlike the older grep-based probe snippets, every instruction-form result in
this report is extracted from the candidate COFF body only. The original PE
and candidate sections are decoded independently to prevent accidentally
reporting native instructions as candidate progress. Float windows follow
verified getter/renderer call roles instead of fixed native offset ranges.
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


def scale_width_window(mode, native_getter, instructions, relocs, native_calls, candidate_calls):
    # The complete call sequence gives a stable boundary even when a probe
    # moves a case away from its original native offset.
    if len(native_calls) != len(candidate_calls):
        raise ValueError("call census differs; mode boundary is unproven")
    index = native_calls.index(native_getter)
    getter, renderer = candidate_calls[index:index + 2]
    symbols = {int(row["offset"]) - 1: str(row["symbol"])
               for row in relocs if row["type"] == "REL32"}
    target = "draw_shape_43c780@" if mode in (35, 36) else "draw_shape_43df30@"
    if ("animation_inherited_aux_scale_x@" not in symbols.get(getter, "")
            or target not in symbols.get(renderer, "")):
        raise ValueError("getter/renderer roles differ; mode boundary is unproven")
    window = [ins for ins in instructions
              if candidate_calls[index - 1] + 5 <= ins.address - HEAD < renderer]
    operator = "addss" if mode in (35, 45) else "subss"
    arithmetic = [ins for ins in window
                  if ins.address - HEAD > getter and ins.mnemonic == operator]
    if len(arithmetic) != 2:
        raise ValueError(f"expected scale/width arithmetic pair, found {len(arithmetic)}")
    scale, width = arithmetic
    divisions = [ins.address - HEAD for ins in window if ins.mnemonic == "divss"]
    phases = (sum(site < getter for site in divisions),
              sum(getter < site < scale.address - HEAD for site in divisions),
              sum(scale.address - HEAD < site < width.address - HEAD for site in divisions))
    if sum(phases) != len(divisions):
        raise ValueError("division lies outside the identified scale/width phases")
    return getter, scale, width, phases


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

        native_slot_stores = [ins.address - HEAD for ins in instructions
                        if ins.mnemonic == "fstp" and ins.op_str == "dword ptr [ebp - 0x160]"]
        print(f"{path.name}: contribution={len(body)}B code={code_end}B "
              f"x86={len(instructions)} ordinary={ordinary}/{comparable} "
              f"E8={aligned}/{len(native_calls)} abs-E8-delta={abs_delta} "
              f"HIGHLOW-sites={exact_highlow_sites}/{len(native_highlow)}")
        print(f"  candidate-only fstp-m32 stores at [ebp-0x160]={len(native_slot_stores)} {native_slot_stores}")
        for mode, native_getter in ((35, 0x1016), (36, 0x1103), (45, 0x15DD), (46, 0x16BC)):
            try:
                getter, scale, width, phases = scale_width_window(
                    mode, native_getter, instructions, relocs, native_calls, candidate_calls)
            except ValueError as exc:
                print(f"  candidate-only mode{mode}: unavailable ({exc})")
                continue
            order = "native" if phases == (1, 0, 1) else "DIFFERENT"
            print(f"  candidate-only mode{mode}: getter=+0x{getter:X}; "
                  f"scale=+0x{scale.address - HEAD:X} {scale.mnemonic} {scale.op_str}; "
                  f"width=+0x{width.address - HEAD:X} {width.mnemonic} {width.op_str}; "
                  f"divisions(pre-getter, before-scale, before-width)={phases} division-order={order}")
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
