#!/usr/bin/env python3
"""Original PE-only complete Motion polygon 76B fan / 104B outline callers.

Read actual immutable original body boundaries/ABI, E8 callsite targets,
PE HIGHLOW fields, native parent callsites and the actual 16.0f constant.
The 76B whole fan wrapper can be independently source-accepted; the 104B
outline wrapper remains NONEXACT unless a real source emits its native ESI
register lifetime. Never patch candidate/source to fake acceptance.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
CASES={
 'outline_caller_104':{
  'head':0x0045FAA0,'size':104,'ins':36,'frame':'esp, 0x10','ret':'4',
  'calls':{0x1A:0x00414580,0x2D:0x0040BDA0,0x5B:0x0043D370},
  'data':{0x3E:0x0056CD90,0x57:0x005C0028},
  'parent_site':0x0045FA5F,
 },
 'fan_caller_76':{
  'head':0x0045FB10,'size':76,'ins':27,'frame':'esp, 0x10','ret':'4',
  'calls':{0x19:0x00414580,0x24:0x0040BDA0,0x40:0x0043CB70},
  'data':{0x3C:0x005C0028},
  'parent_site':0x0045FA84,
 },
}

def verify():
 img,_=pe.verified_target();base,sections=pe.parse_sections(img)
 highlow=pe.physical_highlow(img,base,sections)
 parent_head=0x0045F9B0
 parent=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(img,base,sections,parent_head,233),parent_head))
 for label,c in CASES.items():
  head=c['head'];size=c['size']
  body=pe.raw_at(img,base,sections,head,size)
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(ins)==c['ins'] and ins[-1].address+ins[-1].size==head+size,(label,len(ins))
  assert ins[2].mnemonic=='sub' and ins[2].op_str==c['frame']
  assert ins[-1].mnemonic=='ret' and ins[-1].op_str==c['ret']
  callmap={i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if len(i.bytes)==5 and i.bytes[0]==0xE8}
  assert callmap==c['calls'],(label,callmap)
  datamap={a-head:struct.unpack('<I',pe.raw_at(img,base,sections,a,4))[0]
           for a in highlow if head<=a<head+size}
  assert datamap==c['data'],(label,datamap)
  origin=[i for i in parent if i.address==c['parent_site']]
  assert len(origin)==1 and len(origin[0].bytes)==5 and origin[0].bytes[0]==0xE8
  site=origin[0]
  assert ((site.address+5+struct.unpack_from('<i',site.bytes,1)[0])&0xffffffff)==head
  assert any(i.mnemonic=='push' and i.op_str==('1' if size==104 else '0') for i in ins)
  assert any(i.mnemonic=='push' and i.op_str==('0x3c' if size==104 else '0x3d') for i in ins)
  assert any(i.mnemonic=='nop' for i in ins)
  print(f'PASS original whole {label} native {size}B/{len(ins)} i386, real frame {c["frame"]}, RET {c["ret"]}')
  print(f'PASS original {len(callmap)} E8 site/target pairs, {len(datamap)} PE HIGHLOW field/target pairs, native parent E8 at {site.address:#010x}')
 assert struct.unpack('<f',pe.raw_at(img,base,sections,0x0056CD90,4))[0]==16.0
 print('PASS original 16.0f outline width at 0x56CD90 and real renderer global 0x5C0028; 104B remains separately nonexact until complete source replay')

if __name__=='__main__':verify()
