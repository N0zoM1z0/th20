#!/usr/bin/env python3
"""Whole locked TH20 269B game Renderer AnimationFile preloader native proof.

Verify original native slot<42 guard, lock17 lifetime, actual 67B
AnimationFile allocation/34B array::at, independently exact 1022B
file loading and 97B release error branch; all PE E8/HIGHLOW roles.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('anmprepe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('anmprecm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044ED40
SHA='a802bfc6ec01c915d6c382ed0d6ed9c6098f5865507900690495871f8a50cb7d'
CALLS={0x34:0x0040C6B0,0x4C:0x00454230,0x62:0x0040C310,
 0x6B:0x0040B730,0x82:0x004477B0,0x9D:0x0043EB10,
 0xBF:0x0040B900,0xCC:0x0044A700,0xDF:0x004473A0,0x102:0x005429EE}
DATA={0x06:0x005676ED,0x15:0x005B25C0,0x30:0x0056E378,
 0x43:0x0056E38C,0x48:0x005C0678,0x5E:0x005C0240,
 0x78:0x0056E3B0,0x7E:0x005B8894,0xDB:0x005B8894}
SYM='?preload_anm_44ed40@NativeRendererAnmPreloadView@th20@@QAEPAUNativeAnimationFileLoadView@2@IPBD@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 b=pe.raw_at(im,base,sec,HEAD,269)
 assert hashlib.sha256(b).hexdigest()==SHA
 inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(inst)==79 and inst[-1].address+inst[-1].size==HEAD+269
 assert (inst[-1].mnemonic,inst[-1].op_str)==('ret','8')
 assert calls(inst,HEAD)==CALLS
 high={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
       for p in hl if HEAD<=p<HEAD+269}
 assert high==DATA
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp + 8], 0x2a' for i in inst)
 assert any(i.mnemonic=='push' and i.op_str=='0x11' for i in inst)
 assert calls(inst,HEAD)[0x9D]==0x0043EB10
 assert high[0x7E]==high[0xDB]==0x005B8894
 assert calls(inst,HEAD)[0xCC]==0x0044A700
 assert calls(inst,HEAD)[0xDF]==0x004473A0
 for orighead,n,sha in [
   (0x0044A700,1022,'b750b3b8810f442dfe717b1c4b49eabad84423ed2771efa794c28c0321273021'),
   (0x004477B0,67,'c96a602aad1857a4831183cf380a6d977b55cce8ee800cdf4be31bd0f42673c0'),
   (0x0043EB10,34,'eaa83e9ae14a702132668b9e75d6e3b2bc17ea5450698a20449327a620a67cf2'),
   (0x004473A0,97,'82befc5d4ed5d51076f2eefcb6923d4ae81452176adafcb65f0cf3af27a09b38')]:
  assert hashlib.sha256(pe.raw_at(im,base,sec,orighead,n)).hexdigest()==sha
 assert pe.raw_at(im,base,sec,0x0056E378,19).startswith(b'::preloadAnim')
 assert pe.raw_at(im,base,sec,0x0056E3B0,68).startswith(b'D:\\cygwin')
 obj=ROOT/'build/core1097-canonical/AnimationFilePreload269.obj'
 cmp=cm.compare(obj,SYM,HEAD,269)
 assert cmp['result']=='structural-exact'
 assert cmp['matched_comparable_bytes']==cmp['comparable_bytes']==193
 roles={**{k:('DIR32',v) for k,v in DATA.items()},
        **{k+1:('REL32',v) for k,v in CALLS.items()}}
 assert len(cmp['relocations'])==len(roles)==19
 for r in cmp['relocations']:
  off=int(r['offset'],16)
  assert off in roles and r['type']==roles[off][0]
  assert int(r['solved_destination'],16)==roles[off][1]
 unit=cm.compare_unit('animation_file_preload_269')
 assert unit['result']=='exact' and unit['size']==269 and unit['matched_bytes']==269
 assert len(unit['relocations'])==19
 print('PASS original whole game 269B/79-i386 AnimationFile slot preload, ten original E8 and nine physical PE HIGHLOW')
 print('PASS signed slot bound 42, original lock slot17, real 67B allocate_object<AnimationFile> and 34B checked table at Renderer+0x6000730')
 print('PASS unlock precedes exact 1022B loader; original unsuccessful load calls true 97B release_object then returns separate nullptr')
 print('PASS canonical original 269/269 native x86, 193/193 ordinary bytes, 19 independent original reloc site/type/destination pairs')
 print('One new authored-game original 269B function; existing allocator, checked-array, logger and 1022B loader are not recredited')
if __name__=='__main__':verify()
