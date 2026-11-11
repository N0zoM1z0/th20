#!/usr/bin/env python3
"""Original 111B Animation pool staging reset: full function and real callers."""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
def load(name, path):
    spec = importlib.util.spec_from_file_location(name, ROOT / path)
    module = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

pe = load('staging_pe', 'scripts/verify-animation-draw-boss-native.py')
cf = load('staging_coff', 'scripts/compare-coff-function.py')
HEAD = 0x00445A40
SIZE = 111
BODY_SHA = '5926f138147b933a68c1e3d7e85d7bbf87cafd36c812a160b82ead7fd171f16d'
SYM = '?reset_staging_buffers_445a40@NativeAnimationPoolStagingView@th20@@QAEXXZ'
CALLS = (0x00419D1C, 0x00419F72, 0x0041A0ED)


def main():
    original = cf.verified_target()
    base, sections = pe.parse_sections(original)
    code = cf.pe_bytes_at(original, HEAD, SIZE)
    assert hashlib.sha256(code).hexdigest() == BODY_SHA
    native = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(code, HEAD))
    assert len(native) == 29 and native[-1].address + native[-1].size == HEAD + SIZE
    assert (native[-1].mnemonic, native[-1].op_str) == ('ret', '')
    assert all(i.bytes[0] != 0xE8 for i in native)
    relocs = pe.physical_highlow(original, base, sections)
    assert not any(HEAD <= site < HEAD + SIZE for site in relocs)
    # The actual game has three frame recovery paths. Each reads the same
    # process pool pointer before its physical call, not a fabricated owner.
    for call in CALLS:
        assert cf.pe_bytes_at(original, call - 6, 6) == bytes.fromhex('8b0d28005c00')
        assert cf.pe_bytes_at(original, call, 1) == b'\xe8'
        signed_disp = struct.unpack('<i', cf.pe_bytes_at(original, call + 1, 4))[0]
        assert call + 5 + signed_disp == HEAD
    obj = ROOT / 'build/core1115-canonical/AnimationPoolResetStaging111.obj'
    generated, fields = cf.object_function(obj, SYM, SIZE)
    assert len(generated) == SIZE and not fields
    assert bytes(generated) == code
    result = cf.compare_unit('animation_pool_staging_reset_111')
    assert result['result'] == 'exact' and result['matched_bytes'] == SIZE
    print('PASS original 111B/29-instruction whole Animation pool staging reset; SHA-pinned, no native E8/HIGHLOW')
    print('PASS three original frame recovery callers load actual process AnimationPoolOwner +0x5C0028')
    print('PASS fresh canonical source 111/111 whole exact, no compiler relocation, no unrelated source replay')

if __name__ == '__main__':
    main()
