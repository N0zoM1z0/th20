#!/usr/bin/env python3
"""Original complete 82B glyph pixel-format lookup with native 681B caller.

Table stride/sentinel are attested from the immutable target, not guessed
from the compiled candidate or treated as a newly owned source array.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph82pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph82cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00415640
SHA='d1980926efef1321fd130e8f043d405927252e1dd05f69f54cba12a77b1e913f'
PHYSICAL_FIELDS={0x21:0x005AE078,0x2E:0x005AE078,0x48:0x005AE078}
PARENT=0x00415120
PARENT_SHA='62554c335c22f75345ca164715188e77712c1e8348c199e3757843b193aa33d3'
TABLE=0x005AE078
EXPECTED_CODES=[22,21,24,23,25,26,-1]
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);high=pe.physical_highlow(img,base,sec)
 body=pe.raw_at(img,base,sec,HEAD,82)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==26 and ins[-1].address+ins[-1].size==HEAD+82
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert not calls(ins,HEAD)
 fields={p-HEAD:struct.unpack('<I',pe.raw_at(img,base,sec,p,4))[0]
         for p in high if HEAD<=p<HEAD+82}
 assert fields==PHYSICAL_FIELDS
 codes=[]
 for i in range(len(EXPECTED_CODES)):
  desc=pe.raw_at(img,base,sec,TABLE+i*24,24)
  code,bpp,alpha,red,green,blue=struct.unpack('<i5I',desc)
  codes.append(code)
  assert bpp in (0,16,32)
 assert codes==EXPECTED_CODES
 assert struct.unpack('<i',pe.raw_at(img,base,sec,TABLE+6*24,4))[0]==-1
 parent=pe.raw_at(img,base,sec,PARENT,681)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pins)==176 and calls(pins,PARENT)[0x35]==HEAD
 report=cm.compare_unit('glyph_pixel_format_lookup_82')
 assert report['result']=='exact' and report['size']==82 and report['matched_bytes']==82
 assert len(report['relocations'])==3
 print('PASS immutable 82B/26-i386 glyph descriptor lookup, three physical PE HIGHLOW to 0x005AE078, no E8')
 print('PASS six 24B native descriptors plus exact -1 terminator, original font format codes 22,21,24,23,25,26')
 print('PASS actual original 681B GDI bitmap initializer E8 +0x35 to this complete 82B head')
 print('PASS canonical whole 82/82 source and three independently pinned native descriptor relocations')
 print('681B GDI bitmap initializer remains NONEXACT; no transitive 681B credit')
if __name__=='__main__':verify()
