# CORE/RECON-916 — original 60B ribbon segment constructor whole strict exact

Locked original Japanese TH20 Steamless v1.00a:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897` (SHA-256).
The original `0x0045D610` is the **60B /20-i386** game-specific
constructor of the same `0x3C0`-byte segment whose
[538B updater](ANIMATION_RIBBON_SEGMENT_DYNAMICS_538_STRICT_EXACT.md) and
[76B renderer](ANIMATION_RIBBON_SEGMENT_DRAW_76_STRICT_EXACT.md)
are already independently whole exact.

## Original physical call and allocation evidence

[`scripts/verify-animation-ribbon-segment-ctor60-native.py`](../scripts/verify-animation-ribbon-segment-ctor60-native.py)
independently reads the exact original PE code and relocation table.
The complete 60B body ends at its real `ret` and has **20 i386 instructions**,
three genuine E8 positions/destinations and no in-body PE HIGHLOW:

| Original E8 | Real destination | Physical behavior |
| --- | --- | --- |
| `+0x0A` | `0x0045D500` | Default-construct 60 native `Vector2` positions |
| `+0x18` | `0x0045D4B0` | Default-construct 60 4B `AnimationHandle`-compatible color cells |
| `+0x2D` | `0x00544760` | Clear exactly `0xF0` bytes of 60 float radii at `+0x2D0` |

Independent original `0x0045E670` three-element array constructor
contains a **physical DIR32 field at `0x0045E697`** pointing back to
`0x0045D610`, which is the genuine callback for one 0x3C0 element.
The segment sizes are native-supported: `60*8 +60*4 +60*4 =0x3C0`.
The separate 75B position/color-cell array constructor targets remain
unaccepted until their own C++ byte and relocation proofs.

## Native C++ and exact replay

The shared [`NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp)
retains one canonical C++ segment class, now with actual 60
`AnimationHandle`-compatible four-byte cells instead of nominal raw words.
[`src/AnimationRibbonSegmentCtor60.cpp`](../src/AnimationRibbonSegmentCtor60.cpp)
uses the natural `NativeRibbonSegment() noexcept : radius_2d0{} {}`:
positions and colors default-construct, while **only** the native 60-float
radius buffer value-initializes. Its C++20 locked MSVC x86 `/Od /Ob0 /GS
/Gy /Zl /arch:SSE2 /fp:precise /sdl` no-`/EHsc` body reproduces all
60/60 original relocated machine bytes:

```text
animation_ribbon_segment_ctor_60: exact (60/60 bytes)
Exact replay: 1/1 units, 1 cold objects
```

All **5 affected preexisting exact ribbon C++ objects** were recompiled
and locally replayed after the shared-header change, **5/5 exact**:
19B three-segment end; 140B update; 156B draw; 76B LINESTRIP wrapper;
538B segment dynamics. The two 19B position/radius end helper inputs
include a different header, and are unchanged. There was no graph-wide
cold replay.

This adds **one genuine authored original game function /60 native `.text`
bytes**. It does not give any code credit to the separate still-unaccepted
75B array constructors, 78B triple-array parent, or 89B group constructor.

```bash
scripts/repo-python scripts/verify-animation-ribbon-segment-ctor60-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentCtor60.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentArrayEnd19.cpp --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonGroupDraw156.cpp --source src/AnimationRibbonSegmentDraw76.cpp --source src/AnimationRibbonSegmentDynamics538.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
