#!/usr/bin/env python3
"""Original-only complete 1486B/372-x86 rotated-corner Boss and source COFF audit.

Rejects in-memory padded alternatives: checks real compiled code bytes and
relocation fields against locked original PE through canonical original oracle.
"""
from pathlib import Path
import importlib.util
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sp=importlib.util.spec_from_file_location('prior',ROOT/'scripts/verify-animation-corner-axis96-rotated1486-native.py')
prior=importlib.util.module_from_spec(sp);sp.loader.exec_module(prior)
sp=importlib.util.spec_from_file_location('cf',ROOT/'scripts/compare-coff-function.py')
cf=importlib.util.module_from_spec(sp);sp.loader.exec_module(cf)
SYMBOL='?project_rotated_corners_43ef20@NativeAnimationCornerProjector@th20@@QAEXPAVAnimation@2@PAUVector3@2@111@Z'

def verify():
    # This calls the original-only PE native proof and 96B original data audit;
    # do not use the prior in-memory NOP insertion diagnostic.
    prior.verify()
    object_path=ROOT/'build/core945-canonical/AnimationCornerRotated1486.obj'
    assert object_path.is_file(),f'Build the changed source first: {object_path}'
    code,rel=cf.object_function(object_path,SYMBOL,1486)
    instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,prior.HEAD))
    assert len(instructions)==372
    assert (instructions[-1].address+instructions[-1].size)==prior.HEAD+1486
    assert code[0x41]==0x90,code[0x39:0x46].hex()
    assert len(rel)==22
    native_fields=set(prior.HIGHLOW)|{site+1 for site in prior.CALLS}
    assert {r['offset'] for r in rel}==native_fields
    original=cf.compare(object_path,SYMBOL,prior.HEAD,1486)
    assert original['result']=='structural-exact',original
    assert original['matched_comparable_bytes']==1398==original['comparable_bytes']
    print('PASS actual unmodified COFF 1486B/372 i386, natural +0x41 NOP and all 22 true relocation sites')
    print('PASS 1398/1398 non-relocated original code bytes, no virtual byte insertion')
    print('NOTE canonical source-scoped replay separately certifies all real target addresses')

if __name__=='__main__':verify()
