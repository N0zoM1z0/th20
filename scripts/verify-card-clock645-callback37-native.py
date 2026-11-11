#!/usr/bin/env python3
"""Strict original Card clock Boss 645B and 37B C callback, full physical proof."""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(n,path):
    spec=importlib.util.spec_from_file_location(n,ROOT/path)
    m=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m
cf=load('clock645_cf','scripts/compare-coff-function.py')
pe=load('clock645_pe','scripts/verify-animation-draw-boss-native.py')
CALLS={
 0x027:0x0041CB10,0x072:0x0041CB10,0x0B8:0x0054FFA0,
 0x12A:0x00550130,0x132:0x00543310,0x15E:0x00550130,
 0x193:0x00488990,0x1BB:0x00488830,0x1D5:0x00474D60,
 0x1E7:0x00488740,0x213:0x00474D60,0x225:0x00488770,
 0x253:0x004885E0,0x266:0x00488990,
}
DATA={
 0x023:0x005B6758,0x06E:0x005B6758,0x09C:0x0056FE60,
 0x0E2:0x0056FE60,0x0EA:0x0056FE68,0x108:0x0056FE60,
 0x17D:0x0056FE70,0x1B7:0x005BA828,0x1D1:0x005BA568,
 0x1E3:0x005C60FC,0x20F:0x005BA568,0x221:0x005C60FC,
}
SYMBOL_TARGETS={
 '?current_seconds_41cb10@':0x0041CB10,
 '_fmod':0x0054FFA0,'_floor':0x00550130,
 '__ftol2_sse_excpt':0x00543310,
 '?encode_time@Card@':0x00488990,
 '?restart@GameController@':0x00488830,
 '?clamped_field_1f4@Session@':0x00474D60,
 '?primary_record_488740@':0x00488740,
 '?alternate_record_488770@':0x00488770,
 '?invalid_encoded_time@Card@':0x004885E0,
}
DATA_TARGETS={
 '?native_card_window_time_5b6758@':0x005B6758,
 '?native_card_tick_seconds_56fe60@':0x0056FE60,
 '?native_card_double_two_56fe68@':0x0056FE68,
 '?native_card_double_hundred_56fe70@':0x0056FE70,
 '?current_game_controller@':0x005BA828,
 '?session@':0x005BA568,
 '?native_card_play_5c60fc@':0x005C60FC,
}
SPECS=(
 ('card_clock_boss_645',0x004872D0,645,164,
  '9e7b7674f89795cf5c67db7779ca48fd470fa1d06fe7c023418f6060ca3f95fe',
  'build/core1121-canonical/CardClockBoss645.obj',
  '?process_clock_4872d0@NativeCardClockView@th20@@QAEXXZ',CALLS,DATA),
 ('card_clock_callback_37',0x00487560,37,15,
  '5c138796ce302ea43cc3e97829b34f5bd9f18194f5757739dde41bc876b5e2ac',
  'build/core1121-canonical/CardClockCallback37.obj',
  '?card_clock_update_487560@th20@@YAXXZ',
  {0x05:0x00478EA0,0x13:0x00478EA0,0x1D:0x004872D0},{}),
)
def main():
    image=cf.verified_target()
    base,sections=pe.parse_sections(image)
    fields=pe.physical_highlow(image,base,sections)
    for unit,h,n,num,sha,obj,sym,expected_calls,expected_data in SPECS:
        native=pe.raw_at(image,base,sections,h,n)
        assert len(native)==n and hashlib.sha256(native).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,h))
        assert len(ins)==num and ins[-1].address+ins[-1].size==h+n
        assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
        calls={i.address-h:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
               for i in ins if i.size==5 and i.bytes[0]==0xe8}
        data={p-h:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
              for p in fields if h<=p<h+n}
        assert calls==expected_calls and data==expected_data
        source,rr=cf.object_function(ROOT/obj,sym,n)
        assert len(source)==n and len(rr)==len(calls)+len(data)
        assert sum(r['type']=='REL32' for r in rr)==len(calls)
        mask={i for r in rr for i in range(r['offset'],r['offset']+4)}
        assert len(mask)==4*len(rr)
        assert all(native[i]==source[i] for i in range(n) if i not in mask)
        for r in rr:
            kind=r['type'];offset=r['offset'];site=offset-1 if kind=='REL32' else offset
            target=calls.get(site) if kind=='REL32' else data.get(site)
            assert target and r['addend']==0
            if n==645:
                expected=[v for prefix,v in (SYMBOL_TARGETS if kind=='REL32' else DATA_TARGETS).items()
                          if r['symbol'].startswith(prefix)]
            else:
                assert kind=='REL32'
                expected=[v for prefix,v in
                          {'?card@':0x00478EA0,'?process_clock_4872d0@':0x004872D0}.items()
                          if r['symbol'].startswith(prefix)]
            assert expected==[target],(unit,hex(site),r['symbol'],hex(target),expected)
        result=cf.compare_unit(unit)
        assert result['result']=='exact' and result['matched_bytes']==n
        print(f'PASS {unit}: original {n}/{n}B whole exact, {num} instructions, {len(calls)} E8 and {len(data)} PE HIGHLOW targets at all original physical sites')
    # The original emits a real FWAIT after the exception-mode MSVC
    # __ftol2_sse_excpt call. The source pragma changes floating exception
    # semantics, not the function length through manufactured padding.
    image_call=pe.raw_at(image,base,sections,0x004872D0+0x132,5)
    assert image_call[0]==0xe8 and 0x004872D0+0x137+struct.unpack('<i',image_call[1:])[0]==0x00543310
    assert pe.raw_at(image,base,sections,0x004872D0+0x137,1)==b'\x9b'
    for addr,value in ((0x0056FE60,0.0167),(0x0056FE68,2.0),(0x0056FE70,100.0)):
        assert pe.raw_at(image,base,sections,addr,8)==struct.pack('<d',value)
    assert CALLS[0x132]==0x00543310 and SPECS[1][7][0x1D]==0x004872D0
    print('PASS authentic MSVC floating-exception FWAIT and __ftol2_sse_excpt, original 0.0167/2.0/100.0 time constants')
    print('PASS two new separate whole-native game heads and 682 original bytes; no 346B clock helper or CRT duplicate credit')
if __name__=='__main__':main()
