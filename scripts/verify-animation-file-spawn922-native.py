#!/usr/bin/env python3
"""Independent original PE proof of entire 922B/269-i386 AnimationFile::spawn.

Physical E8, HIGHLOW, complete body, original return ABI, and actual
83B child-wrapper caller are audited without trusting candidate COFF.
"""
from pathlib import Path
import hashlib,importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(sp);sp.loader.exec_module(p)
HEAD,SIZE=0x00450CB0,922
BODY_SHA256='696333456f3244a79e4401d452c4ad30b377183b9c76c6ffe601dc7260874476'
E8={
 0x032:0x0040C310,0x03B:0x0040B730,0x05C:0x0044C9B0,
 0x083:0x00446DE0,0x097:0x0040C6B0,0x0A7:0x0044C8C0,
 0x0C4:0x0044C8A0,0x0DC:0x0044C8C0,0x0EF:0x00438B70,
 0x210:0x00422DD0,0x295:0x0042B5D0,0x29D:0x00422E10,
 0x2A9:0x004376E0,0x2B1:0x00425CC0,0x2DD:0x0044B890,
 0x312:0x0044B8E0,0x348:0x0044B840,0x361:0x0044B7F0,
 0x377:0x0040B900,0x38F:0x005429EE,
}
HIGHLOW={
 0x006:0x0056872D,0x015:0x005B25C0,0x02E:0x005C0240,
 0x058:0x005C0028,0x093:0x0056E584,0x0A3:0x005C0028,
 0x0C0:0x005C0028,0x0D8:0x005C0028,
 0x169:0x0056CDAC,0x171:0x0056CDA4,0x179:0x0056C8D0,
 0x181:0x0056CDA4,0x189:0x0056C8D0,0x1AF:0x0056CD90,
}
CALLER=0x0045D210+0x45

def verify():
 image,_=p.verified_target();base,secs=p.parse_sections(image)
 reloc=p.physical_highlow(image,base,secs)
 code=p.raw_at(image,base,secs,HEAD,SIZE)
 assert hashlib.sha256(code).hexdigest()==BODY_SHA256
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==269 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x20')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xE8}
 data={loc-HEAD:struct.unpack('<I',p.raw_at(image,base,secs,loc,4))[0]
       for loc in reloc if HEAD<=loc<HEAD+SIZE}
 assert calls==E8,(calls,E8)
 assert data==HIGHLOW,(data,HIGHLOW)
 assert p.raw_at(image,base,secs,HEAD+SIZE,6)==b'\xcc'*6
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('push','9') in ops and ('sub','esp, 0x40') in ops
 assert ('or','edx, 0x200') in ops
 assert ('and','eax, 0xfffbffff') in ops
 assert ('and','al, 0xfc') in ops and ('and','dl, 0xfc') in ops
 assert ('cmp','dword ptr [ebp + 0x1c], 0x17') in ops
 assert sum(x.mnemonic=='call' for x in ins)==20
 for address,val in {0x0056CDAC:640.0,0x0056CDA4:384.0,
                    0x0056C8D0:2.0,0x0056CD90:16.0}.items():
  assert struct.unpack('<f',p.raw_at(image,base,secs,address,4))[0]==val
 parent=p.raw_at(image,base,secs,CALLER,5)
 assert parent[0]==0xe8
 target=(CALLER+5+struct.unpack_from('<i',parent,1)[0])&0xffffffff
 assert target==HEAD,(hex(CALLER),hex(target))
 print('PASS immutable original 922B/269-i386 AnimationFile::spawn, genuine ret0x20 and 6 original INT3')
 print('PASS 20 original physical E8 instruction/site/target pairs, 14 PE HIGHLOW site/target pairs')
 print('PASS real lock9, AnimationPool new, optional stem guard, script bind, four renderer branches')
 print('PASS original flag/position branch, genuine byte-mode writes, 640/384/2/16 float sources')
 print(f'PASS original 83B particle parent physical E8 {CALLER:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
