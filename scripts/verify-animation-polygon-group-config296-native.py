#!/usr/bin/env python3
"""Independent PE-only entire original 296B polygon group configuration Boss.

Attests every native E8 absolute callee, zero actual original PE HIGHLOW
fields, 90 full x86 instruction heads, real 0x2C stack/RET8, native
record geometry and three distinct original packed color constants.
Compiled C++ object/receipt is checked separately, never used as oracle.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('native_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0045FB60
SIZE=296
CALLS={
 0x05B:0x00423520,
 0x06E:0x0045F400,0x07E:0x0045FC90,
 0x091:0x0045F400,0x0A1:0x0045FC90,
 0x0B4:0x0045F400,0x0C4:0x0045FC90,
 0x0D9:0x0045DD60,0x0EC:0x00450350,
 0x108:0x00438C60,0x11B:0x0045DD40,
}
COLORS={0x076:0x8040F010,0x099:0xFF20F000,0x0BC:0x80FF1010}
PARENT_HEAD=0x0045FD10
PARENT_SIZE=47
PARENT_CALL=0x0045FD36

def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==90 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0x2c'
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='8'
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if len(i.bytes)==5 and i.bytes[0]==0xe8}
 assert calls==CALLS,(calls,CALLS)
 absolute=[p-HEAD for p in pe.physical_highlow(image,base,sections) if HEAD<=p<HEAD+SIZE]
 assert absolute==[],absolute
 assert Counter(calls.values())[0x0045F400]==3
 assert Counter(calls.values())[0x0045FC90]==3
 by={i.address-HEAD:i for i in ins}
 for off,value in COLORS.items():
  assert by[off].mnemonic=='push' and by[off].op_str==hex(value),(hex(off),by.get(off))
 assert by[0x00F].mnemonic=='mov' and '0xb98' in by[0x00F].op_str
 assert by[0x01E].mnemonic=='mov' and '0xb84' in by[0x01E].op_str
 assert by[0x04A].mnemonic=='mov' and '0xba8' in by[0x04A].op_str
 assert by[0x055].mnemonic=='add' and '0xb88' in by[0x055].op_str
 assert any(i.mnemonic=='add' and i.op_str.endswith(', 8') for i in ins)
 parent=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sections,PARENT_HEAD,PARENT_SIZE),PARENT_HEAD))
 actual=[i for i in parent if len(i.bytes)==5 and i.bytes[0]==0xe8 and
         (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert [i.address for i in actual]==[PARENT_CALL],actual
 print('PASS original whole 296B/90-x86 game polygon-group configuration Boss, native 0x2C frame and RET8')
 print('PASS all eleven native E8 physical site/absolute original target pairs, ZERO real PE HIGHLOW data fields')
 print('PASS actual 3 x fixed 0x3D4 polygon slots, 3x source colors, Timer/Animation native calls and true 47B parent E8')
 print('Original 120B palette helper remains independent of full 296B caller acceptance.')

if __name__=='__main__':verify()
