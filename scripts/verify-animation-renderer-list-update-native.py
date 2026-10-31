#!/usr/bin/env python3
"""Attested original primary/secondary Renderer update, including their exact frontier.

Candidate normalization removes ONLY the independently identified 10-byte
native /sdl class preclear. That diagnostic is explicitly NOT strict exactness.
"""
import argparse
import hashlib
import importlib.util
import struct
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('original_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp)
sp.loader.exec_module(pe)
cp=importlib.util.spec_from_file_location('coff_compare',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(cp)
cp.loader.exec_module(coff)

PRIMARY_CALLS={
 0x030:0x0040C080, 0x038:0x00418A50, 0x042:0x0044A640,
 0x053:0x0040C080, 0x05F:0x00412280, 0x06E:0x00412540,
 0x07B:0x00411C30, 0x088:0x00411BB0, 0x09B:0x0040C300,
 0x0A6:0x0040F160, 0x0BA:0x0040F160, 0x0CE:0x0040F160,
 0x0E1:0x0040F160, 0x0F9:0x0044F840, 0x104:0x0040F160,
 0x117:0x0040F160, 0x11E:0x0042B5D0, 0x12A:0x0040F160,
 0x142:0x0044F840, 0x157:0x00411B00, 0x168:0x0040C080,
 0x174:0x00412280, 0x183:0x00412540, 0x190:0x00411C30,
 0x19D:0x00411BB0, 0x1AC:0x0040C300, 0x1B7:0x0040F160,
 0x1CB:0x0044C2F0, 0x1DD:0x00411B00, 0x1F3:0x005429EE,
}
PRIMARY_DATA={0x006:0x00568315,0x015:0x005B25C0,
              0x0F5:0x005C0028,0x13E:0x005C0028,0x1C7:0x005C0028}
# The secondary function's only additional instruction is ADD EAX,0x18
# between the shared temporary list initialization and its first iterator.
SECONDARY_CALLS={k+(3 if k>=0x053 else 0):v for k,v in PRIMARY_CALLS.items()}
SECONDARY_DATA={k+(3 if k>=0x0F5 else 0):v for k,v in PRIMARY_DATA.items()}
VARIANTS={
 '508':(0x00449870,508,152,'72f3b77118e6fba3230975dc9998241d7251a6cfa01c058a02bdb535b618fc6d',PRIMARY_CALLS,PRIMARY_DATA,'?animation_list_update_449870@th20@@YIXPAU?$IntrusiveList@VAnimation@th20@@@1@@Z'),
 '511':(0x00449B20,511,153,'82610fc6e8e74938e509de8a188f053c31e2e9e08ff4039f498b7046861258d8',SECONDARY_CALLS,SECONDARY_DATA,'?animation_list_update_secondary_449b20@th20@@YIXPAUNativeSpawnRendererView@1@@Z'),
}

def verify(variant,object_name=None):
 addr,size,count,sha,calls,data,symbol=VARIANTS[variant]
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 highlow=pe.physical_highlow(image,base,sections)
 body=pe.raw_at(image,base,sections,addr,size)
 assert hashlib.sha256(body).hexdigest()==sha
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,addr))
 assert len(ins)==count and ins[-1].address+ins[-1].size==addr+size
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 observed={i.address-addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0]) & 0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xe8}
 observed_data={site-addr:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
                for site in highlow if addr<=site<addr+size}
 assert observed==calls,(observed,calls)
 assert observed_data==data,(observed_data,data)
 assert body[0x2B:0x30]==b'\x6a\x18\x8d\x4d\xc8'
 assert calls[0x30]==0x0040C080 and calls[0x38]==0x00418A50
 assert calls[0x42]==0x0044A640
 assert sum(v==0x0044F840 for v in calls.values())==2
 assert sum(v==0x0044C2F0 for v in calls.values())==1
 assert pe.raw_at(image,base,sections,addr+size,1)==b'\xcc'
 if variant=='511':
  assert any(i.mnemonic=='add' and i.op_str=='eax, 0x18' for i in ins)
 print(f'PASS original {variant}B/{count} i386, {len(calls)} E8/{len(data)} HIGHLOW, immutable SHA-256 and actual end')
 if not object_name:return
 obj,relocs=coff.object_function(Path(object_name),symbol,size-10)
 assert len(obj)==size-10
 # Native physical field locations come ONLY from the locked original PE,
 # not by solving object fields against target bytes.
 masked=bytearray(body)
 for offset in calls:masked[offset+1:offset+5]=b'\0'*4
 for offset in data:masked[offset:offset+4]=b'\0'*4
 # 0x2b:0x35 is exactly PUSH 0x18, LEA ECX,[EBP-0x38], CALL autozero.
 assert masked[0x2B:0x35]==b'\x6a\x18\x8d\x4d\xc8\xe8\0\0\0\0'
 del masked[0x2B:0x35]
 candidate=bytearray(obj)
 for reloc in relocs:
  offset=int(reloc['offset']);candidate[offset:offset+4]=b'\0'*4
 assert len(relocs)==len(calls)+len(data)-1
 assert candidate==masked, [(i,a,b) for i,(a,b) in enumerate(zip(candidate,masked)) if a!=b][:12]
 print(f'PASS diagnostic: {len(candidate)}/{len(masked)} normalized bytes after ONLY original 10B preclear is removed')
 print('NONEXACT: an unchanged, canonical class/struct IntrusiveList ABI still omits this real call')

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--variant',choices=VARIANTS,required=True)
 p.add_argument('--candidate-object')
 a=p.parse_args();verify(a.variant,a.candidate_object)
