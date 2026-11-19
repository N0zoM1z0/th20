#!/usr/bin/env python3
"""Compile and measure the complete, intentionally nonexact Animation VM source."""
from __future__ import annotations
import collections
import hashlib
import importlib.util
import re
import struct
import subprocess
import sys
import tomllib
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,path):
 spec=importlib.util.spec_from_file_location(name,ROOT/path);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
pe=load('animation_update_pe','scripts/verify-animation-draw-boss-native.py')
cf=load('animation_update_coff','scripts/compare-coff-function.py')
ADDRESS=0x0042B5D0
ORIGINAL_SIZE=39470
ORIGINAL_SHA='044f8246c167aaaf50c00a46a86baa1898e70af55ca5715bcc2450289ba83b87'
ORIGINAL_INSTRUCTIONS=8559
ORIGINAL_CALLS=505
ORIGINAL_HIGHLOW=55
SYMBOL='?update@Animation@th20@@QAEHXZ'
CANDIDATE_SIZE=41048
CANDIDATE_CODE_SIZE=40404
CANDIDATE_INSTRUCTIONS=8417
CANDIDATE_JUMP_TABLE_ENTRIES=161
CANDIDATE_CALLS=505
SECURITY_COOKIE=0x005429EE
SPECIAL_CALL_TARGETS={
 '?project_corners@NativeAnimationCornerProjectionDispatchView@th20@@QAEXPAUVector3@2@@Z':0x00445770,
 '?interpolate_primary_rgb_438d50@NativeAnimationColorConfigView@th20@@QAEXHHABUColor3@2@0@Z':0x00438D50,
 '?interpolate_rgb_438cc0@NativeAnimationColorConfigView@th20@@QAEXHHABUColor3@2@0@Z':0x00438CC0,
 '??_H@YGXPAXIIP6EPAX0@Z@Z':0x0040BC20,
}
ARRAY_CTOR_SYMBOL='??_H@YGXPAXIIP6EPAX0@Z@Z'
ARRAY_CTOR_SIZE=56

def verify_original():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image);body=pe.raw_at(image,base,sections,ADDRESS,ORIGINAL_SIZE)
 assert hashlib.sha256(body).hexdigest()==ORIGINAL_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDRESS));assert len(ins)==ORIGINAL_INSTRUCTIONS and sum(x.size for x in ins)==ORIGINAL_SIZE
 calls=[x for x in ins if x.size==5 and x.bytes[0]==0xE8]
 highlow=[x for x in pe.physical_highlow(image,base,sections) if ADDRESS<=x<ADDRESS+ORIGINAL_SIZE]
 assert len(calls)==ORIGINAL_CALLS and len(highlow)==ORIGINAL_HIGHLOW
 targets=collections.Counter((x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff for x in calls)
 print(f'PASS original Boss boundary/hash: {ORIGINAL_SIZE}B, {len(ins)} instructions, {len(calls)} E8, {len(highlow)} PE HIGHLOW')
 return targets

def candidate_call_targets(relocations):
 units=tomllib.loads((ROOT/'config/match-units.toml').read_text())['units']
 symbol_to_address={u['symbol']:int(u['target_address']) for u in units.values() if u.get('symbol') and u.get('target_address') is not None}
 targets=collections.Counter();unknown=collections.Counter()
 for relocation in relocations:
  if relocation['type']!='REL32':continue
  symbol=relocation['symbol']
  match=re.search(r'(?:call|vm)_([0-9a-fA-F]{8})',symbol)
  if match:address=int(match.group(1),16)
  elif symbol=='@__security_check_cookie@4':address=SECURITY_COOKIE
  elif symbol in SPECIAL_CALL_TARGETS:address=SPECIAL_CALL_TARGETS[symbol]
  elif symbol in symbol_to_address:address=symbol_to_address[symbol]
  else:
   matches={value for key,value in symbol_to_address.items() if key and (key in symbol or symbol in key)}
   if len(matches)==1:address=matches.pop()
   else:unknown[symbol]+=1;continue
  targets[address]+=1
 assert not unknown,unknown
 return targets

def compile_candidate(original_targets):
 source=ROOT/'src/AnimationUpdate39470.cpp';text=source.read_text()
 cases=set(int(x,0) for x in re.findall(r'^\s*case\s+(0x[0-9a-fA-F]+|\d+)\s*:',text,re.M))
 assert len(cases)==161,len(cases)
 for forbidden in ('__asm','__declspec(naked)','_emit','__nop'):
  assert forbidden not in text,forbidden
 obj=ROOT/'build/gptweb-animation-vm-boss/AnimationUpdate39470.obj';obj.parent.mkdir(parents=True,exist_ok=True)
 flags=['/nologo','/c','/std:c++20','/Od','/Ob0','/GS','/Gy','/Zl','/arch:SSE2','/fp:precise','/sdl','/EHsc']
 subprocess.run([str(ROOT/'scripts/compile-probe.sh'),str(source),str(obj),*flags],cwd=ROOT,check=True)
 body,relocations=cf.object_function(obj,SYMBOL,CANDIDATE_SIZE)
 # A natural Vector3[4] declaration emits the compiler's array-construction
 # helper. Its complete 56-byte body is identical to original game helper
 # 0x0040BC20, including the indirect constructor call and RET 0x10.
 array_ctor,_=cf.object_function(obj,ARRAY_CTOR_SYMBOL,ARRAY_CTOR_SIZE)
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 original_array_ctor=pe.raw_at(image,base,sections,0x0040BC20,ARRAY_CTOR_SIZE)
 assert array_ctor==original_array_ctor,'native Vector3 array-constructor helper differs from original 0x0040BC20'
 print(f'PASS natural Vector3[4] constructor helper: {ARRAY_CTOR_SIZE}/{ARRAY_CTOR_SIZE} bytes exact to original 0x0040BC20')
 # MSVC emits the 161-entry switch dispatch table as a trailing COFF
 # contribution with one DIR32 relocation per case label. Do not disassemble
 # these 644 bytes as fake x86 instructions.
 label_relocs=sorted(int(x['offset']) for x in relocations
                     if x['type']=='DIR32' and x['symbol'].startswith('$LN'))
 assert len(label_relocs)==CANDIDATE_JUMP_TABLE_ENTRIES+1,len(label_relocs)
 jump_table=label_relocs[-CANDIDATE_JUMP_TABLE_ENTRIES:]
 assert jump_table==list(range(jump_table[0],jump_table[0]+4*CANDIDATE_JUMP_TABLE_ENTRIES,4))
 assert jump_table[-1]+4==len(body)
 jump_table_size=4*CANDIDATE_JUMP_TABLE_ENTRIES
 code=body[:jump_table[0]]
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,0))
 calls=[x for x in ins if x.size==5 and x.bytes[0]==0xE8]
 rel32=[x for x in relocations if x['type']=='REL32']
 assert len(body)==CANDIDATE_SIZE and len(code)==CANDIDATE_CODE_SIZE and len(ins)==CANDIDATE_INSTRUCTIONS and len(calls)==CANDIDATE_CALLS,(len(body),len(code),len(ins),len(calls))
 assert len(rel32)==CANDIDATE_CALLS,(len(rel32),CANDIDATE_CALLS)
 assert sum(x.size for x in ins)==len(code)
 candidate_targets=candidate_call_targets(relocations)
 assert candidate_targets==original_targets,('call target multiset mismatch',original_targets-candidate_targets,candidate_targets-original_targets)
 dir32=sum(x['type']=='DIR32' for x in relocations)
 print(f'PASS source compile and opcode coverage: {len(cases)} case labels')
 print(f'PASS all {len(calls)} candidate E8 targets exactly match the original 505-call target multiset')
 print(f'NONEXACT contribution: {len(body)}B = {len(code)}B code + {jump_table_size}B {CANDIDATE_JUMP_TABLE_ENTRIES}-entry switch table')
 print(f'Code decode: {len(ins)} instructions, {len(calls)} E8, {dir32} total DIR32 ({len(label_relocs)} local-label relocations)')
 print(f'Explicit gap: +{len(body)-ORIGINAL_SIZE}B total; +{len(code)-ORIGINAL_SIZE}B code before the switch table; original has {ORIGINAL_HIGHLOW} HIGHLOW fields; no exactness claim')

def main():
 original_targets=verify_original();compile_candidate(original_targets)
if __name__=='__main__':main()
