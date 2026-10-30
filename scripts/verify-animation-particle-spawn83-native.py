#!/usr/bin/env python3
"""Original 83B/30-x86 6-param animation spawn wrapper and four parent E8."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
HEAD,SIZE=0x0045D210,83
PARENT=0x0045C360
SITES=(0x227,0x28A,0x2FC,0x37A)

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hl=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==30 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x18')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x45:0x00450CB0},calls
 assert not any(HEAD<=loc<HEAD+SIZE for loc in hl)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('cmp','dword ptr [ebp + 0x1c], 1') in ops
 assert ('mov','dword ptr [ebp - 4], 0x10') in ops
 assert ('mov','dword ptr [ebp - 4], 0') in ops
 assert ('push','-1') in ops
 assert ('push','0') in ops
 for off in SITES:
  site=PARENT+off;raw=p.raw_at(im,base,sec,site,5);assert raw[0]==0xe8
  dest=(site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert dest==HEAD,(hex(site),hex(dest))
  print(f'PASS original 2884B Update parent E8 {site:#010x} -> {HEAD:#010x}')
 print('PASS whole original 83B/30-i386 6-argument wrapper, one E8 to native 922B spawn 0x450CB0')
 print('PASS special mode 1 -> flag16 else zero; original return output pointer, no HIGHLOW')

if __name__=='__main__':verify()
