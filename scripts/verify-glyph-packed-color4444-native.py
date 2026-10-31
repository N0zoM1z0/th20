#!/usr/bin/env python3
"""Exact whole original 22B ARGB4444 color default constructor and real 2245B caller."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pack22pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('pack22cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00414280
SHA='b7fd8b74d2296f36938c0067299f46916f23a7f60c178579e2b2db4d478a0cc7'
PARENT=0x00416420
PARENT_SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img)
 body=pe.raw_at(img,base,sec,HEAD,22)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==11 and ins[-1].address+ins[-1].size==HEAD+22
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert any(i.mnemonic=='xor' and i.op_str=='eax, eax' for i in ins)
 assert any(i.mnemonic=='mov' and i.op_str=='word ptr [ecx], ax' for i in ins)
 assert not calls(ins,HEAD)
 assert not any(HEAD<=p<HEAD+22 for p in pe.physical_highlow(img,base,sec))
 parent=pe.raw_at(img,base,sec,PARENT,2245)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pins)==612 and pins[-1].address+pins[-1].size==PARENT+2245
 assert calls(pins,PARENT)[0x505]==HEAD
 assert calls(pins,PARENT)[0x4FD]==0x004142A0
 report=cm.compare_unit('glyph_packed_color4444_ctor_22')
 assert report['result']=='exact' and report['size']==22 and report['matched_bytes']==22
 assert not report['relocations']
 for unit in ('glyph_mask_offsets_vector_ctor_63','glyph_mask_offsets_vector_dtor_20',
              'glyph_mask_offsets_vector_begin_26','glyph_mask_offsets_vector_end_26'):
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS immutable native 22B/11-i386 16-bit ARGB4444 color default constructor, real zero word and no relocs')
 print('PASS entire original 2245B/612-i386 compositor E8 +0x505 to 22B ctor, +0x4FD to prior exact 24B PackedColor')
 print('PASS canonical whole 22/22 natural pixel-color value, four existing PMR-vector children unchanged')
 print('The native 2245B parent still SOURCE-PRESENT/NONEXACT and adds zero parent byte credit')
if __name__=='__main__':verify()
