#!/usr/bin/env python3
"""Independent original PE-only renderer draw-call ABI and ownership audit.

Confirms the original 2769B thiscall mode6 receiver and 18 native draw
backend callee cleanup widths. The source ledger/decompiler is not treated
as authority for these stack contracts. This does not establish parent exactness.
"""
from pathlib import Path
import csv
import importlib.util
import sys
import struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('abi_native',ROOT/'scripts/verify-animation-draw-boss-native.py')
native=importlib.util.module_from_spec(sp)
sp.loader.exec_module(native)

# Original backend heads -> observed original full-native callee stack byte cleanup.
# Both previously assumed seven-argument methods at CD40/C4E0 actually take
# EIGHT parameters and have the original native `ret 0x20`.
BACKENDS={
    0x00439A00:0x24,0x0043A1C0:0x24,0x0043A2B0:0x24,
    0x0043A750:0x20,0x0043AB20:0x28,0x0043B0E0:0x24,
    0x0043B960:0x1C,0x0043BC60:0x18,0x0043BE80:0x20,
    0x0043C180:0x20,0x0043C4E0:0x20,0x0043C780:0x24,
    0x0043CD40:0x20,0x0043D830:0x0C,0x0043D9B0:0x20,
    0x0043DCE0:0x1C,0x0043DF30:0x24,0x0043E2C0:0x24,
}


def verify():
    pe,_=native.verified_target()
    base,sections=native.parse_sections(pe)
    rows=list(csv.DictReader((ROOT/'config/functions.csv').open(newline='',encoding='utf-8')))
    original_sizes={int(r['address'],16):int(r['size']) for r in rows}
    for head,popped in sorted(BACKENDS.items()):
        size=original_sizes[head]
        body=native.decoded(pe,base,sections,head,size)
        tail=body[-1]
        assert tail.mnemonic=='ret' and tail.op_str==hex(popped)
        assert tail.address+tail.size==head+size
        assert not any(x.mnemonic=='ret' and x.op_str!=hex(popped) for x in body)
    assert len(BACKENDS)==18

    mode6=0x004408B0
    whole=native.decoded(pe,base,sections,mode6,original_sizes[mode6])
    assert len(whole)>300 and whole[-1].mnemonic=='ret'
    assert whole[-1].op_str=='4' and whole[-1].address+whole[-1].size==mode6+2769
    mode6_head={i.address-mode6:i for i in whole}
    assert mode6_head[0x11].mnemonic=='mov' and mode6_head[0x11].op_str=='dword ptr [ebp - 0x20], ecx'
    assert mode6_head[0x14].mnemonic=='mov' and mode6_head[0x14].op_str=='eax, dword ptr [ebp + 8]'
    assert mode6_head[0x17].mnemonic=='push' and mode6_head[0x17].op_str=='eax'
    assert mode6_head[0x18].mnemonic=='mov' and mode6_head[0x18].op_str=='ecx, dword ptr [ebp - 0x20]'
    assert mode6_head[0x1B].mnemonic=='call' and mode6_head[0x1B].op_str=='0x440340'

    boss=native.decoded(pe,base,sections,native.HEAD,native.BODY_SIZE)
    at={i.address-native.HEAD:i for i in boss}
    assert at[0x19E].mnemonic=='mov' and at[0x19E].op_str=='ecx, dword ptr [ebp + 8]'
    assert at[0x1A1].mnemonic=='push' and at[0x1A1].op_str=='ecx'
    assert at[0x1A2].mnemonic=='mov' and at[0x1A2].op_str=='ecx, dword ptr [ebp - 0x14]'
    assert at[0x1A5].op_str=='0x4408b0' and at[0x1A5].mnemonic=='call'
    # Mode 26 real argument fields: the original reads and later pushes BOTH
    # Animation+0x4AC and +0x4A8 before two packed-color source arguments.
    assert at[0x4EE].op_str=='ecx, dword ptr [eax + 0x4ac]'
    assert at[0x4FA].op_str=='eax, dword ptr [edx + 0x4a8]'
    assert at[0x53F].mnemonic=='push' and at[0x543].mnemonic=='push'
    assert at[0x57B].mnemonic=='call' and at[0x57B].op_str=='0x43cd40'
    # Mode 33 original two packed color getters, BOTH real stack arguments.
    for off,callee in [(0xE91,0x004456C0),(0xE9F,0x004456E0),(0xF19,0x0043C4E0)]:
        ins=at[off]
        assert ins.mnemonic=='call' and ins.op_str==f'0x{callee:x}'
    assert at[0xECD].mnemonic=='push' and at[0xED4].mnemonic=='push'
    print('PASS original 18/18 renderer backend full-native RET immediate stack widths (not guessed prototypes)')
    print('PASS mode6 original whole 2769B/thiscall: ECX renderer, one stack Animation*, RET 4')
    print('PASS native case26 two original integer arguments and case33 two real packed colors; both callees RET 0x20')
    print('PARENT NONEXACT: validating original ABI boundaries does not accept the 5993B dispatcher')


if __name__=='__main__':verify()
