#!/usr/bin/env python3
"""Verify the complete original 244B Animation corner projection dispatcher."""
from __future__ import annotations
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "scripts"))

def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

pe = load("corner_dispatch_pe", "scripts/verify-animation-draw-boss-native.py")
coff = load("corner_dispatch_coff", "scripts/compare-coff-function.py")
HEAD = 0x00445770
SIZE = 244
COMPARE_SIZE = 260
NATIVE_SHA256 = "16c02538c572c3e989500be8e565718ad06648de0ddf07436d07aa95267785c4"
SYMBOL = "?project_corners@Animation@th20@@QAEXPAUVector3@2@@Z"
OWNER = "?current_animation_pool@th20@@3PAUAnimationPoolOwner@1@A"
PROJECTOR = "?project_corners_43eb40@NativeAnimationCornerProjector@th20@@QAEXPAVAnimation@2@PAUVector3@2@111@Z"
ROTATED = "?project_rotated_corners_43ef20@NativeAnimationCornerProjector@th20@@QAEXPAVAnimation@2@PAUVector3@2@111@Z"
BODY_RELOCATIONS = (
    (0x26, "DIR32", "$LN9", HEAD + SIZE),
    (0x5F, "DIR32", OWNER, 0x005C0028),
    (0x64, "REL32", PROJECTOR, 0x0043EB40),
    (0xA3, "DIR32", OWNER, 0x005C0028),
    (0xA8, "REL32", ROTATED, 0x0043EF20),
    (0xE4, "DIR32", OWNER, 0x005C0028),
    (0xE9, "REL32", PROJECTOR, 0x0043EB40),
)
TABLE_RELOCATIONS = (
    (0xF4, "DIR32", "$LN4", 0x0044579A),
    (0xF8, "DIR32", "$LN5", 0x004457DE),
    (0xFC, "DIR32", "$LN6", 0x0044581F),
    (0x100, "DIR32", "$LN6", 0x0044581F),
)
EXPECTED_CALLS = ((0x63, 0x0043EB40), (0xA7, 0x0043EF20), (0xE8, 0x0043EB40))
EXPECTED_BODY_HIGHLOW = (0x26, 0x5F, 0xA3, 0xE4)
EXPECTED_TABLE_HIGHLOW = (0xF4, 0xF8, 0xFC, 0x100)

def verify_original():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    body = pe.raw_at(image, base, sections, HEAD, SIZE)
    digest = hashlib.sha256(body).hexdigest()
    assert digest == NATIVE_SHA256, (digest, NATIVE_SHA256)
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(body, HEAD))
    assert len(instructions) == 79, len(instructions)
    assert instructions[-1].address + instructions[-1].size == HEAD + SIZE
    assert instructions[-1].mnemonic == "ret" and instructions[-1].op_str == "4"
    calls = []
    for item in instructions:
        if item.size == 5 and item.bytes[0] == 0xE8:
            destination = (item.address + 5 + struct.unpack_from("<i", item.bytes, 1)[0]) & 0xFFFFFFFF
            calls.append((item.address - HEAD, destination))
    assert tuple(calls) == EXPECTED_CALLS, calls
    body_highlow = tuple(sorted(address - HEAD for address in pe.physical_highlow(image, base, sections)
                                if HEAD <= address < HEAD + SIZE))
    table_highlow = tuple(sorted(address - HEAD for address in pe.physical_highlow(image, base, sections)
                                 if HEAD + SIZE <= address < HEAD + COMPARE_SIZE))
    assert body_highlow == EXPECTED_BODY_HIGHLOW, body_highlow
    assert table_highlow == EXPECTED_TABLE_HIGHLOW, table_highlow
    table = pe.raw_at(image, base, sections, HEAD + SIZE, 16)
    table_values = tuple(struct.unpack_from("<I", table, index * 4)[0] for index in range(4))
    assert table_values == (0x0044579A, 0x004457DE, 0x0044581F, 0x0044581F), table_values
    return body, table

def verify_candidate(path: Path, native_body: bytes, native_table: bytes):
    body, relocations = coff.object_function(path, SYMBOL, COMPARE_SIZE)
    assert len(body) == COMPARE_SIZE, len(body)
    expected = BODY_RELOCATIONS + TABLE_RELOCATIONS
    actual = tuple(sorted((int(item["offset"]), str(item["type"]), str(item["symbol"]),
                           (HEAD + int(item["section_delta"])) if item["section_delta"] is not None
                           else ({OWNER: 0x005C0028, PROJECTOR: 0x0043EB40, ROTATED: 0x0043EF20}[str(item["symbol"])]))
                          for item in relocations))
    assert actual == tuple(sorted(expected)), (actual, expected)

    code = body[:SIZE]
    instructions = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, 0))
    assert len(instructions) == 79, len(instructions)
    assert sum(item.size for item in instructions) == SIZE
    calls = [item.address for item in instructions if item.size == 5 and item.bytes[0] == 0xE8]
    assert calls == [0x63, 0xA7, 0xE8], calls
    ret = instructions[-1]
    assert ret.address == 0xF1 and ret.mnemonic == "ret" and ret.op_str == "4"

    resolved_code = bytearray(code)
    for offset, kind, symbol, target in BODY_RELOCATIONS:
        value = target if kind == "DIR32" else (target - (HEAD + offset + 4)) & 0xFFFFFFFF
        struct.pack_into("<I", resolved_code, offset, value)
    assert bytes(resolved_code) == native_body, "relocated native body differs"

    resolved_table = bytearray(16)
    for offset, kind, symbol, target in TABLE_RELOCATIONS:
        assert kind == "DIR32"
        struct.pack_into("<I", resolved_table, offset - SIZE, target)
    assert bytes(resolved_table) == native_table, "relocated switch table differs"
    assert body[SIZE:] == bytes(16), "COFF table placeholders must be independently relocated"
    return body

def main():
    native_body, native_table = verify_original()
    print("PASS original 244B/79-i386 dispatcher SHA, RET 4, three E8 targets, four body and four table HIGHLOW fields")
    if len(sys.argv) == 3 and sys.argv[1] == "--candidate-object":
        candidate = verify_candidate(Path(sys.argv[2]), native_body, native_table)
        print(f"PASS candidate {len(candidate)}B complete contribution: 244B exact code + 16B exact switch table")
        print("PASS all 11 COFF relocations: switch base, three current_animation_pool references, three projector calls and four table targets")
        print("PASS whole original relocated 260B contribution; origin remains separately tracked")
    elif len(sys.argv) > 1:
        raise SystemExit("usage: verify-animation-corner-projection-dispatch244-native.py [--candidate-object OBJECT]")
    else:
        print("ORIGINAL ONLY: pass --candidate-object build/...obj for full candidate verification")

if __name__ == "__main__":
    main()
