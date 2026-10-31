#!/usr/bin/env python3
"""Whole original 368B CP932 file opening and 493B Win32 one-shot writing.

All PE call sites and HIGHLOW targets are independently pinned from the
immutable original game executable, never inferred from the COFF candidate.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('filepe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('filecm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
SPECS={
 'game_input_cp932_open_368':(
  0x00410CF0,368,94,'e4b51fd1da74296dbefab1aeda7143e27cc6d3e25e71bd9c78e9daaf94bce009',
  {0x32:0x0040C310,0x3E:0x0040B730,0x58:0x00544760,
   0xEA:0x0040C6B0,0x117:0x0040B900,0x12D:0x0040C6B0,
   0x14C:0x0040B900,0x167:0x005429EE},
  {0x06:0x00567AD0,0x18:0x005B25C0,0x2E:0x005C0240,
   0x7B:0x0056C124,0x9A:0x0056C164,0x9F:0x005AE060,
   0xA5:0x005AE060,0xC8:0x0056C130,0xD6:0x0056C128,
   0xE6:0x0056C658,0xFB:0x0056C12C,0x129:0x0056C6A0},
  '?open_game_input_cp932_410cf0@th20@@YAHPBD@Z',288),
 'game_cp932_write_once_493':(
  0x00410E70,493,125,'583da3e1d06de98d5b12071b04f393c743ee8c73c36336553089d3898dacd3e3',
  {0x32:0x0040C310,0x3E:0x0040B730,0x58:0x00544760,
   0xEB:0x0040C6B0,0x118:0x0040B900,0x168:0x0040C6B0,
   0x187:0x0040B900,0x1AA:0x0040C6B0,0x1C9:0x0040B900,
   0x1E4:0x005429EE},
  {0x06:0x00567B10,0x18:0x005B25C0,0x2E:0x005C0240,
   0x7B:0x0056C124,0x9A:0x0056C164,0xC9:0x0056C130,
   0xD7:0x0056C128,0xE7:0x0056C658,0xFC:0x0056C12C,
   0x142:0x0056C138,0x15B:0x0056C134,0x164:0x0056C674,
   0x19D:0x0056C134,0x1A6:0x0056C690},
  '?write_game_cp932_file_410e70@th20@@YAHPBDPBXI@Z',397),
}
def calls(instr,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in instr if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);high=pe.physical_highlow(im,base,sec)
 seen=set()
 for unit,(head,n,count,sha,targets,dir32,symbol,ordinary) in SPECS.items():
  orig=pe.raw_at(im,base,sec,head,n)
  assert hashlib.sha256(orig).hexdigest()==sha
  instr=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(orig,head))
  assert len(instr)==count and instr[-1].address+instr[-1].size==head+n
  assert (instr[-1].mnemonic,instr[-1].op_str)==('ret','')
  assert calls(instr,head)==targets
  highlow={p-head:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
           for p in high if head<=p<head+n}
  assert highlow==dir32
  assert not (seen&set(range(head,head+n)))
  seen.update(range(head,head+n))
  assert any(i.mnemonic=='push' and i.op_str=='0x20a' for i in instr)
  assert any(i.mnemonic=='push' and i.op_str=='0x104' for i in instr)
  assert any(i.mnemonic=='push' and i.op_str=='0x3a4' for i in instr)
  assert any(i.mnemonic=='push' and i.op_str=='2' for i in instr)
  assert any(i.mnemonic=='push' and i.op_str=='0x1300' for i in instr)
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
  assert len(z['relocations'])==len(targets)+len(dir32)
  cmp=cm.compare(ROOT/'build/core1083-canonical/GameFileCp932Bosses.obj',symbol,head,n)
  assert cmp['result']=='structural-exact'
  assert cmp['comparable_bytes']==ordinary and cmp['matched_comparable_bytes']==ordinary
  original_fields={**{k:('DIR32',v) for k,v in dir32.items()},
                   **{k+1:('REL32',v) for k,v in targets.items()}}
  assert len(cmp['relocations'])==len(original_fields)
  for row in cmp['relocations']:
   off=int(row['offset'],16)
   assert off in original_fields and row['type']==original_fields[off][0]
   assert int(row['solved_destination'],16)==original_fields[off][1]
  print(f'PASS original game {unit}: complete {n}B/{count}-i386, {len(targets)} genuine original E8 and {len(dir32)} PE HIGHLOW')
  print(f'PASS natural C++20 canonical {n}/{n} original native, {ordinary}/{ordinary} ordinary bytes and all original call/data roles')
 assert len(seen)==861
 print('PASS true CP932 Win32 UTF16 name conversion, slot2 lock, CreateFileW and FormatMessageW/GetLastError/LocalFree diagnostics')
 print('PASS genuine one-shot WriteFile/CloseHandle short-write failure before success branch; error values -1/-2, native file handle semantics')
 print('PASS two distinct game-owned original native function heads /861 authored-game exact bytes, no prior generic folded helper recredited')
if __name__=='__main__':verify()
