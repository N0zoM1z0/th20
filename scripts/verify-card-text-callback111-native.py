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
 # The concrete erased-target vtable has six original slots. Verify the
 # whole vtable head and each independent native virtual body/relocation.
 vtable=pe.raw_at(image,base,sections,0x0056FE28,24)
 assert struct.unpack('<6I',vtable)==(
     0x004883C0,0x00488480,0x00488440,0x004884F0,0x0044B3A0,0x0044B530)
 expected_virtuals=(
  ('card_tick_func_impl_copy_47',0x004883C0,47,'e00d24e1e4773ab228db23db6e8e80457cf0c64213512578cfeebf2a82ffa78c',2),
  ('card_tick_func_impl_move_104',0x00488480,104,'e17bc087b575ad4da5f566e5ebeb0d8b058f805f2b0dc90496458a325bf6fff8',5),
  ('card_tick_func_impl_do_call_26',0x00488440,26,'f20885c9887766b859475ed7d670a869fbc7dac77ce0e322c27e1866134d3e02',1),
  ('card_tick_func_impl_target_type_16',0x004884F0,16,'ee15f6d9711662c243b2d5e787183414ae7096b951b48c0d8dc1408ca250eddf',1),
  ('card_tick_func_impl_get_26',0x0044B530,26,'2fe2dbee16fa0248d334c545b664f30233f7ef1f467861c20b928e83d2d9ced8',1),
  ('card_tick_func_impl_delete_35',0x0044B3A0,35,'eb6ab290916efc9e256d8cf1de0a7cdd52c0dd35c7ba54cf0829a0b464cf7c3c',1),
  ('card_tick_invoke_14',0x00486AD0,14,'f83c1bf135f1c4f150d0515e498a110cb158a5c9ced72fc3c1c5a7ae1ebd8346',1),
 )
 for unit_name,address,body_size,digest,reloc_count in expected_virtuals:
  body=pe.raw_at(image,base,sections,address,body_size)
  assert hashlib.sha256(body).hexdigest()==digest
  report=coff.compare_unit(unit_name)
  assert report['result']=='exact' and report['size']==body_size
  assert report['matched_bytes']==body_size and len(report['relocations'])==reloc_count
 # _Move's source-generated 109B COFF contribution is the true 104B body
 # followed by five compiler INT3 bytes. The native adjacent span has the
 # same five alignment bytes; coverage credit remains exactly 104B.
 move_unit=coff.compare_unit('card_tick_func_impl_move_104')
 assert move_unit['compared_size']==109 and move_unit['matched_compared_bytes']==109
 assert pe.raw_at(image,base,sections,0x00488480+104,5)==b'\xCC'*5
 assert pe.raw_at(image,base,sections,0x00488480,109)[104:]==b'\xCC'*5
 invoke_body=pe.raw_at(image,base,sections,0x00486AD0,14)
 invoke_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(invoke_body,0x00486AD0))
 assert calls(invoke_ins,0x00486AD0)=={0x06:0x00486E50}
 print('PASS immutable native Card callback 111B/42-i386, four real E8/one PE HIGHLOW')
 print('PASS nested 102B constructor SHA/call map: 3 E8 + 2 physical PE HIGHLOW; exact 5 relocation roles')
 print('PASS nested 90B _Reset SHA/call map: all five original E8 targets; no PE HIGHLOW')
 print('PASS real capture+4 std::pmr::string::c_str at 0x44BAF0, whole 22B/10 i386, original _Myptr E8')
 print('PASS nested NativeCardTickCallback std::function constructor 102/102, 82 ordinary bytes and five relocations')
 print('PASS nested _Reset 90/90, 70 ordinary bytes and five original E8 destinations')
 print('PASS 53B _Func_impl_no_alloc ctor, 41/41 ordinary bytes, two E8 and its original vtable HIGHLOW')
 print('PASS all six original erased-target vtable virtuals: Copy, Move, Do_call, Target_type, Delete_this, Get')
 print('PASS 104B _Move body + 5 native/compiler INT3 alignment bytes, 109/109 compare; 104B coverage')
 print('PASS 14B std::invoke bridge calls the distinct original 34B NativeCardTickCallback operator()')
 print('PASS both nested callable boundaries preserve their out-of-line std::forward calls to 0x0040B280')
 print('The 578B ASCII text draw Boss and 1,896B Card start remain NONEXACT, no transitive credit')
if __name__=='__main__':verify()
