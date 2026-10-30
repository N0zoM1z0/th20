#!/usr/bin/env python3
"""Original-only native audit of the complete +0xB40 polygon accessor."""
from pathlib import Path
import importlib.util
import struct

from capstone import CS_ARCH_X86, CS_MODE_32, Cs

ROOT = Path(__file__).resolve().parents[1]
spec = importlib.util.spec_from_file_location(
    "pe", ROOT / "scripts/verify-animation-draw-boss-native.py"
)
pe = importlib.util.module_from_spec(spec)
spec.loader.exec_module(pe)
HEAD, SIZE = 0x0045ECA0, 19
CALLERS = (0x0045E7A2, 0x0045EA7A)


def verify():
    image, _ = pe.verified_target()
    base, sections = pe.parse_sections(image)
    highlow = pe.physical_highlow(image, base, sections)
    decoder = Cs(CS_ARCH_X86, CS_MODE_32)
    code = pe.raw_at(image, base, sections, HEAD, SIZE)
    decoded = list(decoder.disasm(code, HEAD))
    assert len(decoded) == 9 and decoded[-1].address + decoded[-1].size == HEAD + SIZE
    assert (decoded[-1].mnemonic, decoded[-1].op_str) == ("ret", "")
    assert ("add", "eax, 0xb40") in [(ins.mnemonic, ins.op_str) for ins in decoded]
    assert not any(ins.bytes[0] == 0xE8 for ins in decoded)
    assert not any(HEAD <= address < HEAD + SIZE for address in highlow)
    for address in CALLERS:
        call = pe.raw_at(image, base, sections, address, 5)
        assert call[0] == 0xE8
        destination = (address + 5 + struct.unpack_from("<i", call, 1)[0]) & 0xFFFFFFFF
        assert destination == HEAD, (hex(address), hex(destination))
        print(f"PASS original caller E8 {address:#010x} -> {HEAD:#010x}")
    print(f"PASS original 0x{HEAD:08X}: {SIZE}B/9 i386, add eax,0xB40, RET, no relocations")


if __name__ == "__main__":
    verify()
