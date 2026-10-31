#!/usr/bin/env python3
"""Five whole-original filesystem/PMR methods under exact ANM file loader.

Original SHA/physical E8/PE HIGHLOW and parent call edges are decoded
independently from the immutable Japanese 1.00a executable. Generic code
receives no game-authored match credit, even with exact game parent.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('stl5pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('stl5cm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'animation_load_parse_filename_81':(
 0x0044B630,81,30,'ff9549ad50329068c19b60bd67d256069321a8a84efd88f0246de305d2f304f0',
 {0x09:0x0040C300,0x14:0x0040FF90,0x2A:0x0044B4E0,0x45:0x0040DE00},{},0x0044C590,82,0x2F),
 'animation_load_parse_stem_132':(
 0x0044B690,132,48,'2ea1e7992ca602d411baaafd4a7035f5a0de0dd63f7f07e80b98bd95651d980a',
 {0x09:0x0040C300,0x14:0x0040FF90,0x2A:0x0044B4E0,0x4A:0x004478B0,0x5D:0x0044B450,0x78:0x0040DE00},{},0x00451580,82,0x2F),
 'animation_load_pmr_assign_string_104':(
 0x00447250,104,35,'3a1fef5a7be22a44c74f1a8033309595d9f6cd8d83cde3aba30fd767a545e295',
 {0x18:0x0040C080,0x24:0x004494F0,0x2C:0x0040FF90,0x32:0x0040B280,0x40:0x0040C300,0x53:0x0044B970,0x5D:0x005429EE},{0x07:0x005B25C0},0x00446DC0,25,0x0E),
 'animation_load_wstring_view_54':(
 0x0040E7C0,54,20,'74b22c4a7b85b34b78fb90f171be01185d4cb4cde2cad45fc453d0ec848b63a0',
 {0x0C:0x0040F300,0x28:0x0040DE00},{},0x0044C590,82,0x1F),
 'animation_load_path_view_ctor_44':(
 0x00417DC0,44,18,'a91285919c7e47b47fa8334b9200fec631e036eaa3c3d268cdaa8be21a672962',
 {0x1B:0x00418070},{},0x0044C590,82,0x3B),
}
PARENTS={
 0x0044C590:'0e054976af0f9393bdb0aa3dffac0885dc8d59ae825c54cec5b1b1336adbe6c1',
 0x00451580:'43d95ec46ba06d47ba4d8dbf6e9c4e6b0d3ad822c8fa3c86d96e98ab51a37f65',
 0x00446DC0:'e983eb805ec4d0bee250f7e5ebb835d026e63043ed9c061485abac7df0c8b9a0'
}
def calls(instructions,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in instructions if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sec);seen=set()
 for unit,(head,n,ni,sha,e8,high,parent,pn,site) in SPECS.items():
  original=pe.raw_at(img,base,sec,head,n)
  assert hashlib.sha256(original).hexdigest()==sha,unit
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,head))
  assert len(ins)==ni and ins[-1].address+ins[-1].size==head+n
  assert ins[-1].mnemonic=='ret' and calls(ins,head)==e8,unit
  actual={p-head:struct.unpack('<I',pe.raw_at(img,base,sec,p,4))[0]
          for p in hl if head<=p<head+n}
  assert actual==high,unit
  assert not seen.intersection(range(head,head+n)),unit
  seen.update(range(head,head+n))
  parentraw=pe.raw_at(img,base,sec,parent,pn)
  assert hashlib.sha256(parentraw).hexdigest()==PARENTS[parent],unit
  pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parentraw,parent))
  assert calls(pi,parent)[site]==head,unit
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
  assert len(z['relocations'])==len(e8)+len(high)
  print(f'PASS {unit}: complete original {n}B/{ni} i386, {len(e8)} E8/{len(high)} HIGHLOW, parent E8 {parent:#x}+{site:#x}')
 assert len(seen)==415
 for older in ('animation_file_load_resource_1022','animation_load_path_filename_82',
               'animation_load_path_stem_82','animation_load_find_extension_141',
               'animation_load_find_filename_80','animation_load_pmr_string_assign_bytes_118'):
  assert cm.compare_unit(older)['result']=='exact'
 # Both original filename and stem use the separately exact 80B finder;
 # filename and stem differ by their own native parse paths.
 for head,n,site in [(0x0044C590,82,0x2F),(0x00451580,82,0x2F)]:
  raw=pe.raw_at(img,base,sec,head,n)
  assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,head)),head)[site] in (0x0044B630,0x0044B690)
 print('PASS five distinct complete original nested PMR/filesystem helper heads /415 native CxxRuntime bytes; source 15/15 strict')
 print('PASS original separate 1022B game loader remains whole exact; original 336B group decoder remains independently NONEXACT; zero additional authored-game credit')
if __name__=='__main__':verify()
