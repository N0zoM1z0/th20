#!/usr/bin/env python3
"""SHA attest whole original 164B Window Present/Reset and exact C++ source."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 s=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('window164_cf','scripts/compare-coff-function.py')
pe=load('window164_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004199A0
SIZE=164
SHA='88a1ce526edc201f959f36a1e0656b9287e053884985441bc3bde9a9354e906e'
SYM='?present_no_wait_4199a0@NativeWindowFrameScheduleView@th20@@QAEXXZ'
E8={0x0C:0x00419760,0x17:0x00412730,0x42:0x004DD840,
    0x4D:0x0041DBE0,0x57:0x00412730,0x7C:0x0041D9F0,
    0x86:0x004DBD70,0x8B:0x0041A2C0,0x9A:0x004193C0}
DATA={0x13:0x005C4D40,0x3E:0x005C4D40,0x49:0x005C0028,
      0x53:0x005C4D40,0x6B:0x005C4E24,0x78:0x005C0028,
      0x82:0x005C4D40,0x92:0x005C586C}
def main():
 e=cf.verified_target();base,sections=pe.parse_sections(e)
 original=pe.raw_at(e,base,sections,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 i=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(i)==49 and i[-1].address+i[-1].size==HEAD+SIZE
 assert {x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
         for x in i if x.size==5 and x.bytes[0]==0xe8}==E8
 assert {p-HEAD:struct.unpack('<I',pe.raw_at(e,base,sections,p,4))[0]
         for p in pe.physical_highlow(e,base,sections) if HEAD<=p<HEAD+SIZE}==DATA
 assert any(x.address-HEAD==0x11 and x.mnemonic=='nop' for x in i)
 assert any(x.address-HEAD==0x9f and x.mnemonic=='nop' for x in i)
 source,rel=cf.object_function(R/'build/core1133-canonical/WindowPresentNoWait164.obj',SYM,SIZE)
 assert len(source)==SIZE and len(rel)==17
 e8=[r for r in rel if r['type']=='REL32']
 data=[r for r in rel if r['type']=='DIR32']
 assert [r['offset']-1 for r in e8]==list(E8)
 assert [r['offset'] for r in data]==list(DATA)
 mask={z for r in rel for z in range(r['offset'],r['offset']+4)}
 assert len(mask)==68
 assert all(x==y for off,(x,y) in enumerate(zip(original,source)) if off not in mask)
 exact=cf.compare_unit('window_present_no_wait_164')
 assert exact['result']=='exact' and exact['matched_bytes']==164
 for other,n in [('window_active_repeat_31',31),('window_frame_clock_dispatch_32',32)]:
  p=cf.compare_unit(other)
  assert p['result']=='exact' and p['matched_bytes']==n
 snap=cf.compare_unit('window_snapshot_scene_boss_574')
 assert snap['result']=='exact' and snap['matched_bytes']==574
 print('PASS original complete Window Present/Reset 164B/49-i386 SHA, 9 E8/8 PE HIGHLOW physical sites and original destinations')
 print('PASS 164/164 byte natural C++ source, all 96/96 ordinary bytes, real MSVC scope NOP and separate present/reset D3D9 device lifetimes')
 print('PASS previously exact 31B repeat getter and 32B clock dispatch remain strictly exact; 574B scene callee now whole strict exact')
if __name__=='__main__':main()
