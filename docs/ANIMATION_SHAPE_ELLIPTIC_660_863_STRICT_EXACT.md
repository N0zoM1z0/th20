# CORE/RECON-867/868 — complete original 660B ellipse outline and 863B filled ellipse fan strictly exact

The locked Japanese TH20 v1.00a Steamless original executable has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two distinct original game-authored Animation renderer functions now have
real C++ sources yielding *complete original whole-native strict exactness*.
They are not aliases for one another, and their enclosing 5,993B main Draw
parent at `0x00443880` remains independently **NONEXACT**.

| Original physical evidence | Elliptic outline | Elliptic filled fan |
| --- | --- | --- |
| Physical original function head | `0x0043C4E0` | `0x0043C180` |
| Entire original `.text` size | **660 bytes** | **863 bytes** |
| Independently decoded original i386 instructions | **178** | **226** |
| Native frame and return | `sub esp,0x40`, `ret 0x20` | `sub esp,0x40`, `ret 0x20` |
| Genuine original E8 instruction sites and destinations | **12/12** | **12/12** |
| Genuine PE HIGHLOW physical field sites and targets | **8/8** | **9/9** |
| Whole non-relocation code bytes equal | **580/580** | **779/779** |
| Complete original relocated strict code | **660/660 exact** | **863/863 exact** |
| Native D3D9 primitive | `LINESTRIP = 3` | `TRIANGLEFAN = 6` |

## Immutable original PE-only proof

[`scripts/verify-animation-shape-elliptic660-863-native.py`](../scripts/verify-animation-shape-elliptic660-863-native.py)
reads the entire immutable original `.text` extents and original PE
`.reloc` rather than using COFF candidate positions as original evidence.
It disassembles both whole functions through their real returns, checks
**all 24 real E8 instruction sites and their absolute original callee
heads**, **all 17 PE HIGHLOW field sites and real global targets**, and
verifies the corresponding original whole main Draw parent callers:

- At `0x00444799`, main Draw calls the actual 660B ellipse outline.
- At `0x00444703`, main Draw calls the actual 863B ellipse fan.

Both original methods independently call the game Animation draw flush,
actual `Vector3` default constructor `0x00422E10`, scalar cosine
`0x004397C0`, scalar sine `0x00439820`, genuine `rotate_xy`
`0x00458FA0` and `add_angles` `0x00438600`, Graphics depth-disable
`0x004DDF80`, Graphics state forwarding `0x004D9DB0`, renderer color
selection `0x00446690`, two original D3D9 device getters `0x00412730`,
and the real compiler cookie checker `0x005429EE`.

Native PE HIGHLOW references are independently fixed: compiler security
cookie `0x005B25C0`, original pi `0x0056E0F0`, float two
`0x0056C8D0`, the original float one `0x0056C8CC` (once in outline,
twice in fan), and four native Graphics global references
`0x005C4D40` in each function. No callee address is guessed from
candidate source relocation bytes.

## Recovered original gameplay semantics and compiler ordering

The natural C++ sources are
[`src/AnimationShapeEllipticLine660.cpp`](../src/AnimationShapeEllipticLine660.cpp)
and [`src/AnimationShapeEllipticFan863.cpp`](../src/AnimationShapeEllipticFan863.cpp).
Both operate on the real renderer-owned **65,536×20B** fixed
`SpriteColoredVertex` pool with the original mutable write cursor,
segment-count guard and `2*pi/count` angle step. For each outer point,
the source computes original `radius_x*cos(angle)` and
`radius_y*sin(angle)` into a real local `Vector3`, rotates its XY with
the user rotation, applies world and renderer XY offsets, Z=0,
reciprocal W=1 and native diffuse color, then advances the genuine
source cursor and accumulates the angle. Both apply real Graphics
depth state, `SetRenderState(23,8)`, renderer color mode2, and
D3D9 FVF `0x44`, then update the actual draw cursor and count.

The **660B outline** has no center vertex. Its final D3D9
`DrawPrimitiveUP` uses **LINESTRIP type3** with `segment_count`
primitives; its cursor advances by `segment_count+1` records.

The **863B filled fan** creates one *additional indexed center vertex
`current[0]`* with its own center packed color and native XY/Z/W
stores. It then constructs the local `Vector3` **before incrementing
the live current vertex pointer** and entering the perimeter loop. This
order is visible in the original PE: `Vector3::Vector3` E8 at
`+0x132`, followed by the pointer advance at `+0x137`.
An initially plausible source advanced the pointer before constructing
`Vector3`; the candidate still had **863B/226 i386** and all data
field offsets, but its constructor E8 was shifted by nine bytes and
13 nonrelocation bytes differed. Expressing the true original order
naturally restores **all 12 E8 offsets and all 779/779 nonrelocation
bytes** without dummy locals, manual native bytes or artificial padding.
The fan finally issues `DrawPrimitiveUP(TRIANGLEFAN=6,segment_count,
vertices,20)` and advances the cursor by `segment_count+2` vertices.

## Strict pinned compiler acceptance, changed-source scope, original credit

Two separate canonical full-function units in
[`config/match-units.toml`](../config/match-units.toml) compile with pinned
MSVC i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
Each receives a fresh object/receipt and all independently attested
original symbol/type/physical offset/destination relocation roles:
**12 E8 REL32 +8 DIR32** for the outline and **12 E8 REL32 +9 DIR32**
for the fan. The complete fresh relocated native compare reports:

```text
animation_shape_ellipticline_660: exact (660/660 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_shape_ellipticfan_863: exact (863/863 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The provisional renderer declaration return types were corrected from
`void` to the genuine original integer-zero `ret 0x20` ABI. Previous
accepted source providers that include the modified
`AnimationDrawDetailedOwner.hpp` must be cold-rebuilt and strictly
replayed **only as affected source units**. The still-NONEXACT 5,993B
Draw parent has a focused original-native call/switch role regression;
it earns no exact game byte credit from its now-exact children.
**No unfiltered whole-graph cold replay** is needed.

This adds **two unique original authored game functions, 1,523 distinct
original `.text` bytes**. Live tracking after acceptance is **622 exact
original game functions /227,875 native game code bytes**, **1,268
source-present mappings /1,269 strict canonical units /287 accepted
pinned compiler object/receipt providers**. Library/CRT, already exact
Graphics/geometry helpers, and the nonexact main Draw body receive no
duplicate credit.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-elliptic660-863-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeEllipticLine660.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeEllipticFan863.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
