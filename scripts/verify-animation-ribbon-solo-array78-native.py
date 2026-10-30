#!/usr/bin/env python3
"""Locked PE proof: one 0x3C0 ribbon segment std::array ctor, 78B plus 5 INT3."""
from pathlib import Path
import importlib.util, struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045D550,78
CALLS={0x36:0x0040BC20}
DATA={0x06:0x00567600,0x13:0x005B25C0,0x27:0x0045D610}
PARENT=0x0045D5B0+0x22

def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);hi=pe.physical_highlow(image,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==27 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xE8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0] for p in hi if HEAD<=p<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 assert ('push','1') in [(x.mnemonic,x.op_str) for x in ins]
 assert ('push','0x3c0') in [(x.mnemonic,x.op_str) for x in ins]
 assert pe.raw_at(image,base,sec,HEAD+SIZE,5)==b'\xCC'*5
 encoded=pe.raw_at(image,base,sec,PARENT,5);assert encoded[0]==0xE8
 dest=(PARENT+5+struct.unpack_from('<i',encoded,1)[0])&0xffffffff
 assert dest==HEAD,(hex(PARENT),hex(dest))
 print('PASS original 78B/27-x86 single 0x3C0 segment std::array, 5 real INT3')
 print('PASS original 3 physical HIGHLOW and single E8 to native EH vector ctor')
 print(f'PASS native 89B solo group parent call {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
