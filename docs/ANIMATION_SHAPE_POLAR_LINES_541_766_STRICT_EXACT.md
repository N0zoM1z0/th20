# CORE/RECON-862 — whole original 541B and 766B polar-shape renderers strict exact

The target is the locked Japanese TH20 v1.00a Steamless original PE,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint reconstructs **two separate game-authored whole native
functions**, not merely their shared `polar2`/`add_angles` loop and not
any part of the still-NONEXACT 5,993B Animation main Draw dispatcher.

| Independently attested original property | Simple circle LINESTRIP | Dual-radius TRIANGLESTRIP |
| --- | --- | --- |
| Physical original code head | `0x0043BC60` | `0x0043BE80` |
| Entire native size / actual x86 heads | **541B /147 i386** | **766B /201 i386** |
| Original native stack and return | `sub esp,0x24`, `ret 0x18` | `sub esp,0x2C`, `ret 0x20` |
| Original E8 sites/real callee destinations | **6/6 exact** | **7/7 exact** |
| Original physical PE HIGHLOW sites/targets | **5/5 exact** | **8/8 exact** |
| All nonrelocation code bytes | **497/497 identical** | **706/706 identical** |
| Complete canonical relocated native bytes | **541/541 zero differences** | **766/766 zero differences** |
| Original D3D9 primitive | `D3DPT_LINESTRIP = 3` | `D3DPT_TRIANGLESTRIP = 5` |

## Actual original PE evidence, not source-probe speculation

[`scripts/verify-animation-shape-polar-lines-native.py`](../scripts/verify-animation-shape-polar-lines-native.py)
reads the immutable original `.text` and actual PE `.reloc`, decodes
both complete real x86 bodies through their original returns, and
checks **all 13 original direct E8 physical site/target pairs plus all
13 PE HIGHLOW physical field/target pairs**. It also independently
disassembles the whole 5,993B Draw parent to prove its actual E8 callers:

- **541B LINESTRIP:** original parent E8 `0x00444A7D`, native calls to
  `AnimationPoolOwner::flush_draws` at `0x004455C0`, genuine `polar2`
  at `0x00439330`, `add_angles` at `0x00438600`, renderer color mode
  at `0x00446690` and two Graphics device getters `0x00412730`.
  The original five absolute PE fields point to real `pi`
  `0x0056E0F0`, `2.0f` `0x0056C8D0`, `1.0f` `0x0056C8CC`, and two
  Graphics owner `0x005C4D40` references.
- **766B TRIANGLESTRIP:** original parent E8 `0x00444B02`,
  `0x00444B94` and `0x00444C2A`. Its seven native calls are the
  original flush, **two real `polar2`**, one `add_angles`, color mode,
  and two Graphics device getters. Original eight PE HIGHLOW fields
  target **three `2.0f`**, one `pi`, **two `1.0f`**, and two real
  Graphics references. Every field position/target is recorded from
  immutable PE before any compiler-source comparison.

Neither original body uses an extra standalone depth-state helper;
copying a neighbor's depth-disable call into either source would
be incorrect. The historical source identifiers remain provisional,
but the actual native ABIs, call destinations, data references and
visible rendering behavior are established by the physical target.

## Real geometry and C++ codegen recovered

The maintained source functions
[`src/AnimationShapeSimpleLine541.cpp`](../src/AnimationShapeSimpleLine541.cpp)
and [`src/AnimationShapePolarStrip766.cpp`](../src/AnimationShapePolarStrip766.cpp)
use the existing genuine **65,536 ×20-byte `SpriteColoredVertex` fixed
pool** and the original mutable renderer write cursor, rather than
allocating new source-owned vertex storage. Each reserves its real
number of records with an unsigned original buffer-end `JB` guard and
has a native segment-count-at-least-two test. The actual angle start
is saved in a meaningful local; the caller's mutable original
start-angle parameter slot is reused for the `2*pi/count` increment.

The 541B renderer generates exactly `segment_count+1` perimeter
vertices via one `polar2` call per step. Each writes real world/renderer
XY, Z=0, reciprocal W=1 and one packed perimeter color, then advances
one 20B cursor and accumulates the angle with the actual `add_angles`
function. It configures FVF `0x44`, native renderer color mode 2 and
issues `DrawPrimitiveUP(LINESTRIP,segment_count,buffer,20)` before
advancing the live cursor by `segment_count+1` and the render counter.

The 766B renderer uses an **inner radius `radius-thickness/2` and
outer radius `radius+thickness/2`** as genuine separate source values.
For each of `segment_count+1` angle steps it emits an *inner* 20B
vertex and then an *outer* 20B vertex, with separate packed colors,
world XY offsets and the genuine source pointer increment after each.
It calls the real `polar2` twice per step, and finally issues native
`DrawPrimitiveUP(TRIANGLESTRIP,2*segment_count,buffer,20)`, updating
the cursor by `segment_count*2+2` and the original renderer draw count.
The primitive type and vertex/cursor accounting are distinct, not
interchangeable despite sharing the polar math leaf.

Both ordinary C++ methods emit the complete native original
source/ABI/branch structure under pinned i386 MSVC 19.44.35211 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
There is no hand-written assembly, original binary byte copying,
artificial NOP padding or fabricated duplicate callee.

## Strict COFF acceptance and bounded replay

Two distinct canonical units in
[`config/match-units.toml`](../config/match-units.toml)
use separate pinned compiler objects/receipts:

```text
animation_shape_simpleline_541: exact (541/541 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_shape_polarstrip_766: exact (766/766 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The first canonical unit has **six true REL32 E8 + five true
DIR32/HIGHLOW** symbolic original relocation roles, and the second
has **seven E8 + eight HIGHLOW**. Each real symbol, field offset,
relocation type and native destination was cross-checked against the
independently read original PE. These two functions are fully exact
and add **2 original game-authored functions /1,307 disjoint original
`.text` bytes**, not duplicated credit for `polar2`, `add_angles`,
Graphics, the earlier rounded fans or the still-NONEXACT 5,993B main
Draw dispatcher.

The original signatures returned zero through EAX and used native
`ret 0x18`/`ret 0x20`, so the two provisional member declarations in
`AnimationDrawDetailedOwner.hpp` were corrected from `void` to
`std::int32_t`. Affected old accepted source providers must therefore
be replayed **only in the shared-header include closures**, and the
5,993B Draw parent checked with its own focused NONEXACT verifier.
No unfiltered full-graph cold replay is required or run.

| Live original game tracking | Before | After |
| --- | ---: | ---: |
| Original authored whole-native strict functions | 615 | **617** |
| Native disjoint original game `.text` exact bytes | 222,029 | **223,336** |
| Source-present original/function mappings | 1,261 | **1,263** |
| Canonical strict match units | 1,262 | **1,264** |
| Pinned exact MSVC objects/receipts | 280 | **282** |

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-polar-lines-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeSimpleLine541.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapePolarStrip766.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
