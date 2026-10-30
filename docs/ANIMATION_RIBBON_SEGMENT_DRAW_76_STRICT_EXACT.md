# CORE/RECON-913 — complete 76B ribbon segment LINESTRIP wrapper native exact

Original target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The genuine `0x0045EAC0` is a distinct **76B/27-i386 authored game method**,
called by the independently strict exact [156B ribbon-group draw](ANIMATION_RIBBON_GROUP_DRAW_156_STRICT_EXACT.md).
Its sibling 76B `0x0045FB10` fan renderer has a different `+0x1E8`
color stream, 61 vertices and TRIANGLEFAN backend; it is **not** this body.

## Independently original-PE-verified dispatch and data

[`scripts/verify-animation-ribbon-segment-draw76-native.py`](../scripts/verify-animation-ribbon-segment-draw76-native.py)
validates all 76 native code bytes, 27 decoded instructions, full `ret 4`,
original `+0x1E0` packed-color stream, 60-vertex count, three real E8
positions and the one genuine PE HIGHLOW field:

| Original field | Actual target | Meaning |
| --- | --- | --- |
| E8 `+0x19` | `0x00414580` | Actual `Vector3::operator[](0)` color-stream begin |
| E8 `+0x24` | `0x0040BDA0` | Offset-zero `Motion::position_ref()` geometry begin |
| DIR32 `+0x3C` | `0x005C0028` | Real global AnimationPoolOwner* |
| E8 `+0x40` | `0x0043D1A0` | Independently whole exact 455B colored LINESTRIP backend |
| Parent E8 `0x0045EAA4` | `0x0045EAC0` | Exact parent 156B ribbon draw calls this 76B body |

The source [`src/AnimationRibbonSegmentDraw76.cpp`](../src/AnimationRibbonSegmentDraw76.cpp)
uses the actual same-size ribbon segment view, a genuine typed Vector3
color-array access, the offset-zero Motion position, original line
primitive count 60 and the accepted 455B LINESTRIP renderer. No target
byte copying, shortening, raw x86, artificial padding, ABI falsehoods or
`TH20_MATCH_EXACT` branches are involved.

## Complete canonical acceptance

Fresh pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` reconstructs all four native COFF relocation
fields with independently original PE-attested destinations. Full
canonical relocation-aware replay:

```text
animation_ribbon_segment_draw_76: exact (76/76 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one new authored-game whole exact function /76 native text
bytes**. The separately exact 140B update and 156B draw now have a
complete exact draw child, but the distinct **538B ribbon segment updater**
called by the update remains source absent and receives zero credit.
Only the one new 76B source/object was cold compiled and replayed;
existing canonical sources and their receipts are unchanged.

```bash
scripts/repo-python scripts/verify-animation-ribbon-segment-draw76-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentDraw76.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
