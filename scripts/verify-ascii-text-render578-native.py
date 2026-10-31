#!/usr/bin/env python3
"""Independently attest 578B native ASCII text render and source frontier.

Strict exact is deliberately NOT claimed; this verifier checks every native
physical call/PE HIGHLOW and only reports the five SSE nonreloc byte gaps.
"""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('ascii578pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
sp=importlib.util.spec_from_file_location('ascii578coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(sp);sp.loader.exec_module(coff)
HEAD=0x0044B020
SIZE=578
SHA='fd121bcfb2bb70f0ea9015ed166f137eaa8fef7e663b5c4cbc781d0cee9a4617'
SYMBOL='?draw_44b020@NativeTextSubmitOwner@th20@@QAA?AUNativeTextDrawResult8@2@PAVAnimation@2@HIHHHV?$function@$$A6AXXZ@std@@PBDZZ'
CALLS={0x039:0x0040C310,0x045:0x0040B730,0x07D:0x00447940,
       0x092:0x00437CD0,0x12A:0x0054FE20,0x19C:0x00445A00,
       0x1B6:0x004140F0,0x202:0x0044FFF0,0x211:0x0040B900,
       0x220:0x00414400,0x239:0x005429EE}
DATA={0x006:0x00568578,0x018:0x005B25C0,0x035:0x005C0240,
      0x056:0x0056C768,0x10F:0x0056C8D0,0x117:0x0056C8CC,
      0x14E:0x0056CDD0,0x172:0x0056C8D0}
UNMATCHED={0x16D,0x171,0x17F,0x184,0x188}

def verify(candidate):
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(instructions)==139 and instructions[-1].address+instructions[-1].size==HEAD+SIZE
 assert (instructions[-1].mnemonic,instructions[-1].op_str)==('ret','')
 native_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
               for i in instructions if i.size==5 and i.bytes[0]==0xe8}
 assert native_calls==CALLS
 highlow=pe.physical_highlow(image,base,sections)
 native_data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
             for p in highlow if HEAD<=p<HEAD+SIZE}
 assert native_data==DATA
 assert pe.raw_at(image,base,sections,HEAD+SIZE,5)==b'\xcc'*5
 # The original submit callee has this in ECX and cleans 0x58 bytes of
 # by-value callable/arguments itself; the outer formatter is variadic,
 # keeping this on the stack before its hidden eight-byte return buffer.
 submit=pe.raw_at(image,base,sections,0x0044FFF0,294)
 subins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(submit,0x0044FFF0))
 assert len(subins)==106 and (subins[-1].mnemonic,subins[-1].op_str)==('ret','0x58')
 callback=pe.raw_at(image,base,sections,0x00486E80,111)
 assert hashlib.sha256(callback).hexdigest()=='12212f28b9331ddb3041bea74034cf798e3bc7ab873eb2372b2146cb430d21ae'
 assert callback[0x62]==0xe8
 assert (0x00486E80+0x67+struct.unpack_from('<i',callback,0x63)[0])&0xffffffff==HEAD
 print('PASS native ASCII text renderer: immutable 578B/139 i386, 11 E8/8 PE HIGHLOW, real ret and INT3')
 print('PASS native 294B submit callee ret 0x58 and native Card lambda 111B E8 +0x62 into renderer')
 if candidate:
  object_code,relocations=coff.object_function(candidate,SYMBOL,SIZE)
  assert len(object_code)==SIZE and len(relocations)==19
  expected_fields={off+1:'REL32' for off in CALLS}
  expected_fields.update({off:'DIR32' for off in DATA})
  assert {r['offset']:r['type'] for r in relocations}==expected_fields
  report=coff.compare(candidate,SYMBOL,HEAD,SIZE)
  assert report['result']=='mismatch'
  assert (report['matched_comparable_bytes'],report['comparable_bytes'])==(497,502)
  assert {int(d['offset'],16) for d in report['first_differences']}==UNMATCHED
  assert len(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(object_code),0)))==139
  print('NONEXACT: natural C++20 578B/139 i386, all 19 physical relocation FIELD SITES, 497/502 nonreloc bytes')
  print('Five SSE register-selector bytes differ at',','.join(hex(i) for i in sorted(UNMATCHED)))
  print('The source-generated __xmm table symbol at +0x14E is not an accepted original data owner')
 print('No native-authored exact head/bytes or complete gameplay/linkage claim for this 578B Boss')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
