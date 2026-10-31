#!/usr/bin/env python3
"""Full original 20-byte canvas width getter and four true 2245B call sites."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('width20pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('width20cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00415800
SHA='97c6c65b5c5a98f6312636a1ebc9b041bdd6ee5342f3be907178f7afaa868936'
PARENT=0x00416420
PARENT_SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
CALL_SITES=(0x307,0x39A,0x6E0,0x797)
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sec)
 b=pe.raw_at(img,base,sec,HEAD,20)
 assert hashlib.sha256(b).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==9 and ins[-1].address+ins[-1].size==HEAD+20
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert not calls(ins,HEAD) and not any(HEAD<=x<HEAD+20 for x in hl)
 assert any(i.mnemonic=='mov' and i.op_str=='eax, dword ptr [eax + 0x104]' for i in ins)
 parent=pe.raw_at(img,base,sec,PARENT,2245)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pins)==612 and pins[-1].address+pins[-1].size==PARENT+2245
 assert tuple(o for o,d in calls(pins,PARENT).items() if d==HEAD)==CALL_SITES
 result=cm.compare_unit('glyph_canvas_width_20')
 assert result['result']=='exact' and result['size']==20 and result['matched_bytes']==20
 assert not result['relocations']
 assert cm.compare_unit('glyph_canvas_format_fallback_104')['result']=='exact'
 for unit in ('glyph_canvas_device_context_20','glyph_canvas_bitmap_pixels_20','glyph_canvas_pixel_stride_20'):
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS whole original 20B/9-i386 custom canvas width getter, native owner+0x104, no relocations')
 print('PASS entire immutable original 2,245B/612-i386 compositor and 4 physical E8 into getter')
 print('PASS natural canonical 20/20 and earlier exact 104B/three 20B shared-provider methods unchanged')
 print('Full 2,245B glyph compositor still SOURCE-ABSENT/NONEXACT; no transitive credit')
if __name__=='__main__':verify()
