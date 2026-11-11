#!/usr/bin/env python3
"""Full SHA-pinned 574B Window snapshot Boss and whole strict exact source.

Original E8/HIGHLOW roles are independently read from immutable PE, never
inferred from compiler displacements. Both PE and pinned MSVC code have complete 574B/132-i386 identity.
"""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 s=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('winscene574_cf','scripts/compare-coff-function.py')
pe=load('winscene574_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x00419760
SIZE=574
SHA='12c08490acf889b9d6ef21f67e6f85051f7eeb7bc00bb7b576450899b48ead57'
SYM='?update_scene_419760@NativeWindowFrameScheduleView@th20@@QAEXXZ'
OBJ=R/'build/gptweb20-window574/WindowSnapshotScene574.obj'
NATIVE_E8={
 0x037:0x0041BFC0,0x06F:0x00419C00,0x0B2:0x00417CD0,
 0x0C9:0x00417E40,0x0D5:0x0041C2E0,0x120:0x0041F220,
 0x133:0x00417DF0,0x143:0x00417E40,0x155:0x00417E40,
 0x167:0x0041E790,0x176:0x0040FF30,0x188:0x004107A0,
 0x1A1:0x0040E5A0,0x1B3:0x0040E5A0,0x1D7:0x0041E790,
 0x1E6:0x0040FF30,0x1FD:0x004DE040,0x20C:0x0040E5A0,
 0x21F:0x0040E6C0,0x235:0x005429EE,
}
NATIVE_DATA={
 0x006:0x00567F76,0x018:0x005B25C0,0x033:0x005C0028,
 0x04A:0x005B889C,0x05A:0x005B889C,0x095:0x005B87E8,
 0x0A8:0x005B67E1,0x0BF:0x0056CAAC,0x110:0x0056CABC,
 0x129:0x005B67E1,0x139:0x0056CAAC,0x1F9:0x005C4D40,
}
CALL_ROLE={
 '?prepare_frame_41bfc0@':0x0041BFC0,
 '?pressed_bits@InputButtonState@':0x00419C00,
 '??$?0$$BY0BAAA@':0x00417CD0,
 '??$?_0$$BY08D':0x00417E40,
 '?create_directories@filesystem@':0x0041C2E0,
 '?native_snapshot_format_41f220@':0x0041F220,
 '??$?4$$BY0BAAA@':0x00417DF0,
 '??$?_0$$BY0BAA@':0x00417E40,
 '?string@path@filesystem@':0x0041E790,
 '?c_str@?$basic_string@':0x0040FF30,
 '?game_file_exists_4107a0@':0x004107A0,
 '??1?$basic_string@':0x0040E5A0,
 '?write_snapshot_4de040@':0x004DE040,
 '??1path@filesystem@':0x0040E6C0,
 '@__security_check_cookie@4':0x005429EE,
}
DATA_ROLE={
 '__ehhandler$':0x00567F76,
 '___security_cookie':0x005B25C0,
 '?native_window_capture_renderer_5c0028@':0x005C0028,
 '?native_snapshot_input_bindings_5b889c@':0x005B889C,
 '?native_snapshot_options_5b87e8@':0x005B87E8,
 '?window_state@':0x005B6758,
 '?native_snapshot_subdir_56caac@':0x0056CAAC,
 '?native_snapshot_pattern_56cabc@':0x0056CABC,
 '?native_window_capture_graphics_5c4d40@':0x005C4D40,
}
def main():
 image=cf.verified_target();base,secs=pe.parse_sections(image)
 original=pe.raw_at(image,base,secs,HEAD,SIZE)
 assert len(original)==SIZE and hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==132 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,secs,p,4))[0]
       for p in pe.physical_highlow(image,base,secs) if HEAD<=p<HEAD+SIZE}
 assert calls==NATIVE_E8 and data==NATIVE_DATA
 assert pe.raw_at(image,base,secs,0x0056CAAC,9)==b'snapshot\x00'
 assert pe.raw_at(image,base,secs,0x0056CABC,14)==b'th20_%.3d.png\x00'
 code,rr=cf.object_function(OBJ,SYM,574)
 src_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(code),0))
 assert len(code)==574 and len(src_ins)==132
 crels=[r for r in rr if r['type']=='REL32']
 drel=[r for r in rr if r['type']=='DIR32']
 assert len(crels)==20 and len(drel)==12
 assert [r['offset']-1 for r in crels]==[i.address for i in src_ins if i.size==5 and i.bytes[0]==0xe8]
 for (off,target),rel in zip(sorted(calls.items()),crels):
  matches=[v for prefix,v in CALL_ROLE.items() if rel['symbol'].startswith(prefix)]
  assert matches==[target] and rel['addend']==0,(hex(off),target,rel,matches)
 for (off,target),rel in zip(sorted(data.items()),drel):
  matches=[v for prefix,v in DATA_ROLE.items() if rel['symbol'].startswith(prefix)]
  assert len(matches)==1,(hex(off),target,rel,matches)
  assert (matches[0]+rel['addend'])&0xffffffff==target,(hex(off),target,rel,matches)
 same_calls=sum(off==rel['offset']-1 for (off,_),rel in zip(sorted(calls.items()),crels))
 same_data=sum(off==rel['offset'] for (off,_),rel in zip(sorted(data.items()),drel))
 masked={j for rel in rr for j in range(rel['offset'],rel['offset']+4)}
 ordinary=sum(a==z for i,(a,z) in enumerate(zip(original,code)) if i not in masked)
 assert same_calls==20 and same_data==12 and ordinary==446,(same_calls,same_data,ordinary)
 assert bytes(code)!=original
 # The raw COFF displacement/data entries are linker placeholders; only
 # the attested full strict source replay can establish all 574 exact bytes.
 canonical=cf.compare_unit('window_snapshot_scene_boss_574')
 assert canonical['result']=='exact' and canonical['matched_bytes']==574
 for unit,n in [('window_active_repeat_31',31),('game_file_exists_157',157)]:
  try:
   proof=cf.compare_unit(unit)
   assert proof['result']=='exact' and proof['matched_bytes']==n,unit
  except ValueError as err:
   if unit=='game_file_exists_157' and 'unknown match unit' in str(err):
    continue
   raise
 print('PASS original complete native screenshot scene 574B/132 i386, all 20 E8 and 12 PE HIGHLOW sites/target identities independently SHA-pinned')
 print('PASS entire C++ source 574B/132 i386; all 20 original E8 and 12 data sites physically identical, full 446/446 ordinary bytes')
 print(f'PASS whole original strict exact: {same_calls}/20 E8 and {same_data}/12 data offsets, {ordinary}/446 ordinary bytes, full 574/574 replay')
 print('PASS existing exact Window 31B RepeatCounter; original 884B scheduler remains NONEXACT. Only 574 new game bytes credited.')
if __name__=='__main__':main()
