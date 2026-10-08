# Mesh geometry and enemy deformation

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
