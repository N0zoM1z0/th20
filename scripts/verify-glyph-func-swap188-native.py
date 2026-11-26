#!/usr/bin/env python3
"""Verify whole native function movement/swap and queue-pump EH ownership."""
import hashlib,importlib.util,re,struct,subprocess,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('swap188pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('swap188cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00414C80
SHA='bd26afa8cbf43e1b3a8a8537b77b089f737ca7a740074f1d8ac3fbdb11d85858'
PARENT=0x00417A90
PARENT_SHA='c9ad68875594b49feb0f43c0fb920cff68c9d95fe7404452e0eb9de1f65824e6'
CALLS={0x16:0x00414AF0,0x25:0x00414AF0,0x34:0x00414AD0,
 0x3F:0x00414AD0,0x48:0x00414C60,0x54:0x00414C60,
 0x5F:0x00413F80,0x68:0x0040B280,0x74:0x00414BE0,
 0x7D:0x0040B280,0x89:0x00414BE0,0x92:0x0040B280,
 0x9E:0x00414BE0,0xA6:0x00414310,0xB1:0x005429EE}
DIR32={0x07:0x005B25C0}
PREFIX='?_Swap@?$_Func_class@X$$V@std@@'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify_move_forward(obj,im,base,sec,manifest):
 unit=manifest['glyph_queue_func_class_swap_188']
 _,rows=cm.object_function(obj,unit['symbol'],188)
 moves=[r for r in rows if r['symbol'].startswith('??$move@AAV?$_Func_class@')]
 assert [r['offset'] for r in moves]==[0x69,0x7E,0x93]
 assert len({r['symbol'] for r in moves})==1
 body,relocations=cm.object_function(obj,moves[0]['symbol'],8)
 assert not relocations and body==pe.raw_at(im,base,sec,0x0040B280,8)
 print('PASS actual out-of-line std::move<_Func_class<void>&> identity at all three swap sites')

def verify_pump_eh(obj,im,base,sec):
 symbol='?glyph_task_pump_416140@th20@@YAXXZ'
 raw=obj.read_bytes();symbols=subprocess.check_output(['objdump','-t',str(obj)],text=True).splitlines()
 row=next(s for s in symbols if s.endswith(' __ehfuncinfo$'+symbol))
 m=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',row)
 assert m and int(m[2],16)==24
 sh=20+40*(int(m[1])-1);size,offset,reloc=struct.unpack_from('<III',raw,sh+16)
 assert (size,struct.unpack_from('<H',raw,sh+32)[0])==(60,4)
 data=bytearray(raw[offset:offset+size])
 symoff,count=struct.unpack_from('<II',raw,8);strings=raw[symoff+count*18:]
 expected=[(4,0x00567E10,'__unwindfunclet$'+symbol+'$0'),
           (12,0x00567E18,'__unwindfunclet$'+symbol+'$1'),
           (20,0x00567E20,'__unwindfunclet$'+symbol+'$2'),
           (32,0x005A98CC,'__unwindtable$'+symbol)]
 for i,(field,target,name) in enumerate(expected):
  actual,index,kind=struct.unpack_from('<IIH',raw,reloc+10*i)
  observed=cm.coff_name(raw[symoff+18*index:][:8],strings)
  assert (actual,kind,observed)==(field,6,name) and struct.unpack_from('<I',data,field)[0]==0
  struct.pack_into('<I',data,field,target)
 # The cleanup owner follows the previously pinned 0x567E2D handler.
 # Locate its complete metadata independently, excluding the map self-pointer.
 hits=[]
 for name,_,rva,length,off in sec:
  if name!=b'.rdata':continue
  area,start=im[off:off+length],0
  while (start:=area.find(data[:24],start))>=0:
   if all(area[start+i]==b for i,b in enumerate(data) if not 32<=i<36):hits.append(base+rva+start)
   start+=1
 assert hits==[0x005A98CC]
 assert data==pe.raw_at(im,base,sec,0x005A98CC,60)
 high={p-0x005A98CC for p in pe.physical_highlow(im,base,sec) if 0x005A98CC<=p<0x005A9908}
 assert high=={4,12,20,32}
 print('PASS complete 60B queue-pump metadata, three unwind actions and four physical DIR32 fields')

def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im)
 original=pe.raw_at(im,base,sec,HEAD,188)
 assert hashlib.sha256(original).hexdigest()==SHA
 ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ni)==63 and ni[-1].address+ni[-1].size==HEAD+188
 assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','4')
 assert calls(ni,HEAD)==CALLS
 hl={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
     for x in pe.physical_highlow(im,base,sec) if HEAD<=x<HEAD+188}
 assert hl==DIR32
 p=pe.raw_at(im,base,sec,PARENT,26)
 assert hashlib.sha256(p).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p,PARENT))
 assert len(pi)==12 and calls(pi,PARENT)[0x0E]==HEAD
 manifest=cm.load_manifest('match-units.toml')['units']
 obj=ROOT/manifest['glyph_queue_func_class_swap_188']['object']
 verify_move_forward(obj,im,base,sec,manifest)
 verify_pump_eh(obj,im,base,sec)
 for name,head,size,count,sha,edges in [
  ('glyph_queue_func_move_ctor_46',0x004140C0,46,18,'56a11a2c04ab37a80184f042adaff7918280e0c243bfe65ca3795c2f9946fe8c',
   {0x0A:0x00413F80,0x13:0x0040B280,0x1F:0x00414BE0}),
  ('glyph_queue_func_reset_move_125',0x00414BE0,125,44,'7ce39dfeb58413ed98a6f39ce1b046753e25178ef98d2b74704e98431b7a70a6',
   {0x0C:0x00414A80,0x1B:0x00414AF0,0x2A:0x00414AD0,0x4B:0x00414C60,
    0x53:0x00414D50,0x5E:0x00414AD0,0x67:0x00414C60,0x71:0x00414C60})]:
  body=pe.raw_at(im,base,sec,head,size)
  assert hashlib.sha256(body).hexdigest()==sha
  inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,head))
  assert len(inst)==count and inst[-1].address+inst[-1].size==head+size
  assert (inst[-1].mnemonic,inst[-1].op_str)==('ret','4')
  assert calls(inst,head)==edges
  assert not any(head<=p<head+size for p in pe.physical_highlow(im,base,sec))
  print(f'PASS complete native {name}: {size}B/{count} instructions, all {len(edges)} direct calls')
 sources={'src/GlyphTextQueuePump254.cpp','src/GlyphTaskAllocatorConstruct.cpp'}
 names=[name for name,u in manifest.items() if u['source'] in sources]
 for name in names:
  result=cm.compare_unit(name)
  assert result['result']=='exact' and result['matched_compared_bytes']==result['compared_size'],name
 print('PASS complete 188B/63-instruction swap, fifteen calls and security-cookie field')
 print('PASS complete 68B pump EH code including five INT3 tail bytes, with double-cookie handler')
 print(f'PASS {len(names)} scoped canonical units from two providers; no new authored-game credit')
if __name__=='__main__':verify()
