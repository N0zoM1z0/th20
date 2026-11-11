#!/usr/bin/env python3
"""Independent strict original Card registration/bridge whole-function attestation.

The three physical heads have disjoint original code boundaries; a correct
reconstructed E8 destination is required, not just an E8 at the right site.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name,path):
    spec=importlib.util.spec_from_file_location(name,R/path)
    m=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m
cf=load('cardregistration_cf','scripts/compare-coff-function.py')
pe=load('cardregistration_pe','scripts/verify-animation-draw-boss-native.py')
SPECS=(
  ('card_registration_121',0x00487B10,121,41,
    '291171ffef108b276b58d792a2fded039dc512edd792827bbb7276ba46a46ba8',
    'build/core1119-canonical/CardRegisterCallbacks121.obj',
    '?register_callbacks_487b10@NativeCardSetupView@th20@@QAEHH@Z',
    {0x10:0x00488A20,0x1E:0x0040BBC0,0x2D:0x00412DA0,
     0x3D:0x00412310,0x56:0x004123B0,0x6C:0x00423520},
    {0x1A:0x005BA568,0x37:0x004885D0,0x50:0x00488680}),
  ('card_tick_callback_13',0x004885D0,13,6,
    '4252c6deb271e04cca8d29c3fb3b7ad05f0cb9bf3b66ec72fd012cb4429ac090',
    'build/core1119-canonical/CardCallbackBridges13.obj',
    '?card_tick_callback_4885d0@th20@@YAHPAUNativeCardTickView@1@@Z',
    {0x6:0x00486F60},{}),
  ('card_draw_callback_13',0x00488680,13,6,
    '47116c4f8122744b9b4eed866079a6908916c42fdf551011c91138bef77a7855',
    'build/core1119-canonical/CardCallbackBridges13.obj',
    '?card_draw_callback_488680@th20@@YAHPAUNativeCardDrawView@1@@Z',
    {0x6:0x00487590},{}),
)

def main():
    image=cf.verified_target()
    base,sec=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sec)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for unit,head,size,ninstr,sha,obj,sym,expect_calls,expect_data in SPECS:
        native=pe.raw_at(image,base,sec,head,size)
        assert hashlib.sha256(native).hexdigest()==sha
        ins=list(cs.disasm(native,head))
        assert len(ins)==ninstr and ins[-1].address+ins[-1].size==head+size
        tail=('ret','4') if size==121 else ('ret','')
        assert (ins[-1].mnemonic,ins[-1].op_str)==tail
        actual_calls={i.address-head:(i.address+5+struct.unpack('<i',i.bytes[1:5])[0])&0xffffffff
                      for i in ins if i.size==5 and i.bytes[0]==0xE8}
        actual_data={p-head:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
                     for p in highlow if head<=p<head+size}
        assert actual_calls==expect_calls,(unit,actual_calls,expect_calls)
        assert actual_data==expect_data,(unit,actual_data,expect_data)
        body,rels=cf.object_function(R/obj,sym,size)
        assert len(body)==size
        assert len(rels)==len(expect_calls)+len(expect_data)
        assert sorted((r['offset']-1 if r['type']=='REL32' else r['offset']) for r in rels)==sorted([*expect_calls,*expect_data])
        assert not any(r['addend'] for r in rels)
        covered={i for r in rels for i in range(r['offset'],r['offset']+4)}
        assert all(a==b for i,(a,b) in enumerate(zip(native,body)) if i not in covered)
        result=cf.compare_unit(unit)
        assert result['result']=='exact' and result['matched_bytes']==size
        print(f'PASS {unit}: full native {size}/{size}B, {ninstr} instructions; {len(expect_calls)} pinned original E8 and {len(expect_data)} HIGHLOW sites and destinations')
    # The 121B parent embeds both exact C callback bridge pointers, and
    # the bridges target different physical Card update/draw parents.
    assert SPECS[0][8][0x37]==SPECS[1][1]
    assert SPECS[0][8][0x50]==SPECS[2][1]
    assert SPECS[1][7][0x6]==0x00486F60
    assert SPECS[2][7][0x6]==0x00487590
    print('PASS Card register -> 13B callback -> 875B exact update, independently 13B draw callback -> 797B NONEXACT draw parent')
    print('PASS three distinct newly accepted original game heads /147 total bytes; 797B draw parent not credited')

if __name__=='__main__':main()
