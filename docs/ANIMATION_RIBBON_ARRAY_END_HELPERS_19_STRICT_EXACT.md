# CORE/RECON-914 — 60-element ribbon point/radius array ends whole native exact, 538B original frontier

> **CORE/RECON-915 update:** The earlier source-absent 538B parent is now
> independently [whole 538/538 strict exact](ANIMATION_RIBBON_SEGMENT_DYNAMICS_538_STRICT_EXACT.md).
> The previously accepted two 19B leaf receipts and origin decisions
> are unchanged.


Target: locked Japanese TH20 v1.00a Steamless image SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native `0x0045E800` **538B/149-i386** ribbon segment dynamics Boss is
still **SOURCE-ABSENT and NONEXACT**. This checkpoint does **not** count its
entire body just because its 140B caller or small helpers have become exact.
It establishes two separate whole original **19B/9-i386** array-end bodies,
their actual original call instructions, and the complete 538B original
call/absolute-data relocation census.

## Original native data and full 538B parent edges

[`scripts/verify-animation-ribbon-array-ends-native.py`](../scripts/verify-animation-ribbon-array-ends-native.py)
reads only the hash-locked PE `.text` and `.reloc`. It independently attests
the original 538B instruction boundaries, final `ret 4`, all **13 real E8
sites/targets**, all **10 in-body HIGHLOW positions/targets**, two genuine
array-end child calls, 60 two-float vertices at segment `+0x000`, a 60-cell
four-byte color region at `+0x1E0`, 60 radii at `+0x2D0`, and the closing
point access index **59**. The exact source-level representation of color
cells beyond their original four-byte size is still provisional.

| Native whole body | Original role | Child original call |
| --- | --- | --- |
| `0x0045DCA0` **19B/9 i386** | `+0xF0` one-past-end of 60 float radii | E8 `0x0045E83F` |
| `0x0045DCC0` **19B/9 i386** | `+0x1E0` one-past-end of 60 Vector2 points | E8 `0x0045E92A` |

Both helpers return a pointer in EAX and use ordinary `ret`; neither has
original E8 or PE HIGHLOW fields. The original 538B parent also has genuine
RNG, Angle constructor/value/increment, native vector indexing, polar point
transformation, 13 complete physical calls and ten referenced data globals,
including the real security cookie. These are original facts, **not**
compiler-exact proof of the enclosing 538B body.

## Natural source and strict 19B +19B replay

[`src/NativeRibbonArraySpans.hpp`](../src/NativeRibbonArraySpans.hpp)
declares actual C++ array views of **60 floats /60 Vector2**, respectively.
These views are composed once in the genuine
[`NativeRibbonSegment`](../src/NativeRibbonPolygonGroup.hpp), preserving its
real 0x3C0 stride, with no duplicate nominal polygon group. The single
[`source provider`](../src/AnimationRibbonArraySpanEnds19.cpp)
contains only their genuine one-past-end pointer methods.

Pinned MSVC x86 C++17 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl` reproduces both full 19B bodies with no relocation fields:

```text
animation_ribbon_scalar_end_19: exact (19/19 bytes)
animation_ribbon_point_end_19: exact (19/19 bytes)
```

The new header's include closure also affects four already canonical
polygon/ribbon methods. A **serial, affected-only replay** of the one
new provider plus all four affected prior providers confirms:

```text
Exact replay: 6/6 units, 5 cold objects
```

The two 19B bodies are `origin=unknown/review`, likely source-generation
or `std::array` helpers; **zero additional authored game functions/bytes**
are credited. The original **538B Boss remains unfinished**, and the
whole program still does not link or play.

```bash
scripts/repo-python scripts/verify-animation-ribbon-array-ends-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonArraySpanEnds19.cpp --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonGroupDraw156.cpp --source src/AnimationRibbonSegmentArrayEnd19.cpp --source src/AnimationRibbonSegmentDraw76.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
