#!/usr/bin/env python3
"""Whole original 266B game persistent CP932 file reader, native exact.

Independently SHA-pin the real Win32 read and DiagnosticAllocator call
sequence and all E8/HIGHLOW fields from immutable Japanese TH20 original.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('readerpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('readercm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00410990
SHA='4c72d68bc74555900a166b2880a2de67ce56964aec974813fd98942dcd6fca4a'
CALLS={0x2F:0x0040C310,0x38:0x0040B730,0x5E:0x0040B900,
 0x7A:0x0041F610,0xA7:0x0040B900,0xD1:0x0040C6B0,
 0xE9:0x0040B900,0x101:0x005429EE}
DATA={0x06:0x0056755D,0x15:0x005B25C0,0x2B:0x005C0240,
 0x46:0x005AE060,0x6C:0x0056C6D4,0x76:0x005B8894,
 0x8A:0x005AE060,0x91:0x0056C134,0xC1:0x005AE060,
 0xC8:0x0056C0B0,0xCD:0x0056C710}
SYM='?read_game_input_bytes_410990@th20@@YAPAXI@Z'
def calls(instr,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in instr if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 raw=pe.raw_at(image,base,sec,HEAD,266)
 assert hashlib.sha256(raw).hexdigest()==SHA
 instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(instr)==74 and instr[-1].address+instr[-1].size==HEAD+266
 assert (instr[-1].mnemonic,instr[-1].op_str)==('ret','')
 assert calls(instr,HEAD)==CALLS
 hl={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
     for p in pe.physical_highlow(image,base,sec) if HEAD<=p<HEAD+266}
 assert hl==DATA
 assert [hl[x] for x in (0x46,0x8A,0xC1)]==[0x005AE060]*3
 assert any(x.mnemonic=='push' and x.op_str=='2' for x in instr)
 assert any(x.mnemonic=='cmp' and '0x5ae060' in x.op_str for x in instr)
 orig_open=pe.raw_at(image,base,sec,0x00410CF0,368)
 assert hashlib.sha256(orig_open).hexdigest()=='e4b51fd1da74296dbefab1aeda7143e27cc6d3e25e71bd9c78e9daaf94bce009'
 assert cm.compare_unit('game_input_cp932_open_368')['result']=='exact'
 alloc=pe.raw_at(image,base,sec,0x0041F610,88)
 assert hashlib.sha256(alloc).hexdigest()=='227cb206a9333c3a02fa426a1f62fc207863fdeedda1ace1031fa06f5c8b3af0'
 z=cm.compare_unit('game_input_bytes_read_266')
 assert z['result']=='exact' and z['size']==266 and z['matched_bytes']==266
 assert len(z['relocations'])==len(CALLS)+len(DATA)==19
 comp=cm.compare(ROOT/'build/core1084-canonical/GameFileInputRead266.obj',SYM,HEAD,266)
 assert comp['result']=='structural-exact'
 assert comp['matched_comparable_bytes']==comp['comparable_bytes']==190
 for rel in comp['relocations']:
  off=int(rel['offset'],16)
  role={**{k:('DIR32',v) for k,v in DATA.items()},**{k+1:('REL32',v) for k,v in CALLS.items()}}[off]
  assert rel['type']==role[0] and int(rel['solved_destination'],16)==role[1]
 print('PASS original whole game 266B/74-i386 persistent-input reader, 8 real native E8/11 PE HIGHLOW')
 print('PASS true native file input HANDLE at 0x005AE060, three original global references, slot2 recursive lock and real ReadFile')
 print('PASS original 88B allocator and 368B file-input open are distinct previously exact physical heads; error CloseHandle and ReadFile callback correct')
 print('PASS complete canonical 266/266 original with 190/190 nonrelocated bytes and 19 original PE independently proven roles')
if __name__=='__main__':verify()
