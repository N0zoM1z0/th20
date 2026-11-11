#!/usr/bin/env python3
"""Whole SHA and 14 genuine Window-frame scheduler calls to exact 31B entry selector."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 sp=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m
cf=load('winrepeat_cf','scripts/compare-coff-function.py')
pe=load('winrepeat_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x0041CA50
SIZE=31
SHA='c11144f7911afde92376e350a33c7d514a79ac683cf11885551195b85e08648b'
SYM='?active_repeat_41ca50@NativeWindowFrameScheduleView@th20@@QAEPAURepeatCounter@WindowState@2@XZ'
def main():
 exe=cf.verified_target();base,secs=pe.parse_sections(exe)
 native=pe.raw_at(exe,base,secs,HEAD,SIZE)
 assert hashlib.sha256(native).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ins)==11 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert not any(i.size==5 and i.bytes[0]==0xe8 for i in ins)
 assert not any(HEAD<=p<HEAD+SIZE for p in pe.physical_highlow(exe,base,secs))
 assert any(i.mnemonic=='imul' and '0xc' in i.op_str and '0x2100' in i.op_str for i in ins)
 assert any(i.mnemonic=='lea' and '0x2104' in i.op_str for i in ins)
 obj=R/'build/core1129-canonical/WindowActiveRepeat31.obj'
 body,rel=cf.object_function(obj,SYM,SIZE)
 assert bytes(body)==native and not rel
 exact=cf.compare_unit('window_active_repeat_31')
 assert exact['result']=='exact' and exact['matched_bytes']==SIZE
 parent=0x004193E0
 code=pe.raw_at(exe,base,secs,parent,884)
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,parent))
 sites=[op.address-parent for op in ops if op.size==5 and op.bytes[0]==0xe8 and op.address+5+struct.unpack_from('<i',op.bytes,1)[0]==HEAD]
 assert sites==[0x6B,0x99,0xA9,0xB8,0xC9,0xE4,0xF2,0xFC,0x10B,0x126,0x246,0x254,0x326,0x33C],sites
 print('PASS original Window repeat selector 31/31B, 11 instructions, WindowState+0x2100 index and +0x2104*12 stride')
 print('PASS all 14 original E8 caller sites in 884B frame scheduler, exact original/native protected receipt and no relocations')
if __name__=='__main__':main()
