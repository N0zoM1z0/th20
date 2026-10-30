# CORE/RECON-917 — full original 78B ribbon three-segment array constructor strict exact

Locked Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The native `0x0045E670` **78B/27-i386** C++20 array constructor
constructs three actual **0x3C0-byte** ribbon segments, using the
independently [whole exact 60B segment constructor](ANIMATION_RIBBON_SEGMENT_CTOR_60_STRICT_EXACT.md).
The function ends at `ret` `+0x4D`, followed by **five real original
`INT3` bytes**. These trailing bytes are alignment, not authored code.

[`scripts/verify-animation-ribbon-segment-array78-native.py`](../scripts/verify-animation-ribbon-segment-array78-native.py)
independently verifies original PE function boundaries, all 27
instructions, exact three-element count and stride, its one real E8
at `+0x36 -> 0x0040BC20` (native EH vector constructor), and three
physical HIGHLOW positions:

| Original field | Destination | Role |
| --- | --- | --- |
| `+0x06` | `0x00567600` | Native C++ EH handler |
| `+0x13` | `0x005B25C0` | MSVC security cookie |
| `+0x27` | `0x0045D610` | Whole exact genuine 60B ribbon segment constructor callback |
| E8 `+0x36` | `0x0040BC20` | Real EH vector construction iterator |

Independent original E8 in the still-unaccepted **89B native group
constructor** physically invokes this head at `0x0045E6F2`.
The typed one-canonical-class segment array is declared in
[`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp).
The natural [`src/AnimationRibbonSegmentArrayCtor78.cpp`](../src/AnimationRibbonSegmentArrayCtor78.cpp)
instantiates its genuine `std::array<NativeRibbonSegment,3>` default
construction, which MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` emits as the entire original contribution.

```text
animation_ribbon_segment_array_ctor_78: exact (78/78 coverage bytes; 83/83 compared bytes)
Exact replay: 1/1 units, 1 cold objects
```

After the shared array header declaration, **six** existing affected
ribbon source providers were cold recompiled and **6/6 whole-exact
units remain exact**: 19B group array-end, 140B update, 156B draw,
76B renderer, 538B dynamics and 60B segment constructor. No unrelated
providers or unfiltered graph-wide replay were rebuilt.

This native array constructor remains `origin=unknown/review` and is
excluded from game-authored `.text` totals, despite complete strict
byte/relocation match. This **does not** yet establish exactness for the
89B polymorphic group constructor or 156B allocation factory.

```bash
scripts/repo-python scripts/verify-animation-ribbon-segment-array78-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentArrayCtor78.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
