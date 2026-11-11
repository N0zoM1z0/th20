#!/usr/bin/env python3
"""Whole 136B native Graphics D3D9 resource release, real PE owner offsets."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 sp=importlib.util.spec_from_file_location(n,R/p)
 m=importlib.util.module_from_spec(sp);sp.loader.exec_module(m);return m
cf=load('gres136_cf','scripts/compare-coff-function.py')
pe=load('gres136_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004DD840
SIZE=136
SHA='1d64e1c20d778cd77e8f322d2c08780602a512c030de01df187c3ca6694f05f6'
SYM='?frame_recover_4dd840@NativeFrameGraphicsView@th20@@QAEXXZ'
SITES={
 0x09:0x19C,0x11:0x19C,0x19:0x19C,0x25:0x19C,
 0x2F:0x1A0,0x38:0x1A0,0x3F:0x1A0,0x4B:0x1A0,
 0x55:0x1A4,0x5E:0x1A4,0x66:0x1A4,0x72:0x1A4,
 0x7C:0x19C,
}
def main():
 image=cf.verified_target();base,secs=pe.parse_sections(image)
 original=pe.raw_at(image,base,secs,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==35 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert not any(i.size==5 and i.bytes[0]==0xe8 for i in ins)
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,secs,p,4))[0]
       for p in pe.physical_highlow(image,base,secs) if HEAD<=p<HEAD+SIZE}
 assert data=={off:0x005C4D40+member for off,member in SITES.items()}
 assert sum('call'==i.mnemonic for i in ins)==3
 assert sum('0x19c' in i.op_str for i in ins)==0
 compiled,rel=cf.object_function(R/'build/core1145-canonical/GraphicsReleaseD3DResources136.obj',SYM,SIZE)
 assert len(compiled)==SIZE and len(rel)==13
 assert [r['offset'] for r in rel]==list(data)
 assert all(r['type']=='DIR32' and r['symbol'].startswith('?process_graphics@') and
    r['addend']==SITES[r['offset']] for r in rel)
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==52
 assert all(a==b for i,(a,b) in enumerate(zip(original,compiled)) if i not in mask)
 exact=cf.compare_unit('graphics_d3d_resource_release_136')
 assert exact['result']=='exact' and exact['matched_bytes']==SIZE
 frame=cf.compare_unit('window_frame_scheduler_boss_884')
 assert frame['result']=='exact' and frame['matched_bytes']==884
 print('PASS immutable 136B/35-i386 Graphics release SHA and 13 PE HIGHLOW original physical locations')
 print('PASS exact canonical 136/136B, 84/84 ordinary bytes; authentic Graphics base+0x19C/1A0/1A4 COFF addends')
 print('PASS already whole-exact 884B Window scheduler uses this true original Graphics cleanup leaf')
if __name__=='__main__':main()
