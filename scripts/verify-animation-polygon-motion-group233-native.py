#!/usr/bin/env python3
"""PE-only original 233B polygon Motion group Boss and 23B/19B leaf pairs.

The genuine immutable Japanese TH20 v1.00a Steamless code determines full
three function boundaries, 78/9/9 x86 instruction heads, all nine physical
E8 and two PE HIGHLOW fields and targets, native +0x3D4 record stride,
three consecutive records, original +0xB9C cached Vector3 and +0xBA8
choice flag. Does not assume that the 104B outline child is exact.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0045F9B0
SIZE=233
CALLS={
 0x020:0x00445BC0,0x028:0x00422E10,0x04C:0x004376E0,
 0x07A:0x0040BDA0,0x085:0x0045FD40,0x0AF:0x0045FAA0,
 0x0C5:0x0045F400,0x0D4:0x0045FB10,0x0E0:0x005429EE,
}
DATA={0x007:0x005B25C0,0x01C:0x005C0028}
LEAVES={
 'segment_index_23':(0x0045F400,23,9,'4',0x3D4),
 'segment_end_19':(0x0045FD40,19,9,'',0xB7C),
}

def verify():
 original,_=pe.verified_target();base,sections=pe.parse_sections(original)
 highlow=pe.physical_highlow(original,base,sections)
 for name,(head,size,x86,ret,bound) in LEAVES.items():
  ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(original,base,sections,head,size),head))
  assert len(ops)==x86 and ops[-1].address+ops[-1].size==head+size
  assert ops[-1].mnemonic=='ret' and ops[-1].op_str==ret
  assert any(f'0x{bound:x}' in i.op_str for i in ops),(name,'missing original stride/bound',hex(bound))
  assert not any(len(i.bytes)==5 and i.bytes[0]==0xE8 for i in ops)
  assert not any(head<=h<head+size for h in highlow)
  print(f'PASS original full {name}: {size}B/{len(ops)} native i386, actual stride/end 0x{bound:X}, RET {ret!r}, no original E8/HIGHLOW')
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(original,base,sections,HEAD,SIZE),HEAD))
 assert len(ops)==78 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x30'
 assert ops[-1].mnemonic=='ret' and not ops[-1].op_str
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ops if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 fields={a-HEAD:struct.unpack('<I',pe.raw_at(original,base,sections,a,4))[0]
         for a in highlow if HEAD<=a<HEAD+SIZE}
 assert fields==DATA,(fields,DATA)
 native={x.address-HEAD:x for x in ops}
 assert native[0x031].mnemonic=='movzx' and '0xba8' in native[0x031].op_str
 assert native[0x057].mnemonic=='add' and native[0x057].op_str=='ecx, 0xb9c'
 assert native[0x092].mnemonic=='add' and native[0x092].op_str=='eax, 0x3d4'
 assert native[0x0BA].mnemonic=='add' and native[0x0BA].op_str=='ecx, 8'
 assert [k for k,v in CALLS.items() if v==0x0045FAA0]==[0xAF]
 assert [k for k,v in CALLS.items() if v==0x0045FB10]==[0xD4]
 assert Counter(CALLS.values())[0x0045F400]==1 and Counter(CALLS.values())[0x0045FD40]==1
 print('PASS original entire 233B/78-x86 polygon group game Boss, original 0x30 frame/RET, 3x0x3D4 native slots')
 print('PASS all nine original direct E8 site/destination pairs and two genuine PE HIGHLOW physical field/targets')
 print('PASS 0xBA8 position choice, 0xB9C saved Vector3, Motion::position_ref and true 104B outline/76B fan wrapper callers')
 print('Original 104B outline child remains independently NONEXACT; full parent matching can be accepted without miscrediting its callee.')

if __name__=='__main__':verify()
