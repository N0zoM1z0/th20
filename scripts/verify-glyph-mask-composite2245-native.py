#!/usr/bin/env python3
"""Original whole 2245B glyph compositor and 4 native-exact PMR vector children.

Big Boss is SOURCE-PRESENT/NONEXACT; do not award its 2245 bytes. Genuine
children are accepted only via separate whole-extent canonical receipts.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph2245pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph2245cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00416420
SHA='06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad'
DATA={0x06:0x00567E75,0x18:0x005B25C0,0x57:0x0056C7E0,0x5D:0x005B8894,0x894:0x005B8894}
SPECS={
 'glyph_mask_offsets_vector_ctor_63':(0x004141C0,63,25,'5b64525640460b4bf2a1ca1d319561289b8e7bd91acdeb9236f144f6bd8bc82f',{0x17:0x00412E10,0x32:0x0040EC90},(0x0D2,0x44A),'',),
 'glyph_mask_offsets_vector_dtor_20':(0x00414440,20,10,'bea187ec35a9c0c408a803467e4111ede1fad6a19d50ad203d206605e8cb532a',{0x0A:0x00414E10},(0x420,0x885),'',),
 'glyph_mask_offsets_vector_begin_26':(0x00414F30,26,12,'db047528c06f10ed3961b6acd195d73434b9674a8bab904fc4d8ed7f3ac004f3',{0x0E:0x0040B280},(0x24B,0x613),'',),
 'glyph_mask_offsets_vector_end_26':(0x00414F70,26,12,'438927ecbee31817b9fe6e4c6deddcd7b5ef0897a8fdfb23bd7fae1f534c8a67',{0x0E:0x0040B280},(0x25C,0x624),'',),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);high=pe.physical_highlow(img,base,sec)
 b=pe.raw_at(img,base,sec,HEAD,2245)
 assert hashlib.sha256(b).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==612 and ins[-1].address+ins[-1].size==HEAD+2245
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x14')
 native_calls=calls(ins,HEAD)
 assert len(native_calls)==37
 native_data={pos-HEAD:struct.unpack('<I',pe.raw_at(img,base,sec,pos,4))[0]
              for pos in high if HEAD<=pos<HEAD+2245}
 assert native_data==DATA
 assert native_calls[0x32]==0x004156C0
 assert native_calls[0x44]==0x004156A0
 for off in (0x307,0x39A,0x6E0,0x797):assert native_calls[off]==0x00415800
 for name,(addr,size,count,sha,callrole,parents,_) in SPECS.items():
  child=pe.raw_at(img,base,sec,addr,size)
  assert hashlib.sha256(child).hexdigest()==sha
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(child,addr))
  assert len(ci)==count and ci[-1].address+ci[-1].size==addr+size
  assert ci[-1].mnemonic=='ret'
  assert calls(ci,addr)==callrole
  assert not any(addr<=p<addr+size for p in high)
  for site in parents:assert native_calls[site]==addr,(name,hex(site))
  report=cm.compare_unit(name)
  assert report['result']=='exact' and report['size']==size and report['matched_bytes']==size
  assert len(report['relocations'])==len(callrole)
  print(f'PASS {name}: whole {size}B/{count} original, {len(callrole)} native calls and both real 2245B parent E8 edges')
 print('PASS original entire 2245B/612-instruction glyph compositor, 37 E8/5 physical HIGHLOW and two distinct alpha paths')
 print('PASS four different generic PMR-vector heads total 135B whole exact, without game-authored credit')
 print('NONEXACT: 2245B game compositor has typed source but is not itself canonically accepted')
if __name__=='__main__':verify()
