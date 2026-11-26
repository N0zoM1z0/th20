#!/usr/bin/env python3
"""Immutable original 294B ASCII text submit and nonexact typed C++20 frontier.

The source 292B candidate is NEVER compared to a shortened native extent.
All seven original E8 destinations are read from the locked original PE.
"""
import argparse,hashlib,importlib.util,re,struct,subprocess,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('sub294pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('sub294coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x0044FFF0
SIZE=294
SHA='daf9779671bfb7d0dfa8918eaadbbe26c68a659255a569e7ded769d0b3144f53'
E8={0x041:0x004140F0,0x06C:0x00415830,0x092:0x00414400,
    0x0AB:0x004140F0,0x0D4:0x00415830,0x0FA:0x00414400,
    0x10F:0x00414400}
DATA={0x06:0x005686FD,0x15:0x005B25C0}
SYM='?submit_text_44fff0@NativeTextSubmitOwner@th20@@QAE?AUNativeTextDrawResult8@2@PAUIDirect3DBaseTexture9@@PAUSpriteData@2@HHIPBDHHHPBUNativeTextTransform4@2@HV?$function@$$A6AXXZ@std@@@Z'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify_owned_eh(obj,img,base,sections):
 raw=obj.read_bytes();symbols=subprocess.check_output(['objdump','-t',str(obj)],text=True).splitlines()
 info='__ehfuncinfo$'+SYM
 row=next(r for r in symbols if r.endswith(' '+info))
 m=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',row)
 assert m and int(m[2],16)==8
 sh=20+40*(int(m[1])-1);size,offset,reloc=struct.unpack_from('<III',raw,sh+16)
 assert raw[sh:sh+8]==b'.xdata$x' and (size,struct.unpack_from('<H',raw,sh+32)[0])==(44,2)
 data=bytearray(raw[offset:offset+size]);symoff,count=struct.unpack_from('<II',raw,8);strings=raw[symoff+count*18:]
 for i,(field,target,name) in enumerate([(4,0x005686F0,'__unwindfunclet$'+SYM+'$0'),
                                       (16,0x005A9E88,'__unwindtable$'+SYM)]):
  actual,index,kind=struct.unpack_from('<IIH',raw,reloc+10*i)
  observed=coff.coff_name(raw[symoff+18*index:][:8],strings)
  assert (actual,kind,observed)==(field,6,name) and struct.unpack_from('<I',data,field)[0]==0
  struct.pack_into('<I',data,field,target)
 # Reuse the reviewed handler/owned cleanup anchor; locate full metadata
 # independently with its map self-pointer excluded from the search.
 hits=[]
 for name,_,rva,length,off in sections:
  if name!=b'.rdata':continue
  area,start=img[off:off+length],0
  while (start:=area.find(data[:16],start))>=0:
   if all(area[start+i]==b for i,b in enumerate(data) if not 16<=i<20):hits.append(base+rva+start)
   start+=1
 assert hits==[0x005A9E88] and data==pe.raw_at(img,base,sections,0x005A9E88,44)
 high={p-0x005A9E88 for p in pe.physical_highlow(img,base,sections) if 0x005A9E88<=p<0x005A9EB4}
 assert high=={4,16}
 bindings={'??1?$function@':0x00414400,'@__security_check_cookie@4':0x005429EE,
           info:0x005A9E90,'___CxxFrameHandler3':0x00544722}
 for symbol,address,size in [('__unwindfunclet$'+SYM+'$0',0x005686F0,13),
                             ('__ehhandler$'+SYM,0x005686FD,29)]:
  body,rows=coff.object_function(obj,symbol,size)
  for r in rows:
   targets=[a for prefix,a in bindings.items() if r['symbol'].startswith(prefix)]
   assert len(targets)==1 and r['addend']==0 and r['type']==('DIR32' if r['symbol']==info else 'REL32')
   value=targets[0] if r['type']=='DIR32' else (targets[0]-address-r['offset']-4)&0xffffffff
   struct.pack_into('<I',body,r['offset'],value)
  assert body==pe.raw_at(img,base,sections,address,size)
 print('PASS complete 42B owned EH code and 44B one-state metadata; cleanup destroys the incoming callback')

def verify(candidate):
 canonical=candidate is None
 if canonical:
  unit=coff.load_manifest('match-units.toml')['units']['ascii_text_submit_unwind_8']
  candidate=ROOT/unit['object']
 img,_=pe.verified_target();base,sections=pe.parse_sections(img)
 body=pe.raw_at(img,base,sections,HEAD,SIZE)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==106 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x58')
 assert calls(ins,HEAD)==E8
 data={x-HEAD:struct.unpack('<I',pe.raw_at(img,base,sections,x,4))[0]
       for x in pe.physical_highlow(img,base,sections) if HEAD<=x<HEAD+SIZE}
 assert data==DATA
 assert pe.raw_at(img,base,sections,HEAD+SIZE,5)==b'\xCC'*5
 parenthead=0x0044B020
 parent=pe.raw_at(img,base,sections,parenthead,578)
 assert hashlib.sha256(parent).hexdigest()=='fd121bcfb2bb70f0ea9015ed166f137eaa8fef7e663b5c4cbc781d0cee9a4617'
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,parenthead))
 assert len(pins)==139
 assert [off for off,target in calls(pins,parenthead).items() if target==HEAD]==[0x202]
 print('PASS immutable 294B/106-i386 text submit, two actual E8 to full 2,227B native text core')
 print('PASS three destruction sites for the incoming by-value callback and two argument copies; 7 E8/2 HIGHLOW, ret 0x58')
 print('PASS original 578B text renderer E8 +0x202 to this 294B native method')
 if candidate:
  b,rel=coff.object_function(candidate,SYM,292)
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b),0))
  assert len(b)==292 and len(ci)==104 and len(rel)==9
  assert sum(r['type']=='REL32' for r in rel)==7
  assert sum(r['type']=='DIR32' for r in rel)==2
  mapped=[]
  for row in rel:
   sym=row['symbol']
   if row['type']=='REL32':
    if sym.startswith('??0?$function@'):mapped.append(0x004140F0)
    elif sym.startswith('??1?$function@'):mapped.append(0x00414400)
    elif sym.startswith('?native_text_core_415830@'):mapped.append(0x00415830)
    else:raise AssertionError(('Unknown source E8 role',sym))
  assert mapped==list(E8.values())
  assert all(row['addend']==0 for row in rel)
  native_filtered=[i for i in ins if i.address-HEAD not in (0x97,0xFF)]
  assert len(native_filtered)==len(ci)==104
  native_nops=[i.address-HEAD for i in ins if i.mnemonic=='nop']
  assert native_nops==[0x97,0xFF,0x114]
  # The first two calls destroy the incoming callback on returning paths;
  # the third is the compiler-emitted fallthrough cleanup, not an EH funclet.
  for index,(left,right) in enumerate(zip(ci,native_filtered)):
   assert left.mnemonic==right.mnemonic and left.size==right.size,(index,left,right)
   if left.mnemonic not in ('call','je','jne','jmp') and right.address-HEAD not in (0x05,0x14):
    assert left.bytes==right.bytes,(index,left,right)
  expected_fields={0x06:'DIR32',0x15:'DIR32',0x42:'REL32',0x6D:'REL32',0x93:'REL32',
                   0xAB:'REL32',0xD4:'REL32',0xFA:'REL32',0x10E:'REL32'}
  assert {row['offset']:row['type'] for row in rel}==expected_fields
  print('FRONTIER: natural C++20 292B/104 i386, seven E8 original semantic roles/two data HIGHLOW')
  print('PASS 104/104 native instruction mnemonics and sizes after excluding ONLY the two authentic native NOPs')
  print('NONEXACT: two original one-byte post-destruction NOPs at +0x97 and +0xFF are absent; branch displacements adjust')
 verify_owned_eh(candidate,img,base,sections)
 if canonical:
  for name in ('ascii_text_submit_unwind_8','ascii_text_submit_eh_handler_29'):
   result=coff.compare_unit(name)
   assert result['result']=='exact' and result['matched_compared_bytes']==result['compared_size'],name
  print('PASS two whole canonical EH units from one fresh submit provider')
 print('NONEXACT: no strict unit or authored-game credit for the 294B submit body')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
