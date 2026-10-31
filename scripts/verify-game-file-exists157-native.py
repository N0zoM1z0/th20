#!/usr/bin/env python3
"""Whole immutable original 157B game filesystem-exists wrapper frontier.

The pinned current C++20 candidate is 155B/46 i386, NOT exact. The
original native 157B/47 includes a real legacy filesystem::path copy
ctor format argument (push 0) missing from current standard-library ABI.
"""
import hashlib,importlib.util,struct,sys,subprocess,difflib
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('existpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('existcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004107A0
SHA='59d4263ec85f2e658ccf89ab882725dbd54578bc167d5affea7a61f43ba2830b'
E8={0x2F:0x0040C310,0x38:0x0040B730,0x4D:0x0040C720,
    0x5A:0x00410610,0x6C:0x0040E6C0,0x7B:0x0040B900,0x94:0x005429EE}
HIGHLOW={0x06:0x00567A15,0x15:0x005B25C0,0x2B:0x005C0240}
SYM='?game_file_exists_4107a0@th20@@YA_NABVpath@filesystem@std@@@Z'
def calls(instr,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in instr if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im)
 raw=pe.raw_at(im,base,sec,HEAD,157)
 assert hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==47 and ins[-1].address+ins[-1].size==HEAD+157
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)==E8
 native_hl={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
            for x in pe.physical_highlow(im,base,sec) if HEAD<=x<HEAD+157}
 assert native_hl==HIGHLOW
 assert [(i.address-HEAD,i.mnemonic,i.op_str) for i in ins if 0x44<=i.address-HEAD<0x4D]==[
  (0x44,'push','0'),(0x46,'lea','eax, [ebp + 8]'),(0x49,'push','eax'),(0x4A,'lea','ecx, [ebp - 0x2c]')]
 for h,n,sha in [(0x0040C720,44,'3d89ba11c5975e31b96f125766a18a270f2cc25c78e92f381c47bc40b3342a7c'),
                (0x00410610,104,'841e6c77dcaccfa8cb38ab8a3fec14aac8fadce63f22da94d930ec353e23ed60')]:
  assert hashlib.sha256(pe.raw_at(im,base,sec,h,n)).hexdigest()==sha
 p=ROOT/'build/core1085-probes/GameFileExists157.obj'
 b,r=cm.object_function(p,SYM,155)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b),0))
 assert len(b)==155 and len(ci)==46 and len(r)==10
 assert sum(x['type']=='REL32' for x in r)==7
 assert sum(x['type']=='DIR32' for x in r)==3
 assert all(x['addend']==0 for x in r)
 assert [(i.address,i.mnemonic,i.op_str) for i in ci if 0x44<=i.address<0x4B]==[
  (0x44,'mov','eax, dword ptr [ebp + 8]'),(0x47,'push','eax'),(0x48,'lea','ecx, [ebp - 0x2c]')]
 assert [s[0] for s in difflib.SequenceMatcher(None,[x.mnemonic for x in ci],[x.mnemonic for x in ins],autojunk=False).get_opcodes()].count('replace')==1
 print('PASS original complete TH20 game 157B/47-i386 filesystem exists wrapper, 7 genuine native E8 and 3 PE HIGHLOW')
 print('PASS native slot2 lock, real 24B std::filesystem::path copy, original 44B format-aware path constructor E8+0x4D and 104B exists E8+0x5A')
 print('NONEXACT: actual current C++20 const-path local-copy source 155B/46 i386, seven E8/three DIR32; legacy original pushes extra format=0 before path source pointer (2B/one instruction net gap)')
 print('No original 157B whole-exact unit or newly credited original authored-game bytes; no fake enum argument, asm or no-op compiler pad')
if __name__=='__main__':verify()
