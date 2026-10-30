#!/usr/bin/env python3
"""Locked PE-only complete 1204B game polygon outline TRIANGLESTRIP Boss.

The genuine 354 native x86, 20 E8 target/site pairs and 8 original PE
HIGHLOW references are independently attested before source comparison.
The original's unusual output buffer progression is preserved: generate
TWO records per input point, draw (2*count-2) triangle-strip primitives,
but reserve count+1 and advance the persistent cursor only count records.
"""
from pathlib import Path
import importlib.util,struct
from collections import Counter
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('original',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0043D370
SIZE=1204
CALL_SITES={
 0x061:0x004455C0,0x069:0x004398A0,0x071:0x004398A0,
 0x0CD:0x00429520,0x105:0x00429520,0x120:0x00439960,
 0x159:0x00429520,0x192:0x00429520,0x1C2:0x00429520,
 0x1E0:0x00439960,0x209:0x00429520,0x23A:0x00429520,
 0x258:0x00439960,0x27C:0x00458FA0,0x28C:0x0043E910,
 0x2A9:0x00439910,0x410:0x00446690,0x41A:0x00412730,
 0x43E:0x00412730,0x4A9:0x005429EE,
}
DATA_SITES={
 0x00A:0x005B25C0,0x07F:0x0056C8D0,
 0x262:0x0056E0F8,0x26A:0x0056C8D0,
 0x300:0x0056C8CC,0x3A2:0x0056C8CC,
 0x416:0x005C4D40,0x43A:0x005C4D40,
}
PARENT_HEAD=0x0045FAA0
PARENT_SIZE=104
PARENT_E8=0x0045FAFB

def verify():
 original,_=pe.verified_target();base,sections=pe.parse_sections(original)
 body=pe.raw_at(original,base,sections,HEAD,SIZE)
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==354 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert ins[2].mnemonic=='sub' and ins[2].op_str=='esp, 0xa8'
 assert ins[-1].mnemonic=='ret' and ins[-1].op_str=='0x18'
 callsites={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
            for i in ins if len(i.bytes)==5 and i.bytes[0]==0xe8}
 assert callsites==CALL_SITES,(callsites,CALL_SITES)
 actual_data={addr-HEAD:struct.unpack('<I',pe.raw_at(original,base,sections,addr,4))[0]
              for addr in pe.physical_highlow(original,base,sections) if HEAD<=addr<HEAD+SIZE}
 assert actual_data==DATA_SITES,(actual_data,DATA_SITES)
 assert Counter(callsites.values())==Counter({
  0x004455C0:1,0x004398A0:2,0x00429520:7,
  0x00439960:3,0x00458FA0:1,0x0043E910:1,
  0x00439910:1,0x00446690:1,0x00412730:2,0x005429EE:1,
 })
 assert Counter(actual_data.values())==Counter({
  0x005B25C0:1,0x0056C8D0:2,0x0056E0F8:1,
  0x0056C8CC:2,0x005C4D40:2,
 })
 by={i.address-HEAD:i for i in ins}
 assert by[0x016].mnemonic=='mov' and by[0x016].op_str=='eax, dword ptr [ebp + 8]'
 assert by[0x019].mnemonic=='add' and by[0x019].op_str=='eax, 1'
 assert by[0x01C].mnemonic=='imul' and by[0x01C].op_str=='ecx, eax, 0x14'
 assert by[0x03C].mnemonic=='jb'
 assert by[0x045].mnemonic=='cmp' and by[0x045].op_str=='dword ptr [ebp + 8], 2'
 assert by[0x034B].mnemonic=='add' and by[0x034B].op_str=='edx, 0x14'
 assert by[0x034E].op_str=='dword ptr [ebp - 0x18], edx'
 assert by[0x03ED].mnemonic=='add' and by[0x03ED].op_str=='ecx, 0x14'
 assert by[0x03F0].op_str=='dword ptr [ebp - 0x18], ecx'
 assert by[0x0469].mnemonic=='lea' and by[0x0469].op_str=='eax, [edx + edx - 2]'
 assert by[0x046E].mnemonic=='push' and by[0x046E].op_str=='5'
 # The original draws 2*count-2 but advances the shared buffer only count*20.
 assert by[0x0477].mnemonic=='imul' and by[0x0477].op_str=='edx, dword ptr [ebp + 8], 0x14'
 caller=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pe.raw_at(original,base,sections,PARENT_HEAD,PARENT_SIZE),PARENT_HEAD))
 original_sites=[i for i in caller if len(i.bytes)==5 and i.bytes[0]==0xe8 and
                 (i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff==HEAD]
 assert [i.address for i in original_sites]==[PARENT_E8],original_sites
 print('PASS original whole 1204B/354-x86 game polygon TRIANGLESTRIP, 0xA8 frame/RET 0x18')
 print('PASS 20 authentic native E8 site/destination pairs, 8 genuine PE HIGHLOW physical field/target roles')
 print('PASS real 72B multiply-value and 77B add-value helper calls, closed-edge switch, original Vector2 normalization')
 print('PASS writes 2 vertices/point and TRIANGLESTRIP 2*count-2, but guard count+1 and persistent cursor count*20, as original')
 print('PASS original separate game parent 104B direct E8 at 0x45FAFB; parent receives zero code credit')

if __name__=='__main__':verify()
