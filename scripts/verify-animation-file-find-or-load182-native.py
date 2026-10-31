#!/usr/bin/env python3
"""Whole immutable 182B game Renderer AnimationFile find/preload/wait proof.

Real original atomic bool vs integer-load ABI; no invented source or
reforged native E8/HIGHLOW data. Check whole canonical C++ body.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('findpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('findcm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044EB30
SHA='559e1e2c9c7e103c8f856e127908eb1b10b4929f2a25ac714b1d8089b5d276fe'
E8={0x10:0x00437970,0x22:0x0040C6B0,0x31:0x00437970,
    0x43:0x0044ED40,0x5D:0x004493C0,0x69:0x004292C0,0xA5:0x0040C6B0}
HL={0x1E:0x0056E3F4,0x85:0x005C5888,0x95:0x0056C16C,0xA1:0x0056E410}
SYM='?find_or_load_file_44eb30@NativeRendererAnmFindOrLoadView@th20@@QAEPAVAnimationFile@2@HPBD@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);hls=pe.physical_highlow(image,base,sec)
 raw=pe.raw_at(image,base,sec,HEAD,182)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==64 and ins[-1].address+ins[-1].size==HEAD+182
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 assert calls(ins,HEAD)==E8
 high={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
       for p in hls if HEAD<=p<HEAD+182}
 assert high==HL
 assert any(x.address==HEAD+0x62 and x.mnemonic=='nop' for x in ins)
 assert any(x.address==HEAD+0x99 and x.mnemonic=='nop' for x in ins)
 assert [E8[p] for p in (0x10,0x31)]==[0x00437970]*2
 assert [E8[p] for p in (0x5D,0x69)]==[0x004493C0,0x004292C0]
 assert pe.raw_at(image,base,sec,0x0056E3F4,27).startswith(b'::preloadAnim already : %s')
 assert pe.raw_at(image,base,sec,0x0056E410,26).startswith(b'::preloadAnimEnd : %s')
 for addr,n,sha in [
  (0x00437970,40,'8b9fce492db39f692e526a4181a320e25860bcf30fed6c69430d98f68ff2a3f9'),
  (0x0044ED40,269,'a802bfc6ec01c915d6c382ed0d6ed9c6098f5865507900690495871f8a50cb7d'),
  (0x004493C0,28,'92b9ef8a164060015ffd17d7e4fd8dc3b4e51cb2035abcc33df7051c195705c7'),
  (0x004292C0,21,'c0826eff4a5d0e01f268b19ea363af174e4165357bef14133664b1cf291bd715')]:
  assert hashlib.sha256(pe.raw_at(image,base,sec,addr,n)).hexdigest()==sha,hex(addr)
 # The original 28B atomic assignment wrapper forwards to 0x0040C550,
 # and the different 21B bool conversion forwards to 0x0040C420.
 assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sec,0x004493C0,28),0x004493C0)),0x004493C0)=={0x0E:0x0040C550}
 assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sec,0x004292C0,21),0x004292C0)),0x004292C0)=={0x0C:0x0040C420}
 obj=ROOT/'build/core1098-canonical/AnimationFileFindOrLoad182.obj'
 z=cm.compare(obj,SYM,HEAD,182)
 assert z['result']=='structural-exact'
 assert z['matched_comparable_bytes']==z['comparable_bytes']==138
 roles={**{k:('DIR32',v) for k,v in HL.items()},**{k+1:('REL32',v) for k,v in E8.items()}}
 assert len(z['relocations'])==len(roles)==11
 for r in z['relocations']:
  k=int(r['offset'],16)
  assert k in roles and r['type']==roles[k][0]
  assert int(r['solved_destination'],16)==roles[k][1]
 result=cm.compare_unit('animation_file_find_or_load_182')
 assert result['result']=='exact' and result['size']==182 and result['matched_bytes']==182
 assert len(result['relocations'])==11
 print('PASS original 182B/64-i386 Renderer AnimationFile find/preload/poll whole game Boss, seven native E8/four PE HIGHLOW')
 print('PASS two original calls to exact 40B Renderer file_by_index, distinct exact 269B preload and two genuine atomic<uint32_t> wrapper heads')
 print('PASS native atomic bool conversion not integer load, original shared mode global at 0x005C5888 and Sleep(1) IAT 0x0056C16C, original NOPs and logs')
 print('PASS source entire 182/182 native, 138/138 ordinary bytes, all 11 independent original relocated sites and physical destinations')
 print('PASS 1 newly authored game head/182 bytes; existing 40B/269B game and 28B/21B generic wrappers not credited twice')
if __name__=='__main__':verify()
