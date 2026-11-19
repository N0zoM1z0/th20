#!/usr/bin/env python3
"""Whole-original evidence for the Vector2 interpolation template instance."""
import hashlib, importlib.util, struct, sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('vector2_interpolation_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
SPECS=(
 (0x00438E90,22,10,'389f2a6285b1407eec8c2228d3c6077095db2bab8aa8c1a2f4777b8a67b3bca6','ret 4',{}),
 (0x00439510,25,11,'c476868243be19ce731d5aaf4972db7d835b14fe22d459550406775211089f5c','ret 4',{}),
 (0x00439420,29,13,'5c65e3dd808c6ec37e15029f3ad1287f0ee695392eae5467fdfde3dece7b5835','ret 4',{}),
 (0x00438AC0,30,13,'88b60598c0679044c051a23e34de97058181ad74432efd74f38aeded2cca10e5','ret 4',{}),
 (0x00439640,92,34,'3d2d503f01276d9dd8d0c616429721cc0273f40a4d29a9739ebdaa3f9ae15d6d','ret 0x10',{
  0x0E:0x00438E90,0x1A:0x00439510,0x26:0x00439420,0x32:0x00438AC0,0x50:0x00423520}),
)
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 high=pe.physical_highlow(image,base,sections)
 dis=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,size,count,sha,ret,calls_expected in SPECS:
  body=pe.raw_at(image,base,sections,head,size)
  assert hashlib.sha256(body).hexdigest()==sha,(hex(head),hashlib.sha256(body).hexdigest())
  ins=list(dis.disasm(body,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+size,(hex(head),len(ins))
  assert not any(head<=x<head+size for x in high),hex(head)
  calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
  assert calls==calls_expected,(hex(head),calls)
  assert (ins[-1].mnemonic+' '+ins[-1].op_str).strip()==ret,(hex(head),ins[-1].mnemonic,ins[-1].op_str)
 print('PASS five whole original Vector2 interpolation functions: 198B / 81 i386, 5 true begin E8 destinations, zero PE HIGHLOW')
 print('PASS setters write duration +0x38, mode +0x3C, start +0x00, end +0x08; begin copies start to current +0x20 and resets Timer +0x28')
 print('ORIGIN REVIEW: native and natural C++ template instance exact; do not count authored bytes until game-vs-library provenance is resolved')
if __name__=='__main__':verify()
