#!/usr/bin/env python3
"""Original full 56B glyph render queue submission, two native E8 roles."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('q56pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('q56cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004162F0
SHA='5213451236ddccc50439af53540e50639d92771ca89506c80233331e217ebac9'
PARENT=0x00415830
PARENT_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
APPEND=0x004131E0
APPEND_SHA='a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 raw=pe.raw_at(im,base,sec,HEAD,56)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==22 and ins[-1].address+ins[-1].size==HEAD+56
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)=={0x0D:0x0040B280,0x2C:APPEND}
 assert not any(HEAD<=pos<HEAD+56 for pos in high)
 assert any(i.mnemonic=='mov' and i.op_str=='edx, dword ptr [ecx + 4]' for i in ins)
 parent=pe.raw_at(im,base,sec,PARENT,2227)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pinst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pinst)==470 and calls(pinst,PARENT)[0x824]==HEAD
 assert hashlib.sha256(pe.raw_at(im,base,sec,APPEND,151)).hexdigest()==APPEND_SHA
 c=cm.compare_unit('glyph_text_queue_submit_56')
 assert c['result']=='exact' and c['size']==56 and c['matched_bytes']==56
 assert len(c['relocations'])==2
 print('PASS original whole 56B/22-i386 glyph queue bridge, native E8 +0x0D to std::_Unfancy and +0x2C to 151B queue backend')
 print('PASS original +4 nested queue state pointer, 40B existing function borrowed by reference, ret 4, zero HIGHLOW')
 print('PASS original full 2227B/470-i386 glyph text Boss E8 +0x824 into queue bridge')
 print('PASS canonical full 56/56 natural source, true std::_Unfancy forwarding, no 2227B or 151B parent credit')
if __name__=='__main__':verify()
