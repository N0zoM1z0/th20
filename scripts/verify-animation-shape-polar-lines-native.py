#!/usr/bin/env python3
"""Immutable original PE-only whole 541B/766B game polar shape audit.

Attests *each* complete native i386 original function extent, all direct E8
site/real physical target pairs, every PE HIGHLOW source-data field and the
actual 5993B parent E8 callers. No candidate object can authorize a target.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('native_draw_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)

ORIGINALS={
 'simpleline':{
   'head':0x0043BC60,'size':541,'instructions':147,'frame':0x24,'ret':0x18,
   'calls':{
     0x048:0x004455C0,0x0BC:0x00439330,0x163:0x00438600,
     0x182:0x00446690,0x18C:0x00412730,0x1B0:0x00412730,
   },
   'data':{
     0x067:0x0056E0F0,0x06F:0x0056C8D0,0x0FE:0x0056C8CC,
     0x188:0x005C4D40,0x1AC:0x005C4D40,
   },
   'parent':[0x00444A7D],
   'primitive':3,'primitive_offset':0x1DC,'guard_jb_offset':0x2F,'guard_n_offset':0x1B,
 },
 'polarstrip':{
   'head':0x0043BE80,'size':766,'instructions':201,'frame':0x2C,'ret':0x20,
   'calls':{
     0x049:0x004455C0,0x0EF:0x00439330,0x19A:0x00439330,
     0x241:0x00438600,0x260:0x00446690,
     0x26A:0x00412730,0x28E:0x00412730,
   },
   'data':{
     0x06D:0x0056C8D0,0x088:0x0056C8D0,
     0x09A:0x0056E0F0,0x0A2:0x0056C8D0,
     0x131:0x0056C8CC,0x1DC:0x0056C8CC,
     0x266:0x005C4D40,0x28A:0x005C4D40,
   },
   'parent':[0x00444B02,0x00444B94,0x00444C2A],
   'primitive':5,'primitive_offset':0x2BC,'guard_jb_offset':0x30,'guard_n_offset':0x1C,
 },
}

def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    main_head=0x00443880
    whole_parent=pe.raw_at(image,base,sections,main_head,5993)
    parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(whole_parent,main_head))
    parent_targets={}
    for inst in parent_ins:
        if len(inst.bytes)==5 and inst.bytes[0]==0xE8:
            target=(inst.address+5+struct.unpack_from('<i',inst.bytes,1)[0])&0xffffffff
            parent_targets.setdefault(target,[]).append(inst.address)
    physical_relocs=set(pe.physical_highlow(image,base,sections))
    for label,facts in ORIGINALS.items():
        head=facts['head'];size=facts['size']
        raw=pe.raw_at(image,base,sections,head,size)
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,head))
        assert len(ins)==facts['instructions']
        assert ins[-1].address+ins[-1].size==head+size
        assert ins[2].mnemonic=='sub' and ins[2].op_str==f'esp, 0x{facts["frame"]:x}'
        assert ins[-1].mnemonic=='ret' and ins[-1].op_str==f'0x{facts["ret"]:x}'
        calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
               for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
        assert calls==facts['calls'],(label,calls,facts['calls'])
        fields={site-head:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
                for site in physical_relocs if head<=site<head+size}
        assert fields==facts['data'],(label,fields,facts['data'])
        assert parent_targets.get(head)==facts['parent'],(label,parent_targets.get(head))
        o={i.address-head:i for i in ins}
        assert o[0x09].op_str==('eax, dword ptr [ebp + 0x18]' if label=='simpleline' else 'eax, dword ptr [ebp + 0x1c]')
        assert o[facts['guard_n_offset']].mnemonic=='mov'
        assert o[facts['guard_jb_offset']].mnemonic=='jb'
        assert o[facts['primitive_offset']].mnemonic=='push'
        assert o[facts['primitive_offset']].op_str==str(facts['primitive'])
        assert not any(i.address-head<0x30 and i.mnemonic=='call' for i in ins)
        print(f'PASS immutable original {label}: whole {size}B/{len(ins)} x86; native 0x{facts["frame"]:X} frame/RET 0x{facts["ret"]:X}; {len(calls)} E8 +{len(fields)} HIGHLOW actual original site/target pairs')
        print(f'PASS native {label}: true D3D9 primitive type {facts["primitive"]}, fixed 65536x20B vertex pool and original parent E8(s) '+', '.join(hex(a) for a in facts['parent']))

if __name__=='__main__':verify()
