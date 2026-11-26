#!/usr/bin/env python3
"""Audit the complete ANM parser and distinguish its two native frame slots."""
import argparse,hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32,CS_GRP_JUMP
from capstone.x86 import X86_OP_MEM,X86_REG_EBP,X86_REG_ESP
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('grp336pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('grp336cm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x0044EBF0
SHA='0ab86e2cc9985d672ff96e5fe0e9ae4b52b5a02c69b63e87a310344ae21b3a67'
E8={0x33:0x00454230,0x61:0x00454230,0xC6:0x00429120,
    0xDE:0x00410AA0,0x106:0x00454230,0x145:0x005429EE}
HL={0x0A:0x005B25C0,0x2A:0x0056E428,0x2F:0x005C0678,
    0x58:0x0056E464,0x5D:0x005C0678,0xBB:0x0056E0E4,
    0xFD:0x0056E488,0x102:0x005C0678}
SYM='?parse_group_44ebf0@NativeRendererAnmGroupView@th20@@QAEHPAUNativeAnimationFileLoadView@2@HPBUNativeAnmGroupHeader@2@@Z'
BINDINGS={
 '___security_cookie':0x005B25C0,
 '?native_anm_err_corrupt_56e428@th20@@3QBDB':0x0056E428,
 '?native_anm_err_version_56e464@th20@@3QBDB':0x0056E464,
 '?native_anm_err_texture_56e488@th20@@3QBDB':0x0056E488,
 '?diagnostic_log@th20@@3UDiagnosticLog@1@A':0x005C0678,
 '?report_log_error@th20@@YAPBDPAUDiagnosticLog@1@PBDZZ':0x00454230,
 '??$sprintf_s@$0BAE@@@YAHAAY0BAE@DPBDZZ':0x00429120,
 '?read_game_resource@th20@@YAPAEPBDPAHH@Z':0x00410AA0,
 '@__security_check_cookie@4':0x005429EE,
}
DEFAULT_OBJECT=ROOT/'build/gpt61-anm-group-probe/AnimationFileGroupParse336.obj'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
def slot_accesses(instructions,slot,head):
 result=[]
 for ins in instructions:
  for operand in ins.operands:
   if operand.type==X86_OP_MEM and operand.mem.base==X86_REG_EBP:
    assert operand.mem.index==0,'indexed frame access needs separate alias analysis'
    if operand.mem.disp<slot+4 and slot<operand.mem.disp+operand.size:
     result.append((ins.address-head,ins.mnemonic,ins.op_str,operand.size))
 return result

def verify(obj=DEFAULT_OBJECT):
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 body=pe.raw_at(im,base,sec,HEAD,336)
 assert hashlib.sha256(body).hexdigest()==SHA
 md=Cs(CS_ARCH_X86,CS_MODE_32);md.detail=True
 ni=list(md.disasm(body,HEAD))
 assert len(ni)==83 and ni[-1].address+ni[-1].size==HEAD+336
 assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','0xc')
 assert calls(ni,HEAD)==E8
 high={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
       for x in hl if HEAD<=x<HEAD+336}
 assert high==HL
 assert high[0xBB]==0x0056E0E4
 assert pe.raw_at(im,base,sec,0x0056E0E4,3)==b'%s\0'
 assert [high[k] for k in (0x2F,0x5D,0x102)]==[0x005C0678]*3
 assert calls(ni,HEAD)[0xC6]==0x00429120 and calls(ni,HEAD)[0xDE]==0x00410AA0
 assert [calls(ni,HEAD)[k] for k in (0x33,0x61,0x106)]==[0x00454230]*3
 # Three authentic original CP932 Japanese diagnostics in original .rdata.
 for off in (0x0056E428,0x0056E464,0x0056E488):
  assert pe.raw_at(im,base,sec,off,1)==bytes([0x83]),hex(off)
 assert body[0x05]==0x20 and body[0x1B]==0xE0
 assert slot_accesses(ni,-0x120,HEAD)==[(0x19,'mov','dword ptr [ebp - 0x120], 0',4)]
 assert slot_accesses(ni,-0x10C,HEAD)==[
  (0xD0,'lea','eax, [ebp - 0x10c]',4),
  (0x11D,'mov','ecx, dword ptr [ebp - 0x10c]',4)]
 for ins in ni:
  for operand in ins.operands:
   if operand.type==X86_OP_MEM:
    assert operand.mem.base!=X86_REG_ESP
    if ins.mnemonic=='lea' and operand.mem.base==X86_REG_EBP:
     assert operand.mem.disp>-0x120,'unowned zero slot address escapes'
 for address,conversions in ((0x0056E428,0),(0x0056E464,0),(0x0056E488,1)):
  message=pe.raw_at(im,base,sec,address,128).split(b'\0',1)[0]
  assert message.count(b'%')==message.count(b'%s')==conversions
 parent=pe.raw_at(im,base,sec,0x0044A700,1022)
 assert hashlib.sha256(parent).hexdigest()=='b750b3b8810f442dfe717b1c4b49eabad84423ed2771efa794c28c0321273021'
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x0044A700))
 assert calls(pi,0x0044A700)[0x332]==HEAD
 src,rel=cm.object_function(obj,SYM,326)
 ci=list(md.disasm(src,0))
 assert len(src)==326 and len(ci)==82 and sum(i.size for i in ci)==326 and len(rel)==14
 assert sum(x['type']=='REL32' for x in rel)==6
 assert sum(x['type']=='DIR32' for x in rel)==8
 assert all(x['addend']==0 for x in rel)
 resolved=[];replayed=bytearray(src)
 for row in rel:
  target=0x0056E0E4 if row['literal']=='257300' else BINDINGS[row['symbol']]
  offset=row['offset'];resolved.append((offset,row['type'],target))
  value=target-(HEAD+offset+4) if row['type']=='REL32' else target
  struct.pack_into('<I',replayed,offset,value&0xFFFFFFFF)
 expected=[(offset if offset<0x19 else offset-10,'DIR32',target) for offset,target in HL.items()]
 expected += [(offset+1-10,'REL32',target) for offset,target in E8.items()]
 assert sorted(resolved)==sorted(expected)
 assert slot_accesses(ci,-0x10C,0)==[
  (0xC6,'lea','eax, [ebp - 0x10c]',4),
  (0x113,'mov','ecx, dword ptr [ebp - 0x10c]',4)]
 assert not slot_accesses(ci,-0x120,0)
 # This instruction-aligned diagnostic accounts for the unmatched native
 # store explicitly. It does not shorten the native extent or grant exactness.
 projected=[ins for ins in ni if ins.address!=HEAD+0x19]
 current=list(md.disasm(bytes(replayed),HEAD))
 native_heads={ins.address:index for index,ins in enumerate(projected)}
 current_heads={ins.address:index for index,ins in enumerate(current)}
 assert len(current)==len(projected)==82
 for index,(original,candidate) in enumerate(zip(projected,current)):
  assert original.mnemonic==candidate.mnemonic
  if index==2:
   assert original.op_str=='esp, 0x120' and candidate.op_str=='esp, 0x11c'
  elif original.group(CS_GRP_JUMP):
   assert native_heads[original.operands[0].imm]==current_heads[candidate.operands[0].imm]
  else:
   assert original.op_str==candidate.op_str,(hex(original.address-HEAD),original.op_str,candidate.op_str)
 print('PASS immutable original complete 336B/83-i386 Renderer ANM group parser, 6 native E8 and 8 PE HIGHLOW')
 print('PASS real header signature8, zero flag+0x20, embedded path+0x10, CP932 errors, actual resource read+file extent and 24B texture-record metadata writes')
 print('PASS original zero slot [EBP-0x120] is separate from resource-size output [EBP-0x10C], which has no caller initialization')
 print('PASS complete 326B/82-instruction candidate, all 14 independently bound relocations and unchanged remaining instruction/branch protocol')
 print('NONEXACT: full native extent remains 336B/83; its unmatched 10B zero store and extra four-byte frame allocation remain unresolved')
 print('Affected exact replay scope zero: only this nonexact source changed; no shared header changed')
if __name__=='__main__':
 parser=argparse.ArgumentParser(description=__doc__)
 parser.add_argument('--candidate-object',type=Path,default=DEFAULT_OBJECT)
 verify(parser.parse_args().candidate_object)
