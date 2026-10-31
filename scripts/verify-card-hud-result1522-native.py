#!/usr/bin/env python3
"""Immutable native Card result Boss PE, 7-way pointer table and complete COFF proof.

Target E8s and PE HIGHLOW are independent static original-only evidence.
No target destination is solved from compiled COFF relocation bytes.
"""
import hashlib
import importlib.util
import struct
import sys
from collections import Counter
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
sp=importlib.util.spec_from_file_location('card_hud1522_native',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(sp);sp.loader.exec_module(pe)
sp=importlib.util.spec_from_file_location('card_hud1522_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(sp);sp.loader.exec_module(coff)
HEAD=0x004B90E0
SIZE=1522
COMPARED=1552
NATIVE_SHA='af638942de7619ec46f71a2adafdea6b612ead352799a29d91a27ee9d650aaa0'
E8={
  0x037: 0x00414580,
  0x03E: 0x0044FCD0,
  0x065: 0x00450C70,
  0x080: 0x00414580,
  0x0CD: 0x00414580,
  0x0D4: 0x0044FCD0,
  0x0E0: 0x00437950,
  0x0FF: 0x00450C70,
  0x11C: 0x00414580,
  0x14B: 0x00414580,
  0x163: 0x0044BD70,
  0x182: 0x00414580,
  0x189: 0x00450120,
  0x1A3: 0x00414580,
  0x1AA: 0x0044FA30,
  0x1DE: 0x00414580,
  0x1E5: 0x0044FCD0,
  0x1FA: 0x00437950,
  0x214: 0x00450C70,
  0x22F: 0x00414580,
  0x24A: 0x00414580,
  0x25A: 0x0044BD70,
  0x270: 0x00414580,
  0x277: 0x0044FCD0,
  0x28C: 0x00437950,
  0x2A6: 0x00450C70,
  0x2C0: 0x00414580,
  0x2DB: 0x00414580,
  0x2EB: 0x0044BD70,
  0x31F: 0x00450C70,
  0x344: 0x00414580,
  0x34B: 0x0044FCD0,
  0x378: 0x00450C70,
  0x39C: 0x00414580,
  0x3DD: 0x00450C70,
  0x409: 0x00414580,
  0x410: 0x0044FCD0,
  0x43D: 0x00450C70,
  0x461: 0x00414580,
  0x489: 0x00414580,
  0x490: 0x0044FCD0,
  0x4BD: 0x00450C70,
  0x4E1: 0x00414580,
  0x50A: 0x00414580,
  0x511: 0x0044FCD0,
  0x53E: 0x00450C70,
  0x562: 0x00414580,
  0x587: 0x00414580,
  0x58E: 0x0044FCD0,
  0x5BB: 0x00450C70,
  0x5DF: 0x00414580,
}
HIGHLOW={
  0x022: 0x004B96D4,
  0x057: 0x00570638,
  0x0DC: 0x005C0698,
  0x1F6: 0x005C0698,
  0x288: 0x005C0698,
  0x311: 0x00570638,
  0x367: 0x00570638,
  0x3CC: 0x00570638,
  0x42C: 0x00570638,
  0x4AC: 0x00570638,
  0x52D: 0x00570638,
  0x5AA: 0x00570638,
  0x5F4: 0x004B9106,
  0x5F8: 0x004B9414,
  0x5FC: 0x004B94D2,
  0x600: 0x004B9553,
  0x604: 0x004B95D3,
  0x608: 0x004B96CC,
  0x60C: 0x004B9651,
}
TABLE_TARGETS=(0x004B9106,0x004B9414,0x004B94D2,0x004B9553,0x004B95D3,0x004B96CC,0x004B9651)
# These source identity relationships are grounded independently in genuine
# native callee bodies and already accepted provider/caller units.
SYMBOL_TARGETS={
 '??A?$array@':0x00414580,
 '?retire@AnimationHandle@':0x0044FCD0,
 '?spawn@AnimationFile@':0x00450C70,
 '?current_file_437950@':0x00437950,
 '?set_digit_44bd70@':0x0044BD70,
 '?hide_leading_450120@':0x00450120,
 '?show_digit_44fa30@':0x0044FA30,
}
def verify():
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    highlow_directory=pe.physical_highlow(image,base,sections)
    physical=pe.raw_at(image,base,sections,HEAD,COMPARED)
    code=physical[:SIZE]
    assert hashlib.sha256(code).hexdigest()==NATIVE_SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
    assert len(ins)==416 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','8')
    calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xE8}
    assert calls==E8
    assert len(E8)==51 and Counter(E8.values())==Counter({
        0x00414580:23,0x00450C70:11,0x0044FCD0:9,0x00437950:3,
        0x0044BD70:3,0x00450120:1,0x0044FA30:1})
    original_data={site-HEAD:struct.unpack_from('<I',physical,site-HEAD)[0]
                   for site in highlow_directory if HEAD<=site<HEAD+COMPARED}
    assert original_data==HIGHLOW
    assert len(HIGHLOW)==19
    assert len([k for k in HIGHLOW if k<SIZE])==12
    assert physical[SIZE:SIZE+2]==b'\x66\x90'
    assert HIGHLOW[0x22]==HEAD+SIZE+2
    assert tuple(struct.unpack_from('<7I',physical,SIZE+2))==TABLE_TARGETS
    assert tuple(HIGHLOW[off] for off in range(SIZE+2,COMPARED,4))==TABLE_TARGETS
    assert all(HEAD<=v<HEAD+SIZE for v in TABLE_TARGETS)
    parent=pe.raw_at(image,base,sections,0x004878B0,602)
    assert hashlib.sha256(parent).hexdigest()=='17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f'
    for parent_off in (0xD0,0x235):
        assert parent[parent_off]==0xE8
        target=0x004878B0+parent_off+5+struct.unpack_from('<i',parent,parent_off+1)[0]
        assert target==HEAD,(hex(parent_off),hex(target))
    print('PASS immutable 1,522B/416 original Card HUD Boss, all 51 native E8/12 body HIGHLOW')
    print('PASS original 2-byte 6690 alignment and 7 genuine switch-pointer HIGHLOW/alias entries (1,552B full)')
    print('PASS 602B whole-exact original Card finish E8 +0xD0/+0x235 to 1,522B result HUD Boss')
    unit=coff.compare_unit('card_hud_spell_result_boss_1522')
    assert unit['result']=='exact' and unit['size']==SIZE and unit['compared_size']==COMPARED
    assert unit['matched_bytes']==SIZE and unit['matched_compared_bytes']==COMPARED
    # Use the PE for relocation roles, never solve an object field from the
    # target. The manifest then independently replays every original byte.
    obj,relocs=coff.object_function(ROOT/unit['object'],'?report_spell_result_4b90e0@NativeCardHudView@th20@@QAEXHH@Z',COMPARED)
    assert len(obj)==COMPARED and len(relocs)==70
    for row in relocs:
        offset=int(row['offset']);sym=str(row['symbol'])
        assert row['addend']==0
        if row['type']=='REL32':
            assert offset>0 and offset-1 in E8
            expected={value for prefix,value in SYMBOL_TARGETS.items() if sym.startswith(prefix)}
            assert expected=={E8[offset-1]},(hex(offset),sym,expected)
        else:
            assert row['type']=='DIR32' and offset in HIGHLOW
            dest=HIGHLOW[offset]
            if offset==0x22:assert sym.startswith('$LN') and dest==HEAD+SIZE+2
            elif offset>=SIZE+2:assert sym.startswith('$LN') and HEAD<=dest<HEAD+SIZE
            elif dest==0x00570638:assert sym.startswith('$SG')
            else:assert dest==0x005C0698 and sym.startswith('?native_card_renderer_')
    print('PASS canonical complete 1,522/1,522 body plus 1,552/1,552 table comparison, all 70 original relocations')
    print('PASS entire Card mode0/1/2/3/4/6 result and 8-digit bonus HUD source; no duplicate callee credit')
if __name__=='__main__':verify()
