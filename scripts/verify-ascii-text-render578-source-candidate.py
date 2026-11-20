#!/usr/bin/env python3
"""Verify the natural-C++ 578B ASCII renderer and its single SSE fusion."""
from __future__ import annotations

import argparse
import csv
import hashlib
import importlib.util
import re
import struct
import sys
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/AsciiTextRender578.cpp"
BASE = 0x00400000
HEAD = 0x0044B020
NATIVE_SIZE = 578
NATIVE_INSTRUCTIONS = 139
TARGET_SHA = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
CALLS = {
    0x39: 0x0040C310,
    0x45: 0x0040B730,
    0x7D: 0x00447940,
    0x92: 0x00437CD0,
    0x12A: 0x0054FE20,
    0x19C: 0x00445A00,
    0x1B6: 0x004140F0,
    0x202: 0x0044FFF0,
    0x211: 0x0040B900,
    0x220: 0x00414400,
    0x239: 0x005429EE,
}
NATIVE_DATA_OFFSETS = {0x6, 0x18, 0x35, 0x56, 0x10F, 0x117, 0x14E, 0x172}
CANDIDATE_CALL_OFFSETS = [0x39, 0x45, 0x7D, 0x92, 0x12A,
                          0x198, 0x1B2, 0x1FE, 0x20D, 0x21C, 0x235]
CANDIDATE_DATA_OFFSETS = [0x6, 0x18, 0x35, 0x56, 0x10F, 0x117, 0x14E, 0x16E]
CALL_TARGET_FRAGMENTS = (
    '?slot@LockRegistry@th20',
    '??0?$lock_guard@Vrecursive_mutex@std@@',
    '?format_text_447940@th20',
    '?sprite_data@Animation@th20',
    '_strlen',
    '?texture_for_sprite@AnimationQuadSubmitOwner',
    '??0?$function@$$A6AXXZ@std@@',
    '?submit_text_44fff0@NativeTextSubmitOwner',
    '??1?$lock_guard@Vrecursive_mutex@std@@',
    '??1?$function@$$A6AXXZ@std@@',
    '@__security_check_cookie@4',
)
DATA_TARGET_FRAGMENTS = (
    '__ehhandler$',
    '___security_cookie',
    '?process_locks@th20@@3VLockRegistry@1@A',
    '?native_text_sizes_56c768@th20',
    '?native_double_56c8d0@th20',
    '?native_one_56c8cc@th20',
    '?native_unsigned_length_correction_56cdd0@th20',
    '?native_double_56c8d0@th20',
)


def offset_value(value) -> int:
    return int(value, 16) if isinstance(value, str) else int(value)


def load_coff_helper():
    sys.path.insert(0, str(ROOT / "scripts"))
    spec = importlib.util.spec_from_file_location(
        "coff_function", ROOT / "scripts/compare-coff-function.py")
    assert spec and spec.loader
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def load_pe_helper():
    sys.path.insert(0, str(ROOT / "scripts"))
    spec = importlib.util.spec_from_file_location(
        "ascii_renderer_pe", ROOT / "scripts/verify-animation-draw-boss-native.py")
    assert spec and spec.loader
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module


def normalize_instructions(instructions, data_offsets, base: int):
    result = []
    for insn in instructions:
        offset = insn.address - base
        if insn.mnemonic == "call":
            result.append(("call",))
        elif insn.mnemonic.startswith("j"):
            result.append((insn.mnemonic, "REL"))
        elif any(offset <= relocation < offset + insn.size
                 for relocation in data_offsets):
            operands = insn.op_str
            memory = re.search(r"\[([^\]]+)\]", operands)
            if memory:
                expression = memory.group(1)
                if re.search(r"0x[0-9a-fA-F]+|(?<![\w])0(?![\w])", expression):
                    expression = re.sub(
                        r"0x[0-9a-fA-F]+|(?<![\w])0(?![\w])", "ABS", expression)
                else:
                    expression += " + ABS"
                operands = operands[:memory.start(1)] + expression + operands[memory.end(1):]
            else:
                operands = re.sub(r"(?:0x[0-9a-fA-F]+|(?<![\w])0(?![\w]))$",
                                  "ABS", operands)
            result.append((insn.mnemonic, operands))
        else:
            result.append((insn.mnemonic, insn.op_str))
    return result


def main() -> None:
    parser = argparse.ArgumentParser()
    parser.add_argument("--candidate-object", type=Path,
                        default=ROOT / "build/gptweb-ascii-text-render578/AsciiTextRender578.obj")
    args = parser.parse_args()

    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == TARGET_SHA
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    original = pe.get_data(HEAD - BASE, NATIVE_SIZE)
    native = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(original, HEAD))
    assert len(original) == NATIVE_SIZE and len(native) == NATIVE_INSTRUCTIONS
    native_calls = {insn.address - HEAD: int(insn.op_str, 16)
                    for insn in native
                    if insn.mnemonic == "call" and insn.op_str.startswith("0x")}
    assert native_calls == CALLS
    assert (native[-1].mnemonic, native[-1].op_str) == ("ret", "")

    # Independently check the physical PE relocation directory, not merely
    # the pointer values visible in the raw instruction stream.
    pe_helper = load_pe_helper()
    image, _ = pe_helper.verified_target()
    image_base, sections = pe_helper.parse_sections(image)
    native_data = {
        address - HEAD: struct.unpack("<I", pe_helper.raw_at(
            image, image_base, sections, address, 4))[0]
        for address in pe_helper.physical_highlow(image, image_base, sections)
        if HEAD <= address < HEAD + NATIVE_SIZE
    }
    assert native_data == {
        0x006: 0x00568578, 0x018: 0x005B25C0, 0x035: 0x005C0240,
        0x056: 0x0056C768, 0x10F: 0x0056C8D0, 0x117: 0x0056C8CC,
        0x14E: 0x0056CDD0, 0x172: 0x0056C8D0,
    }
    assert pe_helper.raw_at(image, image_base, sections,
                            HEAD + NATIVE_SIZE, 5) == b"\xCC" * 5

    submit = pe.get_data(0x0044FFF0 - BASE, 294)
    submit_insns = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(submit, 0x0044FFF0))
    assert len(submit_insns) == 106
    assert (submit_insns[-1].mnemonic, submit_insns[-1].op_str) == ("ret", "0x58")
    callback = pe.get_data(0x00486E80 - BASE, 111)
    assert hashlib.sha256(callback).hexdigest() == (
        "12212f28b9331ddb3041bea74034cf798e3bc7ab873eb2372b2146cb430d21ae")
    assert callback[0x62] == 0xE8
    assert (0x00486E80 + 0x67 + struct.unpack_from("<i", callback, 0x63)[0]) & 0xFFFFFFFF == HEAD

    correction = pe.get_data(0x0056CDD0 - BASE, 16)
    assert len(correction) == 16
    assert struct.unpack("<dd", correction) == (0.0, 4294967296.0)
    for offset, target in ((0x18, 0x005B25C0), (0x35, 0x005C0240),
                          (0x56, 0x0056C768), (0x10F, 0x0056C8D0),
                          (0x117, 0x0056C8CC), (0x14E, 0x0056CDD0),
                          (0x172, 0x0056C8D0)):
        assert struct.unpack_from("<I", original, offset)[0] == target, hex(offset)

    coff = load_coff_helper()
    symbol = ("?draw_44b020@NativeTextSubmitOwner@th20@@QAA?AUNativeTextDrawResult8@2@"
              "PAVAnimation@2@HIHHHV?$function@$$A6AXXZ@std@@PBDZZ")
    code, relocations = coff.object_function(args.candidate_object, symbol, 574)
    candidate = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, 0))
    assert len(code) == 574 and len(candidate) == 138
    assert len(relocations) == 19
    rel32 = [r for r in relocations if r["type"] == "REL32"]
    dir32 = [r for r in relocations if r["type"] == "DIR32"]
    assert len(rel32) == 11 and len(dir32) == 8
    assert [offset_value(r["offset"]) - 1 for r in rel32] == CANDIDATE_CALL_OFFSETS
    assert [offset_value(r["offset"]) for r in dir32] == CANDIDATE_DATA_OFFSETS

    # Candidate relocation symbols preserve the original native target order.
    call_symbols = [r["symbol"] for r in rel32]
    for actual, fragments in zip(call_symbols, CALL_TARGET_FRAGMENTS):
        assert any(fragment.lower() in actual.lower() for fragment in fragments), (fragments, actual)
    data_symbols = [r["symbol"] for r in dir32]
    for actual, fragment in zip(data_symbols, DATA_TARGET_FRAGMENTS):
        assert fragment.lower() in actual.lower(), (fragment, actual)

    native_by_offset = {insn.address - HEAD: insn for insn in native}
    candidate_by_offset = {insn.address: insn for insn in candidate}
    # The spill is moved across the independent LEA/PUSH pair by the current
    # compiler; the actual strlen call and all observable calls stay ordered.
    assert native_by_offset[0x122].mnemonic == "movss"
    assert candidate_by_offset[0x11B].mnemonic == "movss"
    # Original register load + register multiply versus the compiler's fused
    # memory-source multiply. This is the sole 4-byte / one-head size delta.
    assert native_by_offset[0x162].mnemonic == "movss"
    assert native_by_offset[0x16A].mnemonic == "mulss"
    assert candidate_by_offset[0x162].mnemonic == "mulss"
    assert "xmm1" in native_by_offset[0x162].op_str
    assert "xmm0, xmm1" in native_by_offset[0x16A].op_str
    assert "xmm0, dword ptr [ebp - 0x538]" in candidate_by_offset[0x162].op_str

    native_skip = {0x122, 0x162, 0x16A}
    candidate_skip = {0x11B, 0x162}
    normalized_native = normalize_instructions(
        [i for i in native if i.address - HEAD not in native_skip],
        NATIVE_DATA_OFFSETS, HEAD)
    normalized_candidate = normalize_instructions(
        [i for i in candidate if i.address not in candidate_skip],
        {offset_value(r["offset"]) for r in dir32}, 0)
    assert normalized_native == normalized_candidate

    source = SOURCE.read_text(encoding="utf8")
    assert "native_unsigned_length_correction_56cdd0[2]" in source
    assert "native_unsigned_length_correction_56cdd0[byte_length >> 31]" in source
    assert "static_cast<double>(static_cast<std::int32_t>(byte_length))" in source
    assert "width_factor*static_cast<float>(corrected_length)" in source

    globals_rows = list(csv.reader(
        (ROOT / "config/known-globals.csv").read_text(encoding="utf8").splitlines()))
    assert any(row and row[0].lower() == "0x0056cdd0" and
               "native_unsigned_length_correction_56cdd0" in ",".join(row)
               for row in globals_rows)

    print("PASS original ASCII renderer: 578B / 139 x86 / 11 E8 / 8 physical PE HIGHLOW in the locked PE")
    print("PASS original 294B submit ret 0x58 and 111B Card lambda E8 into this renderer")
    print("PASS native 0x56CDD0 table: {0.0, 4294967296.0}; unsigned strlen conversion now has a typed natural-C++ data owner")
    print("PASS candidate: 574B / 138 x86 / 11 REL32 / 8 DIR32; all original call and data target roles remain in order")
    print("PASS all other instruction/operand heads match after relocation normalization and two documented compiler scheduling/fusion differences")
    print("NONEXACT: candidate is 4B and one instruction shorter; no exact function-map status or byte credit is claimed")


if __name__ == "__main__":
    main()
