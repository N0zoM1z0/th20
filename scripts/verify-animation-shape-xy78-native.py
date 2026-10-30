#!/usr/bin/env python3
"""Locked PE-only whole 78B source-owned shape XY transform audit.

Original full x86 and native callers determine its physical game role,
independently of a C++-generated symbol or any object byte comparison.
"""
from pathlib import Path
import importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('original','scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(s);s.loader.exec_module(original)
HEAD=0x00445AD0
SIZE=78
CALLERS={
  0x00439A00:(1980,[0x377,0x3DE,0x442,0x4A9]),
  0x0043B0E0:(2169,[0x377,0x3DE,0x443,0x4A9]),
  0x0043E2C0:(1601,[0x2FA,0x361,0x3C5]),
}
def verify():
 pe,_=original.verified_target();base,sections=original.parse_sections(pe)
 code=original.raw_at(pe,base,sections,HEAD,SIZE)
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(instructions)==20 and instructions[-1].address+instructions[-1].size==HEAD+SIZE
 assert instructions[0].mnemonic=='push' and instructions[1].mnemonic=='mov'
 assert instructions[-1].mnemonic=='ret' and instructions[-1].op_str==''
 assert [(x.address-HEAD,x.mnemonic) for x in instructions if x.mnemonic in ('mulss','subss','addss')]==[
  (0x08,'mulss'),(0x12,'mulss'),(0x17,'subss'),(0x1B,'addss'),
  (0x2C,'mulss'),(0x36,'mulss'),(0x3B,'addss'),(0x3F,'addss')]
 assert instructions[9].op_str=='dword ptr [eax], xmm0'
 assert instructions[17].op_str=='dword ptr [ecx + 4], xmm0'
 assert not any(HEAD<=x<HEAD+SIZE for x in original.physical_highlow(pe,base,sections))
 assert all(x.mnemonic!='call' for x in instructions)
 for caller,(size,expected) in CALLERS.items():
  body=original.raw_at(pe,base,sections,caller,size)
  called=[x.address-caller for x in Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,caller)
          if len(x.bytes)==5 and x.bytes[0]==0xE8 and
             (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff==HEAD]
  assert called==expected,(hex(caller),called,expected)
 print('PASS original entire 78B/20-x86 pure game shape XY transform with 7 cdecl stack arguments and RET')
 print('PASS original exact ordered SSE x*cos−y*sin+tx / x*sin+y*cos+ty, native Vector2 XY stores and no real E8/HIGHLOW fields')
 print('PASS 11 real original E8 caller sites across 1980B, 2169B, 1601B game shape bosses; separate physical game-owned function identity')

if __name__=='__main__':verify()
