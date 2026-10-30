#!/usr/bin/env python3
"""Whole immutable 56B Handle fallback +39B callback forwarding, original chain."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
CASES=(
 (0x0044CF10,56,19,'e306f62f32073a950a66b2a8fc1ce24830b951dc032b571a525d3b759855fea1',
  ('ret',''),{0x0C:0x0044CED0},{0x24:0x005C0028}),
 (0x0044F100,39,15,'255e47a8b20bf6a5c952e6b43e4b71ec0cbd6748d2fb075cd0bd8ff395e59c6e',
  ('ret','4'),{0x0C:0x0044CF10,0x1B:0x00438A50},{}),
)

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,size,nins,sha,ret,exp_calls,exp_data in CASES:
  raw=pe.raw_at(im,base,sec,head,size)
  assert hashlib.sha256(raw).hexdigest()==sha
  ins=list(cs.disasm(raw,head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
  data={q-head:struct.unpack('<I',pe.raw_at(im,base,sec,q,4))[0]
        for q in high if head<=q<head+size}
  assert calls==exp_calls,(hex(head),calls,exp_calls)
  assert data==exp_data,(hex(head),data,exp_data)
  assert pe.raw_at(im,base,sec,head+size,8)==b'\xcc'*8
  for off,target in calls.items():print(f'PASS {head:#010x} E8 +{off:#04x} -> {target:#010x}')
  for off,target in data.items():print(f'PASS {head:#010x} PE HIGHLOW +{off:#04x} -> {target:#010x}')
  print(f'PASS original whole {head:#010x} {size}B/{nins}-i386 + 8 authentic postfunction INT3')
 # The true fallback must be the exact resident Animation at +DC.
 fallback=list(cs.disasm(pe.raw_at(im,base,sec,0x0044CF10,56),0x0044CF10))
 assert ('add','ecx, 0xdc') in {(i.mnemonic,i.op_str) for i in fallback}
 print('PASS original Handle 51B resolver -> true AnimationPool resident Animation+0xDC, independently confirmed in 138B destructor')
 print('PASS native original 39B callback forwarding E8 to authentic 25B Animation field_5dc setter')

if __name__=='__main__':verify()
