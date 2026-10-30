# CORE/RECON-864/865 — complete 1,001B rotated-ring and 1,116B two-point Bosses strict exact

The target is the locked Japanese TH20 v1.00a Steamless original PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
These are **two distinct whole game-authored renderers**, not a duplicated
leaf, a selected original prefix, or an independently still-NONEXACT
5,993B Animation Draw enclosing dispatcher.

| Strict original property | Rotated dual-radius ring | Two-endpoint LINESTRIP |
| --- | --- | --- |
| Genuine original code head | `0x0043C780` | `0x0043CD40` |
| Complete `.text` body | **1,001B /258 i386** | **1,116B /282 i386** |
| Native stack frame and return | `sub esp,0x58` / `ret 0x24` | `sub esp,0x3C` / `ret 0x20` |
| Original direct E8 call physical sites/target heads | **15/15 exact** | **10/10 exact** |
| Original PE HIGHLOW physical fields/target identities | **13/13 exact** | **13/13 exact** |
| Original nonrelocation bytes | **889/889 identical** | **1,024/1,024 identical** |
| Full independently relocated strict canonical body | **1,001/1,001 exact** | **1,116/1,116 exact** |
| Native D3D9 submission | `D3DPT_TRIANGLESTRIP=5`, `2*count` | `D3DPT_LINESTRIP=3`, one segment |

## Original-only native x86 provenance

[`scripts/verify-animation-shape-rotatedring1001-native.py`](../scripts/verify-animation-shape-rotatedring1001-native.py)
decodes all 258 immutable original x86 instructions and freezes the
**15 E8 physical site/target identities, 13 PE HIGHLOW physical
site/target identities**, original 0x58 frame, return and native D3D
primitive arguments without consulting compiled C++. Three actual E8
calls to this source method occur in the independently disassembled
5,993B main Draw dispatcher at `0x0044483A`, `0x00444927` and
`0x00444A18`. Original call roles include genuine `Vector3` local
default construction `0x00422E10`, **two cosine and two sine calls**,
**two XY rotation calls**, one `add_angles` and the real Animation/
Graphics/D3D interface and cookie roles. The native 13 HIGHLOW
fields target one security cookie, one pi, five 2.0f, two 1.0f and
four live Graphics global references.

[`scripts/verify-animation-shape-twopoint1116-native.py`](../scripts/verify-animation-shape-twopoint1116-native.py)
reads the complete original 1,116B independently, disassembles all
282 real native x86 heads and original `ret 0x20`, enumerates **ten
true E8 site/target pairs and 13 actual PE HIGHLOW field/target
pairs**, and authenticates the original `0x00443DFB` E8 caller in
the main 5,993B Draw parent. Its two calls to the separately exact
78B `animation_shape_xy` are physically real, as are the original
sine/cosine imports, depth-state calls, device access and security
cookie checker. Original data fields include two 128-bit sign-bit
XOR masks at `0x0056D7D0`, two `0.5f` fields at `0x0056E0EC`,
**five genuine 1.0f fields** at `0x0056C8CC`, three actual Graphics
globals at `0x005C4D40` and the original cookie `0x005B25C0`.
Neither set of native sites is inferred by solving candidate code bytes.

## Native source behavior restored

The ordinary source
[`src/AnimationShapeRotatedRing1001.cpp`](../src/AnimationShapeRotatedRing1001.cpp)
operates directly on the pre-existing **65,536×20B fixed vertex pool**
and genuine renderer cursor. After its real unsigned buffer-end guard
and segment-count threshold, the source flushes the draw pool and
constructs one actual `Vector3` local with the original native
constructor. Each of the `count+1` angular steps generates an inner
and outer 20B vertex: its unrotated XY components use *independent*
width/height minus/plus half-thickness values multiplied by original
cosine/sine of the current angle, then calls the genuine `rotate_xy`
helper with the specified shape rotation. Both vertices retain their
original world XY/renderer XY additions, Z=0, reciprocal-W=1 and
packed inner/outer diffuse colors. The angular step is real
`2*pi/count`; the native Graphics pipeline sets state 23/value 8,
selects the original draw color mode and FVF `0x44`, then submits
`DrawPrimitiveUP(TRIANGLESTRIP,2*count,buffer,20)` and advances the
cursor by `2*count+2` records. It is distinct from a simple circular
ring drawn with a single `polar2` per vertex.

The natural source
[`src/AnimationShapeTwoPoint1116.cpp`](../src/AnimationShapeTwoPoint1116.cpp)
also uses the original fixed 20B vertex pool, but reserves **two**
records and reads the original x-position anchors through two
`float[2]` arrays. Three anchor states place the two endpoints at
`[-width/2,+width/2]`, `[0,width]` or `[-width,0]`, then call the
already strict native 78B XY rotation/translation helper twice with
the actual sine/cosine and real `y=0` source coordinates.
It sets only the two submitted vertices' Z and renderer XY positions,
while also writing **five** actual reciprocal-W=1 slots, for records
`[4],[3],[2],[1],[0]` in the original instruction order. This is
surprising for a two-vertex draw, but it is an independently observed
original side effect and is **not silently fixed or removed**. The
original then applies two packed colors, Graphics depth-disable,
FVF `0x44`, color mode2 and the genuine
`DrawPrimitiveUP(LINESTRIP,1,buffer,20)`, incrementing the live cursor
by two and the renderer draw count.

All source constructs are real meaningful game operations; there are
no inert padding locals, copied original native bytes, artificial NOPs
or mismatched `D3DPRIMITIVETYPE` values. Both ordinary source functions
use the pinned MSVC 19.44.35211 x86 C++20
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
compiler profile with the original exact stack/return contracts.

## Independent whole strict replay and bounded regression

Two canonical full-function units in
[`config/match-units.toml`](../config/match-units.toml) own separate
fresh pinned objects/receipts. The 1,001B unit specifies the actual
**15 REL32 +13 DIR32** original symbols/types/offsets/destinations;
the 1,116B unit specifies **10 REL32 +13 DIR32**. Their full fresh
original PE relocated whole code comparisons report:

```text
animation_shape_rotatedring_1001: exact (1001/1001 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_shape_twopoint_1116: exact (1116/1116 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Both original game methods return zero through EAX; their old
provisional `void` signatures in shared
`AnimationDrawDetailedOwner.hpp` have been corrected to
`std::int32_t`. Previously accepted sources with that shared header
are cold-recompiled and strictly replayed **only in the affected
source include closures**. The 5,993B parent is checked with its
focused original-native call/switch verifier and remains **NONEXACT**.
No unfiltered whole-graph cold replay is run.

These two complete original authored functions add **2 physically
unique code heads /2,117 true game `.text` bytes** without duplicating
accepted game/math/library subfunctions or the parent. Live tracking
becomes **619 whole original game-authored exact functions /225,453
native bytes**, **1,265 source-present mappings /1,266 strict
canonical units /284 pinned exact object/receipt providers**. Full
game linkage/playability remains an independent open task.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-rotatedring1001-native.py
scripts/repo-python scripts/verify-animation-shape-twopoint1116-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeRotatedRing1001.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeTwoPoint1116.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
