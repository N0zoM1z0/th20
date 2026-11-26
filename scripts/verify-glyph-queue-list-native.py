#!/usr/bin/env python3
"""Verify glyph PMR-list insertion, allocator construction and owned EH."""
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
SPEC.update({
 'glyph_queue_list_emplace_151':(MAIN,151,51,MAIN_SHA,MAIN_CALLS,MAIN_DATA,'bridge',0x2C,'8'),
 'glyph_queue_node_ctor_158':(0x00413000,158,51,'5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b',
   {0x2F:0x00413F50,0x3E:0x004148D0,0x47:0x0040B280,0x5C:0x0040B280,0x7B:0x00413B00},
   {0x06:0x00567CBD,0x15:0x005B25C0},'main',0x5B,'8'),
 'glyph_queue_traits_construct_31':(0x00413B00,31,14,'a3636b851ea7f0edb5db28d8ebb7dec7d0f8ab35bec63ce5020865529280a463',
   {0x07:0x0040B280,0x17:0x00413B20},{},'node_ctor',0x7B,''),
 'glyph_queue_pmr_construct_78':(0x00413B20,78,30,'08c33c70016459c03dced99339d02febb1670f58f420e9e1a505dc0ceeb38cdb',
   {0x0D:0x0040B280,0x1E:0x00413D50,0x30:0x0040B670,0x40:0x00413A40},{},'traits_construct',0x17,'8'),
})

PARENT={
 'main':(0x004131E0,151,'a1e5d8303be8a6e2c711f15a2174863b26046d8fe8c8f7be913613b806321f75',51),
 'node_ctor':(0x00413000,158,'5f339325649d81d3a161cbcd2f58f2d6b434b36e8520a5e30126966d0fbeb31b',51),
 'max_size':(0x00416270,59,'fbb799363d9bc646869ed1314c0932fa65dea9772c3a12c04952969383bca7eb',22),
 'node_dtor':(0x00414350,118,'2178295c45864a5e293c4a6aa79c4cdad68014a9d1f2adb26202055d40416f52',41),
}
PARENT.update({
 'bridge':(0x004162F0,56,'5213451236ddccc50439af53540e50639d92771ca89506c80233331e217ebac9',22),
 'traits_construct':(0x00413B00,31,'a3636b851ea7f0edb5db28d8ebb7dec7d0f8ab35bec63ce5020865529280a463',14),
})

def verify_owned_eh(obj,im,base,secs):
 import re
 symbols=subprocess.check_output(['objdump','-t',str(obj)],text=True).splitlines()
 node=next(r.rsplit(' ',1)[-1] for r in symbols if ' ??$?0V?$function' in r and '_List_node_emplace_op2@' in r and '(ty   20)' in r)
 guard=next(r.rsplit(' ',1)[-1] for r in symbols if ' ??1?$_List_node_emplace_op2@' in r and '(ty   20)' in r)
 raw=obj.read_bytes();symoff,count=struct.unpack_from('<II',raw,8);strings=raw[symoff+count*18:]
 literal_name='??_C@_0O@NKNMEGII@list?5too?5long@'
 row=next(r for r in symbols if r.endswith(' '+literal_name))
 m=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',row);assert m
 sh=20+40*(int(m[1])-1);size,offset=struct.unpack_from('<II',raw,sh+16);value=int(m[2],16)
 assert raw[sh:sh+6]==b'.rdata' and value+14<=size
 assert raw[offset+value:offset+value+14]==pe.raw_at(im,base,secs,0x0056C8BC,14)==b'list too long\0'
 forward=next(r.rsplit(' ',1)[-1] for r in symbols if ' ??$forward@V?$function@' in r and '(ty   20)' in r)
 body,rows=cm.object_function(obj,forward,8)
 assert not rows and body==pe.raw_at(im,base,secs,0x0040B280,8)
 for symbol,handler,cleanup,metadata in ((node,0x00567CBD,13,0x005A9934),(guard,0x00567750,0,0x005A91B8)):
  row=next(r for r in symbols if r.endswith(' __ehfuncinfo$'+symbol))
  m=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',row)
  info_offset=8 if cleanup else 0
  assert m and int(m[2],16)==info_offset
  sh=20+40*(int(m[1])-1);size,offset,reloc=struct.unpack_from('<III',raw,sh+16);n=struct.unpack_from('<H',raw,sh+32)[0]
  assert (size,n)==((44,2) if cleanup else (36,0))
  data=bytearray(raw[offset:offset+size])
  expected=((4,handler-cleanup,'__unwindfunclet$'+symbol+'$0'),(16,metadata,'__unwindtable$'+symbol)) if cleanup else ()
  for i,(field,target,name) in enumerate(expected):
   actual,index,kind=struct.unpack_from('<IIH',raw,reloc+10*i)
   observed=cm.coff_name(raw[symoff+18*index:][:8],strings)
   assert (actual,kind,observed)==(field,6,name) and struct.unpack_from('<I',data,field)[0]==0
   struct.pack_into('<I',data,field,target)
  # Bind metadata by its contents and the previously pinned cleanup owner;
  # the node map's self-pointer is excluded from the independent search.
  hits=[]
  for name,_,rva,length,off in secs:
   if name!=b'.rdata':continue
   area,start=im[off:off+length],0
   while (start:=area.find(data[:16] if cleanup else data,start))>=0:
    if all(area[start+i]==b for i,b in enumerate(data) if not(cleanup and 16<=i<20)):hits.append(base+rva+start)
    start+=1
  assert hits==[metadata]
  assert data==pe.raw_at(im,base,secs,metadata,size)
  high={a-metadata for a in pe.physical_highlow(im,base,secs) if metadata<=a<metadata+size}
  assert high=={field for field,_,_ in expected}
  parts=[('__unwindfunclet$'+symbol+'$0',13,handler-13)] if cleanup else []
  parts += [('__ehhandler$'+symbol,29,handler)]
  for name,length,address in parts:
   body,rows=cm.object_function(obj,name,length)
   bindings={'??1?$_Alloc_construct_ptr@':0x004142E0,'@__security_check_cookie@4':0x005429EE,
             '___CxxFrameHandler3':0x00544722,'__ehfuncinfo$'+symbol:metadata+info_offset}
   for r in rows:
    targets=[target for prefix,target in bindings.items() if r['symbol'].startswith(prefix)]
    assert len(targets)==1 and r['addend']==0
    value=targets[0] if r['type']=='DIR32' else (targets[0]-address-r['offset']-4)&0xffffffff
    struct.pack_into('<I',body,r['offset'],value)
   assert body==pe.raw_at(im,base,secs,address,length)
  print(f'PASS complete {cleanup+29}B owned EH code and {size}B metadata at {metadata:#x}')

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
  print(f'PASS {unit}: original {n}B/{count} instructions, {len(edges)} E8/{len(reloc)} HL, authentic {par} E8 +0x{calloff:X}')
 manifest=cm.load_manifest('match-units.toml')['units']
 names=[name for name,u in manifest.items() if u['source']=='src/GlyphTextQueueList151.cpp']
 obj=ROOT/manifest['glyph_queue_list_emplace_151']['object']
 verify_owned_eh(obj,img,base,secs)
 for unit in names:
  result=cm.compare_unit(unit)
  assert result['result']=='exact' and result['matched_compared_bytes']==result['compared_size'],unit
 print(f'PASS {len(names)} whole canonical units from the one affected queue-list provider')
 print('PASS full151B insertion,158B node construction,31B traits and78B PMR construction; generic code has no authored-game credit')
if __name__=='__main__':verify()
