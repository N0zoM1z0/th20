#!/usr/bin/env python3
"""Immutable original Renderer 439B D3D9 surface blit: WHOLE strict exact.

Natural lifetime scope around the acquired surface recreates genuine
original post-flush compiler NOP without assembly, dead code or padding.
All native E8 and PE HIGHLOW are pinned independently from original PE.
"""
import hashlib,importlib.util,struct,sys,subprocess
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('surf439pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('surf439cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044BB10
SHA='27b31b093609d78ab184c3b2894a380b9180404e726fd64202d946651451e860'
CALLS={0x27:0x00414580,0x51:0x004455C0,0x6C:0x00414580,
       0x12F:0x0054069C,0x15D:0x00414580,0x1AC:0x005429EE}
HIGHLOW={0x07:0x005B25C0,0x120:0x005C4EE4}
SYM='?blit_surface_rect_44bb10@NativeRendererSurfaceBlitView@th20@@QAEXPBUNativeSurfaceBlitCommand@2@@Z'
def native_calls(instr,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in instr if i.size==5 and i.bytes[0]==0xe8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im)
 native=pe.raw_at(im,base,sec,HEAD,439)
 assert hashlib.sha256(native).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ins)==158 and ins[-1].address+ins[-1].size==HEAD+439
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert native_calls(ins,HEAD)==CALLS
 hl={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
     for x in pe.physical_highlow(im,base,sec) if HEAD<=x<HEAD+439}
 assert hl==HIGHLOW
 assert native[0x56]==0x90
 assert next(i for i in ins if i.address==HEAD+0x56).mnemonic=='nop'
 assert [k for k,v in CALLS.items() if v==0x00414580]==[0x27,0x6C,0x15D]
 obj=ROOT/'build/core1091-canonical/AnimationSurfaceBlit439.obj'
 symbols=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 assert SYM in symbols
 body,rel=cm.object_function(obj,SYM,439)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
 assert len(body)==439 and len(ci)==158 and len(rel)==8
 assert sum(x['type']=='REL32' for x in rel)==6
 assert sum(x['type']=='DIR32' for x in rel)==2
 assert all(x['addend']==0 for x in rel)
 assert body[0x56]==0x90
 assert next(i for i in ci if i.address==0x56).mnemonic=='nop'
 fields={**{k:('DIR32',v) for k,v in HIGHLOW.items()},
         **{k+1:('REL32',v) for k,v in CALLS.items()}}
 assert set(fields)=={r['offset'] for r in rel}
 for r in rel:
  assert r['type']==fields[r['offset']][0]
 comp=cm.compare(obj,SYM,HEAD,439)
 assert comp['result']=='structural-exact'
 assert comp['matched_comparable_bytes']==comp['comparable_bytes']==407
 for r in comp['relocations']:
  off=int(r['offset'],16)
  assert r['type']==fields[off][0]
  assert int(r['solved_destination'],16)==fields[off][1]
 result=cm.compare_unit('animation_renderer_surface_blit_439')
 assert result['result']=='exact' and result['size']==439 and result['matched_bytes']==439
 assert len(result['relocations'])==8
 print('PASS immutable original whole 439B/158-i386 game D3D9 texture surface blit, six E8 and two native PE HIGHLOW')
 print('PASS original 3 folded array-index E8, 192B draw-queue flush, native D3DXLoadSurfaceFromSurface and actual source surface global')
 print('PASS real scoped C++20 surface owner naturally emits original post-flush one-byte NOP at +0x56 and matching actual native branch displacement')
 print('PASS canonical WHOLE STRICT EXACT 439/439 native bytes, 407/407 ordinary bytes and all original eight original PE relocation field/target roles')
 print('PASS one additional whole native game-authored head/439 bytes; folded 22B array index and 192B flush not recredited')
if __name__=='__main__':verify()
