#!/usr/bin/env python3
"""Independent PE proof for four complete function<void()> base members.

All call edges are read from the immutable original, not derived from the
COFF symbol, relocation addends or any candidate instruction offsets.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('funcclass_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('funcclass_cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'ascii_func_class_ctor_25':(0x00413F80,25,12,'089d0981ad87f09792c183406c00c00f368ca07f09d54ea7e5075d1a7ea27a8b', {0x0C:0x00414C60},'','copy93',0x29),
 'ascii_func_class_reset_copy_71':(0x00414B90,71,27,'9e2d832d4bf8e6176e2f5c02905836278f55967032de6c2917b483184bc8485b',{0x0C:0x00414A80,0x1B:0x00414AD0,0x3B:0x00414C60},'4','copy93',0x3C),
 'ascii_func_class_dtor_20':(0x00414310,20,10,'9cbd4d93d66dfc32cc9ccad0d9d2f7cb54fdbaf4fc82ceff6130762dbe96ef68',{0x0A:0x00414D50},'','dtor20',0x0A),
 'ascii_func_class_set_30':(0x00414C60,30,12,'549a96cca7d84463191f9a6c361ce36eb8ea0d407c7f3a7ad15f52d77310a5b6',{},'4','ctor25',0x0C),
}
PARENTS={
 'copy93':(0x004140F0,93,'557c7cd46e973490cb1c19336e4988976baedac63924d7d6226fe4efa1c13bad',29),
 'dtor20':(0x00414400,20,'9f2ba240a91fa75f8c7bf95b1de5f98309e802f6922cdf0b4c847d2fd1cffdbe',10),
 'ctor25':(0x00413F80,25,'089d0981ad87f09792c183406c00c00f368ca07f09d54ea7e5075d1a7ea27a8b',12),
 'resetcopy71':(0x00414B90,71,'9e2d832d4bf8e6176e2f5c02905836278f55967032de6c2917b483184bc8485b',27),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img);hl=pe.physical_highlow(img,base,secs)
 for unit,(addr,size,count,sha,expected,ret,parent,off) in SPECS.items():
  b=pe.raw_at(img,base,secs,addr,size)
  assert hashlib.sha256(b).hexdigest()==sha
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,addr))
  assert len(ins)==count and ins[-1].address+ins[-1].size==addr+size
  assert (ins[-1].mnemonic,ins[-1].op_str)==('ret',ret)
  assert calls(ins,addr)==expected,(unit,calls(ins,addr),expected)
  assert not any(addr<=p<addr+size for p in hl)
  ph,pn,psha,pcount=PARENTS[parent]
  pb=pe.raw_at(img,base,secs,ph,pn)
  assert hashlib.sha256(pb).hexdigest()==psha
  pin=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,ph))
  assert len(pin)==pcount and calls(pin,ph)[off]==addr
  report=cm.compare_unit(unit)
  assert report['result']=='exact' and report['size']==size and report['matched_bytes']==size
  assert len(report['relocations'])==len(expected)
  print(f'PASS {unit}: whole {size}B/{count}-i386, {len(expected)} real E8/0 HIGHLOW and native {parent} +0x{off:X} caller')
 # Cross-link 71B reset-copy to native Set at 0x3B, another independently
 # observed original edge beyond the 25B constructor -> Set chain.
 assert SPECS['ascii_func_class_reset_copy_71'][5-1][0x3B]==0x00414C60
 print('PASS four distinct native standard function heads, 146B total; canonical 4/4 exact and no game-authored credit')
 print('PASS native 578B text render remains NONEXACT; exact child closure does not imply exactness')
if __name__=='__main__':verify()
