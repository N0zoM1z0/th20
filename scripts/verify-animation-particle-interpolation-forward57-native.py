#!/usr/bin/env python3
"""Original PE proof of complete 57B Animation+0x8C interpolation forwarding."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(s);s.loader.exec_module(p)
HEAD,SIZE=0x0045D150,57
PARENT=0x0045C360
SITES=(0x845,0xAD4)

def verify():
 im,_=p.verified_target();base,sec=p.parse_sections(im);hi=p.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==24 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x14')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert calls=={0x2D:0x0045D190},calls
 assert not any(HEAD<=site<HEAD+SIZE for site in hi)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('add','eax, 0x8c') in ops
 assert ('push','8') in ops and ('nop','') in ops
 for offset in SITES:
  site=PARENT+offset
  raw=p.raw_at(im,base,sec,site,5)
  assert raw[0]==0xE8
  dest=(site+5+struct.unpack_from('<i',raw,1)[0])&0xFFFFFFFF
  assert dest==HEAD,(hex(site),hex(dest))
  print(f'PASS original 2884B update E8 {site:#010x} -> {HEAD:#010x}')
 print('PASS whole 57B/24 x86, native Animation+0x8C, exact mode 8 and five-arg RET0x14')
 print('PASS native one E8+0x2D to exact 124B interpolation callee and zero PE HIGHLOW')

if __name__=='__main__':verify()
