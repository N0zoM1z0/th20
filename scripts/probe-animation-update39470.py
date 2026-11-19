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
CANDIDATE_SIZE=41004
CANDIDATE_INSTRUCTIONS=8721
CANDIDATE_CALLS=505
SECURITY_COOKIE=0x005429EE
SPECIAL_CALL_TARGETS={
 '?project_corners@NativeAnimationCornerProjectionDispatchView@th20@@QAEXPAUVector3@2@@Z':0x00445770,
}

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
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
 calls=[x for x in ins if x.size==5 and x.bytes[0]==0xE8]
 rel32=[x for x in relocations if x['type']=='REL32']
 assert len(body)==CANDIDATE_SIZE and len(ins)==CANDIDATE_INSTRUCTIONS and len(calls)==CANDIDATE_CALLS,(len(body),len(ins),len(calls))
 assert len(rel32)==CANDIDATE_CALLS,(len(rel32),CANDIDATE_CALLS)
 candidate_targets=candidate_call_targets(relocations)
 assert candidate_targets==original_targets,('call target multiset mismatch',original_targets-candidate_targets,candidate_targets-original_targets)
 dir32=sum(x['type']=='DIR32' for x in relocations)
 print(f'PASS source compile and opcode coverage: {len(cases)} case labels')
 print(f'PASS all {len(calls)} candidate E8 targets exactly match the original 505-call target multiset')
 print(f'NONEXACT candidate: {len(body)}B, {len(ins)} instructions, {len(calls)} E8, {dir32} DIR32')
 print(f'Explicit gap: +{len(body)-ORIGINAL_SIZE} bytes, +{len(ins)-ORIGINAL_INSTRUCTIONS} instructions; original has {ORIGINAL_HIGHLOW} HIGHLOW fields; no exactness claim')

def main():
 original_targets=verify_original();compile_candidate(original_targets)
if __name__=='__main__':main()
