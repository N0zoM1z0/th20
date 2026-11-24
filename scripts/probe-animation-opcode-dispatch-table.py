#!/usr/bin/env python3
"""Strictly replay the 636-byte native Animation VM opcode map as C++ data."""
from __future__ import annotations
import hashlib
import importlib.util
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))


def load(name: str, path: Path):
    spec = importlib.util.spec_from_file_location(name, path)
    module = importlib.util.module_from_spec(spec)
    assert spec.loader is not None
    spec.loader.exec_module(module)
    return module


pe = load('animation_opcode_dispatch_pe', ROOT / 'scripts/verify-animation-draw-boss-native.py')
ADDRESS = 0x00435284
SIZE = 0x27C
SHA256 = 'a030f37522ea5b860c9a06ab56c02978832b477fd4e7c6f94957fbadc7cab34d'
SYMBOL = '?native_animation_opcode_dispatch_435284@th20@@3QBEB'
SOURCE = ROOT / 'src/AnimationOpcodeDispatchTable.cpp'
OBJECT = ROOT / 'build/gptweb-animation-opcode-dispatch/AnimationOpcodeDispatchTable.obj'
FLAGS = [
    '/nologo', '/c', '/std:c++20', '/Od', '/Ob0', '/GS', '/Gy', '/Zl',
    '/arch:SSE2', '/fp:precise', '/sdl', '/EHsc',
]


def coff_name(raw: bytes, strings: bytes) -> str:
    if raw[:4] == b'\0\0\0\0':
        offset = struct.unpack_from('<I', raw, 4)[0]
        if not 4 <= offset < len(strings):
            raise ValueError(f'invalid COFF string-table offset {offset}')
        return strings[offset:].split(b'\0', 1)[0].decode('ascii')
    return raw.split(b'\0', 1)[0].decode('ascii')


def read_defined_data(path: Path) -> tuple[bytes, str, int]:
    data = path.read_bytes()
    if len(data) < 20:
        raise ValueError('truncated COFF object')
    machine, section_count, _, symbol_offset, symbol_count, optional_size, _ = struct.unpack_from(
        '<HHIIIHH', data, 0
    )
    if machine != 0x14C or optional_size != 0:
        raise ValueError('expected i386 COFF without an optional header')
    sections = []
    for index in range(section_count):
        offset = 20 + index * 40
        fields = struct.unpack_from('<8sIIIIIIHHI', data, offset)
        sections.append({
            'name': fields[0].split(b'\0', 1)[0].decode('ascii'),
            'size': fields[3],
            'raw': fields[4],
            'reloc': fields[5],
            'reloc_count': fields[7],
            'flags': fields[9],
        })
    strings_offset = symbol_offset + symbol_count * 18
    strings_size = struct.unpack_from('<I', data, strings_offset)[0]
    strings = data[strings_offset:strings_offset + strings_size]
    found = []
    index = 0
    while index < symbol_count:
        offset = symbol_offset + index * 18
        raw_name, value, section_number, type_id, storage_class, aux_count = struct.unpack_from(
            '<8sIhHBB', data, offset
        )
        name = coff_name(raw_name, strings)
        if name == SYMBOL:
            found.append((value, section_number, type_id, storage_class))
        index += 1 + aux_count
    if len(found) != 1:
        raise ValueError(f'expected exactly one definition of {SYMBOL}, found {len(found)}')
    value, section_number, type_id, storage_class = found[0]
    if section_number <= 0 or type_id != 0 or storage_class != 2:
        raise ValueError((section_number, type_id, storage_class))
    section = sections[section_number - 1]
    if not section['name'].startswith('.rdata') or section['reloc_count'] != 0:
        raise ValueError(f'unexpected data section ownership: {section}')
    start = section['raw'] + value
    payload = data[start:start + SIZE]
    if len(payload) != SIZE or value + SIZE > section['size']:
        raise ValueError('COFF data symbol does not own the complete 636-byte table')
    return payload, section['name'], section['reloc_count']


def main() -> None:
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    original = pe.raw_at(image, base, sections, ADDRESS, SIZE)
    digest = hashlib.sha256(original).hexdigest()
    assert digest == SHA256, (digest, SHA256)
    assert original[0] == 0 and original[1] == 0xA0 and original[-1] == 0x9F
    assert original.count(0xA0) == 475

    OBJECT.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([
        str(ROOT / 'scripts/repo-python'),
        str(ROOT / 'scripts/compile-probe.py'), str(SOURCE), str(OBJECT), *FLAGS,
    ], cwd=ROOT, check=True)
    candidate, section_name, reloc_count = read_defined_data(OBJECT)
    assert candidate == original
    print(f'PASS original .rdata {SIZE}B at 0x{ADDRESS:08X}: SHA-256 {SHA256}')
    print(f'PASS C++ data owner {section_name}: {len(candidate)}/{SIZE} bytes exact, {reloc_count} relocations')
    print('PASS external symbol ABI matches Animation::update sentinel-table reference')


if __name__ == '__main__':
    main()
