# EnemyMeshOwner value construction and exact allocation

CORE/EXACT-139 closes the complete 82-byte EnemyMeshOwner allocation factory at
`0048B010`. It preserves the complete 88-byte constructor at `0048B370`, the
28-byte owner layout and the previously accepted nested retirement chain. The
factory was already reviewed authored; this batch adds source and physical exact
coverage without changing its origin classification.

## Native initialization and natural source

The complete factory calls scalar operator new for 28 bytes, branches around
construction when the returned pointer is null, clears all seven words and calls
the owner constructor. Its original diagnostic pointer is an unused stack
argument, and it ends with RET 4h. The separate constructor establishes the
mesh pointer, opaque word, two radii and color as zero and invokes the real Angle
default constructor for both phase members. Independent Enemy command publication
and later deformation/retirement consumers establish this owned game object;
see [the lifetime evidence](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md).

The maintained owner now expresses the same initialization in default member
initializers and a constructor defaulted at its first declaration. The shared
allocator has one variadic body: copied arguments are forwarded into ordinary
`new T(args...)`. An empty argument pack therefore value-initializes T. For this
non-user-provided default constructor, value initialization naturally performs
the initial zero-initialization before the real member initialization. There
are no handwritten preclear stores, inert locals or duplicate constructor bodies.

A private locked-compiler experiment emits both complete native contributions:
82 bytes for allocation and 88 for construction. Independent operator-new and
Angle/owner constructor anchors strictly resolve every relocation. A second
experiment includes all eight existing MeshInterfaces methods; all ten complete
contributions strictly match. This representation explains the previously
unresolved seven zero stores through standard initialization semantics. It is a
supported reconstruction, not proof of original source spelling.

The previous no-argument `new T` overload is removed in favor of the shared
variadic expression used by both default and parameterized allocation. Existing
scalar-owner instantiations and their callers preserve their complete native
bytes. Their decorated names now encode the empty template pack; canonical
relocation destinations and target extents remain fixed. No type-specific
allocation specialization or profile-selected source body is introduced.

## Build ownership and exception boundary

MeshInterfaces.cpp owns the explicit EnemyMeshOwner allocation instantiation and
therefore emits its defaulted constructor. The canonical constructor mapping
moves from EnemyMesh.cpp to that provider. EnemyMesh.cpp retains the actual
nontrivial destructor and outer release instantiation. All existing object
layouts and member visibility are preserved.

Only the MeshInterfaces profile drops /EHsc, matching the complete native scalar
factory without an exception-registration frame. Its eight prior interfaces
remain exact under that profile. Other profiles, including EnemyMesh destruction
and the C++17 parameterized RenderMesh allocation, retain their existing options.
The owner constructor's exception contract is not changed to noexcept: the real
Angle constructor is potentially throwing, so the defaulted enclosing constructor
remains potentially throwing and nontrivial. The portable fixture asserts both
traits. The tests do not claim original allocation-failure or cross-module
exception behavior; the native profile observation is bounded to this provider.

## Verification scope

All 163 original object/receipt pairs and authentic input versions are preserved
before production changes. Actual include closures select 31 objects and 205
existing units; 132 objects remain reusable. Every selected object is built once.
The maintained source/probe path set remains 278 entries. The complete old
canonical contracts, original relocation roles and whole unresolved deformation
extent remain separately checked.

The expanded owned-mesh fixture creates both outer owners and inner meshes
through the actual shared factory. It verifies every initialized field, positive
floating zero for radii and phases, direct default construction, an empty heap
owner and nested buffer/handle retirement across multiple column counts. It
retains the cross-thread observation that game lock one is available during
nested destruction. The constructor trait checks prevent an accidental noexcept
or trivial-constructor substitution. Existing geometric and surface fixtures
continue to run with genuine owners and explicit original resource boundaries.

The 1,649-byte whole deformation remains nonexact, and the enclosing Enemy
opcode dispatcher remains unimplemented. This factory does not establish their
exactness or original game runtime. Current results are recorded below and in
[the handoff](RE_HANDOFF.md).

Public CI passes all 81 tests in 358.927 seconds. Three focused UBSan /
float-cast-overflow fixtures pass in 33.918 seconds, and both actual-owner mesh
lifecycle fixtures pass ASan / UBSan / float-cast-overflow in 32.779 seconds.
The existing destructor and parameterized mesh factory's complete EH/folded
support also strictly replay over 197 bytes, without additional physical credit.
Validation inputs and logs are SHA-bound in the private gate receipt.

The affected replay preserves 38 independently anchored literal roles across
38 compiler-label renames and six empty-pack definition-symbol changes. After
archiving original inputs and immutable receipts, 31 replaced canonical pairs
and two completed private probe pairs are retired. All 890 units then strictly
replay from existing objects over 167,670 disjoint comparison bytes. All 326
protected product hashes and 278 source hashes remain unchanged; cleanup invokes
no compiler. Authored exact coverage is 181 functions / 47,071 bytes, while the
190 independently confirmed authored origins remain unchanged.
