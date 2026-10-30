# CORE/RECON-905 — original polygon segment 60B constructor and 75B C++ array helper whole-native exact

> **CORE/RECON-906 update:** The native [78B three-segment `std::array` constructor](ANIMATION_POLYGON_SEGMENT_ARRAY_78_STRICT_EXACT.md) is now whole strict exact. The 60B `noexcept` segment ctor uses its natural no-`/EHsc` profile; the 75B color-cell array ctor has moved to the separate normal `/EHsc` C++20 source provider. Both remain whole exact, with 45/45 affected units. Historical prior-source/provider counts below are checkpoint data only.

The locked Japanese TH20 v1.00a Steamless target is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire **game-owned 60B /20-i386 polygon segment constructor at
`0x0045F3C0`** and a complete **75B /27-i386 array default-construction
helper at `0x0045F210`** are now strict canonical relocated exact from one
natural maintained C++20 translation unit. The 75B helper includes five
actual original `INT3` alignment bytes in its **80/80B** full COFF comparison;
these do not inflate physical game-code credit or represent instructions
executed within its original 75B function body.

## Independently observed source type, not the previous byte blob

The original segment constructor `0x0045F3C0` takes a genuine pointer to a
`0x3D4`-byte segment and does **three native E8 calls** at its real sites:

| E8 site | Original physical target | Role |
| --- | --- | --- |
| `+0x0A` | `0x0045F260` | 61 × 8B vector array default constructor |
| `+0x18` | `0x0045F210` | 61 × 4B word/color cell array constructor |
| `+0x2D` | `0x00544760` | Actual CRT `memset` for 62 float radii |

This is consistent with the independently recovered whole-exact 827B
polygon dynamics Boss. The original record is **61 `Vector2` coordinates
(0x1E8B), 61 four-byte words (0xF4B) and 62 float radii (0xF8B)**, with
field starts `+0`, `+0x1E8`, `+0x2DC` and `sizeof=0x3D4`.

The original 75B `0x0045F210` array constructor has real
**`+0x33 → 0x0040BC20` E8** to the compiler array constructor loop,
and **three genuine PE HIGHLOW relocations**: `+0x06 → 0x00567600`
(EH handler), `+0x13 → 0x005B25C0` (security cookie), and
`+0x27 → 0x00425CC0` (4B element default constructor callback).
The 4B callback is a physically folded zero-default constructor already
strictly accepted at `0x00425CC0` under an `AnimationHandle` nominal owner.
The **original C++ source spelling of these four-byte polygon color cells
remains unproven**: a common 4-byte trivial-zero constructor can be shared
between color and handle types. Accordingly, the maintained typed
`std::array<AnimationHandle,61>` is an ABI/codegen-compatible 4B cell view,
**not evidence that the rendered color bytes are semantically animation
identifiers**. Color/rendering operations still treat this region as packed
32-bit color words. Do not duplicate credit for the folded element ctor.

The separate `0x0045F260` **75B** `Vector2` array constructor is original-PE
authenticated by the same script, including `+0x33 → 0x0040BC20` and
three original HIGHLOW fields with vector ctor callback at `0x004398A0`.
Its current C++20 `std::array<Vector2,61>` compiler instantiation is **not
exact** (33B), so **no strict unit or credit for this 75B function** is
claimed. Likewise the original **78B three-segment array constructor
`0x0045F2B0`** and enclosing **113B derived polymorphic group constructor
`0x0045F340`** are original-PE mapped but remain independently unfinished.

[`scripts/verify-animation-polygon-segment-construction-native.py`](../scripts/verify-animation-polygon-segment-construction-native.py)
reads only the immutable PE, verifies all five entire original constructor
boundaries/return instructions, their complete E8 site/true destination pairs,
all real HIGHLOW fields, the physical five-INT3 gap after `0x0045F210`, and
the original group vtable entries (49B destructor, exact 140B tick, exact
233B draw). Native source names are not assumed from Ghidra alone.

## Natural source and exact whole compiled contributions

The canonical original class declaration
[`src/NativePolygonSegmentSlot.hpp`](../src/NativePolygonSegmentSlot.hpp)
replaces its older opaque 980B byte array with the three independently
attested `std::array` fields. The original game 60B source is simply:

```cpp
NativePolygonSegmentSlot::NativePolygonSegmentSlot() : radius{} {}
```

The other two nontrivial `std::array` members are implicitly default
constructed. This is **not** an invented manual `memset`: the genuine
62-float `radius{}` value initialization naturally emits the original
`0xF8`-byte zeroing call. Value-initializing all three arrays would
incorrectly add two early `memset` calls and was **rejected** by direct
MSVC source experiments. The native original method contains no `HIGHLOW`.

The pinned C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
object `build/core905-canonical/AnimationPolygonSegmentCtor60.obj` produces
strict zero-difference relocated comparisons:

```text
animation_polygon_segment_ctor_60: exact (60/60 bytes)
animation_polygon_color_array_ctor_75: exact (75/75 coverage bytes; 80/80 compared bytes)
Exact replay: 2/2 units, 1 cold objects
```

The 60B original function contributes **one new game-authored whole native
code head /60 original `.text` bytes**, once, through `config/matches.csv`.
The 75B array helper is separately whole exact but remains
`origin=unknown / disposition=review` and is **not counted as authored
game code**. Its five real following `CC` bytes are not game-authored
executed code and do not become additional match coverage.

## Protecting the large existing exact parent

The actual tracked source-include closure for
`NativePolygonSegmentSlot.hpp` contains **four previously canonical
source providers and 42 earlier whole-exact units**: the polygon group
owner (4), palette/registry/tick provider (5), 827B dynamics and
range/STL helpers (32), and C++17 156B group factory (1). After the
typed-header edit, these four providers were **cold rebuilt** and all
**42/42 strict native units remained exact**, including the complete
827B game Boss, the 156B factory and 233B/296B group parents. The
new ctor and color-array helper were compiled from one fifth source
provider. Compiler receipt input-hash inventories contain more than
actual transitive `#include` dependencies, so they are not mistaken
for a justification to replay unrelated providers. No unfiltered
full cold replay was performed.

The new snapshot is **1,331 source-present mappings /1,330 strict
canonical units /302 native object providers** and **639 game-authored
whole original exact functions /234,689 native `.text` bytes**. The game
is not yet linked or playable.

### Bounded verification

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-segment-construction-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonSegmentCtor60.cpp --source src/AnimationPolygonMotionGroup233.cpp --source src/AnimationPolygonPalette120.cpp --source src/AnimationPolygonDynamics827.cpp --source src/AnimationPolygonMotionGroupFactory156.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_segment_ctor_60
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_color_array_ctor_75
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
