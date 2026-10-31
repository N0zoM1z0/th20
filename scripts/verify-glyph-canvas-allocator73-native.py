#!/usr/bin/env python3
"""Original glyph canvas 73B allocator with real preclear and ctor E8 graph.

This is an independent native-boundary proof, not exact source acceptance.
The original 73B wrapper remains source-absent; helper matches are separate.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('allocator73_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x00413C50
SHA='b82f916474d1365d308fa06635f6d8b54d7f305f8e6003f360d97879e7c9ee91'
CTOR=0x00414200
CTOR_SHA='753f6983e88c30419652a69281f0f57138b3d583df317f85ad3be51e51fcc9dd'
INIT=0x0040C080
INIT_SHA='6425a6ff69dca64c6adc953b405e901ac7180cdffb28a9f49a86e4f8d440581b'
CORE=0x00415830
CORE_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
E8={0x0E:0x0054275D,0x27:INIT,0x2F:CTOR}
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in inst if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 high=pe.physical_highlow(img,base,secs)
 native=pe.raw_at(img,base,secs,HEAD,73)
 assert hashlib.sha256(native).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
 assert len(ins)==22 and ins[-1].address+ins[-1].size==HEAD+73
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)==E8
 assert not any(HEAD<=p<HEAD+73 for p in high)
 assert any(i.mnemonic=='push' and i.op_str=='0x124' for i in ins)
 preclear=pe.raw_at(img,base,secs,INIT,31)
 assert hashlib.sha256(preclear).hexdigest()==INIT_SHA
 ai=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(preclear,INIT))
 assert len(ai)==14 and calls(ai,INIT)=={0x11:0x00544760}
 assert (ai[-1].mnemonic,ai[-1].op_str)==('ret','4')
 ctor=pe.raw_at(img,base,secs,CTOR,124)
 assert hashlib.sha256(ctor).hexdigest()==CTOR_SHA
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(ctor,CTOR))
 assert len(ci)==28 and calls(ci,CTOR)=={0x12:0x00544760}
 core=pe.raw_at(img,base,secs,CORE,2227)
 assert hashlib.sha256(core).hexdigest()==CORE_SHA
 parents=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(core,CORE))
 assert len(parents)==470 and calls(parents,CORE)[0x89]==HEAD
 print('PASS native original glyph allocator 73B/22 i386, ret 4 and physical 0x124-byte new')
 print('PASS actual allocator E8 +0xE -> operator new, +0x27 -> class preclear, +0x2F -> 124B ctor')
 print('PASS preclear native 31B/14 and ctor 124B/28, each authentic original E8 to CRT memset')
 print('PASS immutable 2227B/470 text Boss physical E8 +0x89 into this original allocator')
 print('NONEXACT/SOURCE-ABSENT: allocator original 73B remains unaccepted; no parent or new byte credit')
if __name__=='__main__':verify()
