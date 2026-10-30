# CORE/RECON-923 — complete original 88B ribbon palette and 31B/31B native forwarding chain strict exact

Locked original Japanese TH20 1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original ribbon segment palette `0x0045EC10` is **88B/29-i386**.
Two independently original physical **31B/14-i386** native forwarding
functions operate on its 60 color/60 float-radius cells. The fully
accepted [252B ribbon group configuration Boss](ANIMATION_RIBBON_GROUP_CONFIG_252_STRICT_EXACT.md)
contains three physical calls of the 88B palette function, one for each
segment, with authentic palette values `0xFFFF4040`, `0xFFC040FF`,
`0xFFFFFF40`.

## Original PE evidence, independent of C++/compiler candidates

[`scripts/verify-animation-ribbon-palette88-native.py`](../scripts/verify-animation-ribbon-palette88-native.py)
verifies the three entire original function boundaries and `ret 4`,
all five native E8 site/destination pairs, all original HIGHLOW fields,
real `+0x2C`/`+0x51` `NOP`s, and original float **32.0f** stored at
`0x0056CD94`:

| Original body | Native E8 and data relocation roles |
| --- | --- |
| `0x0045EC10`, **88B/29-i386** | E8 `+0x1B -> 0x004142A0` (`PackedColor` ctor), `+0x27 -> 0x0045DD20` (color forwarding), `+0x4C -> 0x0045DD00` (radius forwarding); actual HIGHLOW `+0x3C -> 0x0056CD94` (32.0f) |
| `0x0045DD20`, **31B/14-i386** | E8 `+0x11 -> 0x0045D430`: tag `0x3C` color forwarding; zero HIGHLOW |
| `0x0045DD00`, **31B/14-i386** | E8 `+0x11 -> 0x0045D360`: tag `0x3C` radius forwarding; zero HIGHLOW |

The 88B source accesses actual segment offset `+0x1E0` for color cells
and `+0x2D0` for radius floats, consistent with the previously whole
exact constructor and 538B segment dynamics Boss.

## Natural C++ and strict canonical acceptance

[`src/AnimationRibbonPalette88.cpp`](../src/AnimationRibbonPalette88.cpp)
implements all three bodies as ordinary C++20, with a real `PackedColor`
value and two natural forwarding methods; the float radius is loaded
from the existing original 32.0f constant, not a literal compiler-inlined
replacement. The color temporary has its own genuine lexical scope,
which naturally emits the original `NOP` at `+0x2C`.

A first ordinary C++ candidate lacking that scope emitted **87B** and
was rejected. A too-narrow call-only scope generated **89B** and was also
rejected. The actual scoped color object yields the full original **88B**
without inline assembly, manual padding or machine-byte copying.

Pinned MSVC x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/EHsc` produces the complete original code and all six real relocation
fields across the three functions:

```text
animation_ribbon_palette_88: exact (88/88 bytes)
animation_ribbon_color_forward_31: exact (31/31 bytes)
animation_ribbon_radius_forward_31: exact (31/31 bytes)
Exact replay: 3/3 units, 1 cold objects
```

The original 88B game-specific method adds **one game-authored exact
function /88 `.text` bytes**. Both 31B forwarding wrappers remain
`origin=unknown/review`; their original generated/compiler/template
ownership has not been proven, so they add **zero** authored-game
byte credit. The separately exact 252B parent receives no extra credit.

### Affected-only verification

```bash
scripts/repo-python scripts/verify-animation-ribbon-palette88-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonPalette88.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
