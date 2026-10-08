# Sprite, ANM, rendering and texture review

CORE/EXACT-095 closes four further complete native mesh operations: context
selection, UV conversion, strip update and grid initialization. Their reference
target associations now point to canonical actual-owner bodies; the reference
free replacement wrappers remain diagnostic rather than byte-exact imports.
Thirteen complete mesh/interface roots add 1,165 comparison bytes. The whole
enemy deformation consumer remains 1,548/native 1,649 and receives no exact
credit. See [mesh protocol evidence](RENDER_MESH_RECONSTRUCTION.md). Historical
REF-042 counts and open-owner descriptions below retain their original scope.

EXACT-060 independently reconstructs the real ANM Base/Animation owners rather
than importing reference raw clearing and packed fields. Ten whole lifetime,
partial-reset, resource-release and recursive-scale/extent functions add2,870
comparison bytes. All427 units/79 cold objects/79,802 disjoint bytes replay.
The true nontrivial destructor, complete flags5 EH and raw Vector2[4] construction
close the prior707/native725 Base hypothesis. Natural pooled115/native59 remains
rejected; Controller/file/callback/global and whole Enemy work remain pending.
See EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md. Review findings below are
historical and are not claims that these newly closed ten bodies remain open.

## REF-042 — 2026-10-07

All **540 remaining Sprite implementations** were individually read across
**46 indexed files**, including nested lambdas, inline members, CPU drivers,
fixtures and the opcode evidence writer. Original CRLF body and file hashes
are bound to the clean pinned reference. Supporting value headers, CMake,
callback registrations and documented oracle domains were also read.

Decisions are **7 absorbed / 153 nonexact / 380 support**. Five files with
17 indexed grammar sites were manually reconciled without changing the
reference: two array-new expressions, one callback-registration initializer,
and fourteen calling-convention annotation sites. All explicit bodies at these
sites are indexed; no missing local implementation was found.

Global coverage reaches **6,640 terminal / 304 pending** of 6,944 bodies;
parser-gap coverage is **96 complete / 17 pending files**. All 540 Sprite bodies
now have individual decisions. StageBackground 121 and 183 other bodies remain;
the exhaustive review goal is active.

## Natural component batch

Original construction at `448D70` calls actual integer, angle, matrix and mixed
ANM value constructors, rather than clearing the reference's raw aggregate.
The native Controller constructor passes actual constructor pointers and array
strides: four 20-byte corners, 1,048,576 28-byte textured vertices and 65,536 20-byte
colored vertices. These establish value boundaries without accepting the
131,337,876-byte Controller, its Worker or its resource lifetime.

| Complete contribution | Address | Bytes |
| --- | --- | ---: |
| IntegerTriple constructor | `0x00414090` | 43 |
| Matrix4 constructor | `0x00447DC0` | 30 |
| SpriteCorner constructor | `0x00449110` | 44 |
| SpriteColoredVertex constructor | `0x00449140` | 43 |
| SpriteTexturedVertex constructor | `0x00449170` | 65 |
| AnmVariables constructor | `0x00449050` | 182 |
| Integer interpolation constructor | `0x00447980` | 94 |
| IntegerTriple interpolation constructor | `0x00447A50` | 97 |
| Angle interpolation constructor | `0x00447BA0` | 97 |
| ARGB1555 accumulation | `0x00451640` | 183 |
| ARGB4444 accumulation | `0x00451700` | 183 |
| ARGB8332 accumulation | `0x004517C0` | 187 |
| BGRA8888 accumulation | `0x00451880` | 139 |

These **13 new canonical units add 1,387 disjoint complete bytes**. All 234 units
pass cold construction from 56 objects and complete relocation replay, covering
17,277 disjoint bytes. Source presence 234, pending origins 173 and library 4 are
separate from authored 57 / 4,074 bytes, which remain unchanged. Original tags,
field roles and authored/compiler/library origins remain pending.

The shared Interpolation template gains three genuine value instantiations;
there is one semantic implementation. IntegerTriple is three signed components,
used by native color curves. Angle construction calls the already recovered
Angle value, preserving its distinction from float interpolation. AnmVariables
contains seven integer words and nine floats in the actual 64-byte member at
Base+444; offset labels retain unknown names. Matrix4 contains sixteen floats:
original `443020` copies both 64-byte matrices, scales diagonal floats and passes
matrix storage through real D3DX rotation/multiply and D3D transform paths.
Decompiler library aliases do not establish the original matrix type spelling.

The three Sprite vertex values contain the existing Vector3, with actual UV,
RHW and diffuse fields. Sprite diffuse defaults to white; the previously
recovered Screen ColoredVertex has a different zero diffuse default. Neither
value supplies an enclosing Controller facade.

Texel accumulation uses the independently observed uint16 channel extraction
widths and native little-endian bitfield layout, or four BGRA bytes. Null RGB
returns before dereferencing pixel/count; nonzero alpha gates RGB additions,
then the count increments. Unsigned wrapping and count/RGB alias order are
preserved. The whole transparent-edge repair loop remains nonexact.

All 13 native ranges decode completely, close their direct branches and agree
with attested Ghidra. Native Vector3/Timer/Angle/IntegerTriple/memset callees were
read before probing; canonical relocations use those independent destinations,
not solved comparison fields. Portable C++20/g++13 with UBSan passes
**2,613,444 independent checks**: dirty guarded value construction, every
16-bit texel representation, packed channel decoding, random BGRA inputs,
wrapping arithmetic, alias order, input preservation and null short circuits.
No original Windows oracle was rerun.

## Complete reference diagnostics and unresolved owners

All 36 unmodified reference production translation units were freshly compiled
serially after the maintained source freeze, preserving the reviewed CMake
strict-FP renderer/platform versus separate entry-adapter profiles and inherited
include paths. They define 1,516 functions, including 297 static functions.
**212 complete diagnostic comparisons across 159 bodies** yield 210 size
differences and 2 structural mismatches; no structural match is promoted.
Reference address associations remain diagnostic, not accepted mappings.
Two unbounded ANM associations were skipped rather than sliced at an interior
address. The independently written typed AnimationBase probe has 707 bytes
against the native 725; the whole constructor is rejected without a prefix
comparison or compiler-shaping workaround.

The reference Base uses packed raw words, explicit gaps and whole-range clearing
where original constructors use real float, interpolation and matrix members.
Animation owns five intrusive links, callbacks, geometry and parent references;
Controller owns a Worker, typed containers, two embedded Animations, a large
pool and vertex arrays. Full construction, EH, list/iterator, allocator, callback
vtable and resource destruction remain unclosed. Small getters or setters on
these owners receive no padded-facade credit.

The pool review preserves generation wrapping/skipping zero, FFFF heap lookup,
inclusive pooled address bounds, callback replacement during retirement,
child-before-parent queuing and mutation-aware iterator observers. Four list
registration functions and primary/secondary updates are merged by reference
bool selectors. Interrupt propagation visits self/immediate children, with the
returned-iterator temporary's observer-clearing quirk; it does not recurse into
grandchildren. Named spawning preserves counters, optional output order,
alternate group stride, inherited transforms and VM-before-handle assignment.

File preload/postload/task flows retain writable archive bytes, linked entry
stages, texture/sprite/script tables, template initialization and frame budgets.
Reference bounds exceptions, clearing an original dangling failure slot, and
replacing the original unload null write with an exception are explicit behavior
differences. PMR/filesystem/thread/allocator/COM lifetimes remain dependencies.

The complete ANM source dispatcher contains 163 known cases, 161 routed away from
default. The native 161-slot table and 636-byte index are independently checked;
default routes through `42B8D3` to `434DAD`, including opcode 0 and label 5.
Writable argument destinations, RNG consumption, clock restoration, wait and
interrupt state, six interpolation kinds and seven geometry generators were
reviewed. Generic source samplers and extracted dispatch helpers do not restore
the single original member/EH/result ABI. External camera/binding/spawn/effect/
allocation domains and exceptional numerical paths remain open.

Rendering review covers anchor/parent/screen transforms, snap/viewport early
outs, cached texture/blend/filter/sampler state, packed color/tint/fog modes,
colored primitive capacities and original extra/unused writes, matrix projection
and order, stream/FVF changes and grid-strip generation. COM traces, finite
projection fixtures and selected storage checks do not establish complete
rendered gameplay, device-loss behavior or original owner linkage.

## Retained evidence limits

| Historical report | Recorded checks/cases | Current distinct source hashes | Scope limits |
| --- | ---: | ---: | --- |
| ANM CPU | 261,652 | 8/8 | Prepared raw Controller; finite arithmetic; external domains fail fast |
| Controller CPU | 14 | 13/14 | Worker header stale; zero/A5 same storage; empty/32 pooled active; no active worker/geometry |
| Sprite CPU | 29,252 | 7/7 | Scoped buffers and COM spies; valid format 0..8; no full Controller or GPU rendering |
| File preload | 3,308 | 1/1 | Source integration, 73 assets; no native preload ABI/postload/live teardown |
| Shared pool CPU | 2,915,831 | 389/389 | Multiple suites; prepared globals/64-element pool snapshots/COM and pointer normalization |
| Texture CPU/GPU | 2,181 | 2/2 | 469,066,224 pixel comparisons; dynamic/render-target uninitialized pixels excluded |

Texture scenarios use scales 1/1.5/2, external crop insets 0/1/8 and low-resolution
flags. Mesh fixtures normalize separate allocations and use small positive grid
counts. Shared pool results include many assertions per scenario and other
subsystems. Current hashes do not bind the executed test binary, compiler,
startup state, all transitive dependencies or every domain.

The evidence/report writer and all test drivers were fully read but never
executed here. No target or Ghidra bytes were changed. Fresh canonical and
portable evidence belongs to the independently maintained components above;
retained reports remain historical supporting evidence.
