#!/usr/bin/env python3
"""Independent original-PE-only whole elliptic outline/fan shape audit.

Both original code extents, all 24 E8 true physical destinations, all 17
PE HIGHLOW fields, native geometry ordering, ABI, and genuine original Draw
callers are checked independently of any candidate COFF source or receipt.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('immutable_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
BASE_CALLS={
 0x004455C0:'draw queue flush',0x00422E10:'Vector3 default construction',
 0x004397C0:'scalar cosine',0x00439820:'scalar sine',
 0x00458FA0:'XY rotation',0x00438600:'angle accumulation',
 0x004DDF80:'depth-write disable',0x004D9DB0:'Graphics render state forwarding',
 0x00446690:'renderer color mode',0x00412730:'D3D9 device getter',
 0x005429EE:'compiler cookie verification',
}
CASES={
 'elliptic_line_660':{
  'head':0x0043C4E0,'size':660,'ins':178,'frame':'esp, 0x40','ret':'0x20','primitive':3,
  'calls':{
   0x068:0x004455C0,0x070:0x00422E10,0x0BF:0x004397C0,
   0x0E4:0x00439820,0x111:0x00458FA0,0x1B8:0x00438600,
   0x1CD:0x004DDF80,0x1DB:0x004D9DB0,0x1EF:0x00446690,
   0x1F9:0x00412730,0x21D:0x00412730,0x289:0x005429EE,
  },
  'data':{
   0x007:0x005B25C0,0x079:0x0056E0F0,0x081:0x0056C8D0,
   0x153:0x0056C8CC,0x1C9:0x005C4D40,0x1D7:0x005C4D40,
   0x1F5:0x005C4D40,0x219:0x005C4D40,
  },
  'parent':[0x00444799], 'ctor_offset':0x070,'number_of_vertices':1,
 },
 'elliptic_fan_863':{
  'head':0x0043C180,'size':863,'ins':226,'frame':'esp, 0x40','ret':'0x20','primitive':6,
  'calls':{
   0x068:0x004455C0,0x132:0x00422E10,0x18A:0x004397C0,
   0x1AF:0x00439820,0x1DC:0x00458FA0,0x283:0x00438600,
   0x298:0x004DDF80,0x2A6:0x004D9DB0,0x2BA:0x00446690,
   0x2C4:0x00412730,0x2E8:0x00412730,0x354:0x005429EE,
  },
  'data':{
   0x007:0x005B25C0,0x0BB:0x0056C8CC,
   0x144:0x0056E0F0,0x14C:0x0056C8D0,0x21E:0x0056C8CC,
   0x294:0x005C4D40,0x2A2:0x005C4D40,
   0x2C0:0x005C4D40,0x2E4:0x005C4D40,
  },
  'parent':[0x00444703],'ctor_offset':0x132,'number_of_vertices':2,
 },
}

def verify():
 img,_=pe.verified_target();base,sects=pe.parse_sections(img)
 highlow=pe.physical_highlow(img,base,sects)
 parent=0x00443880
 pcode=pe.raw_at(img,base,sects,parent,5993)
 p_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pcode,parent))
 for name,item in CASES.items():
  head=item['head'];size=item['size']
  code=pe.raw_at(img,base,sects,head,size)
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,head))
  assert len(ins)==item['ins'] and ins[-1].address+ins[-1].size==head+size
  assert ins[2].mnemonic=='sub' and ins[2].op_str==item['frame']
  assert ins[-1].mnemonic=='ret' and ins[-1].op_str==item['ret']
  actual_calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
  assert actual_calls==item['calls'],(name,actual_calls,item['calls'])
  assert all(t in BASE_CALLS for t in actual_calls.values())
  data={p-head:struct.unpack('<I',pe.raw_at(img,base,sects,p,4))[0]
        for p in highlow if head<=p<head+size}
  assert data==item['data'],(name,data,item['data'])
  incoming=[i.address for i in p_ins if len(i.bytes)==5 and i.bytes[0]==0xE8
            and (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==head]
  assert incoming==item['parent'],(name,incoming)
  op_by={i.address-head:i for i in ins}
  assert op_by[0x013].mnemonic=='mov' and op_by[0x013].op_str=='eax, dword ptr [ebp + 0x1c]'
  assert op_by[0x019].mnemonic=='imul' and op_by[0x019].op_str=='ecx, eax, 0x14'
  assert op_by[0x039].mnemonic=='jb'
  assert op_by[item['ctor_offset']].mnemonic=='call'
  assert op_by[item['ctor_offset']].op_str=='0x422e10'
  prim=[i for i in ins if i.mnemonic=='push' and i.op_str==str(item['primitive'])]
  assert prim,(name,'missing D3D9 primitive literal',item['primitive'])
  assert Counter(actual_calls.values())[0x00422E10]==1
  assert Counter(actual_calls.values())[0x00412730]==2
  assert Counter(data.values())[0x005C4D40]==4
  if name=='elliptic_fan_863':
   assert op_by[0x137].mnemonic=='mov' and op_by[0x137].op_str=='eax, dword ptr [ebp - 0x14]'
   assert op_by[0x13A].mnemonic=='add' and op_by[0x13A].op_str=='eax, 0x14'
   assert op_by[0x13D].mnemonic=='mov' and op_by[0x13D].op_str=='dword ptr [ebp - 0x14], eax'
   assert data[0x0BB]==data[0x21E]==0x0056C8CC
  print(f'PASS original entire {name}: {size}B/{item["ins"]} real x86, native frame {item["frame"]} and RET {item["ret"]}')
  print(f'PASS independently original {len(actual_calls)} E8 physical sites/destinations, {len(data)} PE HIGHLOW physical fields/targets; D3D9 primitive {item["primitive"]}')
  print(f'PASS real Vector3 ctor at +0x{item["ctor_offset"]:X}, genuine 65536*20B pool and original 5993B parent E8 {[hex(x) for x in incoming]}')
 print('PASS PE-only original proof complete. Candidate C++ acceptance requires pinned whole canonical relocated-byte comparison, separately.')

if __name__=='__main__':verify()
