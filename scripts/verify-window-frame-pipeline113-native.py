#!/usr/bin/env python3
"""Full original 113B frame timestamp pipeline and its accepted device/caller."""
from pathlib import Path
import hashlib,importlib.util,struct,sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(name,path):
 s=importlib.util.spec_from_file_location(name,R/path);m=importlib.util.module_from_spec(s);s.loader.exec_module(m);return m
cf=load('pipeline_cf','scripts/compare-coff-function.py')
pe=load('pipeline_pe','scripts/verify-animation-draw-boss-native.py')
HEAD=0x004AC0E0
SIZE=113
SHA='9ad2cf3886f3d23a07838f2577d9298bb21c6c548c69b39fd4fdf448edc22f6e'
CALLS={0x0D:0x004AC170,0x33:0x004AC200,0x5D:0x004AC270}
ROLES={'?read_frame_pair_4ac170@':0x004AC170,
       '?frame_time_u64_4ac200@':0x004AC200,
       '?frame_time_breakdown_4ac270@':0x004AC270}
def main():
 exe=cf.verified_target()
 base,secs=pe.parse_sections(exe)
 raw=pe.raw_at(exe,base,secs,HEAD,SIZE)
 assert len(raw)==SIZE and hashlib.sha256(raw).hexdigest()==SHA
 ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,HEAD))
 assert len(ins)==34 and ins[-1].address+ins[-1].size==HEAD+SIZE
 assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','')
 actual={i.address-HEAD:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
         for i in ins if i.size==5 and i.bytes[0]==0xe8}
 assert actual==CALLS
 assert not any(HEAD<=p<HEAD+SIZE for p in pe.physical_highlow(exe,base,secs))
 assert all(i.mnemonic!='call' or i.address-HEAD in CALLS for i in ins)
 obj=R/'build/core1126-canonical/WindowFramePipeline113.obj'
 sym='?frame_pipeline_4ac0e0@NativeFrameDeviceClockView@th20@@QAEPAUNativeFrameTimePair@2@XZ'
 code,rels=cf.object_function(obj,sym,SIZE)
 assert len(rels)==3 and all(r['type']=='REL32' and r['addend']==0 for r in rels)
 covered={j for r in rels for j in range(r['offset'],r['offset']+4)}
 assert len(covered)==12 and all(raw[i]==code[i] for i in range(SIZE) if i not in covered)
 for r in rels:
  site=r['offset']-1
  target=CALLS[site]
  matches=[v for prefix,v in ROLES.items() if r['symbol'].startswith(prefix)]
  assert matches==[target],(hex(site),target,r['symbol'])
 assert b'\x64\xa1' not in raw and b'\xe8' in raw
 # The parent original function calls this 113B device helper with ECX=this.
 caller=0x004ABD50+0x1A7
 call=pe.raw_at(exe,base,secs,caller,5)
 assert call[0]==0xe8 and caller+5+struct.unpack_from('<i',call,1)[0]==HEAD
 for unit,n in [('window_frame_pipeline_113',113),('window_frame_device_clock_boss_437',437),('window_frame_clock_dispatch_32',32)]:
  check=cf.compare_unit(unit)
  assert check['result']=='exact' and check['matched_bytes']==n,(unit,check)
 print('PASS frame device pipeline complete original 113/113B, 34 instructions, 3/3 true E8 physical sites and original callee roles')
 print('PASS all 101/101 ordinary bytes, zero original PE HIGHLOW/security-cookie fields, natural GS-disabled compiler mode')
 print('PASS genuine original 437B parent E8 and all 3/3 affected source-scoped protected MSVC whole exact receipts')
if __name__=='__main__':main()
