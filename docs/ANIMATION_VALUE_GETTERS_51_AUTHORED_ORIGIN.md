# CORE/RECON-836 — three original 17B Animation value getters: game-authored origin independently confirmed

This checkpoint promotes **three already whole-native-strict matched
Animation class accessors** from *origin unknown* to *game-authored* using
fresh independent original PE evidence. It does **not** claim to have
reconstructed a new object, shortened a function, created duplicate source,
or recovered the original C++ spelling. It is a **source-origin acceptance
checkpoint** for the locked original Japanese TH20 v1.00a Steamless binary
(SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).

The maintained natural typed definitions remain in the existing
[`src/AnimationGeometry.cpp`](../src/AnimationGeometry.cpp), alongside
the already strict original **5,388B** `Animation::update_geometry` Boss,
**103B** `Animation::position` and **660B**
`Animation::transform_position`. This run makes **zero source/header/compiler
profile/manifest changes** to that exact provider.

## Locked-PE original 17-byte functions and real fields

| Native head | Maintained semantic operation | Original return and actual field |
| --- | --- | --- |
| `0x00437930` | `th20::Animation::rotation_z_value()` | native x87 `FLD dword ptr [eax+0x40]` (`AnimationBase::vector_38.z`) |
| `0x004379A0` | `th20::Animation::scale_y_value()` | native x87 `FLD dword ptr [eax+0x54]` (`AnimationBase::vector_50.y`) |
| `0x004379C0` | `th20::Animation::scale_x_value()` | native x87 `FLD dword ptr [eax+0x50]` (`AnimationBase::vector_50.x`) |

Each original body consists of **exactly 17 bytes /nine real x86
instructions**, starting with `push ebp; mov ebp,esp; push ecx`, then
stores the real member-function ECX receiver, loads it into EAX, returns
the relevant original Animation field through the x87 float stack, and
ends in a real `ret`. None has an original PE HIGHLOW relocation field.
The new
[`scripts/verify-animation-value-getters-native.py`](../scripts/verify-animation-value-getters-native.py)
independently extracts and decodes each complete native body from the
locked original PE. It neither trusts old Ghidra names nor manufactures a
new ABI; the original member receiver, offsets, return protocol, extent
and absence of original relocations are all measured directly.

## Authored ownership, not merely an exact compiler object

These field accessors are custom methods of the original, game-owned
Animation object. C++ compilers and the standard library do not
spontaneously invent accessors for these game-specific offsets and
Animation parent-transform rules. Real physical E8 calls from **three
separate original game-owning functions** confirm the fields' semantic
use in the gameplay renderer/geometry pipeline:

| Native getter | Actual original game callers and E8 instruction sites |
| --- | --- |
| Rotation Z +0x40 | Full 5,993B Animation draw dispatcher: `0x00443C28`, `0x00443C79`; exact 660B Animation transform: `0x00437AB8` |
| Scale Y +0x54 | Exact 5,388B Animation geometry update: `0x00435EB4`, `0x00436346`, `0x00436BFE`; exact 660B transform: `0x00437B19` |
| Scale X +0x50 | Exact 5,388B Animation geometry update: `0x00435E8E`, `0x00436320`, `0x004366CF`, `0x00436BD8`; exact 660B transform: `0x00437AEB` |

**12 real original E8 instruction sites** resolve independently to these
three physical function heads, with no library/runtime imports, proxy
symbols or target-field guessing. The `Animation` game owner and field
layout are also separately established by the whole-native-exact geometry
and transform parent functions. The current `0x00443880` draw Boss remains
**NONEXACT** even though its two real calls to Rotation Z are grounded in
the locked original PE; an exact callee never implies an exact parent.

The earlier [CORE/EXACT-121 geometry document](ANIMATION_GEOMETRY_RECONSTRUCTION.md)
correctly withheld authorship despite already exact machine code: its
native extent proof did not independently classify these tiny accessors.
This report does not assume that old *unknown* label is immutable or
wrong merely because the code matches; it now supplies the specific
original caller/owner provenance needed for authored classification.
Names such as `rotation_z_value` are descriptive reconstruction names,
not assertions about original source identifiers.

The other small `Vector3` constructor/arithmetics in the shared game graph
are **not promoted as part of this checkpoint**. Their original
compiler-generated-versus-game-authored provenance remains separately
open; matching a 46B constructor's machine code alone would not settle
that origin. There is no blanket promotion of unknown-origin functions.

## Fresh existing-source strict replay and accounting

A **fresh pinned-MSVC x86 cold build restricted to the single existing
`src/AnimationGeometry.cpp` provider** (profile `/std:c++20 /Od /Ob0 /GS
/Gy /Zl /arch:SSE2 /fp:strict /sdl /EHsc`) produced a new receipt and
passed **all six** of that source's already configured canonical match
units, not a full-graph cold replay:

```text
animation_geometry: exact (5388/5388 coverage bytes; 5452/5452 compared bytes)
animation_position: exact (103/103 bytes)
animation_parent_position: exact (660/660 bytes)
animation_rotation_z_value: exact (17/17 bytes)
animation_scale_x_value: exact (17/17 bytes)
animation_scale_y_value: exact (17/17 bytes)
Exact replay: 6/6 units, 1 cold objects
```

The **original complete physical bytes** of these three small game methods
are counted exactly once, through their existing 17B manifest units
(`animation_rotation_z_value`, `animation_scale_x_value`,
`animation_scale_y_value`). The function and origin ledgers now classify
only these three unique original heads `matching / authored`, with fresh
per-head provenance; `config/matches.csv` adds precisely three matching
rows. Their previously strict source-present `implemented.csv` mappings
and the entire manifest/object graph are unchanged.

| Live authored metric | Before | After | Delta |
| --- | ---: | ---: | ---: |
| Whole game-authored exact physical functions | 590 | **593** | +3 |
| Strict original game `.text` exact bytes | 196,671 | **196,722** | **+51** |
| Authored-origin reviewed candidates | 602 | **605** | +3 |
| Remaining origin/boundary review candidates | 6,244 | **6,241** | −3 |
| Source-present mappings | 1,239 | **1,239** | 0 |
| Canonical strict units /distinct providers | 1,240 /260 | **1,240 /260** | 0 |

This is **new justified game-authored exact credit on previously
whole-strict original code**, not three new compiled functions, a claim
that the whole executable links/plays, or an increase in source-present
coverage. A 20B `std::round(float)` library wrapper remains explicitly
excluded from authored game credit, demonstrating that the owner
classification is handled independently from successful exact compilation.

## Focused reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-value-getters-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationGeometry.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/progress.py --check
```

**Replay scope is precisely six previously configured exact units from
one provider**, to establish fresh current receipt evidence for origin
promotion. No other source/header/profile/manifest/locked target changed;
no unfiltered cold replay was run. The current 5,993B Animation draw Boss
remains independently **SOURCE-PRESENT/NONEXACT** and the whole exact
3,159B renderer quad-submit Boss remains separately unchanged.
