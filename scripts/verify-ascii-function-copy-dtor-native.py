#!/usr/bin/env python3
"""Immutable PE proof for native 93B copy and 20B destructor of std::function<void()>.

These two physical STL heads are folded callers' common dependencies;
they do not establish exactness of the 578B ASCII text draw Boss.
"""
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('ascii_std_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('ascii_std_cmp',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
DRAW=0x0044B020
DRAW_SHA='fd121bcfb2bb70f0ea9015ed166f137eaa8fef7e663b5c4cbc781d0cee9a4617'
SPECS={
 'ascii_function_copy_93':(0x004140F0,93,29,'557c7cd46e973490cb1c19336e4988976baedac63924d7d6226fe4efa1c13bad',
       {0x29:0x00413F80,0x3C:0x00414B90},
       {0x06:0x00567C8D,0x13:0x005B25C0},[0x1B6], '4'),
 'ascii_function_dtor_20':(0x00414400,20,10,'9f2ba240a91fa75f8c7bf95b1de5f98309e802f6922cdf0b4c847d2fd1cffdbe',
       {0x0A:0x00414310},{},[0x220],''),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 high=pe.physical_highlow(image,base,sections)
 native_parent=pe.raw_at(image,base,sections,DRAW,578)
 assert hashlib.sha256(native_parent).hexdigest()==DRAW_SHA
 parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native_parent,DRAW))
 assert len(parent_ins)==139
 parent_calls=calls(parent_ins,DRAW)
 assert len(parent_calls)==11
 for unit,(head,size,count,sha,e8,dir32,parent_offsets,ret_operand) in SPECS.items():
  body=pe.raw_at(image,base,sections,head,size)
  assert hashlib.sha256(body).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret',ret_operand)
  assert calls(ins,head)==e8
  fields={pos-head:struct.unpack('<I',pe.raw_at(image,base,sections,pos,4))[0]
          for pos in high if head<=pos<head+size}
  assert fields==dir32
  assert [off for off,dest in parent_calls.items() if dest==head]==parent_offsets
  result=coff.compare_unit(unit)
  assert result['result']=='exact' and result['size']==size and result['matched_bytes']==size
  assert len(result['relocations'])==len(e8)+len(dir32)
  print(f'PASS {unit}: whole original {size}B/{count}-i386, {len(e8)} true E8/{len(dir32)} actual HIGHLOW; canonical {size}/{size}')
 print('PASS physical 578B ASCII text render E8 +0x1B6 (copy) / +0x220 (destructor)')
 print('Original 578B text renderer remains SOURCE-PRESENT/NONEXACT; generic STL source ownership uncredited')
if __name__=='__main__':verify()
