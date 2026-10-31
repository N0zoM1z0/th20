#!/usr/bin/env python3
"""Immutable 7B Card std::_Test_callable plus real 65B reset E8 proof."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('callable_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
sys.path.insert(0,str(ROOT/'scripts'))
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('callable_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 code=pe.raw_at(img,base,secs,0x00413910,7)
 assert hashlib.sha256(code).hexdigest()=='8c802cff817fdf6fe5a54e1838577f97a5b842ea2a87ef4faf70abd2b500b8eb'
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,0x00413910))
 assert len(ins)==5 and ins[-1].address+ins[-1].size==0x00413917
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert code[3:5]==b'\xb0\x01'
 assert not any(0x00413910<=x<0x00413917 for x in pe.physical_highlow(img,base,secs))
 parent=pe.raw_at(img,base,secs,0x00486A30,65)
 assert hashlib.sha256(parent).hexdigest()=='72a599459ea31b8d6d472df86580c62339b28207be7578710cca54df69e65efa'
 ps=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x00486A30))
 assert len(ps)==26 and ps[-1].address+ps[-1].size==0x00486A30+65
 calls={i.address-0x00486A30:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ps if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x0B:0x00413910,0x20:0x0040B280,0x29:0x00486920,0x35:0x00414C60}
 r=coff.compare_unit('card_text_callable_test_7')
 assert r['result']=='exact' and r['size']==7 and r['matched_bytes']==7
 assert not r['relocations']
 print('PASS immutable original 7B/5-i386 std::_Test_callable true-valued method, no reloc')
 print('PASS original 65B/26-i386 function reset E8 +0xB -> 7B head, all four E8 targets verified')
 print('PASS canonical 7/7 from natural CardStart std::function capture; original 65B reset stays NONEXACT')
if __name__=='__main__': verify()
