#!/usr/bin/env python3
"""Complete original 2245B glyph vector insertion/growth/rollback parents.

All five source-present STL template methods are full original PE pinned;
modern MSVC generated code is meaningful but individually NONEXACT.
"""
import hashlib,importlib.util,subprocess,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('parpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('parcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'emplace_back':(0x00416330,35,15,'bd26f62ba6f30fe4d6e5845561e0cc2ecdd80da8bc771cdcdd260e25109343b4',2,0,33,13,1,0,'??$emplace_back@ABV?$array@'),
 'one_at_back':(0x00413370,108,40,'2ad1446dee98794f9578c474b883145c2296ff1adcb2def8d653e3d365e5e04b',4,0,78,30,2,0,'??$_Emplace_one_at_back@ABV?$array@'),
 'reallocate':(0x004133E0,488,170,'5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57',14,2,467,163,13,2,'??$_Emplace_reallocate@ABV?$array@'),
 'uninitialized_move':(0x00413920,200,65,'ec0f652bfa6eaf3ee4ac165bd3088e80e924fc7b8747e74ba133d3041febca65',9,2,191,62,8,2,'??$_Uninitialized_move@PAV?$array@'),
 'non_growth':(0x004132E0,140,52,'1f514d2135b7b78ef041cc44ba21003fe295a2033b33a1a78eb8e40862bc37f2',5,0,125,47,4,0,'??$_Emplace_back_with_unused_capacity@ABV?$array@'),
}
PARENT=0x00416420
PARENT_SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
def calls(instr,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in instr if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sections=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sections)
 code={};orig_calls={}
 obj=ROOT/'build/core1052-canonical/GlyphMaskComposite2245.obj'
 symbols=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 for label,(head,n,nins,sha,ecount,hcount,csize,cins,ce,cd,prefix) in SPECS.items():
  data=pe.raw_at(img,base,sections,head,n)
  assert hashlib.sha256(data).hexdigest()==sha,label
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(data,head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+n
  assert ins[-1].mnemonic=='ret'
  dest=calls(ins,head);orig_calls[label]=dest
  assert len(dest)==ecount
  high={p-head:struct.unpack('<I',pe.raw_at(img,base,sections,p,4))[0]
        for p in hl if head<=p<head+n}
  assert len(high)==hcount
  if label=='reallocate':assert high=={0x06:0x00567CED,0x15:0x005B25C0}
  if label=='uninitialized_move':assert high=={0x06:0x00567D6D,0x15:0x005B25C0}
  code[label]=set(range(head,head+n))
  sym=next(s for s in symbols if s.startswith(prefix))
  b,r=cm.object_function(obj,sym,csize)
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b),0))
  assert len(b)==csize and len(ci)==cins and len(r)==ce+cd
  assert sum(x['type']=='REL32' for x in r)==ce
  assert sum(x['type']=='DIR32' for x in r)==cd
  assert all(x['addend']==0 for x in r)
  print(f'PASS original entire {label} at {head:#x}: {n}B/{nins} x86, {ecount} real E8/{hcount} HL; SOURCE-PRESENT NONEXACT {csize}B/{cins} x86, {ce} E8/{cd} DIR32')
 assert all(not(a&b) for i,a in enumerate(code.values()) for b in list(code.values())[i+1:])
 assert orig_calls['emplace_back']=={0x0B:0x0040B280,0x17:0x00413370}
 assert orig_calls['one_at_back']=={0x2C:0x0040B280,0x38:0x004132E0,0x43:0x0040B280,0x61:0x004133E0}
 assert orig_calls['reallocate'][0x146]==orig_calls['reallocate'][0x162]==orig_calls['reallocate'][0x18B]==0x00413920
 assert orig_calls['non_growth'][0x69]==0x00414B60
 outer=pe.raw_at(img,base,sections,PARENT,2245)
 assert hashlib.sha256(outer).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(outer,PARENT))
 assert len(pi)==612
 outer_calls=calls(pi,PARENT)
 assert [pos for pos,val in outer_calls.items() if val==0x00416330]==[0x165,0x4DD]
 for unit in ['glyph_vec_calculate_growth_84','glyph_vec_allocate_at_least_19','glyph_vec_pmr_array_allocate_58',
              'glyph_vec_backout_ctor_42','glyph_vec_backout_release_28','glyph_vec_backout_dtor_39',
              'glyph_vec_orphan_range_13','glyph_vec_growth_change_array_165']:
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS whole original 2245B glyph Boss two E8 to 35B wrapper -> 108B one-at-back -> 140B no-growth or 488B reallocation ->200B uninitialized move')
 print('PASS eight representative exact native PMR child units, zero parent/game-authored code credited from five NONEXACT STL parents')
if __name__=='__main__':verify()
