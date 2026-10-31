#!/usr/bin/env python3
"""Read-only original 71B HUD two-slot cleanup and original 22/34B call graph."""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('card_hud_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('card_hud_cmp',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
SPECS={
 'vm_setter':(0x00477450,34,13,'cca7a010f22f156820752be560ac83387443c77ba38a234138310dd0c427f4d3',
              '?set_vm_event_477450@NativeHudAnimationView@th20@@QAEXH@Z',{0x16:0x0042B5D0},'4'),
 'bridge':(0x00488900,22,11,'e36c4547389b0ea8bbdc98f42f9eb75e763dd34f0d3b481650c537fb74f77741',
           '?finish_stage_488900@NativeHudAnimationView@th20@@QAEXXZ',{0x0C:0x00477450},''),
 'hud_boss':(0x00488AB0,71,24,'098426e2c54ec1c6bae79b2fd7d55292ca34ccbd5bbc085ca0e6b28564c3c1c9',
             '?clear_spell_effects_488ab0@NativeCardHudView@th20@@QAEXXZ',
             {0x19:0x00414580,0x20:0x00488900,0x36:0x00414580,0x3D:0x00488900},''),
}
def verify(obj):
 image,_=pe.verified_target();base,secs=pe.parse_sections(image)
 reloc=pe.physical_highlow(image,base,secs)
 for name,(addr,size,count,sha,symbol,calls,ret_size) in SPECS.items():
  body=pe.raw_at(image,base,secs,addr,size)
  assert hashlib.sha256(body).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,addr))
  assert len(ins)==count and ins[-1].address+ins[-1].size==addr+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret',ret_size)
  observed={i.address-addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in ins if i.size==5 and i.bytes[0]==0xe8}
  assert observed==calls,(name,observed,calls)
  assert not any(addr<=r<addr+size for r in reloc)
  assert pe.raw_at(image,base,secs,addr+size,5)==b'\xcc'*5
  print(f'PASS native {name}: whole {size}B/{count} i386, {len(calls)} real E8, no PE HIGHLOW, genuine RET and INT3')
  if obj:
   result=coff.compare(obj,symbol,addr,size)
   assert result['result']=='structural-exact',result
   assert result['matched_comparable_bytes']==size-4*len(calls)
   assert {(int(r['offset'],16)-1,int(r['solved_destination'],16)) for r in result['relocations']}==set(calls.items())
   print(f'PASS source {name}: complete {size}/{size} original, {len(calls)} independent relocated roles')
 card=pe.raw_at(image,base,secs,0x004878B0,602)
 assert hashlib.sha256(card).hexdigest()=='17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f'
 assert card[0x8E]==0xE8
 assert (0x004878B0+0x8E+5+struct.unpack_from('<i',card,0x8F)[0])&0xffffffff==0x00488AB0
 print('PASS actual original Card finish 602B E8 +0x8E -> 71B HUD boss')
 print('Original 602B Card finish stays source-present NONEXACT; no transitive credit')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path);a=p.parse_args();verify(a.candidate_object)
