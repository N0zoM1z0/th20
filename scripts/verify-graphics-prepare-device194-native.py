#!/usr/bin/env python3
"""Pinned PE and whole original 194B D3D9 Graphics matrix stage."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1];sys.path.insert(0,str(R/'scripts'))
def load(n,path):
 spec=importlib.util.spec_from_file_location(n,R/path)
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module);return module
cf=load('gp194_cf','scripts/compare-coff-function.py')
pe=load('gp194_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004DA120
SIZE=194
SHA='47f84290a4acb9348b8c74c3de8dad80751aa344472f98d129353ba8afafa011'
SYM='?prepare_device_4da120@NativeGraphicsModeAction@th20@@QAEXPAUViewportState@2@@Z'
CALLEES={0x18:0x004455C0,0x23:0x00412730,0x4E:0x00412730}
DATA={0x0B:0x005C0028,0x14:0x005C0028,0x1F:0x005C4D40,
      0x4A:0x005C4D40,0x7A:0x005C0028,0x8A:0x005C0028,0xA8:0x005C0028}
def main():
 exe=cf.verified_target();base,sec=pe.parse_sections(exe)
 original=pe.raw_at(exe,base,sec,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ops)==55 and ops[-1].address+ops[-1].size==HEAD+SIZE
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ops if i.size==5 and i.bytes[0]==0xe8}
 data={p-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sec,p,4))[0] for p in pe.physical_highlow(exe,base,sec) if HEAD<=p<HEAD+SIZE}
 assert calls==CALLEES,calls
 assert data==DATA,data
 assert any(i.mnemonic=='imul' and ', 0' in i.op_str for i in ops)
 assert any(i.mnemonic=='nop' and i.address-HEAD==0x77 for i in ops)
 code,rel=cf.object_function(R/'build/core1141-canonical/GraphicsPrepareDevice194.obj',SYM,SIZE)
 assert len(code)==SIZE and len(rel)==10
 assert [r['offset']-1 for r in rel if r['type']=='REL32']==list(calls)
 assert [r['offset'] for r in rel if r['type']=='DIR32']==list(data)
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==40
 assert all(a==b for i,(a,b) in enumerate(zip(original,code)) if i not in mask)
 for unit,size in [('graphics_prepare_device_194',194),('graphics_viewport_clip_284',284)]:
  proof=cf.compare_unit(unit)
  assert proof['result']=='exact' and proof['matched_bytes']==size,unit
 print('PASS original 194B/55-i386 SHA, three genuine E8 and seven HIGHLOW physical targets')
 print('PASS canonical whole original 194/194B, 154/154 ordinary bytes and original Imul/NOP')
 print('PASS independent existing 284B Graphics viewport selector remains exact')
if __name__=='__main__':main()
