#!/usr/bin/env python3
"""Independent original PE/COFF check of 54B PMR string pointer helper.

The native 22B c_str parent and its two lower callees are separate already
exact physical code heads; this proof grants no transitive game credit.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('myptr_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('myptr_cmp',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x0040F2C0
SHA='c3a6a6bc297539e707d0ab4e7f8bf1336e9fab94acc6b28a65da5486b2a2ea03'
CSTR=0x0044BAF0
CSTR_SHA='43bd0312020d597cfa7218127be88cc8f928d51c1671f92cda054524d49f043b'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,sections=pe.parse_sections(img)
 body=pe.raw_at(img,base,sections,HEAD,54)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==21 and ins[-1].address+ins[-1].size==HEAD+54
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)=={0x12:0x0040F180,0x24:0x0040B280}
 reloc=pe.physical_highlow(img,base,sections)
 assert not any(HEAD<=p<HEAD+54 for p in reloc)
 cstr=pe.raw_at(img,base,sections,CSTR,22)
 assert hashlib.sha256(cstr).hexdigest()==CSTR_SHA
 parent=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(cstr,CSTR))
 assert len(parent)==10 and calls(parent,CSTR)=={0x0D:HEAD}
 proof=coff.compare_unit('card_text_string_myptr_54')
 assert proof['result']=='exact' and proof['size']==54 and proof['matched_bytes']==54
 assert len(proof['relocations'])==2
 print('PASS original 54B/21-i386 PMR String_val _Myptr, 2 native E8 and no HIGHLOW')
 print('PASS actual 22B std::pmr::string::c_str original E8 +0x0D into this helper')
 print('PASS existing exact 42B large mode and 8B _Unfancy targets at original native locations')
 print('PASS canonical full 54/54 natural C++20; no authored-game credit or repeated lower helper credit')
if __name__=='__main__':verify()
