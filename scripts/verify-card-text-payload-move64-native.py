#!/usr/bin/env python3
"""Immutable original 64B typed Card payload move constructor and parent E8."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('move_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('move_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x00486AF0
SHA='73fe6bdfd5aaa84445e1648d41ce27562dd4717d3af492a96b14cb3a28f6ad3b'
PARENT=0x004867B0
PARENT_SHA='f91c1c12104a5688a3ef89f1b971eb7695e4b4520449c78e3b5bfa007dc3a802'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img);high=pe.physical_highlow(img,base,secs)
 body=pe.raw_at(img,base,secs,HEAD,64)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==24 and ins[-1].address+ins[-1].size==HEAD+64
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)=={0x26:0x0046A710}
 assert not any(HEAD<=p<HEAD+64 for p in high)
 parent=pe.raw_at(img,base,secs,PARENT,66)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pins)==23 and pins[-1].address+pins[-1].size==PARENT+66
 assert calls(pins,PARENT)=={0x0C:0x0040BDA0,0x27:0x0040B280,0x33:HEAD}
 unit=coff.compare_unit('card_text_payload_move_64')
 assert unit['result']=='exact' and unit['size']==64 and unit['matched_bytes']==64
 assert len(unit['relocations'])==1
 print('PASS native Card PMR capture move: 64B/24 i386, exact E8 +0x26 to original PMR move ctor 0x0046A710')
 print('PASS original 66B lambda target wrapper E8 +0x33 directly into native 64B payload move')
 print('PASS pinned canonical complete 64/64 source; original 108B PMR move callee not claimed exact')
if __name__=='__main__':verify()
