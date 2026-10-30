# CORE/RECON-860 — whole original 971B rounded LINESTRIP Boss strictly exact

The immutable Japanese TH20 v1.00a Steamless original executable is
identified by SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-authored rounded-rectangle outline renderer at
**`0x0043A750`** occupies **971B/255 real x86 instructions** with native
`sub esp,0x28` and `ret 0x20`. Its ECX receiver is the existing
Animation rendering owner; it has eight actual stack arguments. The
larger 5,993B Animation Draw dispatcher calls this physical original
function through real E8 at **`0x004441EF`**, but the enclosing parent
remains independently **SOURCE-PRESENT/NONEXACT**.

The maintained ordinary C++
[`src/AnimationShapeRoundedLine971.cpp`](../src/AnimationShapeRoundedLine971.cpp)
compiles under pinned MSVC 19.44.35211 i386 C++20 flags
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
into the **entire original 971/971B whole-native strict exact body**.
All **255/255 real instruction heads**, native frame/return, **9/9
original E8 site/target pairs**, **18/18 original PE HIGHLOW field
site/target pairs**, and **863/863 non-relocation bytes** match.

## Independent original game PE and real gameplay semantics

[`scripts/verify-animation-shape-roundedline971-native.py`](../scripts/verify-animation-shape-roundedline971-native.py)
reads original game `.text` and actual PE `.reloc` without relying on
source COFF or historical Ghidra names. It verifies the complete 971B
native function and the original main Draw caller, as well as the
physical destinations of all nine E8 instructions:

| Original game call destination | Original role |
| --- | --- |
| `0x004455C0` | Flush pending Animation draw queue |
| `0x00439330` | Original folded polar2 89B geometry |
| `0x00458FA0` | Original 137B XY rotation |
| `0x00438600` | Original 29B angular accumulation |
| `0x004DDF80` | Real Graphics depth-write disable |
| `0x004D9DB0` | Original Graphics render-state forwarding, state23/value8 |
| `0x00446690` | Select original renderer color mode2 |
| `0x00412730` (twice) | Original Graphics device getter and D3D9 calls |

The 18 genuine PE HIGHLOW references comprise real negative pi
`0x0056E0F8`, positive pi `0x0056E0F0`, **eleven** original 2.0f
references `0x0056C8D0`, one 1.0f `0x0056C8CC`, and **four** real
Graphics global `0x005C4D40` references. These actual original
PE fields and targets are fixed independently in the strict unit.

The renderer has a genuine fixed **65,536×20B** typed
`SpriteColoredVertex` pool and one mutable vertex write cursor at
receiver `+0x7D40E80`. It rejects a full buffer using the original
unsigned `JB` capacity test for `segment_count+2`, and requires at
least two segments. It subtracts `2*radius` from the *actual mutable*
width/height parameters before generating the ring. For each of the
`segment_count+1` perimeter vertices, the real source computes
`polar2` at the current angle and radius, adjusts XY by native signed
quarter thresholds, assigns the actual packed perimeter color,
rotates XY, adds world and renderer offsets, and advances the vertex
cursor. Angular steps use `add_angles` with the actual `2*pi/count`
increment and negative-pi start.

Unlike the independently whole-exact
[1,174B rounded TRIANGLEFAN Boss](ANIMATION_SHAPE_ROUNDEDFAN_1174_STRICT_EXACT.md),
this function **does not create a center vertex**. The true final
D3D9 call is `DrawPrimitiveUP(D3DPT_LINESTRIP=3,segment_count,
vertices,20)` with FVF `0x44`, real `SetRenderState(23,8)`, original
Graphics depth-write disable, and renderer counter/cursor updates.
The natural source emits these different gameplay semantics without
copying the sibling's code bytes, adding an unused local or manually
constructing an x86 stub.

## Canonical acceptance, regression scope and exact-game credit

Only one new native match unit, `animation_shape_roundedline_971` in
[`config/match-units.toml`](../config/match-units.toml), owns this
physical original body. Its pinned source object/receipt is
`build/core860-canonical/AnimationShapeRoundedLine971.obj`; it has
**nine real REL32/E8 + eighteen real DIR32/HIGHLOW** original
source-symbol/physical-offset/target roles. Whole strict replay:

```text
animation_shape_roundedline_971: exact (971/971 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The provisional renderer member's return declaration was corrected
from `void` to the real native `std::int32_t`/`ret 0x20` ABI.
Previously accepted sources that include the changed
`AnimationDrawDetailedOwner.hpp` must be recompiled and strictly
replayed **by affected source only**, along with a noncanonical
focused source-role regression for the still NONEXACT 5,993B parent.
No unfiltered whole-graph cold replay is run.

The new game-authored credit is **one physical original 971B function**,
not the already exact rounded fan, Geometry/Graphics callees or enclosing
Draw dispatcher. See the separately verified
[755B simple fan Boss](ANIMATION_SHAPE_SIMPLEFAN_755_STRICT_EXACT.md)
for the companion checkpoint.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-roundedline971-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeRoundedLine971.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
