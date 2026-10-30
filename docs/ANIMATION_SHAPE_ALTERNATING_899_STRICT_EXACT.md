# CORE/RECON-866 — whole original 899B alternating-radius triangle-strip Boss strictly exact

The locked Japanese TH20 v1.00a Steamless original PE has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-authored polar geometry method at **`0x0043DF30`**
occupies **899B /236 real i386 instructions**, native `sub esp,0x3C`,
`ret 0x24`, zero in EAX and nine original stack arguments beyond the
Animation renderer ECX receiver. The enclosing original 5,993B main
Animation Draw dispatcher calls this physical head at **three E8 sites**
`0x00444E0F`, `0x00444EEE` and `0x00444FD1`; the parent is independently
**SOURCE-PRESENT/NONEXACT** and earns no game code credit here.

[`src/AnimationShapeAlternating899.cpp`](../src/AnimationShapeAlternating899.cpp)
now compiles with pinned x86 MSVC 19.44.35211 C++20
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
into **899/899 entire strict relocated original bytes**, with the
original 236 x86 heads and frame, **7/7 E8 true physical site/target
pairs**, **10/10 original PE HIGHLOW physical field/target pairs**,
and **831/831 nonrelocation bytes identical**. This is full native
codebody exactness, not a prefix or an unverified shape similarity.

## Independent locked original PE evidence

[`scripts/verify-animation-shape-alternating899-native.py`](../scripts/verify-animation-shape-alternating899-native.py)
reads original `.text` and PE `.reloc` independently of source C++,
decodes every native 236-instruction head through original return,
records the actual seven E8 site/destination pairs and ten original
HIGHLOW field/target pairs, checks both genuine **signed `i%2` parity
branches**, real D3D9 triangle-strip primitive type **5**, and the three
original parent call sites. The physical E8 roles are the true
AnimationPool flush `0x004455C0`, **two real original `polar2`** calls
`0x00439330`, one `add_angles` `0x00438600`, renderer color mode
`0x00446690` and two Graphics device getters `0x00412730`.
All ten original PE HIGHLOW data fields resolve to **five real 2.0f**
references at `0x0056C8D0`, one pi at `0x0056E0F0`, **two 1.0f** at
`0x0056C8CC`, and two Graphics owners `0x005C4D40`. These are physical
original target values, never copied from candidate relocation bytes.

## Original semantics and corrected source hypothesis

The original renderer uses the existing **65,536×20B typed fixed
vertex pool** and mutable write cursor. It checks an unsigned bound for
`2*segment_count+2` vertices, requires at least two segments, flushes
pending draws, and prepares the actual angle progression `2*pi/count`.
Its essential difference from an ordinary constant-thickness ring is
that **two different source radii alternate by signed step parity**:

- Before the loop, the source calculates **four real float values**
  `radius_a−thickness/2`, `radius_a+thickness/2`,
  `radius_b−thickness/2`, and `radius_b+thickness/2` in the genuine
  original source order, each using a real original 2.0f field.
- At each angle it performs one signed C++ `i%2` test before the inner
  vertex and another before the outer vertex. Even steps select the
  precomputed `radius_a` variants, odd steps the `radius_b` variants.
  Each of two real `polar2` calls writes separate 20B records with
  world XY/renderer XY offsets, Z=0, reciprocal W=1 and a separate
  inner/outer packed color, with a single advancing real buffer cursor.
- The original `add_angles` result advances the angular state, and
  after the loop native D3D9 FVF `0x44` and renderer color mode2 submit
  `DrawPrimitiveUP(D3DPT_TRIANGLESTRIP=5,2*segment_count,buffer,20)`.
  The live cursor advances by `2*segment_count+2` and the draw count
  increments. No fabricated depth state/extra Graphics callee is added.

The initial C++ experiment stored **four half-thickness locals** and
recomputed the chosen radius *inside* the loop. It generated
**887B/232 x86**, with identical callee roles but E8 sites shifted by
12–20 bytes and many nonrelocation differences. The real original PE
shows the four radius results stored **before the loop** and branch
selection from their already computed local slots. Correcting these
actual gameplay data lifetimes, not adding padding, naturally emits
the exact **899B/236 native instructions**, original `0x3C` stack,
and all seven E8 and ten HIGHLOW physical sites in the right places.

## Whole canonical acceptance, tracking and scoped rebuild

One canonical `animation_shape_alternating_899` source unit in
[`config/match-units.toml`](../config/match-units.toml) compiles one new
pinned object/receipt `build/core866-canonical/AnimationShapeAlternating899.obj`.
The manifest explicitly fixes **seven genuine REL32 E8 and ten genuine
DIR32/HIGHLOW** original physical symbol/type/site/target roles from
independently authenticated original PE. Fresh full relocation replay:

```text
animation_shape_alternating_899: exact (899/899 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The header's provisional `void draw_shape_43df30` signature is corrected
to its actual `std::int32_t` return and `ret 0x24` ABI. Existing accepted
sources affected through this header are cold-built and replayed
**only in those source include closures**; the original 5,993B Draw
parent has a separate scoped NONEXACT source-role test. No unfiltered
whole-graph cold replay is used.

This credits **one new physical original game function and 899 disjoint
`.text` bytes**. The updated live totals are **620 whole authored game
strict exact functions /226,352 original game bytes**, **1,266
source-present mappings /1,267 canonical strict units /285 pinned
exact MSVC objects/receipts**. None of its already exact geometry/
Graphics callees or the enclosing NONEXACT main Draw parent receives
duplicated code credit.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-alternating899-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeAlternating899.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
