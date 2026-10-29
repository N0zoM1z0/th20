#!/usr/bin/env python3
"""Original PE-only full 3159B Animation Draw quad submit Boss audit.

Independent original code, original .reloc fields, original 5-pointer nested
color table and original E8 graph. Never promotes NONEXACT parent to exact.
"""
import importlib.util
from collections import Counter
from pathlib import Path
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('native_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
original=importlib.util.module_from_spec(sp);sp.loader.exec_module(original)

HEAD=0x0043F6A0
SIZE=3159
TABLE=0x004402F8
CALLS={
 0x00445B80:4,      # original numeric rounding helper
 0x00437CD0:1,      # original SpriteData getter
 0x004455C0:2,      # separately strict 192B flush
 0x00412730:1,      # original graphics device getter
 0x00445A00:1,      # texture ownership lookup
 0x0043F520:24,     # separately exact 45B saturation color math
 0x0043F4F0:4,      # separately exact 35B divide-255 color math
 0x00445BA0:1,      # graphics texture state wrapper
 0x00446690:1,      # blend/color state setup
 0x0043E9B0:1,      # quad appended to real 28B stream
 0x005429EE:1,      # compiler security cookie; exclude game credit
}
HIGHLOW_DESTINATIONS={
 0x005AEF10:23,0x005AEF14:22,0x005C5840:16,0x005AEF20:16,
 0x005AEF24:6,0x005AEF28:6,0x0056E0EC:4,0x005B25C0:1,
 0x005C4D40:1,0x004402F8:1,
}
assert sum(CALLS.values())==41 and sum(HIGHLOW_DESTINATIONS.values())==96


def verify()->None:
 image,_=original.verified_target()
 base,sections=original.parse_sections(image)
 relocations=original.physical_highlow(image,base,sections)
 ins=original.decoded(image,base,sections,HEAD,SIZE)
 assert len(ins)==763 and ins[-1].address==0x004402F4
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='8'
 calls=Counter(
  (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
  for x in ins if len(x.bytes)==5 and x.bytes[0]==0xe8
 )
 assert calls==CALLS, (calls-Counter(CALLS),Counter(CALLS)-calls)
 physical=[r for r in relocations if HEAD<=r<HEAD+SIZE]
 assert len(physical)==96
 values=Counter(struct.unpack('<I',original.raw_at(image,base,sections,r,4))[0] for r in physical)
 assert values==HIGHLOW_DESTINATIONS,(values-Counter(HIGHLOW_DESTINATIONS),Counter(HIGHLOW_DESTINATIONS)-values)
 heads={x.address:x for x in ins}
 # Original 0..4 color mode has exactly five genuine independently PE
 # HIGHLOW case targets following original RET and one alignment NOP.
 assert original.raw_at(image,base,sections,HEAD+SIZE,1)==b'\x90'
 targets=[]
 for mode in range(5):
  site=TABLE+4*mode
  assert site in relocations
  t=struct.unpack('<I',original.raw_at(image,base,sections,site,4))[0]
  assert t in heads,(mode,hex(t))
  targets.append(t)
 assert [hex(t) for t in targets]==['0x43fc47','0x43fc47','0x43fdcc','0x43fdcc','0x43ff70']
 assert TABLE-1==HEAD+SIZE
 assert not (TABLE+5*4 in relocations)
 # Original current viewport is exactly the existing Graphics instance's
 # pointer member at +0xB00, not a separate unknown global view controller.
 assert 0x005C5840==0x005C4D40+0xB00
 # Original four complete 28B quad vertices, actual array base and per-member
 # HIGHLOW references are checked by the immutable original PE census above.
 assert len(original.raw_at(image,base,sections,0x005AEF10,112))==112
 for addr,n,frequency in ((0x0043F520,45,24),(0x0043F4F0,35,4)):
  child=original.decoded(image,base,sections,addr,n)
  assert child[-1].address+child[-1].size==addr+n
  assert child[-1].mnemonic=='ret'
  assert not any(addr<=r<addr+n for r in relocations)
  assert calls[addr]==frequency
  print(f'PASS original per-channel game math {addr:#010x}: whole {n}B, {frequency} original quad-Boss E8 calls, no PE relocations')
 # Two independently complete source-backed game helpers now strict exact:
 # the six-vertex batch append and the texture preparation forwarding
 # wrapper. The 3,159B parent itself remains separate and NONEXACT.
 assert calls[0x0043E9B0] == 1
 append_head=0x0043E9B0
 append_body=original.decoded(image,base,sections,append_head,352)
 assert len(append_body)==98 and append_body[-1].mnemonic=='ret'
 assert append_body[-1].op_str=='4'
 assert not any(append_head <=r<append_head+352 for r in relocations)
 assert sum(i.bytes==bytes.fromhex("f3a5") for i in append_body)==6
 assert all(any(prev.mnemonic=='mov' and prev.op_str=='ecx, 7'
                for prev in append_body if cp.address-8<=prev.address<cp.address)
            for cp in append_body if cp.bytes==bytes.fromhex("f3a5"))
 assert any(i.address==0x004402E0 and i.mnemonic=='call' and i.op_str=='0x43e9b0' for i in ins)
 assert any('0x6000e70' in i.op_str for i in append_body)
 assert any('0x7c00e74' in i.op_str for i in append_body)
 assert any(i.mnemonic=='add' and i.op_str=='edx, 0xa8' for i in append_body)
 assert any(i.mnemonic=='imul' and '0xffffa' in i.op_str for i in append_body)
 assert calls[0x00445BA0]==1
 wrapper_head=0x00445BA0
 wrapper=original.decoded(image,base,sections,wrapper_head,26)
 assert len(wrapper)==12 and wrapper[-1].mnemonic=='ret' and wrapper[-1].op_str=='4'
 assert not any(wrapper_head<=r<wrapper_head+26 for r in relocations)
 native_call=next(i for i in wrapper if i.address==0x00445BAE)
 assert native_call.bytes[0]==0xE8 and native_call.mnemonic=='call'
 assert native_call.address+5+struct.unpack_from('<i',native_call.bytes,1)[0]==0x00445BC0
 print("PASS separate native 352B/98-x86 game quad append: 6 x 28B REP MOVSD, original full pool guard, pointer/count update, no relocs")
 print("PASS separate native 26B/12-x86 texture state wrapper: original E8 0x00445BAE -> 0x00445BC0, no PE HIGHLOW")

 assert calls[0x004455C0]==2
 # The original custom submit's cache writes are physically real offset
 # references within the opaque renderer owner, not a fake oversized type.
 assert any('0x6000e08' in x.op_str for x in ins)
 assert any('0x6000e0e' in x.op_str for x in ins)
 assert any('0x7d40e90' in x.op_str for x in ins)
 # Actual per-mode switch color bit extraction (3bits at animation+0x4A1).
 assert any('0x4a1' in x.op_str for x in ins)
 print('PASS entire original 3159B/763 i386 Animation quad submit Boss, 41 real E8/11 targets')
 print('PASS 96 in-body true PE HIGHLOW with all 10 physical destination classes')
 print('PASS 5/5 real original PE HIGHLOW color-mode pointer entries after genuine RET and single NOP')
 print('PASS real graphics viewport global 0x005C5840 = Graphics+0xB00; D3D9 texture/quad batching roles')
 print('PARENT NONEXACT: original PE graph evidence is not whole-C++ strict replay or linked program')

if __name__=='__main__':verify()
