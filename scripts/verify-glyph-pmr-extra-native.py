#!/usr/bin/env python3
"""Immutable original PMR glyph vector max-size and construct helpers.

Whole-native original boundaries and E8s are anchored independently of COFF.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyphExtraPe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyphExtraCmp',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_vec_max_size_59':(0x004162B0,59,22,'b64feb77efc50cd36b4b27b774a1a6eb602d3d1b0532f1e4dadffe9ffd75375e',
  {0x0C:0x0040F160,0x12:0x00416260,0x1D:0x0040D0E0,0x2D:0x0040D980},0x004133E0,488,0x6F),
 'glyph_vec_allocator_max_size_13':(0x00416260,13,6,'22be529d9ab519d4328159c34a94961db0208af170e2bf5722cd28fa2d049413',
  {0x03:0x004111E0},0x004162B0,59,0x12),
 'glyph_vec_normal_traits_construct_22':(0x00415440,22,11,'7517486f8cd562d4d11f99b23944b572f36732ad4cc9c01631833701e3f04be4',
  {0x0E:0x00415460},None,None,None),
}
PARENTS={0x004133E0:'5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57',
 0x004162B0:'b64feb77efc50cd36b4b27b774a1a6eb602d3d1b0532f1e4dadffe9ffd75375e'}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,secs=pe.parse_sections(im);high=pe.physical_highlow(im,base,secs)
 for unit,(head,size,count,sha,expected,parent,parent_size,site) in SPECS.items():
  b=pe.raw_at(im,base,secs,head,size)
  assert hashlib.sha256(b).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+size
  assert ins[-1].mnemonic=='ret' and calls(ins,head)==expected
  assert not any(head<=p<head+size for p in high)
  if parent is not None:
   pb=pe.raw_at(im,base,secs,parent,parent_size)
   assert hashlib.sha256(pb).hexdigest()==PARENTS[parent]
   pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,parent))
   assert calls(pi,parent)[site]==head
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['matched_bytes']==z['size']==size
  assert len(z['relocations'])==len(expected)
  print(f'PASS {unit} {size}B/{count} i386, {len(expected)} native E8, zero PE HL; '+
        (f'parent 0x{parent:X} E8 +0x{site:X}' if parent is not None else 'native 85B lower construct callee'))
 assert cm.compare_unit('glyph_vec_growth_xlength_16')['result']=='exact'
 print('PASS three distinct generic PMR glyph heads, 94B whole exact; no newly authored game bytes')
if __name__=='__main__':verify()
