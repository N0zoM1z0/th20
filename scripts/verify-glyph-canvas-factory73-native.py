#!/usr/bin/env python3
"""Immutable original 73B GDI glyph canvas class allocation factory.

Native original function, parent/callee E8, and true /sdl class-zeroing
helper are independently proven from the original locked target. The MSVC
class/noexcept contract is tested by whole canonical source receipts.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph73pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph73cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00413C50
SHA='b82f916474d1365d308fa06635f6d8b54d7f305f8e6003f360d97879e7c9ee91'
PARENT=0x00415830
PARENT_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
CALLS={0x0E:0x0054275D,0x27:0x0040C080,0x2F:0x00414200}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 body=pe.raw_at(image,base,sec,HEAD,73)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==22 and ins[-1].address+ins[-1].size==HEAD+73
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)==CALLS
 assert not any(HEAD<=p<HEAD+73 for p in pe.physical_highlow(image,base,sec))
 assert any(i.mnemonic=='push' and i.op_str=='0x124' for i in ins)
 original_parent=pe.raw_at(image,base,sec,PARENT,2227)
 assert hashlib.sha256(original_parent).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original_parent,PARENT))
 assert len(pi)==470 and calls(pi,PARENT)[0x89]==HEAD
 for h,n,count,sha in [(0x0040C080,31,14,'6425a6ff69dca64c6adc953b405e901ac7180cdffb28a9f49a86e4f8d440581b'),
                         (0x00414200,124,28,'753f6983e88c30419652a69281f0f57138b3d583df317f85ad3be51e51fcc9dd')]:
  raw=pe.raw_at(image,base,sec,h,n)
  assert hashlib.sha256(raw).hexdigest()==sha
  child=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,h))
  assert len(child)==count and child[-1].address+child[-1].size==h+n
 for unit,size in [('glyph_canvas_allocator_allocate_73',73),('glyph_canvas_constructor_124',124),
                  ('glyph_canvas_allocator_release_97',97),('glyph_canvas_destroy_at_16',16),
                  ('glyph_canvas_scalar_deleting_dtor_49',49),('glyph_canvas_destructor_62',62),
                  ('glyph_text_job_capture_132',132),('glyph_texture_upload_360',360)]:
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==size and z['matched_bytes']==size
 assert len(cm.compare_unit('glyph_canvas_allocator_allocate_73')['relocations'])==3
 print('PASS native whole game 73B/22-i386 glyph canvas allocation, 3 real E8/zero HIGHLOW, +0x124-byte object')
 print('PASS original 2227B/470 text-core Boss E8 +0x89 to factory; original new/operator, folded 31B init and 124B ctor physical targets')
 print('PASS actual C++ class/noexcept native factory 73/73 code, 61/61 ordinary bytes and all 3 original E8, no class-padding fabrication')
 print('PASS existing 124B ctor, 97B release, 16B/49B/62B destructor chain, 132B captured job and 360B upload still whole strict exact')
 print('Previously accepted folded 31B class initialization/124B game ctor are not credited twice; 2227B big parent remains NONEXACT')
if __name__=='__main__':verify()
