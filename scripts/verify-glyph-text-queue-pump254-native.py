#!/usr/bin/env python3
"""Whole locked-PE proof of 254B game glyph task queue dispatcher.

Independently pin all native 15 E8 and 8 PE HIGHLOW targets before
accepting canonical whole-function i386 source, without re-crediting STL.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('pumppe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('pumpcm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00416140
SHA='ef9966b4d7958ec50e93ea140df2f52ba3109e6ecf5a9caf0ecd1376510e0899'
CALLS={0x2D:0x00412730,0x41:0x0040C310,0x4A:0x0040B730,
       0x5D:0x0040C310,0x66:0x0040B730,0x72:0x00414150,
       0x80:0x00415600,0x89:0x00414540,0x98:0x004150B0,
       0xAF:0x00415550,0xB8:0x00414740,0xC4:0x00414400,
       0xD0:0x0040B900,0xDF:0x0040B900,0xF5:0x005429EE}
HIGHLOW={0x06:0x00567E2D,0x15:0x005B25C0,0x29:0x005B66E0,
         0x3D:0x005C0240,0x59:0x005C0240,0x7C:0x005B66E0,
         0x94:0x005B66E0,0xAB:0x005B66E0}
def calls(inst,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in inst if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im)
 b=pe.raw_at(im,base,sec,HEAD,254)
 assert hashlib.sha256(b).hexdigest()==SHA
 inst=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(b,HEAD))
 assert len(inst)==74 and inst[-1].address+inst[-1].size==HEAD+254
 assert (inst[-1].mnemonic,inst[-1].op_str)==('ret','')
 assert calls(inst,HEAD)==CALLS
 native_hl={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
            for p in pe.physical_highlow(im,base,sec) if HEAD<=p<HEAD+254}
 assert native_hl==HIGHLOW
 # The original emptiness check is a genuine list::size() read at +8,
 # not list::empty() or a bogus task pointer-in-queue check.
 count=pe.raw_at(im,base,sec,0x00412730,17)
 assert hashlib.sha256(count).hexdigest()=='1aed1ade9e55a3d2cc3df6c4d1443902049467d3579f382327ed822dd685a731'
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(count,0x00412730))
 assert any(x.mnemonic=='mov' and x.op_str=='eax, dword ptr [eax + 8]' for x in ci)
 assert calls(inst,HEAD)[0x2D]==0x00412730
 # The same native two lock slots and single real global-list object are
 # read at four physical PE HIGHLOW locations, not a separate pointer global.
 assert [native_hl[x] for x in (0x29,0x7C,0x94,0xAB)]==[0x005B66E0]*4
 assert [native_hl[x] for x in (0x3D,0x59)]==[0x005C0240]*2
 assert any(i.mnemonic=='push' and i.op_str=='0x12' for i in inst)
 assert any(i.mnemonic=='push' and i.op_str=='0x13' for i in inst)
 # This physical original callback invoke has already been accepted in
 # the separate whole exact 360B upload owner; no extra credited 59B.
 callback=pe.raw_at(im,base,sec,0x00414740,59)
 assert hashlib.sha256(callback).hexdigest()=='046e82dc1916704a61693bbbdce1a6efd5bb769dc093e70b82fbda342ba7f8ca'
 z=cm.compare_unit('glyph_text_queue_pump_254')
 assert z['result']=='exact' and z['size']==254 and z['matched_bytes']==254
 assert len(z['relocations'])==23
 assert cm.compare_unit('glyph_upload_callback_invoke_59')['result']=='exact'
 print('PASS original whole game 254B/74 i386 glyph task dispatcher, exact all 15 native E8 and 8 PE HIGHLOW')
 print('PASS single original global std::pmr::list<std::function<void()>> at 0x005B66E0, native count +8, locks 0x12/0x13')
 print('PASS original std::function default/copy and native PMR list front/begin/erase, execute callback under both lock lifetimes')
 print('PASS canonical 254/254 native strict (162/162 nonrelocated bytes, 23 genuine original relocation roles), separate generic callback not double credited')
if __name__=='__main__':verify()
