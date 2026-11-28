#!/usr/bin/env python3
"""Whole 35B tangent adapter source proof; author origin held review."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,path):
 spec=importlib.util.spec_from_file_location(n,R/path)
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
cf=load('tan35_cf','scripts/compare-coff-function.py')
pe=load('tan35_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00439850
SIZE=35
SHA='883a31db55344f543fa8f0c7823bf4aa241c5e0db38e7dac33a591917ce25f7a'
SYM='?native_tan_439850@th20@@YAMM@Z'
UNIT='graphics_camera_tan_adapter_35'
def verify_tangent_relocation(relocations):
 fields=[(r['offset'],r['type'],r['symbol'],r['addend']) for r in relocations]
 assert fields==[(0x12,'REL32','_tan',0)],'adapter must call _tan; ordinary-byte identity alone does not establish the callee'
def main():
 image=cf.verified_target();base,sec=pe.parse_sections(image)
 native=pe.raw_at(image,base,sec,HEAD,SIZE)
 assert hashlib.sha256(native).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ins)==13 and ins[-1].address+ins[-1].size==HEAD+SIZE
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x11:0x00550000}
 assert pe.raw_at(image,base,sec,0x55B47D,2)==bytes.fromhex('d9f2') # FPTAN in the independently identified default body.
 assert not any(HEAD<=p<HEAD+SIZE for p in pe.physical_highlow(image,base,sec))
 unit=cf.load_manifest('match-units.toml')['units'][UNIT]
 code,rel=cf.object_function(R/unit['object'],SYM,SIZE)
 assert len(code)==SIZE
 verify_tangent_relocation(rel)
 assert code[:0x12]+code[0x16:]==native[:0x12]+native[0x16:]
 proof=cf.compare_unit(UNIT)
 assert proof['result']=='exact' and proof['matched_bytes']==SIZE
 parent=cf.compare_unit('graphics_camera_matrix_boss_846')
 assert parent['result']=='exact' and parent['matched_bytes']==846
 print('PASS immutable native 35B/13-i386 tangent wrapper, genuine E8 at +0x11 to _tan at 0x00550000')
 print('PASS full source 35/35B, 31/31 ordinary bytes and 846B camera Boss whole exact')
 print('ORIGIN REVIEW: standard math/CRT-like generated wrapper, no new game-authored byte credit')
if __name__=='__main__':main()
