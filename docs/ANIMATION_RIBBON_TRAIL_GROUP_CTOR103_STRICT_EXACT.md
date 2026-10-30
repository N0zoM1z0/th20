# CORE/RECON-936 — complete original 103B trail ribbon constructor and 49B deletion strict exact

Locked Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This independently distinct polymorphic `AnimationCallback` group has
vtable `0x0056ED1C` and native class size **0x320**. Original constructor
`0x0045DED0` is **103B/28-i386**; the original scalar-deleting wrapper
`0x0045DF40` is **49B/18-i386**.

## Independent native PE proof

[`scripts/verify-animation-ribbon-trail-ctor103-native.py`](../scripts/verify-animation-ribbon-trail-ctor103-native.py)
fully verifies both immutable native function bodies, every true E8
instruction/destination, the constructor's single physical vptr HIGHLOW,
zero deleting-wrapper HIGHLOW, and the entire original six-slot vtable:

| Original site | Target | Actual role |
| --- | --- | --- |
| ctor E8 `+0x0E` | `0x00446B60` | Native AnimationCallback base |
| ctor DIR32 `+0x18` | `0x0056ED1C` | Real derived virtual table |
| ctor E8 `+0x22` | `0x0045DE80` | Genuine `std::array<Vector2,64>` construction |
| ctor E8 `+0x30` | `0x0045DE30` | Genuine `std::array<AnimationHandle,64>` construction |
| ctor E8 `+0x4C` | `0x00422D90` | Native Timer ctor at owner `+0x30C` |
| delete E8 `+0x0A` | `0x0045C2A0` | Existing folded 20B ordinary destructor |
| delete E8 `+0x20` | `0x0054278D` | Sized delete of true `0x320` bytes |

The original layout observed in constructor and update includes 64 two-float
points `+0x08..+0x207`, 64 four-byte color cells `+0x208..+0x307`,
angle `+0x308`, Timer `+0x30C..+0x31B` and terminal pointer-sized
member `+0x31C`. The original vtable's update slot points to the
separate **520B native Boss `0x0045DF80`** and draw slot to the
separate **165B native draw `0x0045E190`**, neither inferred exact here.

[`src/NativeRibbonTrailGroup.hpp`](../src/NativeRibbonTrailGroup.hpp)
implements one layout-asserted natural C++ class, and
[`src/AnimationRibbonTrailGroupCtor103.cpp`](../src/AnimationRibbonTrailGroupCtor103.cpp)
uses genuine base/member initialization rather than manually writing a
vptr or padding. The compiler emits both original target contributions:

```text
animation_ribbon_trail_group_ctor_103: exact (103/103 bytes)
animation_ribbon_trail_scalar_delete_49: exact (49/49 bytes)
Exact replay: 2/2 units, 1 cold object
```

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl` with the original-target-bound relocation-aware oracle verifies
all bytes and target roles. The unique 103B constructor adds **one
original game-authored function /103 `.text` bytes**. The compiler-like
49B deletion wrapper and already accepted folded 20B ordinary destructor
receive **zero** additional authored-game credit. This does not assert
whole-game linkage or playability.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-ctor103-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGroupCtor103.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
