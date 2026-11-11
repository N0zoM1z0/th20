#!/usr/bin/env python3
"""Two whole-native Animation field leaves with original PE caller evidence.

Independent original bytes and physical callers establish roles; only a
fresh, fully compiled COFF/receipt can establish whole strict exactness.
"""
from pathlib import Path
import hashlib
import importlib.util
import struct
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))

def load(name,path):
    spec=importlib.util.spec_from_file_location(name,ROOT/path)
    module=importlib.util.module_from_spec(spec)
    spec.loader.exec_module(module)
    return module

cf=load('field_cf','scripts/compare-coff-function.py')
pe=load('field_pe','scripts/verify-animation-draw-boss-native.py')
OBJ=ROOT/'build/core1116-canonical/AnimationFieldReadLeaves.obj'
SPECS=(
    ('animation_color_alpha_21',0x0044C650,21,9,
     '0db22c6bec703e8f1bba18ced2635741d7bbfa4a3e6b82a80deaa446001f342d',
     '?color_alpha_44c650@NativeAnimationReadView@th20@@QBEEXZ',
     ('movzx','eax, byte ptr [eax + 0x493]'),
     (0x00461F7B,0x00461FB7,0x00462276)),
    ('animation_vector_484_19',0x0044CB00,19,9,
     '47d9a163f8e0cc4ba692c29d17e640400a0e7893ad7b454c95fc4658a48376ef',
     '?vector_484_44cb00@NativeAnimationReadView@th20@@QAEAAUVector3@2@XZ',
     ('add','eax, 0x484'),
     (0x0044CAF1,0x004B18F2,0x004B1936,0x004B197A,0x004B1F26)),
)

def main():
    original=cf.verified_target()
    base,sections=pe.parse_sections(original)
    absolute_fields=pe.physical_highlow(original,base,sections)
    cs=Cs(CS_ARCH_X86,CS_MODE_32)
    for unit,head,length,instruction_count,body_sha,symbol,operation,callers in SPECS:
        native=pe.raw_at(original,base,sections,head,length)
        assert len(native)==length and hashlib.sha256(native).hexdigest()==body_sha
        ni=list(cs.disasm(native,head))
        assert len(ni)==instruction_count
        assert ni[-1].address+ni[-1].size==head+length
        assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','')
        assert [(i.mnemonic,i.op_str) for i in ni if i.address==head+0x0A]==[operation]
        assert not any(i.size==5 and i.bytes[0]==0xE8 for i in ni)
        assert not any(head<=site<head+length for site in absolute_fields)
        for site in callers:
            opcode=cf.pe_bytes_at(original,site,5)
            assert opcode[0]==0xE8
            assert site+5+struct.unpack('<i',opcode[1:])[0]==head,(hex(site),hex(head))
        code,relocations=cf.object_function(OBJ,symbol,length)
        assert len(code)==length and not relocations and bytes(code)==native
        ci=list(cs.disasm(code,0))
        assert len(ci)==len(ni)==instruction_count
        # This checks protected compiler input receipts and all native bytes.
        check=cf.compare_unit(unit)
        assert check['result']=='exact' and check['matched_bytes']==length
        print(f'PASS {unit}: full original {length}/{length}B, {instruction_count} i386, zero E8/HIGHLOW; {len(callers)} pinned physical caller sites')
    # The 9KB original controller mutates the Y component of this true
    # Vector3 via returned EAX; it is not an opaque non-game pointer.
    consumer=cf.pe_bytes_at(original,0x004B18FF,8)
    assert consumer[:4]==bytes.fromhex('f30f1140') and consumer[4]==0x04,consumer.hex()
    print('PASS native 0x004B18FF writes vector+4 through returned EAX, and alpha byte is widened by original 4KB Animation caller')
    print('PASS distinct original 21+19 game-authored code bytes; one new source, two separate canonical exact units, no duplicate code credit')

if __name__=='__main__':
    main()
