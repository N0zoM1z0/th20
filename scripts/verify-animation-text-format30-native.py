#!/usr/bin/env python3
"""Audit the native narrow-format wrapper, CRT path and 417B caller."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
from capstone.x86 import X86_OP_MEM, X86_OP_REG, X86_REG_ESI, X86_REG_AL
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x00447940,30

def verify_narrow_output_store(instructions):
 stores=[i for i in instructions if i.mnemonic=='mov'
         and i.operands[0].type==X86_OP_MEM
         and i.operands[0].mem.base==X86_REG_ESI
         and i.operands[0].mem.index==0 and i.operands[0].mem.disp==0]
 assert len(stores)==1,'expected one output-buffer terminator store'
 store=stores[0]
 assert store.operands[0].size==1,'native formatter must clear one char, not wchar_t'
 assert store.operands[1].type==X86_OP_REG and store.operands[1].reg==X86_REG_AL

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hi=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==13 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x14:0x00439880},calls
 assert ('push','0x500') in {(i.mnemonic,i.op_str) for i in ins}
 assert not any(HEAD<=q<HEAD+SIZE for q in hi)
 caller=0x0044AC20+0x69;raw=pe.raw_at(im,base,sec,caller,5);assert raw[0]==0xe8
 dest=(caller+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert dest==HEAD,(hex(caller),hex(dest))
 # The Ghidra library name alone cannot distinguish narrow/wide wrappers.
 # Follow the actual calls down to the character-specific CRT body.
 md=Cs(CS_ARCH_X86,CS_MODE_32);md.detail=True
 for address,size,targets in (
     (0x00439880,31,[0x0041F1D0]),
     (0x0041F1D0,77,[0x0041F1C0,0x0054A498]),
     (0x0054A498,65,[0x00547DB0,0x005488AF,0x00547DF8]),
     (0x005488AF,159,[0x0054803F,0x0054873B,0x0054803F])):
  decoded=list(md.disasm(pe.raw_at(im,base,sec,address,size),address))
  assert decoded and sum(i.size for i in decoded)==size
  assert decoded[-1].mnemonic=='ret'
  actual=[(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
          for i in decoded if i.size==5 and i.bytes[0]==0xe8]
  assert actual==targets,(hex(address),actual)
  if address==0x005488AF:
   assert any(i.mnemonic=='mov' and i.op_str=='esi, dword ptr [ebp + 0x10]' for i in decoded)
   verify_narrow_output_store(decoded)
 print(f'PASS native entire 30B/13-i386 narrow-format helper: fixed 0x500 count, E8 +0x14 -> 0x00439880')
 print('PASS complete 31B/77B/65B/159B CRT call path and byte output terminator')
 print(f'PASS actual 417B Animation text-Boss E8 {caller:#010x} -> {HEAD:#010x}, zero HIGHLOW')

if __name__=='__main__':verify()
