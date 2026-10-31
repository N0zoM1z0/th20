#!/usr/bin/env python3
"""Independently original 542B glyph alpha Boss and whole strict canonical source."""
import argparse,hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('alpha542pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('alpha542cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00417AB0
SHA='b510c0d99e2c1d40f1388c77952a55775dfd24617858922e56ed178e1fdf64df'
CALLS={0x0C:0x004156C0,0x1B:0x004156A0,0x6B:0x00415800,0x198:0x00415800}
PARENT=0x00415830
PARENT_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
SYM='?invert_alpha_417ab0@NativeGlyphCanvasView@th20@@QAE_NHHHH@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify(obj):
 img,_=pe.verified_target();base,sec=pe.parse_sections(img)
 b=pe.raw_at(img,base,sec,HEAD,542)
 assert hashlib.sha256(b).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==164 and ins[-1].address+ins[-1].size==HEAD+542
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x10')
 assert calls(ins,HEAD)==CALLS
 assert not any(HEAD<=p<HEAD+542 for p in pe.physical_highlow(img,base,sec))
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp - 0x20], 0x15' for i in ins)
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp - 0x20], 0x19' for i in ins)
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp - 0x20], 0x1a' for i in ins)
 pb=pe.raw_at(img,base,sec,PARENT,2227)
 assert hashlib.sha256(pb).hexdigest()==PARENT_SHA
 pin=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,PARENT))
 assert len(pin)==470 and calls(pin,PARENT)[0x6D6]==HEAD
 print('PASS native entire 542B/164-i386 Alpha Boss: format 0x15/0x19/0x1A, 4 native E8/0 HIGHLOW, ret 0x10')
 print('PASS physical original 2227B text core E8 +0x6D6 -> original 542B canvas method')
 if obj:
  candidate,rel=cm.object_function(obj,SYM,542)
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(candidate),0))
  assert len(candidate)==542 and len(ci)==164 and len(rel)==4
  expected={0x0D:0x004156C0,0x1C:0x004156A0,0x6C:0x00415800,0x199:0x00415800}
  assert {r['offset']:r['type'] for r in rel}=={k:'REL32' for k in expected}
  assert all(r['addend']==0 for r in rel)
  assert 'pixel_stride_4156c0@' in rel[0]['symbol']
  assert 'bitmap_pixels_4156a0@' in rel[1]['symbol']
  assert all('canvas_width_415800@' in r['symbol'] for r in rel[2:])
  result=cm.compare(obj,SYM,HEAD,542)
  assert result['result']=='structural-exact'
  assert (result['matched_comparable_bytes'],result['comparable_bytes'])==(526,526)
  print('PASS whole candidate 542B/164 x86, 526/526 nonrelocated native bytes, 4 genuine original E8 sites/roles')
 unit=cm.compare_unit('glyph_canvas_alpha_invert_542')
 assert unit['result']=='exact' and unit['size']==542 and unit['matched_bytes']==542
 assert len(unit['relocations'])==4
 print('PASS original full 542/542 canonical strict game-authored Alpha Boss, native four physical E8 anchored independently')
 print('Original 2227B text core still SOURCE-PRESENT/NONEXACT and earns no transitive parent bytes')

if __name__=='__main__':
 parser=argparse.ArgumentParser();parser.add_argument('--candidate-object',type=Path)
 args=parser.parse_args();verify(args.candidate_object)
