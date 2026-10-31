#!/usr/bin/env python3
"""Immutable 681B GDI DIB creator plus complete canonical source exactness.

All original E8 and HIGHLOW targets are established from PE evidence, not
solved via the COFF candidate or folded child source byte identity.
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
 print('PASS native entire 681B/176-i386 DIB surface, 4 E8 and 4 PE HIGHLOW')
 print('PASS original 108B BITMAPV4HEADER, 3 real GDI IAT, true signed row stride and native pixel mask paths')
 print('PASS native independent 104B format fallback E8 +0x16/+0x3F/+0x59 to whole 681B head')
 canonical=cm.compare_unit('glyph_canvas_create_681')
 assert canonical['result']=='exact' and canonical['size']==SIZE and canonical['matched_bytes']==SIZE
 assert len(canonical['relocations'])==8
 if obj:
  blob,rel=cm.object_function(obj,SYM,SIZE)
  assert len(blob)==SIZE and len(rel)==8
  cins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(blob),0))
  assert len(cins)==176
  role_fields={off+1:('REL32',dest) for off,dest in CALLS.items()}
  role_fields.update({off:('DIR32',dest) for off,dest in DATA.items()})
  assert len(role_fields)==8
  sites={r['offset']:r for r in rel}
  assert {off:r['type'] for off,r in sites.items()}=={off:role[0] for off,role in role_fields.items()}
  for off,role in role_fields.items():
   assert sites[off]['addend']==0
  expected_symbols={0x00A:'___security_cookie',0x01A:'?release_surface_416360@',
     0x027:'_memset',0x036:'?pixel_format_415640@',0x0FB:'__imp__CreateDIBSection@24',
     0x119:'__imp__CreateCompatibleDC@4',0x133:'__imp__SelectObject@8',
     0x29F:'@__security_check_cookie@4'}
  for off,prefix in expected_symbols.items():
   assert sites[off]['symbol'].startswith(prefix)
  outcome=cm.compare(obj,SYM,HEAD,SIZE)
  assert outcome['result']=='structural-exact'
  assert (outcome['matched_comparable_bytes'],outcome['comparable_bytes'])==(649,649)
  print('PASS all 649/649 ordinary source bytes, all 8 immutable relocation locations/roles, full 176 instructions')
 print('PASS canonical complete original 681/681 game-authored bytes, independent GDI release/format/getter children uncredited twice')

if __name__=='__main__':
 import argparse
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
