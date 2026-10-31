#!/usr/bin/env python3
"""Independent immutable-PE proof: 0x5B66E0 is a native 12B PMR LIST.

Original 2227B producer, whole exact 254B consumer and 56B submission
bridge share one physical object; never an extern queue pointer at that VA.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('queueglobalpe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('queueglobalcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
QUEUE=0x005B66E0
PUMP=0x00416140
CORE=0x00415830
SUBMIT=0x004162F0
PUMP_SHA='ef9966b4d7958ec50e93ea140df2f52ba3109e6ecf5a9caf0ecd1376510e0899'
CORE_SHA='c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70'
SUBMIT_SHA='5213451236ddccc50439af53540e50639d92771ca89506c80233331e217ebac9'
SIZE_SHA='1aed1ade9e55a3d2cc3df6c4d1443902049467d3579f382327ed822dd685a731'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify(candidate=None):
 image,_=pe.verified_target();base,sec=pe.parse_sections(image)
 high=pe.physical_highlow(image,base,sec)
 pump=pe.raw_at(image,base,sec,PUMP,254)
 assert hashlib.sha256(pump).hexdigest()==PUMP_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(pump,PUMP))
 assert len(pi)==74 and pi[-1].address+pi[-1].size==PUMP+254
 p_data={p-PUMP:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
         for p in high if PUMP<=p<PUMP+254}
 assert {p_data[k] for k in (0x29,0x7C,0x94,0xAB)}=={QUEUE}
 assert p_data[0x3D]==p_data[0x59]==0x005C0240
 assert calls(pi,PUMP)[0x2D]==0x00412730
 size=pe.raw_at(image,base,sec,0x00412730,17)
 assert hashlib.sha256(size).hexdigest()==SIZE_SHA
 size_ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(size,0x00412730))
 assert any(i.mnemonic=='mov' and i.op_str=='eax, dword ptr [eax + 8]' for i in size_ins)
 assert calls(pi,PUMP)[0x80]==0x00415600
 assert calls(pi,PUMP)[0xAF]==0x00415550
 core=pe.raw_at(image,base,sec,CORE,2227)
 assert hashlib.sha256(core).hexdigest()==CORE_SHA
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(core,CORE))
 assert len(ci)==470
 c_data={p-CORE:struct.unpack('<I',pe.raw_at(image,base,sec,p,4))[0]
         for p in high if CORE<=p<CORE+2227}
 assert c_data[0x820]==QUEUE
 assert calls(ci,CORE)[0x824]==SUBMIT
 bridge=pe.raw_at(image,base,sec,SUBMIT,56)
 assert hashlib.sha256(bridge).hexdigest()==SUBMIT_SHA
 bi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bridge,SUBMIT))
 assert len(bi)==22 and bi[-1].address+bi[-1].size==SUBMIT+56
 assert calls(bi,SUBMIT)=={0x0D:0x0040B280,0x2C:0x004131E0}
 assert any(i.mnemonic=='mov' and i.op_str=='edx, dword ptr [ecx + 4]' for i in bi)
 for unit in ('glyph_text_queue_pump_254','glyph_text_queue_submit_56','glyph_text_job_capture_132','glyph_text_job_dtor_23'):
  assert cm.compare_unit(unit)['result']=='exact'
 print('PASS entire original 254B/74-i386 pump: four physical PE HIGHLOW -> SAME 0x005B66E0 PMR list, native count +8')
 print('PASS original 2227B/470-i386 GDI text core PE HIGHLOW +0x820 -> SAME 0x005B66E0, E8 +0x824 -> native 56B submission')
 print('PASS original 56B submit bridge reads receiver+4 and invokes real 151B PMR _Emplace; no extra pointer global')
 print('PASS whole exact 254B queue pump, 56B bridge, 132B capture and 23B dtor retain valid canonical receipts')
 if candidate:
  sym='?native_text_core_415830@th20@@YA_KPBUNativeTextTransform4@1@HHIPBDPAUIDirect3DBaseTexture9@@HHHHV?$function@$$A6AXXZ@std@@@Z'
  b,r=cm.object_function(candidate,sym,2080)
  inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(b),0))
  assert len(b)==2080 and len(inst)==486
  assert sum(v['type']=='REL32' for v in r)==25 and sum(v['type']=='DIR32' for v in r)==54
  globals_=[x for x in r if 'native_glyph_task_queue_5b66e0@' in x['symbol']]
  bridge_calls=[x for x in r if 'submit_4162f0@' in x['symbol']]
  assert len(globals_)==len(bridge_calls)==1
  assert globals_[0]['offset']==0x72A and globals_[0]['type']=='DIR32'
  assert bridge_calls[0]['offset']==0x72F and bridge_calls[0]['type']=='REL32'
  print('PASS natural 2080B/486 C++ candidate now references actual global std::pmr::list address and borrowed exact 56B member bridge')
 print('2227B parent remains SOURCE-PRESENT/NONEXACT, no additional game exact credit')
if __name__=='__main__':
 import argparse
 parser=argparse.ArgumentParser();parser.add_argument('--candidate-object',type=Path)
 verify(parser.parse_args().candidate_object)
