#!/usr/bin/env python3
"""PE-only whole-original 985B quad projection and two 455B vertex draw methods.

Attest complete native x86 extents, all genuine E8 and PE HIGHLOW physical
sites and targets, real typed 96B corner data, ABI and original game callers.
The original executable alone supplies these facts; compiled candidate COFF
is consulted separately by canonical unit comparison, not by this verifier.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('native_orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
CASES={
 'corner_projection_985':{
  'head':0x0043EB40,'size':985,'ins':233,'frame':0x24,'ret':0x14,
  'calls':{0x048:0x00437CD0,0x343:0x004376E0,0x350:0x004296E0,
           0x35D:0x004296E0,0x36A:0x004296E0,0x377:0x004296E0},
  'data':{0x020:0x0056E140,0x03E:0x0056E140,
          0x13E:0x005B8818,0x150:0x005B8818,
          0x181:0x005B8818,0x189:0x0056E0EC,
          0x19B:0x005B8818,0x1A3:0x0056E0EC,
          0x33C:0x005C0018,0x349:0x005C0018,0x356:0x005C0018,
          0x363:0x005C0018,0x370:0x005C0018},
  'callers':[(0x0043F550,97,0x0043F598),
             (0x0043F5C0,97,0x0043F608),
             (0x00445770,244,0x004457D3),
             (0x00445770,244,0x00445858)],
 },
 'vertex_fan_455':{
  'head':0x0043CB70,'size':455,'ins':129,'frame':0x20,'ret':0x10,
  'calls':{0x054:0x004455C0,0x12E:0x00446690,0x138:0x00412730,0x15C:0x00412730},
  'data':{0x0B7:0x0056C8CC,0x134:0x005C4D40,0x158:0x005C4D40},
  'count_min':3,'primitive':6,'count_subtract':2,
  'callers':[(0x0045DAE0,76,0x0045DB20),
             (0x0045FB10,76,0x0045FB50),
             (0x00461B80,4238,0x004620D1)],
 },
 'vertex_line_455':{
  'head':0x0043D1A0,'size':455,'ins':129,'frame':0x20,'ret':0x10,
  'calls':{0x054:0x004455C0,0x12E:0x00446690,0x138:0x00412730,0x15C:0x00412730},
  'data':{0x0B7:0x0056C8CC,0x134:0x005C4D40,0x158:0x005C4D40},
  'count_min':2,'primitive':3,'count_subtract':1,
  'callers':[(0x0045E190,165,0x0045E220),
             (0x0045EAC0,76,0x0045EB00),
             (0x00467820,146,0x0046789D)],
 },
}


def verify():
 original,_=pe.verified_target();base,sections=pe.parse_sections(original)
 physical_highlow=pe.physical_highlow(original,base,sections)
 disasm=Cs(CS_ARCH_X86,CS_MODE_32)
 for key,rec in CASES.items():
  head=rec['head'];size=rec['size']
  body=pe.raw_at(original,base,sections,head,size)
  instructions=list(disasm.disasm(body,head))
  assert len(instructions)==rec['ins'] and instructions[-1].address+instructions[-1].size==head+size
  assert instructions[2].mnemonic=='sub' and instructions[2].op_str==f'esp, 0x{rec["frame"]:x}'
  assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str==f'0x{rec["ret"]:x}'
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in instructions if len(i.bytes)==5 and i.bytes[0]==0xE8}
  assert calls==rec['calls'],(key,'E8',calls)
  fields={addr-head:struct.unpack('<I',pe.raw_at(original,base,sections,addr,4))[0]
          for addr in physical_highlow if head<=addr<head+size}
  assert fields==rec['data'],(key,'HIGHLOW',fields)
  by={i.address-head:i for i in instructions}
  if 'count_min' in rec:
   assert by[0x38].mnemonic=='cmp' and by[0x38].op_str==f'dword ptr [ebp + 8], {rec["count_min"]}'
   assert by[0x187].mnemonic=='sub' and by[0x187].op_str==f'eax, {rec["count_subtract"]}'
   assert by[0x18B].mnemonic=='push' and by[0x18B].op_str==str(rec['primitive'])
   assert by[0x1C4].mnemonic=='ret' and by[0x1C4].op_str=='0x10'
  else:
   # Two full three-by-four-float source axes, 0x30 bytes per axis.
   assert by[0x09].op_str=='eax, 0x30'
   assert by[0x1A].mnemonic=='shl' and by[0x1A].op_str=='eax, 4'
   assert by[0x27].op_str=='edx, 0x30'
   assert by[0x38].mnemonic=='shl' and by[0x38].op_str=='ecx, 4'
   assert Counter(fields.values())==Counter({
    0x0056E140:2,0x005B8818:4,0x0056E0EC:2,0x005C0018:5})
   assert Counter(calls.values())==Counter({0x00437CD0:1,0x004376E0:1,0x004296E0:4})
  for c_head,c_size,c_e8 in rec['callers']:
   parent=list(disasm.disasm(pe.raw_at(original,base,sections,c_head,c_size),c_head))
   physical=[i for i in parent if i.address==c_e8]
   assert len(physical)==1 and len(physical[0].bytes)==5 and physical[0].bytes[0]==0xE8,(key,hex(c_e8))
   i=physical[0];actual=(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
   assert actual==head,(key,hex(c_e8),hex(actual))
  print(f'PASS original whole {key} {size}B/{len(instructions)} real i386, 0x{rec["frame"]:X} frame, RET 0x{rec["ret"]:X}')
  print(f'PASS all {len(calls)} native E8 physical site/destination pairs and {len(fields)} original PE HIGHLOW physical field/target pairs')
  print(f'PASS {len(rec["callers"])} independent original game direct E8 caller sites, not reconstructed-source guesses')
 raw=pe.raw_at(original,base,sections,0x0056E140,96)
 axes=[((-0.5,0.5,-0.5,0.5),(0.0,1.0,0.0,1.0),(-1.0,0.0,-1.0,0.0)),
       ((-0.5,-0.5,0.5,0.5),(0.0,0.0,1.0,1.0),(-1.0,-1.0,0.0,0.0))]
 for axis in range(2):
  for group in range(3):
   floats=struct.unpack_from('<4f',raw,axis*48+group*16)
   assert floats==axes[axis][group],(axis,group,floats)
 print('PASS immutable original 96B 2-axis x3-mode x4-corner float table at 0x56E140 and native 16B indexing, not scalar indexing')
 print('PE-only provenance complete; original and fresh C++ canonical relocation byte replay must be checked separately')

if __name__=='__main__':verify()
