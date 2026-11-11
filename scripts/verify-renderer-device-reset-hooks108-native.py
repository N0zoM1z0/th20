#!/usr/bin/env python3
"""Five distinct game-authored Renderer D3D9 reset hooks /108 native bytes."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 sp=importlib.util.spec_from_file_location(n,R/p)
 m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m
cf=load('reset108_cf','scripts/compare-coff-function.py')
pe=load('reset108_pe','scripts/verify-animation-draw-boss-native.py')
ROWS=[
 (0x0041DB40,21,0x06000E0C,0x0B,'c466e45dc4538ff1dd7e55f3e3e6cb9a27816055a06f145d32342487f0922a82'),
 (0x0041DB60,21,0x06000E0D,0xFF,'7e1b6fd7034bc77a2c883216b1bcc8d35de8c0cf732a6626042a9585b3fab0a3'),
 (0x0041DB80,21,0x06000E0E,0xFF,'75beda62d49fb93e5fe999fd82cedc4635e1413020730f47cce33b262e42b91f'),
 (0x0041DBA0,24,0x06000E08,0xFFFFFFFF,'b260ca3aeb0c92102a77f863682e2798baa504a7d1cbffe98ec50a16336a947d'),
 (0x0041DBC0,21,0x06000E10,0xFF,'37d1c63516c38f42fa7f70238f337ac7a53b8f630908ebf9c8ecc248629b69cf')
]
def main():
 exe=cf.verified_target();base,sec=pe.parse_sections(exe)
 obj=R/'build/core1147-canonical/RendererDeviceResetHooks108.obj'
 total=0
 for a,n,offset,value,sha in ROWS:
  orig=pe.raw_at(exe,base,sec,a,n)
  assert hashlib.sha256(orig).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(orig,a))
  assert len(ins)==9 and ins[-1].address+ins[-1].size==a+n
  assert not any(a<=p<a+n for p in pe.physical_highlow(exe,base,sec))
  assert not any(x.size==5 and x.bytes[0]==0xe8 for x in ins)
  stores=[i for i in ins if i.mnemonic=='mov' and f'0x{offset:x}' in i.op_str]
  assert len(stores)==1 and f'0x{value:x}' in stores[0].op_str,(hex(a),stores)
  tag=f'{a:06x}'
  sym=f'?restart_state_{tag}@NativeAnimationResetHooks@th20@@QAEXXZ'
  src,rel=cf.object_function(obj,sym,n)
  assert not rel and bytes(src)==orig
  receipt=cf.compare_unit(f'renderer_device_reset_{tag}')
  assert receipt['result']=='exact' and receipt['matched_bytes']==n
  total+=n
  print(f'PASS 0x{a:08X} native {n}/{n}B nine x86, original owner +0x{offset:X} =0x{value:X}, SHA and canonical source full strict exact')
 assert total==108
 # Each source belongs to a unique physical game function head;
 # no folded alias or parent instructions are counted as duplicates.
 assert len({row[0] for row in ROWS})==5
 assert cf.compare_unit('window_frame_scheduler_boss_884')['result']=='exact'
 print('PASS all five unique Renderer game reset hooks, 108/108 original bytes in one source-local cold object')
 print('PASS 884B Window scheduler remains exact; 1954B D3D9 reset parent remains separately NONEXACT and uncredited')
if __name__=='__main__':main()
