#!/usr/bin/env python3
"""PE-only whole 308B AnimationPool retire, 82B geometry, 90B range, 23B stride."""
from pathlib import Path
import importlib.util,hashlib,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
CASES=(
 (0x0044C2F0,308,80,('ret','4'),'81818ace7b3c2c97e4859a23ea139095bf8ca487707f87479a5410fd31f2456c',
  {0x3E:0x0041F7C0,0x53:0x0044C5F0,0x61:0x00411CE0,0x6F:0x00411CE0,
   0x95:0x0044D970,0xB7:0x004494D0,0xE8:0x004494D0,0xF6:0x00411EE0,
   0xFE:0x0044C240,0x10E:0x004117A0,0x120:0x00447410},
  {0x3A:0x005B8894,0x11C:0x005B8894}),
 (0x0044C5F0,82,22,('ret',''),'4aa26618695dbbf86199e018529b4da831413a88b4fba1462a7d0050c20a289a',
  {0x2F:0x0041F670},{0x2B:0x005B8894}),
 (0x0044D970,90,27,('ret','4'),'d4750d8f4efd48992d194a0df24cb6c9c1c43d8beed277d52a3a66d71b9063d8',
  {0x19:0x004494D0,0x37:0x004494D0},{}),
 (0x004494D0,23,9,('ret','4'),'1af670782786d22bde99c385bb4e24cefc060bdaed6db36120c6e174b0773706',
  {},{}),
)

def verify():
 im,_=pe.verified_target();base,secs=pe.parse_sections(im);hi=pe.physical_highlow(im,base,secs)
 cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,size,count,ret,hash_value,expected_e8,expected_data in CASES:
  raw=pe.raw_at(im,base,secs,head,size)
  assert hashlib.sha256(raw).hexdigest()==hash_value
  instructions=list(cs.disasm(raw,head))
  assert len(instructions)==count and instructions[-1].address+instructions[-1].size==head+size
  assert (instructions[-1].mnemonic,instructions[-1].op_str)==ret
  e8={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in instructions if i.size==5 and i.bytes[0]==0xe8}
  data={loc-head:struct.unpack('<I',pe.raw_at(im,base,secs,loc,4))[0]
        for loc in hi if head<=loc<head+size}
  assert e8==expected_e8,(hex(head),e8,expected_e8)
  assert data==expected_data,(hex(head),data,expected_data)
  assert pe.raw_at(im,base,secs,head+size,4)==b'\xcc'*4
  print(f'PASS original whole {head:#010x} {size}B/{count}-i386 E8={len(e8)} PE HIGHLOW={len(data)} real INT3 boundary')
 parent=0x0044C2F0
 for offset,target in ((0x53,0x0044C5F0),(0x95,0x0044D970),(0xB7,0x004494D0),(0xE8,0x004494D0),(0xF6,0x00411EE0)):
  disp=struct.unpack('<i',pe.raw_at(im,base,secs,parent+offset+1,4))[0]
  assert parent+offset+5+disp==target
 print('PASS original 308B game Boss calls entire 82B/90B/23B children and 76B native folded insert_after')
 for start,n in ((0x00449870,508),(0x00449B20,511),(0x0044A3A0,339)):
  ins=list(cs.disasm(pe.raw_at(im,base,secs,start,n),start))
  sites=[i.address for i in ins if i.size==5 and i.bytes[0]==0xe8 and int(i.op_str,16)==parent]
  assert sites,(hex(start),sites)
  print('PASS original native parent calls 308B at',','.join(hex(x) for x in sites))

if __name__=='__main__':verify()
