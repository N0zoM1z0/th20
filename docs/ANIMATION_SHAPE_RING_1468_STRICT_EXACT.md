# CORE/RECON-853 — whole original 1,468B Animation shape-ring Boss strict native exact

The immutable original Japanese TH20 v1.00a Steamless executable has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real game-authored polygon ring/strip renderer at **`0x0043AB20`** is a
complete **1,468B /387 native i386** method with original **`sub esp,0x2C`**
and real `ret 0x28` returning EAX=0. The original enclosing 5,993B
Animation Draw dispatcher calls that actual head at **three independent
E8 sites** `0x00444304`, `0x0044442C` and `0x00444558`.

A single real source function
[`src/AnimationShapeRing1468.cpp`](../src/AnimationShapeRing1468.cpp)
now yields **1,468/1,468 whole-native strict exact** with ordinary pinned
MSVC x86 C++20 compilation, **all 387 actual x86 heads**, **11/11 real
E8 positions and original targets**, **26/26 original PE HIGHLOW physical
field positions and original data targets**, and **1,320/1,320 original
non-relocation bytes**. This is a whole-game Boss function, not a short
leaf or a prefix of the original executable.

## Original PE-only proof of the entire body

[`scripts/verify-animation-shape-ring-1468-native.py`](../scripts/verify-animation-shape-ring-1468-native.py)
reads all 1,468 immutable original .text bytes and the actual PE `.reloc`
directory; Capstone independently decodes 387 instructions through the
actual return. The verifier freezes all **11 original E8 site/destination
pairs**, all **26 real HIGHLOW site/target pairs**, and the three actual
main Draw callers **before** using any newly compiled COFF object.

| Independently attested native role | Source/strict result |
| --- | --- |
| Whole original 1,468B/387 i386; `0x2C` local frame/RET 0x28 | **1,468/1,468 bytes, 387/387 instructions, exact native frame and ABI** |
| 11 direct E8 original physical call sites | **11/11 offsets and independently mapped original callee destinations** |
| 26 real original PE HIGHLOW data fields | **26/26 offsets/target values and authentic original source owners** |
| 18 float 2.0f references | Exact original native `0x0056C8D0` at all 18 positions |
| Two float 1.0f references | Original `0x0056C8CC`, reciprocal W for both ring vertices |
| Positive/negative π | Original immutable float `+3.141592741` `0x0056E0F0` and `−3.141592741` `0x0056E0F8` |
| Four Graphics live owner references | Exact actual original `0x005C4D40` locations, not guessed imports |
| Complete body non-relocation bytes | **1,320/1,320 bytes equal** before the 37 actual original COFF fields are replayed |

The genuine original 11 E8 roles are: one game AnimationPool draw flush
`0x004455C0`; two physical calls to **one already established 89B polar
Vector2/Vector3 folded helper** `0x00439330`; two to the original whole
137B typed Vector2 XY rotation `0x00458FA0`; one to native 29B
`add_angles` `0x00438600`; one to already exact Graphics depth-disable
`0x004DDF80`; one to actual game Graphics device
`SetRenderState` forwarding member `0x004D9DB0` (whose historical
identifier is still provisional); one to real renderer color-mode
`0x00446690` and two to the original Graphics D3D9 device getter
`0x00412730`. No imported/CRT helper or already counted folded geometry
body receives extra authored-game byte credit here.

## Important corrected source semantics and original MSVC codegen

The original renderer owns a **fixed capacity array of 65,536 genuine
20B `SpriteColoredVertex` records** starting at receiver
`this+0x7C00E80`, with an advancing live write-cursor pointer stored at
`this+0x7D40E80`. The original unsigned capacity comparison is not
merely `capacityBytes > count`: it calculates `(count+2)*20 + cursor`
and compares this against `&vertices[65536]` using the true unsigned
x86 `JB` branch. The natural C++ typed array address and explicit
parenthesized count calculation emit the exact original
`MOV EAX,0x14; SHL EAX,0x10` endpoint arithmetic. Earlier pointer
arithmetic that flattened constants generated different instructions
and made original E8 sites shift by up to ten bytes. No new allocation,
large copied buffer, runtime storage object or forced padding is created.

The function uses one **actual 20-byte vertex cursor** in its original
single local slot. Each of `segment_count + 1` iterations generates:

1. A first *inner* vertex from true native `polar2(current,angle,
   radius−thickness/2)`, Z=0, reciprocal W=1, signed quarter-threshold
   width/height adjustments, first packed color, genuine XY rotation,
   game world XY coordinates and renderer XY offsets.
2. Increment **the same actual cursor** by one `SpriteColoredVertex`,
   then generate the *outer* vertex at `radius+thickness/2`, its own
   color and identical native quarter-boundary transform and offsets.
3. Advance **the same cursor** once more, then update the actual angle
   with `add_angles(angle,(π*2)/segment_count)`. The signed quarter
   expressions are C++ signed division by 4, emitting original native
   CDQ/AND/ADD/SAR negative handling; this was not replaced by an
   incorrect unsigned shift.

An earlier attempt kept a separate `inner` alias, `outer` pointer and
`current+=2` even though the resulting coordinates could agree. MSVC
then generated an extra 4B stack slot, frame `0x30` rather than native
`0x2C`, and physically different operands. Replacing those with one
real cursor and **two actual one-vertex increments** emitted the entire
native original **1,468B/387 x86**, exact original `0x2C` stack, and
**all 11 E8 and 26 HIGHLOW physical positions**. There are no
artificial unused locals, hand-authored x86, manual NOPs or fabricated
unread state changes.

After generating the ring, the original game disables depth writes,
sets the genuine Graphics device render state **state=23/value=8** via
the actual 67B member wrapper, stores renderer FVF/cache byte `1`,
selects color mode `2`, sets the real FVF `0x44` and draws the native
triangle strip with **`segment_count*2` primitives and 20B stride**.
It then advances the actual receiver-owned cursor by
`2*segment_count+2` vertices and increments the original renderer
counter at `this+0xC4`. The natural C++ source preserves the complete
original state machine, rather than implementing only the inner loop.

## Whole canonical acceptance, ABI correction and scoped replay

The original member's return contract is **integer return zero**, so
`AnimationDrawDetailedOwner::draw_shape_43ab20` changed from an earlier
provisional `void` declaration to `std::int32_t` in the shared
[`src/AnimationDrawDetailedOwner.hpp`](../src/AnimationDrawDetailedOwner.hpp).
The original method source spelling remains provisional, but the
ABI/return bytes are now attested by physical original `xor eax,eax`
and `ret 0x28`. This shared header correction is a genuine semantic
change, not an extra wrapper or an invented owner object.

The new single pinned C++ object/receipt
`build/core853-canonical/AnimationShapeRing1468.obj` backs only one
`animation_shape_ring_1468` canonical full strict native unit in
[`config/match-units.toml`](../config/match-units.toml). Its 37 real
source relocations are **11 REL32 E8 sites +26 DIR32 original data
fields**, independently checked symbol/type/offset/owner/target roles.
The full zero-difference native replay reports:

```text
animation_shape_ring_1468: exact (1468/1468 bytes)
Exact replay: 1/1 units, 1 cold objects
```

Because the shared header changed, the nine previously accepted source
provider *include closures* using `AnimationDrawDetailedOwner.hpp` were
**each separately cold-recompiled and strictly replayed**, not bypassed:
whole 2,136B mesh24/25, 2,769B mode6, 1,378B mode6 setup, 753B mode7,
1,996B mode7 setup, 4,347B mode8, 534B strip11, 612B strip9, and the
one shared 73B/86B projection math provider. **All ten affected existing
strict units remained whole-native exact**. The enclosing 5,993B
Animation main Draw candidate was also independently recompiled and
checked by its original-only source-role verifier: 123 real call target
roles unchanged, 49+31 switch pointers unchanged, and it remains
**NONEXACT**. No unrelated canonical unit or full-graph cold replay ran.

This adds **one unique original game-authored whole exact function,
1,468 disjoint native bytes, one new source mapping, one new canonical
unit and one pinned source object/receipt provider**. The resulting
live count is **607 game-authored strict exact functions /213,061
original `.text` bytes**, **1,253 source mappings /1,254 canonical
units /272 accepted object providers**. No duplicate credit is assigned
for its main Draw caller, the already strict geometry/math callees, or
any shared folding of source types.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-ring-1468-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeRing1468.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/progress.py --check
```
