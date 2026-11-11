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
 # This is a complete NONEXACT 2141B/565-i386 source, not a prefix
 # compared to the original 2245B/612-i386 parent extent.
 body,rel=cm.object_function(obj,SYM,2141)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(body),0))
 assert len(body)==2141 and len(ci)==565 and len(rel)==42
 assert (ci[-1].mnemonic,ci[-1].op_str)==('ret','0x14')
 assert ci[-1].address+ci[-1].size==len(body)
 cr=[r for r in rel if r['type']=='REL32']
 dr=[r for r in rel if r['type']=='DIR32']
 assert len(cr)==37 and len(dr)==5
 assert all(x['addend']==0 for x in rel)
 # Each COFF REL32 belongs to a real E8 opcode in the entire body.
 real_calls=[i.address for i in ci if i.size==5 and i.bytes[0]==0xe8]
 assert len(real_calls)==37
 assert [x['offset']-1 for x in cr]==real_calls
 # The original has 37 real physical E8 destinations, nine of which
 # read the live stride. The corrected RGBA4444 per-pixel source pointer
 # uses the missing ninth getter BEFORE the stencil iterator begins.
 real_original_order=[native_calls[x] for x in sorted(native_calls)]
 assert len(real_original_order)==37
 original_stride=[off for off in sorted(native_calls)
                  if native_calls[off]==0x004156C0]
 assert original_stride==[0x32,0x197,0x1D7,0x5A6,0x5E7,0x69B,0x6FA,0x752,0x7B4]
 candidate_stride=[x['offset']-1 for x in cr
                   if 'pixel_stride_4156c0' in x['symbol']]
 assert candidate_stride==[0x32,0x197,0x1CA,0x5BD,0x607,0x6BC,0x70D,0x757,0x7A7]
 assert len(candidate_stride)==len(original_stride)==9
 # Genuine folded std::array<int32_t,2>::operator[] emits the same four
 # real index helper calls across the two native pixel-format branches.
 sites=[x['offset'] for x in rel if x['symbol']==ARRAY_SYM]
 assert sites==[0x2B5,0x2C7,0x688,0x69A],sites
 # Independent native PE E8 destinations are compared against the actual
 # locked-MSVC C++ COFF symbol roles for EVERY physical call in order.
 # Do not infer the original targets from candidate relocation operands.
 roles={
     '?pixel_stride_4156c0@':0x004156C0,
     '?bitmap_pixels_4156a0@':0x004156A0,
     '??$allocate_array@E@':0x0040D8C0,
     '_memcpy':0x00543E20,
     '?__autoclassinit2@':0x0040C080,
     '??0?$vector@':0x004141C0,
     '??$emplace_back@':0x00416330,
     '??0PackedColor@':0x004142A0,
     '?_Unchecked_begin@':0x00414F30,
     '?_Unchecked_end@':0x00414F70,
     '??A?$array@H$01@':0x00414580,
     '?canvas_width_415800@':0x00415800,
     '??1?$vector@':0x00414440,
     '??0NativeGlyphColor4444@':0x00414280,
     '??$release_array@E@':0x00413B70,
     '@__security_check_cookie@4':0x005429EE,
 }
 for i,(source,original_addr) in enumerate(zip(cr,real_original_order)):
  matched=[address for prefix,address in roles.items()
           if source['symbol'].startswith(prefix)]
  assert len(matched)==1 and matched[0]==original_addr,(i,source['symbol'],matched,hex(original_addr))
 # The candidate preserves all five independent PE HIGHLOW address roles,
 # even while its current source-local field offsets remain NONEXACT.
 highlow={
     '__ehhandler$':0x00567E75,
     '___security_cookie':0x005B25C0,
     '$SG':0x0056C7E0,
     '?process_allocator@':0x005B8894,
 }
 for o,r in zip(sorted(actual),dr):
  dest=[value for prefix,value in highlow.items()
        if r['symbol'].startswith(prefix)]
  assert len(dest)==1 and dest[0]==actual[o],(hex(o),r['symbol'],dest)
 assert [x['offset'] for x in dr]==[0x06,0x18,0x63,0x69,0x836]
 assert sum(x['offset']==o for x,o in zip(dr,sorted(actual)))==2
 assert sum('bitmap_pixels_4156a0' in x['symbol'] for x in rel)==1
 assert sum('pixel_stride_4156c0' in x['symbol'] for x in rel)==9
 assert sum('??A?$array@H$01@' in x['symbol'] for x in rel)==4
 # Only +0x32 and +0x197 currently align as physical call sites; the
 # original logical role graph is stronger than this still-NONEXACT layout.
 assert sum(a==b for a,b in zip(sorted(native_calls),real_calls))==2
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
 print('PASS immutable original whole 2245B/612 game Boss, 37 native E8/5 PE HIGHLOW and both complete pixel-format branches')
 print('PASS original four folded array-index E8 at +0x29E/+0x2B0/+0x666/+0x678, existing 22B array helper whole structural 22/22 (no duplicate credit)')
 print('PASS complete natural 2141B/565-i386 source: all 37 E8/5 DIR32 roles, nine live-stride getter calls, including per-pixel RGBA4444 source at native +0x5E7')
 print('PASS 37/37 candidate E8 target roles in original order, both 32-bit and 16-bit row/source pointer lifetimes; 2/37 E8 physical sites aligned')
 print('PASS all 24 previously accepted PMR/color generic source descendants remain whole native exact')
 print('SOURCE-PRESENT NONEXACT: entire 2141B candidate vs original 2245B parent, no new game-authored code credit')
if __name__=='__main__':
 import argparse
 a=argparse.ArgumentParser();a.add_argument('--candidate-object',required=True,type=Path)
 verify(a.parse_args().candidate_object)
