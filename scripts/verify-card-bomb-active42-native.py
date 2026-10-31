#!/usr/bin/env python3
"""Original 42B Bomb active predicate and Card start's independent E8."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pe42',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('cmp42',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x00478130
SHA='2b2d4d3752de62d8d422963622a2fc921cf81e7ac441baede296ed98e6fc1517'
def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    body=pe.raw_at(image,base,sections,HEAD,42)
    assert hashlib.sha256(body).hexdigest()==SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(ins)==14 and ins[-1].address+ins[-1].size==HEAD+42
    assert ins[-1].mnemonic=='ret'
    assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [eax + 0x18], 1' for i in ins)
    assert not any(HEAD<=x<HEAD+42 for x in pe.physical_highlow(image,base,sections))
    parent=pe.raw_at(image,base,sections,0x00487C30,1896)
    assert hashlib.sha256(parent).hexdigest()=='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
    caller=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x00487C30))
    sites=[i.address-0x00487C30 for i in caller if i.size==5 and i.bytes[0]==0xE8 and i.address+5+struct.unpack_from('<i',i.bytes,1)[0]==HEAD]
    assert sites==[0x1D6],sites
    result=coff.compare_unit('card_start_bomb_active_42')
    assert result['result']=='exact' and result['matched_bytes']==42 and result['size']==42
    assert result['relocations']==[]
    print('PASS native 42B BombController active-state bool, true +0x18 and 14 i386 instructions')
    print('PASS original 1,896B Card start E8 +0x1D6 -> original 42B Bomb predicate')
    print('PASS canonical C++20 42/42 original, no PE relocations')
if __name__=='__main__':verify()
