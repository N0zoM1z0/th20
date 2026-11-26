#!/usr/bin/env python3
"""Whole original 488B vector-growth Boss and its natural C++ PMR body.

The complete 488B/170-i386 body now strictly replays with all 14 E8 calls,
both HIGHLOW fields, and separately checked EH code and state metadata.
"""
import argparse,hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('grow488pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('grow488cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004133E0
SHA='5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57'
ORIGINAL_E8={0x02E:0x0040F160,0x06F:0x004162B0,0x079:0x00414FE0,
 0x08F:0x00414900,0x09F:0x00413120,0x0E6:0x0040B280,
 0x0FB:0x0040B280,0x112:0x00413A90,0x146:0x00413920,
 0x162:0x00413920,0x18B:0x00413920,0x1A9:0x00414960,
 0x1C5:0x004144E0,0x1DD:0x005429EE}
DATA={0x06:0x00567CED,0x15:0x005B25C0}
SYM='??$_Emplace_reallocate@ABV?$array@H$01@std@@@?$vector@V?$array@H$01@std@@V?$polymorphic_allocator@V?$array@H$01@std@@@pmr@2@@std@@AAEPAV?$array@H$01@1@QAV21@ABV21@@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify(obj):
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 body=pe.raw_at(image,base,sec,HEAD,488)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==170 and ins[-1].address+ins[-1].size==HEAD+488
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 assert calls(ins,HEAD)==ORIGINAL_E8
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
       for p in pe.physical_highlow(image,base,sec) if HEAD<=p<HEAD+488}
 assert data==DATA
 for unit,site,target in [('glyph_vec_growth_xlength_16',0x79,0x00414FE0),
       ('glyph_vec_growth_change_array_165',0x1A9,0x00414960),
       ('glyph_vec_growth_reallocation_guard_81',0x1C5,0x004144E0)]:
  assert calls(ins,HEAD)[site]==target
  report=cm.compare_unit(unit)
  assert report['result']=='exact' and report['matched_bytes']==report['size']
 print('PASS immutable original 488B/170-i386 vector-growth Boss, all 14 physical E8 and 2 PE HIGHLOW')
 print('PASS three native-exact 16/165/81-byte children at original E8 +0x79/+0x1A9/+0x1C5')
 if obj:
  import subprocess
  candidate = obj if obj.is_absolute() else ROOT / obj
  subprocess.run([sys.executable, str(ROOT / "scripts/verify-glyph-mask-emplace35-native.py"),
                  "--candidate-object", str(candidate)], cwd=ROOT, check=True)
  print('PASS C++20 PMR growth protocol, complete EH support, and dependent child units')
 report=cm.compare_unit('glyph_emplace_reallocate_488')
 assert report['result']=='exact' and report['matched_bytes']==488
 print('STRICT EXACT: complete 488B growth method with all relocations; source origin remains unknown')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
