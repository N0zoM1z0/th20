# EXACT-048: native collision shapes and vector dependencies

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

This coherent batch reconstructs seven complete collision predicates, vector
normalization, ellipse sampling and genuine Vector3 division. Ten complete
functions add 3,841 comparison bytes. The existing circle predicate, planar
rotation, bounded angle normalization, square-root wrapper and vector arithmetic
retain their canonical owners and provide independently reviewed dependencies.

## Complete native contributions

| Operation | Entry | Complete bytes |
| --- | --- | ---: |
| Circle versus rotated ellipse | 0x004562E0 | 932 |
| Circle versus regular polygon | 0x00456690 | 313 |
| Circle versus alternating-radius polygon | 0x004567D0 | 324 |
| Segment intersection | 0x00456920 | 533 |
| Point in rotated ellipse | 0x00457040 | 173 |
| Point in regular polygon | 0x004570F0 | 517 |
| Point in alternating-radius polygon | 0x00457380 | 651 |
| Vector3 division | 0x00452FF0 | 80 |
| Normalize vector to requested length | 0x004532C0 | 229 |
| Ellipse perimeter sample | 0x00459190 | 89 |

Wrapper-attested Ghidra instructions and an independent locked-PE decoder cover
all 1,166 instructions, ending at each actual return. Every direct branch reaches
an instruction in its complete contribution; every direct call has an independent
callee binding. No shortened prefix, gap ownership, dispatch table or copied
instruction bytes are used. Original source names and origins remain pending.

The native dispatcher at 0x004C1030 supplies eight stack arguments to the circle
ellipse/polygon paths and nine to the star path, cleans 32/36 bytes, and consumes
AL through MOVZX. The counts passed to polygon paths are integer words, distinct
from the float direction/radii. Point predicates supply signed loop comparisons;
segment callers consume AL. These seven predicates therefore use cdecl bool,
rather than the full integer return inferred in some decompiler hypotheses.
The complete enclosing dispatcher and its shape/controller ownership stay open.

## Native boundary protocol

The ellipse point predicate constructs a real zero Vector3, writes translated
XY, rotates in place by negative direction, and compares the sum of squared
normalized coordinates inclusively with one. Rotation preserves its Z lane.

Circle/ellipse collision first tests the circle center against axes shrunk by
its radius when the minimum axis exceeds that radius. After rotating the center
delta, a circle larger than the maximum axis has a second containment shortcut.
Only then do radius/maximum-axis values below one fail. Consequently a subunit
circle can still succeed through containment; the early rejection is not a
universal minimum-size rule.

The remaining circle/ellipse path samples one perimeter, beginning at negative
pi. If the circle is larger, ellipse sample count is int(axis_x + axis_y) / 4;
conversion precedes signed division. Otherwise count is int(radius / 4.0f).
Both are at least eight. Direction advances after producing each sample, before
testing it against the other shape. This is the game's finite sampled predicate,
not a mathematically exhaustive intersection solver.

Both polygon wrappers first accept when their center lies in the inclusive
circle. Otherwise they normalize the vector from circle center to shape center,
scale it by circle radius, translate it back, and test that near point. The regular
polygon walks its edges with 2*pi/sides increments. The alternating-radius polygon
walks twice as many edges, alternating two actual radial Vector3 values and using
(2*pi/sides)/2. Both normalize direction after each increment. Edge storage is a
real two-element Vector3 array with native twelve-byte stride and construction.

Polygon point tests reject when the segment from queried point to shape center
intersects an edge, including a touch. Nonpositive small counts execute no edges
and return true. These native boundary/count rules are preserved rather than
replaced with a generic convex-polygon or ray-casting implementation.

Segment intersection uses orientation products. Its collinear path orders each
endpoint pair by X alone, swaps the associated Y with the same active scratch
value, then tests four non-strict coordinate bounds. Descending/vertical overlap
can therefore be rejected even when a geometric intersection exists. Source
retains the exact paired-coordinate comparisons and true/false branch order.

## Actual vector storage and math ABI

Vector3 remains the existing twelve-byte named x/y/z value. Division is a const
member with aggregate hidden result and RET8, delegating to its coordinate
constructor. The result has three independent scalar divisions, without reciprocal
substitution, alternative storage or fabricated owner.

Normalization is a three-argument cdecl void operation with explicit destination
and const input references. It computes square-root of the ordered three-lane
squared sum, passes that magnitude to the existing comparison-based absolute
wrapper, and tests against the native float object 0x0056E1A0 (0.01f). Below the
threshold it multiplies the original vector by requested length. Otherwise it
divides by magnitude and then multiplies. Assignment occurs after the aggregate
result is formed, permitting destination/input aliasing and retaining all lanes.

Ellipse sampling is cdecl void with four stack arguments, independently
corroborated by its callers' sixteen-byte cleanup. It uses already canonical
standard-header float cosine/sine overloads, scales X/Y by distinct axes, and
leaves destination Z untouched. A decompiler thiscall hypothesis is rejected by
the complete native stack/caller protocol.

## Compiler, anchors and validation

CollisionShapes uses /Od /Ob0 /GS /fp:strict and the documented MSVC
strict_gs_check policy for address-taken vector storage. It is a separate natural
translation unit: existing CollisionGeometry's precise/no-GS profile is retained.
MotionMath retains strict/no-GS, and Vector3 retains precise/no-GS. These local
recipes reproduce the observations without establishing original global flags.
There is one maintained semantic body per operation, with no assembly, byte
arrays, inert locals, ABI substitutions or conditional matching bodies.

Braced coordinate initialization preserves ordered active XY evaluation. Implicit
braced operands construct the actual center temporary bound to vector addition's
const reference. Alternating radial pointer selection passes a reference to the
actual selected radial object. These are ordinary typed C++ operations, not fake
storage or padding introduced for compilation.

Canonical relocation destinations use independently reviewed native heads,
previous canonical dependency bindings and directly checked PE constant objects:
zero, one, two, four, positive/negative pi, normalization threshold, and the
sixteen-byte repeated sign-bit mask. Security cookie/check bindings retain the
prior independently observed runtime addresses. Unit-local dispatch labels from
older units are never treated as global symbol anchors.

Native 0x0040BC20 is the complete 56-byte stdcall array-construction iterator:
count is unsigned, element pointer advances by stride, callback receives ECX,
constructor return is ignored, and RET16 cleans all four arguments. MSVC emits
a structurally identical genuine helper for the two-element Vector3 arrays.
Its target binding follows the complete independent protocol/instructions and
native calls. It receives no additional source mapping or authored exact credit.

All 309 units / 61 cold objects strictly replay over 41,401 disjoint complete
comparison bytes. The whole previous graph is cold-rebuilt after shared headers
and source change. Public C++20/UBSan checks cover independently known vector
lengths, three-lane scaling, threshold equality and the tiny-vector path, aliasing,
input preservation, division, planar Z preservation, rotated ellipse boundaries,
segment crossings/touches and native collinear quirks, polygon/star interior and
exterior across five edge counts, vertex exclusion, vacuous counts, wrapper
center shortcuts, circle/ellipse sampling and subunit containment.

Finite component acceptance requires valid objects, int32-representable perimeter
sample conversions, and small polygon counts with representable doubled count
and terminating loop increments. Extremely large/overflowing counts, nonfinite
float conversion, exceptional floating-control/CRT behavior, enclosing ownership,
original names/origins, full linkage and gameplay are unaccepted. This batch does
not replace the surrounding native collision dispatch or establish a playable
source-built game. Source becomes 309, pending origins 248; four classified library
comparisons and authored 57 functions / 4,074 bytes remain unchanged. Exhaustive
reference review remains 6,945 bodies and 113 reconciled grammar files.
