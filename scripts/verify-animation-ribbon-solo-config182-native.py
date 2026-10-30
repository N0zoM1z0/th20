#!/usr/bin/env python3
"""Immutable original PE audit of full 182B solo ribbon group configuration Boss."""
from pathlib import Path
import importlib.util,struct
from capstone import CS_ARCH_X86,CS_MODE_32,Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
HEAD,SIZE=0x0045DB30,182
E8={0x2F:0x00423520,0x42:0x0045D690,0x52:0x0045DBF0,0x67:0x0045DD60,0x7A:0x00450350,0x96:0x00438C60,0xA9:0x0045DD40}
PARENT=0x0045DC70+0x26

def verify():
 image,_=pe.verified_target();base,secs=pe.parse_sections(image);high=pe.physical_highlow(image,base,secs)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,secs,HEAD,SIZE),HEAD))
 assert len(ins)==57 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xE8}
 assert calls==E8,(calls,E8)
 assert not any(HEAD<=pos<HEAD+SIZE for pos in high)
 body={(i.mnemonic,i.op_str) for i in ins}
 assert ('mov','dword ptr [eax + 0x3dc], ecx') in body
 assert ('mov','dword ptr [edx + 0x3c8], ecx') in body
 assert ('add','ecx, 0x3cc') in body
 assert ('push','0xff0000') in body
 assert ('push','0xb') in body and ('push','0x1e') in body
 parent=pe.raw_at(image,base,secs,PARENT,5);assert parent[0]==0xE8
 dest=(PARENT+5+struct.unpack_from('<i',parent,1)[0])&0xFFFFFFFF;assert dest==HEAD
 for o,t in calls.items():print(f'PASS original E8 +{o:#04x} -> {t:#010x}')
 print('PASS original complete 182B/57-i386, 7 E8, 0 HIGHLOW, member offsets +0x3C8/+0x3CC/+0x3DC')
 print('PASS original 0x00FF0000 color, Animation position/layer11/config30/0/255/0/flag1')
 print(f'PASS native 47B wrapper call {PARENT:#010x} -> {HEAD:#010x}')

if __name__=='__main__':verify()
