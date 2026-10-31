#!/usr/bin/env python3
"""Locked 2245B original Boss, one bitmap fetch/live stride and real array index.

This verifies a meaningful full C++ source candidate, not a shortened
original or a whole-exact parent. Native original E8 and physical HIGHLOW
come from pinned immutable PE; accepted children keep their own receipts.
"""
import argparse,collections,hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('maskpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('maskcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00416420
SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
SYM='?composite_glyph_mask_416420@NativeGlyphCanvasView@th20@@QAE_NHHHIM@Z'
ORIG={0x004156C0:[0x32,0x197,0x1D7,0x5A6,0x5E7,0x69B,0x6FA,0x752,0x7B4],
      0x004156A0:[0x44],0x00414580:[0x29E,0x2B0,0x666,0x678],
      0x00415800:[0x307,0x39A,0x6E0,0x797]}
DATA={0x06:0x00567E75,0x18:0x005B25C0,0x57:0x0056C7E0,0x5D:0x005B8894,0x894:0x005B8894}
def native_calls(inst,head):
 d=collections.defaultdict(list)
 for i in inst:
  if i.size==5 and i.bytes[0]==0xE8:
   d[(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff].append(i.address-head)
 return d
def verify(candidate):
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 raw=pe.raw_at(im,base,sec,HEAD,2245)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==612 and ins[-1].address+ins[-1].size==HEAD+2245
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x14')
 original=native_calls(ins,HEAD)
 assert sum(map(len,original.values()))==37
 for addr,offsets in ORIG.items():assert original[addr]==offsets,(hex(addr),original[addr])
 actual={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
         for x in hl if HEAD<=x<HEAD+2245}
 assert actual==DATA
 p=ROOT/candidate
 body,rel=cm.object_function(p,SYM,2061)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(body),0))
 assert len(body)==2061 and len(ci)==545
 assert len(rel)==41
 assert sum(x['type']=='REL32' for x in rel)==36
 assert sum(x['type']=='DIR32' for x in rel)==5
 assert all(x['addend']==0 for x in rel)
 fromcollections=collections.Counter()
 for x in rel:
  for text in ['pixel_stride_4156c0','bitmap_pixels_4156a0','canvas_width_415800','??A?$array@H$01@']:
   if text in x['symbol']:fromcollections[text]+=1
 assert fromcollections=={'pixel_stride_4156c0':8,'bitmap_pixels_4156a0':1,'canvas_width_415800':4,'??A?$array@H$01@':4}
 for unit in ['glyph_mask_offsets_vector_ctor_63','glyph_mask_offsets_vector_dtor_20',
              'glyph_mask_offsets_vector_begin_26','glyph_mask_offsets_vector_end_26',
              'glyph_vec_max_size_59','glyph_vec_allocator_max_size_13']:
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS locked original complete 2245B/612-i386 game glyph Boss, 37 real E8/5 native HIGHLOW')
 print('PASS original one bitmap_pixels getter at E8+0x44, nine native stride calls, four genuine folded 22B offset-index E8')
 print('SOURCE-PRESENT NONEXACT: meaningful current C++20 complete 2061B/545 i386, 36 E8/5 DIR32')
 print('PASS source restores one-time bitmap pixels getter, eight live stride E8 and four folded std::array<int32_t,2> offset-index E8')
 print('PASS six representative separate exact generic PMR vector units; original game 2245B parent not exact and not credited')
if __name__=='__main__':
 parser=argparse.ArgumentParser();parser.add_argument('--candidate-object',type=Path,required=True)
 verify(parser.parse_args().candidate_object)
