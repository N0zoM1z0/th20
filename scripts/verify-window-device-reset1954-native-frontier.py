#!/usr/bin/env python3
"""Full immutable 1954B D3D9 Window reset Boss vs real NONEXACT C++ source.

All native roles and candidate COFF symbols are evaluated in physical order.
This is complete executable gameplay SOURCE evidence, not parent-byte credit.
"""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 spec=importlib.util.spec_from_file_location(n,R/p)
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
cf=load('reset1954_cf','scripts/compare-coff-function.py')
pe=load('reset1954_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x0041A2C0
SIZE=1954
SHA='47eeb9e563d439887c764aa863415a55551f7d8a2d6065a019897a86d147137a'
SYM='?window_frame_initialize_41a2c0@th20@@YAXXZ'
OBJ=R/'build/gptweb23-window1954/WindowDeviceResetStatesBoss1954.obj'
CALLEES=[0x00412730]*38+[
 0x0041DB40,0x0041DB60,0x0041DB80,0x0041DBA0,0x0041DBC0]
def symbol_target(symbol):
 vals={
  '?get_device@Graphics@':0x00412730,
  '?restart_state_41db40@':0x0041DB40,
  '?restart_state_41db60@':0x0041DB60,
  '?restart_state_41db80@':0x0041DB80,
  '?restart_state_41dba0@':0x0041DBA0,
  '?restart_state_41dbc0@':0x0041DBC0,
  '?process_graphics@':0x005C4D40,
  '?native_reset_one_56c8cc@':0x0056C8CC,
  '?native_reset_thousand_56cdb0@':0x0056CDB0,
  '?native_reset_five_thousand_56cdb8@':0x0056CDB8,
  '?current_animation_pool@':0x005C0028,
 }
 found=[v for prefix,v in vals.items() if symbol.startswith(prefix)]
 assert len(found)==1,(symbol,found)
 return found[0]
def main():
 exe=cf.verified_target();base,sec=pe.parse_sections(exe)
 original=pe.raw_at(exe,base,sec,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 oi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(oi)==507 and oi[-1].address+oi[-1].size==HEAD+SIZE
 oc=[(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
     for i in oi if i.size==5 and i.bytes[0]==0xe8]
 assert oc==CALLEES+[0x005429EE]
 data=[struct.unpack('<I',pe.raw_at(exe,base,sec,p,4))[0]
       for p in pe.physical_highlow(exe,base,sec) if HEAD<=p<HEAD+SIZE]
 assert len(data)==48 and data[0]==0x005B25C0
 assert pe.raw_at(exe,base,sec,0x56C8CC,4)==struct.pack('<f',1.)
 assert pe.raw_at(exe,base,sec,0x56CDB0,4)==struct.pack('<f',1000.)
 assert pe.raw_at(exe,base,sec,0x56CDB8,4)==struct.pack('<f',5000.)
 body,rel=cf.object_function(OBJ,SYM,1911)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
 assert len(ins)==499 and len(rel)==90
 calls=[r for r in rel if r['type']=='REL32']
 fields=[r for r in rel if r['type']=='DIR32']
 assert len(calls)==43 and len(fields)==47
 assert [symbol_target(r['symbol']) for r in calls]==CALLEES
 assert [symbol_target(r['symbol']) for r in fields]==data[1:]
 assert [i.address for i in ins if i.size==5 and i.bytes[0]==0xe8]==[r['offset']-1 for r in calls]
 for original_offset,expected in ((0xE4,24),(0x10C,8),(0x114,6)):
  assert sum(f'+ 0x{original_offset:x}]' in i.op_str for i in oi)==expected
  assert sum(f'+ 0x{original_offset:x}]' in i.op_str for i in ins)==expected
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 same=sum(a==b for j,(a,b) in enumerate(zip(original,body)) if j not in mask)
 assert same==95 and len(body)!=SIZE
 assert cf.compare_unit('window_frame_scheduler_boss_884')['result']=='exact'
 print('PASS original locked 1954B/507-i386 SHA, 38 real D3D9 getters + five Renderer reset hooks + GS-cookie check')
 print('PASS complete pinned-MSVC 1911B/499-i386 source: original 43/43 game E8 and 47/47 data destination roles in original order')
 print('PASS all 24 SetRenderState, eight SetTextureStageState, six SetSamplerState true vtable offsets, original game constants')
 print(f'NONEXACT 1954B parent: {same} same-position ordinary bytes and original GS cookie not naturally reproduced; zero parent exact credit')
if __name__=='__main__':main()
