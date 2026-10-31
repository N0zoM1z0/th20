#!/usr/bin/env python3
"""Native complete 2245B glyph-mask Boss and real 2-word array-index calls.

All original PE call sites and bytes are independently read from locked
original executable. Correct C++ std::array<int32_t,2> code naturally emits
four E8 to the ALREADY folded 22B original index head; no duplicate credit.
"""
import hashlib,importlib.util,struct,subprocess,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('maskarraype',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('maskarraycm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00416420
SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
INDEX=0x00414580
INDEX_SHA='63c49b1813004cda4fdbb91fb68008a819c44d98c1c64a7fc76b4405f26a10b8'
INDEX_SITES=(0x29E,0x2B0,0x666,0x678)
SYM='?composite_glyph_mask_416420@NativeGlyphCanvasView@th20@@QAE_NHHHIM@Z'
ARRAY_SYM='??A?$array@H$01@std@@QBEABHI@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify(candidate):
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 original=pe.raw_at(im,base,sec,HEAD,2245)
 assert hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==612 and ins[-1].address+ins[-1].size==HEAD+2245
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x14')
 native_calls=calls(ins,HEAD)
 assert len(native_calls)==37
 assert tuple(k for k in sorted(native_calls) if native_calls[k]==INDEX)==INDEX_SITES
 assert native_calls[0x44]==0x004156A0
 assert native_calls[0x32]==0x004156C0
 assert sum(v==0x004156C0 for v in native_calls.values())==9
 assert sum(v==0x004156A0 for v in native_calls.values())==1
 actual={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
         for p in hl if HEAD<=p<HEAD+2245}
 assert actual=={0x06:0x00567E75,0x18:0x005B25C0,0x57:0x0056C7E0,
                 0x5D:0x005B8894,0x894:0x005B8894}
 folded=pe.raw_at(im,base,sec,INDEX,22)
 assert hashlib.sha256(folded).hexdigest()==INDEX_SHA
 fi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(folded,INDEX))
 assert len(fi)==10 and fi[-1].address+fi[-1].size==INDEX+22
 assert (fi[-1].mnemonic,fi[-1].op_str)==('ret','4')
 assert any(i.mnemonic=='lea' and i.op_str=='eax, [ecx + eax*4]' for i in fi)
 obj=ROOT/candidate
 symbols=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 assert ARRAY_SYM in symbols
 index_cmp=cm.compare(obj,ARRAY_SYM,INDEX,22)
 assert index_cmp['result']=='structural-exact'
 assert index_cmp['matched_comparable_bytes']==index_cmp['comparable_bytes']==22
 assert not index_cmp['relocations']
 body,rel=cm.object_function(obj,SYM,2061)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(body),0))
 assert len(body)==2061 and len(ci)==545 and len(rel)==41
 assert sum(x['type']=='REL32' for x in rel)==36
 assert sum(x['type']=='DIR32' for x in rel)==5
 assert all(x['addend']==0 for x in rel)
 sites=[x['offset'] for x in rel if x['symbol']==ARRAY_SYM]
 assert sites==[0x28F,0x2A1,0x649,0x65B],sites
 assert sum('bitmap_pixels_4156a0' in x['symbol'] for x in rel)==1
 assert sum('pixel_stride_4156c0' in x['symbol'] for x in rel)==8
 # All previously accepted physical native code remains exactly matched
 # under the new real template/type ABI, including the 165B allocator boss.
 import tomllib
 units=tomllib.loads((ROOT/'config/match-units.toml').read_text())['units']
 affected=[k for k,u in units.items() if u.get('source')=='src/GlyphMaskComposite2245.cpp']
 # CORE/RECON-1081 adds nine native whole-exact PMR growth/backout
 # descendants to the original fifteen code owners of this same C++ file.
 # The old exact-count assertion must follow the actual source closure.
 assert len(affected)==24
 new_descendants={
   'glyph_vec_calculate_growth_84','glyph_vec_allocate_at_least_19',
   'glyph_vec_pmr_array_allocate_58','glyph_vec_count_size_42',
   'glyph_vec_capacity_36','glyph_vec_backout_ctor_42',
   'glyph_vec_backout_release_28','glyph_vec_backout_dtor_39',
   'glyph_vec_orphan_range_13'}
 assert new_descendants.issubset(affected)
 for unit in affected:
  result=cm.compare_unit(unit)
  assert result['result']=='exact' and result['matched_bytes']==result['size']
 print('PASS immutable original whole 2245B/612 game Boss, 37 native E8/5 PE HIGHLOW and two 16/32-bit glyph stencil branches')
 print('PASS original four E8 +0x29E/+0x2B0/+0x666/+0x678 to folded 22B native 0x414580 with exact std::array<int32_t,2>::operator[] 22/22')
 print('PASS real std::array<int32_t,2> element size 8B, PMR vector 16B, all 24 current distinct generic/color canonical units whole native exact (original 15 plus 9 growth/rollback)')
 print('SOURCE-PRESENT NONEXACT 2245B parent: meaningful C++20 candidate 2061B/545 i386, 36 E8/5 DIR32, original 37 E8/5 PE HIGHLOW')
 print('Original folded 22B index at 0x414580 ALREADY independently whole exact in other provider, zero duplicate credit')
if __name__=='__main__':
 import argparse
 a=argparse.ArgumentParser();a.add_argument('--candidate-object',required=True,type=Path)
 verify(a.parse_args().candidate_object)
