#!/usr/bin/env python3
"""Audit the complete 1896B Card start, owned EH and canonical children."""
import argparse
import hashlib
import importlib.util
import struct
import re
import subprocess
import sys
from pathlib import Path
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,filename):
    spec=importlib.util.spec_from_file_location(name,ROOT/filename)
    mod=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod
pe=load('card1896_pe','scripts/verify-animation-draw-boss-native.py')
coff=load('card1896_coff','scripts/compare-coff-function.py')
HEAD=0x00487C30
SIZE=1896
SHA='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
SYM='?start_spell@Card@th20@@QAEXHPBDHH@Z'
CHILDREN={
    0x0AB:0x004888C0,
    0x1D6:0x00478130,
    0x213:0x00437950, # real Renderer file getter
    0x249:0x00470670, # real, separate shared text file getter
    0x293:0x00437950,
    0x30D:0x00486B70,
    0x325:0x00486800,
    0x330:0x00470180,
    0x33F:0x0046ADE0,
    0x68D:0x00488960,
    0x746:0x00449240, # PMR name lifetime ends after all scene work
}
# These are independent original physical destination identities, not
# displacements copied from the candidate under test.
CALL_ROLE_TARGETS={
    '??4Timer@':0x00423520, '_strcpy_s':0x00548610,
    '?clear_capture_effect_flag_4888c0@':0x004888C0,
    '?is_paused_488800@':0x00488800,
    '?field_70_is_two@':0x00488850,
    '?native_primary_records_50fc50@':0x0050FC50,
    '?record_486e10@':0x00486E10,
    '?increment_attempt_488590@':0x00488590,
    '?secondary_488700@':0x00488700,
    '?start_spell_effects_488a60@':0x00488A60,
    '?bomb_controller@':0x00478040,
    '?active_478130@':0x00478130,
    '?current_file_437950@':0x00437950,
    '?spawn@AnimationFile@':0x00450C70,
    '?text_animation_file@AsciiInf@':0x00470670,
    '?__autoclassinit2@':0x0040C080,
    '??0?$basic_string@':0x0046A830,
    '?resolve@AnimationHandle@':0x0044CED0,
    '??0NativeCardTextPayload@':0x00486B70,
    '??$?0UNativeCardTextPayload@':0x00486800,
    '?enqueue_470180@':0x00470180,
    '??1NativeCardTextPayload@':0x0046ADE0,
    '?request_effect@SoundInf@':0x00426D70,
    '?effect_info@Context@':0x0041CAD0,
    '?animation_file@EffectInfo@':0x0045D100,
    '?enemy_controller@Context@':0x00412730,
    '?selected@EnemyController@':0x00485660,
    '?position_ref@Enemy@':0x0047A2C0,
    '??0Vector3@':0x00422DD0,
    '?set_position@AnimationHandle@':0x004502C0,
    '?find_child@AnimationHandle@':0x0044C670,
    '?variables@Animation@':0x0045D0C0,
    '?clamped_field_1f4@Session@':0x00474D60,
    '?mode@Session@':0x004640A0,
    '?enemy_controller@th20@@':0x00478060,
    '?animation_file@EnemyController@':0x004AAE10,
    '?set_spell_flag9_488960@':0x00488960,
    '??1?$basic_string@':0x00449240,
    '@__security_check_cookie@4':0x005429EE,
}
# All 26 original PE HIGHLOW locations and destinations are immutable.
NATIVE_DATA={
  0x006:0x00569248, 0x018:0x005B25C0, 0x0B3:0x005C60FC,
  0x0C5:0x005BA568, 0x0ED:0x005C6108, 0x124:0x005C6108,
  0x152:0x005C6108, 0x183:0x005C6108, 0x1B2:0x005C06A4,
  0x20F:0x005C0698, 0x245:0x005C0698, 0x269:0x0056FE1C,
  0x28F:0x005C0698, 0x32C:0x005C0698, 0x34A:0x005BA830,
  0x379:0x0056EC84, 0x4EF:0x005BA568, 0x4FB:0x005BA568,
  0x56E:0x0056EC84, 0x5B2:0x005C6110, 0x5E8:0x005C6110,
  0x625:0x005C6110, 0x671:0x005C6110, 0x699:0x005C6110,
  0x6CA:0x005C6110, 0x702:0x005C6110,
}
DATA_ROLE_TARGETS={
  '__ehhandler$':{0x00569248}, '___security_cookie':{0x005B25C0},
  '?native_card_play_5c60fc@':{0x005C60FC},
  '?session@':{0x005BA568},
  '?native_card_records_5c6108@':{0x005C6108},
  '?native_card_hud_5c06a4@':{0x005C06A4},
  '?native_card_renderer_5c0698@':{0x005C0698},
  '$SG':{0x0056FE1C,0x0056EC84},
  '?process_sound@':{0x005BA830},
  '?native_card_script_table_5c6110@':{0x005C6110},
}
def verify_eh_metadata(obj, image, base, sections):
    # Establish the owned code address without reading the root's EH field.
    code, mask = bytearray(), set()
    for name, size in (('__unwindfunclet$' + SYM + '$0', 8),
                       ('__unwindfunclet$' + SYM + '$1', 16),
                       ('__ehhandler$' + SYM, 42)):
        body, relocs = coff.object_function(obj, name, size)
        for r in relocs:
            mask.update(range(len(code) + r['offset'], len(code) + r['offset'] + 4))
        code.extend(body)
    hits = []
    for name, _, rva, length, offset in sections:
        if name != b'.text':
            continue
        area, start = image[offset:offset + length], 0
        while (start := area.find(code[:4], start)) >= 0:
            if all(area[start + i] == b for i, b in enumerate(code) if i not in mask):
                hits.append(base + rva + start)
            start += 1
    assert hits == [0x00569230]
    symbol = '__ehfuncinfo$' + SYM
    rows = subprocess.check_output(['objdump', '-t', str(obj)], text=True).splitlines()
    row = next(line for line in rows if line.endswith(' ' + symbol))
    match = re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ', row)
    assert match and int(match[2], 16) == 16
    raw = obj.read_bytes()
    header = 20 + 40 * (int(match[1]) - 1)
    size, offset, reloc_offset = struct.unpack_from('<III', raw, header + 16)
    count = struct.unpack_from('<H', raw, header + 32)[0]
    assert size == 52 and count == 3
    data = bytearray(raw[offset:offset + size])
    sym_offset, sym_count = struct.unpack_from('<II', raw, 8)
    strings = raw[sym_offset + sym_count * 18:]
    expected = ((4, 0x00569230, '__unwindfunclet$' + SYM + '$0'),
                (12, 0x00569238, '__unwindfunclet$' + SYM + '$1'),
                (24, 0x005AA6A4, '__unwindtable$' + SYM))
    for index, (field, target, name) in enumerate(expected):
        actual_field, sym_index, kind = struct.unpack_from('<IIH', raw, reloc_offset + 10 * index)
        actual_name = coff.coff_name(raw[sym_offset + sym_index * 18:][:8], strings)
        assert (actual_field, kind, actual_name) == (field, 6, name)
        assert struct.unpack_from('<I', data, field)[0] == 0
        struct.pack_into('<I', data, field, target)
    # Cleanup targets are independently anchored above. Mask only the map's
    # self-pointer when locating FuncInfo, rather than solving its handler field.
    hits = []
    for name, _, rva, length, offset in sections:
        if name != b'.rdata':
            continue
        area, start = image[offset:offset + length], 0
        while (start := area.find(data[:24], start)) >= 0:
            if all(area[start + i] == b for i, b in enumerate(data) if not 24 <= i < 28):
                hits.append(base + rva + start)
            start += 1
    assert hits == [0x005AA6A4]
    assert data == pe.raw_at(image, base, sections, 0x005AA6A4, size)
    highlow = {address - 0x005AA6A4 for address in pe.physical_highlow(image, base, sections)
               if 0x005AA6A4 <= address < 0x005AA6A4 + size}
    assert highlow == {field for field, _, _ in expected}
    print('PASS complete 52B two-state EH metadata, both cleanup actions and all three DIR32 fields')

def verify(candidate):
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    original=pe.raw_at(image,base,sections,HEAD,SIZE)
    assert hashlib.sha256(original).hexdigest()==SHA
    native=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
    assert len(native)==512 and native[-1].address+native[-1].size==HEAD+SIZE
    assert (native[-1].mnemonic,native[-1].op_str)==('ret','0x10')
    original_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                    for i in native if i.size==5 and i.bytes[0]==0xe8}
    native_data={site-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
                 for site in pe.physical_highlow(image,base,sections) if HEAD<=site<HEAD+SIZE}
    assert len(original_calls)==62 and native_data==NATIVE_DATA
    for off,dest in CHILDREN.items():assert original_calls[off]==dest,(hex(off),hex(original_calls[off]))
    assert pe.raw_at(image,base,sections,0x0056FE1C,5)==b'text\0'
    assert pe.raw_at(image,base,sections,0x0056EC84,7)==b'effect\0'
    print('PASS native original entire 1896B/512 i386, 62 real E8 and all 26 genuine PE HIGHLOW positions/targets')
    print('PASS original 20B/16B separate file getters, text capture/queue and end-of-function PMR name destructor')
    if candidate:
        body, relocs = coff.object_function(candidate, SYM, SIZE)
        compiled = list(Cs(CS_ARCH_X86, CS_MODE_32).disasm(bytes(body), 0))
        assert len(body) == SIZE and len(compiled) == 512
        assert compiled[-1].address + compiled[-1].size == SIZE
        assert (compiled[-1].mnemonic, compiled[-1].op_str) == ('ret', '0x10')
        calls = [r for r in relocs if r['type'] == 'REL32']
        data = [r for r in relocs if r['type'] == 'DIR32']
        assert len(relocs) == 88 and len(calls) == 62 and len(data) == 26
        assert all(r['addend'] == 0 for r in relocs)
        relocated = bytearray(body)
        for r in calls:
            matches = [target for prefix, target in CALL_ROLE_TARGETS.items()
                       if r['symbol'].startswith(prefix)]
            assert len(matches) == 1
            assert original_calls[r['offset'] - 1] == matches[0]
            struct.pack_into('<I', relocated, r['offset'],
                             (matches[0] - HEAD - r['offset'] - 4) & 0xffffffff)
        for r in data:
            if r['symbol'].startswith('$SG'):
                literal = bytes.fromhex(r['literal'])
                word = literal.split(b'\0', 1)[0] + b'\0'
                assert not any(literal[len(word):])
                target = {b'text\0': 0x0056FE1C, b'effect\0': 0x0056EC84}[word]
            else:
                matches = [target for prefix, targets in DATA_ROLE_TARGETS.items()
                           if not prefix.startswith('$SG') and r['symbol'].startswith(prefix)
                           for target in targets]
                assert len(matches) == 1
                target = matches[0]
            assert NATIVE_DATA[r['offset']] == target
            struct.pack_into('<I', relocated, r['offset'], target)
        assert relocated == original
        verify_eh_metadata(candidate, image, base, sections)
        units = ('card_start_spell_1896', 'card_start_eh_name_cleanup_8',
                 'card_start_eh_payload_cleanup_16', 'card_start_eh_handler_42',
                 'card_start_pmr_string_char_ctor_128', 'card_text_callable_test_7',
                 'card_text_function_ctor_102', 'card_text_function_reset_65')
        for unit in units:
            result = coff.compare_unit(unit)
            assert result['result'] == 'exact' and result['matched_bytes'] == result['size'], unit
        print('PASS complete 1896B/512-instruction parent: all bytes, 62 call fields and 26 data fields')
        print('PASS eight canonical units in the affected Card-start provider, including 66B owned EH code')
if __name__=='__main__':
    p=argparse.ArgumentParser()
    p.add_argument('--candidate-object',type=Path)
    verify(p.parse_args().candidate_object)
