# CORE/RECON-921 — entire original 23B ribbon segment pointer index whole strict exact

Locked Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

Original `0x0045D690` is a complete **23B /9-x86** pointer helper
for the actual three-element, `0x3C0` stride ribbon segment array.
[`scripts/verify-animation-ribbon-segment-at23-native.py`](../scripts/verify-animation-ribbon-segment-at23-native.py)
reads only the immutable original PE and proves the full function
boundary, `imul eax,[ebp+8],0x3c0`, `ret 4`, zero in-body
HIGHLOW/E8, and all **three** physical callers from the independently
separate original 252B ribbon group configuration Boss:

| Original parent E8 | Destination | Index used |
| --- | --- | --- |
| `0x0045EB52` | `0x0045D690` | 0 |
| `0x0045EB75` | `0x0045D690` | 1 |
| `0x0045EB98` | `0x0045D690` | 2 |

The true `NativeRibbonSegmentArray` class shares the same
[`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp)
segment layout used in exact 60B ctor, 538B dynamics and 140B update.
[`src/AnimationRibbonSegmentAt23.cpp`](../src/AnimationRibbonSegmentAt23.cpp)
returns `reinterpret_cast<NativeRibbonSegment*>(this) + index` through
normal C++ pointer arithmetic, without raw x86 bytes or padding.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` produces the entire canonical contribution:

```text
animation_ribbon_segment_at_23: exact (23/23 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This helper's original compiler/STL vs game-source ownership is
unverified, and it contributes **zero authored-game exact-byte credit**.
The 252B parent needs its own whole native source and validation;
the three correct E8 links do not make it exact. Only the affected
ribbon sources, not the entire project, are eligible for cold replay.

```bash
scripts/repo-python scripts/verify-animation-ribbon-segment-at23-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentAt23.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
