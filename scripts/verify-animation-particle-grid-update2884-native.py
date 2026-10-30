#!/usr/bin/env python3
"""Immutable-original 2884B particle-grid VM/update Boss and 12B INT3 audit.

This is an ORIGINAL-NATIVE frontier only: it cannot claim a 2884B strict
C++ source, compiler output, or completed reconstruction.
"""
from pathlib import Path
import hashlib,importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
HEAD,SIZE=0x0045C360,2884
END=HEAD+SIZE
DATA_COUNT=25
CALL_COUNT=99
CALL_FINGERPRINT='d4f686014fe5a3b932af7e85e26b3091be1b54f905d50dbfa03f3e9222809860'
FIELD_FINGERPRINT='856f206143237e2f2a3352bac77718b629b46e27a7c8bdc53d2f027dba558177'
BODY_SHA256='0d8c82a2018031e59c5e7172e08318e133f3513b6fc4639a1bab506c41eb02d1'
ALIGN_SHA256='a0d08a155aa4e9aadd5da959565de99acc8dc9dbda96ec3852dde76c97330902'

def digest(pairs):
 text=''.join(f'{a:04x}:{b:08x}\n' for a,b in pairs)
 return hashlib.sha256(text.encode()).hexdigest()

def verify():
 image,_=pe.verified_target();base,secs=pe.parse_sections(image)
 highlow=pe.physical_highlow(image,base,secs)
 code=pe.raw_at(image,base,secs,HEAD,SIZE)
 assert hashlib.sha256(code).hexdigest()==BODY_SHA256
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==768,len(ins)
 assert ins[-1].address+ins[-1].size==END
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert sum(i.mnemonic=='ret' for i in ins)==1
 assert code.startswith(bytes.fromhex('538bdc83ec0883e4f883c404'))
 align=pe.raw_at(image,base,secs,END,12)
 assert align==bytes([0xCC])*12
 assert hashlib.sha256(align).hexdigest()==ALIGN_SHA256
 call_pairs=[(i.address-HEAD,int(i.op_str,16)) for i in ins if i.size==5 and i.bytes[0]==0xe8]
 assert len(call_pairs)==CALL_COUNT
 assert digest(call_pairs)==CALL_FINGERPRINT
 fields=[(loc-HEAD,struct.unpack('<I',pe.raw_at(image,base,secs,loc,4))[0])
         for loc in sorted(highlow) if HEAD<=loc<END]
 assert len(fields)==DATA_COUNT and digest(fields)==FIELD_FINGERPRINT
 assert Counter(v for _,v in call_pairs)[0x0045CF10]==2
 assert Counter(v for _,v in call_pairs)[0x00414580]==13
 assert Counter(v for _,v in call_pairs)[0x0045D0C0]==12
 assert Counter(v for _,v in call_pairs)[0x005429EE]==1
 assert Counter(v for _,v in fields)[0x005BA4C4]==10
 vtable_addr=0x0056EC14
 values=struct.unpack('<6I',pe.raw_at(image,base,secs,vtable_addr,24))
 assert values==(0x0045C320,HEAD,0x00412540,0x0045CEB0,0x0045D060,0x00414B50)
 assert all(vtable_addr+4*i in highlow for i in range(6))
 next_method=pe.raw_at(image,base,secs,END+12,4)
 assert next_method==bytes.fromhex('558bec83'),next_method.hex()
 branches=[]
 for i in ins:
  if i.mnemonic.startswith(('j','loop')):
   try: target=int(i.op_str,16)
   except ValueError:continue
   branches.append((i.address,target))
 assert branches and all(HEAD<=t<END for _,t in branches)
 print('PASS original vtable 0x0056EC14 slot1 -> 0x0045C360; true body 2884B/768 i386')
 print('PASS 99 original E8 site/destination pairs, frozen SHA256',CALL_FINGERPRINT)
 print('PASS 25 real PE HIGHLOW site/target fields, frozen SHA256',FIELD_FINGERPRINT)
 print('PASS real native ret 0x0045CEA3, 12 genuine INT3 then separate 92B method at 0x0045CEB0')
 print('PASS two physical 202B normalization child E8, game RNG/cookie and native branch boundaries')
 print('NOT EXACT: no canonical C++ source, no new original-authored .text credit or game-function mapping')

if __name__=='__main__':verify()
