# CORE/RECON-884/885/886 — whole original 233B polygon Motion group Boss and two 23B/19B container leaves strictly exact

The locked original Japanese TH20 v1.00a Steamless executable is identified by
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Its polygon Motion group method at **`0x0045F9B0`** is now a complete
**233B/78-original-x86 game-owned whole-native strict exact Boss**.
Two distinct native array-member helpers, **23B/9 x86** and **19B/9 x86**, are
also fully source-recovered and strictly exact in the same translation unit.
Their likely C++ standard-library/template-instantiation ownership remains
**pending original symbol provenance**, so neither helper is credited
prematurely as hand-authored game code.

| Original physical source result | Polygon group Boss | Indexed segment helper | Segment-end helper |
| --- | --- | --- | --- |
| Native original head | `0x0045F9B0` | `0x0045F400` | `0x0045FD40` |
| Whole body and native x86 | **233B/78** | **23B/9** | **19B/9** |
| Original return | `ret` with EAX=0 | `ret 4`, pointer | `ret`, pointer |
| Actual native direct E8 site/target roles | **9/9** | **0** | **0** |
| Original PE HIGHLOW data fields/targets | **2/2** | **0** | **0** |
| Identical original nonrelocation bytes | **189/189** | **23/23** | **19/19** |
| Pinned whole strict relocated comparison | **233/233 exact** | **23/23 exact** | **19/19 exact** |
| Game-authored code credit | **233B** | **0B, origin pending** | **0B, origin pending** |

## Original PE-only x86 evidence and caller graph

[`scripts/verify-animation-polygon-motion-group233-native.py`](../scripts/verify-animation-polygon-motion-group233-native.py)
reads the immutable original `.text` and PE `.reloc` directly, before
consulting the compiled candidate C++. It confirms the three complete
method extents, their respective native stack/return ABI and **all nine
actual E8 physical call-site/absolute original destination pairs and
both original PE HIGHLOW field/absolute global targets** in the 233B
Boss. The original true `sub esp,0x30` frame/`ret` covers **all 78 x86
instructions**; the two actual globals are the compiler cookie
`0x005B25C0` and the genuine global AnimationPoolOwner* pointer
`0x005C0028`.

The nine native direct E8 calls in the group Boss are to the actual
whole-exact 2,725B Animation texture-state binder `0x00445BC0`,
original `Vector3` default constructor `0x00422E10`, whole-exact
`Animation::position` `0x004376E0`, original `Motion::position_ref`
`0x0040BDA0`, segment-array end helper `0x0045FD40`, **104B
polygon-outline caller `0x0045FAA0`**, indexed segment helper
`0x0045F400`, independently exact **76B polygon-fan caller
`0x0045FB10`**, and compiler cookie checker `0x005429EE`.
The 104B callee is **still SOURCE-PRESENT/NONEXACT**—the parent can
match its complete original native E8 target and code bytes without
claiming that every callee is also exact. See
[CORE/RECON-882/883](ANIMATION_POLYGON_MOTION_CALLERS_76_104_FRONTIER.md)
for the separate original wrapper verification.

## Native three-item layout, real source state and exact C++ lifetime

The genuine group receiver retains one original `Animation*` at `+0x04`,
a native three-element polygon segment array starting at `+0x08`,
a cached `Vector3` at **`+0xB9C`**, and a byte choosing live-versus-
cached position at **`+0xBA8`**. Each original segment record has
**stride `0x3D4`** (980 bytes), so three records occupy **`0xB7C`
bytes** and the array's one-past-end is at group offset `+0xB84`.
Other original bytes between `+0xB84` and `+0xB9C` have unresolved
roles; these are retained only as **genuine native record fields**
needed for accurate `offsetof` and `sizeof` assertions, not machine-
code padding or fabricated behavior.

The natural, maintained C++ source
[`src/AnimationPolygonMotionGroup233.cpp`](../src/AnimationPolygonMotionGroup233.cpp)
models that original object layout with explicit compile-time offset
checks. It first binds the current Animation texture state using the
real global `AnimationPoolOwner`, constructs a native `Vector3` local,
then chooses between copying the actual cached `+0xB9C` Vector3 and
calling `Animation::position` depending on the authentic `+0xBA8`
flag. Its first loop pointer is obtained through the **actual
`Motion::position_ref` E8** on the array's base, and its one-past-end
through the separate **19B original `end()`** helper. It traverses
exactly three **`0x3D4`-stride** records, calling the original 104B
outline wrapper for each item. After the loop it obtains the array
base **again**, passes index zero to the **23B original indexed access
helper**, and invokes the previously exact 76B fan wrapper on the
first item, using the same chosen center position.

The first normal source candidate was **225B/75 x86** with a `0x28`
stack frame. It reused the first array-base pointer for the final
lookup and passed the loop cursor directly to the 104B method. The
original instead has **two real distinct array-base local lifetimes**
(first inside the loop setup, second after loop completion), plus one
real current-item pointer local for each outline call. Giving these
true game values their separate source lifetimes recovers the native
`0x30` frame, original **233B/78 x86** and all nine E8 positions;
**189/189 nonrelocation bytes** now agree exactly. Nothing is patched,
no NOP inserted, and no inert local variable was added simply to
change machine-code size.

The indexed helper naturally implements access to `segment[index]`,
compiling to the original native `imul eax,[ebp+8],0x3D4` followed by
addition to the receiver base, with `ret 4`. The end helper naturally
returns `reinterpret_cast` of the owner byte address plus
`sizeof(segments)`—the true `0xB7C` one-past-array offset—matching
all original **19/19 bytes**, with no native calls or data
relocations. These are complete function bodies, not decompiler
pseudocode stubs.

**Origin caution:** These two small functions are typical of
compiler-generated fixed-container `operator[]`/`end` wrappers.
The original PE lacks proof that their implementations were directly
game-authored rather than STL/template-generated. Their exact native
source remains accepted in `config/match-units.toml`, but their
`function-origins.csv` records remain **unknown/review**, and they
are intentionally omitted from the authored-game `matches.csv` code
credit until independently resolved. This is more conservative than
treating every C++ function surrounding a game Boss as hand-authored.

## Pinned three-unit replay and scoped native accounting

One pinned MSVC 19.44.35211 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` source object/receipt,
`build/core884-canonical/AnimationPolygonMotionGroup233.obj`, owns
three distinct canonical whole native units:

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
Exact replay: 3/3 units, 1 cold objects
```

The 233B unit fixes **nine actual REL32 E8 and two DIR32/HIGHLOW**
source symbol/field/type/absolute target roles verified independently
against the locked PE. The 23B and 19B units have **zero original
relocations**, and both compare their entire genuine bytes. The
new translation unit does not edit existing accepted source/header
providers; replay is restricted to just this one modified source, not
an unfiltered full-graph cold replay.

This checkpoint credits **one new original authored whole game
function and 233 `.text` bytes**. The same source has since gained an
independently [whole-native exact 296B group configuration method](ANIMATION_POLYGON_GROUP_CONFIG_296_STRICT_EXACT.md),
without modifying its original 233B/23B/19B strict bodies. The additional **42 complete native
bytes of two helpers** are strict exact but remain origin-pending
rather than counted as authored game. Live totals are therefore
**633 original authored whole-native exact functions /233,199 code
bytes**, **1,283 source-present mappings /1,282 strict units /297
pinned compiler objects/receipts**. The prior 104B polygon outline
child still remains NONEXACT, and the enclosing game is not yet
linked/playable.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-motion-group233-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_motion_group_233
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_segment_at_23
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_segment_end_19
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
