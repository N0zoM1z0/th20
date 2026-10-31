#!/usr/bin/env python3
"""Physical original 10B/24B/43B/153B PMR glyph vector resource chain.

Every E8 edge and function boundary is anchored in the original locked PE;
current COFF symbols only generate natural standard-library source bodies.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('vecpmrpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('vecpmrcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_mask_default_resource_10':(0x00415820,10,5,'253b445022798eeeab6c5977d225e12049b368998db8ab993e906c46ff2ac48f',{0x03:0x00541550},'ctor24',0x07,''),
 'glyph_mask_pmr_allocator_ctor_24':(0x004141A0,24,11,'3dc515ab87c6ec58281ed2be2f011d87d19d0cf8b8694cf40598c5e34db77cdc',{0x07:0x00415820},'pair43',0x11,''),
 'glyph_mask_compressed_pair_ctor_43':(0x00412E10,43,17,'30d77db7578e4703e537d1c5e953133d975cc6b1595673112c0a65afc6296161',{0x11:0x004141A0,0x1C:0x00414090},'vector63',0x17,'4'),
 'glyph_mask_vector_tidy_153':(0x00414E10,153,54,'ad0821e3a7978cddff47a70d174a934306a24467dec51ba9e88995a890d0bb09',{0x0C:0x0040F160,0x38:0x0040E5E0,0x56:0x0040C6B0,0x75:0x004154C0},'vector20',0x0A,''),
}
PARENTS={
 'ctor24':(0x004141A0,24,'3dc515ab87c6ec58281ed2be2f011d87d19d0cf8b8694cf40598c5e34db77cdc',11),
 'pair43':(0x00412E10,43,'30d77db7578e4703e537d1c5e953133d975cc6b1595673112c0a65afc6296161',17),
 'vector63':(0x004141C0,63,'5b64525640460b4bf2a1ca1d319561289b8e7bd91acdeb9236f144f6bd8bc82f',25),
 'vector20':(0x00414440,20,'bea187ec35a9c0c408a803467e4111ede1fad6a19d50ad203d206605e8cb532a',10),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);high=pe.physical_highlow(img,base,sec)
 for unit,(head,size,count,sha,roles,parent,site,ret) in SPECS.items():
  raw=pe.raw_at(img,base,sec,head,size)
  assert hashlib.sha256(raw).hexdigest()==sha
  inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,head))
  assert len(inst)==count and inst[-1].address+inst[-1].size==head+size
  assert (inst[-1].mnemonic,inst[-1].op_str)==('ret',ret)
  assert calls(inst,head)==roles
  assert not any(head<=p<head+size for p in high)
  pa,n,psha,pcount=PARENTS[parent]
  parentbytes=pe.raw_at(img,base,sec,pa,n)
  assert hashlib.sha256(parentbytes).hexdigest()==psha
  pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parentbytes,pa))
  assert len(pins)==pcount and calls(pins,pa)[site]==head
  report=cm.compare_unit(unit)
  assert report['result']=='exact' and report['size']==size and report['matched_bytes']==size
  assert len(report['relocations'])==len(roles)
  print(f'PASS {unit}: whole original {size}B/{count}-i386, {len(roles)} real E8, native {parent} +0x{site:X} caller')
 for unit in ('glyph_mask_offsets_vector_ctor_63','glyph_mask_offsets_vector_dtor_20','glyph_mask_offsets_vector_begin_26','glyph_mask_offsets_vector_end_26'):
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS original 2,245B glyph compositor PMR vector ctor/dtor whole exact, no duplicated previously credited original lower leaves')
 print('PASS 4 new distinct generic PMR lifecycle heads total 230 native bytes, no newly authored game code credit')
 print('Original 2,245B and 2,227B game glyph bosses remain independently NONEXACT')
if __name__=='__main__':verify()
