#!/usr/bin/env python3
"""Whole original Card tick Boss 875B, HUD clear 32B, and exact Card bit8 leaf.

Strict whole-body + native call/data role proofs, not a prefix or call-count score.
Uses canonical receipts so the pinned MSVC object was compiled from source.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name, file):
    spec=importlib.util.spec_from_file_location(name,R/file)
    m=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m
cf=load('cardtick_coff','scripts/compare-coff-function.py')
pe=load('cardtick_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00486F60
LENGTH=875
SHA='580adb8f5e4f41c29033e2654b23f480e7f8f4dde927bbfb8f3f4f15b4ed986d'
CALLS={
 0x03C:0x004235C0,0x05C:0x00487B90,0x073:0x004235C0,
 0x0F5:0x00423540,0x109:0x004235C0,0x12E:0x004888A0,
 0x140:0x0040FF90,0x147:0x00460850,0x15D:0x004888A0,
 0x16F:0x0040FF90,0x176:0x00460850,0x1BF:0x0044EF90,
 0x1F2:0x0040FF90,0x1F9:0x00460850,0x223:0x0040FF90,
 0x22A:0x00460850,0x26F:0x0044EF90,0x28F:0x00412730,
 0x29C:0x00485660,0x2AE:0x00412730,0x2BB:0x00485660,
 0x2C2:0x0047A2C0,0x2DB:0x00429440,0x2F8:0x004292F0,
 0x307:0x004296E0,0x322:0x004502C0,0x33F:0x00424010,
 0x346:0x00478130,
}
HIGHLOW={
 0x058:0x005C069C,0x150:0x0056FE7C,0x17F:0x0056D7C0,
 0x187:0x0056FE7C,0x206:0x0056CD98,0x233:0x0056D7C0,
 0x23B:0x0056CD98,0x2E8:0x0056FE5C,
}
NATIVE_UI=0x00487B90
UI_SHA='d0c5dc0bf24d68834a4e0f5ad9ac71b6c73523bd993d8359032fd0211a54c3aa'


def main():
    image=cf.verified_target()
    base,sects=pe.parse_sections(image)
    original=pe.raw_at(image,base,sects,HEAD,LENGTH)
    assert len(original)==LENGTH and hashlib.sha256(original).hexdigest()==SHA
    native=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
    assert len(native)==262 and native[-1].address+native[-1].size==HEAD+LENGTH
    assert (native[-1].mnemonic,native[-1].op_str)==('ret','')
    original_calls={ins.address-HEAD:(ins.address+5+struct.unpack_from('<i',ins.bytes,1)[0])&0xffffffff
                    for ins in native if ins.size==5 and ins.bytes[0]==0xe8}
    assert original_calls==CALLS
    actual_highlow={site-HEAD:struct.unpack('<I',pe.raw_at(image,base,sects,site,4))[0]
                    for site in pe.physical_highlow(image,base,sects)
                    if HEAD<=site<HEAD+LENGTH}
    assert actual_highlow==HIGHLOW
    for addr,value in ((0x0056FE7C,96.0),(0x0056CD98,128.0),
                       (0x0056D7C0,448.0),(0x0056FE5C,0.05)):
        assert pe.raw_at(image,base,sects,addr,4)==struct.pack('<f',value)
    # Native main thread callback wrapper, not another claimed authored copy.
    wrapper=pe.raw_at(image,base,sects,0x004885D6,5)
    assert wrapper[0]==0xE8
    assert 0x004885D6+5+struct.unpack('<i',wrapper[1:])[0]==HEAD

    symbol='?update_486f60@NativeCardTickView@th20@@QAEHXZ'
    body,relocations=cf.object_function(R/'build/core1118-canonical/CardTickBoss875.obj',symbol,LENGTH)
    source=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(body),0))
    assert len(body)==875 and len(source)==len(native)==262
    assert len(relocations)==36
    assert sum(x['type']=='REL32' for x in relocations)==28
    assert sum(x['type']=='DIR32' for x in relocations)==8
    covered=set()
    for rel in relocations:
        off=rel['offset'];typ=rel['type'];sym=rel['symbol']
        assert rel['addend']==0
        assert (CALLS[off-1] if typ=='REL32' else HIGHLOW[off])
        if off==0x2E8:assert typ=='DIR32' and sym=='__real@3d4ccccd'
        covered.update(range(off,off+4))
    assert len(covered)==144
    assert all(original[i]==body[i] for i in range(875) if i not in covered)
    # The canonical strict comparator additionally matches each relocation's
    # symbol and the independently pinned ORIGINAL physical destination.
    result=cf.compare_unit('card_tick_boss_875')
    assert result['result']=='exact' and result['matched_bytes']==875
    print('PASS Card tick Boss original 875/875B whole strict exact, 262 i386, 28/28 native E8 sites/targets, 8/8 PE HIGHLOW sites/targets')
    print('PASS all 731/731 ordinary body bytes, exact literal 0.05f, original callback wrapper and canonical build receipt')

    ui=pe.raw_at(image,base,sects,NATIVE_UI,32)
    assert hashlib.sha256(ui).hexdigest()==UI_SHA
    ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(ui,NATIVE_UI))
    assert len(ni)==12 and ni[-1].address+ni[-1].size==NATIVE_UI+32
    assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','')
    assert not any(i.size==5 and i.bytes[0]==0xe8 for i in ni)
    assert not any(NATIVE_UI<=a<NATIVE_UI+32 for a in pe.physical_highlow(image,base,sects))
    assert original_calls[0x5C]==NATIVE_UI
    code,rr=cf.object_function(R/'build/core1118-canonical/CardTickUiClear32.obj',
                               '?clear_ui_flag0_487b90@NativeCardTickUiView@th20@@QAEXXZ',32)
    assert bytes(code)==ui and not rr
    result=cf.compare_unit('card_tick_ui_clear_32')
    assert result['result']=='exact' and result['matched_bytes']==32
    print('PASS Card HUD original 32/32B whole exact, actual +0x3344 bit0 owner, single parent E8 and zero native PE relocations')
    # Existing child was replayed from the updated borrowed-views header;
    # it remains a separate original 23B body, not a folded duplicate.
    result=cf.compare_unit('card_flag8_getter_23')
    assert result['result']=='exact' and result['matched_bytes']==23
    assert original_calls[0x12E]==original_calls[0x15D]==0x004888A0
    print('PASS existing Card flag8 getter 23/23B independently strict exact; two Boss E8 calls both genuine')
    print('PASS one new authored whole-native 875B Boss + one new authored whole-native 32B leaf; zero duplicate credit for pre-existing 23B flag getter')

if __name__=='__main__':main()
