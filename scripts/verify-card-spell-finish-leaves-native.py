#!/usr/bin/env python3
"""Original PE/whole-COFF proof for four typed Card spell-finish helpers."""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('card_finish_native',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('card_finish_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
PARENT=0x004878B0
PARENT_SIZE=602
PARENT_SHA='17601f659a19106028345e6ea7349827979a354946d8f728d56cd3a12b08003f'
SPECS={
 'mark':(0x004883A0,32,12,'dafa99db8283cd0c63d14482fb9d624ecf7ee9d71ae357049da9bbf81175a571','?mark_finished_4883a0@NativeCardUiDirtyView@th20@@QAEXXZ',[0x01F]),
 'counter':(0x00488510,61,18,'4197627a972edfd6745332fb291a33fb4e9870518e16deb36538eb684e4cc7fa','?increment_capture_488510@NativeSpellRecordView@th20@@QAEXH@Z',[0x142,0x179]),
 'archive':(0x00488700,19,9,'77e8c2448ccf9c304a4f32a3b39953b7ba68f80de7493b14655588ac9155833f','?secondary_488700@NativeCardRecordArchive@th20@@QAEPAEXZ',[0x14D,0x1A3,0x1D4]),
 'record':(0x00486E10,23,9,'e27301c600902e72075a2e6690e16bdc2a12a0a8199b6c0b3904950b1761f3e0','?record_486e10@NativeSpellRecordArrayView@th20@@QAEPAUNativeSpellRecordView@2@H@Z',[0x133,0x16A,0x1B7,0x1E8]),
}
def native_calls(instructions,start):
    return {i.address-start:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in instructions if i.size==5 and i.bytes[0]==0xe8}
def verify(candidate):
    image,_=pe.verified_target();base,secs=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,secs)
    parent=pe.raw_at(image,base,secs,PARENT,PARENT_SIZE)
    assert hashlib.sha256(parent).hexdigest()==PARENT_SHA
    parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,PARENT))
    assert len(parent_ins)==172 and parent_ins[-1].address+parent_ins[-1].size==PARENT+PARENT_SIZE
    calls=native_calls(parent_ins,PARENT)
    assert len(calls)==26
    for name,(addr,size,count,sha,symbol,parent_fields) in SPECS.items():
        body=pe.raw_at(image,base,secs,addr,size)
        assert hashlib.sha256(body).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,addr))
        assert len(ins)==count and ins[-1].address+ins[-1].size==addr+size
        assert ins[-1].mnemonic=='ret'
        assert not native_calls(ins,addr)
        assert not any(addr<=h<addr+size for h in highlow)
        assert [p for p,target in calls.items() if target==addr]==parent_fields
        print(f'PASS native {name}: whole {size}B/{count} i386, zero in-body relocations, Card 602B caller E8 {len(parent_fields)}')
        if candidate is None: continue
        proof=coff.compare(candidate,symbol,addr,size)
        assert proof['result']=='structural-exact' and proof['matched_comparable_bytes']==size
        assert proof['relocations']==[]
        print(f'PASS compiler {name}: all {size}/{size} original bytes, no solved relocation fields')
    print('Original 602B parent remains independently NONEXACT; neither its complete-source nor runtime acceptance follows from four leaves.')
if __name__=='__main__':
 p=argparse.ArgumentParser();p.add_argument('--candidate-object',type=Path)
 a=p.parse_args();verify(a.candidate_object)
