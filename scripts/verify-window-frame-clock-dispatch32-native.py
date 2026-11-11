#!/usr/bin/env python3
"""Whole-original 32B Window/Frame dispatch with anchored Card clock and device."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(n,p):
 s=importlib.util.spec_from_file_location(n,ROOT/p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('window_frame_cf','scripts/compare-coff-function.py')
pe=load('window_frame_pe','scripts/verify-animation-draw-boss-native.py')
ADDR=0x004193C0
SIZE=32
SHA='fc38d8ab189161a0f23b5f052a00e5e0e52c747701e01b05bca72d045f2d125a'
def main():
 img=cf.verified_target();base,sec=pe.parse_sections(img)
 original=pe.raw_at(img,base,sec,ADDR,SIZE)
 assert len(original)==SIZE and hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,ADDR))
 assert len(ins)==11 and ins[-1].address+ins[-1].size==ADDR+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-ADDR:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x12:0x004ABD50,0x18:0x00487560}
 data={p-ADDR:struct.unpack('<I',pe.raw_at(img,base,sec,p,4))[0]
       for p in pe.physical_highlow(img,base,sec) if ADDR<=p<ADDR+SIZE}
 assert data=={0x05:0x005C4A00,0x0E:0x005C4A00}
 symbol='?window_frame_clock_dispatch_4193c0@th20@@YAXXZ'
 obj,rr=cf.object_function(ROOT/'build/core1124-canonical/WindowFrameClockDispatch32.obj',symbol,SIZE)
 assert len(obj)==SIZE and len(rr)==4
 assert sum(x['type']=='REL32' for x in rr)==2
 assert sum(x['type']=='DIR32' for x in rr)==2
 mask={i for x in rr for i in range(x['offset'],x['offset']+4)}
 assert len(mask)==16 and all(a==b for i,(a,b) in enumerate(zip(obj,original)) if i not in mask)
 for x in rr:
  typ=x['type'];o=x['offset'];site=o-1 if typ=='REL32' else o;target=(calls if typ=='REL32' else data)[site]
  assert x['addend']==0
  if typ=='DIR32':assert target==0x005C4A00 and x['symbol'].startswith('?native_frame_device_5c4a00@')
  elif site==0x12:assert target==0x004ABD50 and x['symbol'].startswith('?frame_seconds_4abd50@')
  else:assert site==0x18 and target==0x00487560 and x['symbol'].startswith('?card_clock_update_487560@')
 check=cf.compare_unit('window_frame_clock_dispatch_32')
 assert check['result']=='exact' and check['matched_bytes']==SIZE
 child=cf.compare_unit('card_clock_callback_37')
 assert child['result']=='exact' and child['matched_bytes']==37
 print('PASS original Window Frame 32/32B, 11 i386, two real E8 and two original process-pointer HIGHLOW sites and targets')
 print('PASS all 16 ordinary bytes, MSVC whole original canonical receipt; separate 37B Card time callback still strictly exact')
 print('PASS new authored game physical head 0x004193C0 +32 original bytes, no duplicate 437B frame owner credit')
if __name__=='__main__':main()
