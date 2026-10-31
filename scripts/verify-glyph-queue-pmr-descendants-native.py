#!/usr/bin/env python3
"""Whole original glyph task-list PMR allocation/destruction descendants.

This verifies the immutable original PE, including original parent E8
positions, complete physical functions and each original relocation field,
independently of every generated COFF symbol or original code prefix.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('queuepe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('queuecm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_queue_node_allocator_allocate_47':(0x004148D0,47,17,'c7a120ba1e1726b3ddbbda154b6ed19745e453a2ca6d404812f02b5249fba67a',{0x20:0x00414FF0},0x00413000,158,0x3E),
 'glyph_queue_pmr_node_allocate_58':(0x00414FF0,58,22,'2cbe45ce0fa718f4bd907a03b39d6fb6df0192c834bfb24fefe743651e3cea27',{0x15:0x00413730,0x29:0x00415070},0x004148D0,47,0x20),
 'glyph_queue_memory_resource_allocate_59':(0x00415070,59,24,'cd953255fcb8e65b5f3751d4d71321e9cb2ebf84ac6f88a72021b2f86ab640b5',{0x2D:0x0040E700},0x00414FF0,58,0x29),
 'glyph_queue_allocator_destroy_17':(0x00413CA0,17,8,'6f8a6040223f12608494e188091a732c78660074fb18c505fe6107e68dd14bc5',{0x07:0x00413CC0},0x00414350,118,0x56),
 'glyph_queue_function_destroy_at_16':(0x00413CC0,16,8,'fc62691d4b96d2ce46d70a424f3d7a906633d8aa5b8cf34846d15c72c48c9c1d',{0x08:0x004147B0},0x00413CA0,17,0x07),
}
PARENT_SHA={0x00413000:'5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b',
 0x00414350:'2178295c45864a5e293c4a6aa79c4cdad68014a9d1f2adb26202055d40416f52',
 0x004148D0:'c7a120ba1e1726b3ddbbda154b6ed19745e453a2ca6d404812f02b5249fba67a',
 0x00414FF0:'2cbe45ce0fa718f4bd907a03b39d6fb6df0192c834bfb24fefe743651e3cea27',
 0x00413CA0:'6f8a6040223f12608494e188091a732c78660074fb18c505fe6107e68dd14bc5'}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);hl=pe.physical_highlow(image,base,sec)
 seen=set()
 for unit,(head,size,ins_count,sha,real_calls,parent,parent_size,parent_off) in SPECS.items():
  body=pe.raw_at(image,base,sec,head,size)
  assert hashlib.sha256(body).hexdigest()==sha,unit
  inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(inst)==ins_count and inst[-1].address+inst[-1].size==head+size
  assert inst[-1].mnemonic=='ret' and calls(inst,head)==real_calls
  assert not any(head<=p<head+size for p in hl)
  assert not (seen & set(range(head,head+size)))
  seen.update(range(head,head+size))
  origin=pe.raw_at(image,base,sec,parent,parent_size)
  assert hashlib.sha256(origin).hexdigest()==PARENT_SHA[parent],unit
  pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(origin,parent))
  assert calls(pi,parent)[parent_off]==head,unit
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==size and z['matched_bytes']==size
  assert len(z['relocations'])==len(real_calls)
  print(f'PASS {unit} {size}B/{ins_count} native i386, {len(real_calls)} actual E8/zero HIGHLOW, original {hex(parent)} E8+{parent_off:#x}')
 assert len(seen)==197
 orig=pe.raw_at(image,base,sec,0x004131E0,151)
 assert hashlib.sha256(orig).hexdigest()=='a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75'
 instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(orig,0x004131E0))
 assert len(instr)==51 and calls(instr,0x004131E0)[0x5B]==0x00413000
 assert calls(instr,0x004131E0)[0x7F]==0x00414350
 for old in ['glyph_queue_list_max_size_59','glyph_queue_list_transfer_124','glyph_queue_allocator_construct_34','glyph_queue_allocator_max_size_19','glyph_queue_allocator_destroy_48']:
  assert cm.compare_unit(old)['result']=='exact'
 print('PASS original entire 151B/51 list Emplace parents 158B node ctor and 118B guard dtor, all five new nested children and five prior original generic exact units')
 print('Original 151B and 158B remain NONEXACT; original 118B guard dtor now independently WHOLE exact under CORE/RECON-1073')
if __name__=='__main__': verify()
