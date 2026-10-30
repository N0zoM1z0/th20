#!/usr/bin/env python3
"""Original-only 51B particle-grid event and folded Timer helper ABI audit.

These native facts are not canonical exact acceptance for the caller.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
EVENT=0x0045D060;EVENT_SIZE=51
WRAPPER=0x0045C300;GROUP_CTOR=0x0045C1F0;TIMER_CTOR=0x00422D90
VTABLE=0x0056EC14

def native_calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}

def verify():
 im,_=pe.verified_target();base,secs=pe.parse_sections(im);hl=pe.physical_highlow(im,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 event=list(cs.disasm(pe.raw_at(im,base,secs,EVENT,EVENT_SIZE),EVENT))
 assert len(event)==18 and event[-1].address+event[-1].size==EVENT+EVENT_SIZE
 assert (event[-1].mnemonic,event[-1].op_str)==('ret','4')
 assert native_calls(event,EVENT)=={0x25:WRAPPER},native_calls(event,EVENT)
 assert not any(EVENT<=p<EVENT+EVENT_SIZE for p in hl)
 ops={(i.mnemonic,i.op_str) for i in event}
 assert ('cmp','dword ptr [ebp - 4], 1') in ops
 assert ('push','0x12c') in ops
 assert ('add','ecx, 0x1930') in ops
 assert ('nop','') in ops
 v=struct.unpack('<6I',pe.raw_at(im,base,secs,VTABLE,24))
 assert v[4]==EVENT and VTABLE+16 in hl
 # Verify actual wrapper's function code up to ret, separately from padding.
 wrapped=list(cs.disasm(pe.raw_at(im,base,secs,WRAPPER,26),WRAPPER))
 assert (wrapped[-1].mnemonic,wrapped[-1].op_str)==('ret','4')
 assert native_calls(wrapped,WRAPPER)=={0x0E:0x004297A0}
 assert ('nop','') in {(i.mnemonic,i.op_str) for i in wrapped}
 # The canonical group constructor directly calls the genuine Timer::Timer;
 # this is exactly why the private derived-member ctor cannot be accepted.
 original_ctor=list(cs.disasm(pe.raw_at(im,base,secs,GROUP_CTOR,172),GROUP_CTOR))
 assert native_calls(original_ctor,GROUP_CTOR)[0x9D]==TIMER_CTOR
 print(f'PASS original event {EVENT:#010x}: whole 51B/18 i386, E8 +0x25 -> {WRAPPER:#010x}, no HIGHLOW')
 print(f'PASS vtable {VTABLE:#010x} slot 4 -> original event; event1 forwards 300 at owner+0x1930')
 print('PASS original 26B folded wrapper E8 +0x0E -> 0x004297A0 Timer +=, native NOP')
 print(f'PASS original 172B group ctor E8 +0x9D -> {TIMER_CTOR:#010x} actual Timer ctor')
 print('NOT ACCEPTED: private derived Timer view changes this ctor relocation symbol and is not native ABI proof')

if __name__=='__main__':verify()
