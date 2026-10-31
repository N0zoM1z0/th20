#!/usr/bin/env python3
"""Immutable native glyph canvas 3x20B field getters and two large callers."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyphaccpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyphacccm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_canvas_device_context_20':(0x00415620,0x114,'ef877a67be3c67c5afdbf486dbef09942bf750bd3e2ef50a5cc510cb06a55d7c'),
 'glyph_canvas_bitmap_pixels_20':(0x004156A0,0x120,'76e2b0e00c4fde908a610902941a1e01ee596ba4d901069e1c342b70a1bcbde4'),
 'glyph_canvas_pixel_stride_20':(0x004156C0,0x110,'64e00b3aa7139dc316f671d53a7dc4c7fad720ac6dad4c7a6612e3574400e3a3'),
}
PARENT_CORE=0x00415830
PARENT_CORE_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
PARENT_GLYPH=0x00416420
PARENT_GLYPH_SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
STRIDE_SITES=(0x32,0x197,0x1D7,0x5A6,0x5E7,0x69B,0x6FA,0x752,0x7B4)
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img)
 hl=pe.physical_highlow(img,base,sec)
 core=pe.raw_at(img,base,sec,PARENT_CORE,2227)
 assert hashlib.sha256(core).hexdigest()==PARENT_CORE_SHA
 core_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(core,PARENT_CORE))
 assert len(core_ins)==470 and calls(core_ins,PARENT_CORE)[0x36D]==0x00415620
 glyph=pe.raw_at(img,base,sec,PARENT_GLYPH,2245)
 assert hashlib.sha256(glyph).hexdigest()==PARENT_GLYPH_SHA
 glyph_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(glyph,PARENT_GLYPH))
 assert len(glyph_ins)==612 and (glyph_ins[-1].mnemonic,glyph_ins[-1].op_str)==('ret','0x14')
 glyph_calls=calls(glyph_ins,PARENT_GLYPH)
 assert tuple(off for off,dest in glyph_calls.items() if dest==0x004156A0)==(0x44,)
 assert tuple(off for off,dest in glyph_calls.items() if dest==0x004156C0)==STRIDE_SITES
 for unit,(head,offset,sha) in SPECS.items():
  code=pe.raw_at(img,base,sec,head,20)
  assert hashlib.sha256(code).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,head))
  assert len(ins)==9 and ins[-1].address+ins[-1].size==head+20
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
  assert any(i.mnemonic=='mov' and i.op_str==f'eax, dword ptr [eax + 0x{offset:x}]' for i in ins)
  assert not any(head<=site<head+20 for site in hl)
  assert not calls(ins,head)
  result=cm.compare_unit(unit)
  assert result['result']=='exact' and result['size']==20 and result['matched_bytes']==20
  assert not result['relocations']
  print(f'PASS {unit}: native 20B/9-i386, real GDI receiver+0x{offset:X}, whole 20/20 strict')
 assert cm.compare_unit('glyph_canvas_format_fallback_104')['result']=='exact'
 print('PASS genuine original 2,227B/470 glyph core E8 +0x36D to HDC getter')
 print('PASS genuine original 2,245B/612 glyph compositing Boss E8 +0x44 to pixels and 9 original stride E8')
 print('PASS earlier 104B pixel format fallback still strict exact; no ancestor boss exactness claimed')
if __name__=='__main__':verify()
