# CORE/RECON-935 — original 123B solo ribbon segment palette whole strict exact

Locked Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This independently authored original `0x0045DBF0` palette method is
**123B /39 x86 instructions**, and is physically called by the already
whole exact [182B one-segment configuration Boss](ANIMATION_RIBBON_SOLO_CONFIG_182_STRICT_EXACT.md)
at original instruction `0x0045DB82`. It differs from both the 88B
three-segment ribbon palette and the 120B polygon palette, despite using
some genuinely shared 31B forwarding helpers.

## Original PE facts, not candidate-derived relocation assumptions

[`scripts/verify-animation-ribbon-solo-palette123-native.py`](../scripts/verify-animation-ribbon-solo-palette123-native.py)
reads the immutable original PE to check the complete 123B function,
all 39 decoded instructions through the genuine `ret 4`, **all five
physical E8 instruction locations and targets**, the single real
**HIGHLOW location/target**, original three NOP instructions at
`+0x2C`, `+0x4E`, `+0x74`, and the original 182B parent E8.

| Original field | Native target | Purpose |
| --- | --- | --- |
| E8 `+0x1B` | `0x004142A0` | Real `PackedColor` constructor for caller color |
| E8 `+0x27` | `0x0045DD20` | Independently exact 31B color tag-60 forwarding |
| E8 `+0x42` | `0x00414580` | Actual first packed-color-cell indexed address |
| E8 `+0x49` | `0x0045D650` | Actual `PackedColor::operator=` after native constant `0x80FFFF80` |
| E8 `+0x6F` | `0x0045DD00` | Independently exact 31B radius tag-60 forwarding |
| HIGHLOW `+0x5F` | `0x0056CD94` | Real native 32.0f radius constant |

The two actual member starts are color-array `+0x1E0` and float-radius
array `+0x2D0` within the independently established real 0x3C0-byte
segment. The initial PackedColor uses the caller's color; the genuine
second assignment overwrites the first cell with `0x80FFFF80`.
The original shader/vertex meaning of that packed constant is not
inferred beyond the observed four-byte write.

## Ordinary source and full canonical acceptance

[`src/AnimationRibbonSoloSegmentPalette123.cpp`](../src/AnimationRibbonSoloSegmentPalette123.cpp)
uses the same nominal non-owning `NativeRibbonSoloPaletteView`
member-function ABI as the independently exact 182B caller, actual
`PackedColor` construction and assignment, native `Vector3::operator[](0)`
addressing, and the already established radius 32.0f source.
The C++ block around first-cell assignment is a legitimate temporary
lifetime, not manually inserted NOP/padding: it naturally reproduces the
required original `+0x4E` NOP. Its other two native scope NOPs are also
compiler-emitted, without handwritten assembly or copied code bytes.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /EHsc` emits all six authentic original relocation roles,
exactly 99/99 non-relocated bytes, and full original-target-bound
relocation-aware **123/123 strict exact**:

```text
animation_ribbon_solo_segment_palette_123: exact (123/123 bytes)
Original 182B configuration parent: exact (182/182 bytes)
Exact replay: 2/2 affected units, 2 cold objects
```

Only one new MSVC provider/source was added. The earlier strict
182B config and its saved receipt remain unchanged. This contributes
**one new original game-authored exact function /123 `.text` bytes**.
The already accepted two 31B tag-forwarding physical functions are
not counted again. No full-project cold replay ran; the game remains
neither globally linked nor playable.

```bash
scripts/repo-python scripts/verify-animation-ribbon-solo-palette123-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSoloSegmentPalette123.cpp --source src/AnimationRibbonSoloGroupConfig182.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
