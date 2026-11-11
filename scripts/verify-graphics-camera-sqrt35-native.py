#!/usr/bin/env python3
"""Whole 35B standard sqrt adapter source proof; author origin held review."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,path):
 spec=importlib.util.spec_from_file_location(n,R/path)
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
cf=load('sqrt35_cf','scripts/compare-coff-function.py')
pe=load('sqrt35_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00439850
SIZE=35
SHA='883a31db55344f543fa8f0c7823bf4aa241c5e0db38e7dac33a591917ce25f7a'
SYM='?native_sqrt_439850@th20@@YAMM@Z'
def main():
 image=cf.verified_target();base,sec=pe.parse_sections(image)
 native=pe.raw_at(image,base,sec,HEAD,SIZE)
 assert hashlib.sha256(native).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ins)==13 and ins[-1].address+ins[-1].size==HEAD+SIZE
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x11:0x00550000}
 assert not any(HEAD<=p<HEAD+SIZE for p in pe.physical_highlow(image,base,sec))
 code,rel=cf.object_function(R/'build/core1143-canonical/GraphicsCameraSqrtAdapter35.obj',SYM,SIZE)
 assert len(code)==SIZE and rel==[{'offset':0x12,'type_id':20,'type':'REL32','symbol':'_sqrt','addend':0}]
 assert code[:0x12]+code[0x16:]==native[:0x12]+native[0x16:]
 proof=cf.compare_unit('graphics_camera_sqrt_adapter_35')
 assert proof['result']=='exact' and proof['matched_bytes']==SIZE
 parent=cf.compare_unit('graphics_camera_matrix_boss_846')
 assert parent['result']=='exact' and parent['matched_bytes']==846
 print('PASS immutable native 35B/13-i386 sqrt wrapper, genuine E8 at +0x11 to 0x00550000')
 print('PASS full source 35/35B, 31/31 ordinary bytes and 846B camera Boss whole exact')
 print('ORIGIN REVIEW: standard math/CRT-like generated wrapper, no new game-authored byte credit')
if __name__=='__main__':main()
