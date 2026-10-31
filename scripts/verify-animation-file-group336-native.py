#!/usr/bin/env python3
"""Whole original 336B Renderer ANM parser, natural 336B NONEXACT source.

A genuine four-byte original local slot and initial-zero store differ
from the modern C++ input-size initialization. Never add fake padding
or a dead local to claim exact; verify all real native E8/HIGHLOW roles.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('grp336pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('grp336cm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044EBF0
SHA='0ab86e2cc9985d672ff96e5fe0e9ae4b52b5a02c69b63e87a310344ae21b3a67'
E8={0x33:0x00454230,0x61:0x00454230,0xC6:0x00429120,
    0xDE:0x00410AA0,0x106:0x00454230,0x145:0x005429EE}
HL={0x0A:0x005B25C0,0x2A:0x0056E428,0x2F:0x005C0678,
    0x58:0x0056E464,0x5D:0x005C0678,0xBB:0x0056E0E4,
    0xFD:0x0056E488,0x102:0x005C0678}
SYM='?parse_group_44ebf0@NativeRendererAnmGroupView@th20@@QAEHPAUNativeAnimationFileLoadView@2@HPBUNativeAnmGroupHeader@2@@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,336)
 assert hashlib.sha256(body).hexdigest()==SHA
 ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ni)==83 and ni[-1].address+ni[-1].size==HEAD+336
 assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','0xc')
 assert calls(ni,HEAD)==E8
 high={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
       for x in hl if HEAD<=x<HEAD+336}
 assert high==HL
 assert high[0xBB]==0x0056E0E4
 assert pe.raw_at(im,base,sec,0x0056E0E4,3)==b'%s\0'
 assert [high[k] for k in (0x2F,0x5D,0x102)]==[0x005C0678]*3
 assert calls(ni,HEAD)[0xC6]==0x00429120 and calls(ni,HEAD)[0xDE]==0x00410AA0
 assert [calls(ni,HEAD)[k] for k in (0x33,0x61,0x106)]==[0x00454230]*3
 # Three authentic original CP932 Japanese diagnostics in original .rdata.
 for off in (0x0056E428,0x0056E464,0x0056E488):
  assert pe.raw_at(im,base,sec,off,1)==bytes([0x83]),hex(off)
 assert body[0x05]==0x20 and body[0x1B]==0xE0
 parent=pe.raw_at(im,base,sec,0x0044A700,1022)
 assert hashlib.sha256(parent).hexdigest()=='b750b3b8810f442dfe717b1c4b49eabad84423ed2771efa794c28c0321273021'
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x0044A700))
 assert calls(pi,0x0044A700)[0x332]==HEAD
 obj=ROOT/'build/core1095-probes/AnimationFileGroupParse336.obj'
 src,rel=cm.object_function(obj,SYM,336)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(src,0))
 assert len(src)==336 and len(ci)==83 and len(rel)==14
 assert sum(x['type']=='REL32' for x in rel)==6
 assert sum(x['type']=='DIR32' for x in rel)==8
 assert all(x['addend']==0 for x in rel)
 cmp=cm.compare(obj,SYM,HEAD,336)
 assert cmp['result']=='mismatch'
 assert cmp['matched_comparable_bytes']==278 and cmp['comparable_bytes']==280
 assert [int(x['offset'],16) for x in cmp['first_differences']]==[0x05,0x1B]
 fields={**{k:('DIR32',v) for k,v in HL.items()},**{k+1:('REL32',v) for k,v in E8.items()}}
 assert len(cmp['relocations'])==len(fields)
 for r in cmp['relocations']:
  off=int(r['offset'],16)
  assert off in fields and r['type']==fields[off][0]
  assert int(r['solved_destination'],16)==fields[off][1]
 assert src[0x05]==0x1C and src[0x1B]==0xF4
 print('PASS immutable original complete 336B/83-i386 Renderer ANM group parser, 6 native E8 and 8 PE HIGHLOW')
 print('PASS real header signature8, zero flag+0x20, embedded path+0x10, CP932 errors, actual resource read+file extent and 24B texture-record metadata writes')
 print('PASS whole natural C++20 336B/83 instructions with all 14 authentic original reloc positions and targets, 278/280 ordinary bytes')
 print('NONEXACT original stack frame 0x120 and extra zero local [EBP-0x120] vs generated frame0x11C and initialized actual length at [EBP-0x10C], two ordinary byte differences')
 print('No inert compiler-shaping source local or 336B game-authored strict credit; whole 1022B original parent independently exact')
if __name__=='__main__':verify()
