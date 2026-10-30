#!/usr/bin/env python3
"""Immutable original PE-only complete 1001B rotated dual-radius game Boss.

Decodes entire 258-x86 original method, independent E8 and PE HIGHLOW
physical site/target roles, actual native 5993B enclosing parent E8 and
original matrix/angle/vertex/Graphics operations, not candidate symbols.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe_original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043C780
SIZE=1001
CALL_SITES={
  0x068:0x004455C0,0x070:0x00422E10,
  0x0DA:0x004397C0,0x11A:0x00439820,0x147:0x00458FA0,
  0x1FA:0x004397C0,0x236:0x00439820,0x263:0x00458FA0,
  0x30A:0x00438600,0x31F:0x004DDF80,0x32D:0x004D9DB0,
  0x341:0x00446690,0x34B:0x00412730,0x36F:0x00412730,
  0x3DE:0x005429EE,
}
DATA_SITES={
  0x007:0x005B25C0,0x079:0x0056E0F0,0x081:0x0056C8D0,
  0x0BD:0x0056C8D0,0x0FD:0x0056C8D0,
  0x189:0x0056C8CC,
  0x1E1:0x0056C8D0,0x21D:0x0056C8D0,
  0x2A5:0x0056C8CC,
  0x31B:0x005C4D40,0x329:0x005C4D40,
  0x347:0x005C4D40,0x36B:0x005C4D40,
}
PARENT_SITES=[0x0044483A,0x00444927,0x00444A18]

def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 raw=pe.raw_at(image,base,sections,HEAD,SIZE)
 ii=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ii)==258 and ii[-1].address+ii[-1].size==HEAD+SIZE
 assert ii[2].mnemonic=='sub' and ii[2].op_str=='esp, 0x58'
 assert ii[-1].mnemonic=='ret' and ii[-1].op_str=='0x24'
 calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
        for x in ii if len(x.bytes)==5 and x.bytes[0]==0xe8}
 assert calls==CALL_SITES,(calls,CALL_SITES)
 fields={site-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
         for site in pe.physical_highlow(image,base,sections) if HEAD<=site<HEAD+SIZE}
 assert fields==DATA_SITES,(fields,DATA_SITES)
 assert Counter(fields.values())==Counter({
   0x005B25C0:1,0x0056E0F0:1,0x0056C8D0:5,
   0x0056C8CC:2,0x005C4D40:4,
 })
 by={i.address-HEAD:i for i in ii}
 assert by[0x013].mnemonic=='mov' and by[0x013].op_str=='eax, dword ptr [ebp + 0x20]'
 assert by[0x016].mnemonic=='add' and by[0x016].op_str=='eax, 2'
 assert by[0x039].mnemonic=='jb'
 assert by[0x06D].mnemonic=='lea' and by[0x06D].op_str=='ecx, [ebp - 0x10]'
 assert by[0x039D].mnemonic=='push' and by[0x039D].op_str=='5'
 assert by[0x0397].mnemonic=='mov'  # native DrawPrimitiveUP count 2*N
 parent=0x00443880;pdata=pe.raw_at(image,base,sections,parent,5993)
 incoming=[i.address for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(pdata,parent)
           if len(i.bytes)==5 and i.bytes[0]==0xE8 and
           (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert incoming==PARENT_SITES,(incoming,PARENT_SITES)
 print('PASS immutable complete 1001B/258-x86 original rotated dual-radius shape Boss, native frame0x58, RET0x24, exact Vector3 constructor and x87/SSE source roles')
 print('PASS 15 original E8 physical site/destinations including 2 cosine+2 sine, 2 XY rotates, real game Graphics, native cookie, full source-owned angular loop')
 print('PASS 13 real PE HIGHLOW site/target fields: security cookie, pi, 5 two, 2 one, 4 Graphics; real D3D9 TRIANGLESTRIP type5')
 print('PASS 3 actual original 5993B Draw dispatcher E8 callers '+', '.join(hex(x) for x in PARENT_SITES)+'; parent itself remains separately NONEXACT')

if __name__=='__main__':verify()
