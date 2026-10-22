# Enemy mesh ownership, retirement and origin audit

CORE/EXACT-136 closes the actual EnemyMeshOwner retirement chain. Its native
nontrivial destructor releases the owned RenderMesh through the process allocator
and clears its pointer. The maintained declaration previously exposed only the
constructor; an implicit trivial destructor could not reproduce this ownership.
The existing struct, 28-byte layout and constructor exception declaration remain
unchanged. Animation.cpp's separate File/PMR retirement is unaffected.

| Native head | Maintained operation | Body / compared bytes | Origin |
| --- | --- | ---: | --- |
| 004A38A0 | EnemyMeshOwner destruction | 79 / 84 | Authored |
| 0048AF30 | DiagnosticAllocator scalar EnemyMeshOwner release | 97 / 97 | Authored |
| 004A2800 | DiagnosticAllocator scalar RenderMesh release | 97 / 97 | Authored |
| 0048B090 | std::destroy_at for EnemyMeshOwner | 16 / 16 | Library |
| 004713B0 | std::destroy_at for RenderMesh | 16 / 16 | Library |
| 0048BE80 | Generated EnemyMeshOwner scalar deleting destructor | 46 / 46 | Compiler |
| 004720D0 | Generated RenderMesh scalar deleting destructor | 46 / 46 | Compiler |

These seven complete contributions add 402 disjoint comparison bytes. The five
actual CC bytes following the owner's 79-byte body remain compared. No wrapper,
SDK implementation, instruction array or assembly is handwritten.

## Actual producers and nested retirement

The bounded Enemy command listing at `00495A9A` first releases the existing
State+2D4 owner and clears that field, then calls the native 28-byte allocation
factory at `0048B010` and publishes its result. Subsequent instructions set the
radius, current radius 16, color and two zero phases. A positive radius creates
a 17-by-17 RenderMesh through `004712D0`, with surface zero and the State view
index, and stores that pointer in the owner. This is concrete game storage and
policy, independent of the factory or destructor comparison fields.

Ghidra's function-based callers query reports no caller for `0048B010`, but its
xref at `00495ACD` and the attested listing preserve the actual call in the large
Enemy dispatcher. No whole-dispatcher source or exact credit follows from this
bounded command slice. The Enemy destructor at `004A3B10` independently calls
owner release at `004A3C88` for Enemy+35C, the same member at State+2D4 within
Enemy's +88 State subobject, then clears it.

Both scalar release templates handle null, destroy the object before acquiring
game lock one, and release its storage with unsized scalar delete while guarded.
Owner destruction calls the real nested RenderMesh release and only afterward
clears its own pointer. The inner release executes the previously accepted
RenderMesh destructor, which retires root/strip handles and its owned arrays.
Thus inner resources and mesh storage retire before outer owner storage; the
outer release guard does not enclose nested destruction.

The actual SDK destroy_at expressions emit the complete sixteen-byte calls to
the compiler scalar deleting destructors with flags zero. Those wrappers retain
their optional sized-delete branches: 28 bytes for EnemyMeshOwner and 36 for
RenderMesh. The automatic ExceptionPtrDestroy and Concurrency condition-variable
labels do not establish their semantic identities. Actual typed callers,
complete destructor destinations, object sizes and SDK expressions establish
the roles separately from the zero-difference replay.

The complete 29-byte owner EH handler at `00567600` is read through a bounded
attested range, including both initial NOPs. It names the already-established
zero-state flags-5 FuncInfo at `005A91B8` and the established security-cookie and
C++ frame handlers. All 29 handler bytes and 36 metadata bytes strictly replay
as support without additional physical credit. Canonical relocations use these
independently reviewed identities and complete callee bodies.

## Source ownership and allocation boundary

EnemyMesh.cpp owns the real destructor and explicit instantiation of the shared
outer release template. The destructor naturally instantiates inner release;
ordinary SDK and compiler mechanisms emit both destroy_at and deleting wrappers.
The shared release body remains in DiagnosticAllocator.hpp. No production
source file, compiler profile, layout or alternate destructor body is added.

The original scalar allocation factory remains a complete 82-byte native body,
with seven explicit zero stores before the real constructor. A private probe
using the existing struct and shared new T body without /EHsc produces 57 bytes;
the same natural struct with the newly established destructor under /EHsc
produces 119 bytes. A private public-class declaration produces 129 bytes under
/EHsc and introduces an automatic initializer helper. These complete observations
do not explain native allocation. The maintained struct and constructor contract
are preserved; no manual preclear or fake noexcept declaration is added.
`0048B010` is reviewed authored from its actual allocator receiver, diagnostic
argument, object constructor and game publication, but has no source mapping or
canonical exact unit. The separate four-argument RenderMesh allocation factory
at `004712D0` remains outside this admission; CORE/EXACT-137 subsequently accepts
it through [the parameterized allocation audit](MESH_ALLOCATION_EXACT_RECONSTRUCTION.md).

## Origins and whole deformation

Three existing exact game contributions now have independently reviewed authored
origins: the 88-byte EnemyMeshOwner constructor, the 20-byte actual Animation
geometry getter and the 25-byte EnemyState position getter. The command producer,
phase/radius/color consumers, real Animation+564 geometry storage and nested
State+110 Motion access establish their custom owner roles. Their 133 bytes were
already physical coverage and are not counted twice.

The complete 1,649-byte EnemyState deformation at `004A4190` is also reviewed as
authored. Its game clock, Window offsets, owner radius/phases/color, vertex
channel policy and final strip publication are explicit custom behavior. Its
maintained complete contribution remains 1,548 bytes and receives no exact unit
or authored exact credit. The full native body, all branches and its return
remain in the boundary review.

The native interval `004A427C..004A42E0` contains 101 bytes of radius-dependent
conversion. A full-body operand audit finds three writes to the local byte at
EBP-31, no overlapping direct read and no direct formation of that byte's
address. Floating-point environment effects are outside the accepted fixture
domain. This observation does not authorize an inert source local or a cropped
comparison; other stack/register differences remain. The generic 47-byte Angle
subtraction and 50-byte XY squared norm retain verified semantic roles but
unresolved original physical origins. Their provenance is not inferred merely
from game callers or matching arithmetic.

## Verification and fixture domain

All 163 prior object/receipt pairs and original input versions are preserved
before editing. Actual include closures select five objects / sixteen existing
units. Each affected object builds once under its existing profile, all sixteen
old units remain exact and the other 158 objects keep their immutable receipts.
Four complete literal roles retain the same labels and independent destinations.
All previous targets, extents, profiles and relocation roles are preserved.
The maintained source/probe path set remains 278 entries.

The expanded mesh fixture allocates actual outer owners and nested RenderMesh
objects, with zero, one, three and seventeen columns and real owned vertex,
position, handle and pointer-array storage. Root-handle retirement observes the
live enclosing owner and confirms from another thread that game lock one is
available during nested destruction. Null outer release and an empty heap owner
are also covered. Existing geometric fixtures explicitly detach borrowed mesh
views before their owners are destroyed. Complete prior deformation, clipping,
phase, UV and strip checks continue to execute.

Handle retirement and Graphics startup remain explicit resource-absent fixture
boundaries. The tests corroborate owned memory lifetime and lock order, without
claiming original VM handle retirement, allocation failure behavior or native
rendering. Current test and retirement results are recorded in the
[handoff](RE_HANDOFF.md). Private core136 native exports, fresh-build results,
full boundary audit, source probes and SHA-bound original archives retain the
underlying evidence.

Public CI passes all 81 tests in 415.013 seconds. The focused existing UBSan /
float-cast-overflow fixture passes in 11.604 seconds; a private ASan / UBSan /
float-cast-overflow build passes in 14.720 seconds. Its first link exposed a
missing TaskInfo RTTI definition in the private test closure; adding the existing
TaskInfo.cpp implementation resolves it without changing production code or
disabling RTTI. These timings and input hashes are retained in the private gates.

Five superseded canonical object/receipt pairs and three completed private probe
pairs are retired after authentic input and receipt preservation. All 888 units
then strictly replay from existing objects, covering 167,375 disjoint comparison
bytes. All 326 current product hashes and 278 frozen source hashes remain
unchanged; cleanup invokes no compiler. Shared archived inputs are referenced by
SHA, while additional private probe inputs are preserved inline.
