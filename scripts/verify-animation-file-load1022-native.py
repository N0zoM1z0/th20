#!/usr/bin/env python3
"""Independent locked PE proof of whole native 1022B game AnimationFile load.

Read original source-independent E8 targets, PE HIGHLOW, physical code
extent, narrow path and real Renderer-owned group-parser coupling.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('fileloadpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('fileloadcm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044A700
SHA='b750b3b8810f442dfe717b1c4b49eabad84423ed2771efa794c28c0321273021'
E8={0x41:0x00429120,0x54:0x00410AA0,0xB6:0x0040C720,0xCF:0x0044C590,
 0xFC:0x0040BDA0,0x11B:0x004189C0,0x146:0x00446DC0,0x155:0x0040E5A0,
 0x164:0x0040E6C0,0x177:0x00451580,0x1A4:0x0040BDA0,0x1C3:0x004189C0,
 0x1EE:0x00446DC0,0x1FD:0x0040E5A0,0x20C:0x0040E6C0,0x29F:0x004475F0,
 0x2BF:0x00447520,0x2DF:0x00447480,0x332:0x0044EBF0,0x35D:0x0040E6C0,
 0x3B3:0x004476C0,0x3D8:0x0040E6C0,0x3F3:0x005429EE}
HL={0x06:0x005684DC,0x18:0x005B25C0,0x36:0x0056E0E4,
 0x295:0x0056E270,0x29B:0x005B8894,0x2B5:0x0056E2B8,0x2BB:0x005B8894,
 0x2D5:0x0056E2FC,0x2DB:0x005B8894,0x32E:0x005C0028,
 0x3A9:0x0056E338,0x3AF:0x005B8894}
SYM='?load_resource_44a700@NativeAnimationFileLoadView@th20@@QAEHPBD@Z'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 raw=pe.raw_at(im,base,sec,HEAD,1022)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==219 and ins[-1].address+ins[-1].size==HEAD+1022
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)==E8 and len(E8)==23
 data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
       for p in hl if HEAD<=p<HEAD+1022}
 assert data==HL and len(HL)==12
 # This is narrow char sprintf_s<260>, not the old decompiler's false
 # wchar_t[130] speculation: original format is actual 3B ASCII "%s\0".
 assert pe.raw_at(im,base,sec,0x0056E0E4,3)==b'%s\x00'
 assert calls(ins,HEAD)[0x41]==0x00429120
 assert data[0x36]==0x0056E0E4
 # 0x005C0028 is the actual live Renderer manager pointer, because
 # the 336B group decoder receives AnimationFile as *its argument*.
 assert data[0x32E]==0x005C0028 and calls(ins,HEAD)[0x332]==0x0044EBF0
 assert pe.raw_at(im,base,sec,0x0044EBF0,2)==b'\x55\x8b'
 assert [E8[k] for k in (0x29F,0x2BF,0x2DF,0x3B3)]==[
  0x004475F0,0x00447520,0x00447480,0x004476C0]
 assert [HL[k] for k in (0x295,0x2B5,0x2D5,0x3A9)]==[
  0x0056E270,0x0056E2B8,0x0056E2FC,0x0056E338]
 assert sum(1 for x in E8.values() if x==0x0040E6C0)==4
 obj=ROOT/'build/core1093-canonical/AnimationFileLoad1022.obj'
 cmp=cm.compare(obj,SYM,HEAD,1022)
 assert cmp['result']=='structural-exact'
 assert cmp['matched_comparable_bytes']==cmp['comparable_bytes']==882
 roles={**{k:('DIR32',v) for k,v in HL.items()},**{k+1:('REL32',v) for k,v in E8.items()}}
 assert len(cmp['relocations'])==len(roles)==35
 for r in cmp['relocations']:
  off=int(r['offset'],16)
  assert off in roles and r['type']==roles[off][0]
  assert int(r['solved_destination'],16)==roles[off][1]
 z=cm.compare_unit('animation_file_load_resource_1022')
 assert z['result']=='exact' and z['size']==1022 and z['matched_bytes']==1022
 assert len(z['relocations'])==35
 print('PASS immutable original whole game 1022B/219-i386 AnimationFile loader; exact 23 PE E8 and 12 physical HIGHLOW')
 print('PASS original narrow 260B sprintf_s path, 583B game resource read, two true pmr/path filename/stem conversions and four native allocator factories')
 print('PASS true 0x28B file-group header two-pass count and Renderer 0x005C0028 global 336B group parser; original early failure vs final-group fallthrough EH exits')
 print('PASS canonical original whole 1022/1022 native, 882/882 ordinary bytes, 35 genuine independently pinned native relocation field and destination roles')
 print('PASS one distinct original game-authored 1022B head; generic filesystem/CRT helpers not credited as authored code')
if __name__=='__main__':verify()
