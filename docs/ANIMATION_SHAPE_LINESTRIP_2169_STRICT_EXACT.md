# CORE/RECON-856 — whole original 2,169B closed line-strip rectangle Boss strict exact

The locked Japanese TH20 v1.00a Steamless executable has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its entire game-authored closed outline renderer at **`0x0043B0E0`** is a
**2,169B /533-real-i386** function with an original `sub esp,0x68` stack,
`ret 0x24`, and nine stack arguments beside its renderer ECX receiver.
The **5,993B** main Animation Draw dispatcher calls the physical function
at genuine original E8 `0x00443F23`, and is independently **NONEXACT**.

One natural typed method in
[`src/AnimationShapeLineStrip2169.cpp`](../src/AnimationShapeLineStrip2169.cpp)
now compiles under pinned x86 MSVC C++20 to a **full 2,169/2,169B strict
canonical zero-difference original native match**. This includes exactly
**533/533 original x86 instructions**, **12/12 genuine direct E8**
physical call sites and native destinations, **17/17 true original PE
HIGHLOW** data field positions and absolute target values, and all
**2,053/2,053 non-relocation bytes** identical. It is a complete renderer
Boss, not a copied assembly block or shortened code region.

## Independent original-native physical provenance

[`scripts/verify-animation-shape-linestrip2169-native.py`](../scripts/verify-animation-shape-linestrip2169-native.py)
reads the immutable original PE `.text`, decodes all 533 instructions
through the real return, and inspects the independent native `.reloc`
directory. It asserts the original 12 E8 site/destination pairs and all
17 original HIGHLOW physical offsets/targets before consulting any new
candidate object. The native roles comprise:

| Original physical role | Original count | Strictly verified |
| --- | ---: | --- |
| Game pool flush, sine/cosine, four real 78B XY transforms, depth disable, render color mode, two Graphics device getters, compiler cookie | 12 real E8 | **12/12 native physical site/target pairs exact** |
| Native four-lane 128-bit floating sign-XOR mask at `0x0056D7D0` | 4 HIGHLOW | **4/4 site and immutable data destinations** |
| Original `0.5f` at `0x0056E0EC` | 4 HIGHLOW | **4/4** |
| Original `1.0f` at `0x0056C8CC` | 5 HIGHLOW | **5/5** |
| Genuine Graphics owner `0x005C4D40` | 3 HIGHLOW | **3/3** |
| Compiler security cookie `0x005B25C0` | 1 HIGHLOW | **1/1** |
| Complete original function body | 2,169B /533 x86 | **2,169/2,169B strict, zero differences** |

The original native D3D9 vtable call explicitly pushes **type 3** and
**four primitives**, the documented `D3DPT_LINESTRIP` protocol, with
actual 20B source stride. It is **not** D3DPT_TRIANGLEFAN (type 6).
This is a material gameplay/visual rendering distinction, not merely a
compiler-size adjustment. The original uses a 20B vertex record, and
consumes **five vertices**, producing four connected line segments.

## Original vertex ownership and sibling hypotheses corrected

The established exact [1,980B filled rectangle](ANIMATION_SHAPE_RECT_1980_STRICT_EXACT.md)
shares much of its real code with this native outline function, but the
actual original differences are important:

1. The source checks space for **five**, not four, `SpriteColoredVertex`
   objects in the genuine receiver-owned **65,536 ×20B** vertex pool.
   The original native guard computes `20*5` through
   `MOV EAX,0x14; IMUL ECX,EAX,5` and compares against the fixed
   one-past-end address using unsigned `JB`. Leaving sibling's four
   vertex guard produced a distinct `SHL EAX,2` and incorrect occupancy.
2. Its four source XY vertices are emitted in a different corner order:
   real vertex 3 receives bottom-left, vertex 2 bottom-right. The fifth
   vertex **copies original vertex 0's XYZ** to close the outline, before
   all five real Z=0, reciprocal-W=1, per-vertex XY renderer offsets
   and packed color assignments.
3. The original has two real four-float stack arrays for X/Y anchors,
   three modes per dimension, six actually reused sign/half scalar
   results, and a 128-bit sign-mask XOR. This is genuine source geometry
   data, not speculative `Ghidra` locals or arbitrary compiler padding.
4. The real D3D9 submission is `DrawPrimitiveUP(D3DPT_LINESTRIP,4,
   vertices,20)` with FVF `0x44`. The initial draft used a triangle fan
   (type 6), giving an otherwise machine-identical **2,169B/533-x86**
   candidate with **12/12 exact E8, 17/17 exact DIR32 locations**, but
   one incorrect non-relocation immediate at original offset `+0x835`.
   Source correction to the real **line strip** produces the original
   `PUSH 3`, all **2,053/2,053 nonrelocation bytes**, and complete
   2,169B canonical equality.
5. The game renderer advances its live vertex cursor by exactly
   **5 ×20B** and increments the actual renderer draw counter. The
   enclosing real main Draw caller at `0x00443F23` is independent native
   evidence for the shape's game-authored role; it earns **no parent code
   credit** from this new method's exactness.

The natural source relies on the already strict physical 78B authored
[`animation_shape_xy`](ANIMATION_SHAPE_XY78_STRICT_EXACT.md) as four
separate E8 callees. No second body for the 78B method is created or
counted, and no static vertex pool is allocated anew in this source.

## Canonical unit, shared header ABI and strictly scoped replay

The only newly authored canonical unit is
`animation_shape_linestrip_2169` in
[`config/match-units.toml`](../config/match-units.toml), with
one pinned `build/core856-canonical/AnimationShapeLineStrip2169.obj`
source object and matching compiler receipt. Its **29 actual relocation
roles** are independently specified original 12 E8 REL32 and 17 real
PE HIGHLOW/DIR32 data fields; none is inferred by solving original
compared bytes. Complete original replay:

```text
animation_shape_linestrip_2169: exact (2169/2169 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The original method returns zero in EAX and `ret 0x24`, so the shared
`AnimationDrawDetailedOwner.hpp` method ABI was corrected from a
provisional `void` to `std::int32_t`. Since that header is included by
previously accepted sources, **each affected exact source provider** is
cold-recompiled and strictly replayed in scope. The full 5,993B Draw
main parent is also checked separately with its original source-role
verifier; it remains **NONEXACT**, not miscredited from the now-exact
children. No unfiltered whole-graph cold replay was run.

Only one original whole game function is newly credited, with
**2,169 disjoint `.text` bytes**, not its 1,980B rectangle sibling,
78B geometry callee, compiler cookie, or the main draw dispatcher:

| Live game progress | Before | After |
| --- | ---: | ---: |
| Whole original game-authored strict exact functions | 609 | **610** |
| Disjoint game original `.text` bytes | 215,119 | **217,288** |
| Source-present original physical mappings | 1,255 | **1,256** |
| Canonical strict units | 1,256 | **1,257** |
| Distinct pinned compiler source-object/receipts | 274 | **275** |

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-linestrip2169-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeLineStrip2169.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/progress.py --check
```
