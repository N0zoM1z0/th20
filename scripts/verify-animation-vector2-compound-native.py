#!/usr/bin/env python3
"""Original PE-only full 72B/77B Vector2 compound-value leaf verification.

The two original methods mutate their ECX receiver, copy the 8-byte
Vector2 to a hidden result pointer at [EBP+8], and use native RET 8.
Check immutable full bodies, instruction heads, real game 1204B caller E8
sites, no true original E8 children or HIGHLOW fields. This verifier does
not depend on source COFF or a speculative decompiler return signature.
"""
from pathlib import Path
import importlib.util,struct
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
CASES={
 'multiply_assign_value_72':(0x00439910,72,24,'mulss',[0x2A9]),
 'add_assign_value_77':(0x00439960,77,26,'addss',[0x120,0x1E0,0x258]),
}
def verify():
 original,_=pe.verified_target();base,sections=pe.parse_sections(original)
 highlow=pe.physical_highlow(original,base,sections)
 parent=0x0043D370
 parent_instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(original,base,sections,parent,1204),parent))
 for name,(head,size,count,opcode,offsets) in CASES.items():
  data=pe.raw_at(original,base,sections,head,size)
  ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(data,head))
  assert len(ins)==count and ins[-1].address+ins[-1].size==head+size
  assert [x.mnemonic for x in ins[:3]]==['push','mov','push']
  assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='8'
  assert [x.mnemonic for x in ins].count(opcode)==2
  assert not any(len(x.bytes)==5 and x.bytes[0]==0xe8 for x in ins)
  assert not any(head<=x<head+size for x in highlow)
  assert len([x for x in ins if x.mnemonic=='mov' and '[ebp + 8]' in x.op_str])>=2
  incoming=[x.address-parent for x in parent_instructions if len(x.bytes)==5 and x.bytes[0]==0xe8
            and ((x.address+5+struct.unpack_from('<i',x.bytes,1)[0])&0xffffffff)==head]
  assert incoming==offsets,(name,incoming,offsets)
  print(f'PASS original whole {name}: {size}B/{count} real x86, exactly two {opcode}, hidden 8B result, native RET 8, no E8/HIGHLOW')
  print(f'PASS original 1204B game polygon Boss actual E8 sites {[hex(x) for x in offsets]} all target {head:#010x}')
if __name__=='__main__':verify()
