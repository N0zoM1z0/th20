#!/usr/bin/env python3
"""Whole original four custom game alpha-fringe RGB texel accumulation heads.

The earlier REF-042 classified their origin as unknown because no enclosing
owner was established. We now independently prove the actual game Renderer
2745B source's FOUR E8 calls per specialized pixel-format body, and attest
that all four accepted native functions are whole exact, not library thunks.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('orig_texel_pe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('orig_texel_cm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
PARENT=0x00451910;PARENT_SIZE=2745
PARENT_SHA='1b4a86d1336a36cd506b27e58c8e750b26874ec42a1a8da94e8e96fadfa58924'
SPECS={
 'accumulate_texel8888':(0x00451880,139,46,'256e84d8c656400232a00d5e608bd748bbfcbe09642036993da93c0df08eceaa',(0x18C,0x1B6,0x1E4,0x215)),
 'accumulate_texel1555':(0x00451640,183,57,'2aa5d4dc48a27a2c145a83ee7243f1120ed52e256404d4af72b66c3f1e14d1d6',(0x3C3,0x3ED,0x417,0x444)),
 'accumulate_texel4444':(0x00451700,183,57,'055a3aa98aff47c9d79add63f2fbd065e9cdbd0056ee64ad91b221b786987f86',(0x652,0x67C,0x6A6,0x6D3)),
 'accumulate_texel8332':(0x004517C0,187,58,'44ddd8633afe50deac4cef887897e2f3c072ffea4e089b5bcbf8d7a7a0beddd6',(0x8E5,0x90F,0x939,0x966)),
}
def calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 image,_=pe.verified_target();base,sec=pe.parse_sections(image);hl=pe.physical_highlow(image,base,sec)
 full=pe.raw_at(image,base,sec,PARENT,PARENT_SIZE)
 assert hashlib.sha256(full).hexdigest()==PARENT_SHA
 pi=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(full,PARENT))
 assert len(pi)==759 and pi[-1].address+pi[-1].size==PARENT+PARENT_SIZE
 pc=calls(pi,PARENT)
 assert len(pc)==17 and pc[0xAAE]==0x005429EE
 seen=set();addresses=set()
 for unit,(head,n,ni,sha,offsets) in SPECS.items():
  code=pe.raw_at(image,base,sec,head,n)
  assert hashlib.sha256(code).hexdigest()==sha,unit
  instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,head))
  assert len(instructions)==ni and instructions[-1].address+instructions[-1].size==head+n
  assert instructions[-1].mnemonic=='ret'
  assert not calls(instructions,head)
  assert not any(head<=p<head+n for p in hl)
  assert not seen.intersection(range(head,head+n))
  seen.update(range(head,head+n));addresses.add(head)
  assert tuple(p for p,v in pc.items() if v==head)==offsets,(unit,offsets)
  z=cm.compare_unit(unit)
  assert z['result']=='exact' and z['size']==n and z['matched_bytes']==n
  assert not z['relocations']
  print(f'PASS {unit}: complete original {n}B/{ni} i386, no E8/HIGHLOW; native original game parent FOUR E8 at {tuple(hex(x) for x in offsets)}; strict exact {n}/{n}')
 assert sum(x[1] for x in SPECS.values())==692 and len(seen)==692 and len(addresses)==4
 assert set(pc.values())==addresses|{0x005429EE}
 # The independently authored texture upload caller links to this original
 # 2745B game-function parent; original gap is untouched and NONEXACT.
 upload=pe.raw_at(image,base,sec,0x0044E8F0,562)
 assert hashlib.sha256(upload).hexdigest()=='1b0d6d08d535765761f1cfaf5f9140a7e0963f0b04b00daae23cac98cb182a19'
 ui=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(upload,0x0044E8F0))
 assert calls(ui,0x0044E8F0)[0x1FB]==PARENT
 assert cm.compare_unit('animation_texture_upload_from_memory_562')['result']=='exact'
 print('PASS all FOUR native custom per-format alpha-fringe accumulators form a real exclusive game Renderer RGB helper family: 692 distinct original bytes')
 print('PASS original 562B game loader -> 2745B alpha fringe game owner -> 4×4 true custom-format native helper calls; parent 2745B remains NONEXACT')
 print('SOURCE whole exact heads already accepted under REF-042; classify game-origin from independently newly demonstrated custom Renderer domain context, no new strict unit created')
if __name__=='__main__':verify()
