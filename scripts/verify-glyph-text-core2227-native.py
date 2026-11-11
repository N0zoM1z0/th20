#!/usr/bin/env python3
"""Original whole 2227B GDI text rasterization Boss, 22-pointer source frontier.

This never accepts a shortened code extent and does not infer native target
roles from a generated COFF input. Children have independent match units.
"""
import argparse,hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('core2227pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('core2227cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00415830
SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
E8={0x039:0x0040C310,0x045:0x0040B730,0x057:0x00414580,0x089:0x00413C50,
 0x2E7:0x00544760,0x362:0x004153D0,0x36D:0x00415620,0x3FF:0x00548300,
 0x4AF:0x00416420,0x571:0x00542B55,0x5EA:0x00416420,0x659:0x00542B55,
 0x6D6:0x00417AB0,0x6F7:0x0040C310,0x703:0x0040B730,0x7BC:0x0040B280,
 0x7E7:0x00413EC0,0x80F:0x00412F20,0x824:0x004162F0,0x833:0x00414400,
 0x842:0x004142C0,0x852:0x0040B900,0x87A:0x0040B900,0x889:0x00414400,
 0x8AA:0x005429EE}
IMPORTANT_DATA={0x06:0x00567DD9,0x18:0x005B25C0,0x35:0x005C0240,
 0x53:0x005B66F0,0x68:0x0056C8D0,0x85:0x005B8894,0x2BD:0x005AE120,
 0x2CD:0x0056C8CC,0x2D5:0x005AE120,0x30A:0x0056C124,
 0x388:0x0056C02C,0x3F4:0x0056C028,0x42B:0x0056C030,
 0x453:0x0056C024,0x480:0x0056C01C,0x6B7:0x0056C02C,
 0x6F3:0x005C0240,0x783:0x005B66EC,0x820:0x005B66E0}
SYM='?native_text_core_415830@th20@@YA_KPBUNativeTextTransform4@1@HHIPBDPAUIDirect3DBaseTexture9@@HHHPAEV?$function@$$A6AXXZ@std@@@Z'
CTOR_SYM='??0NativeGlyphRenderJob@th20@@QAE@PAUNativeGlyphCanvasStorage@1@ABIABUNativeTextTransform4@1@2ABHV?$function@$$A6AXXZ@std@@@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify(candidate):
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sec)
 original=pe.raw_at(img,base,sec,HEAD,2227)
 assert hashlib.sha256(original).hexdigest()==SHA
 native=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(native)==470 and native[-1].address+native[-1].size==HEAD+2227
 assert native[-1].mnemonic=='ret'
 assert calls(native,HEAD)==E8
 native_data={pos-HEAD:struct.unpack('<I',pe.raw_at(img,base,sec,pos,4))[0]
              for pos in hl if HEAD<=pos<HEAD+2227}
 assert len(native_data)==43
 for off,dest in IMPORTANT_DATA.items():assert native_data[off]==dest
 for head,length,sha,site in [(0x00416420,2245,'06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad',0x4AF),
                              (0x00417AB0,542,'b510c0d99e2c1d40f1388c77952a55775dfd24617858922e56ed178e1fdf64df',0x6D6),
                              (0x004153D0,104,'20fdd9d772ec1d057d3a77d9795c7c974d44a790a02dff9a3fffdc0fafa78c47',0x362)]:
  assert hashlib.sha256(pe.raw_at(img,base,sec,head,length)).hexdigest()==sha
  assert E8[site]==head
 parent=pe.raw_at(img,base,sec,0x0044FFF0,294)
 assert hashlib.sha256(parent).hexdigest()=='daf9779671bfb7d0dfa8918eaadbbe26c68a659255a569e7ded769d0b3144f53'
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x0044FFF0))
 assert calls(pins,0x0044FFF0)[0x6C]==HEAD and calls(pins,0x0044FFF0)[0xD4]==HEAD
 print('PASS immutable whole 2227B/470-i386 glyph text Boss: 25 real native E8 and 43 PE HIGHLOW')
 print('PASS original 294B submit Boss two E8 into text core and native 2245B outline/542B alpha/104B canvas child links')
 # The physical original switch table follows code plus one real NOP.
 table_start = HEAD + 2228
 assert pe.raw_at(img,base,sec,HEAD+2227,1)==b'\x90'
 original_table=[struct.unpack('<I',pe.raw_at(img,base,sec,table_start+4*i,4))[0]
                 for i in range(22)]
 assert len(set(original_table))==17
 assert all(HEAD <= value < HEAD+2227 for value in original_table)
 assert all(table_start+4*i in hl for i in range(22))
 assert len([x for x in hl if HEAD<=x<table_start+22*4])==43+22
 assert original_table[0]==original_table[7]==original_table[11]
 assert original_table[6]==original_table[8]
 assert original_table[12]==original_table[13]
 assert original_table[18]==original_table[19]
 print('PASS original 2227B code plus one NOP/22 switch HIGHLOW: 2316B whole native physical contribution, 17 original case aliases')
 # The two native color arguments are distinct: +0x10 is the packed GDI
 # text color, +0x14 is the independent glyph-mask outline color.
 at={i.address-HEAD:(i.mnemonic,i.op_str) for i in native}
 assert at[0x392]==('mov','eax, dword ptr [ebp + 0x10]')
 assert at[0x492]==('mov','edx, dword ptr [ebp + 0x14]')
 assert at[0x5CD]==('mov','eax, dword ptr [ebp + 0x14]')
 if candidate:
  # Whole, actual COFF function+switch contribution. Do not compare an
  # original-length prefix or claim that the shorter candidate is exact.
  b,r=cm.object_function(candidate,SYM,2296)
  assert len(b)==2296 and len(r)==90
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b[:2208]),0))
  assert len(ci)==466 and ci[-1].mnemonic=='ret'
  assert ci[-1].address==2207 and ci[-1].address+ci[-1].size==2208
  body_fields=[x for x in r if x['offset']<2208]
  call_fields=[x for x in body_fields if x['type']=='REL32']
  data=[x for x in body_fields if x['type']=='DIR32']
  table=[x for x in r if x['offset']>=2208]
  assert len(call_fields)==25 and len(data)==43 and len(table)==22
  assert [x['offset'] for x in table]==list(range(2208,2296,4))
  assert all(x['type']=='DIR32' and x['symbol'].startswith('$LN') for x in table)
  assert all(x['addend']==0 for x in r)
  ca=[x['symbol'] for x in table]
  assert len(set(ca))==17
  assert all((original_table[i]==original_table[j])==(ca[i]==ca[j])
             for i in range(22) for j in range(22))
  assert [x['offset']-1 for x in call_fields[:17]]==sorted(E8)[:17]
  # Source roles are independent literal identities mapped onto the
  # immutable PE E8 targets, in order (including both destructor paths).
  callsites=(
    ('?slot@LockRegistry@',0x0040C310),('??0?$lock_guard@',0x0040B730),
    ('??A?$array@PAUHFONT',0x00414580),('??$allocate_object@',0x00413C50),
    ('_memset',0x00544760),('?ensure_format_4153d0@',0x004153D0),
    ('?device_context_415620@',0x00415620),('_wcslen',0x00548300),
    ('?composite_glyph_mask_416420@',0x00416420),
    ('___report_rangecheckfailure',0x00542B55),
    ('?composite_glyph_mask_416420@',0x00416420),
    ('___report_rangecheckfailure',0x00542B55),
    ('?invert_alpha_417ab0@',0x00417AB0),('?slot@LockRegistry@',0x0040C310),
    ('??0?$lock_guard@',0x0040B730),
    ('??$addressof@PAVNativeGlyphCanvasStorage@',0x0040B280),
    ('??0NativeGlyphRenderJob@',0x00413EC0),
    ('??$?0UNativeGlyphRenderJob@',0x00412F20),
    ('?submit_4162f0@',0x004162F0),
    ('??1?$function@',0x00414400),('??1NativeGlyphRenderJob@',0x004142C0),
    ('??1?$lock_guard@',0x0040B900),('??1?$lock_guard@',0x0040B900),
    ('??1?$function@',0x00414400),('@__security_check_cookie@4',0x005429EE),
  )
  assert len(callsites)==len(call_fields)==len(E8)
  for (prefix,address),reloc,(_offset,original_target) in zip(callsites,call_fields,sorted(E8.items())):
   assert reloc['symbol'].startswith(prefix),(prefix,reloc['symbol'])
   assert address==original_target,(hex(address),hex(original_target))
  # The genuine 8B folded lib helper at +0x7BC has no original E8 or
  # PE HIGHLOW. The generated std::addressof instantiation is exact as
  # one shared physical helper; it does NOT create additional coverage.
  helper='??$addressof@PAVNativeGlyphCanvasStorage@th20@@@std@@YAPAPAVNativeGlyphCanvasStorage@th20@@AAPAV12@@Z'
  same=cm.compare(candidate,helper,0x0040B280,8)
  assert same['result']=='structural-exact'
  assert same['matched_comparable_bytes']==8 and not same['relocations']
  # Original data destinations are read from the original PE, but role
  # identities are separately fixed here rather than guessed from object.
  roles=(
      ('__ehhandler$',0x00567DD9),('___security_cookie',0x005B25C0),
      ('?process_locks@',0x005C0240),('?native_glyph_fonts_5b66f0@',0x005B66F0),
      ('?native_font_size_56c8d0@',0x0056C8D0),
      ('?native_font_size_56c8d4@',0x0056C8D4),
      ('?native_font_size_56c8d8@',0x0056C8D8),
      ('?native_font_size_56c8dc@',0x0056C8DC),
      ('?native_font_size_56c8e0@',0x0056C8E0),
      ('$SG',0x0056C860),('?process_allocator@',0x005B8894),
      ('$LN',0x004160E4),('?native_font_outline_scale_5ae120@',0x005AE120),
      ('__real@3f800000',0x0056C8CC),
      ('__imp__MultiByteToWideChar@24',0x0056C124),
      ('__imp__SelectObject@8',0x0056C02C),
      ('__imp__SetBkMode@8',0x0056C028),
      ('__imp__GetTextExtentPoint32W@16',0x0056C030),
      ('__imp__SetTextColor@8',0x0056C024),
      ('__imp__TextOutW@20',0x0056C01C),
      ('?native_font_extra_padding_5b66ec@',0x005B66EC),
      ('?native_glyph_task_queue_5b66e0@',0x005B66E0),
  )
  oldsites=sorted(native_data)
  assert len(oldsites)==len(data)==43
  assert sum(offset==ref['offset'] for offset,ref in zip(oldsites,data))==41
  for offset,ref in zip(oldsites,data):
   matches=[target for prefix,target in roles if ref['symbol'].startswith(prefix)]
   assert len(matches)==1 and matches[0]==native_data[offset],(offset,ref['symbol'],matches)
  # No duplicate game credit: mask only actual COFF relocation fields and
  # count ordinary bytes across this COMPLETE 2,296B contribution.
  masked={i for ref in r for i in range(ref['offset'],ref['offset']+4)}
  original_prefix=pe.raw_at(img,base,sec,HEAD,2296)
  equal=sum(a==z for i,(a,z) in enumerate(zip(b,original_prefix)) if i not in masked)
  assert len(masked)==360 and len(b)-len(masked)==1936 and equal==1626
  assert bytes(b)!=original_prefix
  assert cm.compare_unit('glyph_text_queue_submit_56')['result']=='exact'
  assert cm.compare_unit('glyph_text_job_capture_132')['result']=='exact'
  assert cm.compare_unit('glyph_text_job_dtor_23')['result']=='exact'
  assert original[0x43A:0x443]==bytes.fromhex('8b450c83c00289450c')
  assert at[0x797]==('mov','edx, dword ptr [ebp - 0x224]')
  print('PASS typed completion pointer stack slot +0x2C, authentic glyph text/outline args and live +6 region increment')
  print('PASS original physical 8B address helper equals C++ std::addressof 8/8; 17/25 E8 positions and all 25 callee roles preserved in order')
  print('PASS 43/43 original body HIGHLOW target roles, 41/43 original positions, 22 generated font-case pointers and all 17 original alias classes')
  print('PASS natural named glyph job survives queued std::function submit, function destructor precedes job destructor, matching original role order')
  print(f'NONEXACT: candidate 2296B/466 code instructions vs original 2316B/470+NOP, ordinary {equal}/1936; no parent exact credit')
  print('PASS separate 132B glyph job constructor, 23B destructor and 56B queue submit whole native exact')
 print('Original entire 2227B text core remains NONEXACT; exact 132B game-owned capture is a distinct physical native head')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
