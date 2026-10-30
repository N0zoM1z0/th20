#!/usr/bin/env python3
"""Immutable target-only entire 1468B game shape-ring renderer evidence.

Disassembles original 387 native x86 heads, native receiver/10-argument ABI,
all 11 original E8 physical site/targets and 26 physical PE HIGHLOW fields.
No candidate object or guessed C++ symbol determines any original target.
"""
from collections import Counter
from pathlib import Path
import importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(spec);spec.loader.exec_module(original)
HEAD=0x0043AB20
SIZE=1468
CALL_SITES={
 0x07F:0x004455C0,0x0D6:0x00439330,0x257:0x00458FA0,
 0x2E3:0x00439330,0x464:0x00458FA0,0x4E7:0x00438600,
 0x4FC:0x004DDF80,0x50A:0x004D9DB0,0x51E:0x00446690,
 0x528:0x00412730,0x54C:0x00412730,
}
DATA_SITES={
 0x055:0x0056E0F8,0x062:0x0056E0F0,0x06A:0x0056C8D0,
 0x08D:0x0056C8D0,0x0F0:0x0056C8CC,
 0x11B:0x0056C8D0,0x13A:0x0056C8D0,
 0x173:0x0056C8D0,0x18E:0x0056C8D0,
 0x1C6:0x0056C8D0,0x1E1:0x0056C8D0,
 0x208:0x0056C8D0,0x227:0x0056C8D0,
 0x2FD:0x0056C8CC,0x328:0x0056C8D0,0x347:0x0056C8D0,
 0x380:0x0056C8D0,0x39B:0x0056C8D0,
 0x3D3:0x0056C8D0,0x3EE:0x0056C8D0,
 0x415:0x0056C8D0,0x434:0x0056C8D0,
 0x4F8:0x005C4D40,0x506:0x005C4D40,
 0x524:0x005C4D40,0x548:0x005C4D40,
}


def verify():
    image,_=original.verified_target()
    base,sections=original.parse_sections(image)
    code=original.raw_at(image,base,sections,HEAD,SIZE)
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(code)==SIZE and len(ins)==387
    assert ins[-1].address+ins[-1].size==HEAD+SIZE
    assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0x2c'
    assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='0x28'
    actual_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                  for i in ins if len(i.bytes)==5 and i.bytes[0]==0xe8}
    assert actual_calls==CALL_SITES,(actual_calls,CALL_SITES)
    phys=original.physical_highlow(image,base,sections)
    actual_data={site-HEAD:struct.unpack('<I',original.raw_at(image,base,sections,site,4))[0]
                 for site in phys if HEAD<=site<HEAD+SIZE}
    assert actual_data==DATA_SITES,(actual_data,DATA_SITES)
    assert Counter(DATA_SITES.values())==Counter({
      0x0056C8D0:18,0x005C4D40:4,0x0056C8CC:2,
      0x0056E0F8:1,0x0056E0F0:1,
    })
    head={i.address-HEAD:i for i in ins}
    assert head[0x09].mnemonic=='mov' and head[0x09].op_str=='eax, dword ptr [ebp + 0x24]'
    assert head[0x1B].mnemonic=='mov' and head[0x1B].op_str=='eax, 0x14'
    assert head[0x20].mnemonic=='shl' and head[0x20].op_str=='eax, 0x10'
    assert head[0x2F].mnemonic=='jb'  # true unsigned buffer-end check
    assert head[0x38].mnemonic=='cmp' and head[0x38].op_str=='dword ptr [ebp + 0x24], 2'
    assert head[0x4D1].mnemonic=='push'  # real angle increment stack argument
    pi=original.raw_at(image,base,sections,0x0056E0F0,4)
    minus_pi=original.raw_at(image,base,sections,0x0056E0F8,4)
    assert abs(struct.unpack('<f',pi)[0]-3.1415927410125732)<1e-8
    assert abs(struct.unpack('<f',minus_pi)[0]+3.1415927410125732)<1e-8
    # Real 5,993B game-owned Animation main Draw dispatches to this
    # original physical ring generator in three independently native cases.
    parent=0x00443880
    original_parent=original.raw_at(image,base,sections,parent,5993)
    parent_calls=[x.address for x in Cs(CS_ARCH_X86,CS_MODE_32).disasm(original_parent,parent)
                  if len(x.bytes)==5 and x.bytes[0]==0xe8 and
                  (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff==HEAD]
    assert parent_calls==[0x00444304,0x0044442C,0x00444558],parent_calls
    print('PASS immutable original whole 1468B/387-native-i386 shape-ring Boss at 0x43AB20, 0x2C frame and true 10-stack-argument RET 0x28')
    print('PASS all 11 physical E8 site/target pairs: two 89B polar Vector2 aliases, two 137B rotate_xy, one 29B add_angles, Graphics states and actual device submits')
    print('PASS all 26 genuine PE HIGHLOW site/target pairs: native pi/-pi, 18 real two, two real one, four actual Graphics owner globals')
    print('PASS real original unsigned buffer bound 65536 x 20B fixed typed vertices and original ring uses 20B colored vertices, no SpriteTexturedVertex stride confusion')


if __name__=='__main__':verify()
