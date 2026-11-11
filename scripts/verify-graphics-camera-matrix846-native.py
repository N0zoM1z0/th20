#!/usr/bin/env python3
"""Whole immutable 846B game Graphics D3DX9 camera matrix source attestation."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 spec=importlib.util.spec_from_file_location(n,R/p)
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
cf=load('cam846_cf','scripts/compare-coff-function.py')
pe=load('cam846_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004DA1F0
SIZE=846
SHA='6f96ef09b5688b5ca16322fd909a925ac579bbc15e3f7e817c0aa7fd798a0a2c'
SYM='?recompute_current_4da1f0@NativeGraphicsModeAction@th20@@QAEXPAUViewportState@2@PAUNativeViewport@2@@Z'
E8={0x5A:0x00439850,0x167:0x00422DD0,0x25C:0x00422DD0,
    0x284:0x00422DD0,0x29C:0x005406BA,0x338:0x005406C0,
    0x343:0x005429EE}
CONVERSION_SITES={0x31,0x8D,0xB4,0xF2,0x126,0x191,0x1C1,
                 0x203,0x233,0x2D6,0x303}
CONST_SITES={
 0x0A:0x005B25C0,0x31:0x0056CDD0,0x4B:0x0056C8D0,
 0x8D:0x0056CDD0,0xB4:0x0056CDD0,0xCC:0x0056C8D0,
 0xF2:0x0056CDD0,0x10A:0x0056C8D0,0x126:0x0056CDD0,
 0x191:0x0056CDD0,0x1C1:0x0056CDD0,0x1D9:0x0056C8D0,
 0x203:0x0056CDD0,0x233:0x0056CDD0,0x24B:0x0056C8D0,
 0x26F:0x0056E0F4,0x2A6:0x00571EA0,0x2B4:0x0056C8CC,
 0x2D6:0x0056CDD0,0x303:0x0056CDD0
}
def main():
 exe=cf.verified_target();base,sec=pe.parse_sections(exe)
 original=pe.raw_at(exe,base,sec,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(inst)==194 and inst[-1].address+inst[-1].size==HEAD+SIZE
 call={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
       for i in inst if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sec,p,4))[0]
       for p in pe.physical_highlow(exe,base,sec) if HEAD<=p<HEAD+SIZE}
 assert call==E8
 assert data==CONST_SITES
 assert pe.raw_at(exe,base,sec,0x56CDD0,16)==struct.pack('<dd',0.,4294967296.)
 assert pe.raw_at(exe,base,sec,0x56C8D0,4)==struct.pack('<f',2.)
 assert pe.raw_at(exe,base,sec,0x56C8CC,4)==struct.pack('<f',1.)
 assert pe.raw_at(exe,base,sec,0x56E0F4,4)==struct.pack('<f',-1.)
 assert pe.raw_at(exe,base,sec,0x571EA0,4)==struct.pack('<f',10000.)
 assert [i.address-HEAD for i in inst if i.mnemonic=='nop']==[0x33D]
 source,rel=cf.object_function(R/'build/core1142-canonical/GraphicsCameraMatrixBoss846.obj',SYM,SIZE)
 assert len(source)==SIZE and len(rel)==27
 assert [r['offset']-1 for r in rel if r['type']=='REL32']==list(E8)
 assert [r['offset'] for r in rel if r['type']=='DIR32']==list(CONST_SITES)
 assert all(r['addend']==0 for r in rel)
 assert {r['offset'] for r in rel if r['symbol'].startswith('__xmm@')}==CONVERSION_SITES
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==108
 assert all(a==b for i,(a,b) in enumerate(zip(original,source)) if i not in mask)
 for unit,size in [('graphics_camera_matrix_boss_846',846),
                   ('graphics_prepare_device_194',194),
                   ('graphics_viewport_clip_284',284)]:
  proof=cf.compare_unit(unit)
  assert proof['result']=='exact' and proof['matched_bytes']==size,unit
 print('PASS original full 846B/194-i386 SHA, seven genuine E8 and 20 PE HIGHLOW native positions/destinations')
 print('PASS 738/738 ordinary bytes and original 11 unsigned 0/2^32 conversion table sites with exact compiler symbols')
 print('PASS original Vector3/D3DX9 LookAt/Perspective workflow, independent 194B transform and 284B viewport callers exact')
if __name__=='__main__':main()
