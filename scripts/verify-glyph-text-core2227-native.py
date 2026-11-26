#!/usr/bin/env python3
"""Verify the complete GDI text core, font pointers, owned EH and strict replay."""
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

CALL_ROLES = (
 ('?slot@LockRegistry@',0x0040C310),
 ('??0?$lock_guard@',0x0040B730),
 ('??A?$array@PAUHFONT',0x00414580),
 ('??$allocate_object@',0x00413C50),
 ('_memset',0x00544760),
 ('?ensure_format_4153d0@',0x004153D0),
 ('?device_context_415620@',0x00415620),
 ('_wcslen',0x00548300),
 ('?composite_glyph_mask_416420@',0x00416420),
 ('___report_rangecheckfailure',0x00542B55),
 ('?composite_glyph_mask_416420@',0x00416420),
 ('___report_rangecheckfailure',0x00542B55),
 ('?invert_alpha_417ab0@',0x00417AB0),
 ('?slot@LockRegistry@',0x0040C310),
 ('??0?$lock_guard@',0x0040B730),
 ('??$addressof@PAVNativeGlyphCanvasStorage@',0x0040B280),
 ('??0NativeGlyphRenderJob@',0x00413EC0),
 ('??$?0UNativeGlyphRenderJob@',0x00412F20),
 ('?submit_4162f0@',0x004162F0),
 ('??1?$function@',0x00414400),
 ('??1NativeGlyphRenderJob@',0x004142C0),
 ('??1?$lock_guard@',0x0040B900),
 ('??1?$lock_guard@',0x0040B900),
 ('??1?$function@',0x00414400),
 ('@__security_check_cookie@4',0x005429EE),
)
DATA_ROLES = (
 ('__ehhandler$',0x00567DD9),
 ('___security_cookie',0x005B25C0),
 ('?process_locks@',0x005C0240),
 ('?native_glyph_fonts_5b66f0@',0x005B66F0),
 ('?native_font_size_56c8d0@',0x0056C8D0),
 ('?native_font_size_56c8d4@',0x0056C8D4),
 ('?native_font_size_56c8d8@',0x0056C8D8),
 ('?native_font_size_56c8dc@',0x0056C8DC),
 ('?native_font_size_56c8e0@',0x0056C8E0),
 ('$SG',0x0056C860),
 ('?process_allocator@',0x005B8894),
 ('$LN',0x004160E4),
 ('?native_font_outline_scale_5ae120@',0x005AE120),
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
def verify_eh(obj,image,base,sections):
 import re,subprocess
 code,mask = bytearray(),set()
 for symbol,size in [(f'__unwindfunclet${SYM}${i}',size) for i,size in enumerate((8,11,11,11,16))]+[('__ehhandler$'+SYM,42)]:
  body,rows = cm.object_function(obj,symbol,size)
  for r in rows:mask.update(range(len(code)+r['offset'],len(code)+r['offset']+4))
  code.extend(body)
 hits=[]
 for name,_,rva,length,offset in sections:
  if name != b'.text':continue
  area,start=image[offset:offset+length],0
  while (start:=area.find(code[:4],start))>=0:
   if all(area[start+i]==b for i,b in enumerate(code) if i not in mask):hits.append(base+rva+start)
   start+=1
 assert hits == [0x00567DA0]
 rows=subprocess.check_output(['objdump','-t',str(obj)],text=True).splitlines()
 row=next(r for r in rows if r.endswith(' __ehfuncinfo$'+SYM))
 m=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',row)
 assert m and int(m[2],16)==0
 raw=obj.read_bytes();header=20+40*(int(m[1])-1)
 size,offset,reloc=struct.unpack_from('<III',raw,header+16)
 assert size==76 and struct.unpack_from('<H',raw,header+32)[0]==6
 data=bytearray(raw[offset:offset+size]);symoff,count=struct.unpack_from('<II',raw,8);strings=raw[symoff+count*18:]
 expected=[(8,0x005A98A4,'__unwindtable$'+SYM)]
 expected += [(40+8*i,target,f'__unwindfunclet${SYM}${i}') for i,target in enumerate((0x00567DA0,0x00567DA8,0x00567DB3,0x00567DBE,0x00567DC9))]
 for i,(field,target,symbol) in enumerate(expected):
  actual,index,kind=struct.unpack_from('<IIH',raw,reloc+10*i)
  name=cm.coff_name(raw[symoff+18*index:][:8],strings)
  assert (actual,kind,name)==(field,6,symbol) and struct.unpack_from('<I',data,field)[0]==0
  struct.pack_into('<I',data,field,target)
 hits=[]
 for name,_,rva,length,offset in sections:
  if name!=b'.rdata':continue
  area,start=image[offset:offset+length],0
  while (start:=area.find(data[:8],start))>=0:
   if all(area[start+i]==b for i,b in enumerate(data) if not 8<=i<12):hits.append(base+rva+start)
   start+=1
 assert hits==[0x005A9880]
 assert data==pe.raw_at(image,base,sections,0x005A9880,76)
 high={a-0x005A9880 for a in pe.physical_highlow(image,base,sections) if 0x005A9880<=a<0x005A9880+76}
 assert high=={field for field,_,_ in expected}
 print('PASS independently anchored99B EH code and complete76B five-state metadata with all6 DIR32 fields')

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
  b, rows = cm.object_function(candidate, SYM, 2316)
  assert len(b) == 2316 and len(rows) == 90
  ins = list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b[:2227]), 0))
  assert len(ins) == 470 and ins[-1].address + ins[-1].size == 2227
  assert b[2227] == 0x90
  call_fields = [r for r in rows if r['type'] == 'REL32']
  data = [r for r in rows if r['type'] == 'DIR32' and r['offset'] < 2227]
  table = [r for r in rows if r['offset'] >= 2228]
  assert len(call_fields) == 25 and len(data) == 43 and len(table) == 22
  assert all(r['addend'] == 0 for r in rows)
  assert [r['offset'] - 1 for r in call_fields] == sorted(E8)
  assert [r['offset'] for r in data] == sorted(native_data)
  assert [r['offset'] for r in table] == list(range(2228,2316,4))
  patched = bytearray(b)
  for r, (prefix, target) in zip(call_fields, CALL_ROLES):
   assert r['symbol'].startswith(prefix) and E8[r['offset']-1] == target
   struct.pack_into('<I',patched,r['offset'],(target-HEAD-r['offset']-4)&0xffffffff)
  for r in data:
   targets = [target for prefix,target in DATA_ROLES if r['symbol'].startswith(prefix)]
   assert len(targets) == 1 and native_data[r['offset']] == targets[0]
   struct.pack_into('<I',patched,r['offset'],targets[0])
  for r in table:
   assert r['type'] == 'DIR32' and r['symbol'].startswith('$LN')
   assert isinstance(r['section_delta'],int) and 0 <= r['section_delta'] < 2227
   struct.pack_into('<I',patched,r['offset'],HEAD+r['section_delta'])
  assert patched == pe.raw_at(img,base,sec,HEAD,2316)
  verify_eh(candidate,img,base,sec)
  for unit in ('glyph_text_core_2227','glyph_text_job_capture_132','glyph_text_job_dtor_23',
               'glyph_text_queue_submit_56', *(f'glyph_text_core_eh_cleanup_{i}' for i in range(5)),
               'glyph_text_core_eh_handler_42'):
   result = cm.compare_unit(unit)
   assert result['result'] == 'exact' and result['matched_bytes'] == result['size'],unit
   assert result['matched_compared_bytes'] == result['compared_size'],unit
  print('PASS complete 2316B contribution: 2227B/470-instruction core, one NOP and all22 font pointers')
  print('PASS all25 call fields,43 body data fields,22 table fields and ten scoped canonical units')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
