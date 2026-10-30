# CORE/RECON-924 — original 75B ribbon color-array constructor and five INT3 strict exact

Locked original Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x0045D4B0` is a **75B/27-i386** C++
`std::array<AnimationHandle,60>` default constructor for 60 four-byte
packed-color cells in the `0x3C0` ribbon segment. Five immediately
following original PE bytes are authentic `INT3` alignment, not
executable code or authored-game coverage.

Independent [`scripts/verify-animation-ribbon-color-array75-native.py`](../scripts/verify-animation-ribbon-color-array75-native.py)
validates the entire original function and five-byte alignment, real 60
count and four-byte stride, one original E8 at `+0x33 -> 0x0040BC20`
(native EH-vector ctor), and three genuine HIGHLOW fields:

| Original field | PE destination | Role |
| --- | --- | --- |
| DIR32 `+0x06` | `0x00567600` | C++ EH handler |
| DIR32 `+0x13` | `0x005B25C0` | Security cookie |
| DIR32 `+0x27` | `0x00425CC0` | Zero-initializing 4B color-cell constructor |
| E8 `+0x33` | `0x0040BC20` | Native EH vector-constructor iterator |

The independently strict-exact native 60B ribbon segment constructor
physically calls this exact head at `0x0045D628` (`+0x18`). The source
[`src/AnimationRibbonColorArrayCtor75.cpp`](../src/AnimationRibbonColorArrayCtor75.cpp)
uses natural C++20 `std::construct_at` on the real 60-element
`std::array<AnimationHandle,60>`, so the compiler actually generates
the complete constructor body, not an ABI-shaped wrapper or copied bytes.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` reproduces all four original relocation roles,
all **75/75 native function bytes**, and the genuine five following
`INT3` in the complete **80/80 COFF contribution**:

```text
animation_ribbon_color_array_ctor_75: exact (75/75 coverage bytes; 80/80 compared bytes)
Exact replay: 1/1 units, 1 cold objects
```

Historical original C++ authorship of this generated/template-like body
is `unknown/review`; it adds **zero authored-game byte credit**.
The adjacent original `0x0045D500` **75B Vector2[60]** constructor
is a distinct separate native function and **remains NONEXACT**;
the shared `Vector2()` exception specification affects a much wider
canonical object closure. No shared Vector2 header or accepted existing
canonical source was modified and **no full-graph cold replay ran**.

```bash
scripts/repo-python scripts/verify-animation-ribbon-color-array75-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonColorArrayCtor75.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
