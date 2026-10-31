#!/usr/bin/env python3
"""Immutable original Card text capture 22B PMR name getter and 111B caller."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('text22_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('text22_cmp',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x0044BAF0
SHA='43bd0312020d597cfa7218127be88cc8f928d51c1671f92cda054524d49f043b'
CALLER=0x00486E80
CALLER_SHA='12212f28b9331ddb3041bea74034cf798e3bc7ab873eb2372b2146cb430d21ae'
def calls(ins,addr):
 return {i.address-addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 image,_=pe.verified_target();base,secs=pe.parse_sections(image);high=pe.physical_highlow(image,base,secs)
 raw=pe.raw_at(image,base,secs,HEAD,22)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==10 and ins[-1].address+ins[-1].size==HEAD+22
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)=={0x0D:0x0040F2C0}
 assert not any(HEAD<=x<HEAD+22 for x in high)
 caller=pe.raw_at(image,base,secs,CALLER,111)
 assert hashlib.sha256(caller).hexdigest()==CALLER_SHA
 parent=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(caller,CALLER))
 assert len(parent)==42 and parent[-1].address+parent[-1].size==CALLER+111
 assert calls(parent,CALLER)=={0x10:HEAD,0x36:0x004142A0,0x3E:0x00486740,0x62:0x0044B020}
 unit=coff.compare_unit('card_text_capture_cstr_22')
 assert unit['result']=='exact' and unit['size']==22 and unit['matched_bytes']==22
 assert len(unit['relocations'])==1
 print('PASS original 22B/10-i386 Card capture string getter, E8 +0xD -> native PMR pointer 0x0040F2C0')
 print('PASS actual original 111B Card lambda callback E8 +0x10 -> native 22B getter')
 print('PASS canonical whole 22/22 natural C++20 text.c_str(), provenance uncredited')
 print('Native 111B callback, 102B function ctor, 1,896B Card start still NONEXACT')
if __name__=='__main__':verify()
