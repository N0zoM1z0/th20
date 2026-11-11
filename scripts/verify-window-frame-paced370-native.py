#!/usr/bin/env python3
"""Locked PE and canonical source proof for the whole 370B Window paced controller."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
def load(name,path):
 spec=importlib.util.spec_from_file_location(name,ROOT/path)
 module=importlib.util.module_from_spec(spec);spec.loader.exec_module(module)
 return module
cf=load('wframe370_cf','scripts/compare-coff-function.py')
pe=load('wframe370_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x0041A030
SIZE=370
SHA='287e51977fe5528aa1e5061d80d2306ee552ea5950090d48c95c453b86e0bfa8'
SYM='?frame_controller_paced_41a030@NativeWindowFrameScheduleView@th20@@QAEHXZ'
CALLEES={0x1C:0x004455C0,0x28:0x0041DCE0,0x33:0x00412810,
 0x46:0x004D9E30,0x62:0x004D9E30,0x9E:0x00412730,
 0xBD:0x00445A40,0xD1:0x004DDA60,0xDC:0x00412AA0,
 0xE7:0x004455C0,0xF1:0x00412730,0x117:0x00412730,
 0x13A:0x00419A50,0x143:0x0041CB10,0x166:0x00412540}
DATA={0x18:0x005C0028,0x24:0x005C4D40,0x2F:0x005B66D8,
 0x42:0x005C4D40,0x5E:0x005C4D40,0x83:0x005C4F84,
 0x9A:0x005C4D40,0xB9:0x005C0028,0xC4:0x005C5AF8,
 0xCD:0x005C4D40,0xD8:0x005B66D8,0xE3:0x005C0028,
 0xED:0x005C4D40,0x113:0x005C4D40,0x15F:0x005C5B18}
def main():
 image=cf.verified_target();base,sections=pe.parse_sections(image)
 original=pe.raw_at(image,base,sections,HEAD,SIZE)
 assert hashlib.sha256(original).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ins)==97 and ins[-1].address+ins[-1].size==HEAD+SIZE
 original_calls={i.address-HEAD:
     (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
     for i in ins if i.size==5 and i.bytes[0]==0xE8}
 original_data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
     for p in pe.physical_highlow(image,base,sections) if HEAD<=p<HEAD+SIZE}
 assert original_calls==CALLEES and original_data==DATA
 assert [i.mnemonic for i in ins[4:7]]==['mov','test','je'],[
     (i.mnemonic,i.op_str) for i in ins[:9]]
 assert [i.address-HEAD for i in ins if i.mnemonic=='nop']==[0x13F,0x16B]
 code,rel=cf.object_function(ROOT/'build/core1138-canonical/WindowFramePacedBoss370.obj',SYM,SIZE)
 assert len(code)==SIZE and len(rel)==30
 assert [r['offset']-1 for r in rel if r['type']=='REL32']==list(CALLEES)
 assert [r['offset'] for r in rel if r['type']=='DIR32']==list(DATA)
 assert all(r['addend']==0 for r in rel)
 mask={j for r in rel for j in range(r['offset'],r['offset']+4)}
 assert len(mask)==120
 assert all(left==right for j,(left,right) in enumerate(zip(original,code)) if j not in mask)
 for unit,size in [('window_frame_paced_boss_370',370),
                   ('window_paced_present_385',385),
                   ('window_frame_controller_boss_433',433),
                   ('window_frame_no_wait_boss_583',583)]:
  proof=cf.compare_unit(unit)
  assert proof['result']=='exact' and proof['matched_bytes']==size,unit
 print('PASS native 370B/97-i386 whole SHA and genuine constant-true near-branch instructions')
 print('PASS source 370/370B, all 15 E8 and 15 HIGHLOW physical sites and destinations, 250/250 ordinary bytes')
 print('PASS prior 385B Presenter, 433B controller and 583B controller remain exact')
if __name__=='__main__':main()
