# CORE/RECON-902 — 27 original C++20 polygon `drop_view` helper functions strictly exact

This checkpoint follows the [complete exact original 827B polygon dynamics
Boss](ANIMATION_POLYGON_DYNAMICS_827_STRICT_EXACT.md) under the immutable
Japanese TH20 v1.00a Steamless target SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original Boss is **already whole exact**. This investigation follows
its 62-float/61-vertex dropped-range template calls into their original
native C++20/STL closure; it does not re-credit the 827B parent.

## Separate original-PE call graph and binary evidence

[`scripts/verify-animation-polygon-drop-closure-native.py`](../scripts/verify-animation-polygon-drop-closure-native.py)
attests **27 distinct complete original function extents /811 physical `.text`
bytes**, from original PE `.text` and `.reloc`, independent of COFF or source.
Its frozen original-only facts verify each full instruction extent through
the original `ret`, total **24 genuine E8 instruction site/absolute-target
pairs**, **zero original HIGHLOW** data relocations across these 27 bodies,
and the immutable game target fingerprint. In addition to the original 827B
Boss, two already-strict exact 93B drop-view `begin` wrappers provide
physical original callers. Their actual four E8 call sites apiece lead to
these new library functions, which recursively reach six levels of
array/reference-view iterator APIs and the shared `std::min<int>`.

| Original physical head | Complete body | Native E8 | MSVC C++20 semantic candidate |
| --- | ---: | ---: | --- |
| `0x0045EDF0` | 30B /12 x86 | 1 | 62-float array begin CPO |
| `0x0045EE30` | 23B /9 x86 | 1 | 62-float array size CPO |
| `0x0045EE90` | 30B /12 x86 | 1 | 61-vertex array begin CPO |
| `0x0045EED0` | 23B /9 x86 | 1 | 61-vertex array size CPO |
| `0x0045EEF0` | 30B /12 x86 | 1 | 62-float ref-view begin CPO |
| `0x0045EF30` | 23B /9 x86 | 1 | 62-float ref-view size CPO |
| `0x0045EF50` | 17B /8 x86 | 1 | 62-float range distance |
| `0x0045EF70` | 30B /12 x86 | 1 | 61-vertex ref-view begin CPO |
| `0x0045EFB0` | 23B /9 x86 | 1 | 61-vertex ref-view size CPO |
| `0x0045EFD0` | 17B /8 x86 | 1 | 61-vertex range distance |
| `0x0045F140` | 45B /19 x86 | 0 | shared `std::min<int>` |
| `0x0045F170` | 30B /13 x86 | 0 | 62-float const iterator ctor |
| `0x0045F190` | 30B /13 x86 | 0 | 61-vertex const iterator ctor |
| `0x0045F1B0` | 33B /15 x86 | 1 | 62-float mutable iterator ctor |
| `0x0045F1E0` | 33B /15 x86 | 1 | 61-vertex mutable iterator ctor |
| `0x0045F4C0` | 48B /19 x86 | 2 | 62-float iterator advance-by-count |
| `0x0045F4F0` | 48B /19 x86 | 2 | 61-vertex iterator advance-by-count |
| `0x0045F520` | 32B /14 x86 | 0 | 62-float const iterator `+=` |
| `0x0045F540` | 32B /14 x86 | 0 | 61-vertex const iterator `+=` |
| `0x0045F560` | 28B /12 x86 | 1 | 62-float iterator `+=` forwarder |
| `0x0045F580` | 28B /12 x86 | 1 | 61-vertex iterator `+=` forwarder |
| `0x0045FD60` | 30B /13 x86 | 1 | 62-float array `begin` |
| `0x0045FD80` | 30B /13 x86 | 1 | 61-vertex array `begin` |
| `0x0045FE60` | 34B /15 x86 | 1 | 62-float ref-view `begin` |
| `0x0045FE90` | 34B /15 x86 | 1 | 61-vertex ref-view `begin` |
| `0x00460000` | 25B /12 x86 | 1 | 62-float ref-view `size` |
| `0x00460020` | 25B /12 x86 | 1 | 61-vertex ref-view `size` |


The explicit `std::array<float,62>` and `std::array<Vector2,61>`
instantiations emitted from the **same maintained real 827B Boss source**
(`src/AnimationPolygonDynamics827.cpp`) supply each of the 27 functions.
For every individual body, the complete candidate COFF contribution length,
all non-relocation bytes, each REL32 site/type and the independent original
absolute callee target were checked before admission. The first-level
`std::views::drop(1)` factory (`0x0045EFF0`, native 29B vs candidate 20B)
and range pipe (`0x0045F010`, native 59B vs candidate 24B) **do not match**:
these are specifically **not** admitted and their old source/provenance is
still unresolved. The generic `0x0040C080` helper is outside this bounded
closure; its presence as a genuine called target is not conflated with
successful byte acceptance here.

## Canonical compiler acceptance and non-authorship

The manifest `config/match-units.toml` now contains 27 separate
`polygon_std_range_XXXXXXXX` units, one per independent original physical
function head. Each has the full original extent, actual compiler decorated
symbol, independently captured original PE E8 destination and original
relocation offset/type; there is **no copied original target byte data**.
A fresh pinned MSVC x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` cold build of **one** source provider produces
`build/core900-canonical/AnimationPolygonDynamics827.obj` and its receipt.
Replaying all affected units gives **32/32 full canonical exact**:
27 new helpers, the four previously exact `16B/93B` helpers, and the
827B authored game Boss.

The newly accepted helper functions are **811B of unique original code**,
not duplicated physical addresses or parent-body credit. All 27 remain
`origin=unknown / disposition=review`, with an explicit nominal mapping
name and the real COFF template symbol recorded separately. Their semantics
strongly suggest compiler/STL template instantiations, but the executable has
no independent original author symbols to prove source ownership; therefore
**none of the 811B is added to authored game `.text` totals**.

Live progress after this batch: **1,328 source-present mappings /1,327
canonical strict units /300 object providers**; **638 authored-game
whole-exact functions /234,629 original bytes** (unchanged). The game is
not yet linked or playable.

### Narrow reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-drop-closure-native.py
scripts/repo-python scripts/verify-animation-polygon-drop-ranges-native.py
scripts/repo-python scripts/verify-animation-polygon-dynamics827-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonDynamics827.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Only the actually affected source is cold-compiled. There is **no**
unfiltered or full-graph cold replay. The still-NONEXACT 104B outline
caller and 1,486B rotated-corner Boss were separately investigated in
private diagnostic probes without modifying their maintained source or
inventing instruction padding.
