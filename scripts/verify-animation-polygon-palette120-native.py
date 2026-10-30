#!/usr/bin/env python3
"""Independent locked PE original whole 120B palette and two 31B wrapper leaves.

Read entire original native x86 and PE HIGHLOW positions/targets without
candidate COFF bytes. The original 120B code uses 32.0f at 0x56CD94 and
has NO compiler security cookie; its source belongs to a distinct no-/sdl
pinned compilation profile from the already strict 296B/233B group TU.
"""
from pathlib import Path
from collections import Counter
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('original_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
CASES={
 'palette_120':{
   'head':0x0045FC90,'size':120,'ins':39,'frame':'esp, 0x18','ret':'4',
   'calls':{0x01B:0x004142A0,0x027:0x0045FFC0,0x03F:0x00414580,
            0x046:0x0045D650,0x06C:0x0045FFA0},
   'absolute':{0x05C:0x0056CD94},
 },
 'forward_color_31':{
   'head':0x0045FFC0,'size':31,'ins':14,'frame':None,'ret':'4',
   'calls':{0x011:0x0045D430}, 'absolute':{},
 },
 'forward_radius_31':{
   'head':0x0045FFA0,'size':31,'ins':14,'frame':None,'ret':'4',
   'calls':{0x011:0x0045D360}, 'absolute':{},
 },
}
PARENT_HEAD=0x0045FB60
PARENT_SIZE=296
PARENT_SITES=[0x0045FBDE,0x0045FC01,0x0045FC24]

def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 relocs=pe.physical_highlow(image,base,sections)
 disasm=Cs(CS_ARCH_X86,CS_MODE_32)
 for name,rec in CASES.items():
  head=rec['head'];size=rec['size']
  ins=list(disasm.disasm(pe.raw_at(image,base,sections,head,size),head))
  assert len(ins)==rec['ins'] and ins[-1].address+ins[-1].size==head+size
  if rec['frame'] is not None:
   assert ins[2].mnemonic=='sub' and ins[2].op_str==rec['frame']
  assert ins[-1].mnemonic=='ret' and ins[-1].op_str==rec['ret']
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if len(i.bytes)==5 and i.bytes[0]==0xe8}
  assert calls==rec['calls'],(name,calls,rec['calls'])
  data={p-head:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
        for p in relocs if head<=p<head+size}
  assert data==rec['absolute'],(name,data,rec['absolute'])
  by={i.address-head:i for i in ins}
  if name=='palette_120':
   assert [i.address-head for i in ins if i.mnemonic=='nop']==[0x02C,0x04B,0x071]
   assert not any(x==0x005B25C0 for x in data.values())
   assert by[0x058].mnemonic=='movss' and '0x56cd94' in by[0x058].op_str
   assert Counter(calls.values())[0x0045D650]==1
  elif name=='forward_color_31':
   assert by[0x00B].mnemonic=='push' and by[0x00B].op_str=='0x3d'
  elif name=='forward_radius_31':
   assert by[0x00B].mnemonic=='push' and by[0x00B].op_str=='0x3e'
  print(f'PASS independent whole original {name}: {size}B/{len(ins)} real i386, {len(calls)} native E8 site/targets, {len(data)} PE HIGHLOW physical fields')
 parent=list(disasm.disasm(pe.raw_at(image,base,sections,PARENT_HEAD,PARENT_SIZE),PARENT_HEAD))
 incoming=[i.address for i in parent if len(i.bytes)==5 and i.bytes[0]==0xe8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==0x0045FC90]
 assert incoming==PARENT_SITES,(incoming,PARENT_SITES)
 assert struct.unpack('<f',pe.raw_at(image,base,sections,0x0056CD94,4))[0]==32.0
 print('PASS original 296B game Boss calls palette exactly three times; original 32.0f at 0x56CD94')
 print('PASS palette native has exactly two real scope-boundary NOPs after color calls and one final; no original security cookie')

if __name__=='__main__':verify()
