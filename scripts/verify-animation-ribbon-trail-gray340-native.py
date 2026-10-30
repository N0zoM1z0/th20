#!/usr/bin/env python3
"""Original PE proof for the entire 340B 64-point gray-ribbon config Boss."""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045E240,340
CALLS={0x18:0x0045D670,0x32:0x0045D670,0x52:0x004298B0,0x6B:0x00423520,
       0xA6:0x00414580,0xD6:0x00414580,0x102:0x00414580,
       0x128:0x0045DD60,0x13B:0x00450350,0x146:0x0045E590}
DATA={0x44:0x0056E0F0,0x4E:0x005BA4C4}
PARENT_E8=0x0045E520+0x26

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hi=pe.physical_highlow(im,base,sec)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(im,base,sec,HEAD,SIZE),HEAD))
 assert len(ins)==101 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={pos-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,pos,4))[0] for pos in hi if HEAD<=pos<HEAD+SIZE}
 assert calls==CALLS,(calls,CALLS)
 assert data==DATA,(data,DATA)
 native={(i.mnemonic,i.op_str) for i in ins}
 assert ('push','0xff505050') not in native
 assert ('mov','dword ptr [eax], 0xff505050') in native
 assert ('cmp','dword ptr [ebp - 8], 0x40') in native
 assert ('push','0x13') in native
 assert ('push','1') in native
 assert struct.unpack('<f',pe.raw_at(im,base,sec,0x0056E0F0,4))[0]>3.14
 raw=pe.raw_at(im,base,sec,PARENT_E8,5);assert raw[0]==0xe8
 target=(PARENT_E8+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
 assert target==HEAD,(hex(PARENT_E8),hex(target))
 for off,t in calls.items():print(f'PASS original E8 +{off:#05x} -> {t:#010x}')
 for off,t in data.items():print(f'PASS original HIGHLOW +{off:#05x} -> {t:#010x}')
 print('PASS whole original 340B/101-x86 gray ribbon config, 10 E8/2 HIGHLOW, 64 color cells')
 print('PASS original 47B parent, two-argument RET8 ABI, gray 0xFF505050, layer19 and zero flag')

if __name__=='__main__':verify()
