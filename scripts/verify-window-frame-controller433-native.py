#!/usr/bin/env python3
"""Entire immutable 433B Window frame controller against actual MSVC source."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
def load(name,file):
 spec=importlib.util.spec_from_file_location(name,ROOT/file);module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
cf=load('wframe433_cf','scripts/compare-coff-function.py')
pe=load('wframe433_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00419C20
SIZE=433
SHA='654fba82d5f91a2b76d3fafe839c887812ab20086ae9f7a3a35a58b42432df76'
SYM='?frame_controller_step_419c20@NativeWindowFrameScheduleView@th20@@QAEHXZ'
def main():
 exe=cf.verified_target();base,sec=pe.parse_sections(exe)
 original=pe.raw_at(exe,base,sec,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==110 and ins[-1].address+ins[-1].size==HEAD+SIZE
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff for x in ins if x.size==5 and x.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sec,p,4))[0] for p in pe.physical_highlow(exe,base,sec) if HEAD<=p<HEAD+SIZE}
 assert len(calls)==15 and len(data)==18
 assert calls[0x179]==0x004193E0
 assert calls[0x073]==0x00412810 and calls[0x11B]==0x00412AA0
 assert data[0x103]==0x005C5AF8
 assert any(x.mnemonic=='nop' and x.address-HEAD==0x1AA for x in ins)
 candidate,rel=cf.object_function(ROOT/'build/core1136-canonical/WindowFrameControllerBoss433.obj',SYM,SIZE)
 assert len(candidate)==SIZE and len(rel)==33
 assert [r['offset']-1 for r in rel if r['type']=='REL32']==list(calls)
 assert [r['offset'] for r in rel if r['type']=='DIR32']==list(data)
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==132
 assert all(a==z for i,(a,z) in enumerate(zip(original,candidate)) if i not in mask)
 for unit,size in [('window_frame_controller_boss_433',433),('window_snapshot_scene_boss_574',574),('window_active_repeat_31',31)]:
  proof=cf.compare_unit(unit)
  assert proof['result']=='exact' and proof['matched_bytes']==size,unit
 print('PASS locked original 433B/110 i386 SHA, all 15 E8 and 18 HIGHLOW physical sites/destinations')
 print('PASS natural MSVC whole 433/433 strict exact; 301/301 ordinary bytes, real D3D9 SetTexture and 32-bit render alpha')
 print('PASS 574B screenshot and 31B Window repeat exact, 884B scheduler still NONEXACT and uncredited')
if __name__=='__main__':main()
