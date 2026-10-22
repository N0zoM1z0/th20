# AnimationFile destruction and template-array lifetime

CORE/EXACT-132 accepts nine complete physical units / 866 disjoint comparison
bytes from the actual File and Animation owners. File-loaded resource clearing
remains an undefined interface; these results do not establish Renderer
detachment, file loading, VM execution or a playable program.

| Entry | Maintained operation | Body / compared bytes | Origin |
| --- | --- | ---: | --- |
| 004477B0 | DiagnosticAllocator::allocate_object<AnimationFile> | 67 / 67 | Authored |
| 00449310 | AnimationFile::~AnimationFile | 85 / 90 | Authored |
| 004473A0 | DiagnosticAllocator::release_object<AnimationFile> | 97 / 97 | Authored |
| 004476C0 | DiagnosticAllocator::allocate_array<Animation> | 238 / 238 | Authored |
| 004472C0 | DiagnosticAllocator::release_array<Animation> | 108 / 108 | Authored |
| 00447850 | std::destroy_at<AnimationFile> | 16 / 16 | Library |
| 00449760 | Compiler scalar deleting destructor for File | 46 / 46 | Compiler |
| 004496B0 | Compiler vector deleting destructor for Animation | 170 / 175 | Compiler |
| 00449240 | std::pmr::string destruction | 29 / 29 | Library |

All primary functions retain complete control flow, returns and compiler
contributions. The two five-byte alignment tails remain compared. The generated
31-byte File initializer folds to the already-covered `0040C080` implementation
and adds no physical credit. No destructor/deleting wrapper is handwritten to
imitate compiler code.

## Independent native owner and allocation evidence

Attested full listings and callers distinguish File allocation from loaded-data
preparation. The native preload owner at `0044ED40` takes game lock 17, allocates
the actual 112-byte File, publishes it into a 42-entry file table and stores its
index. Loading at `0044A700` separately allocates template storage. That complete
array factory passes stride `0x5E4`, the real Animation constructor at `00448B40`
and its nontrivial destructor at `00449370` to the EH vector constructor helper.
It writes the actual array cookie and retains both multiplication and cookie-add
overflow saturation paths. Signed count behavior follows the existing shared
new-array template; no source overflow or allocation substitute is introduced.

The independently read preload allocation diagnostic at `0056E3B0` names
`src/core/sprtlib.cpp:950 SprtGroupInf`. AnimationFile is the maintained
descriptive name; the diagnostic is retained as original target evidence rather
than silently treated as recovered class/RTTI spelling.

The full File constructor remains 186 bytes. Its two 28-byte PMR strings at +4
and +20, buffer/template pointers, counts and atomic stage already have one
canonical declaration. Independent initialization, binding and resource consumers
establish storage; allocation size alone is not a layout oracle. See
[Animation lifetime](EXACT_ANIMATION_LIFETIME_RECONSTRUCTION.md) and
[template preparation](ANIMATION_BINDING_RECONSTRUCTION.md).

## Source and compiler observations

File now uses a public class declaration, including its Graphics and Bullet
forward declarations. Storage, member access and constructor exception contract
are unchanged. As with [Node](FUNCTION_CHAIN_ALLOCATION_EXACT_RECONSTRUCTION.md)
and [Region](DAMAGE_REGION_ALLOCATION_EXACT_RECONSTRUCTION.md), the existing
shared `new T` body then emits the native automatic initializer. No explicit
clear, brace/value substitution or allocator specialization is maintained.

File construction and scalar allocation stay in AnimationFile.cpp under its
existing C++20/Od/Ob0/GS/Gy/Zl/SSE2/fp:precise/sdl profile. Adding /EHsc to that
factory produces 129 bytes instead of 67 because its constructor declaration
remains potentially throwing; the exception contract is not changed to force
emission. File destruction and typed array/release instantiations live beside
Animation lifetime in Animation.cpp under its existing /EHsc profile. That
profile naturally emits all 238 array-allocation bytes and 90 complete File
destruction bytes. Without /EHsc, those contributions are 185 and 43 bytes and
are rejected. Per-source recipes do not establish the original global build or
translation-unit partition.

The File destructor calls its real `clear()` interface, then automatic member
destruction retires stem before filename. The original 284-byte clear method is
reviewed separately and remains unimplemented. Seven resource-absent fixtures
now provide that actual unresolved interface, allowing production destruction
and ordinary string member teardown to run. No production empty clear or loaded
resource lifetime substitute is added.

## Destruction, locks and complete ABI support

Scalar File release ignores null, invokes destroy_at before acquiring game lock
one, and applies unsized scalar delete under the guard. The complete 16-byte
STL wrapper calls the compiler scalar deleting destructor with flags zero.
That wrapper calls ordinary File destruction and optionally sized delete for
112 bytes. The actual SDK destruction expression and native typed chain reject
the automatic ExceptionPtrDestroy label at `00447850` as its semantic identity.

Array release also accepts null, but acquires lock one before delete[]. Its
complete compiler wrapper retains both array and scalar flag branches. The array
branch reads the preceding count cookie, destroys elements in reverse order and
optionally performs sized array delete on the original allocation. A separate
native Concurrency array-deletion caller corroborates the two-argument sized
array-delete entry at `0054303B`; that full 14-byte callee forwards to ordinary
array delete. File/string/Animation destructor and runtime anchors come from
independently reviewed complete bodies, never solved compared fields.

All nine EH/metadata/cleanup/initializer support records, totaling 257 bytes,
strictly replay without extra coverage. File and vector destruction share the
complete 29-byte handler and zero-state flags-5 FuncInfo. Array allocation has
the full 39-byte handler at `0056828D`, complete 36-byte FuncInfo at `005A9FB0`,
one eight-byte unwind entry and a complete 13-byte lock-guard cleanup funclet.
The read-only range listing retains this handler despite missing Ghidra function
membership. It is not truncated or treated as padding.

## Origin and boundary review

Five previously exact application bodies are now independently classified:
AnimationBase construction (725 bytes), Animation construction (498), ordinary
Animation destruction (62), resource retirement (171) and File construction
(186). Their custom game storage, nontrivial allocation/deletion callbacks,
geometry/callback/handle state and File consumers establish application origin
independently of matching. Together with the five new application roots, they
add 2,237 bytes to reviewed authored exact coverage; existing physical coverage
is not counted twice. The two STL and two compiler roots are separate exclusions.

The full native File::clear at `0044AB00` is also authored, from its actual game
File/Renderer/allocator protocol, but remains source-absent and nonexact. Its
null-buffer path returns immediately. Otherwise it detaches File animations,
retires texture data, releases/reset arrays, releases the +6C and file buffers,
then destroys/releases templates. The +6C producer and complete Renderer owner
remain open; the observed pointer use does not silently rewrite its maintained
opaque word. No clear implementation, source mapping, canonical unit or partial
credit follows from the declaration or origin decision.

Complete locked-PE decoding reconciles 15 whole bodies, every direct branch and
all returns. Source origins and boundaries remain separate from linkage and
runtime acceptance. Original names and class spelling remain inferences.

## Semantic and frozen verification

The extended actual-owner fixture covers zero, one, three and seventeen template
elements; real geometry and virtual callbacks prove reverse retirement and
cleanup order. Another thread's try_lock distinguishes destruction under the
array guard from scalar File destruction before its guard. Three long filename/
stem pairs use an instrumented PMR resource to prove clear precedes both string
releases and that stem retires first. The fixture permits only resource-absent
File clear; original Renderer-mediated resource retirement is not simulated.

All 80 public tests pass in 342.394 seconds. The private actual-owner lifetime
fixture also passes ASan/UBSan in 8.546 seconds. Retirement removes 66 superseded
object/receipt products totaling 2,468,065 bytes after preserving authentic
SHA-bound inputs and immutable receipts in a verified 855,825-byte archive.
All 861 current units then strictly replay from existing objects with all 326
protected hashes and frozen source unchanged; cleanup invokes no compiler.
All 852 prior physical units retain their extents, profiles, targets and
relocation roles.

Before editing, all 163 original object/receipt pairs are verified and authentic
input versions are archived by SHA. Actual include lists select 31 affected
objects; each builds once and all 128 previous affected units strictly replay.
The other 132 objects retain their original immutable receipts. Eighteen original
literal roles preserve complete NUL-terminated payloads and independent target
literal identity; six fresh generated labels change without changing anchors.
All 278 source/probe paths remain present. Current validation, products and
retirement records are in [the handoff](RE_HANDOFF.md).

The graph contains 861 strict physical units, 163 objects and 165,103 disjoint
comparison bytes. There are 869 source mappings, with eight mapped whole functions
nonexact. Confirmed origins are 163 authored and 40 excluded, with 6,725 pending;
158 authored functions / 44,627 bytes are exact. File::clear is deliberately
included in the authored denominator while remaining absent from source coverage.
These reviewed-subset totals do not measure whole-game completion.

Private evidence includes the attested core132 File/producer/PMR/EH listings,
`core132-new-exact-results.json`, `core132-eh-support.json`,
`core132-boundaries.json` and `core132-pre-header-inputs.json.gz`. The reference's
range checks, manual clears and repaired preload-failure table entry are not
imported. Actual loaded-data clearing, preload failure lifetime, Renderer, whole
VM and game startup/runtime remain open.
