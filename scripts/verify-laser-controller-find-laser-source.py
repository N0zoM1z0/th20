#!/usr/bin/env python3
"""Verify the native LaserController::find_laser handle-search leaf."""
from __future__ import annotations

import hashlib
import re
import subprocess
from pathlib import Path

import pefile
from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
PE = ROOT / "resources/th20.exe"
PE_SHA256 = "a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897"
START = 0x00498FF0
SIZE = 230
END = START + SIZE
SHA256 = "0b577415aa056a83ebb14cc6fde44c32a3524368450ee6951ae6ee0ae0770d1f"
OBJECT = ROOT / "build/gpt-web-laser-canonical/LaserControllerFindLaser.obj"
SYMBOL = "?find_laser@LaserController@th20@@QAEPAVLaser@2@H@Z"

NATIVE_CALLS = [
    (0x00499029, 0x0040C080),  # zero-initialize the two-pointer iterator
    (0x00499035, 0x00412280),  # active-list begin iterator construction
    (0x00499044, 0x00412540),  # null end iterator
    (0x00499051, 0x00411C30),  # advance
    (0x0049905E, 0x00411BB0),  # differs
    (0x0049906D, 0x0040C300),  # iterator get
    (0x00499078, 0x0040C300),  # link node for +0x8C handle comparison
    (0x0049908B, 0x0040C300),  # link node again on the match return path
    (0x0049909D, 0x00411B00),  # iterator destructor on match
    (0x004990B3, 0x00411B00),  # iterator destructor on miss
    (0x004990CB, 0x005429EE),  # security-cookie check
]

COFF_CALLS = [
    "?__autoclassinit2@?$IntrusiveIterator@VLaser@th20@@@th20@@QAEXI@Z",
    "?begin@?$IntrusiveList@VLaser@th20@@@th20@@QAE?AV?$IntrusiveIterator@VLaser@th20@@@2@XZ",
    "?end@?$IntrusiveList@VLaser@th20@@@th20@@QAEPAV?$IntrusiveIterator@VLaser@th20@@@2@XZ",
    "?advance@?$IntrusiveIterator@VLaser@th20@@@th20@@QAEAAV12@XZ",
    "?differs@?$IntrusiveIterator@VLaser@th20@@@th20@@QBE_NPBV12@@Z",
    "?get@?$IntrusiveIterator@VLaser@th20@@@th20@@QAEPAV?$IntrusiveLink@VLaser@th20@@@2@XZ",
    "?node_value@?$IntrusiveLink@VLaser@th20@@@th20@@QAEPAVLaser@2@XZ",
    "?node_value@?$IntrusiveLink@VLaser@th20@@@th20@@QAEPAVLaser@2@XZ",
    "??1?$IntrusiveIterator@VLaser@th20@@@th20@@QAE@XZ",
    "??1?$IntrusiveIterator@VLaser@th20@@@th20@@QAE@XZ",
    "@__security_check_cookie@4",
]


def main() -> None:
    pe_bytes = PE.read_bytes()
    assert hashlib.sha256(pe_bytes).hexdigest() == PE_SHA256
    pe = pefile.PE(data=pe_bytes, fast_load=True)
    native = pe.get_data(START - pe.OPTIONAL_HEADER.ImageBase, SIZE)
    assert len(native) == SIZE
    assert hashlib.sha256(native).hexdigest() == SHA256

    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(native, START))
    assert len(instructions) == 70
    assert instructions[0].address == START
    assert instructions[-1].address + instructions[-1].size == END
    assert instructions[-1].mnemonic == "ret" and instructions[-1].op_str == "4"
    native_calls = [
        (insn.address, int(insn.op_str, 16))
        for insn in instructions
        if insn.mnemonic == "call" and insn.op_str.startswith("0x")
    ]
    assert native_calls == NATIVE_CALLS, native_calls

    # The native +0x8C handle comparison uses a signed 32-bit argument but
    # compares the same 32-bit representation. It obtains the link's node a
    # second time only on the successful return path, then destroys the local
    # iterator on both match and miss exits.
    native_text = "\n".join(f"{i.mnemonic} {i.op_str}" for i in instructions)
    assert "[eax + 0x8c]" in native_text
    assert native_text.count("call 0x40c300") == 3
    assert native_text.count("call 0x411b00") == 2

    source = (ROOT / "src/LaserControllerFindLaser.cpp").read_text(encoding="utf8")
    for fragment in (
        "Laser* LaserController::find_laser(std::int32_t handle)",
        "auto iterator = active.begin();",
        "auto* const last = active.end();",
        "for (; iterator.differs(last); iterator.advance())",
        "auto* const link = iterator.get();",
        "link->node_value()->handle == static_cast<std::uint32_t>(handle)",
        "return link->node_value();",
        "return nullptr;",
        "offsetof(LaserController, active) == 0x10",
        "offsetof(Laser, handle) == 0x8c",
    ):
        assert fragment in source, fragment
    assert "asm(" not in source and "__asm" not in source

    tests = (ROOT / "tests/enemy_state_dispatch_root.cpp").read_text(encoding="utf8")
    for fragment in (
        "find_laser(0x11223344) == nullptr",
        "find_laser(0x55667788) == &find_laser_second",
        "find_laser(0x99aabbcc) == nullptr",
        "find_laser(0x11223344) == &find_laser_first",
        "find_laser(-1) == &find_laser_first",
        "find_laser_first.link.iterator == nullptr",
        "find_laser_second.link.iterator == nullptr",
    ):
        assert fragment in tests, fragment

    dump = subprocess.run(
        ["objdump", "-dr", str(OBJECT)], cwd=ROOT, check=True,
        text=True, capture_output=True,
    ).stdout
    marker = f"<{SYMBOL}>:"
    assert marker in dump
    function = dump.split(marker, 1)[1].split("Disassembly of section", 1)[0]
    coff_calls = re.findall(r"DISP32\s+([^\r\n]+)", function)
    assert len(coff_calls) == len(COFF_CALLS), (coff_calls, COFF_CALLS)
    for actual, expected in zip(coff_calls, COFF_CALLS):
        assert expected in actual, (actual, expected)
    assert "0x8c(" in function
    assert function.count("?node_value@?$IntrusiveLink@VLaser") == 2
    assert function.count("??1?$IntrusiveIterator@VLaser") == 2
    assert "ret    $0x4" in function

    symbols = subprocess.run(
        ["objdump", "-t", str(OBJECT)], cwd=ROOT, check=True,
        text=True, capture_output=True,
    ).stdout
    assert SYMBOL in symbols

    print("PASS original LaserController::find_laser: 230B / 70 x86 / 11 ordered direct calls, including both node reads and both iterator cleanup exits")
    print("PASS native +0x8C signed-handle comparison, match-only second node lookup, null miss and ret 4")
    print("PASS natural C++ COFF preserves begin/end/advance/differs/get/node/node/dtor/dtor/cookie relocation order")
    print("PASS root-host real intrusive Laser list covers empty, later hit, miss, first duplicate, signed -1 and iterator observer cleanup")


if __name__ == "__main__":
    main()
