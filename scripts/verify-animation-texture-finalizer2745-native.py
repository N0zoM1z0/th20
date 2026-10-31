#!/usr/bin/env python3
"""Whole native original 2745B ANM texture alpha-fringe Boss frontier.

Original jump tables after the code extent are genuine PE data, not
code to shave off or synthetic exact units. Source remains NONEXACT.
"""
import csv,hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('texfinpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('texfincm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00451910
SHA='1b4a86d1336a36cd506b27e58c8e750b26874ec42a1a8da94e8e96fadfa58924'
E8={0x18C:0x00451880,0x1B6:0x00451880,0x1E4:0x00451880,0x215:0x00451880,
    0x3C3:0x00451640,0x3ED:0x00451640,0x417:0x00451640,0x444:0x00451640,
    0x652:0x00451700,0x67C:0x00451700,0x6A6:0x00451700,0x6D3:0x00451700,
    0x8E5:0x004517C0,0x90F:0x004517C0,0x939:0x004517C0,0x966:0x004517C0,
    0xAAE:0x005429EE}
HL={0x0A:0x005B25C0,0xA7:0x004523E0,0xAE:0x004523CC}
CALLS={0x00451880:(139,'?accumulate_texel8888@'),0x00451640:(183,'?accumulate_texel1555@'),
       0x00451700:(183,'?accumulate_texel4444@'),0x004517C0:(187,'?accumulate_texel8332@')}
SYM='?finalize_uploaded_texture_451910@NativeRendererTextureMemoryView@th20@@QAEXPAUIDirect3DTexture9@@@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 raw=pe.raw_at(im,base,sec,HEAD,2745)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==759 and ins[-1].address+ins[-1].size==HEAD+2745
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
 assert calls(ins,HEAD)==E8
 data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
       for p in high if HEAD<=p<HEAD+2745}
 assert data==HL
 assert all(list(E8.values()).count(a)==4 for a in CALLS)
 assert list(E8.values()).count(0x005429EE)==1
 assert HEAD+2745==0x004523C9
 assert pe.raw_at(im,base,sec,0x004523CC,20)==struct.pack('<5I',
  0x004519C2,0x00451BEF,0x00451E7E,0x0045210D,0x0045239B)
 assert [p for p in high if 0x004523CC<=p<0x004523E0]==[
  0x004523CC,0x004523D0,0x004523D4,0x004523D8,0x004523DC]
 # Native second format-index mapping table is 28 bytes and contains
 # no HIGHLOW; it is separate from the physical 2745B function body.
 fmtmap=pe.raw_at(im,base,sec,0x004523E0,28)
 assert fmtmap.hex()=='00040404040404040404040404040404040404040400040404010204'
 assert not any(0x004523E0<=p<0x004523FC for p in high)
 for addr,(n,_) in CALLS.items():
  child=pe.raw_at(im,base,sec,addr,n)
  decoded=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(child,addr))
  assert decoded and decoded[-1].address+decoded[-1].size==addr+n
  assert decoded[-1].mnemonic=='ret'
 obj=ROOT/'build/core1101-probes/AnimationTextureFinalize2745.obj'
 body,rels=cm.object_function(obj,SYM,2558)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,0))
 assert len(body)==2558 and len(ci)==718 and len(rels)==25
 assert sum(x['type']=='REL32' for x in rels)==17
 assert sum(x['type']=='DIR32' for x in rels)==8
 assert all(x['addend']==0 for x in rels)
 lastret=next(i for i in reversed(ci) if i.mnemonic=='ret')
 assert lastret.address+lastret.size==0x9C9 and lastret.op_str=='4'
 assert [x['offset'] for x in rels if x['type']=='DIR32']==[
   0x0A,0xA5,0xAC,0x9CC,0x9D0,0x9D4,0x9D8,0x9DC]
 for addr,(_,prefix) in CALLS.items():
  assert sum(x['type']=='REL32' and x['symbol'].startswith(prefix) for x in rels)==4,hex(addr)
 assert sum(x['type']=='REL32' and x['symbol']=='@__security_check_cookie@4' for x in rels)==1
 assert cm.compare_unit('animation_texture_upload_from_memory_562')['result']=='exact'
 print('PASS immutable entire original 2745B/759-i386 game Renderer texture alpha-fringe finalizer, 17 real E8/3 in-code PE HIGHLOW')
 print('PASS original four different native format branches UNKNOWN/A8R8G8B8, A1R5G5B5, A4R4G4B4, A8R3G3B2; each 4 genuine E8 to distinct 139B/183B/183B/187B neighbor helpers')
 print('PASS original five-target PE jump table at 0x004523CC and 28B format mapping table at 0x004523E0, both OUTSIDE the 2745B physical function extent')
 print('SOURCE-PRESENT NONEXACT: real four-format C++20 source compiles 2558B COFF contribution /718 decoder instructions; 17 correct call roles but 8 COFF DIR32 incl 5 jump-table data relocations')
 print('PASS distinct original whole 562B texture upload caller remains strict exact; no 2745B or helper authored-game code credited')
if __name__=='__main__':verify()
