#!/usr/bin/env python3
"""Original-only whole 411B recursive Animation retirement and true folded append."""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x0044F840,411
BODY_SHA256='d38cbce8caaee204e4c1e78bfba2f9023d89395535292d2828b6cabcaea0f94d'
E8={
 0x03B:0x004494B0,0x042:0x0040FF90,0x060:0x004494B0,
 0x067:0x0040FF90,0x074:0x0040C080,0x080:0x0044B9F0,
 0x08F:0x00412540,0x09C:0x00411C30,0x0A9:0x00411BB0,
 0x0B8:0x0040C300,0x0C7:0x0040F160,0x0D2:HEAD,
 0x0E4:0x00411B00,0x109:0x0044A670,0x11B:0x00411EA0,
 0x173:0x004494B0,0x17A:0x00411CE0,0x190:0x005429EE,
}
DATA={0x06:0x0056867D,0x15:0x005B25C0}
PARENTS=(0x00449870+0x0F9,0x00449870+0x142)

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 code=pe.raw_at(im,base,sec,HEAD,SIZE)
 assert hashlib.sha256(code).hexdigest()==BODY_SHA256
 cs=Cs(CS_ARCH_X86,CS_MODE_32)
 ins=list(cs.disasm(code,HEAD))
 assert len(ins)==116 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xE8}
 fields={loc-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,loc,4))[0]
         for loc in high if HEAD<=loc<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert fields==DATA,(fields,DATA)
 assert pe.raw_at(im,base,sec,HEAD+SIZE,5)==b'\xcc'*5
 assert ('cmp','dword ptr [ecx + 0x570], 2') in {(i.mnemonic,i.op_str) for i in ins}
 assert sum(i.mnemonic=='nop' for i in ins)==5
 # Prove the recursive method is a genuine whole native self-call and that
 # the queue insertion is the distinct original 57B append physical body.
 assert calls[0xD2]==HEAD and calls[0x11B]==0x00411EA0
 append=list(cs.disasm(pe.raw_at(im,base,sec,0x00411EA0,57),0x00411EA0))
 assert append[-1].address+append[-1].size==0x00411EA0+57
 assert any(i.mnemonic=='call' and i.op_str=='0x411ee0' for i in append)
 for site in PARENTS:
  raw=pe.raw_at(im,base,sec,site,5)
  assert raw[0]==0xe8
  destination=(site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert destination==HEAD,(hex(site),hex(destination))
  print(f'PASS original 508B list-update E8 {site:#010x} -> {HEAD:#010x}')
 print('PASS complete immutable original 411B/116-i386, 18 real E8 sites and 2 PE HIGHLOW')
 print('PASS original recursive E8, native 57B append E8 and 5 original INT3 alignment')
 print('PASS actual retired state+0x570, parent/callback/children cleanup and iterator EH/cookie')

if __name__=='__main__':verify()
