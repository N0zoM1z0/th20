#!/usr/bin/env python3
"""Immutable original 182B GDI/DC cleanup: three real GDI imports and 681B caller.

The original returns a boolean despite earlier speculative void declaration.
Physical PE relocations are established independently of compiled COFF.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('glyph182pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('glyph182cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00416360
SHA='632c4839135f7908fc5bda7f2a749944332b8ff3bb76de8484e428a03ce1258e'
HIGHLOW={0x2D:0x0056C02C,0x3D:0x0056C03C,0x4D:0x0056C038}
PARENT=0x00415120
PARENT_SHA='62554c335c22f75345ca164715188e77712c1e8348c199e3757843b193aa33d3'
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 b=pe.raw_at(img,base,secs,HEAD,182)
 assert hashlib.sha256(b).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(ins)==42 and ins[-1].address+ins[-1].size==HEAD+182
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert not calls(ins,HEAD)
 data={pos-HEAD:struct.unpack('<I',pe.raw_at(img,base,secs,pos,4))[0]
       for pos in pe.physical_highlow(img,base,secs) if HEAD<=pos<HEAD+182}
 assert data==HIGHLOW
 assert any(i.mnemonic=='cmp' and i.op_str=='dword ptr [eax + 0x114], 0' for i in ins)
 assert any(i.mnemonic=='mov' and i.op_str=='al, 1' for i in ins)
 assert any(i.mnemonic=='xor' and i.op_str=='al, al' for i in ins)
 parent=pe.raw_at(img,base,secs,PARENT,681)
 assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
 pins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
 assert len(pins)==176 and calls(pins,PARENT)[0x19]==HEAD
 report=cm.compare_unit('glyph_canvas_release_182')
 assert report['result']=='exact' and report['size']==182 and report['matched_bytes']==182
 assert len(report['relocations'])==3
 print('PASS original whole 182B/42-i386 GDI resource release, true bool return, no native E8')
 print('PASS PE HIGHLOW original IAT SelectObject +0x2D, DeleteDC +0x3D, DeleteObject +0x4D')
 print('PASS native full 681B GDI create Boss E8 +0x19 calls original 182B cleanup')
 print('PASS canonical full 182/182 natural C++20, previous void receiver was incorrect')
 print('The whole 681B parent remains source-present NONEXACT; no transitive parent credit')
if __name__=='__main__':verify()
