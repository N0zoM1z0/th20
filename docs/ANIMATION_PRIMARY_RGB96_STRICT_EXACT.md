# Animation primary RGB Color3 interpolation: 96 native bytes strict exact

The genuine TH20 v1.00a Japanese Steamless `Animation` method at
`0x00438D50` is a complete **96-byte** game function called from the still
open 39,470-byte Animation VM. Its source is now maintained as natural C++20
`NativeAnimationColorConfigView::interpolate_primary_rgb_438d50` in
`src/AnimationRGBInterpolation96.cpp`. It uses the true existing
`AnimationBase::interpolation_e0` (`Animation+0xE0`) and constructs two
independent `IntegerTriple` values from its two `Color3` inputs before
calling `IntegerTripleInterpolation::begin` with the original frames and
curve mode.

The original physically has **five** exact relocations:

| Field | Role |
| --- | --- |
| `+0x07` DIR32 | MSVC security cookie `0x005B25C0` |
| `+0x1B` REL32 | `IntegerTriple(Color3)` at `0x00429180` |
| `+0x27` REL32 | A second `IntegerTriple(Color3)` at `0x00429180` |
| `+0x4B` REL32 | Triple interpolation begin at `0x004395D0` |
| `+0x56` REL32 | Security cookie check `0x005429EE` |

Pinned MSVC 19.44 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` produces the complete native 96/96-byte body, including
**76/76** ordinary bytes and all five original relocation positions,
symbol identities, and target addresses. No instructions, filler or duplicate
runtime object are invented. The source reuses the already canonical borrowed
`NativeAnimationColorConfigView`, which is only a declaration of methods on
the live `Animation` owner. The previously exact 132B and 142B color
interpolation methods share this declaration and retain their own original
physical heads and complete matches.

Reproduce with only the affected translation units:

```sh
scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRGBInterpolation96.cpp
scripts/repo-python scripts/replay-exact-units.py --source src/AnimationColorConfig274.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

The newly accepted 96 bytes are distinct game-authored `.text`. Previously
exact Color3 conversion and triple interpolation callees receive no duplicate
credit; the enclosing Animation VM remains **NONEXACT/source-absent**.
