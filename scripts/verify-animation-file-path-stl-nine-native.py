#!/usr/bin/env python3
"""Whole physical original CRT/filesystem/PMR paths of 1022B game loader.

Nine complete original compiler-library function heads; all genuine E8
sites, SHA and parent edges are independently verified from locked PE.
No stdlib bytes are credited as authored game code.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('stlpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('stlcm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'animation_load_sprintf_s_260_39':(0x00429120,39,17,'9db4c24b7685c4c9613f73794b70e5db2c11ff27ce89ce9f02e1130c13b012b5',{0x1B:0x00439880},0x0044A700,1022,0x41),
 'animation_load_path_ctor_44':(0x0040C720,44,18,'3d89ba11c5975e31b96f125766a18a270f2cc25c78e92f381c47bc40b3342a7c',{0x1B:0x0040CDF0},0x0044A700,1022,0xB6),
 'animation_load_path_filename_82':(0x0044C590,82,30,'0e054976af0f9393bdb0aa3dffac0885dc8d59ae825c54cec5b1b1336adbe6c1',{0x1F:0x0040E7C0,0x2F:0x0044B630,0x3B:0x00417DC0},0x0044A700,1022,0xCF),
 'animation_load_path_stem_82':(0x00451580,82,30,'43d95ec46ba06d47ba4d8dbf6e9c4e6b0d3ad822c8fa3c86d96e98ab51a37f65',{0x1F:0x0040E7C0,0x2F:0x0044B690,0x3B:0x00417DC0},0x0044A700,1022,0x177),
 'animation_load_path_string_alloc_75':(0x004189C0,75,28,'138023c84fd5553c009eed0a3a08b2245047ebd40e64f91ac8e9c384954a3820',{0x21:0x0040E7C0,0x31:0x00418100},0x0044A700,1022,0x11B),
 'animation_load_pmr_string_assign_25':(0x00446DC0,25,11,'e983eb805ec4d0bee250f7e5ebb835d026e63043ed9c061485abac7df0c8b9a0',{0x0E:0x00447250},0x0044A700,1022,0x146),
 'animation_load_find_extension_141':(0x0044B450,141,54,'f65544e75cee7efbbbf6b7f8d9987925fe1490c7bb1e2b138c8816017ed67afd',{},0x0044B690,132,0x5D),
 'animation_load_find_filename_80':(0x0044B4E0,80,31,'059a170884c36f949b3fb7a2053457eb65f74a530dfed8c89a688727450dafca',{0x0C:0x0041B8E0,0x2F:0x00419150},0x0044B630,81,0x2A),
 'animation_load_pmr_string_assign_bytes_118':(0x0044B970,118,44,'c1a63ccbb4ba7866bd3073cca53f70d190f0e8b7008b75677b4b250e4df2aedb',{0x1A:0x0040F2C0,0x37:0x00411480,0x4E:0x0040FE90,0x6B:0x00447050},0x00447250,104,0x53),
}
PARENT_SHA={
 0x0044A700:'b750b3b8810f442dfe717b1c4b49eabad84423ed2771efa794c28c0321273021',
 0x0044B690:'2ea1e7992ca602d411baaafd4a7035f5a0de0dd63f7f07e80b98bd95651d980a',
 0x0044B630:'ff9549ad50329068c19b60bd67d256069321a8a84efd88f0246de305d2f304f0',
 0x00447250:'3a1fef5a7be22a44c74f1a8033309595d9f6cd8d83cde3aba30fd767a545e295',
}
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);hl=pe.physical_highlow(image,base,sec)
 seen=set();source='src/AnimationFileLoad1022.cpp'
 for unit,(head,n,nins,sha,expected,parent,pn,poff) in SPECS.items():
  b=pe.raw_at(image,base,sec,head,n)
  assert hashlib.sha256(b).hexdigest()==sha,unit
  inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,head))
  assert len(inst)==nins and inst[-1].address+inst[-1].size==head+n
  assert inst[-1].mnemonic=='ret' and calls(inst,head)==expected,unit
  assert not any(head<=p<head+n for p in hl)
  assert not seen.intersection(range(head,head+n)),unit
  seen.update(range(head,head+n))
  pb=pe.raw_at(image,base,sec,parent,pn)
  assert hashlib.sha256(pb).hexdigest()==PARENT_SHA[parent],unit
  pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,parent))
  assert calls(pi,parent)[poff]==head,unit
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
  assert len(z['relocations'])==len(expected)
  print(f'PASS {unit}: original whole {n}B/{nins} i386, {len(expected)} original E8, zero HIGHLOW, native parent E8 {parent:#x}+{poff:#x}')
 assert len(seen)==686
 # The path basename and stem both route through the SAME 80B native
 # _Find_filename, while stem separately invokes the 141B extension.
 for pa,site in [(0x0044B630,0x2A),(0x0044B690,0x2A)]:
  pb=pe.raw_at(image,base,sec,pa,81 if pa==0x0044B630 else 132)
  assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,pa)),pa)[site]==0x0044B4E0
 native_main=pe.raw_at(image,base,sec,0x0044A700,1022)
 main_calls=calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native_main,0x0044A700)),0x0044A700)
 assert main_calls[0x11B]==main_calls[0x1C3]==0x004189C0
 assert main_calls[0x146]==main_calls[0x1EE]==0x00446DC0
 assert cm.compare_unit('animation_file_load_resource_1022')['result']=='exact'
 print('PASS all nine distinct whole physical original path/PMR/CRT code heads, 686B native generic .text; same source replays 10/10 units')
 print('PASS original 1022B game owner exact remains independent; nine generic function heads retain unknown/review, zero added authored-game byte credit')
if __name__=='__main__':verify()
