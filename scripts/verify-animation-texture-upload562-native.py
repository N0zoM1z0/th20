#!/usr/bin/env python3
"""Whole immutable original 562B Renderer texture-file-memory D3D9 upload.

Compare native full physical function, all six E8, thirteen original PE
HIGHLOW, true COM/D3DX call graph and original 2745B finalizer edge.
The 2745B native finalizer is NOT declared exact by this source.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('up562pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('up562cm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044E8F0
SHA='1b0d6d08d535765761f1cfaf5f9140a7e0963f0b04b00daae23cac98cb182a19'
CALLS={0x17:0x0044CFB0,0x10A:0x00412730,0x12C:0x005406A2,0x1AE:0x00540696,0x1FB:0x00451910,0x227:0x005429EE}
DATA={0x07:0x005B25C0,0x99:0x0056C8D0,0xA0:0x005B8818,0xAF:0x005B8818,0xB7:0x0056E0EC,
 0xCB:0x005B8818,0xD3:0x0056E0EC,0xFE:0x0056E208,0x106:0x005C4D40,
 0x16D:0x0056C8D0,0x174:0x005B8818,0x209:0x0056E22C,0x21E:0x0056E22C}
SYM='?create_uploaded_texture_44e8f0@NativeRendererTextureMemoryView@th20@@QAEHPAUTextureRecord@2@HHHHHHHH@Z'
def calls(instr,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in instr if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 b=pe.raw_at(im,base,sec,HEAD,562)
 assert hashlib.sha256(b).hexdigest()==SHA
 instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(instr)==177 and instr[-1].address+instr[-1].size==HEAD+562
 assert (instr[-1].mnemonic,instr[-1].op_str)==('ret','0x24')
 assert calls(instr,HEAD)==CALLS
 high={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
       for p in hl if HEAD<=p<HEAD+562}
 assert high==DATA
 # Actual native D3DX CreateTexture/LoadSurfaceFromFileInMemory IATs,
 # rather than a non-native hand-authored equivalent COM CreateTexture.
 assert calls(instr,HEAD)[0x12C]==0x005406A2
 assert calls(instr,HEAD)[0x1AE]==0x00540696
 assert calls(instr,HEAD)[0x1FB]==0x00451910
 assert [high[x] for x in (0xA0,0xAF,0xCB,0x174)]==[0x005B8818]*4
 assert high[0xFE]==0x0056E208
 assert high[0x209]==high[0x21E]==0x0056E22C
 # Lock actual immutable D3D format and texture-byte-size tables, not
 # merely the relocation positions. The real source uses precisely
 # one unknown format then eight D3DFMT_A8R8G8B8 (21), all 4B texels.
 assert struct.unpack('<9I',pe.raw_at(im,base,sec,0x0056E208,36))==(0,21,21,21,21,21,21,21,21)
 assert struct.unpack('<9I',pe.raw_at(im,base,sec,0x0056E22C,36))==(4,)*9
 assert struct.unpack('<f',pe.raw_at(im,base,sec,0x0056C8D0,4))[0]==2.0
 assert struct.unpack('<f',pe.raw_at(im,base,sec,0x0056E0EC,4))[0]==0.5
 assert any(i.mnemonic=='mov' and i.op_str=='dword ptr [ebp - 0x34], 0x30004' for i in instr)
 assert any(i.mnemonic=='mov' and i.op_str=='dword ptr [ebp - 0x34], 1' for i in instr)
 assert any(i.mnemonic=='nop' and i.address-HEAD==0x15A for i in instr)
 assert any(i.mnemonic=='ret' and i.op_str=='0x24' for i in instr)
 original_finalizer=pe.raw_at(im,base,sec,0x00451910,2745)
 assert len(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original_finalizer,0x00451910)))>500
 obj=ROOT/'build/core1100-canonical/AnimationFileTextureLoad562.obj'
 cmp=cm.compare(obj,SYM,HEAD,562)
 assert cmp['result']=='structural-exact' and cmp['matched_comparable_bytes']==cmp['comparable_bytes']==486
 roles={**{k:('DIR32',v) for k,v in DATA.items()},**{k+1:('REL32',v) for k,v in CALLS.items()}}
 assert len(cmp['relocations'])==len(roles)==19
 for r in cmp['relocations']:
  off=int(r['offset'],16)
  assert off in roles and r['type']==roles[off][0]
  assert int(r['solved_destination'],16)==roles[off][1]
 unit=cm.compare_unit('animation_texture_upload_from_memory_562')
 assert unit['result']=='exact' and unit['size']==562 and unit['matched_bytes']==562
 assert len(unit['relocations'])==19
 print('PASS immutable original game D3D9 texture-memory upload 562B/177 i386, all six native E8/thirteen real PE HIGHLOW')
 print('PASS real native width/height clipping, scaled graphics condition and explicit D3DX_FILTER_NONE=1 versus 0x30004 filtering')
 print('PASS real original D3DXCreateTexture, GetSurfaceLevel, D3DXLoadSurfaceFromFileInMemory, COM Release and distinct 2745B texture finalizer edge')
 print('PASS entire canonical source 562/562B exact, 486/486 ordinary original bytes and nineteen genuine PE relocation sites/types/destinations')
 print('PASS ONE newly whole-exact game-authored 562B head; 2745B finalizer and folded SDK/Graphics helpers are separate, uncredited')
if __name__=='__main__':verify()
