#!/usr/bin/env python3
"""Original whole 38B/41B Card archive selectors and true 20B/22B indexers."""
from pathlib import Path
import hashlib, importlib.util, struct, sys
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
R=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(R/'scripts'))
def load(n,p):
    spec=importlib.util.spec_from_file_location(n,R/p);m=importlib.util.module_from_spec(spec);spec.loader.exec_module(m);return m
cf=load('archive_cf','scripts/compare-coff-function.py')
pe=load('archive_pe','scripts/verify-animation-draw-boss-native.py')
OBJ=R/'build/core1122-canonical/CardTimeArchiveAccessors38_41.obj'
SPECS=[
 ('card_time_primary_archive_38',0x00488740,38,15,
  '5f48bb4da1245bfaf0b30ef8b3b11fa2a4080dc49c38cd6f7b1604340367da8f',
  '?primary_record_488740@NativeCardTimeSaveArchiveView@th20@@QAEPAEH@Z',
  {0x19:0x00414580}),
 ('card_time_alternate_archive_41',0x00488770,41,15,
  '0161cabfee8293db70aa366e0a193190568abee5cde6e9707d80045c5d89ead0',
  '?alternate_record_488770@NativeCardTimeSaveArchiveView@th20@@QAEPAEH@Z',
  {0x1B:0x00486E30}),
 ('card_time_raw_record_index_20',0x00486E30,20,9,
  '33b39b0c90faa5ff9aa9c9bf53adeedd1be72cb87b1e4c5bba1183ad916cd171',
  '?at@NativeCardRawRecordArray@th20@@QAEAAUNativeCardRawRecord44@2@H@Z',
  {}),
]
def main():
    image=cf.verified_target()
    base,secs=pe.parse_sections(image)
    highlow=pe.physical_highlow(image,base,secs)
    for unit,addr,n,num,sha,sym,calls in SPECS:
        original=pe.raw_at(image,base,secs,addr,n)
        assert len(original)==n and hashlib.sha256(original).hexdigest()==sha
        ins=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(original,addr))
        assert len(ins)==num and ins[-1].address+ins[-1].size==addr+n
        assert (ins[-1].mnemonic,ins[-1].op_str)==('ret','4')
        native_calls={i.address-addr:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xffffffff
                      for i in ins if i.size==5 and i.bytes[0]==0xe8}
        assert native_calls==calls
        assert not any(addr<=p<addr+n for p in highlow)
        body,rr=cf.object_function(OBJ,sym,n)
        assert len(rr)==len(calls) and len(body)==n
        mask={j for r in rr for j in range(r['offset'],r['offset']+4)}
        assert all(original[j]==body[j] for j in range(n) if j not in mask)
        for r in rr:
            assert r['type']=='REL32' and r['addend']==0
            target=calls[r['offset']-1]
            expected=('?at@NativeCardPointerSlots50@' if n==38 else '?at@NativeCardRawRecordArray@')
            assert r['symbol'].startswith(expected)
            assert target==(0x00414580 if n==38 else 0x00486E30)
        result=cf.compare_unit(unit)
        assert result['result']=='exact' and result['matched_bytes']==n
        print(f'PASS {unit}: original whole {n}/{n}B, {num} i386, {len(calls)} anchored native E8 target(s), zero HIGHLOW; canonical exact receipt')
    # Confirm the generated pointer-array indexer folds to the existing
    # 22B original physical head already accepted in the Vector3 owner.
    folded_head=0x00414580
    folded_sha='63c49b1813004cda4fdbb91fb68008a819c44d98c1c64a7fc76b4405f26a10b8'
    original=pe.raw_at(image,base,secs,folded_head,22)
    assert hashlib.sha256(original).hexdigest()==folded_sha
    b,r=cf.object_function(OBJ,'?at@NativeCardPointerSlots50@th20@@QAEAAPAEH@Z',22)
    assert bytes(b)==original and not r
    folded=cf.compare_unit('vector3_index')
    assert folded['result']=='exact' and folded['matched_bytes']==22
    # Real accepted parent Card clock must call both distinct selectors.
    p=0x004872D0
    for off,target in ((0x1E7,0x00488740),(0x225,0x00488770)):
        e8=pe.raw_at(image,base,secs,p+off,5)
        assert e8[0]==0xe8 and p+off+5+struct.unpack('<i',e8[1:])[0]==target
    parent=cf.compare_unit('card_clock_boss_645')
    assert parent['result']=='exact' and parent['matched_bytes']==645
    print('PASS 22/22B previously accepted folded pointer indexer; no duplicate 22B head/credit')
    print('PASS native 645B Card clock source invokes both original 38B/41B archive selectors')
    print('PASS two NEW game-authored 38B + 41B heads = 79 original bytes; new 20B generic index helper proven exact but held authorship-review and uncredited')
if __name__=='__main__':main()
