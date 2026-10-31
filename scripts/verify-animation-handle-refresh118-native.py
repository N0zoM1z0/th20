#!/usr/bin/env python3
"""Whole immutable original game 118B handle rebind and 29B file getter.

The two distinct game original bodies are verified from real PE, then
independently whole canonical pinned MSVC replay receipts are inspected.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('hpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('hcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
S={
 'animation_legacy_file_29':(0x00437470,29,12,'5d522088adaae7cf6dd7874b1fb8dffce62e06decfa592bc4877f4f3d745a246',
  {0x14:0x00437970},{0x10:0x005C0028},'ret','',
  '?previous_file_437470@NativeAnimationLegacyFileView@th20@@QAEPAVAnimationFile@2@XZ'),
 'animation_handle_refresh_boss_118':(0x0044BCD0,118,41,'970c832112e93d29c132e7ebcce3077c751848ef4004a1a4797117a2b7162d3c',
  {0x15:0x0044CD00,0x26:0x00437470,0x31:0x0044FD00,
   0x48:0x00450C70,0x57:0x0040C300,0x65:0x0040C300},
  {0x11:0x005C0028},'ret','4',
  '?rebind_animation_44bcd0@NativeAnimationHandleRefreshView@th20@@QAEXH@Z'),
}
def calls(ins,h):
 return {i.address-h:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sec)
 seen=set()
 obj=ROOT/'build/core1089-canonical/AnimationHandleRefresh118.obj'
 for unit,(head,n,ni,sha,e8,data,mnem,op,sym) in S.items():
  b=pe.raw_at(img,base,sec,head,n)
  assert hashlib.sha256(b).hexdigest()==sha,unit
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,head))
  assert len(ins)==ni and ins[-1].address+ins[-1].size==head+n
  assert (ins[-1].mnemonic,ins[-1].op_str)==(mnem,op)
  assert calls(ins,head)==e8
  actual={x-head:struct.unpack('<I',pe.raw_at(img,base,sec,x,4))[0]
          for x in hl if head<=x<head+n}
  assert actual==data
  assert not (seen & set(range(head,head+n)))
  seen.update(range(head,head+n))
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
  cmp=cm.compare(obj,sym,head,n)
  assert cmp['result']=='structural-exact'
  assert cmp['comparable_bytes']==cmp['matched_comparable_bytes']==n-4*(len(e8)+len(data))
  roles={**{k:('DIR32',v) for k,v in data.items()},**{k+1:('REL32',v) for k,v in e8.items()}}
  assert len(cmp['relocations'])==len(roles)==len(z['relocations'])
  for f in cmp['relocations']:
   off=int(f['offset'],16)
   assert off in roles and f['type']==roles[off][0]
   assert int(f['solved_destination'],16)==roles[off][1]
  print(f'PASS {unit} whole original game {n}B/{ni}-i386, {len(e8)} native E8/{len(data)} PE HIGHLOW, canonical {n}/{n}')
 assert len(seen)==147
 # Distinguish observed +0x18 lookup from previously accepted +0x1C
 # lookup at a separate physical 29B original head.
 existing=pe.raw_at(img,base,sec,0x00437500,29)
 ei=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(existing,0x00437500))
 assert calls(ei,0x00437500)=={0x14:0x00437970}
 assert existing != pe.raw_at(img,base,sec,0x00437470,29)
 assert cm.compare_unit('animation_legacy_file_29')['result']=='exact'
 # Compare whole original 118B last return and all six source E8 targets;
 # source uses real by-value struct assignment from the 57B spawn return.
 assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(img,base,sec,0x0044BCD0,118),0x0044BCD0)),0x0044BCD0)[0x26]==0x00437470
 print('PASS actual native AnimationBase+0x18 alternate file vs existing distinct AnimationBase+0x1C getter 29B: no overlap or duplicate credit')
 print('PASS native 118B rebind: resolve live handle, stop animation, return-by-value spawn, natural AnimationHandle STRUCT assignment, two original file-ID getters')
 print('PASS two new game-owned physical heads /147 exact bytes and one affected canonical source object; no child bytes repeated')
if __name__=='__main__':verify()
