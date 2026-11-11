#!/usr/bin/env python3
"""Whole original 157B narrow-path game-exists caller and complete COFF roles.

The original caller takes char const* by value. The physical `lea [ebp+8]`
passes the address of that pointer to the independently matched 44B
`std::filesystem::path<char const*>` constructor with auto_format=0.
The only authoritative exact admission is the game's unit replay.
"""
from argparse import ArgumentParser
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
HEAD=0x004107A0
SIZE=157
SYM='?game_file_exists_4107a0@th20@@YA_NPBD@Z'
SHA='59d4263ec85f2e658ccf89ab882725dbd54578bc167d5affea7a61f43ba2830b'
E8={0x2F:0x0040C310,0x38:0x0040B730,0x4D:0x0040C720,
    0x5A:0x00410610,0x6C:0x0040E6C0,0x7B:0x0040B900,0x94:0x005429EE}
HIGHLOW={0x06:0x00567A15,0x15:0x005B25C0,0x2B:0x005C0240}
SYMBOL_ROLES={
'?slot@LockRegistry@th20@@QAEAAVrecursive_mutex@std@@I@Z':0x0040C310,
'??0?$lock_guard@Vrecursive_mutex@std@@@std@@QAE@AAVrecursive_mutex@1@@Z':0x0040B730,
'??$?0PBD$0A@@path@filesystem@std@@QAE@ABQBDW4format@012@@Z':0x0040C720,
'?exists@filesystem@std@@YA_NABVpath@12@@Z':0x00410610,
'??1path@filesystem@std@@QAE@XZ':0x0040E6C0,
'??1?$lock_guard@Vrecursive_mutex@std@@@std@@QAE@XZ':0x0040B900,
'@__security_check_cookie@4':0x005429EE,
'__ehhandler$?game_file_exists_4107a0@th20@@YA_NPBD@Z':0x00567A15,
'___security_cookie':0x005B25C0,
'?process_locks@th20@@3VLockRegistry@1@A':0x005C0240,
}

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    assert spec.loader
    spec.loader.exec_module(module)
    return module

pe=load('game_exists_original_pe','scripts/verify-animation-draw-boss-native.py')
coff=load('game_exists_candidate_coff','scripts/compare-coff-function.py')

def main():
    parser=ArgumentParser(description=__doc__)
    parser.add_argument('--candidate-object',default='build/core1114-canonical/GameFileExists157.obj',type=Path)
    args=parser.parse_args()
    image,_=pe.verified_target()
    base,sections=pe.parse_sections(image)
    original=pe.raw_at(image,base,sections,HEAD,SIZE)
    assert hashlib.sha256(original).hexdigest()==SHA
    ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
    assert len(ins)==47 and ins[-1].address+ins[-1].size==HEAD+SIZE
    assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
    calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
           for i in ins if i.size==5 and i.bytes[0]==0xe8}
    assert calls==E8
    data={site-HEAD:struct.unpack('<I',pe.raw_at(image,base,sections,site,4))[0]
          for site in pe.physical_highlow(image,base,sections) if HEAD<=site<HEAD+SIZE}
    assert data==HIGHLOW
    assert [(i.address-HEAD,i.mnemonic,i.op_str) for i in ins if 0x44<=i.address-HEAD<0x4D]==[
        (0x44,'push','0'),(0x46,'lea','eax, [ebp + 8]'),
        (0x49,'push','eax'),(0x4A,'lea','ecx, [ebp - 0x2c]')]
    for address,size,sha in [
        (0x0040C720,44,'3d89ba11c5975e31b96f125766a18a270f2cc25c78e92f381c47bc40b3342a7c'),
        (0x00410610,104,'841e6c77dcaccfa8cb38ab8a3fec14aac8fadce63f22da94d930ec353e23ed60')]:
        assert hashlib.sha256(pe.raw_at(image,base,sections,address,size)).hexdigest()==sha
    obj=(ROOT/args.candidate_object).resolve()
    candidate,relocs=coff.object_function(obj,SYM,SIZE)
    expected={(offset+1,'REL32'):dest for offset,dest in E8.items()}
    expected.update({(offset,'DIR32'):dest for offset,dest in HIGHLOW.items()})
    assert len(relocs)==len(expected)==10
    observed={}
    for row in relocs:
        assert row['addend']==0
        pos=(row['offset'],row['type'])
        assert pos in expected,(row['symbol'],pos)
        assert row['symbol'] in SYMBOL_ROLES
        target=SYMBOL_ROLES[row['symbol']]
        assert target==expected[pos],(pos,hex(target),hex(expected[pos]))
        observed[pos]=target
    assert observed==expected
    result=coff.compare(obj,SYM,HEAD,SIZE)
    assert result['result']=='structural-exact' and result['matched_comparable_bytes']==117
    assert result['comparable_bytes']==117 and not result['first_differences']
    assert len(candidate)==157
    print('PASS entire original 157B/47 i386 file-exists game head and original narrow const char* parameter slot ABI')
    print('PASS real original 44B std::filesystem::path<const char*> ctor with auto_format=0; 104B exists backend')
    print('PASS 7 independent E8 and 3 HIGHLOW physical field/destination roles; 117/117 ordinary native bytes')
    print('Strict relocated acceptance: scripts/repo-python scripts/compare-coff-function.py --unit game_file_exists_157')

if __name__=='__main__':main()
