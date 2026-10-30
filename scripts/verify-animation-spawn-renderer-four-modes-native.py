#!/usr/bin/env python3
"""Immutable-original PE check of all four Renderer list-creation methods.

Proves full native body/returns, both real E8 callees, one HIGHLOW,
actual 922B AnimationFile::spawn parent E8, and list offset +0x18.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
p=importlib.util.module_from_spec(sp);sp.loader.exec_module(p)
PARENT=0x00450CB0
CASES=(
 (0x0044B7F0,72,24,0x00411EA0,0x27,0x36,0x3A,0x361,False),
 (0x0044B840,72,24,0x0044A6B0,0x27,0x36,0x3A,0x348,False),
 (0x0044B8E0,75,25,0x00411EA0,0x2A,0x39,0x3D,0x312,True),
 (0x0044B890,75,25,0x0044A6B0,0x2A,0x39,0x3D,0x2DD,True),
)

def verify():
 im,_=p.verified_target();base,secs=p.parse_sections(im);high=p.physical_highlow(im,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
 for head,size,nins,list_target,list_site,global_site,register_site,parent_site,shifted in CASES:
  ins=list(cs.disasm(p.raw_at(im,base,secs,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
  calls={i.address-head:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
  assert calls=={list_site:list_target,register_site:0x0044C8F0},(hex(head),calls)
  data={loc-head:struct.unpack('<I',p.raw_at(im,base,secs,loc,4))[0]
        for loc in high if head<=loc<head+size}
  assert data=={global_site:0x005C0028},(hex(head),data)
  ops={(i.mnemonic,i.op_str) for i in ins}
  assert ('add','eax, 0x4ec') in ops
  assert ('mov','dword ptr [eax + 0x4e8], ecx') in ops
  assert (('add','edx, 0x18') in ops)==shifted
  site=PARENT+parent_site;raw=p.raw_at(im,base,secs,site,5)
  assert raw[0]==0xE8
  target=(site+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
  assert target==head,(hex(site),hex(target),hex(head))
  print(f'PASS original {head:#010x} {size}B/{nins} i386, E8 {list_target:#010x}/0x0044C8F0 and PE HIGHLOW 0x005C0028')
  print(f'PASS actual 922B spawn parent E8 {site:#010x} -> {head:#010x}; secondary list={shifted}')
 print('PASS four distinct native renderer registration paths, hidden AnimationHandle result and original RET8')

if __name__=='__main__':verify()
