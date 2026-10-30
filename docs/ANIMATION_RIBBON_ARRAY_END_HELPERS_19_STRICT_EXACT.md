# CORE/RECON-914 — two native ribbon 19B array ends, whole strict exact

Locked original: Japanese TH20 1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045E800` **538B /149-i386** ribbon segment updater
physically calls two previously unsourced **19B /9-i386** array-end
functions. These two *separate* helpers are now complete canonical strict
exact, without claiming that the enclosing 538B parent is exact.

## Original-native proof and real 60-element geometry

[`scripts/verify-animation-ribbon-array-ends-native.py`](../scripts/verify-animation-ribbon-array-ends-native.py)
reads only the locked PE, fully decodes both native functions and the
parent's 538B extent, verifies their return boundaries, the genuine
call sites/targets, and the absence of native PE HIGHLOW in either helper.
The original parent uses a 60-element ring with this actual segment layout:

| Original native helper | Body | Original parent E8 | Physical result |
| --- | --- | --- | --- |
| `0x0045DCA0` | **19B/9 x86** | `0x0045E83F` | `this + 0xF0`: end of 60 floating radii from segment offset `+0x2D0` |
| `0x0045DCC0` | **19B/9 x86** | `0x0045E92A` | `this + 0x1E0`: end of 60 two-float vertices from segment offset zero |

The intervening native 60 four-byte color cells begin at `+0x1E0`.
Altogether the segment has **60 Vector2 /60 color words /60 float radii**
and a true `0x3C0` stride, independently corroborated by the earlier exact
140B update, 156B draw and 76B LINESTRIP caller.

## Full native C++ reconstruction and replay

[`src/NativeRibbonArraySpans.hpp`](../src/NativeRibbonArraySpans.hpp)
declares two real 60-element array views. The shared
[`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp)
uses them in the actual segment layout, not parallel invented objects.
[`src/AnimationRibbonArraySpanEnds19.cpp`](../src/AnimationRibbonArraySpanEnds19.cpp)
returns the authentic one-past-end addresses with natural typed arithmetic.
Pinned MSVC x86 C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl`
reproduces the complete original bodies:

```text
animation_ribbon_scalar_end_19: exact (19/19 bytes)
animation_ribbon_point_end_19: exact (19/19 bytes)
Exact replay: 2/2 units, 1 cold objects
```

The shared header's actual captured include closure includes the four
preexisting exact ribbon providers (19B group end, 140B update, 156B draw,
76B LINESTRIP caller); all **4/4 survived fresh native cold builds and
strict relocated replay**, with no broader replay. Another identical
native-matching local approach using `NativeRibbonPerimeterArray` and
`NativeRibbonRadiusArray` was inspected and preserved with SHA-256 source
snapshots privately in `.analysis/gptweb-ribbon-ends-consolidation/` before
consolidating to one canonical owner. No original target, previously accepted
source, or canonical receipts were discarded.

Both new function origins remain `unknown/review` and are excluded from
authored-game code totals. The 538B Boss is **still source absent at this
checkpoint**; the original 149 instructions and both array end calls do not
by themselves prove C++ source or machine-code exactness of the parent.

```bash
scripts/repo-python scripts/verify-animation-ribbon-array-ends-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonArraySpanEnds19.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentArrayEnd19.cpp --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonGroupDraw156.cpp --source src/AnimationRibbonSegmentDraw76.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
