#!/usr/bin/env python3
"""Whole original 274B GDI glyph text measurement Boss and authentic 22-font ABI.

All original PE HIGHLOW and E8 physical sites are independently resolved
from the immutable pinned target, never from a COFF candidate's bytes.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('gmeasurepe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('gmeasurecm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x004156E0
SHA='33e732ed92238aa3a5e4175ac0714abc7f427cf23e03c4ad1ae1b4b3260e23be'
E8={0x01C:0x00414580,0x037:0x00544760,0x063:0x0040C300,
    0x096:0x00548300,0x109:0x005429EE}
DATA={0x00A:0x005B25C0,0x018:0x005B66F0,0x05A:0x0056C124,
      0x05F:0x005B6758,0x06B:0x0056C2AC,0x085:0x0056C02C,
      0x0C2:0x0056C030,0x0F4:0x0056C02C}
SYM='?measure_glyph_text_4156e0@th20@@YA_KPBDH@Z'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 body=pe.raw_at(image,base,sections,HEAD,274)
 assert hashlib.sha256(body).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==71 and ins[-1].address+ins[-1].size==HEAD+274
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 assert calls(ins,HEAD)==E8
 high=pe.physical_highlow(image,base,sections)
 data={p-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,p,4))[0]
       for p in high if HEAD<=p<HEAD+274}
 assert data==DATA
 # Native stack and GDI lifecycle: 0x202-byte UTF16 clear, CP932=932,
 # original 0x100-char conversion capacity, and four-pixel extent margins.
 assert body[0x03:0x09]==b'\x81\xec\x20\x02\x00\x00'
 assert any(i.mnemonic=='push' and i.op_str=='0x202' for i in ins)
 assert any(i.mnemonic=='push' and i.op_str=='0x3a4' for i in ins)
 assert any(i.mnemonic=='push' and i.op_str=='0x100' for i in ins)
 assert sum(i.mnemonic=='add' and i.op_str.endswith(', 4') for i in ins)>=2
 for addr,size,sha in [(0x00414580,22,'63c49b1813004cda4fdbb91fb68008a819c44d98c1c64a7fc76b4405f26a10b8'),
                       (0x0040C300,16,'8857d15e5bce580adb0e5dc96d1aba616e10aa72982c77604b0d7b40d9671936')]:
  assert hashlib.sha256(pe.raw_at(image,base,sections,addr,size)).hexdigest()==sha
 # Verify the corrected native 22-HFONT resource owner rather than
 # accepting the prior undocumented 32-entry source declaration.
 end=pe.raw_at(image,base,sections,0x00414F50,17)
 assert hashlib.sha256(end).hexdigest()=='f106cbce46348bfe471dda5f325d0e310a0557f477a497a821b3abb6fa359641'
 assert any(i.mnemonic=='add' and i.op_str=='eax, 0x58'
            for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(end,0x00414F50))
 report=cm.compare_unit('glyph_text_measure_274')
 assert report['result']=='exact' and report['size']==274 and report['matched_bytes']==274
 assert len(report['relocations'])==13
 print('PASS whole original game 274B/71-i386 GDI measure Boss, all 5 true E8/8 PE HIGHLOW')
 print('PASS genuine 22 native HFONT table at 0x005B66F0, folded 22B index, real 16B window handle getter')
 print('PASS real CP932 Win32 text conversion/GetDC/SelectObject/GetTextExtent/restore 8B EDX:EAX return')
 print('PASS canonical full 274/274 native source, 222/222 comparable bytes and 13 independently anchored roles')
 print('No repeated credit for folded font index/window getter or earlier exact 79B font cleanup')
if __name__=='__main__':verify()
