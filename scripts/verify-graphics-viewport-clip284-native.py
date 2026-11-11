#!/usr/bin/env python3
"""Full original 284B Graphics viewport/clip switch, native strict source proof."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 spec=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
cf=load('viewport284_cf','scripts/compare-coff-function.py')
pe=load('viewport284_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x0041DCE0
SIZE=284
SHA='84fc878beeb6de276535c36c79312e1be8f1d574305fe2c749ba55d90afbd857'
SYM='?set_clip_41dce0@NativeGraphicsModeAction@th20@@QAEXH@Z'
def main():
 exe=cf.verified_target();base,secs=pe.parse_sections(exe)
 native=pe.raw_at(exe,base,secs,HEAD,SIZE)
 assert hashlib.sha256(native).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ins)==67 and ins[-1].address+ins[-1].size==HEAD+SIZE
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(exe,base,secs,p,4))[0]
       for p in pe.physical_highlow(exe,base,secs) if HEAD<=p<HEAD+SIZE}
 assert calls=={0x40:0x004DA1F0,0x52:0x004DA120}
 assert data=={0x9A:0x005C0028,0xB8:0x005C0028,0xD6:0x005C0028,0xF8:0x005C0028}
 assert any(i.address-HEAD==0x0D2 and i.mnemonic=='shl' and 'eax, 1' in i.op_str for i in ins)
 assert any(i.address-HEAD==0x10C and i.mnemonic=='mov' and '0xb04' in i.op_str for i in ins)
 src,rel=cf.object_function(R/'build/core1139-canonical/GraphicsViewportClip284.obj',SYM,SIZE)
 assert len(src)==SIZE and len(rel)==6
 assert [x['offset']-1 for x in rel if x['type']=='REL32']==list(calls)
 assert [x['offset'] for x in rel if x['type']=='DIR32']==list(data)
 mask={j for x in rel for j in range(x['offset'],x['offset']+4)}
 assert len(mask)==24 and all(a==z for i,(a,z) in enumerate(zip(native,src)) if i not in mask)
 for unit,n in [('graphics_viewport_clip_284',284),('animation_graphics_viewport_switch_280',280)]:
  p=cf.compare_unit(unit)
  assert p['result']=='exact' and p['matched_bytes']==n,unit
 print('PASS original 284B/67-i386 Graphics clip viewport SHA and all 2 E8 /4 PE HIGHLOW original physical fields')
 print('PASS complete source 284/284B strict exact, 260/260 ordinary bytes, real viewport+0xE0 and third point coordinates')
 print('PASS original distinct 280B mode-switch sibling remains exactly matched without duplicate credit')
if __name__=='__main__':main()
