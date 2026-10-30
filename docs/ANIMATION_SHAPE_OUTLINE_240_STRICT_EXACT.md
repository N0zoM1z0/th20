# CORE/RECON-858 — whole native 240B game outline-rectangle wrapper strictly exact

The immutable Japanese TH20 v1.00a Steamless executable is locked by
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original native whole 240B/76-i386 method at **`0x0043A1C0`** is a
real game-owned outlined-rectangle draw wrapper using ECX renderer,
nine actual stack parameters, native `sub esp,0xC` and `ret 0x24`.
It is called at two genuine E8 sites in the larger, independently
**NONEXACT** 5,993B Animation main Draw dispatcher:
`0x00444029` and `0x004440B8`.

The ordinary maintained C++ source
[`src/AnimationShapeOutline240.cpp`](../src/AnimationShapeOutline240.cpp)
now emits **240/240 identical relocated original code bytes** under
pinned i386 MSVC C++20, **76/76 authentic x86 instructions** and all
**224/224 non-relocation bytes**. No copied original assembly, alternate
profile or shorter comparison extent is used.

## Actual original game behavior and independent original PE evidence

The independent
[`scripts/verify-animation-shape-outline240-native.py`](../scripts/verify-animation-shape-outline240-native.py)
reads the locked original PE executable `.text` and actual PE `.reloc`
records before using any new source object. It confirms exactly two
true E8 calls at native `+0x94` and `+0xE3`, each to the **whole
already strict exact 1,980B game rectangle** at `0x00439A00`, and
exactly two genuine HIGHLOW float-owner fields at `+0x5E/+0x71`, each
referring to actual `1.0f` at `0x0056C8CC`. The verifier also checks
the native two external callers in the 5,993B original Draw dispatcher.

For each of two packed 32-bit source RGBA colors, the original first
performs an actual integer `AND 0x00FFFFFF` to preserve the RGB bits,
then **`SHR 24; SHR 1; SHL 24`** to halve its 8-bit alpha with
truncation and restore the alpha byte position, finally ORing the
RGB and alpha. This original multi-step shift behavior is not
assumed to be interchangeable with a single right shift at source
level because `/Od` emits different i386 for other source forms.

The method first calls the 1,980B rectangle with native
`(x,y,width+1.0f,height+1.0f,angle,halfAlphaColorA,halfAlphaColorB,
anchorX,anchorY)`, then invokes the **same genuine rectangle** with
the original width/height and unmodified colors, returning zero in
EAX. This is an actual *double-pass* outline effect, not an additional
rectangle implementation or an inferred texture primitive.

## Scoped whole canonical acceptance and disjoint code credit

The one new canonical `animation_shape_outline_240` match unit in
[`config/match-units.toml`](../config/match-units.toml) compiles only
`src/AnimationShapeOutline240.cpp` with the pinned original i386
MSVC profile `/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`. Exactly **two actual REL32 E8
and two genuine PE HIGHLOW/DIR32** relocation roles are independently
specified. The full fresh compiler receipt/native replay proves:

```text
animation_shape_outline_240: exact (240/240 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The shared provisional `draw_shape_43a1c0` signature was corrected to
the real int-returning native ABI. Affected previously accepted
header-consumer source objects are replayed in scope, not blindly
assumed compatible; the 5,993B main parent has its own focused
noncanonical native role verifier. No full cold graph replay ran.

This newly credits **one exact original authored 240B function only**.
Neither its two already exact 1,980B rectangle calls nor the larger
5,993B main Draw parent earns duplicate byte credit. The companion
whole 1,174B rounded-fan Boss is independently accepted in the same
checkpoint; see
[CORE/RECON-859](ANIMATION_SHAPE_ROUNDEDFAN_1174_STRICT_EXACT.md).

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-outline240-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeOutline240.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
