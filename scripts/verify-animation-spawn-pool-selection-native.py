#!/usr/bin/env python3
"""Original-only PE audit of 20B mode, 38B renderer selection, 20B 72-stride index."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
PARENT=0x00450CB0
CASES=(
 (0x00449490,20,9,('ret','4'),{},(),None),
 (0x0044C8A0,20,9,('ret',''),{},(0x0C4,),0x6C4),
 (0x0044C8C0,38,14,('ret','4'),{0x1B:0x00449490},(0x0A7,0x0DC),0x6C8),
)

def verify():
 im,_=p.verified_target();base,secs=p.parse_sections(im);hi=p.physical_highlow(im,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,n,nins,ret,expected_e8,parents,field in CASES:
  ins=list(cs.disasm(p.raw_at(im,base,secs,head,n),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+n
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  e8={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in ins if i.size==5 and i.bytes[0]==0xE8}
  assert e8==expected_e8,(hex(head),e8)
  assert not any(head<=site<head+n for site in hi)
  ops={(i.mnemonic,i.op_str) for i in ins}
  if head==0x00449490:assert ('imul','eax, dword ptr [ebp + 8], 0x48') in ops
  else:assert any(hex(field) in i.op_str for i in ins)
  for parent_offset in parents:
   site=PARENT+parent_offset;code=p.raw_at(im,base,secs,site,5);assert code[0]==0xe8
   target=(site+5+struct.unpack_from('<i',code,1)[0])&0xffffffff
   assert target==head,(hex(site),hex(target),hex(head))
   print(f'PASS native 922B spawn Boss E8 {site:#010x} -> {head:#010x}')
  print(f'PASS original {head:#010x} whole {n}B/{nins} x86, E8={len(e8)}, no HIGHLOW')
 print('PASS complete true +0x6C4 preference, +0x6C8 array and 0x48 renderer-slot stride')

if __name__=='__main__':verify()
