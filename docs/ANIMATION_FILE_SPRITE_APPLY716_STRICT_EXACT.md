# AnimationFile SpriteData application: whole-native 716B exact reconstruction

The original **716B/179-i386** function at `0x00438620` applies one real
`SpriteData` record from an `AnimationFile` to an `Animation`. The complete
original body SHA-256 is
`588b789deec72290b8fd75c577751531b00f231ad30f890a8d8c032ca69bf860`.

The natural source is `src/AnimationFileSpriteApply.cpp`. It uses a zero-data
`NativeAnimationFileSpriteApplyView : AnimationFile` ABI view, with a compile-time
size equality assertion. The inherited AnimationFile base is at offset zero;
no data member, object layout, byte buffer, or SpriteData layout is changed.
The function preserves the original `__thiscall` receiver and its two explicit
arguments (`Animation*`, sprite index).

## Recovered behavior

- A null loaded-file byte buffer returns `-1` before touching the destination.
- The requested sprite index is written to `AnimationBase+0x20`, then the
  existing exact `AnimationFile::sprite` accessor retrieves the 0x58B record.
- Four Vector2 corners at `AnimationBase+0x378..+0x394` receive the original
  UV arrangement: `(u0,v0)`, `(u1,v0)`, `(u0,v1)`, `(u1,v1)`.
- Width and height at `+0x398/+0x39C` are `u1-u0` and `v1-v0`.
- `vector_70` receives the sprite extents; the two identity matrices are copied
  from the original `identity_matrix` at `0x0056E068`.
- The first matrix's diagonal is scaled by the original `native_256` constant
  (`256.0f`, `0x0056CDA0`); the second matrix uses the sprite's extent and
  scale fields. The first matrix is copied to `Animation+0x57C`.
- The original left/top/right/bottom sprite rectangle is converted to four
  signed integer fields at `AnimationBase+0x3A8..+0x3B4`.

## Whole-function proof

The independent verifier
`scripts/verify-animation-file-sprite-apply716-native.py` pins the complete
original SHA and decoded extent, `ret 8`, the sole E8 call at `+0x2C` to the
already exact `AnimationFile::sprite` accessor at `0x00437C80`, and all four
physical PE HIGHLOW fields. It also verifies the original 256.0f constant and
identity matrix data.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS- /Gy /Zl /arch:SSE2 /fp:precise` emits the
complete **716B** contribution. All **696/696** ordinary bytes match and all
five relocations match in position, type and destination: one SpriteData
accessor REL32, two identity-matrix DIR32 fields and two `native_256` DIR32
fields. The function is admitted as a whole strict exact unit; no prefix or
relocation-masked partial credit is used.

This is a game-specific resource-to-Animation operation, not a generic
compiler template. Its VM caller at `0x0042B5D0` and two other original callers
remain independent; this leaf's exactness does not grant any byte credit to
the 39,470B Animation VM parent.
