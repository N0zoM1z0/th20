#!/usr/bin/env python3
"""Immutable original 294B ASCII text submit and nonexact typed C++20 frontier.

The source 319B candidate is never compared to a shortened original extent.
All seven original E8 destinations are read from the locked original PE.
"""
import argparse,hashlib,importlib.util,struct,sys
from pathlib import Path
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('sub294pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('sub294coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x0044FFF0
SIZE=294
SHA='daf9779671bfb7d0dfa8918eaadbbe26c68a659255a569e7ded769d0b3144f53'
E8={0x041:0x004140F0,0x06C:0x00415830,0x092:0x00414400,
    0x0AB:0x004140F0,0x0D4:0x00415830,0x0FA:0x00414400,
    0x10F:0x00414400}
DATA={0x06:0x005686FD,0x15:0x005B25C0}
SYM='?submit_text_44fff0@NativeTextSubmitOwner@th20@@QAE?AUNativeTextDrawResult8@2@PAUIDirect3DBaseTexture9@@PAUSpriteData@2@HHIPBDHHHPBUNativeTextTransform4@2@HV?$function@$$A6AXXZ@std@@@Z'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify(candidate):
 img,_=pe.verified_target();base,sections=pe.parse_sections(img)
 body=pe.raw_at(img,base,sections,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==106 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x58')
 assert calls(ins,HEAD)==E8
 data={x-HEAD:struct.unpack('<I',pe.raw_at(img,base,sections,x,4))[0]
       for x in pe.physical_highlow(img,base,sections) if HEAD<=x<HEAD+SIZE}
 assert data==DATA
 assert pe.raw_at(img,base,sections,HEAD+SIZE,5)==b'\xCC'*5
 parenthead=0x0044B020
 parent=pe.raw_at(img,base,sections,parenthead,578)
 assert hashlib.sha256(parent).hexdigest()=='fd121bcfb2bb70f0ea9015ed166f137eaa8fef7e663b5c4cbc781d0cee9a4617'
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,parenthead))
 assert len(pins)==139
 assert [off for off,target in calls(pins,parenthead).items() if target==HEAD]==[0x202]
 print('PASS immutable 294B/106-i386 text submit, two actual E8 to full 2,227B native text core')
 print('PASS three genuine function destructors/two copies; 7 original E8/2 PE HIGHLOW, ret 0x58')
 print('PASS original 578B text renderer E8 +0x202 to this 294B native method')
 if candidate:
  b,rel=coff.object_function(candidate,SYM,319)
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b),0))
  assert len(b)==319 and len(ci)==112 and len(rel)==9
  assert sum(r['type']=='REL32' for r in rel)==7
  assert sum(r['type']=='DIR32' for r in rel)==2
  mapped=[]
  for row in rel:
   sym=row['symbol']
   if row['type']=='REL32':
    if sym.startswith('??0?$function@'):mapped.append(0x004140F0)
    elif sym.startswith('??1?$function@'):mapped.append(0x00414400)
    elif sym.startswith('?native_text_core_415830@'):mapped.append(0x00415830)
    else:raise AssertionError(('Unknown source E8 role',sym))
  assert mapped==list(E8.values())
  assert all(row['addend']==0 for row in rel)
  print('FRONTIER: natural C++20 source 319B/112 i386, 7 E8 in exact native semantic order, two DIR32')
  print('NONEXACT: unmatched original EH/aggregate-copy lowering, 25B/6 instructions too long')
 print('No canonical strict unit or game-authored exact credit for 294B body or 2,227B core')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
