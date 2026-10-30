# CORE/RECON-942 — complete original 47B gray and 49B magenta ribbon trail creation wrappers

Locked Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Two original game-specific cdecl functions create the same real 0x320-byte
64-point trail ribbon group but choose distinct original color modes.
The gray wrapper `0x0045E520` is **47B/18-i386**; magenta wrapper
`0x0045E550` is **49B/19-i386**. They are neither aliases nor
compiler-generated deleting wrappers.

[`scripts/verify-animation-ribbon-trail-wrappers-native.py`](../scripts/verify-animation-ribbon-trail-wrappers-native.py)
fully authenticates each original PE body and its return, both genuine
E8 locations/destinations, and both in-body HIGHLOW fields/targets:

| Original wrapper | Actual native fields | Original return behavior |
| --- | --- | --- |
| Gray `0x0045E520`, **47B** | Marker HIGHLOW `+0x09 -> 0x0056ED88`; process allocator HIGHLOW `+0x0F -> 0x005B8894`; E8 `+0x13 -> 0x0045DD90` factory; E8 `+0x26 -> 0x0045E240` gray 340B config | Return the actual gray configuration result |
| Magenta `0x0045E550`, **49B** | Marker HIGHLOW `+0x09 -> 0x0056ED38`; process allocator HIGHLOW `+0x0F -> 0x005B8894`; E8 `+0x13 -> 0x0045DD90` factory; E8 `+0x26 -> 0x0045E3A0` magenta 382B config | Ignore the configuration return and explicitly return zero, emitting real extra `xor eax,eax` |

[`src/AnimationRibbonTrailGrayWrapper47.cpp`](../src/AnimationRibbonTrailGrayWrapper47.cpp)
and [`src/AnimationRibbonTrailPinkWrapper49.cpp`](../src/AnimationRibbonTrailPinkWrapper49.cpp)
use one genuine polymorphic `NativeRibbonTrailGroup`, the already
independently exact [156B C++17 factory](ANIMATION_RIBBON_TRAIL_FACTORY156_STRICT_EXACT.md)
with `extern template` to avoid a competing instantiation, and the
separately whole exact [340B gray](ANIMATION_RIBBON_TRAIL_GRAY340_STRICT_EXACT.md)
and [382B magenta](ANIMATION_RIBBON_TRAIL_PINK382_STRICT_EXACT.md)
configuration methods. Both preserve the original two-parameter member
ABI, markers, Animation receiver and return semantics.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` generates both complete original functions with all eight
authentic relocation fields in the correct locations/targets; original
PE checks and original-target-bound relocated replay:

```text
animation_ribbon_trail_gray_wrapper_47: exact (47/47 bytes)
animation_ribbon_trail_pink_wrapper_49: exact (49/49 bytes)
Already exact original factory/340B gray/382B magenta: no regression
Exact replay: 5/5 units, 5 cold objects
```

This adds **two distinct authored original functions /96 total `.text`
bytes**. The allocator is separately accepted but remains template-origin
unknown, and its 156B is not counted again. The complete trail ribbon
runtime branch now has independently strict original entry, allocation,
construction, setup, update, draw and physical deletion; it is not proof
of a globally linked or playable game. No full cold replay was run.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-wrappers-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGrayWrapper47.cpp --source src/AnimationRibbonTrailPinkWrapper49.cpp --source src/AnimationRibbonTrailGroupGray340.cpp --source src/AnimationRibbonTrailGroupPink382.cpp --source src/AnimationRibbonTrailGroupFactory156.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
