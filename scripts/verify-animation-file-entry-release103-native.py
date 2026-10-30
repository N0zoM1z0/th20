#!/usr/bin/env python3
"""Original-only 103B retirement and its preaccepted 16B std::destroy_at callee."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
CASES=(
 (0x00447330,103,36,('ret','4'),
  {0x23:0x00447850,0x32:0x0040C310,0x3B:0x0040B730,
   0x46:0x005429FC,0x51:0x0040B900,0x5C:0x005429EE},
  {0x07:0x005B25C0,0x2E:0x005C0240}),
 (0x00447850,16,8,('ret',''),{0x08:0x00449760},{})
)

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hi=pe.physical_highlow(im,base,sec)
 for head,n,ni,ret,expected,data_expected in CASES:
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,head,n),head))
  assert len(ins)==ni and ins[-1].address+ins[-1].size==head+n
  assert (ins[-1].mnemonic,ins[-1].op_str)==ret
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
  fields={q-head:struct.unpack('<I',pe.raw_at(im,base,sec,q,4))[0]
          for q in hi if head<=q<head+n}
  assert calls==expected,(hex(head),calls,expected)
  assert fields==data_expected,(hex(head),fields,data_expected)
  for off,dest in calls.items():print(f'PASS original {head:#010x} E8 +{off:#x} -> {dest:#010x}')
  print(f'PASS whole original {head:#010x} {n}B/{ni} x86, correct EH/cookie data and return')
 caller=0x0044C430+0x8B;raw=pe.raw_at(im,base,sec,caller,5);assert raw[0]==0xe8
 assert (caller+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff==0x00447330
 print(f'PASS original 209B Renderer file-slot retire E8 {caller:#010x} -> 0x00447330')
 print('PASS original 16B destructor bridge calls genuine 0x00449760 scalar deleting wrapper with flag=0')

if __name__=='__main__':verify()
