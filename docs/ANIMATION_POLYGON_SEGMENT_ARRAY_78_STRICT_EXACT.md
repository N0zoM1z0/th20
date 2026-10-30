# CORE/RECON-906 — complete original 78B polygon segment-array constructor strictly exact

The locked Japanese TH20 Steamless 1.00a target SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The complete physical original **`0x0045F2B0` 78B /27-i386 `std::array<NativePolygonSegmentSlot,3>` default constructor** is now canonical **78/78 native bytes exact**, with an independently verified **83/83 complete COFF contribution** incorporating five genuine following original `INT3` bytes. It is a *separate* function from the already whole strict exact 60B segment constructor and 75B color-cell array constructor; it does **not** make the still-open 113B group constructor exact.

## Original-only native ground truth

The previously independent [`scripts/verify-animation-polygon-segment-construction-native.py`](../scripts/verify-animation-polygon-segment-construction-native.py) reads only original PE `.text` and `.reloc`, with no COFF candidate. It authenticates the entire original 78B function and original E8 at `+0x36` to native `0x0040BC20`, plus three immutable original PE HIGHLOW absolute references:

| Field position | Original physical destination | Real role |
| --- | --- | --- |
| `+0x06` DIR32 | `0x00567600` | C++ EH handler |
| `+0x13` DIR32 | `0x005B25C0` | MSVC security cookie |
| `+0x27` DIR32 | `0x0045F3C0` | Now-whole-exact 60B segment ctor callback |
| `+0x37` REL32 | `0x0040BC20` | Native `eh vector constructor iterator` |

The original passes `0x3D4` element stride, `3` elements and the above real constructor callback. Its own final `ret` is at `+0x4D`. The next five physical bytes, `+0x4E..+0x52`, are real original `CC` alignment bytes, not executable body or extra authored-game credit. These fields and the 3×0x3D4 record count are verified directly in the locked PE.

## Natural C++ type and compiler-profile convergence

The actual group source header [`src/NativePolygonMotionGroup.hpp`](../src/NativePolygonMotionGroup.hpp) now uses **`std::array<NativePolygonSegmentSlot,3>`** as the real `NativePolygonSegmentArray::segments` member. The original 23B indexed pointer helper is preserved by its genuine native-stride pointer calculation (`reinterpret_cast<NativePolygonSegmentSlot*>(this) + index`) and the 19B end-pointer helper still uses the native `sizeof(segments)` stride. `NativePolygonSegmentArray()` actually constructs that C++20 array in [`src/AnimationPolygonSegmentArrayCtor78.cpp`](../src/AnimationPolygonSegmentArrayCtor78.cpp); it is not a copied machine-code stub or fabricated alignment. The same source includes a small placement-construction entry point for the actual 61-cell color array subobject so the existing compiler-generated 75B array constructor retains one complete source/COFF provider. **Only the genuine 78B and 75B original template instantiations**, not those extra scaffolding entry points, are entered into strict units.

A crucial compiler ABI detail: the original `NativePolygonSegmentSlot()` has a **`noexcept`** constructor declaration. In C++20 `/EHsc`, that declaration makes the genuine `std::array<NativePolygonSegmentSlot,3>::array()` emit a full EH-aware 83B COFF contribution. The Segment constructor's own original 60B body has no EH prologue; it is independently compiled using the same pinned compiler **without `/EHsc`**, which naturally reproduces the original 60/60 relocated bytes. The color-cell array constructor, using the compiler's true C++20 EH instantiation, is compiled from the 78B source provider **with `/EHsc`** and remains whole 75/75 native exact plus its original five-INT3 comparison bytes. There are no conflicting duplicate definitions of the 60B constructor across compiler objects.

A more invasive alternative — declaring the globally shared `Vector2()` constructor `noexcept` — also produced 75B/75B native Vector2 array syntax in bounded experiments, but that header has a very broad transitive provider closure and was **not** changed. This exact 78B admission instead touches the polygon owner source closure only. The other original `0x0045F260` 75B Vector2 array constructor remains NONEXACT and is not credited here.

## Canonical replay and credit policy

The two accepted constructor-related units are:

```text
animation_polygon_color_array_ctor_75: exact (75/75 coverage bytes; 80/80 compared bytes)
animation_polygon_segment_array_ctor_78: exact (78/78 coverage bytes; 83/83 compared bytes)
```

The maintained compiler object `build/core906-canonical/AnimationPolygonSegmentArrayCtor78.obj` owns both exact complete source contributions, along with its fresh compiler receipt. The full affected source closure was replayed, **45/45 strict units across six cold objects**: the 60B segment ctor, 75B color array, new 78B three-segment array, 827B dynamics Boss plus 31 range helpers, 156B factory, exact 233B/296B group owners and exact 120B palette all pass without a regression. There is **no full-project cold replay**.

The 78B body is compiler-generated C++20 array construction. Original authorship remains `unknown/review`, and this **78B adds no authored-game `.text` byte credit**. The authored whole-exact total remains **639 heads /234,689 original bytes**, with **1,332 source-present mappings /1,331 canonical strict units /303 pinned object providers**. The 113B polymorphic group parent and 75B vector array constructor are still separately open. The game is not yet globally linked or playable.

### Scoped reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-segment-construction-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonSegmentCtor60.cpp --source src/AnimationPolygonSegmentArrayCtor78.cpp --source src/AnimationPolygonMotionGroup233.cpp --source src/AnimationPolygonPalette120.cpp --source src/AnimationPolygonDynamics827.cpp --source src/AnimationPolygonMotionGroupFactory156.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_segment_array_ctor_78
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
