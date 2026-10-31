#!/usr/bin/env python3
"""Independent native 132B glyph text job capture and true 2227B caller."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('job132pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('job132cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00413EC0
SHA='1bdff818be6f3097007f19698a72a5e969b7e0922c69ca783a23efa6148247fa'
PARENT=0x00415830
PARENT_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
COPY=0x004140F0
COPY_SHA='557c7cd46e973490cb1c19336e4988976baedac63924d7d6226fe4efa1c13bad'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);high=pe.physical_highlow(image,base,sec)
 body=pe.raw_at(image,base,sec,HEAD,132)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==49 and ins[-1].address+ins[-1].size==HEAD+132
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x18')
 assert calls(ins,HEAD)=={0x75:COPY}
 assert not any(HEAD<=a<HEAD+132 for a in high)
 assert hashlib.sha256(pe.raw_at(image,base,sec,COPY,93)).hexdigest()==COPY_SHA
 native_parent=pe.raw_at(image,base,sec,PARENT,2227)
 assert hashlib.sha256(native_parent).hexdigest()==PARENT_SHA
 parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native_parent,PARENT))
 assert len(parent_ins)==470 and calls(parent_ins,PARENT)[0x7E7]==HEAD
 check=cm.compare_unit('glyph_text_job_capture_132')
 assert check['result']=='exact' and check['size']==132 and check['matched_bytes']==132
 assert len(check['relocations'])==1
 copy=cm.compare_unit('ascii_function_copy_93')
 assert copy['result']=='exact' and copy['size']==93
 print('PASS full original 132B/49-i386 glyph text capture, native E8 +0x75 -> exact 93B function copy, zero HIGHLOW')
 print('PASS full original 2227B/470-i386 glyph core E8 +0x7E7 -> captured 132B ctor')
 print('PASS canonical whole 132/132 natural C++20 with borrowed const std::function& and uninitialized true +0x2C field')
 print('2227B core and 294B text submit parents remain source-present NONEXACT')
if __name__=='__main__':verify()
