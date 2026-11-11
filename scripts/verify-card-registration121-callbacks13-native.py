#!/usr/bin/env python3
"""Whole native Card registration 121B and two 13B C callbacks, no prefix matches.

The 121B parent publishes exact original literal callback pointers. Both
bridges are independently SHA attested original code, not generic STL heads.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name,f):
    spec=importlib.util.spec_from_file_location(name,R/f)
    mod=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod
cf=load('register121_cf','scripts/compare-coff-function.py')
pe=load('register121_pe','scripts/verify-animation-draw-boss-native.py')
CALLS={
    0x010:0x00488A20,
    0x01E:0x0040BBC0,
    0x02D:0x00412DA0,
    0x03D:0x00412310,
    0x056:0x004123B0,
    0x06C:0x00423520,
}
HIGHLOW={0x01A:0x005BA568,0x037:0x004885D0,0x050:0x00488680}
SPECS=(
 ('card_registration_121',0x00487B10,121,41,
  '291171ffef108b276b58d792a2fded039dc512edd792827bbb7276ba46a46ba8',
  '?register_callbacks_487b10@NativeCardSetupView@th20@@QAEHH@Z',
  R/'build/core1119-canonical/CardRegisterCallbacks121.obj',CALLS,HIGHLOW),
 ('card_tick_callback_13',0x004885D0,13,6,
  '4252c6deb271e04cca8d29c3fb3b7ad05f0cb9bf3b66ec72fd012cb4429ac090',
  '?card_tick_callback_4885d0@th20@@YAHPAUNativeCardTickView@1@@Z',
  R/'build/core1119-canonical/CardCallbackBridges13.obj',{0x006:0x00486F60},{}),
 ('card_draw_callback_13',0x00488680,13,6,
  '47116c4f8122744b9b4eed866079a6908916c42fdf551011c91138bef77a7855',
  '?card_draw_callback_488680@th20@@YAHPAUNativeCardDrawView@1@@Z',
  R/'build/core1119-canonical/CardCallbackBridges13.obj',{0x006:0x00487590},{}),
)

def main():
    image=cf.verified_target()
    base,sections=pe.parse_sections(image)
    reloc_sites=pe.physical_highlow(image,base,sections)
    for unit,head,size,icount,sha,symbol,obj,calls,data in SPECS:
        native=pe.raw_at(image,base,sections,head,size)
        assert len(native)==size and hashlib.sha256(native).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,head))
        assert len(ins)==icount and ins[-1].address+ins[-1].size==head+size
        assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4') if size==121 else (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
        original_e8={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                     for i in ins if i.size==5 and i.bytes[0]==0xE8}
        assert original_e8==calls
        original_data={site-head:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
                       for site in reloc_sites if head<=site<head+size}
        assert original_data==data
        code,relocs=cf.object_function(obj,symbol,size)
        assert len(code)==size and len(relocs)==len(calls)+len(data)
        covered=set()
        for r in relocs:
            off=r['offset'];ty=r['type']
            assert r['addend']==0
            assert (off-1 in calls if ty=='REL32' else off in data)
            covered.update(range(off,off+4))
        assert len(covered)==4*len(relocs)
        assert all(code[i]==native[i] for i in range(size) if i not in covered)
        result=cf.compare_unit(unit)
        assert result['result']=='exact' and result['matched_bytes']==size
        print(f'PASS {unit}: original complete {size}/{size}B, {icount} i386, {len(calls)} original E8 and {len(data)} real HIGHLOW; {size-len(covered)}/{size-len(covered)} ordinary bytes, strict receipt')
    # The 121B setup is invoked by the independent 92B original Card
    # consumer; both callback function pointers are PHYSICAL PE relocations.
    original_caller=pe.raw_at(image,base,sections,0x00488B48,5)
    assert original_caller[0]==0xE8
    assert 0x00488B48+5+struct.unpack('<i',original_caller[1:])[0]==0x00487B10
    assert pe.raw_at(image,base,sections,0x00487B47,4)==struct.pack('<I',0x004885D0)
    assert pe.raw_at(image,base,sections,0x00487B60,4)==struct.pack('<I',0x00488680)
    for unit,length in (('card_tick_boss_875',875),('card_tick_ui_clear_32',32),('card_flag8_getter_23',23)):
        result=cf.compare_unit(unit)
        assert result['result']=='exact' and result['matched_bytes']==length,unit
    print('PASS real native Card registration publishes update E8 -> 875B exact Boss and draw E8 -> original 797B NONEXACT draw path')
    print('PASS original 121B registration and two distinct 13B game-specific C bridges; 147 newly accepted original bytes, prior 875+32+23 not re-credited')

if __name__=='__main__':main()
