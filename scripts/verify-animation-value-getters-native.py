#!/usr/bin/env python3
"""Independent original-PE evidence for three tiny Animation-owned getters.

Checks whole native 17-byte bodies, x87 thiscall receiver/field semantics,
absence of PE relocations, and real calls from game-owned large parents.
Authored-game classification is separate from an already strict COFF replay.
"""
from collections import defaultdict
from pathlib import Path
import struct
import sys

from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
from project import verified_target  # noqa:E402
import importlib.util

spec=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(spec)
spec.loader.exec_module(original)

# Original Animation-owned getters are distinct physically and return an x87
# float from the actual game AnimationBase offsets. Name spellings are ours.
GETTERS={
 0x00437930:('rotation_z_value',0x40),
 0x004379A0:('scale_y_value',0x54),
 0x004379C0:('scale_x_value',0x50),
}

# Original E8 instruction sites, re-attested from entire original caller
# bodies, never guessed from a decompiler/reference name.
EXPECTED_CALLS={
 0x00437930:{0x00443C28,0x00443C79,0x00437AB8},
 0x004379A0:{0x00435EB4,0x00436346,0x00436BFE,0x00437B19},
 0x004379C0:{0x00435E8E,0x00436320,0x004366CF,0x00436BD8,0x00437AEB},
}
ORIGINAL_CALLER_BODIES={
 0x00443880:(5993,'renderer draw Boss, game-owned NONEXACT'),
 0x00435C80:(5388,'Animation geometry update Boss, game-owned strict exact'),
 0x004379E0:(660,'Animation transform position, game-owned strict exact'),
}


def verify():
    image,_=verified_target()
    base,sections=original.parse_sections(image)
    highlow=original.physical_highlow(image,base,sections)
    asm=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,(label,field) in GETTERS.items():
        raw=original.raw_at(image,base,sections,head,17)
        instructions=list(asm.disasm(raw,head))
        assert len(instructions)==9
        assert [i.mnemonic for i in instructions]==[
            'push','mov','push','mov','mov','fld','mov','pop','ret'
        ]
        assert instructions[3].op_str=='dword ptr [ebp - 4], ecx'
        assert instructions[4].op_str=='eax, dword ptr [ebp - 4]'
        assert instructions[5].op_str==f'dword ptr [eax + {field:#x}]'
        assert instructions[-1].address+instructions[-1].size==head+17
        assert not any(head<=r<head+17 for r in highlow)
        print(f'PASS original {label} at {head:#010x}: whole 17B/9 x86, actual thiscall receiver and float field +{field:#x}, no PE data relocations')

    physical_calls=defaultdict(set)
    for head,(size,description) in ORIGINAL_CALLER_BODIES.items():
        body=original.raw_at(image,base,sections,head,size)
        ins=list(asm.disasm(body,head))
        assert ins and ins[-1].address+ins[-1].size==head+size
        for i in ins:
            if i.bytes[0]==0xE8 and len(i.bytes)==5:
                target=(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                if target in GETTERS:
                    physical_calls[target].add(i.address)
    assert dict(physical_calls)==EXPECTED_CALLS,(physical_calls,EXPECTED_CALLS)
    assert sum(len(v) for v in physical_calls.values())==12
    print('PASS 12 original physical E8 sites from three game-owned callers, including whole 5388B geometry Boss, 660B transform and 5993B draw Boss')
    print('Authorship provenance: these are custom Animation getters invoked in original gameplay, not C++ STL/compiler runtime; exact acceptance still requires pinned COFF replay')


if __name__=='__main__':
    verify()
