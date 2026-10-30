# CORE/RECON-928 — complete original 76B solo ribbon TRIANGLEFAN strictly exact

Locked Japanese TH20 Steamless 1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This is the original `0x0045DAE0` **76B/27-i386** segment fan
renderer called by the independently whole-exact
[156B solo ribbon virtual draw Boss](ANIMATION_RIBBON_SOLO_DRAW_156_STRICT_EXACT.md)
at original E8 instruction `0x0045DAC4`. Its 60-point triangle-fan
protocol differs from the separately exact three-segment group's
76B line-strip renderer, so they cannot be credited as aliases.

## Independently original-native physical evidence

[`scripts/verify-animation-ribbon-solo-fan76-native.py`](../scripts/verify-animation-ribbon-solo-fan76-native.py)
reads the locked PE rather than compiled candidate bytes and
independently verifies the entire 76B/27-instruction native body,
real `ret 4`, all three true E8 instruction/destination pairs, its
single physical PE HIGHLOW field, genuine `nop` and original parent E8:

| Original field | Native destination | Proven role |
| --- | --- | --- |
| E8 `+0x19` | `0x00414580` | Native Vector3 color stream access at `+0x1E0` |
| E8 `+0x24` | `0x0040BDA0` | Native offset-zero Motion geometry begin |
| DIR32 `+0x3C` | `0x005C0028` | Real AnimationPoolOwner global |
| E8 `+0x40` | `0x0043CB70` | Previously exact 455B colored TRIANGLEFAN renderer |
| Parent E8 `0x0045DAC4` | `0x0045DAE0` | The original solo group 156B draw invokes this whole body |

The true count is **60** (push `0x3C`), not the distinct
61-vertex polygon fan. The segment's original receiver layout has
packed colors at `+0x1E0` and a real Motion base at offset zero.

## Natural C++ native acceptance and independent credit

[`src/AnimationRibbonSoloSegmentFan76.cpp`](../src/AnimationRibbonSoloSegmentFan76.cpp)
uses one non-owning nominal receiver interface declared in
[`src/NativeRibbonSoloGroup.hpp`](../src/NativeRibbonSoloGroup.hpp),
without introducing a duplicate allocated segment/vtable. It invokes
the existing whole-exact renderer through the authentic game pool
and typed colors/geometry pointers.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` produces all original
relocation field types and physical targets, and the independent
canonical full-function oracle confirms:

```text
animation_ribbon_solo_fan_76: exact (76/76 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one independent authored-game original head /76 `.text`
bytes**. The distinct 156B parent, 19B array end and 140B update
were separately rebuilt and remain whole exact; no duplicate credit
from those children or unfiltered whole-graph cold replay.
The separate **697B native solo ribbon segment dynamics Boss**
called by the 140B updater remains unsourced.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-fan76-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloSegmentFan76.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
