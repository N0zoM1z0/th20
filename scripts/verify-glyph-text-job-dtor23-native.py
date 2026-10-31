#!/usr/bin/env python3
"""Original 23B game glyph job destructor and real 2227B parent edge."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph23pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph23cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004142C0
SHA='3aacecdb1b3170aea87b3cf029b04e1e4ddbba1e64fa05d9c05920c198fe9d28'
PARENT=0x00415830
PARENT_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
FUNC_DTOR=0x00414400
FUNC_SHA='9f2ba240a91fa75f8c7bf95b1de5f98309e802f6922cdf0b4c847d2fd1cffdbe'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 b=pe.raw_at(im,base,sec,HEAD,23)
 assert hashlib.sha256(b).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==11 and ins[-1].address+ins[-1].size==HEAD+23
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)=={0x0D:FUNC_DTOR}
 assert not any(HEAD<=x<HEAD+23 for x in high)
 assert any(i.mnemonic=='add' and i.op_str=='ecx, 0x30' for i in ins)
 assert hashlib.sha256(pe.raw_at(im,base,sec,FUNC_DTOR,20)).hexdigest()==FUNC_SHA
 original=pe.raw_at(im,base,sec,PARENT,2227)
 assert hashlib.sha256(original).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,PARENT))
 assert len(pins)==470 and calls(pins,PARENT)[0x842]==HEAD
 unit=cm.compare_unit('glyph_text_job_dtor_23')
 assert unit['result']=='exact' and unit['size']==23 and unit['matched_bytes']==23
 assert len(unit['relocations'])==1
 print('PASS whole original game job destructor 23B/11 i386, real +0x30 function cleanup E8 +0x0D -> original 20B std::function destructor')
 print('PASS native entire 2227B/470 core E8 +0x842 to 23B glyph render job destruction')
 print('PASS canonical 23/23 natural C++20 destruction, zero native HIGHLOW and no duplicate generic function credit')
 print('Original 2227B text Boss still SOURCE-PRESENT/NONEXACT')
if __name__=='__main__':verify()
