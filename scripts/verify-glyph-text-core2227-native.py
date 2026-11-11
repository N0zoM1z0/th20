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
SYM='?native_text_core_415830@th20@@YA_KPBUNativeTextTransform4@1@HHIPBDPAUIDirect3DBaseTexture9@@HHHHV?$function@$$A6AXXZ@std@@@Z'
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
 if candidate:
  b,r=cm.object_function(candidate,SYM,2316)
  assert len(b)==2316 and len(r)==90
  # Candidate is still nonexact: executable code is 2228B with no NOP,
  # but the after-return pointer table starts at exactly native +2228.
  candidate_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b[:2228]),0))
  assert len(candidate_ins)==472
  assert candidate_ins[-1].address+candidate_ins[-1].size==2228
  assert candidate_ins[-1].mnemonic=='ret'
  body_fields=[x for x in r if x['offset']<2228]
  call_fields=[x for x in body_fields if x['type']=='REL32']
  data=[x for x in body_fields if x['type']=='DIR32']
  table=[x for x in r if x['offset']>=2228]
  assert len(call_fields)==25 and len(data)==43 and len(table)==22
  assert [x['offset'] for x in table]==list(range(2228,2316,4))
  assert all(x['type']=='DIR32' and x['symbol'].startswith('$LN') for x in table)
  assert all(x['addend']==0 for x in r)
  candidate_alias=[x['symbol'] for x in table]
  assert len(set(candidate_alias))==17
  assert all((original_table[i]==original_table[j]) ==
             (candidate_alias[i]==candidate_alias[j])
             for i in range(22) for j in range(22))
  first_four=[0x039,0x045,0x057,0x089]
  assert [x['offset']-1 for x in call_fields[:4]]==first_four
  actual_native_data=[x-HEAD for x in sorted(hl) if HEAD<=x<HEAD+2227]
  assert sum(x['offset']==old for x,old in zip(data,actual_native_data))==7
  assert any('composite_glyph_mask_416420' in x['symbol'] for x in call_fields)
  assert any('invert_alpha_417ab0' in x['symbol'] for x in call_fields)
  assert any('ensure_format_4153d0' in x['symbol'] for x in call_fields)
  assert any('submit_4162f0' in x['symbol'] for x in call_fields)
  assert cm.compare_unit('glyph_text_queue_submit_56')['result']=='exact'
  assert cm.compare_unit('glyph_text_job_capture_132')['result']=='exact'
  assert cm.compare_unit('glyph_text_job_dtor_23')['result']=='exact'
  print('PASS full C++20 COFF contribution 2316B: 25 E8, 43 body DIR32, all 22 after-ret DIR32, 17/17 native switch alias groups')
  print('PASS original allocator ordering and distinct font-case source; first four native E8 sites and seven native data positions align')
  print('PASS unrelated exact 56B queue and two existing glyph-job source units unchanged (132B/23B)')
  print('NONEXACT original code 2227B/470-i386 + one NOP versus candidate code 2228B/472-i386 with no pad; whole relocation bytes differ')
 print('Original entire 2227B text core remains NONEXACT; exact 132B game-owned capture is a distinct physical native head')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
