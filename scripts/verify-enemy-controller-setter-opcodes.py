#!/usr/bin/env python3
"""Verify Enemy 553/554 source against original PE branch bytes and call order."""
from __future__ import annotations

import hashlib
import json
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE_PATH = ROOT / "resources/th20.exe"
SOURCE = ROOT / "src/EnemyStateControllerSetterOpcode.cpp"
BASE = 0x00400000
CASES = {
    553: (0x00495860, 66, 14, "4030df83f9633828d0156d8759983656132a5c4e45d94b5d21a91c143942165f", {
        0x0049586C: 0x00412730,
        0x0049587F: 0x004AB080,
        0x00495897: 0x0049C490,
    }),
    554: (0x004961D5, 106, 22, "d43e9bc1b266c2d0765936e696da08cc6f3f961425a30492e631ef5f156ffb27", {
        0x004961E1: 0x0040C300,
        0x004961F4: 0x004AAFB0,
        0x00496207: 0x004AAFB0,
        0x00496234: 0x00486480,
    }),
}


def main() -> None:
    pe_bytes = PE_PATH.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    source = SOURCE.read_text(encoding="utf8")
    for opcode, (start, size, count, digest, expected_calls) in CASES.items():
        raw = pe.get_data(start - BASE, size)
        assert len(raw) == size and hashlib.sha256(raw).hexdigest() == digest
        instructions = list(decoder.disasm(raw, start))
        assert len(instructions) == count
        calls = {insn.address: int(insn.op_str, 16)
                 for insn in instructions
                 if insn.mnemonic == "call" and insn.op_str.startswith("0x")}
        assert calls == expected_calls, calls
        assert f"case {opcode}:" in source
        print(f"PASS original opcode {opcode}: {size}B/{count} x86 and {len(calls)} E8 sites")

    case553 = source.split("case 553:", 1)[1].split("case 554:", 1)[0]
    case554 = source.split("case 554:", 1)[1].split("default:", 1)[0]
    assert case553.index("state.context->enemy_controller()") < case553.index("state.integer_argument(0)") < case553.index("owner->set_field_88(value)")
    assert case554.index("state.context->bullet_controller()") < case554.index("state.float_argument(1)") < case554.index("state.float_argument(0)") < case554.index("owner->set_vector_4c(x, y)")
    print("PASS opcode 553 caches EnemyController before operand 0; opcode 554 caches BulletController and reads Y before X")
    print("PASS real typed setter methods; original 41,967B Enemy parent remains NONEXACT")


if __name__ == "__main__":
    main()
