# CORE/RECON-882/883 — original 76B Polygon Motion TRIANGLEFAN caller strict exact; sibling 104B outline caller NONEXACT

The locked Japanese TH20 v1.00a Steamless executable SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
These are two distinct game-authored methods in the original polygon
rendering call graph. Both invoke whole-native strict exact renderer
Bosses, but **only the 76B method has a complete pinned original-byte
match**. The 104B source is valuable for parent reconstruction but
must remain **SOURCE-PRESENT/NONEXACT**.

| Native original fact | Filled fan caller | Polygon stroke caller |
| --- | --- | --- |
| Original function head | `0x0045FB10` | `0x0045FAA0` |
| Whole original body/instructions | **76B /27 i386** | **104B /36 i386** |
| Original ABI | `sub esp,0x10`, `ret 4` | `sub esp,0x10`, `ret 4`, saved ESI |
| Actual native E8 destinations | Vector3::operator[] 0x414580, Motion::position_ref 0x40BDA0, 455B renderer 0x43CB70 | Vector3::operator[] 0x414580, Motion::position_ref 0x40BDA0, 1,204B renderer 0x43D370 |
| Original native E8 physical fields | **3** | **3** |
| Original PE HIGHLOW fields | **1** at global renderer pointer `0x005C0028` | **2** at 16.0f `0x0056CD90` and renderer pointer `0x005C0028` |
| Original direct parent 233B E8 site | `0x0045FA84` | `0x0045FA5F` |
| Natural source whole native comparison | **76/76 exact**, 27 i386 | **102/104**, 34/36 i386, **NONEXACT** |

## Immutable original-only native proof

[`scripts/verify-animation-polygon-motion-callers-native.py`](../scripts/verify-animation-polygon-motion-callers-native.py)
reads original `.text` and actual PE `.reloc`, disassembles both full
bodies through native returns, verifies all three physical E8
site/target pairs in each function, and authenticates the original
**32-bit i386 PE HIGHLOW absolute references**. It independently reads the real **16.0f IEEE-754** value
at `0x0056CD90` and the original AnimationPoolOwner* game global
at `0x005C0028`, then verifies the original **233B caller** at
`0x0045F9B0` actually calls the 104B stroke wrapper and the 76B
filled-fan wrapper at E8 `0x0045FA5F` and `0x0045FA84`.

Both real methods act on a nominal polygon item whose **offset-zero
`Motion` base and `+0x1E8` Vector3 data are native-observed**.
They obtain the actual packed-color source address through the
already exact `Vector3::operator[]` helper on the latter, and obtain
the geometry stream through the original `Motion::position_ref`
helper on the former. The original full ~0x3D4 item class identity
and remaining fields are provisional. A single header
[`src/NativeMotionPolygonOwner.hpp`](../src/NativeMotionPolygonOwner.hpp)
declares both methods without constructing a new object/vtable.

## Complete exact 76B filled-fan wrapper

The natural source
[`src/AnimationPolygonFanCaller76.cpp`](../src/AnimationPolygonFanCaller76.cpp)
uses `Vector3[0]` from receiver `+0x1E8` as the raw packed-color
stream and the real offset-zero Motion position as the `Vector2`
point stream. It invokes the independently whole exact
[455B TRIANGLEFAN renderer](ANIMATION_CORNER_PROJECTION_985_VERTEX_DRAW_455_STRICT_EXACT.md)
with **61 input records**, the caller origin and both native streams.
All three real E8 targets, the one actual PE HIGHLOW owner field and
native receiver/stack return ABI are exact. Its single canonical unit
`animation_polygon_motion_fan_caller_76` in
[`config/match-units.toml`](../config/match-units.toml) owns one fresh
pinned i386 MSVC C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` object/receipt:

```text
animation_polygon_motion_fan_caller_76: exact (76/76 bytes)
Exact replay: 1/1 units, 1 cold objects
```

## Whole semantic 104B stroke wrapper — still NONEXACT

The natural source
[`src/AnimationPolygonMotionCall104.cpp`](../src/AnimationPolygonMotionCall104.cpp)
uses `Vector3[1]` at receiver `+0x1E8` as the packed color array,
the same genuine offset-zero Motion position with an additional **8B
`Vector2` stream offset**, actual center pointer, count **60**, native
16.0f stroke width and closed flag 1. It calls the independently
whole strict exact
[1,204B polygon stroke Boss](ANIMATION_POLYGON_OUTLINE_1204_STRICT_EXACT.md).

The original 104B/36-x86 method **pushes ESI**, computes an
**8-byte `Vector2` element offset as `mov esi,8; shl esi,0` before
calling `Motion::position_ref`**, adds ESI to returned EAX and
**pops ESI** on return. Normal MSVC C++ instead evaluates the method
call first, then computes the typed `[1]` offset into a volatile ECX,
and emits **102B/34-x86**. All three genuine callee roles and both
absolute target classes are present but the physical instructions
and fields do not match. Multiple natural array-index and pointer
forms were tested; none reproduces native ESI lifetime without
inserting artificial instructions. **No strict unit, canonical exact
receipt, or `.text` byte credit is claimed** for this sibling.

An earlier redundant nominal wrapper class/source for the same 104B
physical address was inspected and consolidated into the single
`NativeMotionPolygonOwner` declaration. It is not acceptable to
count two source guesses as separate original game functions.

## Scope and precise progress

The two original wrappers' nominal receiver is declared only in the
new header, so existing strict game source providers are not modified.
Their upstream 233B group method has since been independently recovered
as a [whole-native strict exact Boss](ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md).
This does **not** make the remaining 104B outline wrapper exact.
The 76B source itself is cold-replayed alone. The 104B semantic source
is compiled as a diagnostic probe, not exact replay. Neither its
original 233B parent nor the two already accepted 455B/1,204B
rendering children received duplicate code credit at this prior
checkpoint; the 233B parent is credited independently in the later
linked evidence. The large
5,993B Animation Draw parent independently remains NONEXACT.
No unfiltered graph-wide cold replay is run.

The one new strict game original adds **76 distinct native `.text`
bytes**. Live inventory after the checkpoint is **632 whole authored
exact game functions /232,966 native game bytes**, **1,280
source-present mappings /1,279 strict canonical units /296 pinned
compiler object/receipt providers**. The mapping count can legitimately
exceed strict units because the 104B game wrapper is source present
but not exact.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-motion-callers-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonFanCaller76.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_motion_fan_caller_76
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
