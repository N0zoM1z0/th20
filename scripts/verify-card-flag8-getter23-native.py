#!/usr/bin/env python3
"""Independent original complete Card flag8 leaf and six physical callers."""
from pathlib import Path
import hashlib, importlib.util, struct, sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name,path):
    spec=importlib.util.spec_from_file_location(name,R/path)
    m=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(m)
    return m
cf=load('cardflag_cf','scripts/compare-coff-function.py')
pe=load('cardflag_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004888A0
SIZE=23
SHA='6d3efa8c9ea19f397f043aaab853c9e94fb88993764800ad7205dbf2ae30ea8f'
SYMBOL='?flag8_value_4888a0@NativeCardBit8GetterView@th20@@QBEIXZ'
OBJ=R/'build/core1117-canonical/CardFlag8Getter23.obj'
CALLS=(0x0048708E,0x004870BD,0x004B2F82,0x004B2FB6,0x004B3075,0x004B30A9)
def main():
    image=cf.verified_target()
    base,sections=pe.parse_sections(image)
    original=pe.raw_at(image,base,sections,HEAD,SIZE)
    assert len(original)==SIZE and hashlib.sha256(original).hexdigest()==SHA
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    ins=list(cs.disasm(original,HEAD))
    assert len(ins)==11 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
    assert any((i.mnemonic,i.op_str)==('mov','eax, dword ptr [eax + 0x78]') for i in ins)
    assert any((i.mnemonic,i.op_str)==('shr','eax, 8') for i in ins)
    assert any((i.mnemonic,i.op_str)==('and','eax, 1') for i in ins)
    assert not any(i.size==5 and i.bytes[0]==0xE8 for i in ins)
    assert not any(HEAD<=a<HEAD+SIZE for a in pe.physical_highlow(image,base,sections))
    for site in CALLS:
        call=pe.raw_at(image,base,sections,site,5)
        assert call[0]==0xE8
        assert site+5+struct.unpack('<i',call[1:])[0]==HEAD,hex(site)
    body,reloc=cf.object_function(OBJ,SYMBOL,SIZE)
    assert len(body)==SIZE and not reloc and bytes(body)==original
    check=cf.compare_unit('card_flag8_getter_23')
    assert check['result']=='exact' and check['matched_bytes']==SIZE
    print('PASS original 23B/11-i386 Card+0x78 bit8 getter 0x004888A0 whole strict exact')
    print('PASS two Card update and four battle-controller original E8 callsites; no native relocations or duplicated physical head')
if __name__=='__main__':main()
