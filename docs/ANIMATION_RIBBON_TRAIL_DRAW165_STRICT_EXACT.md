# CORE/RECON-938 — complete 165B 64-point ribbon LINESTRIP draw Boss strict exact

Locked original Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x0045E190` is a **165B/53-i386** polymorphic draw Boss
for the genuine 64-point ribbon trail group, whose separate
[520B update](ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md) and
[103B ctor](ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md) are
independently whole exact. Original vtable slot `0x0056ED24` points
physically to this draw method.

## Independent immutable PE and original ABI proof

[`scripts/verify-animation-ribbon-trail-draw165-native.py`](../scripts/verify-animation-ribbon-trail-draw165-native.py)
reads only the locked original PE and verifies all 165 bytes, 53 decoded
instructions, original function return, **eight physical E8 locations and
destinations**, all **three real HIGHLOW data fields and targets**, and
the true PE-relocated virtual draw slot:

| Original field | Destination | Role |
| --- | --- | --- |
| E8 `+0x20` | `0x00445BC0` | Genuine render texture binding |
| E8 `+0x28` | `0x00422E10` | World Vector3 construction |
| E8 `+0x3D` | `0x004376E0` | Native Animation position |
| E8 `+0x53` | `0x00414580` | First four-byte packed color cell at owner `+0x208` |
| E8 `+0x61` | `0x0040BDA0` | Native Motion begin/address of 64 geometry points at owner `+0x08` |
| E8 `+0x72` | `0x0040FF90` | Active point count from Timer at `+0x30C` |
| E8 `+0x90` | `0x0043D1A0` | Independently whole exact colored LINESTRIP backend |
| E8 `+0x9C` | `0x005429EE` | Security cookie verifier |
| DIR32 `+0x07` | `0x005B25C0` | Native security cookie |
| DIR32 `+0x1C`, `+0x8C` | `0x005C0028` | Genuine current AnimationPool pointer, both sites |

[`src/AnimationRibbonTrailGroupDraw165.cpp`](../src/AnimationRibbonTrailGroupDraw165.cpp)
uses the same single native polymorphic class and meaningful C++20
render flow: bind texture state, read Animation world position, reference
color cell 0, acquire the first Vector2 through the original Motion
begin/address helper, get Timer's current point count and submit the
array with the original backend. No fake vtable, raw byte padding,
manual x86 or abbreviated function was introduced.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` reproduces the entire original code and
11 real relocations, including 121/121 nonrelocated bytes. Strict
canonical original-target-bound replay:

```text
animation_ribbon_trail_draw_165: exact (165/165 bytes)
animation_ribbon_trail_update_520: exact (520/520 bytes)
animation_ribbon_trail_group_ctor_103: exact (103/103 bytes)
animation_ribbon_trail_scalar_delete_49: exact (49/49 bytes)
Exact replay: 4/4 units, 3 cold objects
```

This contributes **one original authored-game exact function /165
physical `.text` bytes**. The parent update and generated destructor
receive no repeated credit. The separate 340B and 382B configuration
Bosses remain independently open; whole-game linkage and playability
remain unproven.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-draw165-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGroupDraw165.cpp --source src/AnimationRibbonTrailGroupUpdate520.cpp --source src/AnimationRibbonTrailGroupCtor103.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
