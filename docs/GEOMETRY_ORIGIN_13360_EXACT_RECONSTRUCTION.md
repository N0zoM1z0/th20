# CORE/ORIGIN-503 and CORE/EXACT-503 — 19 whole original geometry functions, 13,360 authored bytes

Comparison target: the immutable user-selected Japanese TH20 v1.00a
Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**New authored-origin admissions:** 19 independently strict-exact,
nonoverlapping original geometry functions totaling **13,360 game-body bytes**
and **3,530 original i386 instructions**. This is an **origin/evidence audit
of already maintained C++ and already configured strict units**; these
implementations were not newly typed or synthesized in CORE/EXACT-503.
Before this review, all 19 had a provisional `reconstructed` status and
unknown original provenance, so none was in the authored-exact match ledger.
After this audit they each have independently corroborated native gameplay
owners and complete fresh canonical MSVC replay, without duplicate coverage.

## Whole original functions and their actual original callers

| Original entry | Whole original bytes | Retained semantic implementation |
| --- | ---: | --- |
| `0x004545D0` | **526** | Complete segment intersection coordinate computation |
| `0x004547E0` | **1,439** | Full finite line / rotated rectangle intersections |
| `0x00454D80` | **343** | Closest point along a rotated-width segment |
| `0x004562E0` | **932** | Circle / rotated ellipse |
| `0x00456690` | **313** | Circle / regular polygon |
| `0x004567D0` | **324** | Circle / alternating-radius polygon |
| `0x00456920` | **533** | Entire segment / segment intersection and collinearity |
| `0x00456B40` | **517** | Segment / regular polygon boundary |
| `0x00456D50` | **651** | Segment / alternating-radius polygon boundary |
| `0x00457040` | **173** | Point / rotated ellipse |
| `0x004570F0` | **517** | Point / regular polygon |
| `0x00457380` | **651** | Point / alternating-radius polygon |
| `0x00457610` | **669** | Rectangle / circle |
| `0x004578B0` | **849** | Rectangle / rotated ellipse |
| `0x00457C10` | **1,195** | Rectangle / regular polygon |
| `0x004580C0` | **1,452** | Entire rectangle / rectangle collision boss |
| `0x00458670` | **1,250** | Rectangle / alternating-radius polygon boss |
| `0x00458B60` | **804** | Rectangle contains any of four points |
| `0x00458E90` | **222** | Rotated rectangle / point |

The implementations are maintained in `src/RectangleCollisions.cpp`
and `src/CollisionShapes.cpp`, not invented local test-only bodies. Source
and ABI details, unusual boundary behavior and prior full function native
reconstructions remain documented in
[EXACT-048](EXACT_COLLISION_SHAPES_RECONSTRUCTION.md) and
[EXACT-049](EXACT_RECTANGLE_COLLISIONS_RECONSTRUCTION.md).
Those historical notes explicitly left original authored origins pending;
this checkpoint separately establishes them. Original C++ identifier
spelling and historical translation-unit division remain unproven.

The native immutable PE independently shows the complete **2,696-byte
whole-exact** `DamageRegion::intersects` (`0x004C1030`) directly invoking
`rectangle_rectangle` (`0x004580C0`), `circle_ellipse`,
`circle_regular_polygon`, `circle_star`, `rectangle_circle`,
`rectangle_ellipse`, `rectangle_regular_polygon`, and `rectangle_star`.
The independently already accepted **707-byte whole**
`BulletController::cancel_in_rectangle` (`0x0047CC90`) and **661-byte whole**
`Player::collision_rectangle_circle` (`0x004F91D0`) independently invoke
the same native `rectangle_circle` body. These are real custom game
DamageRegion/Bullet/Player consumers, not standard-library wrappers.

The rest of this bespoke geometry graph is reached through the full
native `rectangle_rectangle` corner/edge paths, `rectangle_star` and
`rectangle_regular_polygon` boundary paths, `circle_ellipse` and the
polygon-point predicates. The same original table of 4 directed
rectangle edges at `0x0056E688` has exactly the expected signed 32-byte
payload `(0,1),(1,2),(2,3),(3,0)` in the immutable PE and the
locked compiler object. This, the custom finite polygon/ellipse
sampling, the particular screen/collision conventions and the original
caller provenance support classification as **game-authored geometry**,
not incidental CRT/STL helpers.

Four currently unlabelled original enclosing consumers reduce the
individual origin confidence to **medium** (rather than high) for
`segment_intersection_point`, `line_rectangle_intersections`,
`nearest_width_segment`, and `rotated_rectangle_point`.
Their original direct callers include `0x00503450`, `0x004D2750`,
`0x004D2A20`, `0x004D2DD0` and collision routines in the
`0x004C9AB0..0x004CB510` neighborhood. All four still execute custom
geometry over real game Vector2/Vector3 owners and are fully native exact;
source provenance of their parents is not silently upgraded.
The other 15 have **high** game-origin confidence from the actual
accepted game collision dispatcher and complete internal geometry
call graph. This authored classification does not establish who wrote
a historical source file or disprove a shared custom-game math module.

## Fresh locked compilation and exactness

Initial independent screening used `/fp:precise` to challenge the old
documentation rather than assuming it correct: **13/19** whole original
functions were structurally identical under that alternate profile; six
were **not**. The repository's actual existing canonical profile is
MSVC 19.44.35211 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:strict`
with its maintained source-local `strict_gs_check` pragma. Cold-building
**only the two real source providers** under their already registered
profiles and replaying their existing manifest units gave **19/19
complete `exact` results**, including all six whose code had differed
under `/fp:precise`.

The original code extents are complete and disjoint. The entire
3,530-head original i386 decode covers every instruction through each
physical return; no partial prefix, shortened extent or shared
physical address is given additional authored bytes. Fresh MSVC
canonical objects are the existing owners:
`build/core154-canonical/CollisionShapes.obj` and
`build/core154-canonical/RectangleCollisions.obj` with their fresh
locked input/hash receipts. No source file, header, original executable,
compiler profile, pinned link-time table or manifest relocation has
been changed to force matching.

For each complete original whole body we independently decoded all
**160 original E8 call fields** and parsed all **181 original PE
HIGHLOW absolute fields** directly from the locked executable's
real `.reloc` section. Each offset, kind and observed original target
agreed with the corresponding existing manifest symbol/base plus
the ordinary COFF addend. This was not a backwards relocation solve from
a comparison candidate. Every remaining nonrelocated native byte also
matched exactly. The eleven separately verified original RDATA source
payload identities include signed masks, native float constants and the
32-byte rectangle-edges table; each agrees with the original PE **and**
the defined C/C++ compiler symbol's complete data. The complete source
provenance/position and disjointness audits are retained privately in
`.analysis/core503-geometry-original-19-whole-anchors.json`,
`.analysis/core503-geometry-native-callers.json`,
`.analysis/core503-geometry-pinned-19unit-verification.json`, and
`.analysis/core503-geometry-independent-anchor-proof.log`.

## Acceptance scope and limitations

**Only two source/object providers were cold rebuilt**, covering their
19 previously configured complete native units. Earlier accepted
native provider inputs in other files remained unchanged; an
unfiltered 1,177-unit cold replay would be unnecessary. All 19 now
have `matching` status, directly applicable current function-origin
classification and an authored match ledger row. Native game-authored
whole-function exactness rises from 401 / 124,919 bytes to
**420 / 138,279 disjoint original bytes**. Strict unit and unique
source-object counts do **not** increase; these 19 units already existed
and had original source, but were previously withheld from authored credit.

The other geometry functions, and the entire 3,111B Player frame,
555B Player movement, 1,404B Bullet command 11, 3,735B Bullet
emitter, and huge Animation/Enemy dispatchers remain independent
unfinished tasks. Exact geometry source and native-byte equivalence
is not a whole-game link or actual game-runtime proof.
