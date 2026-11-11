#!/usr/bin/env python3
"""Whole original 88B game screenshot queue versus complete pinned MSVC source."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 s=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('window_pending88_cf','scripts/compare-coff-function.py')
pe=load('window_pending88_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x0041BFC0
SIZE=88
SHA='28b4d96cdaad162015839d6d31defaf58be14a5b964128fb603fd78617baa468'
SYM='?prepare_frame_41bfc0@NativeWindowCaptureRenderer@th20@@QAEXXZ'
BLIT='?blit_surface_rect_44bb10@NativeRendererSurfaceBlitView@th20@@QAEXPBUNativeSurfaceBlitCommand@2@@Z'
def main():
 original_image=cf.verified_target()
 base,sections=pe.parse_sections(original_image)
 orig=pe.raw_at(original_image,base,sections,HEAD,SIZE)
 assert hashlib.sha256(orig).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(orig,HEAD))
 assert len(ins)==28 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert [(i.address-HEAD,i.address+5+struct.unpack_from('<i',i.bytes,1)[0])
         for i in ins if i.size==5 and i.bytes[0]==0xe8]==[(0x3E,0x0044BB10)]
 assert not any(HEAD<=p<HEAD+SIZE for p in pe.physical_highlow(original_image,base,sections))
 assert any(i.mnemonic=='imul' and '0x28' in i.op_str for i in ins)
 assert any(i.mnemonic=='cmp' and '0x18' in i.op_str for i in ins)
 obj=R/'build/core1132-canonical/WindowCapturePending88.obj'
 source,rel=cf.object_function(obj,SYM,SIZE)
 assert len(source)==SIZE and len(rel)==1
 assert rel==[{'offset':0x3F,'type_id':20,'type':'REL32','symbol':BLIT,'addend':0}]
 assert bytes(source[:0x3F])+bytes(source[0x43:])==orig[:0x3F]+orig[0x43:]
 proof=cf.compare_unit('window_capture_pending_88')
 assert proof['result']=='exact' and proof['matched_bytes']==SIZE
 blit=cf.compare_unit('animation_renderer_surface_blit_439')
 assert blit['result']=='exact' and blit['matched_bytes']==439
 print('PASS original complete 88B/28-i386 SHA, four real 40B pending records at +0x18')
 print('PASS entire canonical 88/88B source exact, 84/84 original ordinary bytes and single E8 operand at +0x3F to 0x0044BB10')
 print('PASS independently accepted 439B Renderer blit callee preserved (no duplicate exact game credit)')
if __name__=='__main__':main()
