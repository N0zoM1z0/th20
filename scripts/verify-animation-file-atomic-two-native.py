#!/usr/bin/env python3
"""Two whole native STL atomic<uint32_t> wrapper heads used by 182B game Boss.

Their original PE and native parent E8 edges are independently SHA-pinned.
Do not credit standard-library code as game-authored original text.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('atomicpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('atomiccm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
PARENT=0x0044EB30
PARENT_SHA='559e1e2c9c7e103c8f856e127908eb1b10b4929f2a25ac714b1d8089b5d276fe'
SPECS={
 'animation_file_atomic_assign_28':(0x004493C0,28,12,'92b9ef8a164060015ffd17d7e4fd8dc3b4e51cb2035abcc33df7051c195705c7',0x0E,0x0040C550,0x5D,'??4?$atomic@I@std@@QAEII@Z'),
 'animation_file_atomic_value_21':(0x004292C0,21,10,'c0826eff4a5d0e01f268b19ea363af174e4165357bef14133664b1cf291bd715',0x0C,0x0040C420,0x69,'??B?$atomic@I@std@@QBEIXZ'),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);pehigh=pe.physical_highlow(im,base,sec)
 parent=pe.raw_at(im,base,sec,PARENT,182)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 caller=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT));pc=calls(caller,PARENT)
 assert len(caller)==64 and len(pc)==7
 seen=set()
 for unit,(head,n,count,sha,child_offset,child_target,parent_site,symbol) in SPECS.items():
  orig=pe.raw_at(im,base,sec,head,n)
  assert hashlib.sha256(orig).hexdigest()==sha,unit
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(orig,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+n
  assert ins[-1].mnemonic=='ret' and calls(ins,head)=={child_offset:child_target}
  assert not any(head<=p<head+n for p in pehigh)
  assert pc[parent_site]==head
  assert not seen.intersection(range(head,head+n))
  seen.update(range(head,head+n))
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
  obj=ROOT/'build/core1098-canonical/AnimationFileFindOrLoad182.obj'
  comp=cm.compare(obj,symbol,head,n)
  assert comp['result']=='structural-exact'
  assert comp['matched_comparable_bytes']==comp['comparable_bytes']==n-4
  assert len(comp['relocations'])==1
  r=comp['relocations'][0]
  assert int(r['offset'],16)==child_offset+1 and r['type']=='REL32'
  assert int(r['solved_destination'],16)==child_target
  print(f'PASS {unit}: original whole {n}B/{count} i386, native E8+{child_offset:#x}->{child_target:#x}, zero HIGHLOW, real 182B parent E8+{parent_site:#x}')
 assert len(seen)==49
 assert cm.compare_unit('animation_file_find_or_load_182')['result']=='exact'
 print('PASS two separate original native generic atomic heads/49B, 3/3 scoped source receipts, zero new game-authored exact credit')
if __name__=='__main__':verify()
