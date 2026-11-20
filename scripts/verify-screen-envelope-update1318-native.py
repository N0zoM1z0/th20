#!/usr/bin/env python3
"""Attest the immutable TH20 ScreenInf 1318B envelope callback boundary."""
from __future__ import annotations
import hashlib
import importlib.util
from collections import Counter
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_envelope',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
ADDRESS=0x004244C0
SIZE=1318
SHA='7b7f9e0966aca60704518d7e68d89fbcdd357b9d62613951d41a3b042079c2a4'
CALLS={
 0x29:0x00424030, 0x38:0x00424060,
 0xA0:0x00423540, 0xB9:0x00423560, 0xCB:0x00423BD0,
 0xF4:0x0040FF90, 0x121:0x0040FF90, 0x154:0x0040FF90,
 0x1D1:0x00423EA0, 0x37A:0x00423EA0,
}
HIGHLOW={
 0x009:0x005BA518,
 0x01C:0x005BA828,0x025:0x005BA828,0x034:0x005BA828,
 0x042:0x005BA828,0x056:0x005BA828,0x06A:0x005BA828,
 0x10D:0x0056C8CC,0x16E:0x0056CDD0,0x195:0x0056CDD0,
 0x1CD:0x005BA4C4,
 0x205:0x005C50E4,0x21F:0x005C50E4,0x239:0x005C50E4,
 0x253:0x005C50E4,0x274:0x005C50E4,0x281:0x005B8818,
 0x2A2:0x005C50E4,0x2BE:0x005C50E4,0x2DA:0x005C50E4,
 0x2EB:0x0056D7D0,0x302:0x005C50E4,0x30E:0x0056D7D0,
 0x316:0x005B8818,0x337:0x005C50E4,0x353:0x005C50E4,
 0x36F:0x005C50E4,0x376:0x005BA4C4,
 0x3AE:0x005C50E8,0x3C8:0x005C50E8,0x3E2:0x005C50E8,
 0x3FC:0x005C50E8,0x41D:0x005C50E8,0x42A:0x005B8818,
 0x44B:0x005C50E8,0x467:0x005C50E8,0x483:0x005C50E8,
 0x494:0x0056D7D0,0x4AB:0x005C50E8,0x4B7:0x0056D7D0,
 0x4BF:0x005B8818,0x4E0:0x005C50E8,0x4FC:0x005C50E8,
 0x518:0x005C50E8,
}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,ADDRESS,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,ADDRESS))
 calls={i.address-ADDRESS:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in instructions if i.size==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 highlow=pe.physical_highlow(image,base,sections)
 actual={site-ADDRESS:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
         for site in highlow if ADDRESS<=site<ADDRESS+SIZE}
 assert actual==HIGHLOW,(actual,HIGHLOW)
 assert len(actual)==44 and len(calls)==10
 # Graphics @ 0x5C4D40; ViewportState[6] @ +0x278, stride 0x16C;
 # points[3] @ +0x12C. These are the four native screen-shake channels.
 points={i:0x005C4D40+0x278+i*0x16C+0x12C for i in (0,1,3,5)}
 assert points=={0:0x005C50E4,1:0x005C5250,3:0x005C5528,5:0x005C5800}
 print('PASS ScreenInf envelope callback: immutable 1318B body, 10 physical E8 targets, 44 physical HIGHLOW targets')
 print('PASS Graphics viewport points aliases: [0]=0x005C50E4 [1]=0x005C5250 [3]=0x005C5528 [5]=0x005C5800')
if __name__=='__main__':verify()
