#!/usr/bin/env python3
"""Whole original TH20 PMR glyph-vector growth/backout descendant graph.

Nine native function heads below actual 488B growth, 200B uninitialized
move and 140B normal-element construct are separately original PE proven.
All nine are real generic STL implementations; no game-authored credit.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('deeppe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('deepcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_vec_calculate_growth_84':(0x00414900,84,31,'6ebdd1a5c8dfb301b1bbd4abb71bd70c155b644e0d845f1441d19d9982b70601',{0x0C:0x004150F0,0x17:0x004162B0},0x004133E0,488,0x8F),
 'glyph_vec_allocate_at_least_19':(0x00413120,19,9,'89835240f18e1718f63ed5af81d676d05e7fc1a96e7f6d69d11cac875eaa160a',{0x0C:0x00415030},0x004133E0,488,0x9F),
 'glyph_vec_pmr_array_allocate_58':(0x00415030,58,22,'6dda4df20e9d1f03fa6da6812a9326ea3b0d3f54bcd0bc4aabdb2c996f1de780',{0x15:0x00413700,0x29:0x00415070},0x00413120,19,0x0C),
 'glyph_vec_count_size_42':(0x00413700,42,14,'641bfd506ab4b9fb416f43729dd2048716f5cc5356a177fb760c3f21829ced97',{0x1A:0x0040F880},0x00415030,58,0x15),
 'glyph_vec_capacity_36':(0x004150F0,36,15,'32cdd303952a02cadbf1a7e0da37f403c4d7d593755e14e612253d1b719456b1',{},0x00414900,84,0x0C),
 'glyph_vec_backout_ctor_42':(0x00414060,42,17,'54ef68d339ddaa064c4664fad19c337bf479f455440910ac196cdc8b549dadc0',{},0x00413920,200,0x5B),
 'glyph_vec_backout_release_28':(0x00414B70,28,13,'fd13ed678497b9da392720d0cd36efff6cf9267f27ac0dfc430171c1eec7c1a5',{},0x00413920,200,0x95),
 'glyph_vec_backout_dtor_39':(0x004143D0,39,18,'64ad3140ee80fdee64b18935fe60020cbc35750d4766ac0b4f9e3a251ad44781',{0x1B:0x0040C6B0},0x00413920,200,0xA7),
 'glyph_vec_orphan_range_13':(0x00414B60,13,7,'4ade1d8e5215866f23695f07800936f46a1e0f3cbc31d5027c2919f35615073a',{},0x004132E0,140,0x69),
}
PARENT_SHA={
 0x004133E0:'5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57',
 0x00413920:'ec0f652bfa6eaf3ee4ac165bd3088e80e924fc7b8747e74ba133d3041febca65',
 0x004132E0:'1f514d2135b7b78ef041cc44ba21003fe295a2033b33a1a78eb8e40862bc37f2',
 0x00414900:'6ebdd1a5c8dfb301b1bbd4abb71bd70c155b644e0d845f1441d19d9982b70601',
 0x00413120:'89835240f18e1718f63ed5af81d676d05e7fc1a96e7f6d69d11cac875eaa160a',
 0x00415030:'6dda4df20e9d1f03fa6da6812a9326ea3b0d3f54bcd0bc4aabdb2c996f1de780'}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 seen=set()
 for unit,(head,size,nins,sha,expected,parent,psize,site) in SPECS.items():
  raw=pe.raw_at(im,base,sec,head,size)
  assert hashlib.sha256(raw).hexdigest()==sha,unit
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert ins[-1].mnemonic=='ret' and calls(ins,head)==expected
  assert not any(head<=p<head+size for p in hl)
  assert not seen.intersection(range(head,head+size)),unit
  seen.update(range(head,head+size))
  pb=pe.raw_at(im,base,sec,parent,psize)
  assert hashlib.sha256(pb).hexdigest()==PARENT_SHA[parent],unit
  pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,parent))
  assert calls(pi,parent)[site]==head,(unit,hex(site))
  unit_result=cm.compare_unit(unit)
  assert unit_result['result']=='exact' and unit_result['size']==size and unit_result['matched_bytes']==size
  assert len(unit_result['relocations'])==len(expected)
  print(f'PASS {unit}: original entire {size}B/{nins} i386, {len(expected)} native E8/0 HIGHLOW, native caller {parent:#x} E8+{site:#x}')
 assert len(seen)==361
 for old in ['glyph_vec_growth_change_array_165','glyph_vec_growth_reallocation_guard_81','glyph_vec_max_size_59','glyph_queue_memory_resource_allocate_59']:
  assert cm.compare_unit(old)['result']=='exact'
 print('PASS nine distinct complete original PMR-vector heads, 361 native generic bytes; existing 165B/81B/59B helpers not recredited')
 print('Original game 2245B glyph Boss / compiler STL 488B growth, 200B backout move, 140B construct remain independently NONEXACT')
if __name__=='__main__':verify()
