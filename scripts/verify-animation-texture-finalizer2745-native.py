#!/usr/bin/env python3
"""Whole original game 2745B alpha-fringe finalizer strict native proof.

Coverage is the complete 2745B game function. Entire indivisible 2798B
COFF contribution is also compared against original actual code + 53B
post-return alignment/jump-table/format data. No truncated comparisons.
"""
import hashlib,importlib.util,struct,sys
from pathlib import Path
from capstone import Cs,CS_ARCH_X86,CS_MODE_32
ROOT=Path(__file__).resolve().parents[1];sys.path.insert(0,str(ROOT/'scripts'))
s=importlib.util.spec_from_file_location('texfinpe',ROOT/'scripts/verify-animation-draw-boss-native.py');pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
s=importlib.util.spec_from_file_location('texfincm',ROOT/'scripts/compare-coff-function.py');cm=importlib.util.module_from_spec(s);s.loader.exec_module(cm)
HEAD=0x00451910;CODE=2745;COMPARED=2798
CODE_SHA='1b4a86d1336a36cd506b27e58c8e750b26874ec42a1a8da94e8e96fadfa58924'
E8={0x18C:0x00451880,0x1B6:0x00451880,0x1E4:0x00451880,0x215:0x00451880,
    0x3C3:0x00451640,0x3ED:0x00451640,0x417:0x00451640,0x444:0x00451640,
    0x652:0x00451700,0x67C:0x00451700,0x6A6:0x00451700,0x6D3:0x00451700,
    0x8E5:0x004517C0,0x90F:0x004517C0,0x939:0x004517C0,0x966:0x004517C0,
    0xAAE:0x005429EE}
DATA={0x0A:0x005B25C0,0xA7:0x004523E0,0xAE:0x004523CC,
      0xABC:0x004519C2,0xAC0:0x00451BEF,0xAC4:0x00451E7E,
      0xAC8:0x0045210D,0xACC:0x0045239B}
CHILDREN={0x00451880:(139,'256e84d8c656400232a00d5e608bd748bbfcbe09642036993da93c0df08eceaa'),
          0x00451640:(183,'2aa5d4dc48a27a2c145a83ee7243f1120ed52e256404d4af72b66c3f1e14d1d6'),
          0x00451700:(183,'055a3aa98aff47c9d79add63f2fbd065e9cdbd0056ee64ad91b221b786987f86'),
          0x004517C0:(187,'44ddd8633afe50deac4cef887897e2f3c072ffea4e089b5bcbf8d7a7a0beddd6')}
SYM='?finalize_uploaded_texture_451910@NativeRendererTextureMemoryView@th20@@QAEXPAUIDirect3DTexture9@@@Z'
def native_calls(ins,head):
 return {i.address-head:(i.address+5+struct.unpack_from('<i',i.bytes,1)[0])&0xFFFFFFFF
         for i in ins if i.size==5 and i.bytes[0]==0xE8}
def verify():
 im,_=pe.verified_target();base,sec=pe.parse_sections(im);hl=pe.physical_highlow(im,base,sec)
 original=pe.raw_at(im,base,sec,HEAD,COMPARED);code=original[:CODE]
 assert hashlib.sha256(code).hexdigest()==CODE_SHA
 instructions=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(code,HEAD))
 assert len(instructions)==759 and instructions[-1].address+instructions[-1].size==HEAD+CODE
 assert (instructions[-1].mnemonic,instructions[-1].op_str)==('ret','4')
 assert native_calls(instructions,HEAD)==E8
 native_data={p-HEAD:struct.unpack('<I',pe.raw_at(im,base,sec,p,4))[0]
              for p in hl if HEAD<=p<HEAD+COMPARED}
 assert native_data==DATA
 assert {k:v for k,v in DATA.items() if k<CODE}=={
  0x0A:0x005B25C0,0xA7:0x004523E0,0xAE:0x004523CC}
 assert original[CODE:CODE+3]==bytes.fromhex('0f1f00')
 assert original[CODE+3:CODE+23]==struct.pack('<5I',
  0x004519C2,0x00451BEF,0x00451E7E,0x0045210D,0x0045239B)
 format_map=original[CODE+23:]
 assert len(format_map)==30
 assert format_map.hex()=='000404040404040404040404040404040404040404000404040102040403'
 assert list(native_data)==[0x0A,0xA7,0xAE,0xABC,0xAC0,0xAC4,0xAC8,0xACC]
 for addr,(n,sha) in CHILDREN.items():
  raw=pe.raw_at(im,base,sec,addr,n)
  assert hashlib.sha256(raw).hexdigest()==sha
  ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw,addr))
  assert ci and ci[-1].address+ci[-1].size==addr+n
  assert list(E8.values()).count(addr)==4
 uploader=pe.raw_at(im,base,sec,0x0044E8F0,562)
 assert hashlib.sha256(uploader).hexdigest()=='1b0d6d08d535765761f1cfaf5f9140a7e0963f0b04b00daae23cac98cb182a19'
 ui=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(uploader,0x0044E8F0))
 assert native_calls(ui,0x0044E8F0)[0x1FB]==HEAD
 obj=ROOT/'build/core1103-canonical/AnimationTextureFinalize2745.obj'
 raw_coff,rel=cm.object_function(obj,SYM,COMPARED)
 assert len(raw_coff)==COMPARED and len(rel)==25
 assert sum(r['type']=='REL32' for r in rel)==17
 assert sum(r['type']=='DIR32' for r in rel)==8
 assert all(r['addend']==0 for r in rel)
 ci=list(Cs(CS_ARCH_X86,CS_MODE_32).disasm(raw_coff[:CODE],0))
 assert len(ci)==759 and ci[-1].address+ci[-1].size==CODE
 assert ci[-1].mnemonic=='ret' and ci[-1].op_str=='4'
 roles={**{k:('DIR32',v) for k,v in DATA.items()},
        **{k+1:('REL32',v) for k,v in E8.items()}}
 assert set(roles)=={r['offset'] for r in rel}
 for r in rel:assert r['type']==roles[r['offset']][0]
 left=bytearray(raw_coff);right=bytearray(original)
 for r in rel:
  k=r['offset'];left[k:k+4]=right[k:k+4]=b'\0'*4
 assert left==right
 exact=cm.compare_unit('animation_texture_finalize_alpha_2745')
 assert exact['result']=='exact' and exact['size']==CODE
 assert exact['matched_bytes']==CODE and exact['compared_size']==COMPARED
 assert exact['matched_compared_bytes']==COMPARED
 assert len(exact['relocations'])==len(roles)==25
 for r in exact['relocations']:
  k=int(r['offset'],16)
  assert k in roles and r['type']==roles[k][0]
  assert int(r['target'],16)==roles[k][1]
 print('PASS entire original game Renderer alpha-fringe finalizer 2745B/759 i386, native 17 E8/3 in-function PE HIGHLOW, exact complete code')
 print('PASS four real native custom texel kernels, 4 E8 each, source and original 562B uploader actual original edge into this 2745B Boss')
 print('PASS original SEPARATE after-ret 53B region = 3B alignment, 20B 5 relocated jump targets, 30B byte-format selector; no extra game function credit for data')
 print('PASS entire natural MSVC COFF contribution 2798/2798 bytes, 2698/2698 nonrelocated bytes, all 25 true original relocation site/type/target roles')
 print('PASS strict source-scoped canonical animation_texture_finalize_alpha_2745 exact 2745/2745 original game code, compare_size 2798/2798, one cold object')
if __name__=='__main__':verify()
