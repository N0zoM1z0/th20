#!/usr/bin/env python3
"""Original 32B list<function<void()>>::push_back and real 153B caller."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('push32_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('push32_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x00470A20
SIZE=32
SHA='e61e3cf7c7d9061fe6e5eb45caee8ed3e9a4be730ba4c5cd694fff99e6fad884'
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 body=pe.raw_at(image,base,sec,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==15 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x14:0x004682E0}
 assert not any(HEAD<=p<HEAD+SIZE for p in pe.physical_highlow(image,base,sec))
 parent_addr=0x00470180
 parent=pe.raw_at(image,base,sec,parent_addr,153)
 assert hashlib.sha256(parent).hexdigest()=='49b7446465141dcc4380a69d175ece20eeeab2845c132c9f097fda95b1e50d32'
 parent_calls={i.address-parent_addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,parent_addr) if i.size==5 and i.bytes[0]==0xe8}
 assert [off for off,dest in parent_calls.items() if dest==HEAD]==[0x5D]
 unit=coff.compare_unit('card_ascii_list_push_back_32')
 assert unit['result']=='exact' and unit['size']==32 and unit['matched_bytes']==32
 assert len(unit['relocations'])==1
 print('PASS native 32B/15-i386 list push_back, real +0x14 E8 to 0x004682E0 and no PE HIGHLOW')
 print('PASS true original 153B ASCII enqueue E8 +0x5D calls this complete list helper')
 print('PASS canonical 32/32 native bytes, generic STL origin uncredited')
if __name__=='__main__':verify()
