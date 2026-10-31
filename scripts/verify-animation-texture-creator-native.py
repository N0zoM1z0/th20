#!/usr/bin/env python3
"""Immutable PE proof for the complete Renderer texture creation pair.

No original field is solved from candidate relocation values; the native PE
bytes, instruction bounds, E8 graph and HIGHLOW directory define every role.
"""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('renderer_texture_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
cp=importlib.util.spec_from_file_location('renderer_texture_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(cp);cp.loader.exec_module(coff)
SPECS={
 'target':(0x0044C150,139,48,'7af99aae8840f398d452b070ca18f65ebc943e650a715fcfb628487f5dd707dc',
           {0x20:0x00412730,0x59:0x0040C6B0},
           {0x1C:0x005C4D40,0x55:0x0056E250,0x63:0x005C4E2C},
           '?create_render_target_44c150@NativeRendererTextureOwner@th20@@QAEHPAUTextureRecord@2@HH@Z'),
 'dynamic':(0x0044C0B0,155,51,'dd489bdd5a80aca4ee1b88db8b3535ec19b9eded7f19e3ec685ea5b443a81670',
           {0x20:0x00412730,0x6B:0x0040C6B0},
           {0x1C:0x005C4D40,0x39:0x0056E208,0x67:0x0056E250,0x7C:0x0056E22C,0x91:0x0056E22C},
           '?create_dynamic_texture_44c0b0@NativeRendererTextureOwner@th20@@QAEHPAUTextureRecord@2@HHH@Z'),
}
def verify(variant,object_path=None):
    head,size,instruction_count,sha,e8,data,symbol=SPECS[variant]
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    hl=pe.physical_highlow(image,base,sections)
    body=pe.raw_at(image,base,sections,head,size)
    assert hashlib.sha256(body).hexdigest()==sha
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
    assert len(instructions)==instruction_count and instructions[-1].address+instructions[-1].size==head+size
    assert (instructions[-1].mnemonic,instructions[-1].op_str)==('ret', '0xc' if variant=='target' else '0x10')
    calls={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in instructions if i.size==5 and i.bytes[0]==0xe8}
    original_data={a-head:struct.unpack('<I',pe.raw_at(image,base,sections,a,4))[0]
                   for a in hl if head<=a<head+size}
    assert calls==e8,(calls,e8)
    assert original_data==data,(original_data,data)
    assert pe.raw_at(image,base,sections,head+size,5)==b'\xCC'*5
    assert sum(i.mnemonic=='call' and i.op_str.startswith('dword ptr [ebp -') for i in instructions)==1
    print(f'PASS native {variant}: {size}B/{len(instructions)} x86, {len(e8)} E8/{len(data)} HIGHLOW, real ret and 5 INT3')
    if object_path is None:return
    report=coff.compare(object_path,symbol,head,size)
    assert report['result']=='structural-exact',report
    assert report['matched_comparable_bytes']==size-4*(len(e8)+len(data))
    relocs={int(r['offset'],16):(r['type'],int(r['target_field'],16)) for r in report['relocations']}
    expected={k:('DIR32',v) for k,v in data.items()}
    expected.update({k+1:('REL32', (dst-(head+k+5))&0xffffffff) for k,dst in e8.items()})
    assert relocs==expected,(relocs,expected)
    print(f'PASS complete {size}/{size} natural MSVC bytes and {len(expected)} independently attested relocation roles')

if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--variant',choices=SPECS,required=True)
 p.add_argument('--candidate-object',type=Path);a=p.parse_args();verify(a.variant,a.candidate_object)
