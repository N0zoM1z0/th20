#!/usr/bin/env python3
"""Attest the native strided constructor and renderer cache-reset helpers."""
from __future__ import annotations
import hashlib
import importlib.util
from pathlib import Path
import sys
from capstone import Cs, CS_ARCH_X86, CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
spec=importlib.util.spec_from_file_location('pe_screen_support',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(spec);spec.loader.exec_module(pe)
TARGETS={
 0x0040BC20:(56,'fba949981ac5a4e1adf3d78d9e9b235ae0e940616cbef6c7fb6916cd6d53f79d'),
 0x00424080:(24,'e5e3832548bac6f385db0d91b8547eb61a1655c1a903aeffc49331d2bc531f2e'),
 0x004240A0:(21,'512c0a963bc3c0914a39b1c26bcae54c3d0817c42fb04cda79509c2361966fa4'),
}
def verify():
 image,_=pe.verified_target();base,sections=pe.parse_sections(image)
 all_highlow=pe.physical_highlow(image,base,sections)
 for address,(size,expected_hash) in TARGETS.items():
  body=pe.raw_at(image,base,sections,address,size)
  digest=hashlib.sha256(body).hexdigest()
  assert digest==expected_hash,(hex(address),digest,expected_hash)
  instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,address))
  assert not any(i.size==5 and i.bytes[0]==0xE8 for i in instructions),hex(address)
  assert not any(address<=site<address+size for site in all_highlow),hex(address)
  print(f'PASS {address:#010x}: {size}B immutable body, no direct E8/PE HIGHLOW fields, sha256={digest}')
if __name__=='__main__':verify()
