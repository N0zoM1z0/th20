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
 # The nested NativeCardTickCallback callable has its own constructor and
 # reset pair; independently pin both native bodies and their physical calls.
 tick_ctor=pe.raw_at(image,base,sections,0x00486740,102)
 assert hashlib.sha256(tick_ctor).hexdigest()==(
     '2c7a7d79d5795164ae1b3ee55227647727d114e8a809b9495307f0af3ecc2148')
 tick_ctor_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(tick_ctor,0x00486740))
 assert len(tick_ctor_ins)==32
 assert (tick_ctor_ins[-1].mnemonic,tick_ctor_ins[-1].op_str)==('ret','4')
 assert tick_ctor_ins[-1].address+tick_ctor_ins[-1].size==0x00486740+102
 assert calls(tick_ctor_ins,0x00486740)=={
     0x29:0x00413F80,0x39:0x0040B280,0x45:0x004869D0}
 ctor_data={p-0x00486740:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
            for p in reloc if 0x00486740<=p<0x00486740+102}
 assert ctor_data=={0x06:0x00567C8D,0x13:0x005B25C0}
 impl_ctor=pe.raw_at(image,base,sections,0x004866B0,53)
 assert hashlib.sha256(impl_ctor).hexdigest()==(
     '55cdae513205b64f52ba95b7e706a2209dff51e4cf13c5268e76d890dbbb7fdd')
 impl_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(impl_ctor,0x004866B0))
 assert len(impl_ins)==19
 assert (impl_ins[-1].mnemonic,impl_ins[-1].op_str)==('ret','4')
 assert impl_ins[-1].address+impl_ins[-1].size==0x004866B0+53
 assert calls(impl_ins,0x004866B0)=={0x0A:0x0040BDA0,0x1C:0x0040B280}
 impl_data={p-0x004866B0:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
            for p in reloc if 0x004866B0<=p<0x004866B0+53}
 assert impl_data=={0x14:0x0056FE28}
 tick_reset=pe.raw_at(image,base,sections,0x004869D0,90)
 assert hashlib.sha256(tick_reset).hexdigest()==(
     'f957d4564a030aaad49dd863e78969ee16a2f2343badc5e326dee9d725b59621')
 tick_reset_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(tick_reset,0x004869D0))
 assert len(tick_reset_ins)==34
 assert (tick_reset_ins[-1].mnemonic,tick_reset_ins[-1].op_str)==('ret','4')
 assert tick_reset_ins[-1].address+tick_reset_ins[-1].size==0x004869D0+90
 assert calls(tick_reset_ins,0x004869D0)=={
     0x0D:0x00413910,0x24:0x0040E700,0x33:0x0040B280,
     0x45:0x004866B0,0x4E:0x00414C60}
 assert not any(0x004869D0<=p<0x004869D0+90 for p in reloc)
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
 # Parent Card start 1,896B E8 into its independent text-task std::function
 # producer at +0x325; this deferred callback constructs a second, nested
 # std::function for the NativeCardTickCallback target.
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
 ctor=coff.compare_unit('card_tick_function_ctor_102')
 assert ctor['result']=='exact' and ctor['size']==102 and ctor['matched_bytes']==102
 assert len(ctor['relocations'])==5
 reset=coff.compare_unit('card_tick_function_reset_90')
 assert reset['result']=='exact' and reset['size']==90 and reset['matched_bytes']==90
 assert len(reset['relocations'])==5
 impl=coff.compare_unit('card_tick_func_impl_ctor_53')
 assert impl['result']=='exact' and impl['size']==53 and impl['matched_bytes']==53
 assert len(impl['relocations'])==3
 print('PASS immutable native Card callback 111B/42-i386, four real E8/one PE HIGHLOW')
 print('PASS nested 102B constructor SHA/call map: 3 E8 + 2 physical PE HIGHLOW; exact 5 relocation roles')
 print('PASS nested 90B _Reset SHA/call map: all five original E8 targets; no PE HIGHLOW')
 print('PASS real capture+4 std::pmr::string::c_str at 0x44BAF0, whole 22B/10 i386, original _Myptr E8')
 print('PASS nested NativeCardTickCallback std::function constructor 102/102, 82 ordinary bytes and five relocations')
 print('PASS nested _Reset 90/90, 70 ordinary bytes and five original E8 destinations')
 print('PASS 53B _Func_impl_no_alloc ctor, 41/41 ordinary bytes, two E8 and its original vtable HIGHLOW')
 print('PASS both nested callable boundaries preserve their out-of-line std::forward calls to 0x0040B280')
 print('The 578B ASCII text draw Boss and 1,896B Card start remain NONEXACT, no transitive credit')
if __name__=='__main__':verify()
