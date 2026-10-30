# CORE/RECON-857 — complete original 1,601B game triangle Boss native strict exact

The immutable original Japanese TH20 v1.00a Steamless executable has
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The genuine original `0x0043E2C0` is an **entire 1,601B /394 real x86**
game-owned three-vertex triangle renderer, not a truncated loop. Its
native stack is `sub esp,0x50`; the real method returns zero through
EAX and `ret 0x24` after nine stack arguments. The separate 5,993B
Animation main Draw dispatcher actually calls this original head at
physical E8 `0x004445F3`. The enclosing dispatcher remains **NONEXACT**.

One ordinary source function
[`src/AnimationShapeTriangle1601.cpp`](../src/AnimationShapeTriangle1601.cpp)
now compiles under the pinned C++20 i386 MSVC `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` into the **entire 1,601B/394 real
native instructions with zero nonrelocation differences**. All **11
actual E8 call physical offsets/targets and 19 actual PE HIGHLOW
absolute-reference offsets/target values** are equal to the immutable
original; the complete strict canonical relocated comparison is
**1,601/1,601B exact**.

## Source-independent immutable PE proof

[`scripts/verify-animation-shape-triangle1601-native.py`](../scripts/verify-animation-shape-triangle1601-native.py)
reads the locked original PE `.text`, disassembles all 394 true i386
instruction heads including native `ret 0x24`, and reads the original
`.reloc` directory rather than candidate C++ values. The original
relocation census is independently attested:

| Physical original role | Exact source/native coverage |
| --- | --- |
| 11 native E8 site/target pairs | **11/11**: original draw flush, sine/cosine, three already-exact 78B XY transform calls, Graphics depth/color state and device, security cookie |
| Five 128-bit floating sign-XOR masks at `0x0056D7D0` | **5/5 real HIGHLOW site and source sign-mask roles** |
| Original `3.0f` at `0x0056C8D8` | **2/2 physical HIGHLOW** |
| Original `2.0f` at `0x0056C8D0` | **3/3 physical HIGHLOW** |
| Original `0.5f` at `0x0056E0EC` | **2/2 physical HIGHLOW** |
| Original `1.0f` at `0x0056C8CC` | **3/3 physical HIGHLOW** |
| True Graphics owner at `0x005C4D40` | **3/3 physical HIGHLOW** |
| Actual compiler security cookie `0x005B25C0` | **1/1 physical HIGHLOW** |
| Entire original x86 body | **1,601/1,601B strict**, **394/394 instruction heads**, **1,481/1,481 nonrelocation bytes** |

The original parent Draw dispatcher has one independently native E8
at `0x004445F3` to this actual 1,601B function. This is direct
original game-owned parent/child provenance, not inferred from
similar-looking decompiler names.

## Distinct actual triangle geometry and native codegen

The complete game renderer checks its real fixed **65,536×20B**
`SpriteColoredVertex` storage. Its original unsigned `JB` bound uses
`MOV EAX,0x14; IMUL ECX,EAX,3` to reserve **three** vertices, and the
live source cursor belongs to the existing renderer at
`this+0x7D40E80`. The local x and y anchor arrays each have **three
real float slots**, not the four of the already strict rectangle and
closed line-strip Bosses. The native source supports three anchor
positions in each dimension:

- Horizontal centered: `x[0]=x[2]=-width/3`, `x[1]=(width*2)/3`;
  alternate from-zero: `x[0]=x[2]=0`, `x[1]=width`; alternate negative:
  `x[0]=x[2]=-width`, `x[1]=0`.
- Vertical centered: `y[0]=-height/2`, `y[1]=0`, `y[2]=height/2`;
  alternate from-zero: `y[0]=0`, `y[1]=height/2`, `y[2]=height`;
  alternate negative: `y[0]=-height`, `y[1]=-height/2`, `y[2]=0`.

The SSE operation order matters: the positive horizontal centered arm
uses **multiply by original 2.0f, then divide by original 3.0f**,
not `width*(2/3)`; the negative expression uses the original 128-bit
sign-XOR mask before division. Some vertical branches intentionally
recompute a signed negative for a second slot rather than reuse a
cached float. The source follows those real native lifetimes and
preserves each site of the original 19 HIGHLOW references.

The native calls the separately strict 78B authored
[`animation_shape_xy`](ANIMATION_SHAPE_XY78_STRICT_EXACT.md) three times,
in original vertex order, writes Z=0 and reciprocal-W=1, adds the actual
renderer XY offsets at `+0xD0/+0xD4`, and assigns original two packed
colors. It then applies native Graphics depth/color state and FVF
`0x44`, and calls D3D9
`DrawPrimitiveUP(D3DPT_TRIANGLESTRIP=5,1,vertices,0x14)`: **one
real filled triangle**, not the sibling LineStrip's four connected
edges. The live cursor advances by exactly three 20B vertices and the
original draw counter increments.

This recovered complete native body is genuinely different from the
preceding whole strict 1,980B rectangle and 2,169B closed line-strip,
although all three share the already exact 78B original XY transform.
Neither their code bytes nor their related D3D9 geometry are counted
twice by this independent triangle result.

## Whole strict canonical source acceptance and focused header regression

One new `animation_shape_triangle_1601` unit in
[`config/match-units.toml`](../config/match-units.toml) owns its genuine
`build/core857-canonical/AnimationShapeTriangle1601.obj` compiler
object/receipt. The manifest has exactly **11 real REL32 E8** and **19
real DIR32/HIGHLOW** relocations. Their source symbol, field offset,
actual original destination and relocation type are independently
attested from the original PE and genuine known owner addresses.

```text
animation_shape_triangle_1601: exact (1601/1601 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The shared `AnimationDrawDetailedOwner.hpp` provisional `void`
signature for `draw_shape_43e2c0` changed to the original
`std::int32_t` return ABI, supported by original EAX/RET bytes. Every
previously accepted dependent C++ source/provider must be checked with
**source-scoped** pinned cold replay. The still nonexact original main
5,993B Draw is separately checked by its focused source-role verifier.
No all-graph cold replay or artificially padded source is used.

This checkpoint credits **one new original game-authored function and
1,601 distinct game `.text` bytes**. The live totals are **611 original
whole-game strict functions /218,889 native bytes**, **1,257
source-present mappings /1,258 canonical strict units /276 accepted
compiler source-object/receipt providers**. Game linkage and the
5,993B enclosing Draw parent remain open.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-triangle1601-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeTriangle1601.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
