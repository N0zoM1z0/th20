#!/usr/bin/env python3
"""Locked original TH20 22-font resource array and whole 79B GDI cleanup.

The original font table is 22 HFONTs, never the earlier speculative 32.
Independent PE calls and physical relocations pin all original roles.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyphfont79pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyphfont79cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
MAIN=0x004155B0
MAIN_SHA='9e5f6bcf2be3a4a4f21e09d8693b463af56f5afd6e03b4deeca6691e2befce5c'
END=0x00414F50
END_SHA='f106cbce46348bfe471dda5f325d0e310a0557f477a497a821b3abb6fa359641'
BEGIN=0x0040BDA0
BEGIN_SHA='befca35709395b425403c72a706d2f3c715162ad22664d93df30e0255a4d4e8c'
CORE=0x00415830
CORE_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
FOLD_INDEX=0x00414580
FOLD_SHA='63c49b1813004cda4fdbb91fb68008a819c44d98c1c64a7fc76b4405f26a10b8'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 high=pe.physical_highlow(image,base,sections)
 b=pe.raw_at(image,base,sections,MAIN,79)
 assert hashlib.sha256(b).hexdigest()==MAIN_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,MAIN))
 assert len(ins)==28 and ins[-1].address+ins[-1].size==MAIN+79
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,MAIN)=={0x10:BEGIN,0x1B:END}
 data={p-MAIN:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
       for p in high if MAIN<=p<MAIN+79}
 assert data=={0x09:0x005B66F0,0x44:0x0056C038}
 assert any(i.mnemonic=='add' and i.op_str=='eax, 4' for i in ins)
 for head,size,count,sha in [(BEGIN,14,8,BEGIN_SHA),(END,17,9,END_SHA)]:
  native=pe.raw_at(image,base,sections,head,size)
  assert hashlib.sha256(native).hexdigest()==sha
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,head))
  assert len(ci)==count and ci[-1].address+ci[-1].size==head+size
  assert (ci[-1].mnemonic,ci[-1].op_str)==('ret','')
  assert not calls(ci,head)
  assert not any(head<=p<head+size for p in high)
 assert any(i.mnemonic=='add' and i.op_str=='eax, 0x58'
            for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sections,END,17),END))
 textcore=pe.raw_at(image,base,sections,CORE,2227)
 assert hashlib.sha256(textcore).hexdigest()==CORE_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(textcore,CORE))
 assert len(pi)==470 and calls(pi,CORE)[0x57]==FOLD_INDEX
 assert hashlib.sha256(pe.raw_at(image,base,sections,FOLD_INDEX,22)).hexdigest()==FOLD_SHA
 for unit,n in [('glyph_font_release_79',79),('glyph_font_array_end_17',17)]:
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
 assert len(cm.compare_unit('glyph_font_release_79')['relocations'])==4
 assert not cm.compare_unit('glyph_font_array_end_17')['relocations']
 print('PASS original entire 79B/28-i386 game GDI glyph font cleanup, genuine array-global and DeleteObject IAT HIGHLOW')
 print('PASS original two E8 to folded 14B begin and independently whole-exact 17B end, 4-byte HFONT stepping')
 print('PASS array end returns real +0x58 boundary = exactly 22 native i386 HFONT handles, not previous 32')
 print('PASS original 2227B text Boss E8+0x57 to previously exact folded 22B std::array index')
 print('PASS canonical 79/79 game-authored exact + 17/17 generic, folded earlier begin/index NOT recredited')
if __name__=='__main__':verify()
