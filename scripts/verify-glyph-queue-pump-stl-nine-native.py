#!/usr/bin/env python3
"""Nine independent whole original STL methods of TH20's exact 254B pump.

All E8 parent/child links and original full bodies come from locked PE,
not from generated COFF symbols or inferred parent exactness.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pumpstlpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('pumpstlcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_queue_func_default_ctor_23':(0x00414150,23,11,'4504fdc37a6c59dc6106117a29ad595439105b4623267249429683a57be87dc7',{0x0A:0x00413F80},0x00416140,254,0x72),
 'glyph_queue_list_front_22':(0x00415600,22,11,'e05c60a68ee85c72e72a966596a2afe4d3582186873a2db085623bbb8b4022bf',{},0x00416140,254,0x80),
 'glyph_queue_func_copy_assign_60':(0x00414540,60,22,'40c6645bd8a7f1bc8dd5e6fe41623bd909e121376e238b3eddfa7c9d4f0fd8db',{0x10:0x004140F0,0x25:0x00417A90,0x2D:0x00414400},0x00416140,254,0x89),
 'glyph_queue_list_begin_63':(0x004150B0,63,24,'c55b1d8dfac7725ecb05f7d91f57caa0c6deb475206d8ba1585c8fbfd835ac2b',{0x10:0x0040B280,0x31:0x00413FD0},0x00416140,254,0x98),
 'glyph_queue_list_erase_93':(0x00415550,93,34,'3712763f13b51a3e821ad2038a0dd45e0da1a9de05e10972bf6293fd26b1e0c8',{0x21:0x00414F90,0x2C:0x0040F160,0x3C:0x00413690,0x4F:0x00414B20},0x00416140,254,0xAF),
 'glyph_queue_list_iterator_ctor_33':(0x00413FD0,33,15,'4ab305214c608038aaf0bde79907c52c8f6b2c0ab66d7ba628f459660c894be0',{0x12:0x00413FA0},0x004150B0,63,0x31),
 'glyph_queue_list_unlinknode_70':(0x00414F90,70,27,'d760b7825e13b6d8ff0da535ce7df8af60eb47560757db83eba4163f3cc8e6a6',{0x0E:0x0040EC90},0x00415550,93,0x21),
 'glyph_queue_list_make_iter_44':(0x00414B20,44,18,'d00138bb3e657645546369d04b31136eafc6516bf36cad875c4e238367c73e7b',{0x0E:0x0040B280,0x1E:0x00413FD0},0x00415550,93,0x4F),
 'glyph_queue_func_swap_26':(0x00417A90,26,12,'c9ad68875594b49feb0f43c0fb920cff68c9d95fe7404452e0eb9de1f65824e6',{0x0E:0x00414C80},0x00414540,60,0x25),
}
PARENT_SHA={0x00416140:'ef9966b4d7958ec50e93ea140df2f52ba3109e6ecf5a9caf0ecd1376510e0899',
 0x004150B0:'c55b1d8dfac7725ecb05f7d91f57caa0c6deb475206d8ba1585c8fbfd835ac2b',
 0x00415550:'3712763f13b51a3e821ad2038a0dd45e0da1a9de05e10972bf6293fd26b1e0c8',
 0x00414540:'40c6645bd8a7f1bc8dd5e6fe41623bd909e121376e238b3eddfa7c9d4f0fd8db'}
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 seen=set()
 for unit,(head,size,count,sha,native_calls,parent,parent_size,parent_offset) in SPECS.items():
  body=pe.raw_at(im,base,sec,head,size)
  assert hashlib.sha256(body).hexdigest()==sha,unit
  instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(instr)==count and instr[-1].address+instr[-1].size==head+size
  assert instr[-1].mnemonic=='ret' and calls(instr,head)==native_calls
  assert not any(head<=x<head+size for x in hl)
  assert not (seen & set(range(head,head+size)))
  seen.update(range(head,head+size))
  parent_bytes=pe.raw_at(im,base,sec,parent,parent_size)
  assert hashlib.sha256(parent_bytes).hexdigest()==PARENT_SHA[parent]
  parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent_bytes,parent))
  assert calls(parent_ins,parent)[parent_offset]==head
  unit_result=cm.compare_unit(unit)
  assert unit_result['result']=='exact' and unit_result['size']==size and unit_result['matched_bytes']==size
  assert len(unit_result['relocations'])==len(native_calls)
  print(f'PASS {unit}: entire original {size}B/{count} i386, {len(native_calls)} real E8, no HL, caller E8 {hex(parent)}+{parent_offset:#x}')
 assert len(seen)==434
 pump=cm.compare_unit('glyph_text_queue_pump_254')
 assert pump['result']=='exact' and pump['size']==254 and pump['matched_bytes']==254
 for unit in ['glyph_upload_callback_invoke_59','ascii_function_dtor_20','ascii_function_copy_93']:
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS complete original game 254B pump and nine distinct native 434B generic descendant code heads')
 print('Existing exact 59B callback, 20B std::function dtor and 93B copy constructor not re-credited; zero new game-authored byte credit')
if __name__=='__main__': verify()
