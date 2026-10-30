#!/usr/bin/env python3
"""Native PE only full 59B GameController status gate into 150B Renderer update."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD,SIZE=0x00450880,59
E8={0x12:0x00424030,0x21:0x00424060,0x34:0x004497D0}
DIR={0x05:0x005BA828,0x0E:0x005BA828,0x1D:0x005BA828}

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==18 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 e8={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in ins if i.size==5 and i.bytes[0]==0xe8}
 dirs={loc-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,loc,4))[0]
       for loc in hl if HEAD<=loc<HEAD+SIZE}
 assert e8==E8,(e8,E8)
 assert dirs==DIR,(dirs,DIR)
 ops={(i.mnemonic,i.op_str) for i in ins}
 assert ('mov','eax, 1') in ops
 assert ('test','eax, eax') in ops
 assert ('je','0x4508b1') in ops
 for off,target in e8.items():print(f'PASS original E8 +{off:#04x} -> {target:#010x}')
 for off,target in dirs.items():print(f'PASS original HIGHLOW +{off:#04x} -> {target:#010x}')
 print('PASS immutable entire original 59B/18-i386, true GameController gate and fastcall 150B update receiver')

if __name__=='__main__':verify()
