#!/usr/bin/env python3
"""Immutable complete native 158B PMR glyph-list node constructor frontier.

Modern natural C++20 source generates 143B, not the 158B original;
this checker explicitly forbids treating that smaller candidate as exact.
"""
import hashlib,importlib.util,subprocess,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('q158pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('q158cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00413000
SHA='5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b'
PARENT=0x004131E0
PARENT_SHA='a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75'
E8={0x2F:0x00413F50,0x3E:0x004148D0,0x47:0x0040B280,0x5C:0x0040B280,0x7B:0x00413B00}
DATA={0x06:0x00567CBD,0x15:0x005B25C0}
PREFIX='??$?0V?$function@$$A6AXXZ@std@@@?$_List_node_emplace_op2@'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 body=pe.raw_at(image,base,sec,HEAD,158)
 assert hashlib.sha256(body).hexdigest()==SHA
 instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(instr)==51 and instr[-1].address+instr[-1].size==HEAD+158
 assert (instr[-1].mnemonic,instr[-1].op_str)==('ret','8')
 assert calls(instr,HEAD)==E8
 hl={x-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,x,4))[0]
     for x in pe.physical_highlow(image,base,sec) if HEAD<=x<HEAD+158}
 assert hl==DATA
 parent=pe.raw_at(image,base,sec,PARENT,151)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pi)==51 and calls(pi,PARENT)[0x5B]==HEAD
 assert calls(pi,PARENT)[0x7F]==0x00414350
 p=ROOT/'build/core1061-canonical/GlyphTextQueueList151.obj'
 symbols=subprocess.run(['strings',str(p)],capture_output=True,text=True,check=True).stdout.splitlines()
 sym=next(x for x in symbols if x.startswith(PREFIX))
 candidate,rel=cm.object_function(p,sym,143)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(candidate),0))
 assert len(candidate)==143 and len(ci)==46
 assert sum(x['type']=='REL32' for x in rel)==4
 assert sum(x['type']=='DIR32' for x in rel)==2
 assert all(x['addend']==0 for x in rel)
 assert any('_Alloc_construct_ptr' in x['symbol'] for x in rel)
 assert any('_Allocate@' in x['symbol'] for x in rel)
 assert any('construct@' in x['symbol'] for x in rel)
 assert cm.compare_unit('glyph_queue_allocator_construct_34')['result']=='exact'
 assert cm.compare_unit('glyph_queue_node_allocator_allocate_47')['result']=='exact'
 assert cm.compare_unit('glyph_queue_node_guard_dtor_118')['result']=='exact'
 print('PASS complete original 158B/51-i386 native glyph task-list node-emplace constructor and actual 151B/51 parent E8 +0x5B')
 print('PASS five original child E8 and two physical PE HIGHLOW; first-stage allocation ctor, real memory_resource and folded pointer forwarding')
 print('SOURCE-PRESENT NONEXACT: genuine std::pmr::list C++20 constructor is complete 143B/46 i386, four E8/two DIR32, not original 158B/51 five E8/two HIGHLOW')
 print('PASS independently whole exact 34B/47B allocation children and 118B guard; no native parent or authored-game byte credit')
if __name__=='__main__':verify()
