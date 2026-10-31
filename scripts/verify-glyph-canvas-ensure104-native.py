#!/usr/bin/env python3
"""Immutable native 104B glyph bitmap format fallback and 2227B boss caller.

The three actual 104B E8s all target the separate 681B surface initializer;
that original large callee is not claimed exact by this accepted leaf.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph104pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph104coff',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004153D0
SHA='20fdd9d772ec1d057d3a77d9795c7c974d44a790a02dff9a3fffdc0fafa78c47'
PARENT=0x00415830
PARENT_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in inst if i.size==5 and i.bytes[0]==0xe8}
def verify():
 img,_=pe.verified_target();base,sec=pe.parse_sections(img);hl=pe.physical_highlow(img,base,sec)
 body=pe.raw_at(img,base,sec,HEAD,104)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==43 and ins[-1].address+ins[-1].size==HEAD+104
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0xc')
 assert calls(ins,HEAD)=={0x16:0x00415120,0x3F:0x00415120,0x59:0x00415120}
 assert not any(HEAD<=a<HEAD+104 for a in hl)
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp + 0x10], 0x19' for i in ins)
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp + 0x10], 0x1a' for i in ins)
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [ebp + 0x10], 0x17' for i in ins)
 p=pe.raw_at(img,base,sec,PARENT,2227)
 assert hashlib.sha256(p).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p,PARENT))
 assert len(pins)==470 and calls(pins,PARENT)[0x362]==HEAD
 report=cm.compare_unit('glyph_canvas_format_fallback_104')
 assert report['result']=='exact' and report['size']==104 and report['matched_bytes']==104
 assert len(report['relocations'])==3
 print('PASS immutable 104B/43 native glyph canvas fallback, true pixel formats 0x19/0x1A -> 0x15, 0x17 -> 0x16')
 print('PASS 3 real E8 to original 681B surface create 0x00415120, no PE HIGHLOW, original ret 0x0C')
 print('PASS real original 2227B/470 glyph text Boss E8 +0x362 -> this native head')
 print('PASS canonical whole 104/104 bytes, one game-specific authored head; 681B create and 2227B parent unaccepted')
if __name__=='__main__':verify()
