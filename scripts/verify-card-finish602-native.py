#!/usr/bin/env python3
"""Attest complete original 602B Card finish and the canonical C++20 replay.

Native targets are anchored from the immutable PE's physical E8 instructions
and HIGHLOW directory, never solved from a comparison object's fields.
"""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('card602_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('card602_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x004878B0;SIZE=602
BODY_SHA='17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f'
CALLS={
 0x01F:0x004883A0,0x033:0x00479040,0x047:0x00479040,0x05A:0x00479040,
 0x074:0x0044FCD0,0x08E:0x00488AB0,0x099:0x0044FCD0,
 0x0BC:0x00488550,0x0D0:0x004B90E0,0x0DC:0x00488800,
 0x0EE:0x00488850,0x116:0x0050FC50,
 0x133:0x00486E10,0x142:0x00488510,0x14D:0x00488700,
 0x16A:0x00486E10,0x179:0x00488510,0x1A3:0x00488700,
 0x1B7:0x00486E10,0x1D4:0x00488700,0x1E8:0x00486E10,
 0x212:0x0052F900,0x223:0x00426D70,0x235:0x004B90E0,
 0x23E:0x00488880,0x250:0x00426D70,
}
DATA={0x01B:0x005C069C,0x08A:0x005C06A4,0x0B8:0x005BA568,
 0x0CC:0x005C06A4,0x0D8:0x005C60FC,0x0EA:0x005BA568,
 0x112:0x005C6108,0x149:0x005C6108,0x19F:0x005C6108,
 0x1D0:0x005C6108,0x21F:0x005BA830,0x231:0x005C06A4,
 0x24C:0x005BA830,
}
LEAVES={
 'pause':(0x00488800,41,14,'05a315f5ab25736eea52b9e6976f136441a4e2756b5d3d3165371bc901cdfb3c',
          '?is_paused_488800@NativeCardPlayView@th20@@QBEHXZ',[0xDC]),
 'extra_sound':(0x00488880,23,11,'46c92f973aead0cb4d764e227bda7077557886684d9be3229fe0bbcb336e9732',
          '?requires_extra_sound_488880@NativeCardEndFlagView@th20@@QAEIXZ',[0x23E]),
}
def verify(helpers=None,parent=None):
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 highlow=pe.physical_highlow(image,base,sections)
 body=pe.raw_at(image,base,sections,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==BODY_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==172 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 observed={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xe8}
 fields={site-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
         for site in highlow if HEAD<=site<HEAD+SIZE}
 assert observed==CALLS,(observed,CALLS)
 assert fields==DATA,(fields,DATA)
 print('PASS native Card finish: immutable whole 602B/172 i386, 26 true E8, 13 PE HIGHLOW')
 for key,(addr,size,count,sha,symbol,parents) in LEAVES.items():
  raw=pe.raw_at(image,base,sections,addr,size)
  assert hashlib.sha256(raw).hexdigest()==sha
  ii=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,addr))
  assert len(ii)==count and ii[-1].address+ii[-1].size==addr+size
  assert (ii[-1].mnemonic,ii[-1].op_str)==('ret','')
  assert not any(addr<=site<addr+size for site in highlow)
  assert [off for off,dst in observed.items() if dst==addr]==parents
  if helpers:
   report=coff.compare(helpers,symbol,addr,size)
   assert report['result']=='structural-exact' and report['matched_comparable_bytes']==size
   assert report['relocations']==[]
  print(f'PASS {key}: complete {size}B/{count} i386, original Card E8 and natural compiler zero-reloc equality' if helpers else f'PASS original {key} {size}B/{count} i386 and actual Card E8')
 if parent:
  obj,rels=coff.object_function(parent,'?finish_spell@Card@th20@@QAEXXZ',SIZE)
  assert len(obj)==SIZE and len(rels)==len(CALLS)+len(DATA)
  assert sum(x['type']=='REL32' for x in rels)==len(CALLS)
  assert sum(x['type']=='DIR32' for x in rels)==len(DATA)
  independent_fields={off+1:('REL32',dst) for off,dst in CALLS.items()}
  independent_fields.update({off:('DIR32',dst) for off,dst in DATA.items()})
  assert {row['offset']:(row['type'],independent_fields[row['offset']][1])
          for row in rels}==independent_fields
  assert all(row['addend']==0 for row in rels)
  structural=coff.compare(parent,'?finish_spell@Card@th20@@QAEXXZ',HEAD,SIZE)
  assert structural['result']=='structural-exact'
  assert structural['matched_comparable_bytes']==446 and structural['comparable_bytes']==446
  canonical=coff.compare_unit('card_finish_spell_602')
  assert canonical['result']=='exact' and canonical['size']==SIZE
  assert canonical['object_sha256']==structural.get('object_sha256',canonical['object_sha256'])
  print('PASS entire original 602B/172 source: 446/446 nonreloc bytes; all 26 E8 and 13 HIGHLOW field locations and independent destinations')
  print('PASS canonical card_finish_spell_602: strict exact (602/602 bytes), fresh pinned compiler receipt')
 print('Original Card start 1896B and whole-game linkage remain unfinished')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--helper-object',type=Path);p.add_argument('--parent-object',type=Path)
 a=p.parse_args();verify(a.helper_object,a.parent_object)
