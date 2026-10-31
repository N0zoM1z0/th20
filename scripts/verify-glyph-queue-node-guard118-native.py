#!/usr/bin/env python3
"""Whole original 118B PMR node-emplace cleanup guard and true INT3 tail.

The native destructor ends at 118B and its complete COFF section also owns
five REAL original alignment 0xCC bytes, verified without padding source.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('guard118pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('guard118cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00414350
SHA='2178295c45864a5e293c4a6aa79c4cdad68014a9d1f2adb26202055d40416f52'
PARENT=0x004131E0
PARENT_SHA='a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75'
CALLS={0x3B:0x0040B280,0x56:0x00413CA0,0x61:0x004142E0}
DATA={0x06:0x00567750,0x15:0x005B25C0}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,118)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==41 and ins[-1].address+ins[-1].size==HEAD+118
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)==CALLS
 native_data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
              for p in hl if HEAD<=p<HEAD+118}
 assert native_data==DATA
 assert pe.raw_at(im,base,sec,HEAD+118,5)==b'\xCC'*5
 parent=pe.raw_at(im,base,sec,PARENT,151)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pi)==51 and calls(pi,PARENT)[0x7F]==HEAD
 assert calls(pi,PARENT)[0x5B]==0x00413000
 for unit,size in [('glyph_queue_allocator_destroy_17',17),('glyph_queue_function_destroy_at_16',16),
                  ('glyph_queue_allocator_destroy_48',48)]:
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==size and z['matched_bytes']==size
 result=cm.compare_unit('glyph_queue_node_guard_dtor_118')
 assert result['result']=='exact' and result['size']==118 and result['matched_bytes']==118
 assert result['compared_size']==123 and result['matched_compared_bytes']==123
 assert len(result['relocations'])==5
 print('PASS original whole 118B/41-i386 queue-node guard destructor, all three original E8 and two PE HIGHLOW independently pinned')
 print('PASS true native 118B ret plus five consecutive 0xCC alignment bytes, entire 123B MSVC contribution 123/123 exact')
 print('PASS complete original 151B/51-i386 list Emplace native E8 +0x7F -> this 118B destructor, +0x5B -> separate native 158B node constructor')
 print('PASS downstream original 17B/16B/48B generic destructors separately exact; no double credit')
 print('Source-present original 151B and 158B parent compiler bodies remain NONEXACT; this 118B guard is generic STL, not game-authored credit')
if __name__=='__main__':verify()
