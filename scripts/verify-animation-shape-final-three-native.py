#!/usr/bin/env python3
"""Original PE-only whole 375B point, 809B parity fan, 583B parity line.

Freeze complete instruction extents, direct E8, real PE HIGHLOW fields,
original renderer ABI and authentic main Draw parent site/targets before
consulting the candidate source/COFF objects. Do not infer original data
from newly compiled source relocations.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe_orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
CASES={
 'point_375':{
  'head':0x0043D830,'size':375,'ins':100,'frame':0x1C,'ret':0xC,'primitive':1,
  'calls':{0x046:0x4455C0,0x0D0:0x4DDF80,0x0E4:0x446690,0x0EE:0x412730,0x112:0x412730},
  'data':{0x0AF:0x56C8CC,0x0CC:0x5C4D40,0x0EA:0x5C4D40,0x10E:0x5C4D40},
  'parent':[0x00444C57],
 },
 'alternate_fan_809':{
  'head':0x0043D9B0,'size':809,'ins':214,'frame':0x28,'ret':0x20,'primitive':6,
  'calls':{0x05E:0x4455C0,0x1B0:0x439330,0x257:0x438600,
           0x26C:0x4DDF80,0x27A:0x4D9DB0,0x28E:0x446690,
           0x298:0x412730,0x2BC:0x412730},
  'data':{0x0B1:0x56C8CC,0x132:0x56E0F0,0x13A:0x56C8D0,
          0x1F2:0x56C8CC,0x268:0x5C4D40,0x276:0x5C4D40,
          0x294:0x5C4D40,0x2B8:0x5C4D40},
  'parent':[0x00444CED],
 },
 'alternate_line_583':{
  'head':0x0043DCE0,'size':583,'ins':160,'frame':0x28,'ret':0x1C,'primitive':3,
  'calls':{0x048:0x4455C0,0x0E6:0x439330,0x18D:0x438600,
           0x1AC:0x446690,0x1B6:0x412730,0x1DA:0x412730},
  'data':{0x067:0x56E0F0,0x06F:0x56C8D0,0x128:0x56C8CC,
          0x1B2:0x5C4D40,0x1D6:0x5C4D40},
  'parent':[0x00444D6E],
 },
}

def verify():
 original,_=pe.verified_target();base,sects=pe.parse_sections(original)
 highlow=pe.physical_highlow(original,base,sects)
 ph=0x00443880
 parent=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(original,base,sects,ph,5993),ph))
 for key,f in CASES.items():
  head=f['head'];size=f['size']
  body=pe.raw_at(original,base,sects,head,size)
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(ins)==f['ins'] and ins[-1].address+ins[-1].size==head+size
  assert ins[2].mnemonic=='sub' and ins[2].op_str==f'esp, 0x{f["frame"]:x}'
  assert ins[-1].mnemonic=='ret' and ins[-1].op_str==f'0x{f["ret"]:x}'
  calls={x.address-head:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
         for x in ins if len(x.bytes)==5 and x.bytes[0]==0xE8}
  assert calls==f['calls'],(key,'calls',calls)
  data={x-head:struct.unpack('<I',pe.raw_at(original,base,sects,x,4))[0]
        for x in highlow if head<=x<head+size}
  assert data==f['data'],(key,'fields',data)
  incoming=[i.address for i in parent if len(i.bytes)==5 and i.bytes[0]==0xe8 and
            (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==head]
  assert incoming==f['parent'],(key,incoming)
  assert any(i.mnemonic=='push' and i.op_str==str(f['primitive']) for i in ins)
  assert Counter(calls.values())[0x412730]==2
  if key=='point_375':
   assert len(calls)==5 and len(data)==4
   assert not any(t==0x439330 for t in calls.values())
   assert any(i.mnemonic=='imul' and i.op_str=='ecx, eax, 0' for i in ins)
  else:
   assert len([i for i in ins if i.mnemonic=='and' and i.op_str.endswith(', 0x80000001')])==1
   assert Counter(calls.values())[0x439330]==1
   assert Counter(calls.values())[0x438600]==1
  print(f'PASS original whole {key}: {size}B /{len(ins)} x86, native frame 0x{f["frame"]:X}, RET 0x{f["ret"]:X}, D3D9 primitive {f["primitive"]}')
  print(f'PASS {len(calls)} original E8 true physical site/destinations and {len(data)} PE HIGHLOW physical fields/targets, original main 5993B E8 caller {hex(incoming[0])}')
 print('All native original facts read from locked executable only. Fresh canonical compiler comparison is separate.')

if __name__=='__main__':verify()
