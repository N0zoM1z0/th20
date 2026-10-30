#!/usr/bin/env python3
"""Original 96B Animation corner geometry data and 1486B rotated Boss frontier.

The original PE alone verifies the entire game .rdata owner and the native
1486B/372-x86 function, all actual E8/HIGHLOW physical targets and game
callers. A separate source COFF test verifies 96/96 exact game data bytes.
The parent remains NONEXACT: ordinary source emits 1485B with one missing
compiler NOP. An optional in-memory diagnostic can align the nonrelocation
bytes; this NEVER alters an object/PE, creates a strict unit, or earns bytes.
"""
from pathlib import Path
from collections import Counter
import importlib.util,subprocess,struct,re,hashlib,argparse
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('original',ROOT/'scripts/verify-animation-draw-boss-native.py')
orig=importlib.util.module_from_spec(sp);sp.loader.exec_module(orig)
SYMBOL='?native_quad_axis_layout@th20@@3QBUNativeQuadAxisLayout@1@B'
DATA_HEAD=0x0056E140;DATA_SIZE=96;HEAD=0x0043EF20;SIZE=1486
SHA='8621c0a23993a5becd293c6d5a8653fa9a65184e716027098d635e3096f5968b'
CALLS={
 0x016:0x00437CD0,0x021:0x00437770,0x03C:0x00429210,
 0x045:0x004292E0,0x04E:0x00439820,0x05C:0x004292E0,
 0x065:0x004397C0,0x3D0:0x004376E0,
 0x432:0x00445AD0,0x497:0x00445AD0,0x4FA:0x00445AD0,
 0x55F:0x00445AD0,0x5C3:0x005429EE,
}
HIGHLOW={
 0x007:0x005B25C0,0x087:DATA_HEAD,0x0A5:DATA_HEAD,
 0x19A:0x005B8818,0x1AC:0x005B8818,0x1DD:0x005B8818,
 0x1E5:0x0056E0EC,0x1F7:0x005B8818,0x1FF:0x0056E0EC,
}
EXPECTED=[
  (-0.5,0.5,-0.5,0.5),(0.0,1.0,0.0,1.0),(-1.0,0.0,-1.0,0.0),
  (-0.5,-0.5,0.5,0.5),(0.0,0.0,1.0,1.0),(-1.0,-1.0,0.0,0.0),
]
CALLERS=[(0x0043F630,97,0x0043F678),(0x00445770,244,0x00445817)]


def compiled_symbol_bytes(path:Path, symbol:str, length:int):
 raw=path.read_bytes()
 rows=[x for x in subprocess.check_output(['objdump','-t',str(path)],text=True).splitlines() if x.endswith(' '+symbol)]
 assert len(rows)==1,rows
 m=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',rows[0]);assert m,rows[0]
 section,offset=int(m[1]),int(m[2],16)
 assert section>0
 sh=20+40*(section-1)
 size=struct.unpack_from('<I',raw,sh+16)[0]
 ptr=struct.unpack_from('<I',raw,sh+20)[0]
 section_name=raw[sh:sh+8].rstrip(b'\x00').decode()
 assert offset+length<=size
 return raw[ptr+offset:ptr+offset+length],section_name


def verify(original_object:Path|None=None, rotated_object:Path|None=None):
 pe,_=orig.verified_target();base,sects=orig.parse_sections(pe)
 native_table=orig.raw_at(pe,base,sects,DATA_HEAD,DATA_SIZE)
 assert hashlib.sha256(native_table).hexdigest()==SHA
 assert [struct.unpack_from('<4f',native_table,i*16) for i in range(6)]==EXPECTED
 if original_object is not None:
  compiled,section=compiled_symbol_bytes(original_object,SYMBOL,DATA_SIZE)
  assert section=='.rdata' and compiled==native_table
  print(f'PASS native original 96B source table at 0x{DATA_HEAD:X}, matched full .rdata from {original_object}, sha256 {SHA}')
 else:
  print(f'PASS original PE 96B exactly 2x3x4 float axes and immutable SHA256 {SHA}')
 ops=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(orig.raw_at(pe,base,sects,HEAD,SIZE),HEAD))
 assert len(ops)==372 and ops[-1].address+ops[-1].size==HEAD+SIZE
 assert ops[2].mnemonic=='sub' and ops[2].op_str=='esp, 0x54'
 assert ops[-1].mnemonic=='ret' and ops[-1].op_str=='0x14'
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ops if len(i.bytes)==5 and i.bytes[0]==0xe8}
 assert calls==CALLS,(calls,CALLS)
 fields={r-HEAD:struct.unpack('<I',orig.raw_at(pe,base,sects,r,4))[0]
         for r in orig.physical_highlow(pe,base,sects) if HEAD<=r<HEAD+SIZE}
 assert fields==HIGHLOW,(fields,HIGHLOW)
 by={i.address-HEAD:i for i in ops}
 assert by[0x041].mnemonic=='nop' and by[0x041].bytes==b'\x90'
 assert by[0x081].mnemonic=='shl' and by[0x081].op_str=='edx, 4'
 assert by[0x09F].mnemonic=='shl' and by[0x09F].op_str=='eax, 4'
 assert Counter(calls.values())[0x00445AD0]==4
 assert Counter(fields.values())[DATA_HEAD]==2
 disasm=Cs(CS_ARCH_X86,CS_MODE_32)
 for h,size,site in CALLERS:
  matched=[i for i in disasm.disasm(orig.raw_at(pe,base,sects,h,size),h) if i.address==site]
  assert len(matched)==1 and matched[0].bytes[0]==0xe8 and len(matched[0].bytes)==5
  i=matched[0];target=(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
  assert target==HEAD,(hex(h),hex(site),hex(target))
 print('PASS immutable original 1486B/372-x86 rotated projection Boss, true 0x54 frame/RET0x14, actual Angle ctor NOP at +0x41')
 print('PASS all 13 original E8 physical call/destination roles, 9 real PE HIGHLOW field/target pairs and two independent caller E8 sites')
 if rotated_object is not None:
  sp=importlib.util.spec_from_file_location('cmp',ROOT/'scripts/compare-coff-function.py')
  cmp=importlib.util.module_from_spec(sp);sp.loader.exec_module(cmp)
  sym='?project_rotated_corners_43ef20@NativeAnimationCornerProjector@th20@@QAEXPAVAnimation@2@PAUVector3@2@111@Z'
  code,rel=cmp.object_function(rotated_object,sym,1485)
  ins=list(disasm.disasm(code,HEAD))
  assert len(code)==1485 and len(ins)==371
  assert Counter(x['type'] for x in rel)==Counter({'REL32':13,'DIR32':9})
  # Verify original PE physical roles against unmodified relocated C++
  # candidates with the only native source-code insertion modeled IN MEMORY.
  order=[]
  for x in rel:
   off=x['offset']+(1 if x['offset']>=0x41 else 0)
   if x['type']=='REL32':
    assert code[x['offset']-1]==0xe8
    assert off-1 in CALLS
    order.append((off-1,'E8'))
   else:assert off in HIGHLOW;order.append((off,'HIGHLOW'))
  assert len(order)==22
  original_code=orig.raw_at(pe,base,sects,HEAD,SIZE)
  aligned=code[:0x41]+b'\x90'+code[0x41:]
  assert len(aligned)==SIZE and aligned[0x41]==0x90
  mask=set()
  for x in rel:
   off=x['offset']+(1 if x['offset']>=0x41 else 0)
   mask.update(range(off,off+4))
  mismatch=[i for i in range(SIZE) if i not in mask and original_code[i]!=aligned[i]]
  assert not mismatch,mismatch[:30]
  print('PASS diagnostic only: candidate 1485B/371 x86; modeled missing original +0x41 NOP solely in private in-memory comparison')
  print(f'PASS {SIZE-len(mask)}/{SIZE-len(mask)} virtual-align nonrelocation bytes; UNPATCHED compiler object is NOT original whole exact, no canonical acceptance')

if __name__=='__main__':
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--data-object',type=Path,default=None)
 parser.add_argument('--rotated-object',type=Path,default=None)
 args=parser.parse_args()
 verify(args.data_object,args.rotated_object)
