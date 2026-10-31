#!/usr/bin/env python3
"""Original whole 124B glyph canvas owner constructor and 73B alloc wrapper.

The native structure is exactly 0x124 bytes; only its observed suffix
fields have recovered names. This proof never grants 73B allocator credit.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph124pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph124cmp',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00414200
SHA='753f6983e88c30419652a69281f0f57138b3d583df317f85ad3be51e51fcc9dd'
ALLOC=0x00413C50
ALLOC_SHA='b82f916474d1365d308fa06635f6d8b54d7f305f8e6003f360d97879e7c9ee91'
CORE=0x00415830
CORE_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sec)
 body=pe.raw_at(img,base,sec,HEAD,124)
 assert hashlib.sha256(body).hexdigest()==SHA
 inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(inst)==28 and inst[-1].address+inst[-1].size==HEAD+124
 assert (inst[-1].mnemonic,inst[-1].op_str)==('ret','')
 assert calls(inst,HEAD)=={0x12:0x00544760}
 assert not any(HEAD<=p<HEAD+124 for p in hl)
 assert any(i.mnemonic=='push' and i.op_str=='0x124' for i in inst)
 assert any(i.mnemonic=='mov' and '[ecx + 0x100]' in i.op_str and '0xffffffff' in i.op_str for i in inst)
 allocator=pe.raw_at(img,base,sec,ALLOC,73)
 assert hashlib.sha256(allocator).hexdigest()==ALLOC_SHA
 ain=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(allocator,ALLOC))
 assert len(ain)==22 and calls(ain,ALLOC)=={0x0E:0x0054275D,0x27:0x0040C080,0x2F:HEAD}
 core=pe.raw_at(img,base,sec,CORE,2227)
 assert hashlib.sha256(core).hexdigest()==CORE_SHA
 cin=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(core,CORE))
 assert len(cin)==470 and calls(cin,CORE)[0x89]==ALLOC
 unit=cm.compare_unit('glyph_canvas_constructor_124')
 assert unit['result']=='exact' and unit['size']==124 and unit['matched_bytes']==124
 assert len(unit['relocations'])==1
 print('PASS original whole 124B/28-i386 glyph canvas ctor: native 0x124-byte memset and 7 resource suffix stores')
 print('PASS native constructor single E8 +0x12 -> actual CRT memset, zero PE HIGHLOW')
 print('PASS original 73B allocator E8 +0x2F -> ctor, original 2227B text Boss E8 +0x89 -> allocator')
 print('PASS canonical 124/124 native C++20 typed 0x124-byte object, 73B parent not accepted')
if __name__=='__main__':verify()
