#!/usr/bin/env python3
"""Original typed Card text capture, PMR string lifetime and physical E8 graph."""
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('payload_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('payload_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
SPECS={
 'card_text_payload_ctor_56':(0x00486B70,56,21,'4ecc288db00d1eccedbc09835fce9e0484e74c07a1e9cb714673fdef35f29bd6',
    {0x21:0x0046A780},{},[0x30D],'0xc'),
 'card_text_payload_dtor_23':(0x0046ADE0,23,11,'c7611d27a214e9aa1ba4502692df87bad1d227a8ee228b0d1d0021b44bd9d6f2',
    {0x0D:0x00449240},{},[0x33F],''),
 'card_text_payload_pmr_copy_167':(0x0046A780,167,54,'dac331f72705a53ef1c0e4f6b038420924fef85570274e6a330db00aff997294',
    {0x31:0x0040F160,0x3B:0x00470A40,0x58:0x00467FA0,0x73:0x0040F2C0,0x86:0x00468180},
    {0x06:0x00568CFD,0x15:0x005B25C0},[],'4'),
}
def calls(instructions,head):
    return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in instructions if i.size==5 and i.bytes[0]==0xe8}
def verify():
    image,_=pe.verified_target();base,sections=pe.parse_sections(image)
    high=pe.physical_highlow(image,base,sections)
    parent_head=0x00487C30
    parent=pe.raw_at(image,base,sections,parent_head,1896)
    assert hashlib.sha256(parent).hexdigest()=='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
    parent_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,parent_head))
    assert len(parent_ins)==512 and len(calls(parent_ins,parent_head))==62
    parent_calls=calls(parent_ins,parent_head)
    for unit,(addr,length,count,sha,native_calls,native_data,parents,return_size) in SPECS.items():
        native=pe.raw_at(image,base,sections,addr,length)
        assert hashlib.sha256(native).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(native,addr))
        assert len(ins)==count and ins[-1].address+ins[-1].size==addr+length
        assert (ins[-1].mnemonic,ins[-1].op_str)==('ret',return_size)
        assert calls(ins,addr)==native_calls
        fields={site-addr:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
                for site in high if addr<=site<addr+length}
        assert fields==native_data
        assert [offset for offset,dest in parent_calls.items() if dest==addr]==parents
        result=coff.compare_unit(unit)
        assert result['result']=='exact' and result['size']==length and result['matched_bytes']==length
        assert len(result['relocations'])==len(native_calls)+len(native_data)
        print(f'PASS {unit}: original {length}B/{count} instructions, {len(native_calls)} E8/{len(native_data)} PE HIGHLOW, complete canonical exact')
    print('PASS true 1,896B Card start original calls payload +0x30D and destroy +0x33F')
    print('STATUS: 1,896B Card start remains NONEXACT; three helper exact units do not imply exact parent')
if __name__=='__main__':verify()
