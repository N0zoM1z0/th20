#!/usr/bin/env python3
"""Native original 35B Handle child-event bridge vs *distinct* accepted 35B interrupt."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0044F0D0,35
BRIDGE_CHILD=0x0044EFC0
PREVIOUS_HEAD=0x0044EF90
PREVIOUS_CHILD=0x0044EE90
CALLER=0x00464510

def e8_target(pe_bytes,address):
 assert pe_bytes[0]==0xE8
 return (address+5+struct.unpack_from('<i',pe_bytes,1)[0])&0xffffffff

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==15 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 calls={i.address-HEAD:e8_target(i.bytes,i.address) for i in ins if i.size==5 and i.bytes[0]==0xE8}
 data={off-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,off,4))[0]
       for off in high if HEAD<=off<HEAD+SIZE}
 assert calls=={0x17:BRIDGE_CHILD},calls
 assert data=={0x13:0x005C0028},data
 assert ('nop','') in {(i.mnemonic,i.op_str) for i in ins}
 assert ('mov','edx, dword ptr [ecx]') in {(i.mnemonic,i.op_str) for i in ins}
 # The distinct other 35B handle method has a different physical callee,
 # so keeping its original method name for the offset+7 wrapper is wrong.
 previous=pe.raw_at(im,base,sec,PREVIOUS_HEAD,35)
 prev_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(previous,PREVIOUS_HEAD))
 pcalls=[e8_target(i.bytes,i.address) for i in prev_ins if i.size==5 and i.bytes[0]==0xE8]
 assert pcalls==[PREVIOUS_CHILD],pcalls
 # Existing 29B Dialogue offset+7 wrapper physically calls THIS 35B
 # function, not the other 35B. It is the key source-ABI repair.
 dialog=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,CALLER,29),CALLER))
 sites=[i.address for i in dialog if i.size==5 and i.bytes[0]==0xE8 and e8_target(i.bytes,i.address)==HEAD]
 assert len(sites)==1 and sites[0]-CALLER==0x11,sites
 print('PASS whole original 35B/15-i386, native E8 +0x17 -> original 261B child-event/VM function')
 print('PASS original native global HIGHLOW +0x13 -> current_animation_pool 0x005C0028')
 print('PASS distinct previous 35B interrupt -> 246B pool interrupt at 0x0044EE90')
 print('PASS previously exact 29B Dialogue offset+7 caller genuinely E8 0x00464521 -> 0x0044F0D0')

if __name__=='__main__':verify()
