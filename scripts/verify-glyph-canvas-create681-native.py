#!/usr/bin/env python3
"""Entire immutable original 681B GDI surface creation and C++20 frontier.

The physical target is never shortened to the compiled 684B candidate.
Exact credit remains restricted to separately canonical 104B/20B children.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph681pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph681cmp',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00415120
SIZE=681
SHA='62554c335c22f75345ca164715188e77712c1e8348c199e3757843b193aa33d3'
CALLS={0x019:0x00416360,0x026:0x00544760,0x035:0x00415640,0x29E:0x005429EE}
DATA={0x00A:0x005B25C0,0x0FB:0x0056C020,0x119:0x0056C044,0x133:0x0056C02C}
SYM='?create_gdi_surface_415120@NativeGlyphCanvasView@th20@@QAE_NHHH@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify(obj):
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 body=pe.raw_at(img,base,secs,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==176 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0xc')
 assert calls(ins,HEAD)==CALLS
 hl=pe.physical_highlow(img,base,secs)
 data={site-HEAD:struct.unpack('<I',pe.raw_at(img,base,secs,site,4))[0]
       for site in hl if HEAD<=site<HEAD+SIZE}
 assert data==DATA
 # Original size is exactly 0x6c (108) and the PE performs a real memset
 # before the Win32 GDI bitmap creation. This is BITMAPV4HEADER-size evidence.
 assert body[0x1E:0x20]==b'\x6a\x6c'
 assert body[0x72:0x79]==b'\xc7\x45\x90\x6c\x00\x00\x00'
 parent=pe.raw_at(img,base,secs,0x004153D0,104)
 assert hashlib.sha256(parent).hexdigest()=='20fdd9d772ec1d057d3a77d9795c7c974d44a790a02dff9a3fffdc0fafa78c47'
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x004153D0))
 assert len(pins)==43 and calls(pins,0x004153D0)=={0x016:HEAD,0x03F:HEAD,0x059:HEAD}
 print('PASS immutable original 681B/176-i386 GDI surface boss, four native E8 and four PE HIGHLOW')
 print('PASS 108B bitmap V4 header and original three physical Win32 GDI imports at +0xFB/+0x119/+0x133')
 print('PASS original whole-exact 104B format fallback: E8 +0x16/+0x3F/+0x59 to this 681B head')
 if obj:
  blob,rel=cm.object_function(obj,SYM,684)
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(blob),0))
  assert len(blob)==684 and len(ins)==176 and len(rel)==8
  assert sum(row['type']=='REL32' for row in rel)==4
  assert sum(row['type']=='DIR32' for row in rel)==4
  sites={r['offset']:r for r in rel}
  assert {off for off,r in sites.items() if r['type']=='DIR32'}==set(DATA)
  for off in DATA:
   symbol=sites[off]['symbol'];actual=DATA[off]
   if actual==0x005B25C0:assert symbol=='___security_cookie'
   if actual==0x0056C020:assert symbol=='__imp__CreateDIBSection@24'
   if actual==0x0056C044:assert symbol=='__imp__CreateCompatibleDC@4'
   if actual==0x0056C02C:assert symbol=='__imp__SelectObject@8'
  reloc_call_sites={off for off,r in sites.items() if r['type']=='REL32'}
  assert reloc_call_sites=={0x01A,0x027,0x036,0x2A2}
  assert sites[0x01A]['symbol'].startswith('?release_surface_416360@')
  assert sites[0x027]['symbol']=='_memset'
  assert sites[0x036]['symbol'].startswith('?pixel_format_415640@')
  assert sites[0x2A2]['symbol']=='@__security_check_cookie@4'
  print('FRONTIER NONEXACT: 684B/176 i386 natural BITMAPV4HEADER C++20, 4 E8/4 DIR32 roles')
  print('Three Win32 import relocations and first three E8 physical sites align; final cookie +3B different')
 print('No exact unit or authored-game exact byte credit for the 681B parent')
if __name__=='__main__':
 import argparse
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
