# RenderMesh scalar construction and compiler evidence

CORE/EXACT-139 subsequently closes EnemyMeshOwner allocation and unifies the
scalar factory body through natural empty-pack value initialization. See
[the current allocation evidence](ENEMY_MESH_ALLOCATION_EXACT_RECONSTRUCTION.md).

CORE/EXACT-137 investigates the complete 213-byte allocator factory at
`004712D0`. The native Enemy command at `00495BD0` supplies the process allocator,
a diagnostic label, columns 17, rows 17, surface zero and the actual State view.
The returned 36-byte RenderMesh is published in the EnemyMeshOwner established
by [the retirement audit](ENEMY_MESH_LIFETIME_RECONSTRUCTION.md).

## Native protocol and independent anchors

The complete body ends with `RET 14h`: the diagnostic pointer and four integer
values are stack arguments; ECX is the allocator receiver. Scalar operator new
allocates 36 bytes. On the nonnull path, compiler initialization precedes four
calls to the eight-byte reference identity at `0040B280`, evaluated from the last
argument toward the first. Their returned references are dereferenced and passed
to the already accepted four-integer RenderMesh constructor at `0049CF80`.
The null branch and complete return path remain compared.

The 31-byte zero-initialization helper at `0040C080` already has canonical
physical ownership through HitCtrlInf compiler initialization. Its memset call,
size argument and destination establish its operation independently. The
reference identity at `0040B280` also already has physical ownership through an
SDK storage-address contribution. Typed SDK forwarding emits the same complete
eight bytes; no second physical mapping or unique source-origin claim follows.

The factory's exception handler at `00568EF4` references FuncInfo at `005AA484`.
Its magic is 19930522h, maximum state one and flags one. The eight-byte unwind
map at `005AA47C` contains state -1 and cleanup address `00568EE0`. That cleanup
passes the original allocation and size 36 to sized scalar delete. Its complete
20-byte contribution retains five trailing CC bytes. The 29-byte handler,
36-byte FuncInfo, eight-byte map and 20-byte cleanup total 93 support bytes;
they do not add physical exact coverage. Ghidra's bounded existing listing
contains the handler but omits the cleanup instructions; complete locked-PE
decoding preserves the omitted cleanup and alignment without changing the DB.

## Natural source and bounded compiler observations

The shared allocator now has a parameterized scalar-construction overload.
Arguments are taken by value, then forwarded with the pinned SDK's std::forward
into ordinary `new T(args...)`. The existing no-argument overload retains
ordinary `new T` default initialization. No manual zero stores, replacement SDK
implementation, source-profile branch or exception wrapper is introduced.
MeshResourceAccess.cpp owns the explicit four-integer RenderMesh instantiation.

| Complete private experiment | Factory bytes | Observation |
| --- | ---: | --- |
| Existing struct, C++20 | 135 | SDK forwarding is intrinsic |
| Existing struct, C++17 | 203 | Four actual forwarding calls remain |
| Public class, C++17 | 213 | Compiler initialization supplies the remaining call |

The public-class declaration retains the same nine words, member visibility,
constructor/destructor contracts and 36-byte layout. The WeaponStoneInfo forward
declaration agrees with it. Its compiler-generated initialization call supports
the class-tag inference separately from the original layout evidence.

Only MeshResourceAccess.cpp changes to the demonstrated C++17 profile. The
other translation units retain their existing profiles. A private
MeshInterfaces.cpp trial rejects C++17 because WindowState has actual C++20
bit-field initializers; those initializers are preserved. The successful
MeshResourceAccess trial retains all five existing complete contributions.
These results do not establish the game's global language mode or flags.

## Verification scope

Original input versions and receipts for all 163 prior objects are archived
before production changes. Captured include closures select 36 objects and 228
prior units for fresh serial builds; 127 objects remain reusable. The maintained
source/probe path set stays at 278. Canonical replay preserves prior target
addresses, complete extents and independently established relocation roles,
while updating genuine class-tag symbols and compiler-generated literal labels.

The owned fixture uses the actual shared factory for nested mesh creation and
release. The complete mesh-lifetime fixture uses it for resource-absent objects
and its real construction matrix across columns, rows, surface modes, view
indices, widths and flags. Original VM creation remains an explicit fixture
boundary. These successful-construction tests do not claim allocation-failure
behavior or original renderer/startup integration; native EH is checked through
its complete independently anchored code and metadata.

EnemyMeshOwner's separate 82-byte default allocation and the whole 1,649-byte
mesh deformation remain unresolved. Neither receives new source or exact credit
from this parameterized RenderMesh factory. Final results are recorded below
and in [the current handoff](RE_HANDOFF.md).

The 36 fresh objects preserve all 228 prior affected units. The replay resolves
38 complete literal roles with 38 compiler-label renames and two class-tag
definition-symbol changes; destinations and complete extents remain unchanged.
Public CI passes all 81 tests in 415.228 seconds. Three focused UBSan /
float-cast-overflow fixtures pass in 48.898 seconds, including 3,433 mesh-lifetime
cases and 945 surface grids. Both actual-factory lifecycle fixtures additionally
pass ASan / UBSan / float-cast-overflow in 44.008 seconds. Frozen validation inputs
and private logs bind these results to the maintained source.

After authentic input and receipt preservation, 36 superseded canonical pairs
and four completed private probe pairs are retired. All 889 current units then
strictly replay from existing objects, covering 167,588 disjoint comparison
bytes. All 326 protected product hashes and 278 source hashes remain unchanged;
cleanup performs zero compiler invocations. The private retirement inventory,
original-input archive and final audit retain the detailed proof.
