#!/usr/bin/env python3
"""Verify the original 39-byte Bullet::set_timer_4d8 native wrapper."""
from __future__ import annotations

import hashlib
import re
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE = ROOT / "resources/th20.exe"
START = 0x0049CAE0
SIZE = 39
END = START + SIZE
SHA256 = "1c8c8efe0e3529f45f58dcb33d31b0403d7a1c2392b694805653ee0889249658"
OBJECT = ROOT / "build/gpt-web-enemy-629-canonical/BulletTimer4D8.obj"
SYMBOL = "?set_timer_4d8@Bullet@th20@@QAEXM@Z"
TIMER_ASSIGN = "??4Timer@th20@@QAEXM@Z"


def section_bytes(text: str) -> bytes:
    result = bytearray()
    in_section = False
    for line in text.splitlines():
        if line.startswith("Contents of section .text$mn:"):
            in_section = True
            continue
        if not in_section:
            continue
        match = re.match(r"^\s*[0-9a-fA-F]{4,8}\s+(.+)$", line)
        if not match:
            continue
        for field in match.group(1).split():
            if re.fullmatch(r"(?:[0-9a-fA-F]{2}){1,4}", field):
                result.extend(bytes.fromhex(field))
            else:
                break
    return bytes(result)


def main() -> None:
    pe_bytes = PE.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == (
        "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
    )
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    native = pe.get_data(START - pe.OPTIONAL_HEADER.ImageBase, SIZE)
    assert len(native) == SIZE
    assert hashlib.sha256(native).hexdigest() == SHA256
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(native, START))
    assert len(instructions) == 14
    assert instructions[-1].address + instructions[-1].size == END
    calls = [
        (insn.address, int(insn.op_str, 16))
        for insn in instructions
        if insn.mnemonic == "call" and insn.op_str.startswith("0x")
    ]
    assert calls == [(0x0049CAFB, 0x0047C5F0)], calls
    assert instructions[-1].mnemonic == "ret"
    assert instructions[-1].op_str == "4"

    source = (ROOT / "src/BulletTimer4D8.cpp").read_text(encoding="utf8")
    header = (ROOT / "src/Bullet.hpp").read_text(encoding="utf8")
    assert "void Bullet::set_timer_4d8(float value)" in source
    assert "timer_4d8 = value;" in source
    assert "void set_timer_4d8(float value);" in header
    callback = (ROOT / "src/EnemyStateBulletClearOpcode.cpp").read_text(encoding="utf8")
    assert callback.count("bullet->set_timer_4d8(") == 2

    byte_dump = subprocess.run(
        ["objdump", "-s", "-j", ".text$mn", str(OBJECT)],
        cwd=ROOT, check=True, text=True, capture_output=True,
    ).stdout
    coff = section_bytes(byte_dump)
    assert len(coff) == SIZE, (len(coff), coff.hex())
    assert coff[:0x1C] == native[:0x1C]
    assert coff[0x20:] == native[0x20:]
    assert coff[0x1C:0x20] == bytes(4)

    relocations = subprocess.run(
        ["objdump", "-r", str(OBJECT)],
        cwd=ROOT, check=True, text=True, capture_output=True,
    ).stdout
    assert re.search(
        r"0000001c\s+DISP32\s+" + re.escape(TIMER_ASSIGN), relocations
    ), relocations
    symbols = subprocess.run(
        ["objdump", "-t", str(OBJECT)],
        cwd=ROOT, check=True, text=True, capture_output=True,
    ).stdout
    assert SYMBOL in symbols

    print("PASS original Bullet::set_timer_4d8: 39B / 14 x86 / one E8 to Timer::operator=(float)")
    print("PASS all 35 non-relocation bytes match the locked PE; REL32 at +0x1C resolves to 0x0047C5F0")
    print("PASS natural C++ Bullet+0x4D8 wrapper is used by both opcode-629 callback branches")


if __name__ == "__main__":
    main()
