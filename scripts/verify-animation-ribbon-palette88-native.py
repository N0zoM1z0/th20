#!/usr/bin/env python3
"""Independent locked-original 88B ribbon palette and two 31B tag wrappers."""
from pathlib import Path
import importlib.util
import struct
from capstone import CS_ARCH_X86, CS_MODE_32, Cs
ROOT=Path(__file__).resolve().parents[1]
spec=importlib.util.spec_from_file_location('pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
BODIES={
 0x0045EC10:(88,29,{0x1B:0x004142A0,0x27:0x0045DD20,0x4C:0x0045DD00},{0x3C:0x0056CD94}),
 0x0045DD20:(31,14,{0x11:0x0045D430},{}),
 0x0045DD00:(31,14,{0x11:0x0045D360},{}),
}
PARENT=0x0045EB10
PARENT_CALLS=(0x52,0x75,0x98)

def verify():
    im,_=pe.verified_target();base,secs=pe.parse_sections(im);hi=pe.physical_highlow(im,base,secs);cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for head,(size,nins,want_calls,want_data) in BODIES.items():
        raw=pe.raw_at(im,base,secs,head,size);ins=list(cs.disasm(raw,head))
        assert len(ins)==nins,(hex(head),len(ins))
        assert ins[-1].address+ins[-1].size==head+size
        assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
        calls={i.address-head:(i.address+i.size+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
        fields={p-head:struct.unpack('<I',pe.raw_at(im,base,secs,p,4))[0] for p in hi if head<=p<head+size}
        assert calls==want_calls,(hex(head),calls,want_calls)
        assert fields==want_data,(hex(head),fields,want_data)
        if head==0x0045EC10:
            by={i.address-head:(i.mnemonic,i.op_str) for i in ins}
            assert by[0x2C]==('nop','') and by[0x51]==('nop','')
            assert struct.unpack('<f',pe.raw_at(im,base,secs,0x0056CD94,4))[0]==32.0
        else:assert ('push','0x3c') in [(i.mnemonic,i.op_str) for i in ins]
        print(f'PASS original {head:#010x}: {size}B/{nins} i386, {len(calls)} E8, {len(fields)} HIGHLOW')
    for off in PARENT_CALLS:
        addr=PARENT+off;raw=pe.raw_at(im,base,secs,addr,5)
        assert raw[0]==0xe8
        dest=(addr+5+struct.unpack_from('<i',raw,1)[0])&0xffffffff
        assert dest==0x0045EC10,(hex(addr),hex(dest))
        print(f'PASS original 252B config parent E8 {addr:#010x} -> 0x0045ec10')
    print('PASS original source scopes, two real NOPs and 32.0f physical constant')

if __name__=='__main__':verify()
