# CORE/RECON-878 — exact original 96B corner-axis data; whole 1,486B rotated-corner Boss source, still NONEXACT

The target is the immutable Japanese TH20 v1.00a Steamless PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This work follows the separately accepted
[whole 985B four-corner projector and two 455B vertex methods](ANIMATION_CORNER_PROJECTION_985_VERTEX_DRAW_455_STRICT_EXACT.md),
whose genuine 96B quad corner anchor table previously had only a
correctly typed external declaration. It now has a **real compiled
original-byte exact source data definition**. A second sibling original
**1,486B/372-i386 rotated corner Boss** also has one maintained complete
semantic source, but its unmodified C++ still emits only **1,485B/371
instructions**, so the parent explicitly remains **NONEXACT**.

## New source-owned data: complete real original `.rdata` 96/96 bytes

[`src/AnimationCornerAxisTable.cpp`](../src/AnimationCornerAxisTable.cpp)
defines the actual external symbol
`th20::native_quad_axis_layout[2]` of type `NativeQuadAxisLayout`, a
struct containing **three groups of four floats per axis**. Its
2 ×48B source records, not a copied byte blob, have exactly the
original game values:

| Source axis/mode | Original real four-float corners |
| --- | --- |
| X centered | `-0.5, 0.5, -0.5, 0.5` |
| X positive | `0, 1, 0, 1` |
| X negative | `-1, 0, -1, 0` |
| Y centered | `-0.5, -0.5, 0.5, 0.5` |
| Y positive | `0, 0, 1, 1` |
| Y negative | `-1, -1, 0, 0` |

The independently locked PE has 96 file-backed bytes at original
address **`0x0056E140`**, SHA-256
`8621c0a23993a5becd293c6d5a8653fa9a65184e716027098d635e3096f5968b`.
The pinned i386 MSVC C++20 ordinary source compiler emits one actual
externally linked symbol
`?native_quad_axis_layout@th20@@3QBUNativeQuadAxisLayout@1@B`
in `.rdata` at offset zero with **exactly 96/96 identical original
bytes**, including IEEE-754 signed and zero bits. The independent
[`scripts/verify-animation-corner-axis96-rotated1486-native.py`](../scripts/verify-animation-corner-axis96-rotated1486-native.py)
reads the original PE and the actual COFF `.rdata` symbol bytes,
compares the complete region byte-for-byte, verifies the original
hash, and attests both original physical PE HIGHLOW references to this
same source owner in **each** of the 985B and 1,486B game methods.
This is actual original game *data* recovered, **not 96 additional
`.text` bytes and not a fabricated strict native function/unit**.

## Whole original 1,486B game rotational-corner parent and native gap

The separately maintained
[`src/AnimationCornerRotated1486.cpp`](../src/AnimationCornerRotated1486.cpp)
implements an entire native game-owned quad transformation under one
provisional receiver class shared with the accepted 985B method in
[`src/AnimationCornerProjectionOwner.hpp`](../src/AnimationCornerProjectionOwner.hpp).
The original saves an unused ECX receiver, consumes five stack args
(**`Animation*` plus four `Vector3*` outputs**),
uses the real `0x54` local stack, and returns via `ret 0x14`.
The original game calls it at actual E8 `0x0043F678` in the independently
exact original 97B `AnimationDrawModeOwner::draw_quad_mode1`, and also
at `0x00445817` in a native 244B game function.

The original original PE has **1,486B/372 real x86 instructions**,
**13 genuine E8 physical site/target pairs** and **nine real PE HIGHLOW
physical site/target pairs**. All are directly attested by the locked
binary, including the actual:

- `Animation::sprite_data` `0x00437CD0`, `rotation_sum` `0x00437770`,
  and `Angle::Angle(float)` `0x00429210`;
- Two actual `Angle::operator float` folded calls `0x004292E0`, real
  scalar sine `0x00439820`, cosine `0x004397C0`,
  `Animation::position(Vector3&)` `0x004376E0`;
- **Four original distinct 78B `animation_shape_xy` calls** to
  `0x00445AD0`, and compiler security checker `0x005429EE`;
- One original cookie at `0x005B25C0`, two original table fields
  at `0x0056E140`, four actual `window_state.scale` references at
  `0x005B8818`, and two authentic 0.5f fields at `0x0056E0EC`.

The complete natural source preserves original SpriteData offsets,
parent scale inheritance, original 16B source mode-indexed X/Y corner
tables and four precomputed XY coordinate arrays, the actual
`Angle` construction and float conversions through the native helper
ABI, four genuine same-original `animation_shape_xy` transformations,
and the output depth assignment. The fourth output is first used as
the real world-translation vector through
`animation->position(*d)`, and **then** overwritten by the fourth
XY transformation, as in the original machine code.

A pinned MSVC i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` source compilation produces **1,485B/371 x86**, the
correct original `sub esp,0x54`, **13 E8 and nine DIR32 relocations**
with the correct source-owner/target identity and original call
order. Its three early E8 fields match original physical offsets;
all later original call/data fields are **one byte later** than the
corresponding compiled candidate. The exact missing original opcode
is the **one native `NOP` at original function offset `+0x41` after
the `Angle(float)` constructor call**. The original binary does
contain it. Twelve legitimate source-level `Angle` initialization
forms (`auto`, `const`, copy/braced/direct, etc.) and three different
pinned compiler debug/float profiles were tried. All still emit
1,485B, and none faithfully emits the original post-constructor NOP.

The verifier also performs one **purely in-memory diagnostic**: it
models the missing original NOP in a disposable copy of the candidate
byte sequence, shifts the candidate relocation field offsets by one
for sites following it, and checks **1,398/1,398 original nonrelocation
bytes equal**. This proves the code body has converged semantically
up to the one source/ABI compiler marker; **it is not an accepted
comparison of the real unmodified candidate**. Neither the compiled
COFF object nor the original PE is modified or padded, no canonical
strict unit is created, and no original game code byte is credited
for this 1,486B function. The source's original class name remains
provisional because the ECX receiver's state is unused in this body.

## Scope and live exact inventory

The shared source definitions of `NativeQuadAxisLayout` and the
`NativeAnimationCornerProjector` receiver were moved to one native
header rather than maintaining conflicting class definitions in two
translation units. The already whole exact original 985B source is
therefore rebuilt by **only its own affected source-scoped canonical
replay**. The newly created `.rdata` source is independently compiled
and byte-verified; the new 1,486B candidate is compiled and validated
as NONEXACT and is not included in canonical exact replay. The
original 5,993B main Draw dispatcher remains source-present NONEXACT.
No full cold replay occurs.

This adds **one real 96B original data owner and one original 1,486B
SOURCE-PRESENT/NONEXACT game function**, not a new strict game body.
Live authored whole-native exact coverage remains **628 distinct
original functions /231,537 `.text` bytes**, with **1,275
source-present mappings /1,275 canonical strict units /293 pinned
exact original code object/receipt providers**. The new data source is
not counted as an additional strict *code* provider.

```bash
nice -n 15 scripts/compile-probe.sh src/AnimationCornerAxisTable.cpp build/core878-probe/AnimationCornerAxisTable.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
nice -n 15 scripts/compile-probe.sh src/AnimationCornerRotated1486.cpp build/core877-probe/AnimationCornerRotated1486-plain.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-animation-corner-axis96-rotated1486-native.py --data-object build/core878-probe/AnimationCornerAxisTable.obj --rotated-object build/core877-probe/AnimationCornerRotated1486-plain.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationCornerProjection985.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
