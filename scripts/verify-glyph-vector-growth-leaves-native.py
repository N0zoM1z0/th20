#!/usr/bin/env python3
"""Independently pin three whole PMR-vector growth leaves under 488B Boss."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('growpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('growcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
PARENT=0x004133E0
PARENT_SHA='5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57'
SPECS={
 'glyph_vec_growth_xlength_16':(0x00414FE0,16,7,'cf2025c5d3452455f8177d854541ea93efe40f4452151d90671170478229e830',{0x08:0x00540ED5},{0x04:0x0056C7C0},0x79,'',''),
 'glyph_vec_growth_change_array_165':(0x00414960,165,62,'f32d7aef5aa352c44e86570143f4e38111c62e91b2aa0ef944eae720cb96699e',{0x0C:0x0040F160,0x38:0x0040E5E0,0x56:0x0040C6B0,0x75:0x004154C0},{},0x1A9,'0xc',''),
 'glyph_vec_growth_reallocation_guard_81':(0x004144E0,81,33,'4fdf85ad2632693c011e383a4da9e65af777e7b6917631d0242f8ae6f1039238',{0x26:0x0040C6B0,0x47:0x004154C0},{},0x1C5,'',''),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sections=pe.parse_sections(img)
 high=pe.physical_highlow(img,base,sections)
 p=pe.raw_at(img,base,sections,PARENT,488)
 assert hashlib.sha256(p).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p,PARENT))
 assert len(pi)==170 and pi[-1].address+pi[-1].size==PARENT+488
 assert (pi[-1].mnemonic,pi[-1].op_str)==('ret','8')
 assert len(calls(pi,PARENT))==14
 assert {x-PARENT:struct.unpack('<I',pe.raw_at(img,base,sections,x,4))[0]
         for x in high if PARENT<=x<PARENT+488}=={0x06:0x00567CED,0x15:0x005B25C0}
 for unit,(head,size,count,sha,expected_calls,data,parent_offset,ret,_) in SPECS.items():
  b=pe.raw_at(img,base,sections,head,size)
  assert hashlib.sha256(b).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret',ret)
  assert calls(ins,head)==expected_calls
  actual={x-head:struct.unpack('<I',pe.raw_at(img,base,sections,x,4))[0]
          for x in high if head<=x<head+size}
  assert actual==data
  assert calls(pi,PARENT)[parent_offset]==head
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==size and z['matched_bytes']==size
  assert len(z['relocations'])==len(expected_calls)+len(data)
  print(f'PASS original {unit} {size}B/{count} i386: {len(expected_calls)} real E8, {len(data)} PE HIGHLOW; parent E8 +0x{parent_offset:X}')
 print('PASS full original 488B/170-i386 PMR vector growth Boss 14 E8/2 PE HIGHLOW independently pinned; parent SOURCE-ABSENT/NONEXACT')
 print('PASS 3 new whole exact generic PMR leaves totaling 262 physical native bytes, no game-authored credit')
if __name__=='__main__':verify()
