# Mesh geometry and enemy deformation

## CORE/EXACT-117: whole mesh construction and retirement

Eight complete physical roots add 1,608 disjoint comparison bytes with 59 independent
relocations. The frozen 268-file production graph passes 781 strict units across
153 fresh objects / 147,719 bytes. Three independently audited application roots
add 1,342 authored bytes: authored exact 94 / 30,383 bytes, confirmed authored
98. Mappings are 796; fifteen whole methods remain nonexact. Reference absorption
238, all 6,945 terminal implementation reviews and header-only claims are unchanged.

| Maintained operation | Native address | Complete comparison bytes |
| --- | --- | ---: |
| RenderMesh construction | 0x49CF80 | 878 |
| RenderMesh retirement | 0x471CA0 | 271 (266 code + five CC bytes) |
| Graphics surface strip creation | 0x4DE360 | 198 |
| Animation geometry allocation | 0x42B590 | 63 |
| Animation variables reference | 0x45D0C0 | 19 |
| AnimationFile null-position wrapper | 0x450C70 | 57 |
| AnimationFile position/output wrapper, flags zero | 0x4790E0 | 61 |
| AnimationFile position/output wrapper, flags eight | 0x4ABA30 | 61 |

`RenderMeshLifecycle.cpp` owns the actual four-int constructor and paired
destructor; no default constructor is invented. The existing nine-word owner
remains 36 bytes on x86. Construction checks **Graphics resource +0x19C** rather
than graphics_ready. If absent, it clears the complete owner and returns. Otherwise
it binds actual Session Context and preserves native allocation expressions:
`sizeof(AnimationHandle)*columns-1`, `sizeof(Animation*)*columns-1`, and complete
vertex/position grids. The first two expressions retain the native extra three
bytes on x86. Columns/rows/surface/view are signed 32-bit integers; negative
nonzero surface values take the surface branch.

Grid mode creates root and columns on layer 41 with script zero. Surface mode
uses layer 42 and chooses script 13/14/15 for widths 640/960/other, then changes
root and strips to layer 27. Root Animation publishes the mesh pointer at +0x5C8
and calls the genuine undefined recursive flag-clear interface. Strip resolution,
byte +0x499 clearing and two-bit layer-mode updates preserve native ordering and
unrelated flag bits. Retirement calls root retirement, frees/resets vertices and
positions, retires each column handle, then frees/resets handles and strip pointers.
Original renderer/VM handle creation, recursive child traversal and retirement
remain genuine dependencies, separately bounded by test captures.

`GraphicsMesh.cpp` uses the **global** Graphics surface file even when called on
a different receiver. Geometry allocation always reserves `28*rows*2` bytes. Rows
above two set primitive byte 12, publish rows to the real AnmVariables integer,
and initialize only Z/RHW/color, preserving X/Y/UV. Smaller rows set primitive
zero and retain all geometry bytes. Whole grid creation at 0x4DE430 is maintained
but **nonexact**: natural complete COFF has 224 bytes versus native 223, with 130
full replay differences. Its uint8 OR promotes to MOVZX/32-bit OR, while the target
uses byte MOV/OR. Earlier six-bit and eight-bit-field experiments also disagree.
No shortened comparison, inert local, fake ABI or source-profile branch is used.
The complete mismatch and original trial inputs are retained for further review.

The native spawn ABI corrects a previous declaration: the six-argument wrapper's
last parameter is optional **Animation** output storage (`Animation**`), not a
flags word. Full 0x450CB0 takes a nullable Vector3 pointer, flags and output as
separate arguments and writes nonnull output storage before checking the requested
file stem. The 0x4790E0 wrapper supplies flags zero; the distinct 0x4ABA30 wrapper
supplies flags eight. Item calls use the former and Enemy movement uses the latter.
`MeshResourceAccess.cpp` preserves both wrappers and the null-position overload.
Their common full VM implementation remains undefined. Existing caller symbols
and fixtures are corrected while independent native destinations remain fixed.

Animation +0x5C8 becomes generic `void* user_data`: independently attested mesh
publication and callbacks at 0x531150/0x534F10 consume different actual owner
pointers. It is not an exclusive RenderMesh pointer. A query at 0x531270 resolves
to the encompassing 0x531260 method and is not evidence of another userdata
consumer. The mixed flag byte at +0x4A0 has a standard union with the existing
low-two-bit mode view. All existing Animation constructor/reset/retirement exact
units pass after these shared-header refinements; native size remains 0x5E4.

The full scalar allocation consumer 0x4712D0 allocates/clears 36 bytes and calls
0x49CF80. Screen consumer 0x52C030 owns the mesh at +0x5924, retires it through
allocator/destroy_at/scalar-deleting bodies and then allocates a 64-by-48 surface
mesh. Complete native deletion independently identifies destructor 0x471CA0;
automatic library names are not accepted as ownership evidence. Together with
actual scripts/layers/Context and paired buffer lifetime, these application
consumers establish construction/retirement/Graphics origins independently from
exactness. Five access/wrapper origins remain unknown. Original function spelling,
translation-unit partition and original COFF ownership are still inferences.

Destructor RET is at 0x471DA9, followed by six native CC bytes before the next
function at 0x471DB0. The complete generated contribution owns five CC bytes;
all 271 bytes are compared. Its independently reused generic noexcept handler
is also anchored by prior DamageRegion, FunctionChainNode and ShotMetadata units. Attributing the sixth byte to original linker
alignment remains an inference; it receives no authored coverage. Original EH
handler structure, complete RTTI/link/startup and game runtime remain separate.

Maintained production C++20/O2/ASan/UBSan passes **3,433 cases**: all 256 initial
flag bytes across five row counts and both factories; 864 owned mesh lifetimes
across columns/rows/views/window widths/nonzero surface values/retained flags;
three resource-absent paths; six null/non-null output wrapper cases. Actual mesh,
Graphics/viewport/Worker, Animation values, Session/Context, PMR strings and lock
owners execute. Explicit original VM/handle/recursive-clear captures, empty
resource-file/Graphics teardown and abort-only uncalled Overlay virtual fixtures
bound unimplemented protocols. Heap captures use malloc/free with actual slot-one
guards and sanitizer bounds, record exact allocation/retirement order and seed
buffers to verify preserved bytes. A borrowed opaque API token exercises only
resource-pointer presence. Existing geometry fixtures use the actual absent-resource
constructor and detach externally owned views before the actual destructor.
Malformed dimensions/allocation failures and original resources/runtime remain open.

Before migration, 150 prior canonical and three fresh private original
source/receipt/SDK closures are verified and losslessly archived. Every affected
production object builds once; full typed literal payloads and actual fresh COFF
reference roles identify labels independently, including duplicates. Keep CORE117
frozen source/full comparisons/production semantic/origin/native/literal/retirement
receipts. Seven superseded trial pairs and the losslessly archived private host
graph retire during this batch: 282 files / 951,445 bytes. Current canonical and
active private pairs are protected. Historical sound closures remain historical;
no unchanged-source cold rebuild is used for documentation or cleanup.

All73 public tests pass in277.125 seconds; the full gate passes in281.075
seconds. The first public run exposed two missing AnimationParameters linkage
entries in the existing geometry runners. Targeted regression then exposed a
formerly trivial owning RenderMesh snapshot gaining real destructor behavior.
Both runners now include the actual layer implementation; the surface fixture
uses a non-owning byte snapshot and detaches its borrowed root/views before real
retirement. Failed logs remain unchanged. The final surface fixture is corrected
before its compiler invocation in the successful complete public run. Production
source, canonical objects and the3433-case production semantic body are unchanged
by these test fixes; no canonical cold rebuild is repeated.

Protected final retirement removes150 previous canonical and three migrated
private pairs:306 files/8,534,482 bytes. Including mid-batch retirement,588 files/
9,485,927 bytes (9.05 MiB) retire. Original source/receipt/SDK closures are verified
before deletion; all781 completed comparison results,268 source hashes and306
current canonical-file hashes remain unchanged afterward. Build9.8MiB/analysis
137MiB. Preserve the pre-deletion path/size/hash plans and both cleanup receipts.
Forty-five complete typed literal reference roles reconcile14 label renames,
including duplicate payloads; each of153 production objects compiles once.
Six regenerable Python bytecode files/43490B also retire after final control-plane
checks, yielding594 files/9529417B (9.09 MiB) for the complete batch. All current
source/canonical hashes remain unchanged; no compiler input is retired.


## CORE/EXACT-116: whole local-coordinate surface grid

The complete 480-byte method at 0x49D5B0 is now maintained in
`src/RenderMeshSurface.cpp`, with the existing complete RenderMesh, Graphics,
ViewportState, Animation and Vector3 owners. Ten canonical relocations come from
independently established native symbols and the existing mesh float-one
literal. Frozen 265-source-file replay passes 773 units / 150 fresh objects /
146,111 disjoint bytes. The independent application-origin audit adds one
480-byte function: authored exact 91 / 29,041 bytes, confirmed authored 94.
Mappings are 787; fourteen whole nonexact methods, reference absorption 238 and
all 6,945 terminal reference reviews remain separate and unchanged.

This address is a mesh method, correcting an earlier private next-work
association with Effect draw. Actual Effect update is 271 bytes at 0x49D4A0; its
draw callback at 0x49DEA0 forwards to 0x478BF0. Their original renderer
interfaces remain open. The existing 503-byte mesh initialization at 0x49D850 is
a distinct Window-offset variant and retains its source and semantic tests.

The new method stores column-major **local** Vector3 positions. UV conversion
uses those positions and the real WindowState scaled dimensions, clamping only
negative results. Each displayed vertex then receives signed integer offsets
from `process_graphics.viewports[2]`. The viewport index is fixed; mesh view and
Context selection do not choose it. It writes reciprocal W = 1 and white color,
then copies full adjacent-column vertex pairs into actual Animation strip
buffers. The native 0x16C viewport stride, Graphics viewports at +0x278 and
offset words +0xFC/+0x100 independently establish the receiver and field
association. No Window-offset helper is substituted and no Renderer prefix is
invented.

Two complete, independently attested application consumers at 0x51ED90 and
0x52C030 call the new method. Both retrieve the mesh at their receiver +0x5924
and initialize the full scaled Window extent. The former deforms/colors the
vertices and republishes strips; the latter allocates a 64-by-48 mesh, installs
callbacks and initializes related color/phase state. This custom multi-owner
screen rendering protocol establishes application origin separately from exact
bytes. Original source names and original translation-unit partition remain
inferences; the callers themselves receive no source or exact credit.

Maintained-body C++20/O2/ASan/UBSan passes 946 cases: 945 grids across
dimensions, finite/negative/NaN coordinates, negative-zero preservation,
forward/reversed extents, three signed offset sets, and five mesh view values
including signed extremes, plus a zero-column null-buffer early exit that skips
invalid/divide-by-zero calculations. All six viewports have different offsets,
Window offsets and client dimensions differ from the selected viewport and
scaled dimensions, and the complete mesh/Graphics state is preserved. An
independent local-coordinate/UV/display model checks actual outputs, end guards
and complete 28-byte strip copies. Actual Graphics constructors, viewport
members, Animation/Session values, allocator and Worker member lifetimes
execute. Empty-resource Graphics teardown is an explicit host fixture. Abort-
only uncalled Overlay virtual methods supply RTTI for Context's maintained cast;
no Overlay is constructed or exercised. Initial host runners exposed retained
Overlay RTTI, a missing real Context constructor and an incorrect chain-source
filename; their failed logs are retained. The final fixture uses the real
Context/TaskInfo/chain bodies and explicit uncalled virtual boundaries.
Production behavior was unchanged.

The native 878-byte mesh constructor at 0x49CF80 is fully reviewed but remains
unimplemented. It calls actual Graphics handle creation at 0x4DE430/0x4DE360,
resolves root/strip handles, writes mesh callback state into Animation +0x5C8,
propagates a flag clear through children, sets layer/byte/flag properties, and
preserves diagnostic allocation sizes. Genuine owner storage is available; the
complete original creation and callback protocol still needs
source/type/lifetime closure. The full Item update 4,820 bytes and draw 815
bytes also remain open.

Independent Renderer lifetime evidence confirms both embedded Animation
constructors/destructors and the allocator/blanket-clear size 0x7D40E94. A full
locked-text search finds no encoded direct displacement for +0x6000DFC; that
search neither establishes a field type nor excludes computed accesses. The
following +0x6000E00 word is only directly observed in constructor clearing,
while +0x6000E04 has actual texture-factor consumers. Keep the four-byte
interval unclassified; no padding, guessed alignment or inert stores are
introduced. Original malformed dimensions, ANM/render resources, RTTI/EH/full
linkage and game runtime remain independent open scope.

Original 149 canonical receipt closures plus the fresh private mesh closure are
verified and losslessly archived **before** changing the shared header. Each
affected previous object is rebuilt once; the new maintained mesh object is
reused in full replay. Complete original literal payloads and actual fresh COFF
relocation roles identify changed labels, including duplicates. Preserve
`core116-pre-admission-inputs.json.gz`, the source freeze, whole private proof,
full canonical results, maintained sanitizer receipt, origin audit and attested
native exports. Historical sound probes remain represented by their original
source closures and require fresh builds before new acceptance.
All72 public tests pass in292.555 seconds; the full gate passes in294.904
seconds. Temporary host products and CI bytecode caches retire automatically.
Protected retirement removes149 replaced canonical pairs and the migrated
private surface-grid pair:300 files /8,291,307 bytes (7.91 MiB). Original
source/receipt/SDK closures are verified before deletion. All773 completed
comparison results,265 source hashes and300 current canonical-file hashes remain
unchanged after cleanup. Build9.5MiB/analysis131MiB; keep the cleanup receipt
and pre-deletion path/size/hash plan. Two literal labels are reconciled through
40 verified reference roles, including duplicate full payloads. No unchanged
source cold rebuild is used for documentation or retirement.

CORE095 reconstructs the complete grid initialization, adjacent-column strip
publication, UV conversion and enemy deformation protocol. `RenderMesh.cpp`
owns grid operations, `EnemyMesh.cpp` owns the enemy consumer and its owner
constructor, and `MeshInterfaces.cpp` owns the independently exported interfaces.
These are ordinary maintained C++ bodies using the existing Animation, Session,
WindowState, Motion, Angle, Vector3 and clock owners.

## Native evidence and strict candidates

Attested Ghidra exports cover complete native routines and their support calls.
Independent constructor allocation widths, field consumers and existing startup
evidence establish a 36-byte nine-word RenderMesh and 28-byte EnemyMeshOwner.
The latter contains two actual Angle objects. Window mesh offsets are two
separate two-element integer arrays at offsets 0x38 and 0x40; this refines the
earlier pair placeholders without changing WindowState's 0x2138-byte extent.
Animation's geometry pointer supplies actual 28-byte textured vertices.

The following thirteen complete production candidates strictly replay 1,165
bytes, with independently established native relocations:

| Operation | Address | Bytes |
| --- | --- | ---: |
| EnemyMeshOwner constructor | 0x48B370 | 88 |
| Angle subtract assignment | 0x472060 | 47 |
| XY squared norm | 0x456130 | 50 |
| Animation mesh vertex pointer | 0x49DFF0 | 20 |
| EnemyState position reference | 0x499350 | 25 |
| Window mesh view X | 0x49DF00 | 23 |
| Window mesh view Y | 0x49DF20 | 23 |
| Window scaled mesh width | 0x49DFD0 | 20 |
| Window scaled mesh height | 0x49DFB0 | 20 |
| Mesh context selection | 0x49E050 | 45 |
| Grid initialization | 0x49D850 | 503 |
| Strip update | 0x49DDC0 | 194 |
| UV conversion | 0x49DF40 | 107 |

The candidate MSVC 19.44.35211 profile is C++20, /Od, /Ob0, /GS, /Gy, /Zl,
/arch:SSE2, /fp:strict, /sdl and /EHsc. This observation does not establish the
whole game's compiler profile or application authorship. All thirteen origins
remain pending independent classification; authored coverage is unchanged.

## Owned behavior

Grid initialization uses column-major Vector3 positions and textured vertices,
per-view offsets, separately computed steps, white color and reciprocal W of
one. Strip publication interleaves complete vertices from adjacent columns into
the actual Animation geometry buffers. Context selection uses the real Session
context. UV conversion divides by WindowState's scaled dimensions at 0x20A0 and
0x20A4, clamps negative values only and preserves upper overflow, negative zero
and unordered comparisons. Earlier probes using client dimensions were rejected
by strict comparison and retained only as failure evidence.

EnemyState's complete deformation method at 0x4A4190 retains the old radius for
geometry while updating current radius with the real clock. It combines XY
radial weights, BGRA channel updates, XYZ normalization and phase waves. Enemy
and grid view offsets remain separate. Clipping examines undistorted points;
UVs use those points even when displayed vertices have been displaced. Final
clock-weighted phases and strips are updated through their real owners.

The full method emits 1,548 bytes against a 1,649-byte native extent and remains
explicitly nonexact. Native code includes a 101-byte unused radius-to-byte
calculation. We have not introduced an inert local to reproduce it; stack and
control-flow differences also remain. The native interval is not shortened,
and this method receives no canonical exact credit.

## Semantic verification and remaining scope

The public semantic fixture exercises the actual production bodies under O2,
UBSan and float-cast-overflow checking. It covers eighteen grid shapes/views,
192 complete deformation combinations, repeated phases, old-radius behavior,
negative and fractional clocks, distinct source/vertex geometry, full strip
copies, end guards, scaled-versus-client clipping, getters and UV aliasing,
negative zero, NaN and upper overflow. An independent coordinate/color model
checks valid finite conversion cases. The initial model's missing negative UV
clamp was corrected; production behavior was not changed to fit that model.

Fixtures supply external buffers and startup/allocator services; they retain
real Animation, EnemyState, Session and math lifetimes. The native 878-byte mesh
constructor at 0x49CF80, allocation/deletion, publication, renderer integration,
malformed dimensions and invalid float-to-integer conversions remain open.
No linked playable game or native runtime acceptance is implied.

Private evidence includes core095-mesh-native.asm, core095-mesh-support.asm,
core095-production-bindings.json and the archived historical probe inputs.
Frozen replay of all 659 canonical units passes across 131 fresh objects and
129,436 disjoint comparison bytes, with all 233 source files unchanged during
the replay. Four complete reference target associations are now absorbed;
their free replacement APIs remain diagnostic rather than byte-exact imports.
Authored totals remain 84 exact functions and 24,209 bytes. Protected retirement
and the complete public test result are recorded in the current handoff.

CORE/EXACT-118 closes the formerly undefined whole272-byte recursive Animation
flag clear, together with three related propagation operations and the actual
child-node/iterator protocol. The dedicated1025-case production fixture executes
these real bodies; older mesh protocol fixtures retain their explicit dependency
captures. Original VM/renderer allocation and retirement remain separate.
See [Animation child traversal](ANIMATION_CHILDREN_RECONSTRUCTION.md).
