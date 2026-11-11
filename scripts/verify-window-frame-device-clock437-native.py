#!/usr/bin/env python3
"""Whole original frame/device tick 437B and exact 32B dispatch caller proof."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,path):
 s=importlib.util.spec_from_file_location(n,R/path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('device437_cf','scripts/compare-coff-function.py')
pe=load('device437_pe','scripts/verify-animation-draw-boss-native.py')
H=0x004ABD50
SIZE=437
SHA='8df209582a9bf10136297e2ab5dd135e6911eb7eab5553ff5355d33162ca7bb7'
SYM='?frame_seconds_4abd50@NativeFrameDeviceClockView@th20@@QAEHXZ'
OBJ=R/'build/core1125-canonical/WindowFrameDeviceClock437.obj'
E8={0x00E:0x0041CB10,0x1A7:0x004AC0E0}
DATA={
 0x00A:0x005B6758,0x043:0x0056C468,0x08D:0x0056CDD0,
 0x0AD:0x00570618,0x0D0:0x005BA828,0x0DC:0x005BA828,
 0x0F0:0x005BA828,0x10E:0x0056C470,0x125:0x00570614,
 0x137:0x0056C470,0x15F:0x005BA828,0x167:0x005BA828,
 0x179:0x005BA828,0x190:0x005C4F84,
}
ROLES={
 '?native_card_window_time_5b6758@':0x005B6758,
 '?current_seconds_41cb10@':0x0041CB10,
 '?native_frame_min_window_56c468@':0x0056C468,
 '?correction_table@?6??frame_seconds_4abd50@':0x0056CDD0,
 '?native_frame_maximum_fps_570618@':0x00570618,
 '?current_game_controller@':0x005BA828,
 '?native_frame_count_step_56c470@':0x0056C470,
 '?native_frame_minimum_fps_570614@':0x00570614,
 '?native_frame_skip_count_5c4f84@':0x005C4F84,
 '?frame_pipeline_4ac0e0@':0x004AC0E0,
}
def main():
 img=cf.verified_target();base,sec=pe.parse_sections(img)
 raw=pe.raw_at(img,base,sec,H,SIZE)
 assert len(raw)==SIZE and hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,H))
 assert len(ins)==105 and ins[-1].address+ins[-1].size==H+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-H:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xe8}
 data={p-H:struct.unpack('<I',pe.raw_at(img,base,sec,p,4))[0]
       for p in pe.physical_highlow(img,base,sec) if H<=p<H+SIZE}
 assert calls==E8 and data==DATA
 body,rr=cf.object_function(OBJ,SYM,SIZE)
 assert len(body)==SIZE and len(rr)==16
 assert sum(r['type']=='REL32' for r in rr)==2 and sum(r['type']=='DIR32' for r in rr)==14
 covered={j for r in rr for j in range(r['offset'],r['offset']+4)}
 assert len(covered)==64 and all(raw[i]==body[i] for i in range(SIZE) if i not in covered)
 for r in rr:
  off=r['offset'];typ=r['type'];site=off-1 if typ=='REL32' else off
  target=(calls if typ=='REL32' else data).get(site)
  match=[a for prefix,a in ROLES.items() if r['symbol'].startswith(prefix)]
  assert target is not None and match==[target] and r['addend']==0,(site,r,match,target)
 # These are genuinely observed original data, not assumed thresholds.
 for addr,value,fmt in ((0x0056C468,1.0,'<d'),(0x0056C470,60.0,'<d'),
                        (0x00570618,65.0,'<f'),(0x00570614,57.0,'<f')):
  assert pe.raw_at(img,base,sec,addr,struct.calcsize(fmt))==struct.pack(fmt,value)
 assert pe.raw_at(img,base,sec,0x0056CDD0,16)==struct.pack('<dd',0.0,4294967296.0)
 # The 32B original Window/Frame entry dispatch reaches this exact 437B
 # body before its separately exact Card clock callback.
 site=0x004193C0+0x12
 e8=pe.raw_at(img,base,sec,site,5)
 assert e8[0]==0xe8 and site+5+struct.unpack_from('<i',e8,1)[0]==H
 for unit,size in (('window_frame_device_clock_boss_437',437),
                   ('window_frame_clock_dispatch_32',32),
                   ('window_seconds_clock_boss_346',346)):
  result=cf.compare_unit(unit)
  assert result['result']=='exact' and result['matched_bytes']==size
 print('PASS original complete Window device frame clock 437/437B, 105 i386, 2/2 E8 and 14/14 PE HIGHLOW sites and native roles')
 print('PASS all 373/373 ordinary bytes, real 0/2^32 conversion table and 1.0/60.0/65.0/57.0 original timing constants')
 print('PASS pinned MSVC exact receipts: 437B device, 32B Window/Frame dispatch and 346B WindowState seconds clock; no duplicate game credit')
if __name__=='__main__':main()
