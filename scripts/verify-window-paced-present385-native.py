#!/usr/bin/env python3
"""Original 385B Window pacing Boss, whole native and canonical MSVC evidence."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 s=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('window385_cf','scripts/compare-coff-function.py')
pe=load('window385_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00419A50
SIZE=385
SHA='0df260cff4e294279f3836178fe78ef891f39c2ebd0f86b977d4ef175fbdd19a'
SYM='?present_paced_419a50@NativeWindowFrameScheduleView@th20@@QAEXXZ'
CALLS={0x0C:0x0041CB10,0xC7:0x0041CB10,0xD8:0x00419760,
       0xE3:0x00412730,0x10E:0x004DD840,0x119:0x0041DBE0,
       0x123:0x00412730,0x148:0x0041D9F0,0x152:0x004DBD70,
       0x157:0x0041A2C0,0x169:0x0041CB10,0x177:0x004193C0}
DATA={0x1D:0x005C4F89,0x44:0x0056C468,0x4C:0x0056C470,
      0x70:0x0056CD50,0x7A:0x0056C468,0x82:0x0056C470,
      0xA0:0x0056CD88,0xA8:0x0056CD80,0xBF:0x0056C16C,
      0xDF:0x005C4D40,0x10A:0x005C4D40,0x115:0x005C0028,
      0x11F:0x005C4D40,0x137:0x005C4E24,0x144:0x005C0028,
      0x14E:0x005C4D40,0x15E:0x005C586C}
def main():
 e=cf.verified_target();base,sections=pe.parse_sections(e)
 original=pe.raw_at(e,base,sections,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==94 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert {x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
         for x in ins if x.size==5 and x.bytes[0]==0xe8}==CALLS
 assert {p-HEAD:struct.unpack('<I',pe.raw_at(e,base,sections,p,4))[0]
         for p in pe.physical_highlow(e,base,sections) if HEAD<=p<HEAD+SIZE}==DATA
 assert [i.address-HEAD for i in ins if i.mnemonic=='nop']==[0xC3,0xDD,0x17C]
 src,rel=cf.object_function(R/'build/core1134-canonical/WindowPacedPresent385.obj',SYM,SIZE)
 assert len(src)==SIZE and len(rel)==29
 calls=[r for r in rel if r['type']=='REL32']
 data=[r for r in rel if r['type']=='DIR32']
 assert [r['offset']-1 for r in calls]==list(CALLS)
 assert [r['offset'] for r in data]==list(DATA)
 mask={i for r in rel for i in range(r['offset'],r['offset']+4)}
 assert len(mask)==116
 assert all(x==y for j,(x,y) in enumerate(zip(original,src)) if j not in mask)
 unit=cf.compare_unit('window_paced_present_385')
 assert unit['result']=='exact' and unit['matched_bytes']==SIZE
 for dep,n in [('window_present_no_wait_164',164),('window_active_repeat_31',31)]:
  p=cf.compare_unit(dep)
  assert p['result']=='exact' and p['matched_bytes']==n,dep
 print('PASS original 385B/94 i386 Window 1/60 frame pacing SHA, complete 12 E8/17 HIGHLOW physical sites/destinations')
 print('PASS canonical full 385/385B source, 269/269 ordinary bytes and all three original compiler NOPs; no fake locals/padding')
 print('PASS existing 164B no-wait Present and 31B Window repeat remain exact, 574B screenshot and 884B scheduler still NONEXACT')
if __name__=='__main__':main()
