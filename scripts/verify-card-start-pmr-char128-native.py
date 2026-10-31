#!/usr/bin/env python3
"""Immutable original 128B PMR string(char*) constructor and Card caller."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pe128',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('cmp128',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x0046A830;SIZE=128
ORIGINAL_SHA='415b1e69052289e12f81ff767adfe7714aa896eac6c56df04471d47189c165cb'
E8={0x36:0x00446C10,0x46:0x00411180,0x4F:0x0040B280,0x5F:0x00468030}
DATA={0x06:0x00568D2D,0x15:0x005B25C0}
def verify():
    image,_=pe.verified_target();base,sec=pe.parse_sections(image)
    body=pe.raw_at(image,base,sec,HEAD,SIZE)
    assert hashlib.sha256(body).hexdigest()==ORIGINAL_SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
    assert len(ins)==41 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
    calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xe8}
    assert calls==E8
    native_high={x-HEAD:struct.unpack('<I',pe.raw_at(image,base,sec,x,4))[0]
                 for x in pe.physical_highlow(image,base,sec) if HEAD<=x<HEAD+SIZE}
    assert native_high==DATA
    parent=pe.raw_at(image,base,sec,0x00487C30,1896)
    assert hashlib.sha256(parent).hexdigest()=='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
    native_parent=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x00487C30))
    callers=[i.address-0x00487C30 for i in native_parent if i.size==5 and i.bytes[0]==0xe8
             and i.address+5+struct.unpack_from('<i',i.bytes,1)[0]==HEAD]
    assert callers==[0x2D3],callers
    unit=coff.compare_unit('card_start_pmr_string_char_ctor_128')
    assert unit['result']=='exact' and unit['size']==SIZE and unit['matched_bytes']==SIZE
    assert len(unit['relocations'])==6
    print('PASS native 128B/41-i386 PMR string(char*) constructor, 4 E8/2 PE HIGHLOW original roles')
    print('PASS original 1,896B Card start E8 +0x2D3 to genuine 128B PMR initializer')
    print('PASS canonical 128/128 source-generated whole PMR string code, original library origin uncredited')
if __name__=='__main__':verify()
