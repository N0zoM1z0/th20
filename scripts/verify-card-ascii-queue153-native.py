#!/usr/bin/env python3
"""Independent original PE proof of full 153B Card ASCII task queue."""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('ascii_pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('ascii_coff',ROOT/'scripts/compare-coff-function.py')
coff=importlib.util.module_from_spec(s);s.loader.exec_module(coff)
HEAD=0x00470180
NATIVE_SHA='49b7446465141dcc4380a69d175ece20eeeab2845c132c9f097fda95b1e50d32'
CALLS={0x39:0x0040C310,0x42:0x0040B730,0x5D:0x00470A20,0x69:0x0040B900,0x78:0x00414400,0x8E:0x005429EE}
HIGHLOW={0x06:0x00568E75,0x15:0x005B25C0,0x35:0x005C0240}
def verify():
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 body=pe.raw_at(img,base,secs,HEAD,153)
 assert hashlib.sha256(body).hexdigest()==NATIVE_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(body,HEAD))
 assert len(ins)==45 and ins[-1].address+ins[-1].size==HEAD+153
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','0x28')
 native_calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert native_calls==CALLS
 native_fields={p-HEAD:struct.unpack('<I',pe.raw_at(img,base,secs,p,4))[0] for p in pe.physical_highlow(img,base,secs) if HEAD<=p<HEAD+153}
 assert native_fields==HIGHLOW
 assert len(CALLS)+len(HIGHLOW)==9
 parent=pe.raw_at(img,base,secs,0x00487C30,1896)
 assert hashlib.sha256(parent).hexdigest()=='dccf63fb37fe2957514c65760010eb46e59a8c2f59f710a8c882e7edaa403410'
 parent_calls={i.address-0x00487C30:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff for i in Cs(CS_ARCH_X86,CS_MODE_32).disasm(parent,0x00487C30) if i.size==5 and i.bytes[0]==0xe8}
 assert [off for off,target in parent_calls.items() if target==HEAD]==[0x330]
 unit=coff.compare_unit('card_ascii_task_queue_153')
 assert unit['result']=='exact' and unit['size']==153 and unit['matched_bytes']==153
 assert len(unit['relocations'])==9
 print('PASS immutable original 153B/45-i386 ASCII task enqueue, 6 E8/3 PE HIGHLOW, true ret 0x28')
 print('PASS original 1,896B Card start parent E8 +0x330 -> ASCII queue, independent PE destination')
 print('PASS canonical 153/153 natural recursive_mutex lock_guard + std::list push_back + value cleanup')
 print('Card start 1,896B parent remains NONEXACT; no transitive parent credit')
if __name__=='__main__':verify()
