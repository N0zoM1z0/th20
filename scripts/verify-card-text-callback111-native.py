#!/usr/bin/env python3
"""Original 111B Card text callable + genuine 22B pmr::string::c_str.

The original string helper receiver is capture+4, not the capture itself.
All native roles are pinned from the immutable PE, never solved from COFF.
"""
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('callback111pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('callback111coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
CALLBACK=0x00486E80
CALLBACK_SHA='12212f28b9331ddb3041bea74034cf798e3bc7ab873eb2372b2146cb430d21ae'
CSTR=0x0044BAF0
CSTR_SHA='43bd0312020d597cfa7218127be88cc8f928d51c1671f92cda054524d49f043b'
CALLS={0x10:CSTR,0x36:0x004142A0,0x3E:0x00486740,0x62:0x0044B020}
HIGHLOW={0x5D:0x005C0028}
def calls(instructions,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in instructions if i.size==5 and i.bytes[0]==0xe8}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 reloc=pe.physical_highlow(image,base,sections)
 body=pe.raw_at(image,base,sections,CALLBACK,111)
 assert hashlib.sha256(body).hexdigest()==CALLBACK_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,CALLBACK))
 assert len(ins)==42 and ins[-1].address+ins[-1].size==CALLBACK+111
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,CALLBACK)==CALLS
 data={p-CALLBACK:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
       for p in reloc if CALLBACK<=p<CALLBACK+111}
 assert data==HIGHLOW
 # Native C++ has add ecx,4 to pass the true embedded PMR string to c_str.
 assert body[0x0D:0x10]==b'\x83\xc1\x04'
 # Native color/layer argument is +0x00FFFFFF, not -1 (-1 is a 2B push).
 assert body[0x4E:0x53]==b'\x68\xff\xff\xff\x00'
 original_cstr=pe.raw_at(image,base,sections,CSTR,22)
 assert hashlib.sha256(original_cstr).hexdigest()==CSTR_SHA
 cins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original_cstr,CSTR))
 assert len(cins)==10 and cins[-1].address+cins[-1].size==CSTR+22
 assert (cins[-1].mnemonic,cins[-1].op_str)==('ret','')
 assert calls(cins,CSTR)=={0x0D:0x0040F2C0}
 assert not any(CSTR<=p<CSTR+22 for p in reloc)
 # At the PMR string level, c_str forwards its String_val subobject at +4
 # to the actual native 0x0040F2C0 _Myptr helper.
 assert original_cstr[0x0A:0x0D]==b'\x83\xc1\x04'
 # Parent Card start 1,896B E8 into its std::function producer at +0x325,
 # whose original 102B/65B children remain nonexact source frontiers.
 parent=pe.raw_at(image,base,sections,0x00487C30,1896)
 # Use the full immutable Card parent SHA without assuming it directly calls
 # this deferred callback: the invocation happens later through std::function.
 assert hashlib.sha256(parent).hexdigest()=='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
 cb=coff.compare_unit('card_text_callback_111')
 assert cb['result']=='exact' and cb['size']==111 and cb['matched_bytes']==111
 assert len(cb['relocations'])==5
 pmr=coff.compare_unit('card_text_capture_cstr_22')
 assert pmr['result']=='exact' and pmr['size']==22 and pmr['matched_bytes']==22
 assert len(pmr['relocations'])==1
 print('PASS immutable native Card callback 111B/42-i386, four real E8/one PE HIGHLOW')
 print('PASS real capture+4 std::pmr::string::c_str at 0x44BAF0, whole 22B/10 i386, original _Myptr E8')
 print('PASS native layer 0x00FFFFFF and full original 8B text-result/variadic member ABI')
 print('PASS canonical whole 111/111 callback plus relocated 22/22 PMR c_str (corrected original source owner)')
 print('The 578B ASCII text draw Boss and 1,896B Card start remain NONEXACT, no transitive credit')
if __name__=='__main__':verify()
