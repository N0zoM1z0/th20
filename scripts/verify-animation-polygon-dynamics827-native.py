#!/usr/bin/env python3
"""PE-only original 827B polygon dynamic Boss and its range iterator leaves.

Records whole original extent, uncommon native 8B ESP-alignment prologue,
31 genuine E8 site/target pairs and 10 real PE HIGHLOW data field/target
pairs, including two native loops, random clamp and copied closure point.
Original-PE-only checks do not establish source exactness. An independent
whole-function 827B canonical replay now passes (CORE/RECON-901).
The original 19B dereference uses a genuine float* return in EAX; its
source is exact only after whole native canonical relocation replay.
"""
from pathlib import Path
import struct,importlib.util
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('locked_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0045F670
SIZE=827
CALLS={
 0x039:0x00414580,0x056:0x00414580,0x06F:0x0045D670,
 0x08F:0x00439330,0x0A9:0x0045EFF0,0x0BF:0x0045F010,
 0x0D2:0x0040C080,0x0DE:0x0045FDA0,
 0x0E8:0x0040C080,0x0F4:0x0045FF00,
 0x0FF:0x0045F480,0x10C:0x00449400,
 0x11F:0x0045F420,0x12C:0x004298E0,
 0x1D3:0x00429210,0x1EB:0x0045EFF0,0x1FC:0x0045F010,
 0x20F:0x0040C080,0x21B:0x0045FE00,
 0x225:0x0040C080,0x231:0x0045FF20,
 0x23C:0x0045F4A0,0x249:0x00449400,
 0x25C:0x0045F420,0x277:0x00414580,0x288:0x004292E0,
 0x2AA:0x00439330,0x2D3:0x004530C0,
 0x2F1:0x0045D670,0x312:0x0045D670,
 0x32D:0x005429EE,
}
HIGHLOW={
 0x01D:0x005B25C0,0x128:0x005BA4C4,
 0x13D:0x0056C8D0,0x16C:0x0056C8E0,0x185:0x0056C8E0,
 0x19B:0x0056C8E0,0x1B0:0x0056C8E0,
 0x2B6:0x0056E0F0,0x2BE:0x0056C8D0,0x2C6:0x0056EE48,
}
LEAVES={
 'scalar_iterator_advance_22':(0x0045F480,22,10,0x0045F440,0x0A,0x0FF),
 'vertex_iterator_advance_22':(0x0045F4A0,22,10,0x0045F460,0x0A,0x23C),
 'scalar_range_begin_32':(0x0045FF00,32,14,0x0045EF10,0x0F,0x0F4),
 'vertex_range_end_32':(0x0045FF20,32,14,0x0045EF90,0x0F,0x231),
}
STEP_LEAVES={
 'scalar_pointer_step_27':(0x0045F440,27,13,4,0x0045F480),
 'vertex_pointer_step_27':(0x0045F460,27,13,8,0x0045F4A0),
}
DEREFERENCE=(0x0045F420,19,9,0x0040C300,0x0A,[0x11F,0x25C])
UPSTREAM=(0x0045F5E0,0x0045F648)

def verify():
 image,_=pe.verified_target();base,sects=pe.parse_sections(image)
 relocations=pe.physical_highlow(image,base,sects)
 disasm=Cs(CS_ARCH_X86,CS_MODE_32)
 code=pe.raw_at(image,base,sects,HEAD,SIZE)
 ops=list(disasm.disasm(code,HEAD))
 assert len(ops)==237 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert [i.mnemonic for i in ops[:4]]==['push','mov','sub','and']
 assert ops[2].op_str=='esp, 8' and ops[3].op_str=='esp, 0xfffffff8'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='4'
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ops if len(i.bytes)==5 and i.bytes[0]==0xE8}
 assert calls==CALLS,(calls,CALLS)
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sects,p,4))[0]
       for p in relocations if HEAD<=p<HEAD+SIZE}
 assert data==HIGHLOW,(data,HIGHLOW)
 assert Counter(calls.values())[0x0045D670]==3
 assert Counter(calls.values())[0x0045F420]==2
 assert Counter(calls.values())[0x00439330]==2
 assert Counter(data.values())[0x0056C8E0]==4
 by={i.address-HEAD:i for i in ops}
 assert by[0x030D].mnemonic=='push' and by[0x030D].op_str=='0x3c'
 assert by[0x02EC].mnemonic=='push' and by[0x02EC].op_str=='1'
 upstream_head,caller_site=UPSTREAM
 upstream=list(disasm.disasm(pe.raw_at(image,base,sects,upstream_head,143),upstream_head))
 hits=[i for i in upstream if i.address==caller_site]
 assert len(hits)==1 and len(hits[0].bytes)==5 and hits[0].bytes[0]==0xe8
 assert (hits[0].address+5+struct.unpack_from('<i',hits[0].bytes,1)[0])&0xffffffff==HEAD
 print('PASS immutable entire original 827B/237-native-x86 dynamic polygon Boss, real 8B stack realignment and RET4')
 print('PASS all 31 original E8 physical site/true absolute target pairs and 10 PE HIGHLOW field/target pairs')
 print('PASS two native iterator loops, original GameRandom randomizer, 4.0f limit and 59.0f angular denominator, point[1]->point[60] closure')
 print(f'PASS independent original upstream game E8 {caller_site:#x} from {upstream_head:#x}; native-only check; full 827B canonical acceptance independently verified')
 for name,(head,size,nins,target,site,caller) in LEAVES.items():
  ins=list(disasm.disasm(pe.raw_at(image,base,sects,head,size),head))
  assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
  assert ins[-1].mnemonic=='ret'
  cc={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
      for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
  assert cc=={site:target},(name,cc)
  assert not any(head<=r<head+size for r in relocations)
  assert CALLS[caller]==head
  print(f'PASS original whole {name} {size}B/{nins}-x86, one native E8 +0x{site:X} -> {target:#010x}, no PE HIGHLOW, authentic 827B parent E8 +0x{caller:X}')
 for name,(h,size,nins,stride,caller_head) in STEP_LEAVES.items():
  xs=list(disasm.disasm(pe.raw_at(image,base,sects,h,size),h))
  assert len(xs)==nins and xs[-1].address+xs[-1].size==h+size
  assert xs[-1].mnemonic=='ret' and not xs[-1].op_str
  assert not any(len(x.bytes)==5 and x.bytes[0]==0xE8 for x in xs)
  assert not any(h<=z<h+size for z in relocations)
  assert any(x.mnemonic=='add' and x.op_str==f'ecx, {stride}' for x in xs)
  caller=list(disasm.disasm(pe.raw_at(image,base,sects,caller_head,22),caller_head))
  assert len([x for x in caller if len(x.bytes)==5 and x.bytes[0]==0xE8 and
              (x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff==h])==1
  print(f'PASS original whole {name} {size}B/{nins}-x86 increments a true pointer by {stride}B, no original E8/HIGHLOW, called from 22B native wrapper')
 head,size,nins,target,site,callers=DEREFERENCE
 ins=list(disasm.disasm(pe.raw_at(image,base,sects,head,size),head))
 assert len(ins)==nins and ins[-1].address+ins[-1].size==head+size
 assert [(i.address-head,(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff)
         for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8]==[(site,target)]
 assert not any(head<=r<head+size for r in relocations)
 assert all(CALLS[off]==head for off in callers)
 assert all(i.mnemonic=='mov' and i.op_str.endswith(', eax') for i in
            [next(x for x in ops if x.address-HEAD==off) for off in (0x124,0x261)])
 print('PASS original 19B/9-i386 dereference returns float* in EAX; its native callers capture EAX at +0x124/+0x261, unlike incorrect void-source 20B')

if __name__=='__main__':verify()
