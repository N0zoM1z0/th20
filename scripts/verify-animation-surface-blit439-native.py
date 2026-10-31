#!/usr/bin/env python3
"""Immutable original Renderer 439B D3D9 surface blit vs real 438B C++ source.

The one-byte native NOP after flush_draws() is real original code; the
C++ source is NONEXACT. Diagnostic byte normalization does NOT grant credit.
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
 obj=ROOT/'build/core1086-probes/AnimationSurfaceBlit439.obj'
 symbols=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 assert SYM in symbols
 b,rel=cm.object_function(obj,SYM,438)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,0))
 assert len(b)==438 and len(ci)==157 and len(rel)==8
 assert sum(x['type']=='REL32' for x in rel)==6
 assert sum(x['type']=='DIR32' for x in rel)==2
 assert all(x['addend']==0 for x in rel)
 # For diagnosis only: omit exactly one attested genuine native NOP.
 # Mask each independently established original native PE relocation
 # and corresponding COFF relocation field using original positions.
 physical=bytearray(native);del physical[0x56]
 natural=bytearray(b)
 native_fields={**{k:('DIR32',v) for k,v in HIGHLOW.items()},
                **{k+1:('REL32',v) for k,v in CALLS.items()}}
 assert len(native_fields)==len(rel)==8
 for x in rel:
  off=x['offset'];old_off=off+(off>=0x56)
  assert old_off in native_fields,(off,old_off)
  kind,dst=native_fields[old_off]
  assert x['type']==kind
  natural[off:off+4]=physical[off:off+4]=b'\0'*4
 diffs=[x for x in range(438) if natural[x]!=physical[x]]
 assert diffs==[0x4A],diffs
 assert natural[0x4A]==0x58 and physical[0x4A]==0x59
 print('PASS immutable original whole 439B/158-i386 game Renderer D3D9 surface blit, 6 real native E8/2 PE HIGHLOW')
 print('PASS original 3 folded array-index E8, 192B draw-queue flush, native D3DXLoadSurfaceFromSurface and source-surface original 0x005C4EE4')
 print('PASS natural 438B/157-i386 real D3D9 source, 6 REL32/2 DIR32, correct GetSurfaceLevel/AddDirtyRect/Release and native RECT geometry')
 print('NONEXACT: original has one genuine +0x56 NOP after flush; after diagnostic-only removal, 437/438 native ordinary code bytes match except one jump displacement 0x59 vs 0x58')
 print('No shortened canonical unit or game-authored exact credit; original must remain complete 439B')
if __name__=='__main__':verify()
