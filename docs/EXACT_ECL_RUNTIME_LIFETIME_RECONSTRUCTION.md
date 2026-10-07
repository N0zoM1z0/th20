# Whole ECL Runtime/Manager lifetime and async disposal

EXACT-071 closes ten complete native contributions on the locked Japanese
v1.00a Steamless target: 701 body bytes and 706 comparison bytes. The existing
72-byte Runtime and 112-byte Manager now have actual maintained lifetime bodies;
the shared DiagnosticAllocator has the real typed scalar disposal protocol.
This is a coherent dependency batch for the accepted whole ECL tick and the
still-open 41 KB Enemy execution root. No opcode fragments earn credit.

| Maintained member | Native entry | Body bytes | Comparison bytes |
| --- | --- | ---: | ---: |
| EclRuntime::EclRuntime | 004A3580 | 104 | 104 |
| EclRuntime::~EclRuntime | 0048B8D0 | 34 | 34 |
| Runtime compiler scalar deleting destructor | 0048BEE0 | 46 | 46 |
| EclManager::EclManager | 004A35F0 | 86 | 86 |
| EclManager::~EclManager | 004A3CE0 | 83 | 88 |
| Manager compiler scalar deleting destructor | 004A4120 | 46 | 46 |
| EclManager::terminate_async | 004973C0 | 93 | 93 |
| DiagnosticAllocator::release_object<EclRuntime> | 0048AFA0 | 97 | 97 |
| DiagnosticAllocator::release_object<IntrusiveLink<EclRuntime>> | 00413B70 | 97 | 97 |
| EclManager::read_float default | 004AB070 | 15 | 15 |

All ten source origins remain unknown. Existing authored totals remain
64 functions /16,948 bytes. Complete compiler destruction padding and associated
EH support are compared separately from body and authored counts.

## Native lifetime and valid lifecycle

Runtime construction initializes time, both position words, async id, manager
pointer, signal, rank and flags to zero. Its real PMR stack and interpolation
vector capture the default resource without allocation. Runtime initialization
is distinct from reset: the accepted Manager reset later establishes -1 inactive
position/async sentinels, installs main.manager, chooses current_runtime and
reinitializes the runtime-list sentinel. Old test-only constructors that chose
-1 initially do not establish the native constructor protocol.

The final four-byte field uses aggregate EclRuntimeFlags storage and direct
bits operations. Empty aggregate initialization naturally reproduces the native
zero-register/addressed-word initialization. The original type name and spelling
remain unknown; no fake operators or matching-only body is introduced. The
accepted full 11,504-byte tick compiler contribution and all seven selection/
reset members have identical COFF bytes and relocations after this refinement,
using each existing actual profile. The default intrusive node constructor gains
its allocation-free noexcept contract; the real Manager constructor has no
spurious cleanup state after main construction.

Manager construction zeros its two state words, current_runtime and loader,
constructs main and the five-pointer sentinel, and installs the actual base
vtable. Independent complete-object locator and type descriptor data identifies
the original global SptInf at table 005703B0. Its six slots are scalar cleanup,
zero-return opcode execution, zero integer read, null integer destination,
zero floating read and null floating destination. Read-only independent table
identity binds original data; original emitted RTTI/source spelling remains open.

terminate_async starts at sentinel.next. For each heap-owned async node it saves
next before destruction, reads that node's runtime, releases the runtime, releases
the node and continues from saved next. It leaves sentinel.next stale. The valid
native surrounding protocol performs clear/reset or retires the owner; repeated
clear on stale storage is outside this domain. No detach, sentinel repair or
extra embedded-main deletion is added. The Manager destructor invokes clear,
then automatic member cleanup destroys main's interpolation vector before its
stack vector. Scalar deleting destructors perform their actual one-bit optional
sized release (72 and 112 bytes on x86).

Typed scalar disposal first accepts null as a no-op. Otherwise it invokes real
std::destroy_at before acquiring mutex slot 1, then calls unsized operator delete
under the lock. This is separate from array release and generic malloc/free.
The native Runtime destroy_at wrapper calls its nonvirtual compiler scalar
destructor with flag zero; current MSVC naturally emits this for the implicit
Runtime destructor. The trivial node destroy_at folds to the complete empty
cdecl body. Neither helper earns duplicate coverage.

## Complete compiler and independent support evidence

The ten units use the existing candidate x86 MSVC 19.44.35211 profile with
C++20, Od, Ob0, GS, Gy, Zl, SSE2, fp:precise, sdl and EHsc. This does not
establish the original whole-game compiler/SDK/profile. The actual native
Manager destructor body ends at 004A3D32; its complete 88-byte COFF contribution
also contains five natural INT3 bytes. No source padding is added and no
comparison truncates these bytes.

The independent Manager EH handler is the complete 29 bytes at 00567600.
The following alignment and unrelated funclet at 00567620 are excluded. Its
complete 36-byte FuncInfo at 005A91B8 has zero unwind states and native flag 5.
Both strictly replay. Physical folds with existing entries also strictly replay:
position construction at 00414030/33, default node construction at 00418A10/63,
zero execution at 00412540/13 and three integer/pointer defaults at 00414B50/15.
These receive no duplicate unit or authored credit.

Complete PMR interpolation-vector construction at 004141C0/63 and destruction
at 0048B850/20, actual default pair/proxy and cleanup child endpoints, and both
destroy_at bodies at 0048B0B0/16 and 0040C6B0/5 are independently checked.
The real full 56-byte-element vector cleanup at 00497B60 corroborates resource
capture, deallocation count and pointer reset. Entire STL linkage remains open.
Existing accepted node accessors, LockRegistry/guard operations, allocator
globals, security cookie, sized/unsized delete and CxxFrameHandler3 provide
independent relocation identities. No canonical field is solved from the parent
bytes under comparison.

## Owned behavioral checks and remaining boundaries

The new O2/UBSan test runs real constructors, virtual defaults, reset, async
clear, typed scalar release and actual PMR destruction. It checks zero and
inactive states separately, allocation-free construction, resource capture across
default-resource changes, three-node saved-next cleanup, original stale sentinel,
clear/reset reuse, interpolation-before-stack release, scalar/virtual disposal
and empty/null cases. A different thread tests the recursive mutex during
owned storage destruction, establishing that destruction precedes slot-1 locking.
Original DiagnosticAllocator construction/process startup remains an explicit
fixture boundary. The existing argument/stack test now runs real production
Runtime/Manager lifetimes and concrete base defaults; lookup and derived game
variable semantics retain explicit fixture boundaries. Other existing whole tick/
call/Enemy checks retain their deliberate bounded dependency fixtures.

The full derived include body at 004A5BE0/516 is reconstructed privately and
retains four constant byte-index lowering differences. Relative section-pointer
use closes its earlier register/local mismatches. The actual setter uses a
checked eight-element array; the getter delegates special slots 0, 1 and 7 to
other production owners. These unclosed dependencies and the whole append876/
getter54, process startup, actual variable/Player/Session owners, Enemy root and
whole-game link/runtime remain pending. New bounded pointer-expression probes
retain their full failure evidence without canonical credit.

## Checkpoint validation and storage

The frozen-source graph cold-builds 98 objects and strictly replays all 534 units
over 94,647 disjoint comparison bytes. The complete canonical lifetime audit
also verifies the independent folded/library and EH support. All 44 public tests,
target, tracking, reference review and progress gates pass. Three complete
reference associations close; all 6,945 reviews remain terminal and 160 are
absorbed-exact. Original reference source/adapters are not claimed exact.

Artifact retirement and the exact-head checkpoint are recorded in RE_HANDOFF.md.
Current canonical objects/receipts, native exports, failed source/diagnostics,
reference and installed tools are protected. Strict existing-object replay
checks cleanup without repeating an unchanged cold graph.
