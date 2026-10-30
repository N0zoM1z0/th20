# CORE/RECON-939 — complete native 156B C++17 64-point ribbon trail factory strict exact

Locked original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045DD90` is a **156B/46-i386** C++17 diagnostic
allocation instantiation for the real **0x320-byte polymorphic trail
ribbon group**, whose [103B ctor](ANIMATION_RIBBON_TRAIL_GROUP_CTOR103_STRICT_EXACT.md),
[520B update](ANIMATION_RIBBON_TRAIL_UPDATE520_STRICT_EXACT.md) and
[165B draw](ANIMATION_RIBBON_TRAIL_DRAW165_STRICT_EXACT.md) are already
independently complete and strict exact.

[`scripts/verify-animation-ribbon-trail-factory156-native.py`](../scripts/verify-animation-ribbon-trail-factory156-native.py)
reads the actual original PE and verifies all 156 bytes/46 instructions,
true `ret 8`, both native `push 0x320` values, **four original E8
positions/destinations**, **two genuine HIGHLOW positions/targets**, and
the original parent E8 in both the 47B and 49B configuration wrappers:

| Original field | Destination | Meaning |
| --- | --- | --- |
| E8 `+0x2D` | `0x0054275D` | Allocate real `0x320` bytes |
| E8 `+0x4D` | `0x0040C080` | Genuine C++17 `/sdl` class automatic zeroing |
| E8 `+0x56` | `0x0040B280` | Native forwarded Animation argument |
| E8 `+0x6A` | `0x0045DED0` | Whole-exact 103B trail group ctor |
| DIR32 `+0x06` | `0x00568917` | Native EH handler |
| DIR32 `+0x15` | `0x005B25C0` | Security cookie |
| Wrapper E8 `0x0045E533`, `0x0045E563` | `0x0045DD90` | Both physical upper-level allocation routes |

[`src/AnimationRibbonTrailGroupFactory156.cpp`](../src/AnimationRibbonTrailGroupFactory156.cpp)
instantiates the genuine C++17
`DiagnosticAllocator::allocate_object<NativeRibbonTrailGroup,Animation*>`
without an alternate object representation, explicit fake memset or
manually inserted assembly. Pinned MSVC 19.44 x86 C++17 `/Od /Ob0 /GS
/Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` reproduces the original
`.text` and all six native relocation fields in the correct positions:

```text
animation_ribbon_trail_factory_156: exact (156/156 bytes)
Existing 103B ctor, 49B wrapper, 520B update and 165B draw: whole strict exact
Exact replay: 5/5 strict units, 4 cold objects
```

The historical allocation template/compiler origin is **unknown/review**:
this adds **zero authored-game code byte credit** despite all 156
native bytes matching. It does not imply whole-exactness for the two
separate **340B/382B** configuration Bosses, which remain next targets.
No broad cold replay was performed.

```bash
scripts/repo-python scripts/verify-animation-ribbon-trail-factory156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonTrailGroupFactory156.cpp --source src/AnimationRibbonTrailGroupCtor103.cpp --source src/AnimationRibbonTrailGroupUpdate520.cpp --source src/AnimationRibbonTrailGroupDraw165.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
