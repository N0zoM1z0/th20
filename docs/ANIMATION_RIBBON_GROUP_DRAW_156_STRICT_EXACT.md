# CORE/RECON-912 — complete 156B polymorphic ribbon-group draw Boss strictly exact

> **CORE/RECON-913 update:** The separate original **76B segment draw
> `0x0045EAC0`** is now independently [whole 76/76 native exact](ANIMATION_RIBBON_SEGMENT_DRAW_76_STRICT_EXACT.md).
> The earlier source-absent child descriptions below remain historical;
> parent 156B code and receipts do not change.


Immutable target: Japanese TH20 1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original `0x0045EA20` is the **156B/53-i386** virtual draw method
of the same native group whose independent [140B update](ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md)
is whole strict exact. The PE vtable at `0x0056EDDC` directly points to
this draw head from its original **`0x0056EDE4`** slot.

## Original native function and complete pointer/call roles

[`scripts/verify-animation-ribbon-group-draw156-native.py`](../scripts/verify-animation-ribbon-group-draw156-native.py)
independently checks all 156 original bytes, complete 53 decoded instructions,
original `ret`, **seven complete E8 physical positions and target addresses**,
two genuine PE HIGHLOW fields and the original vtable. Original call table:

| Original E8 instruction | Destination | Role |
| --- | --- | --- |
| `+0x20` | `0x00445BC0` | Genuine texture/render-state binding |
| `+0x28` | `0x00422E10` | Vector3 position construction |
| `+0x3D` | `0x004376E0` | Animation world position |
| `+0x4F` | `0x0040BDA0` | Original Motion begin/address helper |
| `+0x5A` | `0x0045ECA0` | Separate 19B typed three-element array end |
| `+0x84` | `0x0045EAC0` | **76B segment renderer**, still source absent |
| `+0x93` | `0x005429EE` | Native security-cookie verifier |

The two original HIGHLOW locations are `+0x07 -> 0x005B25C0` (security
cookie) and `+0x1C -> 0x005C0028` (live animation-pool global).
The true segment stride is `0x3C0`, the same as the 140B update Boss.
The original single `nop` at `+0x42` follows Animation position output
and precedes the body of the three-segment traversal. No manual NOP
or padding is inserted into maintained source.

## Complete natural C++ and strict native proof

[`src/AnimationRibbonGroupDraw156.cpp`](../src/AnimationRibbonGroupDraw156.cpp)
uses the shared genuinely polymorphic `NativeRibbonGroup`, the real
Animation position output, and a natural **scoped traversal** of all three
0x3C0 segments. Scoping the traversal after texture binding and position
preparation naturally causes pinned MSVC to emit the original `nop` at
`+0x42`; the unscoped C++ compiled to only 155B and was rejected.
This is a genuine lexical lifetime boundary, not a dummy instruction/local,
preprocessor exactness branch or patched target byte.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` reproduces **every original instruction and all nine
relocation fields/targets**. After fresh canonical build and
relocation-aware replay:

```text
animation_ribbon_group_draw_156: exact (156/156 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one original authored-game whole function /156 native `.text`
bytes**. Together with the independently accepted 140B update, the pair
contributes 296 distinct authored bytes. Neither exact parent implies that
the separate 76B per-segment draw or 538B per-segment update is exact.
The separate 19B array end remains origin-unproven and uncredited.
The whole game is still not linked or playable.

```bash
scripts/repo-python scripts/verify-animation-ribbon-group-draw156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupDraw156.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
