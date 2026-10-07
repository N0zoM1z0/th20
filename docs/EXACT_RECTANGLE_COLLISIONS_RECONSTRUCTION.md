# EXACT-049: rectangle/segment neighborhood and planar dependencies

This batch reconstructs all twelve reviewed neighboring collision routines and
nine direct dependencies. The 21 complete contributions add 10,759 comparison
bytes. Every original candidate closes; none is left at a structural-only result.
The previous 309 contributions are rebuilt after the shared declarations change.
All 330 units / 63 cold objects / 52,160 disjoint complete comparison bytes pass
strict canonical replay. These totals include pending origins and are distinct
from the 57 authored-origin functions / 4,074 bytes.

## Complete native contributions

| Operation | Entry | Complete bytes |
| --- | --- | ---: |
| Segment intersection point | 0x004545D0 | 526 |
| Finite line/rectangle intersections | 0x004547E0 | 1,439 |
| Nearest point on rotated width segment | 0x00454D80 | 343 |
| Segment/regular polygon boundary | 0x00456B40 | 517 |
| Segment/alternating-radius polygon boundary | 0x00456D50 | 651 |
| Rectangle/circle | 0x00457610 | 669 |
| Rectangle/ellipse | 0x004578B0 | 849 |
| Rectangle/regular polygon | 0x00457C10 | 1,195 |
| Rectangle/rectangle | 0x004580C0 | 1,452 |
| Rectangle/alternating-radius polygon | 0x00458670 | 1,250 |
| Rectangle contains any of four points | 0x00458B60 | 804 |
| Rotated rectangle/point | 0x00458E90 | 222 |
| XY norm | 0x00455FB0 | 46 |
| XY distance, interleaved scalar endpoints | 0x00455FE0 | 68 |
| XY distance, actual Vector3 inputs | 0x00456030 | 32 |
| Squared XY norm | 0x00456050 | 40 |
| Squared XY distance, scalar endpoints | 0x00456080 | 68 |
| Squared XY distance, Vector3 inputs | 0x004560D0 | 88 |
| Line slope/intercept and vertical status | 0x00456170 | 156 |
| XY array rotation, actual Vector2 stride | 0x00459030 | 172 |
| XY array rotation, actual Vector3 stride | 0x004590E0 | 172 |

Wrapper-attested Ghidra and an independent decoder of the locked PE reconcile
all 2,836 instructions, complete returns and internal branch destinations.
The unreachable jump at 0x0045477D follows an unconditional return-path jump;
it remains inside the full 526-byte contribution. No boundary is shortened.
Every direct call has an independently reviewed callee/ABI anchor.

## Native geometry and active evaluation

Line parameters return full EAX: 1 for a vertical line, otherwise 0. Vertical
classification uses abs(bx-ax) < 0.01f. The vertical intercept stores ax, with
slope zero. The nonvertical intercept evaluates ay-(by-ay)*ax/(bx-ax); this is
not rewritten using the stored slope. Intersection-point status also returns
full EAX, unlike the AL bool returned by the predicate it first calls.
Failure leaves output coordinates unchanged. When both lines are vertical, the
second tolerance is 0.001f; success selects the first endpoint, even when it is
outside the overlap interval. Equal nonvertical slopes retain the native zero
denominator; the source does not add a new parallel-line policy. Output X and
Y are separate expressions, preserving the native write/evaluation order.

The line/rectangle routine constructs actual Vector2 arrays of four corners
and three line values, then actual Vector3 hits[2]. Endpoints extend 1,000 units
in each direction from the input point. The corner-rotation gate tests the line
angle, while the rotation itself uses the rectangle angle. This observable
quirk remains. The first two successful edge intersections are ordered by
squared distance from the negative line endpoint; duplicate vertex hits remain
possible. One hit is copied into both outputs; failure writes neither. Output
Z lanes are preserved. Caller 0x00503450 constructs both outputs with the real
Vector3 default constructor and passes the same input position to the existing
three-lane Vector3 subtraction member at 0x00429740. No enclosing owner is
fabricated from that evidence.

The nearest-width-segment routine subtracts actual Vector3 values, rotates the
planar delta, selects/clamps its X coordinate, zeroes the closest point's Y/Z,
and computes distance using XY alone. It rotates the closest point back and
assigns the complete center-plus-offset value. Output Z therefore equals
center.z, even when the queried point has a different Z. Caller 0x004D2750
corroborates actual default construction, five cdecl arguments and an ST0 result.

Segment/polygon and segment/star tests inspect boundary intersections, without
a containment shortcut. Small nonpositive side counts return false. They retain
the existing alternating-radius pointer selection, active direction advancement,
angle normalization and real Vector3 edge construction. Rectangle/polygon and
rectangle/star first test the shape center using the strict *unrotated*
axis-aligned rectangle, then the rectangle center against the polygon. Four
explicit edge tests follow actual rotated/translated Vector3 corners. These
native shortcuts are retained even when they disagree with ideal geometry.

Rectangle/circle accepts two inclusive straight strips, then four strict corner
radius tests. Its by-value rectangle center arguments become active coordinate
scratch values, matching the original evaluation/storage protocol. Rectangle
point and four-point containment are inclusive, unlike rectangle_point. The
four-point helper uses actual Vector2[4] storage and preserves its four explicit
short-circuit tests.

Rectangle/ellipse rotates the center delta into ellipse space, and separately
rotates the full width/height vector by normalized relative direction. It uses
these signed rotated components directly. If the largest rectangle extent is
larger than the largest ellipse axis, it samples the ellipse perimeter at least
eight times, beginning at the rectangle angle. Otherwise it samples a rectangular
grid with at least three rows/columns; count is int(maximum_extent/8.0f), and
spacing divides by count-1. No absolute-extent correction or continuous collision
solver replaces this finite native predicate.

Rectangle/rectangle first rejects when center distance is at least the sum of
half-diagonal norms. Two actual Vector2 corner arrays are rotated and translated,
then tested for corner containment in either direction. A nested four-by-four
edge loop handles edge-only crossings. Both this routine and line/rectangle use
the same read-only int[4][2] connectivity table at 0x0056E688. Its natural maintained
initializer expresses cyclic edges; it is independently bound as routing data,
with no additional function/exact credit.

## Shared typed math and ABI

The existing scalar XY rotation head at 0x00458FA0 / 137 bytes receives both real
8-byte Vector2 and 12-byte Vector3 objects. One maintained function template,
explicitly instantiated for each actual type, expresses the shared XY operation
without casting either object to an incompatible owner. Both complete compiler
contributions and relocation protocols match that physical head. The existing
canonical unit uses the Vector3 instantiation; Vector2 calls bind the same
independently audited head. No duplicate byte coverage or unit is added. This
does not establish the original source spelling or a global linker ICF recipe.

One array-rotation template provides the two distinct 172-byte native stride
variants. Both compute widened sine/cosine once, save rotated X before writing
Y, then write X and advance pointers/count in forward order. Identical arrays
are supported, destination Z is preserved, and forward overlaps retain their
native read-after-write behavior. Original count signedness is unproved; the
maintained unsigned word uses the established nonnegative valid-array domain.

Scalar distances take x1,x2,y1,y2, not x1,y1,x2,y2. Vector3 overloads also ignore
Z. All float results use the native ST0/cdecl ABI and the already canonical
square-root wrapper. Original predicate consumers at 0x004C1030 clean 32/40/44
bytes and read AL through MOVZX; decompiler full-integer hypotheses are rejected.
Native iterator 0x0040BC20 remains an independent callback/stride/count/RET16
anchor, without additional source or authored credit.

Independent constant reads verify 0.001f at 0x0056E714, 8.0f at 0x0056D7BC and
1,000.0f at 0x0056CDB0. Existing zero/two/pi/0.01/sign-mask, security cookie and
callee anchors remain independently established; canonical fields are not filled
from diagnostic solved destinations. GeometryMetrics retains strict FP/no-GS;
RectangleCollisions uses strict FP/GS with guarded strict_gs_check; MotionMath's
strict FP/no-GS recipe is unchanged. These are local compiler observations,
not proof of the whole game's build recipe.

## Verification and remaining scope

Public C++20/UBSan tests cover all twelve routines and dependencies: interleaved
endpoints, ignored Z, tolerance boundary, output preservation, vertical endpoint
selection, finite line length, the corner-rotation gate, nearest-point aliasing,
scalar/array in-place rotation, zero-length arrays, forward overlap, destination
Z, strict corner versus inclusive strip, boundary-only polygon tests, center
shortcuts, both ellipse sampling branches and signed dimensions, each of four
point slots, rectangle containment, radius rejection and edge-only crossings.
All previous exact units are cold rebuilt after the shared header/source change.

All twelve candidates are exact in this batch. Original names, source-level
signedness outside established domains, authored/compiler/library origins,
exceptional FP/traps, overflowing side counts or nonrepresentable conversions,
complete collision controller/resource lifetimes, linkage and whole-game runtime
remain open. Reference review stays complete at 6,945 bodies / 113 grammar files;
this native batch does not alter reference terminal decisions. Reconstruction
continues in coherent batches; exact component totals are not a playable-game
or whole-program completion claim.
