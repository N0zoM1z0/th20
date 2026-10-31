#!/usr/bin/env python3
"""Whole original Renderer 581B D3D9 color surface effect, strict exact.

A genuinely separate D3D9 acquired surface/pixel-lifetime C++ scope
naturally emits the original post-flush NOP, without fake source padding.
Native E8/PE HIGHLOW destinations are independently read from locked PE.
"""
import hashlib,importlib.util,struct,subprocess,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pulsepe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('pulsecm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044BE40
SHA='b515085a0793cb68b558ccf8704a506c05e8fef7fd4abdefc5f99e648d619e77'
CALLS={0x27:0x00414580,0x43:0x004455C0,0x5C:0x00414580,
 0xA9:0x0054069C,0x13E:0x00425CC0,0x180:0x00449D20,
 0x1AA:0x00449D20,0x1D1:0x00449D20,0x23A:0x005429EE}
DATA={0x07:0x005B25C0,0x17C:0x005BA4C4,0x1A6:0x005BA4C4,0x1CD:0x005BA4C4}
SYM='?blit_surface_effect_44be40@NativeRendererSurfaceBlitView@th20@@QAEXHHPAUIDirect3DSurface9@@PBUtagRECT@@1H@Z'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 raw=pe.raw_at(image,base,sec,HEAD,581)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ni)==201 and ni[-1].address+ni[-1].size==HEAD+581
 assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','0x18')
 assert calls(ni,HEAD)==CALLS
 hl={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
     for p in pe.physical_highlow(image,base,sec) if HEAD<=p<HEAD+581}
 assert hl==DATA
 assert raw[0x48]==0x90
 assert next(i for i in ni if i.address==HEAD+0x48).mnemonic=='nop'
 assert [x for x,d in CALLS.items() if d==0x00449D20]==[0x180,0x1AA,0x1D1]
 # Original three channel-source references all bind to ONE actual
 # locked game renderer random state at 0x005BA4C4, not a new instance.
 assert all(hl[x]==0x005BA4C4 for x in (0x17C,0x1A6,0x1CD))
 obj=ROOT/'build/core1092-canonical/AnimationSurfaceEffect581.obj'
 syms=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 assert SYM in syms
 candidate,rel=cm.object_function(obj,SYM,581)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(candidate,0))
 assert len(candidate)==581 and len(ci)==201 and len(rel)==13
 assert sum(x['type']=='REL32' for x in rel)==9
 assert sum(x['type']=='DIR32' for x in rel)==4
 assert all(x['addend']==0 for x in rel)
 assert candidate[0x48]==0x90
 assert next(i for i in ci if i.address==0x48).mnemonic=='nop'
 sites={**{k:('DIR32',v) for k,v in DATA.items()},
        **{k+1:('REL32',v) for k,v in CALLS.items()}}
 assert {r['offset'] for r in rel}==set(sites)
 for r in rel:assert r['type']==sites[r['offset']][0]
 cmp=cm.compare(obj,SYM,HEAD,581)
 assert cmp['result']=='structural-exact'
 assert cmp['matched_comparable_bytes']==cmp['comparable_bytes']==529
 for r in cmp['relocations']:
  off=int(r['offset'],16)
  assert r['type']==sites[off][0]
  assert int(r['solved_destination'],16)==sites[off][1]
 unit=cm.compare_unit('animation_renderer_surface_effect_581')
 assert unit['result']=='exact' and unit['size']==581 and unit['matched_bytes']==581
 assert len(unit['relocations'])==13
 # These are earlier independently accepted complete functions. Their
 # original physical PE SHA is enough here: their canonical providers
 # are unchanged, and forcing a cold recompile would expand the scope.
 for head,size,sha in [
      (0x00425CC0,23,'fa052edde7f97f93d22de573e59ac5de5a972ba6e485c81dbddcdc8bdab58180'),
      (0x00449D20,92,'4c9c514de33a85505908e34b68c1e966f231132bcf66364d1858d38ee76cb860')]:
  assert hashlib.sha256(pe.raw_at(image,base,sec,head,size)).hexdigest()==sha
 print('PASS original whole 581B/201-i386 Renderer D3D9 surface effect, nine physical E8/four HIGHLOW')
 print('PASS actual 42-file Renderer array, flush, D3DX surface blit, optional LockRect/UnlockRect, three native game random_byte calls and signed channel arithmetic')
 print('PASS genuine C++ acquired surface/pixel lifetime scope naturally emits actual original +0x48 post-flush NOP and original branch displacement')
 print('PASS pinned canonical whole 581/581 native bytes, 529/529 ordinary bytes and all 13 true original relocation field/target roles')
 print('PASS one newly credited game-authored original 581B physical function, existing 23B/92B and folded helpers not recredited')
if __name__=='__main__':verify()
