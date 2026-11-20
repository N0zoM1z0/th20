#!/usr/bin/env python3
"""Independent immutable ScreenInf switch/body/table proof for exact reconstruction."""
import hashlib
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,script):
    spec=importlib.util.spec_from_file_location(name,ROOT/'scripts'/script)
    module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
    return module
pe=load('pe_screen','verify-animation-draw-boss-native.py')
cf=load('coff_screen','compare-coff-function.py')
HEAD=0x00423BF0
BODY=637
COMPARE=680
SHA_BODY='7fe3011c872c1e88346d2d995ec8dd21d0ee16e4dcb709fdfa17e135fa9f70b0'
SHA_COMPARE='cfb1f3db1be2f16636978929be0ce9eb293aa05c2260ae89484ad032326f19d6'
SYMBOL='?initialize_423bf0@NativeScreenInf@th20@@QAEXHIIIIH@Z'
# Independent native i386 instruction offsets and calls, not candidate-solved displacements.
E8={
 0x02F:0x004122C0,0x04A:0x00412360,0x068:0x004122C0,
 0x086:0x004122C0,0x0A1:0x00412360,0x0C9:0x004122C0,
 0x0E4:0x00412360,0x102:0x004122C0,0x11D:0x00412360,
 0x13B:0x004122C0,0x156:0x00412360,0x174:0x004122C0,
 0x18F:0x00412360,0x1AD:0x004122C0,0x1C8:0x00412360,
 0x1E3:0x004122C0,0x1FE:0x004122C0,0x219:0x00412360,
 0x238:0x00412DA0,0x245:0x00423520,
}
# Independent PE .reloc physical HIGHLOW sites: 20 function data, 10 switch entries.
DATA={
 0x01B:0x00423E70,0x029:0x004240C0,0x042:0x00424E00,
 0x062:0x004249F0,0x080:0x00424260,0x099:0x00424F30,
 0x0C3:0x004240C0,0x0DC:0x00424F30,0x0FC:0x00424260,
 0x115:0x00424E00,0x135:0x00424350,0x14E:0x00424FA0,
 0x16E:0x00424180,0x187:0x00424F30,0x1A7:0x00424180,
 0x1C0:0x00424E80,0x1DD:0x004244C0,0x1F8:0x00424460,
 0x211:0x00424F30,0x231:0x00425070,
 0x280:0x00423C14,0x284:0x00423C4D,0x288:0x00423C6B,
 0x28C:0x00423CA4,0x290:0x00423D20,0x294:0x00423CE7,
 0x298:0x00423D59,0x29C:0x00423D92,0x2A0:0x00423DC8,
 0x2A4:0x00423DE3,
}
def verify():
    image,_=pe.verified_target();base,secs=pe.parse_sections(image)
    raw=pe.raw_at(image,base,secs,HEAD,COMPARE)
    assert hashlib.sha256(raw[:BODY]).hexdigest()==SHA_BODY
    assert hashlib.sha256(raw).hexdigest()==SHA_COMPARE
    assert raw[BODY:0x280]==b'\x0f\x1f\x00'
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw[:BODY],HEAD))
    assert len(instructions)==202
    assert instructions[-1].mnemonic=='ret' and instructions[-1].address+instructions[-1].size==HEAD+BODY
    calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in instructions if i.size==5 and i.bytes[0]==0xe8}
    assert calls==E8
    highlow=pe.physical_highlow(image,base,secs)
    data={addr-HEAD:struct.unpack('<I',pe.raw_at(image,base,secs,addr,4))[0]
        for addr in highlow if HEAD<=addr<HEAD+COMPARE}
    assert data==DATA
    assert all(DATA[0x280+4*n]==raw[0x280+4*n] |
        (raw[0x281+4*n]<<8) | (raw[0x282+4*n]<<16) | (raw[0x283+4*n]<<24)
        for n in range(10))
    obj=ROOT/'build/gptweb-screen-boss/ScreenInitialize637.obj'
    body,rel=cf.object_function(obj,SYMBOL,COMPARE)
    actual={(r['offset'],r['type']):r for r in rel}
    required={(off+1,'REL32'):target for off,target in E8.items()}
    required.update({(off,'DIR32'):target for off,target in DATA.items()})
    assert set(actual)==set(required)
    assert len(body)==COMPARE and len(rel)==50
    result=cf.compare(obj,SYMBOL,HEAD,COMPARE)
    assert result['result']=='structural-exact'
    assert result['comparable_bytes']==result['matched_comparable_bytes']==480
    print('PASS immutable native ScreenInf original whole 637B/202-i386 plus 3B alignment +40B switch table')
    print('PASS all 20 original E8 destination roles, all 30 physical PE HIGHLOW addresses including 10 local case entries')
    print('PASS natural C++ compiler contribution 680B, all 50 physical relocation fields and 480/480 ordinary bytes')
    print('Structural diagnostic only; canonical exactness needs the full independently specified relocation unit')
if __name__=='__main__':verify()
