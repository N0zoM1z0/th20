#!/usr/bin/env python3
"""Attest full 20B native renderer file getter and original Card HUD E8 graph."""
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pe20',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('cmp20',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
GETTER=0x00437950
GETTER_SHA='6181bd2fb3b6c96cc30b6297ac35f8f97d01d5721aaced3fdee51766fbc89824'
HUD=0x004B90E0
PARENTS=(0xE0,0x1FA,0x28C)
def verify():
    img,_=pe.verified_target();base,sections=pe.parse_sections(img)
    b=pe.raw_at(img,base,sections,GETTER,20)
    assert hashlib.sha256(b).hexdigest()==GETTER_SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,GETTER))
    assert len(ins)==9 and ins[-1].address+ins[-1].size==GETTER+20
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
    assert any(i.mnemonic=='mov' and i.op_str=='eax, dword ptr [eax + 0x1a244]' for i in ins)
    assert not any(GETTER<=p<GETTER+20 for p in pe.physical_highlow(img,base,sections))
    hud=pe.raw_at(img,base,sections,HUD,1522)
    assert hashlib.sha256(hud).hexdigest()=='af638942de7619ec46f71a2adafdea6b612ead352799a29d91a27ee9d650aaa0'
    calls={i.address-HUD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(hud,HUD) if i.size==5 and i.bytes[0]==0xe8}
    assert len(calls)==51
    assert [off for off,dst in calls.items() if dst==GETTER]==list(PARENTS)
    unit=coff.compare_unit('card_hud_renderer_file_getter_20')
    assert unit['result']=='exact' and unit['size']==20 and unit['matched_bytes']==20
    assert not unit['relocations']
    print('PASS original 20B/9-i386 renderer file getter, receiver+0x1A244 and no PE relocations')
    print('PASS true original 1,522B HUD Boss three E8 +0xE0/+0x1FA/+0x28C into getter')
    print('PASS canonical whole 20/20 native C++20 exact, origin remains review/uncredited')
if __name__=='__main__':verify()
