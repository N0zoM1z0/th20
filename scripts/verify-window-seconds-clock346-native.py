#!/usr/bin/env python3
"""Complete native WindowState 346B clock getter: code, imports, E8 and data."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name,path):
 spec=importlib.util.spec_from_file_location(name,R/path)
 m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
coff=load('winsecs346_coff','scripts/compare-coff-function.py')
pe=load('winsecs346_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x0041CB10
LENGTH=346
ORIGINAL_SHA='0ca56b4953b8cd383b37eeab4cf3798be6abcfb7cda1b0210f694d5818598538'
OBJ=R/'build/core1123-canonical/WindowSecondsClock346.obj'
SYM='?current_seconds_41cb10@NativeCardWindowTimeView@th20@@QAENXZ'
NATIVE_CALLS={
 0x01A:0x0040C310,0x023:0x0040B730,
 0x056:0x00542E00,0x06C:0x00542E00,
 0x0B0:0x0040B900,0x139:0x0040B900,
 0x146:0x0040B900,0x151:0x005429EE,
}
NATIVE_DATA={
 0x007:0x005B25C0,0x016:0x005C0240,
 0x02A:0x005B67D0,0x030:0x005B67D4,
 0x040:0x0056C11C,0x049:0x005B67D8,
 0x052:0x005B67DC,0x05D:0x005B67D4,
 0x063:0x005B67D0,0x083:0x005B8838,
 0x097:0x005B8838,0x0A4:0x005B8838,
 0x0C4:0x0056C2E8,0x0DB:0x0056CDD0,
 0x0E8:0x005B8838,0x0FC:0x005B8838,
 0x104:0x005B8838,0x10C:0x0056CD88,
 0x123:0x0056CD88,
}
CALL_TARGETS={
 '?slot@LockRegistry@':0x0040C310,
 '??0?$lock_guard@':0x0040B730,
 '__ltod3':0x00542E00,
 '__ultod3':0x00542E00,
 '??1?$lock_guard@':0x0040B900,
 '@__security_check_cookie@4':0x005429EE,
}
DATA_TARGETS={
 '___security_cookie':0x005B25C0,
 '?process_locks@':0x005C0240,
 '?window_state@':0x005B6758,
 '__imp__QueryPerformanceCounter@4':0x0056C11C,
 '__imp__timeGetTime@0':0x0056C2E8,
 '?correction@':0x0056CDD0,
 '__real@408f400000000000':0x0056CD88,
}

def main():
 exe=coff.verified_target()
 base,sec=pe.parse_sections(exe)
 code=pe.raw_at(exe,base,sec,HEAD,LENGTH)
 assert len(code)==LENGTH and hashlib.sha256(code).hexdigest()==ORIGINAL_SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(ins)==79 and ins[-1].address+ins[-1].size==HEAD+LENGTH
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 calls={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
        for i in ins if i.size==5 and i.bytes[0]==0xE8}
 data={site-HEAD:struct.unpack('<I',pe.raw_at(exe,base,sec,site,4))[0]
       for site in pe.physical_highlow(exe,base,sec) if HEAD<=site<HEAD+LENGTH}
 assert calls==NATIVE_CALLS
 assert data==NATIVE_DATA
 assert len(calls)==8 and len(data)==19
 # Original native switch from QPC to WinMM is through two different import slots.
 assert any(i.address==HEAD+0x03E and i.mnemonic=='call' for i in ins)
 assert any(i.address==HEAD+0x0C2 and i.mnemonic=='call' for i in ins)
 # The genuine signed/unsigned milliseconds compensation table is [0, 2^32].
 assert pe.raw_at(exe,base,sec,0x0056CDD0,16)==struct.pack('<dd',0.0,4294967296.0)
 assert pe.raw_at(exe,base,sec,0x0056CD88,8)==struct.pack('<d',1000.0)
 obj,rels=coff.object_function(OBJ,SYM,LENGTH)
 generated=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(bytes(obj),0))
 assert len(obj)==LENGTH and len(generated)==len(ins)==79
 assert len(rels)==27 and sum(r['type']=='REL32' for r in rels)==8
 assert sum(r['type']=='DIR32' for r in rels)==19
 assert [i.address for i in generated if i.size==5 and i.bytes[0]==0xE8]==sorted(calls)
 seen=set()
 for r in rels:
  off=r['offset'];ty=r['type'];symbol=r['symbol']
  native_site=off-1 if ty=='REL32' else off
  target=calls.get(native_site) if ty=='REL32' else data.get(native_site)
  assert target is not None and r['addend']>=0
  if ty=='REL32':
   expected=[x for prefix,x in CALL_TARGETS.items() if symbol.startswith(prefix)]
   assert expected==[target],(hex(native_site),symbol,target,expected)
  else:
   expected=[x for prefix,x in DATA_TARGETS.items() if symbol.startswith(prefix)]
   if symbol.startswith('?window_state@'):
    assert expected==[0x005B6758]
    assert target==0x005B6758+r['addend']
   else:
    assert expected==[target] and r['addend']==0,(hex(native_site),symbol,target,expected)
  seen.update(range(off,off+4))
 assert len(seen)==108
 assert all(a==z for j,(a,z) in enumerate(zip(code,obj)) if j not in seen)
 check=coff.compare_unit('window_seconds_clock_boss_346')
 assert check['result']=='exact' and check['matched_bytes']==346
 print('PASS original WindowState seconds 346/346B, 79 i386, 8/8 E8 and 19/19 PE HIGHLOW with every original physical site and destination')
 print('PASS all 238/238 ordinary body bytes, native Win32 QPC/WinMM import slots, signed i64 CRT conversion and actual 2^32 wrap table')
 print('PASS canonical MSVC source cold build receipt, one independent original game function 346B; no duplicate source/frame credit')
 # Both original calls from the independently exact 645B Card-clock Boss.
 caller=0x004872D0
 for off in (0x027,0x072):
  bytes_=pe.raw_at(exe,base,sec,caller+off,5)
  assert bytes_[0]==0xE8
  assert caller+off+5+struct.unpack('<i',bytes_[1:])[0]==HEAD
 parent=coff.compare_unit('card_clock_boss_645')
 assert parent['result']=='exact' and parent['matched_bytes']==645
 print('PASS both native exact 645B Card clock caller E8 sites target this genuine 346B original head')
if __name__=='__main__':
 main()
