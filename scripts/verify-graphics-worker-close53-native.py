#!/usr/bin/env python3
"""Whole 53B native Graphics Worker shutdown leaf: original and canonical MSVC."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,p):
 spec=importlib.util.spec_from_file_location(n,R/p)
 mod=importlib.util.module_from_spec(spec);spec.loader.exec_module(mod);return mod
cf=load('workerclose53_cf','scripts/compare-coff-function.py')
pe=load('workerclose53_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004D9E30
SIZE=53
SHA='6b70ab34d6c494c1230f2f3328ddc8907caee1ed9cfab5fc01ce7fd62732f903'
SYM='?bail_out_4d9e30@NativeTickGraphicsView@th20@@QAEXXZ'
def main():
 exe=cf.verified_target();base,sections=pe.parse_sections(exe)
 original=pe.raw_at(exe,base,sections,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 assert pe.raw_at(exe,base,sections,0x00571E48,20)==b'SyncCloseSubThread\n\x00'
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==17 and ins[-1].address+ins[-1].size==HEAD+SIZE
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
   for i in ins if i.size==5 and i.bytes[0]==0xE8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sections,p,4))[0]
   for p in pe.physical_highlow(exe,base,sections) if HEAD<=p<HEAD+SIZE}
 assert calls=={0x0C:0x0040C6B0,0x1D:0x004BA8B0,0x2B:0x0040BCF0}
 assert data=={0x08:0x00571E48}
 assert any(i.address-HEAD==0x30 and i.mnemonic=='nop' for i in ins)
 for off in [0x17,0x25]:
  assert any(i.address-HEAD==off and '0xd90' in i.op_str for i in ins)
 code,rels=cf.object_function(R/'build/core1140-canonical/GraphicsWorkerClose53.obj',SYM,SIZE)
 assert len(code)==SIZE and len(rels)==4 and all(r['addend']==0 for r in rels)
 assert [r['offset']-1 for r in rels if r['type']=='REL32']==list(calls)
 assert [r['offset'] for r in rels if r['type']=='DIR32']==list(data)
 mask={j for r in rels for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==16
 assert all(a==z for j,(a,z) in enumerate(zip(original,code)) if j not in mask)
 receipt=cf.compare_unit('graphics_worker_close_53')
 assert receipt['result']=='exact' and receipt['matched_bytes']==53
 print('PASS complete original Graphics Worker shutdown 53B/17 i386 SHA and literal SyncCloseSubThread')
 print('PASS canonical source 53/53B, original 3 E8 +1 HIGHLOW native physical targets, 37/37 ordinary bytes and authentic NOP')
 print('PASS real Graphics+0xD90 Worker ownership; no duplicate credit for already recovered Worker or diagnostic callees')
if __name__=='__main__':main()
