# CORE/RECON-927 — complete original 156B one-segment ribbon group virtual draw strictly exact

> **CORE/RECON-928 follow-up:** The separate original 76B segment
> TRIANGLEFAN callee is now independently [whole 76/76 strict exact](ANIMATION_RIBBON_SOLO_FAN_76_STRICT_EXACT.md).
> The previously accepted 156B parent receipt is unchanged.

Immutable Japanese TH20 1.00a Steamless executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Original `0x0045DA40` is a whole **156B/53-i386** virtual draw Boss
in the distinct **one-segment** ribbon polymorphic group, not the earlier
three-segment 156B ribbon group at `0x0045EA20`.

[`scripts/verify-animation-ribbon-solo-draw156-native.py`](../scripts/verify-animation-ribbon-solo-draw156-native.py)
reads the original PE, checks all decoded instructions through the final
`ret`, authentic NOP at `+0x42`, true `0x3C0`-byte stride, real six-slot
vtable `0x0056ECA4` (with native `.reloc` entries), all seven original
E8 sites/targets, and both genuine in-body HIGHLOW fields:

| Original physical field | Destination | Role |
| --- | --- | --- |
| E8 `+0x20` | `0x00445BC0` | Actual texture state binding |
| E8 `+0x28` | `0x00422E10` | Real Vector3 construction |
| E8 `+0x3D` | `0x004376E0` | Animation world position |
| E8 `+0x4F` | `0x0040BDA0` | Motion begin/address helper |
| E8 `+0x5A` | `0x0045DCE0` | Independently exact 19B one-segment array end |
| E8 `+0x84` | `0x0045DAE0` | Separate original **76B TRIANGLEFAN segment renderer**, still unaccepted at this checkpoint |
| E8 `+0x93` | `0x005429EE` | Security-cookie verifier |
| DIR32 `+0x07` | `0x005B25C0` | Original security cookie |
| DIR32 `+0x1C` | `0x005C0028` | Current AnimationPool owner global |

The natural [`src/AnimationRibbonSoloGroupDraw156.cpp`](../src/AnimationRibbonSoloGroupDraw156.cpp)
reconstructs original rendering preparation, Animation position and a
separate scoped traversal of exactly one real ribbon segment. The
`+0x42` NOP is emitted by ordinary MSVC `/Od` lexical lifetime
semantics; no manual padding or inline machine instructions exist.
The separate ABI-only `NativeRibbonSoloSegmentDrawView` is a non-owning
interface to the original 76B child, not a second constructed class.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` and canonical original-bound relocated replay:

```text
animation_ribbon_solo_draw_156: exact (156/156 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Both the already accepted 140B solo update and 19B array end were also
freshly replayed in only their affected local source closure, **3/3
strict exact units across three cold objects**. A parallel candidate
used a different nominal ABI view name; its full source header is
preserved in ignored `.analysis/gptweb-solo-draw156/alternate-renderer-view.hpp`
before choosing one canonical shared ABI owner. No valid work was
silently discarded. The original 76B child and 697B dynamics remain
separate functions requiring independent proof.

This adds **one genuinely game-authored original whole exact function
/156 native `.text` bytes**. Source mapping, compiler/library origin,
static data and whole-program linkability are separate outcomes.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-draw156-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloGroupDraw156.cpp --source src/AnimationRibbonSoloGroupUpdate140.cpp --source src/AnimationRibbonSoloArrayEnd19.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
