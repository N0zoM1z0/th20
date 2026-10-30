# CORE/RECON-943 — original 75B trail-ribbon color-array constructor and 5 INT3 strict exact

Locked Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The complete native original `0x0045DE30` is a **75B/27-i386**
C++20 `std::array<AnimationHandle,64>` default constructor for 64
four-byte color cells in the real 0x320-byte polymorphic trail ribbon
group. The following **five genuine original `INT3` bytes** are
function alignment, not authored-game executable bytes.

[`scripts/verify-animation-ribbon-trail-color75-native.py`](../scripts/verify-animation-ribbon-trail-color75-native.py)
reads the immutable original PE and independently authenticates all
75 native bytes, 27 instructions, native `ret`, 64 elements of four
bytes, original five-byte alignment, and all real PE relocation roles:

| Original field | Actual destination | Role |
| --- | --- | --- |
| DIR32 `+0x06` | `0x00567600` | Native C++ EH handler |
| DIR32 `+0x13` | `0x005B25C0` | Original security cookie |
| DIR32 `+0x27` | `0x00425CC0` | Real four-byte `AnimationHandle` zero constructor |
| E8 `+0x33` | `0x0040BC20` | Native EH-vector constructor iterator |
| Parent E8 `0x0045DF00` | `0x0045DE30` | Original whole-exact 103B trail group ctor invokes this body |

[`src/AnimationRibbonTrailColorArrayCtor75.cpp`](../src/AnimationRibbonTrailColorArrayCtor75.cpp)
uses ordinary `std::construct_at(&std::array<AnimationHandle,64>)`
in C++20 to instantiate the compiler's actual array constructor, not
a handcrafted ABI shim. Pinned MSVC 19.44 x86 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` reproduces every native
relocation field and all 75 executable bytes plus the five original
alignment `INT3`:

```text
animation_ribbon_trail_color_array_ctor_75: exact (75/75 coverage bytes; 80/80 compared bytes)
Original trail-ribbon ctor 103B and 49B deletion: strict exact
Exact replay: 3/3 units, 2 cold objects
```

Compiler/STL authorship remains `unknown/review`, so this adds **zero
authored-game byte credit**. The other 75B native `std::array<Vector2,64>`
constructor `0x0045DE80` is separately NONEXACT: the native exception
specification requires its own verification and must not be implied from
this color array match. No shared `Vector2.hpp` edits or broad cold replay
were used.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-color75-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailColorArrayCtor75.cpp --source src/AnimationRibbonTrailGroupCtor103.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
