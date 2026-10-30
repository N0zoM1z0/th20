# CORE/RECON-941 — complete original 382B magenta trail ribbon configuration Boss strict exact

Immutable Japanese TH20 v1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045E3A0` is a **382B/113-i386** game-specific magenta
64-point ribbon configuration Boss. The distinct
[340B gray configuration](ANIMATION_RIBBON_TRAIL_GRAY340_STRICT_EXACT.md)
and the shared [520B update](ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md),
[165B draw](ANIMATION_RIBBON_TRAIL_DRAW165_STRICT_EXACT.md) and
[103B ctor](ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md)
are all independently whole native exact, using the same real 0x320
polymorphic class. The original 49B creation wrapper `0x0045E550`
physically calls this function at E8 `0x0045E576`.

[`scripts/verify-animation-ribbon-trail-pink382-native.py`](../scripts/verify-animation-ribbon-trail-pink382-native.py)
reads the original target PE and fully validates 382 bytes/113 native
instructions, every **11 E8 site/destination**, both physical HIGHLOW
fields/targets (`pi` at `0x0056E0F0` and RNG at `0x005BA4C4`), the
original `ret 8`, and the exact upper wrapper call site.

Unlike the gray mode, this method writes its second `int32` token to
the genuine owner `+0x31C` field. It zeroes the initial Vector2 point,
sets angle to `GameRandom::range(pi)` and Timer to one, then initializes
64 original four-byte colors at `+0x208` with **`0xFF0080FF`**. The
first eight entries modify **blue byte +2** using `255-(index<<5)`;
entries 32–63 fade **alpha byte +3** with an independent `255-(tail<<4)`
sequence. Animation receives native position, layer **15**, original
flag byte one and the original style arguments `(64,0,255,0)`.

[`src/AnimationRibbonTrailGroupPink382.cpp`](../src/AnimationRibbonTrailGroupPink382.cpp)
uses the real class, two-argument native ABI, structured color-cell
byte fields and ordinary C++ control flow. There is no manual stack
manipulation, copied machine code or forced NOP. Pinned MSVC 19.44
x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
reproduces all 13 real relocation fields and all **330/330
nonrelocated bytes**. Relocation-aware original-bound replay:

```text
animation_ribbon_trail_pink_382: exact (382/382 bytes)
Other local ctor/delete/update/draw/factory/340B gray: all strict exact
Exact replay: 7/7 units, 6 cold objects
```

This adds **one genuinely game-authored whole exact original function
/382 native `.text` bytes**. The gray mode remains separately counted
only once, and generated factory/destructor contributions are not
mistaken for authored game code. The two native 47B/49B creation wrappers
still require their own independent source/PE acceptance.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-pink382-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGroupPink382.cpp --source src/AnimationRibbonTrailGroupGray340.cpp --source src/AnimationRibbonTrailGroupUpdate520.cpp --source src/AnimationRibbonTrailGroupDraw165.cpp --source src/AnimationRibbonTrailGroupFactory156.cpp --source src/AnimationRibbonTrailGroupCtor103.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
