#!/usr/bin/env python3
"""Complete native source-exact frame time helper trio; origin review, no game byte credit."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name,path):
 s=importlib.util.spec_from_file_location(name,R/path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('winleaves_cf','scripts/compare-coff-function.py')
pe=load('winleaves_pe','scripts/verify-animation-draw-boss-native.py')
OBJ=R/'build/core1128-canonical/WindowFrameTimeLeaves109.obj'
SPECS=[
 ('frame_time_pair_read_46',0x004AC170,46,18,'7129bd713e1005057ae65f87ab760622e2e9dee565e275730786b18ed9c20b0a',
  '?read_frame_pair_4ac170@th20@@YAPAUNativeFrameTimePair@1@PAU21@@Z',
  {0x06:0x00541900,0x18:0x00446DA0,0x21:0x00447D20},
  {'?native_clock_ticks_541900@':0x00541900,'??0NativeFrameClockPairValue@':0x00446DA0,'??4NativeFrameClockPairValue@':0x00447D20}),
 ('frame_time_u64_convert_42',0x004AC200,42,17,'f2807246a258ad6b62875747413f8099ec02ab47b6b2c86ad81666214718c570',
  '?frame_time_u64_4ac200@th20@@YA_KPAUNativeFrameTimePair@1@@Z',
  {0x0D:0x00451620,0x17:0x004ABB20,0x21:0x0044C090},
  {'?native_stamp_input_451620@':0x00451620,'?native_stamp_convert_4abb20@':0x004ABB20,'?native_timestamp_value_44c090@':0x0044C090}),
 ('frame_time_breakdown_21',0x004AC270,21,10,'d25a69e45b400e7e84fc251062ba62e839abdd04fc7f682d7f6540e1593c5b83',
  '?frame_time_breakdown_4ac270@th20@@YAXPAEPA_K@Z',
  {0x0B:0x0055139C},
  {'?native_time_breakdown_55139c@':0x0055139C}),
]
def main():
 exe=cf.verified_target();base,sec=pe.parse_sections(exe)
 physical_data=pe.physical_highlow(exe,base,sec)
 for unit,head,n,count,sha,sym,calls,roles in SPECS:
  original=pe.raw_at(exe,base,sec,head,n)
  assert len(original)==n and hashlib.sha256(original).hexdigest()==sha
  ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,head))
  assert len(ops)==count and ops[-1].address+ops[-1].size==head+n
  assert (ops[-1].mnemonic,ops[-1].op_str)==('ret','')
  native={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
          for i in ops if i.size==5 and i.bytes[0]==0xe8}
  assert native==calls
  assert not any(head<=p<head+n for p in physical_data)
  if n==46:
   # This NOP is naturally emitted by the real C++ temporary followed
   # by its assignment, not hand-authored or added as filler.
   assert original[0x26]==0x90
  body,rr=cf.object_function(OBJ,sym,n)
  assert len(rr)==len(calls)
  cover={j for r in rr for j in range(r['offset'],r['offset']+4)}
  assert len(cover)==4*len(calls)
  assert all(a==b for i,(a,b) in enumerate(zip(original,body)) if i not in cover)
  for r in rr:
   assert r['type']=='REL32' and r['addend']==0
   site=r['offset']-1
   assert site in calls
   matches=[dest for prefix,dest in roles.items() if r['symbol'].startswith(prefix)]
   assert matches==[calls[site]],(unit,r,site,matches)
  result=cf.compare_unit(unit)
  assert result['result']=='exact' and result['matched_bytes']==n
  print(f'PASS {unit}: original whole {n}/{n}B, {count} instructions, all {len(calls)} native E8 physical site/target roles; no HIGHLOW')
 # The complete native 113B game-authored caller holds exactly these three
 # source-exact time wrappers at three physical sites, without duplicate
 # credit for the wrapper originals while origin remains under review.
 parent=0x004AC0E0
 for offset,target in ((0x0D,0x004AC170),(0x33,0x004AC200),(0x5D,0x004AC270)):
  site=parent+offset;e8=pe.raw_at(exe,base,sec,site,5)
  assert e8[0]==0xe8 and site+5+struct.unpack_from('<i',e8,1)[0]==target
 for unit,n in [('window_frame_pipeline_113',113),('window_frame_device_clock_boss_437',437),('window_frame_clock_dispatch_32',32)]:
  result=cf.compare_unit(unit)
  assert result['result']=='exact' and result['matched_bytes']==n
 print('PASS original 113B pipeline includes all 46B/42B/21B native callees; accepted 113B/437B/32B parents unchanged')
 print('PASS 6/6 affected functions whole-native exact; 109 helper bytes source proven but authorship REVIEW, zero newly credited game-authored bytes')
if __name__=='__main__':main()
