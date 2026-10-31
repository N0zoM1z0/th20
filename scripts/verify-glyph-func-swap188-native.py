#!/usr/bin/env python3
"""Original whole 188B std::_Func_class<void>::_Swap and 161B source frontier.

Native original triple std::_Unfancy E8 are not in the installed MSVC
STL body. This script explicitly refuses whole parent exact credit.
"""
import difflib,hashlib,importlib.util,struct,subprocess,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('swap188pe',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('swap188cm',ROOT/'scripts/compare-coff-function.py')
cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00414C80
SHA='bd26afa8cbf43e1b3a8a8537b77b089f737ca7a740074f1d8ac3fbdb11d85858'
PARENT=0x00417A90
PARENT_SHA='c9ad68875594b49feb0f43c0fb920cff68c9d95fe7404452e0eb9de1f65824e6'
CALLS={0x16:0x00414AF0,0x25:0x00414AF0,0x34:0x00414AD0,
 0x3F:0x00414AD0,0x48:0x00414C60,0x54:0x00414C60,
 0x5F:0x00413F80,0x68:0x0040B280,0x74:0x00414BE0,
 0x7D:0x0040B280,0x89:0x00414BE0,0x92:0x0040B280,
 0x9E:0x00414BE0,0xA6:0x00414310,0xB1:0x005429EE}
DIR32={0x07:0x005B25C0}
PREFIX='?_Swap@?$_Func_class@X$$V@std@@'
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im)
 original=pe.raw_at(im,base,sec,HEAD,188)
 assert hashlib.sha256(original).hexdigest()==SHA
 ni=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,HEAD))
 assert len(ni)==63 and ni[-1].address+ni[-1].size==HEAD+188
 assert (ni[-1].mnemonic,ni[-1].op_str)==('ret','4')
 assert calls(ni,HEAD)==CALLS
 hl={x-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,x,4))[0]
     for x in pe.physical_highlow(im,base,sec) if HEAD<=x<HEAD+188}
 assert hl==DIR32
 p=pe.raw_at(im,base,sec,PARENT,26)
 assert hashlib.sha256(p).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(p,PARENT))
 assert len(pi)==12 and calls(pi,PARENT)[0x0E]==HEAD
 obj=ROOT/'build/core1075-canonical/GlyphTextQueuePump254.obj'
 syms=subprocess.run(['strings',str(obj)],capture_output=True,text=True,check=True).stdout.splitlines()
 sym=next(x for x in syms if x.startswith(PREFIX))
 candidate,rel=cm.object_function(obj,sym,161)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(candidate,0))
 assert len(candidate)==161 and len(ci)==54
 assert sum(x['type']=='REL32' for x in rel)==12
 assert sum(x['type']=='DIR32' for x in rel)==1
 assert all(x['addend']==0 for x in rel)
 extra=[x for x in ni if x.size==5 and x.bytes[0]==0xE8 and
        (x.address-HEAD) in (0x68,0x7D,0x92)]
 assert len(extra)==3 and all(calls(ni,HEAD)[x.address-HEAD]==0x0040B280 for x in extra)
 # The 27 real extra bytes are exactly the three original live
 # std::_Unfancy calls with return-pointer stack cleanup/re-push.
 diff=[x for x in difflib.SequenceMatcher(None,[i.mnemonic for i in ci],
         [i.mnemonic for i in ni],autojunk=False).get_opcodes() if x[0]!='equal']
 assert [(x[0],x[2]-x[1],x[4]-x[3]) for x in diff]==[('insert',0,3)]*3
 for code,_,_,lo,hi in diff:
  assert [i.mnemonic for i in ni[lo:hi]] in (['call','add','push'],['push','call','add'])
 for site in (0x68,0x7D,0x92):
  offset=site
  assert offset in CALLS and CALLS[offset]==0x0040B280
 assert cm.compare_unit('glyph_queue_func_swap_26')['result']=='exact'
 assert cm.compare_unit('glyph_queue_func_copy_assign_60')['result']=='exact'
 assert cm.compare_unit('glyph_text_queue_pump_254')['result']=='exact'
 print('PASS original whole 188B/63-i386 generic std::_Func_class<void>::_Swap, all 15 native E8 and one native PE HIGHLOW')
 print('PASS actual original 26B std::function::swap parent E8 +0x0E into this 188B physical native head')
 print('NONEXACT: full natural C++20 source _Swap is 161B/54 i386, 12 E8/one DIR32')
 print('SOURCE DIFF: exactly 3 additional original live E8 std::_Unfancy(0x40B280) with stack cleanup/operand forwarding, 9B/3 instructions each')
 print('No 188B exact unit or game-authored credit, prior original 26B wrapper and 60B assign remain independently strict exact')
if __name__=='__main__':verify()
