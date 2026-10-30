# CORE/RECON-918 — complete 89B ribbon group ctor and native 20B/49B destructor chain

> **CORE/RECON-919 follow-up:** The separate original **156B C++17
> diagnostic allocation factory at `0x0045E5D0`** is now independently
> [whole 156/156 strict exact](ANIMATION_RIBBON_GROUP_FACTORY_156_STRICT_EXACT.md).
> A pointer-semantic type for the observed zero word at `+0xB5C` naturally
> restores the factory's genuine `/sdl` auto-class initialization without
> changing the 89B constructor or 20B/49B destructor acceptance.


Locked Japanese TH20 Steamless v1.00a SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This batch reconstructs an actual **0xB60-byte** polymorphic ribbon group
from one ODR-consistent C++20 class, without a fake vptr, a `novtable`
annotation, a second contradictory class definition, machine bytes or
inserted padding. The original `0x0045E6D0` constructor is **89B /25 i386**.
The compiler also reproduces the **20B** shared physical ordinary destructor
and **49B** ribbon scalar-deleting wrapper as independently strict units.

## Independently authenticated original PE

[`scripts/verify-animation-ribbon-group-ctor89-native.py`](../scripts/verify-animation-ribbon-group-ctor89-native.py)
checks all three complete function extents, native instruction counts,
physical E8 and HIGHLOW positions and targets, true returns, object
size, and the six original PE-relocated vtable slots:

| Original body | Complete physical native roles |
| --- | --- |
| `0x0045E6D0`, **89B/25-i386** | E8 `+0x0E -> 0x00446B60` (AnimationCallback base), `+0x22 -> 0x0045E670` (whole-exact 78B three-segment array), `+0x3E -> 0x00422D90` (Timer); genuine HIGHLOW `+0x18 -> 0x0056EDDC` (derived virtual table) |
| `0x0045C2A0`, **20B/10-i386** | E8 `+0x0A -> 0x00446BA0` (AnimationCallback base destructor), one genuine `nop`, no HIGHLOW, `ret` |
| `0x0045E730`, **49B/18-i386** | E8 `+0x0A -> 0x0045C2A0` and `+0x20 -> 0x0054278D` (sized delete), pushes actual `0xB60`, no HIGHLOW, `ret 4` |

Real table `0x0056EDDC` points to the **49B deleting wrapper**,
independently whole-exact [140B update](ANIMATION_RIBBON_GROUP_UPDATE_140_STRICT_EXACT.md)
and [156B draw](ANIMATION_RIBBON_GROUP_DRAW_156_STRICT_EXACT.md), and three
inherited/folded slots. The original 89B constructor writes the real
vtable and initializes a native float control at `+0xB48`, Timer at
`+0xB4C`, and a final zeroed four-byte member at `+0xB5C`.
The last member is not padding guessed to shape the compiler: it is a
literal original word write and makes the authentic object **0xB60**.

## C++ source and complete canonical strict acceptance

[`src/NativeRibbonPolygonGroup.hpp`](../src/NativeRibbonPolygonGroup.hpp)
now contains one typed `std::array<NativeRibbonSegment,3>` subobject at
`+0x08` and the actual named control/Timer/terminal word fields. Its
constructor source in [`src/AnimationRibbonGroupCtor89.cpp`](../src/AnimationRibbonGroupCtor89.cpp)
uses ordinary base and member initialization. The compiler emits an
**implicit derived destructor** naturally; no custom empty destructor or
manual virtual table/stack manipulation is involved. Typed updates in
the two previously exact ribbon update/draw sources still produce their
respective whole original machine code.

Pinned MSVC 19.44 x86 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl` emits a single object with these independently
canonical relocation-replayed original contributions:

```text
animation_ribbon_group_ctor_89: exact (89/89 bytes)
animation_ribbon_group_ordinary_dtor_20: exact (20/20 bytes)
animation_ribbon_group_scalar_delete_49: exact (49/49 bytes)
Exact replay: 3/3 units, 1 cold objects
```

The shared-header change required **seven existing ribbon source
providers** (19B array end, 140B update, 156B draw, 76B LINESTRIP,
538B dynamics, 60B segment ctor, and 78B array ctor) to be cold
recompiled. All **7/7** independently remained strict exact, with no
whole-graph cold replay. An overlapping draft unit declaration was
preserved in ignored `.analysis/gptweb-ribbon-group89/alternate-ctor89-unit.toml`
before deduplicating the canonical manifest; no meaningful dirty work
was silently discarded.

**Authorship credit:** the original game-specific 89B constructor is one
new authored exact game head, **+89 original `.text` bytes**. The 49B
scalar-deleting wrapper and 20B ordinary destructor are authentic strict
exact native compiler contributions but have `origin=unknown/review` and
**zero additional authored-game code credit**. The 20B physical head
is called both by the original ribbon wrapper `0x0045E730` and the
previously exact polygon deleting wrapper `0x0045F5A0`; this may
reflect historical template folding/COMDAT identity. Its unique
original C++ type cannot be proven from the identical native body.

Earlier isolated `__declspec(novtable)` tests yielded a structurally
matching 20B polygon destructor but broke the previously accepted
113B polygon group constructor's real vptr. This complete ribbon class
shows a different, consistent natural source for the same *physical*
20B native destructor, **not** permission to apply conflicting
`novtable` declarations to the earlier polygon class. The polygon
class's separate /Od ordinary destructor source-identity/ODR issue
still needs proper reconciliation.

### Affected-only reproduction

```bash
scripts/repo-python scripts/verify-animation-ribbon-group-ctor89-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonGroupCtor89.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationRibbonSegmentArrayEnd19.cpp --source src/AnimationRibbonGroupUpdate140.cpp --source src/AnimationRibbonGroupDraw156.cpp --source src/AnimationRibbonSegmentDraw76.cpp --source src/AnimationRibbonSegmentDynamics538.cpp --source src/AnimationRibbonSegmentCtor60.cpp --source src/AnimationRibbonSegmentArrayCtor78.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
