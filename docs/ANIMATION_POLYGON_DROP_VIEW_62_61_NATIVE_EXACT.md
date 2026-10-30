# CORE/RECON-900: TH20 polygon dynamics typed ranges and four complete helper matches

> **Later CORE/RECON-901 result:** The enclosing 827B dynamics Boss is now [whole strict exact](ANIMATION_POLYGON_DYNAMICS_827_STRICT_EXACT.md). The 768B NONEXACT status and 637-game-function counts below describe this intermediate checkpoint only.

The immutable Japanese TH20 Steamless 1.00a target is identified by SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original 827-byte polygon dynamics Boss at `0x0045F670` is **source-present,
NONEXACT**. Its two real C++20 `std::views::drop(1)` ranges and correct
`std::array` sizes are recovered in `src/AnimationPolygonDynamics827.cpp`.
Four distinct 16/93-byte helper functions are now **whole-native exact**.

## Original PE findings independently reproduced

`scripts/verify-animation-polygon-drop-ranges-native.py` authenticates the
original 827B/237-i386 parent and its **31 real E8 sites and ten PE HIGHLOW
fields**, the two original full 16B native `std::array::size()` functions,
and both original full 93B `std::ranges::drop_view::begin()` functions' four
true E8 locations/targets. These are target-byte observations, not Ghidra
source names or reconstructed COFF bytes.

| Original record offset | Recovered C++20 field | Extent |
| --- | --- | ---: |
| `+0x000` | `std::array<Vector2,61> perimeter` | `61 × 8 = 488B` |
| `+0x1E8` | `std::array<uint32_t,61> colors` | `61 × 4 = 244B` |
| `+0x2DC` | `std::array<float,62> radius` | `62 × 4 = 248B` |
| **Total** | Original segment | **980B (`0x3D4`)** |

`0x0045FFE0` returns `0x3E` (62) and `0x0045FFF0` returns `0x3D`
(61); both are entire 16-byte original functions with no E8 or PE HIGHLOW.
Those true native array-size functions refute the earlier plain-loop
60-element radius hypothesis. The first dropped range iterates radii
**1..61**, and the second iterates vertices **1..60**. The function copies
the value of vertex 1 into vertex 60 at exit. The original `std::array`
indexing has separate physical generic functions: certain instantiations
produce identical native bytes at already tracked `0x00414580` and
`0x0045D670`. That **does not prove** the original library vs game authorship
or justify changing their earlier game credit without independent review.

Original `drop_view::begin()` E8 targets are:

| Original E8 field | Radius range at `0x0045FDA0` | Vertex range at `0x0045FE00` |
| --- | --- | --- |
| `+0x0E` | `0x0045EF50` | `0x0045EFD0` |
| `+0x24` | `0x0045F140` | `0x0045F140` |
| `+0x39` | `0x0045EEF0` | `0x0045EF70` |
| `+0x4F` | `0x0045F4C0` | `0x0045F4F0` |

The actual `std::views::drop(1)` expression, compiled under pinned MSVC
x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
generates the same full native code, exact original relocation site types,
and independently proven original callee roles for both 93B helpers.
No arbitrary machine-code padding or target bytes were inserted.

## Native exact receipts (stdlib/compiler origin still unproven)

| Unit | Physical native head | Complete exact bytes |
| --- | --- | ---: |
| `animation_polygon_radius_size_16` | `0x0045FFE0` | 16/16 |
| `animation_polygon_vertex_size_16` | `0x0045FFF0` | 16/16 |
| `animation_polygon_radius_drop_begin_93` | `0x0045FDA0` | 93/93 |
| `animation_polygon_vertex_drop_begin_93` | `0x0045FE00` | 93/93 |

`nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source
src/AnimationPolygonDynamics827.cpp` builds **one** locked-compiler object,
`build/core900-canonical/AnimationPolygonDynamics827.obj`, with its fresh
receipt, then accepts **4/4 strict complete canonical relocated units**:
**218B of additional exact C++20 native helper code**. Each is
`origin=unknown / disposition=review` and is **not game-authored credit**.
The previous seven iterator helpers retain their own separate proofs.

The changed parent improves from **513B /137 x86 /7 E8** to **768B /225
x86 /31 E8**. The original is **827B /237 x86 /31 E8 /10 HIGHLOW**.
Equal E8 count and recovered loop structure are **not** whole-parent
exactness. Differences include the original stack alignment and source
expression/local lifetimes. Do not add the parent to strict units or
`config/matches.csv` before a full correct canonical comparison.

Live inventory at this checkpoint: **1,301 source mappings /1,299 strict
units /300 object providers** and **637 original hand-authored exact game
functions /233,802 physical code bytes**, unchanged in the authored total.
The game is not globally linked or playable.

### Bounded verification

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-drop-ranges-native.py
scripts/repo-python scripts/verify-animation-polygon-dynamics827-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonDynamics827.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

Only the affected source and its four strict units need cold replay. No
unfiltered whole-graph build or cold replay is warranted by this change.
