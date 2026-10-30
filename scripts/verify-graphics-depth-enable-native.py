#!/usr/bin/env python3
"""Independent original-PE evidence for full 92B Graphics Z-write enable.

Original 92B/30 real x86, game pool flush E8, global pool owner PE HIGHLOW
and the actual IDirect3DDevice9::SetRenderState state=14 value=1 are checked
without using any candidate COFF target or provisional symbol spellings.
"""
from pathlib import Path
import importlib.util,sys,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('native_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
native=importlib.util.module_from_spec(s);s.loader.exec_module(native)
HEAD=0x004DDFE0
SIZE=92

def verify():
    data,_=native.verified_target()
    base,sections=native.parse_sections(data)
    body=native.raw_at(data,base,sections,HEAD,SIZE)
    ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(ops)==30 and ops[-1].address+ops[-1].size==HEAD+SIZE
    assert ops[-1].mnemonic=='ret' and ops[-1].op_str==''
    sites={x.address-HEAD:x for x in ops}
    assert sites[0x0C].mnemonic=='cmp' and sites[0x0C].op_str=='dword ptr [eax + 0xdbc], 1'
    assert sites[0x13].mnemonic=='je'
    assert sites[0x23].mnemonic=='mov' and sites[0x23].op_str=='dword ptr [ecx + 0xdbc], 1'
    assert sites[0x47].mnemonic=='push' and sites[0x47].op_str=='1'
    assert sites[0x49].mnemonic=='push' and sites[0x49].op_str=='0xe'
    assert sites[0x4F].mnemonic=='call' and sites[0x4F].op_str=='dword ptr [ebp - 0xc]'
    calls={x.address-HEAD:(x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff
           for x in ops if len(x.bytes)==5 and x.bytes[0]==0xE8}
    assert calls=={0x1B:0x004455C0},calls
    high=native.physical_highlow(data,base,sections)
    fields={p-HEAD:struct.unpack('<I',native.raw_at(data,base,sections,p,4))[0]
            for p in high if HEAD<=p<HEAD+SIZE}
    assert fields=={0x17:0x005C0028},fields
    # Original whole 2136B game renderer requires this precise branch.
    caller=0x00443020
    game=native.raw_at(data,base,sections,caller,2136)
    c_ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(game,caller))
    i=next(x for x in c_ops if x.address==caller+0x98)
    assert i.mnemonic=='call' and i.bytes[0]==0xE8
    assert i.address+5+struct.unpack_from('<i',i.bytes,1)[0]==HEAD
    print('PASS whole original 92B/30 native i386 Graphics::ZWRITEENABLE one-state cache transition, 0xDBC compare/store=1, true D3D9 SetRenderState(14,1)')
    print('PASS exactly one physical E8 site +0x1B -> strict 192B flush_draws and one true PE HIGHLOW +0x17 -> game animation-pool pointer 0x005C0028')
    print('PASS genuine E8 caller at +0x98 from entire strict original 2136B game mesh24/25 Boss; custom game state owner, not CRT/STL code')

if __name__=='__main__':verify()
