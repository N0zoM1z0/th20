#!/usr/bin/env python3
"""Whole original 95B Animation VM Vector2 coordinate normalizer proof."""
import hashlib, importlib.util, struct, sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('vector2_normalize_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x00438EB0;SIZE=95
SHA='7f15d5aebdf562ed4ced3304b555d59618d06adebce1b0875c95ab34b7345ec8'
DATA={0x0E:0x0056CDAC,0x25:0x0056CDA8}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 dis=Cs(CS_ARCH_X86,CS_MODE_32);ins=list(dis.disasm(body,HEAD))
 assert len(ins)==28 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls=[i for i in ins if i.size==5 and i.bytes[0]==0xE8]
 assert not calls
 high={pos-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,pos,4))[0]
       for pos in pe.physical_highlow(image,base,sections) if HEAD<=pos<HEAD+SIZE}
 assert high==DATA,high
 print('PASS whole original 95B/28-i386 Vector2 coordinate normalizer, no E8, ret')
 print('PASS both original PE HIGHLOW fields: x/640 at +0x0E -> 0x0056CDAC; y/480 at +0x25 -> 0x0056CDA8')
 print('PASS original clamps only strictly negative normalized components; negative zero and NaN are preserved')
if __name__=='__main__':verify()
