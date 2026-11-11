#!/usr/bin/env python3
"""Original full 797B Card Draw boss, three distinct 25B AsciiInf setters.

Whole immutable original code SHA, native E8 and PE HIGHLOW relocation roles,
all MSVC COFF bytes/targets and canonical cold receipts are independently
checked; no source-presence or prefix-only matching is given exact credit.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,file):
    spec=importlib.util.spec_from_file_location(name,ROOT/file)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module
coff=load('carddraw797_coff','scripts/compare-coff-function.py')
pe=load('carddraw797_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00487590
SIZE=797
SHA='d2db56d68307f6ab895a94c9b44cc8e73c88a2b11de030d2240882efb453f7e6'
SYM='?draw_487590@NativeCardDrawView@th20@@QAEHXZ'
OBJ=ROOT/'build/core1120-canonical/CardDrawBoss797.obj'
# Original E8 destination addresses, independently disassembled from the
# SHA-pinned target executable. Each key is the E8 instruction offset.
NATIVE_E8={
  0x030:0x0044CED0,0x04A:0x00488B00,0x057:0x00488A00,
  0x05F:0x0045D0E0,0x075:0x00488940,0x0B0:0x00422DD0,
  0x0CA:0x0046CD40,0x0FA:0x00422DD0,0x10A:0x0040DDD0,
  0x119:0x0046CE90,0x147:0x00422DD0,0x151:0x00488850,
  0x179:0x0050FC50,0x196:0x00486E10,0x1B2:0x0040DDD0,
  0x1C1:0x0046CE90,0x1D2:0x0050FC50,0x1EF:0x00486E10,
  0x207:0x0050FC50,0x224:0x00486E10,0x249:0x0046C990,
  0x25C:0x0050FC50,0x279:0x00486E10,0x291:0x0050FC50,
  0x2AE:0x00486E10,0x2D7:0x0046C990,0x2E7:0x00488B00,
  0x2F4:0x00488A00,0x304:0x00488940,0x314:0x005429EE,
}
NATIVE_DATA={
  0x007:0x005B25C0,0x046:0x005C0698,0x053:0x005C0698,
  0x071:0x005C0698,0x096:0x0056FE78,0x0A4:0x0056FE80,
  0x0C6:0x005C0698,0x0E0:0x0056FE78,0x0EE:0x0056FE84,
  0x106:0x0056FDF8,0x115:0x005C0698,0x12D:0x0056FE78,
  0x13B:0x0056FE88,0x14D:0x005BA568,0x175:0x005C6108,
  0x1AE:0x0056FDFC,0x1BD:0x005C0698,0x1CE:0x005C6108,
  0x203:0x005C6108,0x23B:0x0056FE04,0x244:0x005C0698,
  0x258:0x005C6108,0x28D:0x005C6108,0x2C9:0x0056FE10,
  0x2D2:0x005C0698,0x2E3:0x005C0698,0x2F0:0x005C0698,
  0x300:0x005C0698,
}
E8_ROLES={
 '?resolve@AnimationHandle@':0x0044CED0,
 '?set_font_488b00@':0x00488B00,
 '?set_layer_488a00@':0x00488A00,
 '?color_ref_45d0e0@':0x0045D0E0,
 '?set_color_alpha_488940@':0x00488940,
 '??0Vector3@':0x00422DD0,
 '?render_number_46cd40@':0x0046CD40,
 '??0?$basic_string_view@':0x0040DDD0,
 '?render_text_46ce90@':0x0046CE90,
 '?field_70_is_two@':0x00488850,
 '?native_primary_records_50fc50@':0x0050FC50,
 '?record_486e10@':0x00486E10,
 '?render_format_46c990@':0x0046C990,
 '@__security_check_cookie@4':0x005429EE,
}
DATA_ROLES={
 '___security_cookie':0x005B25C0,
 '?native_card_renderer_5c0698@':0x005C0698,
 '?native_card_y_37_56fe78@':0x0056FE78,
 '?native_card_x_266_56fe80@':0x0056FE80,
 '?native_card_x_282_56fe84@':0x0056FE84,
 '?native_card_x_360_56fe88@':0x0056FE88,
 '?session@':0x005BA568,
 '?native_card_records_5c6108@':0x005C6108,
}
ORIGINAL_STRINGS={
 0x106:(0x0056FDF8,b'$\x00'),
 0x1AE:(0x0056FDFC,b'MASTER\x00'),
 0x23B:(0x0056FE04,b'%.2d/99+\x00'),
 0x2C9:(0x0056FE10,b'%.2d/%.2d\x00'),
}
SETTERS=(
  ('card_draw_ascii_font_25',0x00488B00,'373f84ea8dfffcd36c71b5cc4df03a0e377f745ba0fe6cb59d44e358e33e5b3e',
   '?set_font_488b00@NativeCardAsciiDrawView@th20@@QAEXH@Z','eax + 0x1a1e0',0x04A,0x2E7),
  ('card_draw_ascii_layer_25',0x00488A00,'5affdc06ec3161551bc9e70b56bf3a650a0f439896e96d656ff23e4d15cc02b7',
   '?set_layer_488a00@NativeCardAsciiDrawView@th20@@QAEXH@Z','eax + 0x1a1ec',0x057,0x2F4),
  ('card_draw_ascii_alpha_25',0x00488940,'25bd78db0359144c1512e78b54fdd3dc3c4ada038213f069119d2d0e1d64224b',
   '?set_color_alpha_488940@NativeCardAsciiDrawView@th20@@QAEXE@Z','eax + 0x1a1c3',0x075,0x304),
)

def main():
    exe=coff.verified_target()
    base,sections=pe.parse_sections(exe)
    highlow=pe.physical_highlow(exe,base,sections)
    native=pe.raw_at(exe,base,sections,HEAD,SIZE)
    assert len(native)==SIZE and hashlib.sha256(native).hexdigest()==SHA
    ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,HEAD))
    assert len(ni)==221 and ni[-1].address+ni[-1].size==HEAD+SIZE
    assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','')
    native_calls={i.address-HEAD:(i.address+5+struct.unpack('<i',i.bytes[1:5])[0])&0xffffffff
                  for i in ni if i.size==5 and i.bytes[0]==0xe8}
    native_data={a-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sections,a,4))[0]
                 for a in highlow if HEAD<=a<HEAD+SIZE}
    assert len(native_calls)==30 and native_calls==NATIVE_E8
    assert len(native_data)==28 and native_data==NATIVE_DATA
    for off,(address,data) in ORIGINAL_STRINGS.items():
        assert native_data[off]==address
        assert pe.raw_at(exe,base,sections,address,len(data))==data
    for address,value in ((0x0056FE78,37.0),(0x0056FE80,266.0),
                          (0x0056FE84,282.0),(0x0056FE88,360.0)):
        assert pe.raw_at(exe,base,sections,address,4)==struct.pack('<f',value)

    body,relocs=coff.object_function(OBJ,SYM,SIZE)
    ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(body),0))
    assert len(body)==SIZE and len(ci)==len(ni)==221
    assert len(relocs)==58 and sum(r['type']=='REL32' for r in relocs)==30
    assert sum(r['type']=='DIR32' for r in relocs)==28
    assert [i.address for i in ci if i.size==5 and i.bytes[0]==0xe8]==sorted(native_calls)
    mask=set()
    for r in relocs:
        off=r['offset'];type_=r['type'];symbol=r['symbol']
        site=off-1 if type_=='REL32' else off
        target=NATIVE_E8.get(site) if type_=='REL32' else NATIVE_DATA.get(site)
        assert target is not None,(hex(site),type_,symbol)
        assert r['addend']==0
        if type_=='REL32':
            matches=[val for key,val in E8_ROLES.items() if symbol.startswith(key)]
            assert matches==[target],(hex(site),hex(target),symbol,matches)
        elif symbol.startswith('$SG'):
            assert site in ORIGINAL_STRINGS and ORIGINAL_STRINGS[site][0]==target
        else:
            matches=[val for key,val in DATA_ROLES.items() if symbol.startswith(key)]
            assert matches==[target],(hex(site),hex(target),symbol,matches)
        mask.update(range(off,off+4))
    assert len(mask)==232 and all(native[i]==body[i] for i in range(SIZE) if i not in mask)
    check=coff.compare_unit('card_draw_boss_797')
    assert check['result']=='exact' and check['matched_bytes']==SIZE
    print('PASS original Card Draw 797/797B whole strict exact, 221 i386, 30 E8 physical sites/target roles and 28 HIGHLOW sites/target roles')
    print('PASS 565/565 non-relocation ordinary body bytes and four genuine dollar/MASTER/count-format strings')

    for unit,addr,sha,symbol,operand,site1,site2 in SETTERS:
        original=pe.raw_at(exe,base,sections,addr,25)
        assert len(original)==25 and hashlib.sha256(original).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,addr))
        assert len(ins)==10 and ins[-1].address+ins[-1].size==addr+25
        assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
        assert any(operand in i.op_str for i in ins)
        assert not any(i.bytes[0]==0xe8 and i.size==5 for i in ins)
        assert not any(addr<=p<addr+25 for p in highlow)
        assert NATIVE_E8[site1]==NATIVE_E8[site2]==addr
        code,rr=coff.object_function(ROOT/'build/core1120-canonical/CardDrawAsciiSetters75.obj',symbol,25)
        assert bytes(code)==original and not rr
        exact=coff.compare_unit(unit)
        assert exact['result']=='exact' and exact['matched_bytes']==25
        print(f'PASS {unit}: whole original 25/25B, 10 i386, true AsciiInf {operand} and two original 797B parent calls')
    callback=coff.compare_unit('card_draw_callback_13')
    assert callback['result']=='exact' and callback['matched_bytes']==13
    # The 13B draw callback was separately SHA-pinned and currently exact.
    e8=pe.raw_at(exe,base,sections,0x00488686,5)
    assert e8[0]==0xe8 and 0x00488686+5+struct.unpack('<i',e8[1:])[0]==HEAD
    print('PASS native 13B registered Card draw callback remains whole exact and points to the complete accepted 797B Boss')
    print('PASS four newly credited original game heads, 797B+25B+25B+25B=872B; no duplicate old callback credit')
if __name__=='__main__':main()
