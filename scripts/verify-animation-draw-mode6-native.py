#!/usr/bin/env python3
"""Independent whole original Mode6 2769B game renderer PE/call/table census.

Never use a candidate COFF or a historical source hypothesis to discover the
original 28 E8 destinations /78 PE HIGHLOW fields or five real switch heads.
This proves original roles, not source byte exactness of its open parent.
"""
from collections import Counter
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(sp);sp.loader.exec_module(original)
HEAD=0x004408B0
SIZE=2769
TABLE=HEAD+SIZE+3
COMPARE_SIZE=SIZE+3+5*4
CALL_SITES={
 0x1B:0x00440340,0x2F:0x00422E10,0x6F:0x00429570,0x87:0x00429570,
 0xA3:0x00429440,0x118:0x00445700,
 0x19E:0x0043F520,0x1B9:0x0043F520,0x1D4:0x0043F520,0x1EF:0x0043F520,
 0x486:0x0043F520,0x4A1:0x0043F520,0x4BC:0x0043F520,0x4D7:0x0043F520,
 0x4F2:0x0043F520,0x50D:0x0043F520,0x528:0x0043F520,0x543:0x0043F520,
 0x844:0x0043F4F0,0x859:0x0043F4F0,0x86E:0x0043F4F0,0x883:0x0043F4F0,
 0x8AA:0x0043F520,0x8C5:0x0043F520,0x8E0:0x0043F520,0x8FB:0x0043F520,
 0xABB:0x0043F6A0,0xAC6:0x005429EE,
}
DATA_TARGETS=Counter({
 0x005AEF20:28,0x005C5840:21,0x0056C8CC:8,
 0x005AEF23:6,0x005AEF21:4,0x005AEF22:4,
 0x0056C8D0:2,0x005B25C0:1,
 0x005B87F8:1,0x005B87FC:1,0x0056D7C0:1,0x00441384:1,
})
TABLE_TARGETS=[0x004409FC,0x004409FC,0x00440CFE,0x00440CFE,0x004410D2]


def verify():
    pe,_=original.verified_target()
    base,sections=original.parse_sections(pe)
    body=original.raw_at(pe,base,sections,HEAD,SIZE)
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(body)==SIZE and len(ins)==683
    assert ins[-1].address+ins[-1].size==HEAD+SIZE
    assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0x64'
    assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='4'
    calls={}
    for x in ins:
        if len(x.bytes)==5 and x.bytes[0]==0xE8:
            calls[x.address-HEAD]=(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
    assert calls==CALL_SITES,(calls,CALL_SITES)
    by_offset={x.address-HEAD:x for x in ins}
    assert by_offset[0x140].mnemonic=='jmp' and '0x441384' in by_offset[0x140].op_str
    assert by_offset[0x204].mnemonic=='comiss' and by_offset[0x20B].mnemonic=='jbe'
    assert by_offset[0x233].mnemonic=='comiss' and by_offset[0x23A].mnemonic=='jb'
    assert by_offset[0x1A3].mnemonic=='add' and by_offset[0x1A3].op_str=='esp, 8'
    highlow=original.physical_highlow(pe,base,sections)
    physical={site-HEAD:struct.unpack('<I',original.raw_at(pe,base,sections,site,4))[0]
              for site in highlow if HEAD<=site<HEAD+SIZE}
    assert len(physical)==78 and Counter(physical.values())==DATA_TARGETS
    assert 0x143 in physical and physical[0x143]==TABLE
    trailing=original.raw_at(pe,base,sections,HEAD+SIZE,COMPARE_SIZE-SIZE)
    assert trailing[:3]==bytes.fromhex('0f1f00')
    table=[struct.unpack_from('<I',trailing,3+4*i)[0] for i in range(5)]
    assert table==TABLE_TARGETS,(table,TABLE_TARGETS)
    assert sorted(site for site in highlow if TABLE<=site<TABLE+20)==[TABLE+i*4 for i in range(5)]
    heads={i.address for i in ins}
    assert all(x in heads for x in table)
    print('PASS original whole 2769B/683 x86 Mode6 renderer, frame0x64 and native RET4')
    print('PASS exactly all 28 original physical E8 sites and independently observed target heads, including 16 sat/4 mult255/2 Vec+ and whole strict quad and setup')
    print('PASS 78 body PE HIGHLOW fields by immutable original target roles; 21 live Graphics viewport, 42 physical quad color/alpha, 8 one float, original native switch')
    print('PASS original one 3B after-RET NOP and five PE-relocated 32-bit switch pointer entries, 2/2/1 native case alias partition')
    print('Immutable original PE roles are NOT proof of game parent source exactness')


if __name__=='__main__':verify()
