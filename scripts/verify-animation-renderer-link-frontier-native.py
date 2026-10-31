#!/usr/bin/env python3
"""Renderer update's real 40/42B list helpers versus compiled 31/42B probe.

Prove the 63/61B child templates are already matched elsewhere; these are
not new game-authored contributions. No ignored or fake machine instructions.
"""
import argparse
import hashlib
import importlib.util
import struct
import sys
from pathlib import Path

from capstone import Cs, CS_ARCH_X86, CS_MODE_32

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / 'scripts'))
ps = importlib.util.spec_from_file_location('renderer_frontier_pe', ROOT / 'scripts/verify-animation-draw-boss-native.py')
pe = importlib.util.module_from_spec(ps)
ps.loader.exec_module(pe)
cs = importlib.util.spec_from_file_location('renderer_frontier_coff', ROOT / 'scripts/compare-coff-function.py')
coff = importlib.util.module_from_spec(cs)
cs.loader.exec_module(coff)

SPECS = (
 # Key, address, length, original SHA-256, C++20 Animation template symbol.
 ('link_ctor', 0x00418A10, 63,
  '27c57c87da6dfeefa66873ffcc00657563332c95b0005a59a2480f6e526c94bd',
  '??0?$IntrusiveLink@VAnimation@th20@@@th20@@QAE@XZ'),
 ('link_initialize', 0x0044A670, 61,
  '9eb41128746354b9f5236dedc33bb847d4f905f5893fd63798ab5e040c717062',
  '?initialize@?$IntrusiveLink@VAnimation@th20@@@th20@@QAEXPAVAnimation@2@@Z'),
 ('list_ctor', 0x00418A50, 40,
  '2ff50d0ce1b86ffa1cf0150cfe4b8edbc22c858913354421c9ac2442c048f830',
  '??0?$IntrusiveList@VAnimation@th20@@@th20@@QAE@XZ'),
 ('list_reset', 0x0044A640, 42,
  'e170d8384142cf82e1f48671d10eeb30bf5f44155cb7649ffda5aaa0b4602f00',
  '?reset@?$IntrusiveList@VAnimation@th20@@@th20@@QAEXPAVAnimation@2@@Z'),
)

def verify(candidate):
    image,_ = pe.verified_target()
    base,sections=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,sections)
    for name,addr,length,sha,symbol in SPECS:
        body=pe.raw_at(image,base,sections,addr,length)
        assert hashlib.sha256(body).hexdigest()==sha,(name,'target SHA')
        instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,addr))
        assert instructions[-1].address+instructions[-1].size==addr+length
        assert instructions[-1].mnemonic=='ret'
        assert not any(addr<=p<addr+length for p in highlow)
        calls={i.address-addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
               for i in instructions if i.size==5 and i.bytes[0]==0xe8}
        expected={'link_ctor':{},'link_initialize':{},'list_ctor':{0x0A:0x00418A10},
                  'list_reset':{0x16:0x0044A670}}[name]
        assert calls==expected,(name,calls,expected)
        print(f'PASS original {name}: {length}B/{len(instructions)} x86, real call sites and SHA')
        if not candidate:continue
        if name=='list_ctor':
            code,_=coff.object_function(candidate,symbol,31)
            assert len(code)==31
            print('FRONTIER list ctor: 31B compiled vs 40B native; second tail publication is absent')
        else:
            result=coff.compare(candidate,symbol,addr,length)
            if name=='list_reset':
                assert result['result']=='mismatch'
                assert (result['matched_comparable_bytes'],result['comparable_bytes'])==(37,38)
                assert result['first_differences']==[{'offset':'0x22','object':0x42,'target':0x50}]
                assert result['relocations'][0]['solved_destination']=='0x0044A670'
                print('FRONTIER list reset: 37/38 nonrelocated bytes, register-direction byte at +0x22')
            else:
                assert result['result']=='structural-exact' and result['comparable_bytes']==length
                assert not result['relocations']
                print(f'PASS {name}: complete {length}/{length} native bytes; ALREADY covered by EXACT-051')
    print('No new strict head/bytes credited: 63B and 61B leaves already exist in canonical exact units.')

if __name__=='__main__':
    parser=argparse.ArgumentParser()
    parser.add_argument('--candidate-object',type=Path)
    args=parser.parse_args()
    verify(args.candidate_object)
