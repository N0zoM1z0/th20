#!/usr/bin/env python3
"""Independent locked original PE proof of game texture lookup and STL at().

Only the 60B native texture lookup is authored game code. The 34B checked
std::array library subscript is canonical-native-exact but not game credit.
"""
import importlib.util
from pathlib import Path
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('original_draw',ROOT/'scripts/verify-animation-draw-boss-native.py')
orig=importlib.util.module_from_spec(spec)
assert spec.loader
spec.loader.exec_module(orig)


def verify():
    pe,_=orig.verified_target()
    base,sections=orig.parse_sections(pe)
    highlow=orig.physical_highlow(pe,base,sections)
    lookup=0x00445A00
    method=orig.decoded(pe,base,sections,lookup,60)
    instructions={i.address:i for i in method}
    assert len(method)==21 and method[-1].address+method[-1].size==lookup+60
    assert method[-1].mnemonic=='ret' and method[-1].op_str=='4'
    assert not [x for x in highlow if lookup<=x<lookup+60]
    assert instructions[0x00445A0C].mnemonic=='add' and instructions[0x00445A0C].op_str=='eax, 0x6000730'
    assert instructions[0x00445A17].mnemonic=='sar' and instructions[0x00445A17].op_str=='ecx, 8'
    assert instructions[0x00445A28].mnemonic=='and' and instructions[0x00445A28].op_str=='eax, 0xff'
    assert instructions[0x00445A2D].mnemonic=='imul' and instructions[0x00445A2D].op_str=='ecx, eax, 0x18'
    assert instructions[0x00445A30].mnemonic=='mov' and instructions[0x00445A30].op_str=='edx, dword ptr [edx + 0x58]'
    assert instructions[0x00445A33].mnemonic=='mov' and instructions[0x00445A33].op_str=='eax, dword ptr [edx + ecx]'
    call=instructions[0x00445A1E]
    assert call.mnemonic=='call' and call.bytes[0]==0xe8
    assert call.address+5+struct.unpack_from('<i',call.bytes,1)[0]==0x0043EB10

    # This physical original std::array<AnimationFile*,42>::at is a library
    # member; original branch rejects index >= 42, and native E8 invokes
    # original 0x00428C80 range-failure implementation before array pointer.
    array_head=0x0043EB10
    at=orig.decoded(pe,base,sections,array_head,34)
    atins={i.address:i for i in at}
    assert len(at)==14 and at[-1].address+at[-1].size==array_head+34
    assert at[-1].mnemonic=='ret' and at[-1].op_str=='4'
    assert not [x for x in highlow if array_head<=x<array_head+34]
    assert atins[0x0043EB17].mnemonic=='cmp' and atins[0x0043EB17].op_str=='dword ptr [ebp + 8], 0x2a'
    assert atins[0x0043EB1B].mnemonic=='jb' and atins[0x0043EB1B].op_str=='0x43eb23'
    error_call=atins[0x0043EB1D]
    assert error_call.mnemonic=='call' and error_call.bytes[0]==0xe8
    assert error_call.address+5+struct.unpack_from('<i',error_call.bytes,1)[0]==0x00428C80
    assert atins[0x0043EB29].mnemonic=='lea' and atins[0x0043EB29].op_str=='eax, [ecx + eax*4]'
    # Ghidra's provisional inventory incorrectly marked the `_Xran` range
    # error as 13B. The immutable original PE has the real return at +0xF:
    # it is a 16B/7-instruction physical compiler library method.
    xran_head=0x00428C80
    xran=orig.decoded(pe,base,sections,xran_head,16)
    xran_map={i.address:i for i in xran}
    assert len(xran)==7 and xran[-1].address==0x00428C8F
    assert xran[-1].mnemonic=='ret' and xran[-1].op_str==''
    assert xran_map[0x00428C83].mnemonic=='push'
    assert xran_map[0x00428C83].op_str=='0x56dc28'
    assert xran_head+4 in highlow
    assert struct.unpack('<I',orig.raw_at(pe,base,sections,xran_head+4,4))[0]==0x0056DC28
    assert orig.raw_at(pe,base,sections,0x0056DC28,30)==b'invalid array<T, N> subscript\0'
    original_throw=xran_map[0x00428C88]
    assert original_throw.mnemonic=='call' and original_throw.bytes[0]==0xe8
    assert original_throw.address+5+struct.unpack_from('<i',original_throw.bytes,1)[0]==0x00540EF5
    assert not [p for p in highlow if xran_head<=p<xran_head+16 and p!=xran_head+4]
    print('PASS original whole 60B/21 x86 game texture lookup: native signed high-word 42-file index, low byte *24, textures+0x58, E8 real 0x0043EB10')
    print('PASS original whole 34B/14 x86 STL std::array<AnimationFile*,42>::at: native cmp index 42, error E8 0x00428C80, no HIGHLOW')
    print('PASS corrected original 16B/7 x86 STL _Xran, authentic 30-byte PE diagnostic string, real HIGHLOW 0x0056DC28 and throw E8 0x00540EF5')
    print('Only the 60B method counts as authored game; 34B at +16B _Xran are STL/library-excluded.')

if __name__=='__main__':verify()
