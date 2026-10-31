#!/usr/bin/env python3
"""Independent whole locked-PE proof of the native GDI canvas release graph.

Original physical extents: 97B allocator::release_object, 16B STL
std::destroy_at, 49B scalar-deleting destructor, 62B real destructor
followed by five independently native INT3 alignment bytes. Both the
original 360B uploader and 124B canvas constructor are independently pinned.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('canvaslifepe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('canvaslifecm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'glyph_canvas_allocator_release_97':(0x00413BE0,97,33,'843797acd1750b9ccdc2b052dd523a64794fc3da1678e9f73f841c9d96dfded4',
  {0x1F:0x00413CD0,0x2E:0x0040C310,0x37:0x0040B730,0x40:0x005429FC,0x4B:0x0040B900,0x56:0x005429EE},
  {0x07:0x005B25C0,0x2A:0x005C0240},'4'),
 'glyph_canvas_destroy_at_16':(0x00413CD0,16,8,'9fb315c8680ef95449989d6f70927d7d1fb25c306b2ac18f480eca7b0c65c5b4',
  {0x08:0x004147E0},{},''),
 'glyph_canvas_scalar_deleting_dtor_49':(0x004147E0,49,18,'8840f29b61c1350c8d795d720a6d1811a26d33815cc99656e626f9c14fd0d50b',
  {0x0A:0x00414460,0x20:0x0054278D},{},'4'),
 'glyph_canvas_destructor_62':(0x00414460,62,22,'d9d5ef3df338f8174402f912e2bb04d827490be090fd184f85fefccce32e1709',
  {0x29:0x00416360},{0x06:0x00567600,0x13:0x005B25C0},''),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 high=pe.physical_highlow(image,base,sec)
 seen=set()
 for unit,(head,n,count,sha,targets,data,ret) in SPECS.items():
  original=pe.raw_at(image,base,sec,head,n)
  assert hashlib.sha256(original).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+n
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret',ret)
  assert calls(ins,head)==targets
  physical={x-head:struct.unpack('<I',pe.raw_at(image,base,sec,x,4))[0]
            for x in high if head<=x<head+n}
  assert physical==data
  assert not (seen & set(range(head,head+n)))
  seen.update(range(head,head+n))
  accepted=cm.compare_unit(unit)
  assert accepted['result']=='exact' and accepted['size']==n and accepted['matched_bytes']==n
  assert len(accepted['relocations'])==len(targets)+len(data)
  if unit=='glyph_canvas_destructor_62':
   assert pe.raw_at(image,base,sec,head+n,5)==b'\xCC'*5
   assert accepted['compared_size']==67 and accepted['matched_compared_bytes']==67
   assert len(accepted['relocations'])==3
  print(f'PASS native {unit} whole {n}B/{count}-i386, {len(targets)} physical E8, {len(data)} PE HIGHLOW')
 assert len(seen)==224
 uploader=pe.raw_at(image,base,sec,0x004145D0,360)
 assert hashlib.sha256(uploader).hexdigest()=='76223b12344a822e9f79546f3b197ce349d9b3467ebbbe2f3b65f73c411b0dcc'
 ui=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(uploader,0x004145D0))
 assert len(ui)==128 and calls(ui,0x004145D0)[0x124]==0x00413BE0
 surface=pe.raw_at(image,base,sec,0x00416360,182)
 assert hashlib.sha256(surface).hexdigest()=='632c4839135f7908fc5bda7f2a749944332b8ff3bb76de8484e428a03ce1258e'
 assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(image,base,sec,0x00414460,62),0x00414460)),0x00414460)[0x29]==0x00416360
 ctor=pe.raw_at(image,base,sec,0x00414200,124)
 assert hashlib.sha256(ctor).hexdigest()=='753f6983e88c30419652a69281f0f57138b3d583df317f85ad3be51e51fcc9dd'
 assert cm.compare_unit('glyph_canvas_constructor_124')['result']=='exact'
 assert cm.compare_unit('glyph_texture_upload_360')['result']=='exact'
 assert cm.compare_unit('glyph_canvas_release_182')['result']=='exact'
 print('PASS entire native 360B D3D9 upload E8 +0x124 to original 97B allocator release, real 124B canvas ctor and 182B surface release')
 print('PASS original 62B normal destructor and five trailing real native INT3 bytes, entire 67B compiler contribution, no fake code padding')
 print('PASS distinct 97B +49B+62B TH20-owned game functions (208B) and 16B generic std::destroy_at (no authored credit), all local exact')
if __name__=='__main__':verify()
