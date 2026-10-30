#!/usr/bin/env python3
"""Original-PE-only entire 78B/83B two 200-element grid array constructors."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
CASES=((0x0045C190,200,4,0x00425CC0,0x0045C1F0+0x22),
       (0x0045C130,200,12,0x00422E10,0x0045C1F0+0x30),
       (0x0045C130,200,12,0x00422E10,0x0045C1F0+0x3E))

def verify():
 image,_=pe.verified_target();base,secs=pe.parse_sections(image)
 reloc=pe.physical_highlow(image,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,count,stride,callback,parent in CASES:
  ins=list(cs.disasm(pe.raw_at(image,base,secs,head,78),head))
  assert len(ins)==27 and ins[-1].address+ins[-1].size==head+78
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
  e8={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
  fields={p-head:struct.unpack('<I',pe.raw_at(image,base,secs,p,4))[0] for p in reloc if head<=p<head+78}
  assert e8=={0x36:0x0040BC20},(hex(head),e8)
  expected={0x06:0x00567600,0x13:0x005B25C0,0x27:callback}
  assert fields==expected,(hex(head),fields,expected)
  ops={(i.mnemonic,i.op_str) for i in ins}
  assert ('push','0xc8') in ops
  assert ('push',hex(stride) if stride>9 else str(stride)) in ops
  assert pe.raw_at(image,base,secs,head+78,5)==b'\xcc'*5
  raw=pe.raw_at(image,base,secs,parent,5);assert raw[0]==0xe8
  dest=(parent+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff;assert dest==head
  print(f'PASS original {head:#010x}: 78B/27 i386, 200 x {stride} bytes, 5 original INT3, 1 E8 +3 HIGHLOW, parent {parent:#010x}')
 print('PASS both distinct array constructors, full 83B physical extents; no authored-game credit')

if __name__=='__main__':verify()
