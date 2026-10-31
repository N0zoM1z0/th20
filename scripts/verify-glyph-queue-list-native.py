#!/usr/bin/env python3
"""Original 151B PMR glyph queue Emplace and five complete STL child bodies.

All PE call and HIGHLOW destinations are independently hashed from the
immutable original. The genuine 151B parent is not accepted exact.
"""
import hashlib,importlib.util,struct,subprocess,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('queuepe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('queuecm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
MAIN=0x004131E0
MAIN_SHA='a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75'
MAIN_CALLS={0x1F:0x00416270,0x30:0x00540ED5,0x39:0x0040F160,
 0x45:0x0040B280,0x5B:0x00413000,0x74:0x00414EB0,
 0x7F:0x00414350,0x8C:0x005429EE}
MAIN_DATA={0x07:0x005B25C0,0x2C:0x0056C8BC}
SPEC={
 'glyph_queue_list_max_size_59':(0x00416270,59,22,'fbb799363d9bc646869ed1314c0932fa65dea9772c3a12c04952969383bca7eb',
       {0x0C:0x0040F160,0x12:0x00416240,0x1D:0x0040D0E0,0x2D:0x0040D980},{},'main',0x1F,''),
 'glyph_queue_list_transfer_124':(0x00414EB0,124,43,'3f8110ae940aa44247567cb1de04b5c4a037ca87b2a79700cc12e2453c01b7f7',
       {0x27:0x0040CD70,0x3D:0x0040CD70,0x71:0x005429EE},{0x07:0x005B25C0},'main',0x74,'4'),
 'glyph_queue_allocator_construct_34':(0x00413F50,34,13,'cb987dc9ffb6989d2b059632015e9f0f326a0822396ca2fba699599d6db9d529',
       {},{},'node_ctor',0x2F,'4'),
 'glyph_queue_allocator_max_size_19':(0x00416240,19,8,'765076ec36fcefd38225b12f20722a3f3a85351256de012e7f6fc9263ac16e35',
       {0x03:0x004111E0},{},'max_size',0x12,''),
 'glyph_queue_allocator_destroy_48':(0x004142E0,48,20,'7d11d178a3029a9e522e72d47b729829ba4333ec0c35d7c370778cd5721d4574',
       {0x26:0x00415460},{},'node_dtor',0x61,''),
}
PARENT={
 'main':(0x004131E0,151,'a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75',51),
 'node_ctor':(0x00413000,158,'5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b',51),
 'max_size':(0x00416270,59,'fbb799363d9bc646869ed1314c0932fa65dea9772c3a12c04952969383bca7eb',22),
 'node_dtor':(0x00414350,118,'2178295c45864a5e293c4a6aa79c4cdad68014a9d1f2adb26202055d40416f52',41),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 high=pe.physical_highlow(img,base,secs)
 main=pe.raw_at(img,base,secs,MAIN,151)
 assert hashlib.sha256(main).hexdigest()==MAIN_SHA
 mi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(main,MAIN))
 assert len(mi)==51 and mi[-1].address+mi[-1].size==MAIN+151
 assert (mi[-1].mnemonic,mi[-1].op_str)==('ret','8')
 assert calls(mi,MAIN)==MAIN_CALLS
 data={p-MAIN:struct.unpack('<I',pe.raw_at(img,base,secs,p,4))[0]
       for p in high if MAIN<=p<MAIN+151}
 assert data==MAIN_DATA
 bridge=pe.raw_at(img,base,secs,0x004162F0,56)
 assert hashlib.sha256(bridge).hexdigest()=='5213451236ddccc50439af53540e50639d92771ca89506c80233331e217ebac9'
 assert calls(list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bridge,0x004162F0)),0x004162F0)[0x2C]==MAIN
 print('PASS native 151B/51-i386 glyph queue Emplace, 8 real E8/2 PE HIGHLOW, actual 56B bridge E8 +0x2C')
 for unit,(head,n,count,sha,edges,reloc,par,calloff,ret) in SPEC.items():
  body=pe.raw_at(img,base,secs,head,n)
  assert hashlib.sha256(body).hexdigest()==sha
  inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(inst)==count and inst[-1].address+inst[-1].size==head+n
  assert (inst[-1].mnemonic,inst[-1].op_str)==('ret',ret)
  assert calls(inst,head)==edges
  physical={p-head:struct.unpack('<I',pe.raw_at(img,base,secs,p,4))[0]
            for p in high if head<=p<head+n}
  assert physical==reloc
  ph,pn,sha_parent,pcount=PARENT[par]
  pb=pe.raw_at(img,base,secs,ph,pn)
  assert hashlib.sha256(pb).hexdigest()==sha_parent
  pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pb,ph))
  assert len(pi)==pcount and calls(pi,ph)[calloff]==head
  evidence=cm.compare_unit(unit)
  assert evidence['result']=='exact' and evidence['size']==n and evidence['matched_bytes']==n
  assert len(evidence['relocations'])==len(edges)+len(reloc)
  print(f'PASS {unit}: original {n}B/{count} instructions, {len(edges)} E8/{len(reloc)} HL, authentic {par} E8 +0x{calloff:X}')
 obj=ROOT/'build/core1061-canonical/GlyphTextQueueList151.obj'
 syms=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 sym=next(x for x in syms if x.startswith('??$_Emplace@V?$function@'))
 candidate,r=cm.object_function(obj,sym,130)
 inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(candidate),0))
 assert len(candidate)==130 and len(inst)==44 and len(r)==9
 assert sum(x['type']=='REL32' for x in r)==7
 assert sum(x['type']=='DIR32' for x in r)==2
 print('NONEXACT native 151B original PMR list Emplace vs 130B/44 i386 C++20, 7 E8/2 DIR32')
 print('PASS 5 distinct generic whole-exact PMR list heads, 284 native bytes, zero added game-authored exact credit')
if __name__=='__main__':verify()
