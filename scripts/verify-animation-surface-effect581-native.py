#!/usr/bin/env python3
"""Whole immutable original Renderer 581B surface-copy/pulse effect Boss.

Natural C++20 source emits 580B/200 i386 with exactly one missing
original flush-boundary NOP. Mask-only diagnostics are NEVER exact credit.
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
 obj=ROOT/'build/core1088-probes/AnimationSurfaceEffect581.obj'
 syms=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 assert SYM in syms
 candidate,rel=cm.object_function(obj,SYM,580)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(candidate,0))
 assert len(candidate)==580 and len(ci)==200 and len(rel)==13
 assert sum(x['type']=='REL32' for x in rel)==9
 assert sum(x['type']=='DIR32' for x in rel)==4
 assert all(x['addend']==0 for x in rel)
 # Compare original full 581B read, then omit ONE real NOP for a
 # deliberately noncanonical compiler-difference diagnostic only.
 normalized=bytearray(raw);del normalized[0x48]
 generated=bytearray(candidate)
 sites={**{k:('DIR32',v) for k,v in DATA.items()},
        **{k+1:('REL32',v) for k,v in CALLS.items()}}
 assert len(sites)==len(rel)==13
 for r in rel:
  off=r['offset'];orig_off=off+(off>=0x48)
  assert orig_off in sites,(off,orig_off)
  assert r['type']==sites[orig_off][0]
  generated[off:off+4]=normalized[off:off+4]=b'\0'*4
 diff=[x for x in range(580) if normalized[x]!=generated[x]]
 assert diff==[0x3C],diff
 assert generated[0x3C]==0xF2 and normalized[0x3C]==0xF3
 # These are earlier independently accepted complete functions. Their
 # original physical PE SHA is enough here: their canonical providers
 # are unchanged, and forcing a cold recompile would expand the scope.
 for head,size,sha in [
      (0x00425CC0,23,'fa052edde7f97f93d22de573e59ac5de5a972ba6e485c81dbddcdc8bdab58180'),
      (0x00449D20,92,'4c9c514de33a85505908e34b68c1e966f231132bcf66364d1858d38ee76cb860')]:
  assert hashlib.sha256(pe.raw_at(image,base,sec,head,size)).hexdigest()==sha
 print('PASS original whole 581B/201-i386 Renderer D3D9 surface effect, nine physical E8 and four native PE HIGHLOW')
 print('PASS native 42-file array lookup, real Draw flush, D3DXLoadSurfaceFromSurface, LockRect/UnlockRect/Release and signed channel arithmetic')
 print('PASS three original separate random_byte_449d20 calls, all bound to actual global 0x005BA4C4 and existing whole-exact 92B native pulse')
 print('PASS natural 580B/200-i386 C++ source: nine REL32/four DIR32, genuine signed /0x300 and /0x500 divisions, actual image pixel/stride handling')
 print('NONEXACT: native one genuine +0x48 NOP after flush; diagnostic-only 579/580 equal ordinary bytes after omission, plus changed jump distance 0xF3 vs 0xF2')
 print('No whole-original 581B strict unit or game exact code credit; no fake padding/inert locals/target edits')
if __name__=='__main__':verify()
