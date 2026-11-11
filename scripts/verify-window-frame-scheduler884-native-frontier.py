#!/usr/bin/env python3
"""Entire 884B original Window scheduler versus 866B actual D3D9 typed source.

Native E8/HIGHLOW targets come only from original SHA-pinned PE; COFF roles are
derived from actual compiler relocations, not inferred from counts or prefixes.
The parent is NONEXACT; this script deliberately awards zero parent bytes.
"""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 s=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('sched884_coff','scripts/compare-coff-function.py')
pe=load('sched884_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004193E0
SIZE=884
SHA='615f5ad822a12bdad16238d5e88b9dc9e965eda8748a019cc4b2c7ef4f4bdeb6'
SYM='?schedule_frame_4193e0@NativeWindowFrameScheduleView@th20@@QAEXXZ'
OBJ=R/'build/gptweb20-window884/WindowFrameSchedulerBoss884.obj'
NATIVE_E8={
 0x017:0x0041CB10,0x06B:0x0041CA50,0x099:0x0041CA50,
 0x0A9:0x0041CA50,0x0B8:0x0041CA50,0x0C9:0x0041CA50,
 0x0E4:0x0041CA50,0x0F2:0x0041CA50,0x0FC:0x0041CA50,
 0x10B:0x0041CA50,0x126:0x0041CA50,0x15D:0x0041CB10,
 0x1AE:0x00415800,0x1C5:0x0041CB10,0x211:0x00412730,
 0x246:0x0041CA50,0x254:0x0041CA50,0x26F:0x0041CB10,
 0x280:0x00419760,0x28B:0x00412730,0x2B6:0x004DD840,
 0x2C1:0x0041DBE0,0x2CC:0x00412730,0x2F5:0x0041D9F0,
 0x2FF:0x004DBD70,0x304:0x0041A2C0,0x313:0x004193C0,
 0x31B:0x0041CB10,0x326:0x0041CA50,0x33C:0x0041CA50,
 0x357:0x0041CB10,0x36B:0x005429EE,
}
NATIVE_DATA={
 0x007:0x005B25C0,0x029:0x0056C468,0x031:0x0056C470,
 0x04F:0x0056CD88,0x057:0x0056CD78,0x19B:0x0056CD60,
 0x1AA:0x005C4D40,0x1E1:0x0056CD58,0x1EF:0x0056C16C,
 0x20D:0x005C4D40,0x287:0x005C4D40,0x2B2:0x005C4D40,
 0x2BD:0x005C0028,0x2C8:0x005C4D40,0x2E0:0x005C4E24,
 0x2F1:0x005C0028,0x2FB:0x005C4D40,0x30B:0x005C586C,
 0x335:0x0056C2D8,0x347:0x0056C16C,0x34F:0x0056C2DC,
}
E8_ROLES={
 '?current_seconds_41cb10@':0x0041CB10,
 '?active_repeat_41ca50@':0x0041CA50,
 '?canvas_width_415800@':0x00415800,
 '?device_412730@':0x00412730,
 '?update_scene_419760@':0x00419760,
 '?frame_recover_4dd840@':0x004DD840,
 '?frame_lost_41dbe0@':0x0041DBE0,
 '?frame_restored_41d9f0@':0x0041D9F0,
 '?frame_complete_4dbd70@':0x004DBD70,
 '?window_frame_initialize_41a2c0@':0x0041A2C0,
 '?window_frame_clock_dispatch_4193c0@':0x004193C0,
 '@__security_check_cookie@4':0x005429EE,
}
DATA_ROLES={
 '___security_cookie':0x005B25C0,
 '?native_scheduler_one_56c468@':0x0056C468,
 '?native_scheduler_sixty_56c470@':0x0056C470,
 '?native_scheduler_thousand_56cd88@':0x0056CD88,
 '?native_scheduler_bias_56cd78@':0x0056CD78,
 '?native_scheduler_refresh_56cd60@':0x0056CD60,
 '?native_frame_graphics_5c4d40@':0x005C4D40,
 '?native_scheduler_poll_56cd58@':0x0056CD58,
 '__imp__Sleep@4':0x0056C16C,
 '?native_frame_renderer_5c0028@':0x005C0028,
 '?native_frame_present_5c4e24@':0x005C4E24,
 '?native_frame_status_5c586c@':0x005C586C,
 '__imp__timeBeginPeriod@4':0x0056C2D8,
 '__imp__timeEndPeriod@4':0x0056C2DC,
}
def main():
 image=cf.verified_target();base,sec=pe.parse_sections(image)
 raw=pe.raw_at(image,base,sec,HEAD,SIZE)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ops)==239 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert (ops[-1].mnemonic,ops[-1].op_str)==('ret','')
 original_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                 for i in ops if i.size==5 and i.bytes[0]==0xE8}
 original_data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
                for p in pe.physical_highlow(image,base,sec) if HEAD<=p<HEAD+SIZE}
 assert original_calls==NATIVE_E8
 assert original_data==NATIVE_DATA
 for addr,value in (
     (0x0056C468,1.0),(0x0056C470,60.0),(0x0056CD88,1000.0),
     (0x0056CD78,2.5),(0x0056CD60,0.019),(0x0056CD58,0.013)):
  assert pe.raw_at(image,base,sec,addr,8)==struct.pack('<d',value)
 obj,rel=cf.object_function(OBJ,SYM,866)
 source=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(obj),0))
 assert len(obj)==866 and len(source)==236
 calls=[r for r in rel if r['type']=='REL32']
 data=[r for r in rel if r['type']=='DIR32']
 assert len(calls)==32 and len(data)==21 and len(rel)==53
 assert [i.address for i in source if i.size==5 and i.bytes[0]==0xE8]==[r['offset']-1 for r in calls]
 for c,(orig_off,target) in zip(calls,sorted(NATIVE_E8.items())):
  matches=[val for prefix,val in E8_ROLES.items() if c['symbol'].startswith(prefix)]
  assert c['addend']==0 and matches==[target],(hex(orig_off),hex(target),c,matches)
 for d,(orig_off,target) in zip(data,sorted(NATIVE_DATA.items())):
  matches=[val for prefix,val in DATA_ROLES.items() if d['symbol'].startswith(prefix)]
  assert d['addend']==0 and matches==[target],(hex(orig_off),hex(target),d,matches)
 orig_call_sites=list(sorted(NATIVE_E8))
 source_call_sites=[r['offset']-1 for r in calls]
 orig_data_sites=list(sorted(NATIVE_DATA))
 source_data_sites=[r['offset'] for r in data]
 same_calls=sum(x==y for x,y in zip(orig_call_sites,source_call_sites))
 same_data=sum(x==y for x,y in zip(orig_data_sites,source_data_sites))
 assert same_calls==13 and same_data==7
 mask={i for r in rel for i in range(r['offset'],r['offset']+4)}
 ordinary=sum(a==z for i,(a,z) in enumerate(zip(raw,obj)) if i not in mask)
 assert ordinary==367,ordinary
 assert bytes(obj)!=raw
 for unit,n in [('window_active_repeat_31',31),('window_seconds_clock_boss_346',346),('window_frame_clock_dispatch_32',32),('window_snapshot_scene_boss_574',574)]:
  proof=cf.compare_unit(unit)
  assert proof['result']=='exact' and proof['matched_bytes']==n,unit
 print('PASS native original 884B/239 i386 complete SHA, 32 real E8 and 21 PE HIGHLOW site/destination identities')
 print('PASS complete candidate 866B/236 i386, all 32/32 original E8 CALLEE roles and 21/21 PE DATA target roles in native order')
 print(f'NONEXACT: only {same_calls}/32 E8 and {same_data}/21 HIGHLOW physical offsets match, {ordinary} ordinary positional bytes equal')
 print('PASS separate 31B RepeatCounter, 346B Window seconds clock, 32B dispatch and now exact 574B screenshot child remain full native exact')
 print('No 884B game parent exactness or newly credited original bytes. Candidate is real compiled gameplay source; no full-graph replay.')
if __name__=='__main__':main()
