#!/usr/bin/env python3
"""Original 8B game polygon width/radius constants vs native pinned COFF .rdata.

Verify two separately external-linked float symbols occur consecutively at
0 and 4 in the same COFF .rdata region and exactly equal immutable TH20 PE
original 16.0f,32.0f at 0x0056CD90. Data bytes never count as game .text.
"""
from pathlib import Path
import argparse,subprocess,re,struct,importlib.util
ROOT=Path(__file__).resolve().parents[1]
s=importlib.util.spec_from_file_location('orig',ROOT/'scripts/verify-animation-draw-boss-native.py')
pe=importlib.util.module_from_spec(s);s.loader.exec_module(pe)
HEAD=0x0056CD90
SYMS=('?native_sixteen@th20@@3MB','?native_polygon_radius32@th20@@3MB')

def verify(object_file:Path):
 img,_=pe.verified_target();base,secs=pe.parse_sections(img)
 original=pe.raw_at(img,base,secs,HEAD,8)
 assert original==struct.pack('<2f',16.0,32.0)
 lines=subprocess.check_output(['objdump','-t',str(object_file)],text=True).splitlines()
 matches=[]
 for sym in SYMS:
  rows=[line for line in lines if line.endswith(' '+sym)]
  assert len(rows)==1,(sym,rows)
  x=re.search(r'\(sec\s+(\d+)\).*?\) (0x[0-9a-fA-F]+) ',rows[0]);assert x,rows[0]
  matches.append((int(x[1]),int(x[2],16)))
 assert matches[0][0]==matches[1][0] and [x[1] for x in matches]==[0,4],matches
 raw=object_file.read_bytes();offset=20+40*(matches[0][0]-1)
 name=raw[offset:offset+8].rstrip(b'\x00')
 assert name==b'.rdata',name
 length=struct.unpack_from('<I',raw,offset+16)[0]
 data_start=struct.unpack_from('<I',raw,offset+20)[0]
 assert length>=8
 candidate=raw[data_start:data_start+8]
 assert candidate==original,(candidate.hex(),original.hex())
 print(f'PASS original exact whole 8/8B .rdata 16.0f/32.0f at game {HEAD:#010x} from fresh COFF {object_file}')
 print('PASS two real extern source symbols +0/+4 in single native section; ZERO executable .text byte credit')

if __name__=='__main__':
 p=argparse.ArgumentParser(description=__doc__)
 p.add_argument('--object',type=Path,default=Path('build/core890-probe/AnimationPolygonWidths8.obj'))
 args=p.parse_args();verify(args.object)
