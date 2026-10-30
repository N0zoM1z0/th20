#!/usr/bin/env python3
"""Immutable TH20 original PE proof of 108B/127B AnimationHandle lookup chain."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
CASES=(
 (0x0044C830,108,37,{0x1E:0x0044C6B0,0x42:0x00425CC0,
                     0x4C:0x004117A0,0x61:0x005429EE},4),
 (0x0044C7B0,127,45,{0x16:0x00425CC0,0x1E:0x0044CED0,
                     0x2B:0x004117A0,0x46:0x0044C830,0x74:0x005429EE},1),
)

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);high=p.physical_highlow(im,base,sec)
 for head,size,nins,want,padding in CASES:
  body=p.raw_at(im,base,sec,head,size)
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0xc')
  e8={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in ins if i.size==5 and i.bytes[0]==0xe8}
  assert e8==want,(hex(head),e8,want)
  hl={q-head:struct.unpack('<I',p.raw_at(im,base,sec,q,4))[0]
      for q in high if head<=q<head+size}
  assert hl=={0x07:0x005B25C0},(hex(head),hl)
  assert p.raw_at(im,base,sec,head+size,padding)==b'\xcc'*padding
  assert ('xor','ecx, ebp') in {(i.mnemonic,i.op_str) for i in ins}
  for off,dest in e8.items():print(f'PASS original {head:#010x} E8 +{off:#x} -> {dest:#010x}')
  print(f'PASS whole original {head:#010x} {size}B/{nins}-i386, cookie HIGHLOW+0x07 and {padding} original INT3')
 print('PASS 127B handle-forward method physically calls separate 108B child query and original 241B find_child')

if __name__=='__main__':verify()
