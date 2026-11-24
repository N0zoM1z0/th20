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
ORIGINAL_CALL_TARGET_SEQUENCE=[]
CANDIDATE_SIZE=39776
CANDIDATE_CODE_SIZE=39132
CANDIDATE_INSTRUCTIONS=8459
CANDIDATE_STACK_FRAME=0x7f8
CANDIDATE_DIR32=215
CANDIDATE_LOCAL_LABEL_DIR32=162
CANDIDATE_EXTERNAL_DIR32=53
CANDIDATE_JUMP_TABLE_ENTRIES=161
CANDIDATE_CALLS=505
SECURITY_COOKIE=0x005429EE
SPECIAL_CALL_TARGETS={
 '?project_corners@Animation@th20@@QAEXPAUVector3@2@@Z':0x00445770,
 '?interpolate_primary_rgb_438d50@NativeAnimationColorConfigView@th20@@QAEXHHABUColor3@2@0@Z':0x00438D50,
 '?interpolate_rgb_438cc0@NativeAnimationColorConfigView@th20@@QAEXHHABUColor3@2@0@Z':0x00438CC0,
 '?set_duration@?$Interpolation@UAngle@th20@@@th20@@QAEXH@Z':0x0041DF50,
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
 global ORIGINAL_CALL_TARGET_SEQUENCE
 ORIGINAL_CALL_TARGET_SEQUENCE=[(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff for x in calls]
 targets=collections.Counter(ORIGINAL_CALL_TARGET_SEQUENCE)
 print(f'PASS original Boss boundary/hash: {ORIGINAL_SIZE}B, {len(ins)} instructions, {len(calls)} E8, {len(highlow)} PE HIGHLOW')
 return targets

def candidate_call_target_sequence(relocations):
 units=tomllib.loads((ROOT/'config/match-units.toml').read_text())['units']
 symbol_to_address={u['symbol']:int(u['target_address']) for u in units.values() if u.get('symbol') and u.get('target_address') is not None}
 sequence=[];unknown=collections.Counter()
 for relocation in sorted((x for x in relocations if x['type']=='REL32'),key=lambda x:int(x['offset'])):
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
  sequence.append(address)
 assert not unknown,unknown
 return sequence

def candidate_call_targets(relocations):
 return collections.Counter(candidate_call_target_sequence(relocations))

def count_call_subsequence(sequence,pattern):
 pattern=tuple(pattern)
 return sum(tuple(sequence[i:i+len(pattern)])==pattern for i in range(len(sequence)-len(pattern)+1))

def compile_candidate(original_targets):
 source=ROOT/'src/AnimationUpdate39470.cpp';text=source.read_text()
 assert 'DAT_' not in text,'raw decompiler global names remain in the VM source'
 cases=set(int(x,0) for x in re.findall(r'^\s*case\s+(0x[0-9a-fA-F]+|\d+)\s*:',text,re.M))
 assert len(cases)==161,len(cases)
 instruction_header=(ROOT/'src/AnmInstruction.hpp').read_text()
 assert 'struct AnmInstruction' in instruction_header
 assert 'offsetof(AnmInstruction, opcode) == 0' in instruction_header
 assert 'offsetof(AnmInstruction, byte_advance) == 2' in instruction_header
 assert 'offsetof(AnmInstruction, frame) == 4' in instruction_header
 assert 'offsetof(AnmInstruction, operand_flags) == 6' in instruction_header
 assert 'offsetof(AnmInstruction, first_operand) == 8' in instruction_header
 assert 'sizeof(AnmInstruction) == 12' in instruction_header
 assert re.search(r'AnmInstruction\s*\*\s*instruction',text)
 assert re.search(r'AnmInstruction\s*\*\s*scan_instruction',text)
 assert 'instruction->opcode' in text and 'instruction->frame' in text
 assert 'instruction->operand_flags' in text and 'instruction->byte_advance' in text
 assert 'if (base.field_28 < 0) goto LAB_00434fb5;' in text
 assert 'base.flags.bits_08.mode == 1' in text
 assert 'current_game_controller->animation_frozen() != 0) goto LAB_00434fb5;' in text
 assert 'if (instruction->frame <= static_cast<std::int32_t>(timer_4c8)) goto LAB_vm_frame_ready;' in text
 assert 'goto LAB_00434dce;\nLAB_vm_frame_ready:' in text
 assert 'if ((instruction->operand_flags & 1U) != 0) {\n          local_554 = this->integer_value((&instruction->first_operand)[0]);' in text
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
 assert len(ins)>=3 and ins[0].mnemonic=='push' and ins[1].mnemonic=='mov' and ins[2].mnemonic=='sub'
 frame_match=re.fullmatch(r'esp,\s*0x([0-9a-fA-F]+)',ins[2].op_str)
 assert frame_match,ins[2].op_str
 candidate_frame=int(frame_match.group(1),16)
 assert candidate_frame==CANDIDATE_STACK_FRAME,hex(candidate_frame)
 calls=[x for x in ins if x.size==5 and x.bytes[0]==0xE8]
 rel32=[x for x in relocations if x['type']=='REL32']
 assert len(body)==CANDIDATE_SIZE and len(code)==CANDIDATE_CODE_SIZE and len(ins)==CANDIDATE_INSTRUCTIONS and len(calls)==CANDIDATE_CALLS,(len(body),len(code),len(ins),len(calls))
 assert len(rel32)==CANDIDATE_CALLS,(len(rel32),CANDIDATE_CALLS)
 assert sum(x.size for x in ins)==len(code)
 native_calls=[x.address-ADDRESS for x in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sections,ADDRESS,ORIGINAL_SIZE),ADDRESS) if x.size==5 and x.bytes[0]==0xE8]
 candidate_calls=[x.address for x in calls]  # candidate disassembly is based at code offset zero
 assert len(native_calls)==len(candidate_calls)==505
 matched_call_sites=sum(a==b for a,b in zip(native_calls,candidate_calls))
 call_offset_delta=sum(abs(a-b) for a,b in zip(native_calls,candidate_calls))
 candidate_sequence=candidate_call_target_sequence(relocations)
 candidate_targets=collections.Counter(candidate_sequence)
 assert candidate_targets==original_targets,('call target multiset mismatch',original_targets-candidate_targets,candidate_targets-original_targets)
 # These three real VM spawn paths have observable child-resolution/writeback
 # ordering. Pin their original target subsequences independently of the
 # broader parent call-target multiset.
 child_writeback=(0x00437470,0x00437D00,0x00451050,0x0044CED0,0x00437EB0,0x00437EB0)
 child_update_vector=(0x00437470,0x00437D00,0x004512B0,0x0044CED0,0x00437EB0,0x00437EB0,0x00422DD0,0x00437840)
 assert count_call_subsequence(ORIGINAL_CALL_TARGET_SEQUENCE,child_writeback)==2
 assert count_call_subsequence(candidate_sequence,child_writeback)==2
 assert count_call_subsequence(ORIGINAL_CALL_TARGET_SEQUENCE,child_update_vector)==1
 assert count_call_subsequence(candidate_sequence,child_update_vector)==1
 dir32_relocations=[x for x in relocations if x['type']=='DIR32']
 label_dir32=sum(str(x['symbol']).startswith('$LN') for x in dir32_relocations)
 external_dir32=collections.Counter(str(x['symbol']) for x in dir32_relocations
                                    if not str(x['symbol']).startswith('$LN'))
 assert len(dir32_relocations)==CANDIDATE_DIR32,len(dir32_relocations)
 assert label_dir32==CANDIDATE_LOCAL_LABEL_DIR32,label_dir32
 assert sum(external_dir32.values())==CANDIDATE_EXTERNAL_DIR32,external_dir32
 expected_owner_relocations={
  '?default_timer_clock@th20@@3UClockScalar@1@A':7,
  '?native_polygon_random_5ba4c4@th20@@3UGameRandom@1@A':6,
  '?current_game_controller@th20@@3PAUGameController@1@A':2,
  '?native_zero_position@th20@@3UVector3@1@B':6,
  '?native_pi@th20@@3MB':8,
  '?native_four@th20@@3MB':6,
  '?native_negative_one@th20@@3MB':4,
  '?native_two@th20@@3MB':2,
  '?native_one@th20@@3MB':1,
  '?native_zero@th20@@3MB':1,
  '?native_animation_opcode_dispatch_435285@th20@@3QBEB':1,
  '?native_vector_5c5540@th20@@3UVector3@1@B':1,
 }
 assert all(external_dir32[symbol]==count for symbol,count in expected_owner_relocations.items()),external_dir32
 print(f'PASS source compile and opcode coverage: {len(cases)} case labels')
 print(f'PASS lexical lifetime stack frame: 0x{candidate_frame:x}')
 print(f'PASS all {len(calls)} candidate E8 targets exactly match the original 505-call target multiset')
 print(f'CALL-SITE FRONTIER: {matched_call_sites}/505 physical E8 offsets match; absolute offset delta {call_offset_delta}')
 print('PASS original child-spawn ordering: 2 resolve+two-float writebacks and 1 child-update+Vector3 transform sequence')
 print(f'NONEXACT contribution: {len(body)}B = {len(code)}B code + {jump_table_size}B {CANDIDATE_JUMP_TABLE_ENTRIES}-entry switch table')
 print(f'Code decode: {len(ins)} instructions, {len(calls)} E8, {len(dir32_relocations)} DIR32 ({label_dir32} local-label + {sum(external_dir32.values())} external data/constructor/cookie relocations)')
 print(f'Code-length delta vs original executable body: {len(code)-ORIGINAL_SIZE:+}B; original has {ORIGINAL_HIGHLOW} HIGHLOW fields; no exactness claim')

def main():
 original_targets=verify_original();compile_candidate(original_targets)
if __name__=='__main__':main()
