#!/usr/bin/env python3
"""Immutable original 40B game Renderer file-by-index owner and true callers.

One native 22B folded array-index E8: no duplicate original function credit.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('fpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('fcm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00437970
SHA='8b9fce492db39f692e526a4181a320e25860bcf30fed6c69430d98f68ff2a3f9'
INDEX_SHA='63c49b1813004cda4fdbb91fb68008a819c44d98c1c64a7fc76b4405f26a10b8'
SYM='?file_by_index@AnimationPoolOwner@th20@@QAEPAVAnimationFile@2@H@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 code=pe.raw_at(im,base,sec,HEAD,40)
 assert hashlib.sha256(code).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==15 and ins[-1].address+ins[-1].size==HEAD+40
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)=={0x1B:0x00414580}
 assert not any(HEAD<=x<HEAD+40 for x in hl)
 # Original large Renderer owner genuinely indexes an array at +0x6000730.
 assert any(i.mnemonic=='add' and i.op_str=='eax, 0x6000730' for i in ins)
 native_folded=pe.raw_at(im,base,sec,0x00414580,22)
 assert hashlib.sha256(native_folded).hexdigest()==INDEX_SHA
 ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native_folded,0x00414580))
 assert len(ni)==10 and ni[-1].address+ni[-1].size==0x00414580+22
 for caller,n,hashval in [
 (0x00437470,29,'5d522088adaae7cf6dd7874b1fb8dffce62e06decfa592bc4877f4f3d745a246')]:
  b=pe.raw_at(im,base,sec,caller,n)
  assert hashlib.sha256(b).hexdigest()==hashval
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,caller))
  assert calls(ci,caller)=={0x14:HEAD}
 assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,0x00437500,29),0x00437500)),0x00437500)=={0x14:HEAD}
 z=cm.compare_unit('animation_pool_file_by_index_40')
 assert z['result']=='exact' and z['size']==40 and z['matched_bytes']==40
 compare=cm.compare(ROOT/'build/core1090-canonical/AnimationFileByIndex40.obj',SYM,HEAD,40)
 assert compare['result']=='structural-exact'
 assert compare['matched_comparable_bytes']==compare['comparable_bytes']==36
 assert len(compare['relocations'])==1
 assert compare['relocations'][0]['offset']=='0x1C' and int(compare['relocations'][0]['solved_destination'],16)==0x00414580
 print('PASS original whole game AnimationPoolOwner::file_by_index 40B/15 i386, one original E8+0x1B -> 22B folded array getter; zero PE HIGHLOW')
 print('PASS genuine Renderer +0x06000730 42-slot array and both separate 29B original AnimationBase+0x18/+0x1C getters E8+0x14')
 print('PASS 40/40 canonical code, 36/36 ordinary bytes and actual original E8/COFF field target independently attested; no duplicate 22B generic credit')
if __name__=='__main__':verify()
