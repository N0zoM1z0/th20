# CORE/RECON-930 — whole original 78B single-segment ribbon array ctor and 5 INT3 strict exact

Original Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045D550` is a complete **78B/27-i386** C++ array
construction method for exactly **one genuine 0x3C0-byte ribbon segment**.
The following **five original `INT3` bytes** are alignment, not game code.

[`scripts/verify-animation-ribbon-solo-array78-native.py`](../scripts/verify-animation-ribbon-solo-array78-native.py)
reads the immutable original PE and checks all native bytes, actual return,
three physical HIGHLOW fields, one E8, 0x3C0 stride, count 1, and the
real parent call from the distinct 89B solo group constructor.

| Original relocation | Destination | Meaning |
| --- | --- | --- |
| HIGHLOW `+0x06` | `0x00567600` | C++ exception handler |
| HIGHLOW `+0x13` | `0x005B25C0` | Security cookie |
| HIGHLOW `+0x27` | `0x0045D610` | Independently exact 60B ribbon-segment element constructor |
| E8 `+0x36` | `0x0040BC20` | Actual EH-vector construction helper |
| Parent E8 `0x0045D5D2` | `0x0045D550` | Original polymorphic solo group construction |

The native actual element array uses the same `NativeRibbonSegment`
class and real 60 `Vector2`/60 color-word/60 float-radius subobjects
from previously accepted sources. Its natural C++20 method is generated
by [`src/AnimationRibbonSoloSegmentArrayCtor78.cpp`](../src/AnimationRibbonSoloSegmentArrayCtor78.cpp)
without inline instruction bytes, compiler-padding hacks or a fake class.
The shared [`NativeRibbonSoloGroup.hpp`](../src/NativeRibbonSoloGroup.hpp)
now declares a normal array wrapper constructor, while its group still
owns its original direct `std::array<NativeRibbonSegment,1>` at +8.

Pinned MSVC 19.44 x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, canonical full relocation-aware comparison:

```text
animation_ribbon_solo_segment_array_ctor_78: exact (78/78 coverage bytes; 83/83 compared bytes)
Exact replay: 1/1 new units, 1 cold object
```

The 140B solo update and 697B segment dynamics were separately compiled
and remained strict exact after the shared header declaration change.
The historical original owner/compiler-STL authorship is not established:
this is **zero authored-game bytes** despite full native exactness.
The original 89B group ctor and 49B deleting wrapper remain separate
functions requiring independent canonical acceptance.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-array78-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloSegmentArrayCtor78.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
