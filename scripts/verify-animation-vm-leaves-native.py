#!/usr/bin/env python3
"""Whole-original PE and candidate proof for eight Animation VM opcode leaves."""
from __future__ import annotations
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,path):
 spec=importlib.util.spec_from_file_location(name,ROOT/path);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
pe=load('vm_leaf_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('vm_leaf_coff','scripts/compare-coff-function.py')
LEAVES=(
 (0x00429150,43,'98b8c786e3f32c1121c838629fcde8a8162ef3c8d5c68241e22fefbd99d708a8',17,'0xc',()),
 (0x00429280,29,'8bee817f74743bbe4902e5a76b13ad64a3341e481832777f4f5b2fdf9cc9cae3',13,'4',((0x11,0x00423F80),)),
 (0x00438AE0,24,'4f312c17c634871c83458242a6937de55f222538c87bf3365a841c849414b81b',11,'4',()),
 (0x00438B50,24,'049baeea9860d668fadf4a3bf041453e3239e25d4456e3c1c861e8985e3f12a2',11,'4',()),
 (0x00439440,23,'10a9bcdb2047305400c472f68f9841da79223b62d2168082b887ce58490bc217',11,'4',()),
 (0x004394B0,24,'24c1afd104703be693b77105a50b5cb4c2dc3d27ccc71ee8b303b900789000c9',11,'4',()),
 (0x00439280,76,'d805322936ff60e836fb8a0eb2d0fce39d0882a8fe0d7555c692b4420382a65f',21,'0xc',()),
 (0x00439390,62,'e33da2021ccad68b005ec917faaf6eeecc870ae43f8a274a3c14cf6a76eb99b4',18,'8',()),
)
CANDIDATES=(
 ('build/gptweb-animation-vm-leaves/Color3.obj','??0Color3@th20@@QAE@EEE@Z',0x00429150,43,()),
 ('build/gptweb-animation-vm-leaves/Timer.obj','?set_from_current@Timer@th20@@QAEXABU12@@Z',0x00429280,29,((0x12,'REL32','?set@Timer@th20@@QAEXH@Z',0x00423F80),)),
 ('build/gptweb-animation-vm-leaves/Interpolation.obj','?set_end@?$Interpolation@UAngle@th20@@@th20@@QAEXABUAngle@2@@Z',0x00438AE0,24,()),
 ('build/gptweb-animation-vm-leaves/Interpolation.obj','?set_tangent_end@?$Interpolation@UAngle@th20@@@th20@@QAEXABUAngle@2@@Z',0x00438B50,24,()),
 ('build/gptweb-animation-vm-leaves/Interpolation.obj','?set_start@?$Interpolation@UAngle@th20@@@th20@@QAEXABUAngle@2@@Z',0x00439440,23,()),
 ('build/gptweb-animation-vm-leaves/Interpolation.obj','?set_tangent_start@?$Interpolation@UAngle@th20@@@th20@@QAEXABUAngle@2@@Z',0x004394B0,24,()),
 ('build/gptweb-animation-vm-leaves/AnimationParameters.obj','?set_rotation_speed@Animation@th20@@QAEXMMM@Z',0x00439280,76,()),
 ('build/gptweb-animation-vm-leaves/AnimationParameters.obj','?set_scale_speed@Animation@th20@@QAEXMM@Z',0x00439390,62,()),
)
def original_bodies():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image);decoder=Cs(CS_ARCH_X86,CS_MODE_32)
 for address,size,digest,count,ret_arg,calls in LEAVES:
  body=pe.raw_at(image,base,sections,address,size);actual=hashlib.sha256(body).hexdigest();assert actual==digest,(hex(address),actual,digest)
  instructions=list(decoder.disasm(body,address));assert len(instructions)==count,(hex(address),len(instructions),count)
  assert sum(i.size for i in instructions)==size,hex(address)
  assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str==ret_arg,(hex(address),instructions[-1])
  actual_calls=[]
  for i in instructions:
   if i.size==5 and i.bytes[0]==0xE8:actual_calls.append((i.address-address,(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff))
  assert tuple(actual_calls)==calls,(hex(address),actual_calls,calls)
  highlow=tuple(sorted(x-address for x in pe.physical_highlow(image,base,sections) if address<=x<address+size))
  assert not highlow,(hex(address),highlow)
 print('PASS original PE: eight whole body hashes, 115/115 instructions, exact returns, one original E8 to Timer::set and zero HIGHLOW fields')
def candidate_proofs():
 total=0
 for path,symbol,address,size,expected_relocs in CANDIDATES:
  obj=ROOT/path;body,relocations=cf.object_function(obj,symbol,size);assert len(body)==size,(symbol,len(body),size)
  actual=tuple(sorted((int(r['offset']),r['type'],str(r['symbol'])) for r in relocations));expected=tuple(sorted((off,typ,sym) for off,typ,sym,_ in expected_relocs));assert actual==expected,(symbol,actual,expected)
  report=cf.compare(obj,symbol,address,size);assert report['result']=='structural-exact' and report['size']==size,(symbol,report);assert not report['first_differences'],(symbol,report['first_differences'])
  solved=tuple(sorted((int(r['offset'],16),r['type'],r['symbol'],int(r['solved_destination'],16)) for r in report['relocations']));assert solved==tuple(sorted(expected_relocs)),(symbol,solved,expected_relocs)
  total+=size;print(f'PASS {hex(address)} {size}/{size}: {symbol}')
 assert total==305,total
 print('PASS 8/8 VM leaves, 305/305 bytes; 301 ordinary bytes plus one genuine four-byte REL32 field; zero ordinary-byte differences')
def main():
 original_bodies()
 if len(sys.argv)==1:candidate_proofs()
 elif len(sys.argv)==2 and sys.argv[1]=='--original-only':return
 else:raise SystemExit('usage: verify-animation-vm-leaves-native.py [--original-only]')
if __name__=='__main__':main()
