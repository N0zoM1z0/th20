# CORE/RECON-945 — original 1,486B rotated four-corner projection Boss whole strict exact

The immutable original is Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This updates the historical [nonexact source frontier](ANIMATION_CORNER_AXIS_96_ROTATED_1486_FRONTIER.md),
which correctly identified the original one-byte gap but did not reproduce it.
The complete original **1,486B /372-i386** `0x0043EF20` is **now an
accepted whole original-target-bound strict exact game function**, not a
virtually padded approximation. The source still shares the one legitimate
`NativeAnimationCornerProjector` class and original source-owned 96B
2×3×4 float corner table with its previously exact 985B sibling.

## Corrected source lowering: original +0x41 NOP is natural

[`src/AnimationCornerRotated1486.cpp`](../src/AnimationCornerRotated1486.cpp)
retains the complete meaningful original quad transformation: native
SpriteData and rotation, Angle, sine/cosine, original anchor-mode axes,
window/inherited scaling, four XY transforms and the original Z plane.
It now places the work **after** `Angle angle(...)` in an ordinary nested
lexical lifetime. MSVC naturally emits the genuine original `NOP` at
`+0x41`, immediately after the original Angle(float) E8 `+0x3C`.
A local isolated probe containing the same real scope was compiled first;
its actual unmodified 1,486-byte COFF contribution yielded 372 x86
instructions and **1,398/1,398 identical nonrelocated original bytes**.
No inline assembly, fake stack operation, C++ dead statement, manual NOP,
memory patch or in-memory byte-alignment model is used for admission.

A subtle original relocation correction was also necessary. The true PE
references `window_state.scale` at **`0x005B8818`**, but MSVC's DIR32
field naturally holds the **0x20C0 addend** for
`?window_state@th20@@3UWindowState@1@A`, whose genuine global base is
**`0x005B6758`**. Four relocation manifest entries correctly name the
base, so the original-bound replay resolves `0x005B6758 + 0x20C0`
=`0x005B8818`. Incorrectly treating the physical *field* address as
the *symbol base* produced a false 1,478/1,486 replay result; it was
rejected before correcting the actual manifest evidence. The 985B sibling
already anchored the same original window global base independently.

## Full original and canonical acceptance

[`scripts/verify-animation-corner-rotated1486-strict-native.py`](../scripts/verify-animation-corner-rotated1486-strict-native.py)
uses immutable original PE verification of complete native boundaries,
actual 372 i386 instructions, `sub esp,0x54`, `ret 0x14`, **all 13
physical E8 site/destination pairs**, **all nine original HIGHLOW fields
and physical targets**, plus two independently original parent calls.
It then checks the **real unmodified cold-compiled COFF** contribution,
full 22 relocation offsets and actual native `NOP` (not the historical
in-memory alignment experiment). The original 96B `.rdata` owner remains
separately byte-exact under its existing evidence.

Pinned x86 MSVC C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` and the original-native relocation-aware canonical tool
confirm all **1,486 of 1,486 bytes**:

```text
animation_corner_rotated_1486: exact (1486/1486 bytes)
Exact replay: 1/1 units, 1 cold objects
animation_corner_projection_985: exact (985/985 bytes)
```

The existing 985B sibling was locally cold-replayed independently, not
recredited. This adds **one original authored function and +1,486
`.text` bytes**; there is **no new source-present mapping**, because
this original function was source-present but NONEXACT before this
checkpoint. There is one new strict canonical unit and one new object
provider. The separate 5,993B Animation Draw parent is still NONEXACT,
not linked/playable merely because this important child is now whole exact.

```bash
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationCornerRotated1486.cpp
scripts/repo-python scripts/verify-animation-corner-rotated1486-strict-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationCornerProjection985.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
