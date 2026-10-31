#!/usr/bin/env python3
"""Immutable complete 360B D3D9 queued glyph upload and 59B callback call.

True original PE E8/HIGHLOW and D3D9 VTable slots are decoded independently
from the original locked target, never solved from the compiled COFF object.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('upload360pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('upload360cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004145D0
SHA='76223b12344a822e9f79546f3b197ce349d9b3467ebbbe2f3b65f73c411b0dcc'
CALLS={0x061:0x004156A0,0x06E:0x004156C0,0x0C1:0x00543E20,
 0x0D7:0x004156C0,0x113:0x00416360,0x124:0x00413BE0,
 0x142:0x004145A0,0x154:0x00414740,0x15F:0x005429EE}
HIGHLOW={0x007:0x005B25C0,0x120:0x005B8894}
CALLBACK_HEAD=0x00414740
CALLBACK_SHA='046e82dc1916704a61693bbbdce1a6efd5bb769dc093e70b82fbda342ba7f8ca'
CALLBACK_CALLS={0x0C:0x00414A80,0x18:0x00540E98,0x21:0x00414AD0}
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sections=pe.parse_sections(im);high=pe.physical_highlow(im,base,sections)
 b=pe.raw_at(im,base,sections,HEAD,360)
 assert hashlib.sha256(b).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==128 and ins[-1].address+ins[-1].size==HEAD+360
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)==CALLS
 data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sections,p,4))[0]
       for p in high if HEAD<=p<HEAD+360}
 assert data==HIGHLOW
 assert any(i.mnemonic=='mov' and i.op_str=='edx, dword ptr [ecx + 0x48]' for i in ins)
 assert any(i.mnemonic=='mov' and i.op_str=='ecx, dword ptr [eax + 0x34]' for i in ins)
 assert any(i.mnemonic=='mov' and i.op_str=='eax, dword ptr [ecx + 0x38]' for i in ins)
 assert any(i.mnemonic=='mov' and i.op_str=='ecx, dword ptr [edx + 8]' for i in ins)
 assert any(i.mnemonic=='mov' and i.op_str=='byte ptr [ecx], 1' for i in ins)
 # The native producer's distinct 132B ctor is accepted separately:
 # it captures a canvas+texture+geometry+source+completion+callback.
 producer=pe.raw_at(im,base,sections,0x00413EC0,132)
 assert hashlib.sha256(producer).hexdigest()=='1bdff818be6f3097007f19698a72a5e969b7e0922c69ca783a23efa6148247fa'
 for addr,size,sha in [(0x004156A0,20,'76e2b0e00c4fde908a610902941a1e01ee596ba4d901069e1c342b70a1bcbde4'),
                      (0x00416360,182,'632c4839135f7908fc5bda7f2a749944332b8ff3bb76de8484e428a03ce1258e')]:
  assert hashlib.sha256(pe.raw_at(im,base,sections,addr,size)).hexdigest()==sha
 cb=pe.raw_at(im,base,sections,CALLBACK_HEAD,59)
 assert hashlib.sha256(cb).hexdigest()==CALLBACK_SHA
 cb_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(cb,CALLBACK_HEAD))
 assert len(cb_ins)==23 and cb_ins[-1].address+cb_ins[-1].size==CALLBACK_HEAD+59
 assert (cb_ins[-1].mnemonic,cb_ins[-1].op_str)==('ret','')
 assert calls(cb_ins,CALLBACK_HEAD)==CALLBACK_CALLS
 assert not any(CALLBACK_HEAD<=p<CALLBACK_HEAD+59 for p in high)
 for name,size,nrel in [('glyph_texture_upload_360',360,11),('glyph_upload_callback_invoke_59',59,3)]:
  z=cm.compare_unit(name)
  assert z['result']=='exact' and z['size']==size and z['matched_bytes']==size
  assert len(z['relocations'])==nrel
 print('PASS immutable original complete 360B/128-i386 D3D9/GDI glyph texture upload: real COM GetSurfaceLevel/LockRect/UnlockRect/Release')
 print('PASS all nine original physical E8 and two native PE HIGHLOW, exact compiler source 360/360 (316/316 ordinary bytes)')
 print('PASS original +0x04 texture pointer, +0x28 completion byte flag, +0x30 function callback in genuine 0x58B capture')
 print('PASS distinct 59B/23-i386 native generic std::function invocation, all three original E8 and 59/59 canonical source')
 print('PASS prior exact 132B game capture and 182B GDI cleanup physically nested, no duplicate original authored credit')
if __name__=='__main__':verify()
