#!/usr/bin/env python3
"""SHA-attested whole original 583B Window no-wait frame controller."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
def load(n,p):
 spec=importlib.util.spec_from_file_location(n,ROOT/p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
cf=load('wframe583_cf','scripts/compare-coff-function.py')
pe=load('wframe583_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00419DE0
SIZE=583
SHA='8be338e7187df3309e96af13f8d550ce3ebed483e99682ba4376b5a8a0e08b5f'
SYM='?frame_controller_no_wait_419de0@NativeWindowFrameScheduleView@th20@@QAEHXZ'
def main():
 exe=cf.verified_target();base,sections=pe.parse_sections(exe)
 original=pe.raw_at(exe,base,sections,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==138 and ins[-1].address+ins[-1].size==HEAD+SIZE
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sections,p,4))[0]
       for p in pe.physical_highlow(exe,base,sections) if HEAD<=p<HEAD+SIZE}
 assert len(calls)==16 and len(data)==20
 assert calls[0x20F]==0x004199A0
 assert calls[0x108]==0x00412810 and calls[0x1B1]==0x00412AA0
 assert data[0x199]==0x005C5AF8 and data[0x234]==0x005C5B18
 assert [i.address-HEAD for i in ins if i.mnemonic=='nop']==[0x8E,0x214,0x240]
 candidate,rel=cf.object_function(ROOT/'build/core1137-canonical/WindowFrameNoWaitBoss583.obj',SYM,SIZE)
 assert len(candidate)==SIZE and len(rel)==36
 assert [r['offset']-1 for r in rel if r['type']=='REL32']==list(calls)
 assert [r['offset'] for r in rel if r['type']=='DIR32']==list(data)
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==144
 assert all(a==z for j,(a,z) in enumerate(zip(original,candidate)) if j not in mask)
 for unit,size in [('window_frame_no_wait_boss_583',583),
                   ('window_present_no_wait_164',164),('window_snapshot_scene_boss_574',574),
                   ('window_frame_controller_boss_433',433)]:
  proof=cf.compare_unit(unit)
  assert proof['result']=='exact' and proof['matched_bytes']==size,unit
 print('PASS original full 583B/138-i386 SHA and 16 E8 /20 HIGHLOW physical sites and target identities')
 print('PASS all 439/439 ordinary code bytes, original three compiler NOPs, complete pinned MSVC 583/583 strict source')
 print('PASS dependent 164B Present, 574B screenshot, 433B frame controller individually exact; 884B scheduler still NONEXACT')
if __name__=='__main__':main()
