# Function-chain allocation, release and source ownership

CORE/EXACT-130 accepts four complete physical functions from the existing
FunctionChain, DiagnosticAllocator and SDK bodies:

| Native entry | Maintained role | Bytes | Origin |
| --- | --- | ---: | --- |
| `00411910` | DiagnosticAllocator::allocate_object<Node> | 67 | Authored |
| `004118A0` | DiagnosticAllocator::release_object<Node> | 97 | Authored |
| `00411960` | std::destroy_at<Node> | 16 | Library |
| `00411CB0` | Node scalar deleting destructor | 46 | Compiler |

They add 226 disjoint comparison bytes. Release, destroy_at and the deleting
destructor were previously support-only; allocation was whole nonexact. Each
new unit retains its complete return and contribution. The compiler's separate
31-byte initialization helper folds to the already represented `0040C080`
primitive, with no duplicate physical credit.

## Class declaration and automatic initialization

The native allocator calls ordinary scalar new for 44 bytes, tests its result,
calls the dynamic-span initialization helper with size 44, then invokes the
actual Node constructor at `00411A70`. Native creation at `004127B0` supplies the
process allocator and the full core/func.cpp:317 funcChainInf diagnostic.

With the unchanged user-provided constructor and shared `new T` body, the pinned
C++20 /sdl compiler emits all 67 native bytes when FunctionChainNode is declared
as a class with every member public. The previous struct form emits 57 bytes.
This independently corroborates the earlier iterator declaration observation in
[CORE099](CORE_ITERATION_EXACT_RECONSTRUCTION.md). Both the forward declaration
and definition now use class. The Node remains 44 bytes on x86, with unchanged
public access, member widths/order, ordinary destructor, noexcept constructor
and scalar allocation family.

No allocation-body change, explicit clear, new temporary or alternate constructor
is maintained. C++17, brace/value initialization, defaulted constructors,
in-class initializers and constructor-visibility probes do not explain the
complete allocator. The defaulted-constructor/value-init alternative emits
73 bytes with a direct memset and is rejected. The original 138-byte constructor
and its five emitted CC alignment bytes remain exact under the class declaration.

Microsoft documents member-pointer initialization before construction under
[/sdl](https://learn.microsoft.com/en-us/cpp/build/reference/sdl-enable-additional-security-checks?view=msvc-170).
The particular class/struct distinction here is an observed result of the
locked compiler experiments. Original source spelling and a whole-game compiler
profile remain inferences; this batch records one shared canonical declaration.

## Actual destruction and storage release

The 97-byte release method returns immediately for null. Otherwise it calls
destroy_at before acquiring recursive game lock slot one, deletes scalar
storage under the guard, then unlocks. Its constructor/destructor/lock/runtime
references reuse independently established bodies and globals. Destruction
outside the lock is preserved.

Pinned SDK xmemory defines non-array destroy_at through the object's ordinary
destructor expression. MSVC emits the complete 16-byte wrapper calling the scalar
deleting destructor with flags zero. That 46-byte compiler wrapper invokes the
actual 41-byte ordinary Node destructor and conditionally applies sized scalar
delete for 44 bytes. Native auto-analysis's ExceptionPtrDestroy label at
`00411960` does not describe this independently reviewed Node chain. No manual
deleting wrapper or virtual destructor is introduced.

The full compiler initializer alias replays 31 bytes using the independently
anchored memset entry. New roots use complete ordinary-new, destructor,
destroy_at, deleting, lock, delete and cookie identities. No compared instruction
field is solved to choose a destination. Typed Node COFF class tags are migrated
consistently in all affected providers and consumers; their native addresses
and calling conventions are unchanged.

## Independent application-origin audit

Seventeen new origin decisions identify fifteen application functions, one SDK
function and one compiler function. Twelve already-exact application roots add
2,616 bytes to reviewed authored coverage without adding physical coverage again:
the Node constructor, controller constructor/create/locked remove, four distinct
registrations, both sorted insertions and whole update/draw dispatchers.
The two new allocator/release roots add 164 authored bytes.

The original core/func.cpp diagnostic, actual callback/link Node, 56-byte game
controller, process registration consumers, observer repair, game locks and
custom action tables establish application ownership independently of matching.
Update's nine destinations and draw's six destinations, original NOP alignment
and full 648/612-byte compiler contributions remain intact. The two internal
jumps omitted by older Ghidra function exports are retained in complete PE
control flow and strict comparison.

Unlocked removal at `00412400` is also classified as authored from that actual
two-list scheduler protocol. It stays whole nonexact at 156 source/native162
bytes: the final native by-value parameter reset remains unexplained. No dead
reset is added merely for emission, and the function receives no exact unit or
partial byte credit. One reference association covering the complete creator
and allocator is now absorbed; its free helper partition is not imported.

## Frozen verification and remaining scope

Original immutable pairs for all 162 objects are verified before editing.
Compiler include traces identify 43 actual Node-header consumers. Each builds
once, and all 225 prior affected units strictly replay. The new allocator needs
one additional production object. The other 119 objects retain their immutable
receipts. Twenty-seven complete literal payloads and fresh reference roles
reconcile renamed generated labels without using target instruction fields.
Eleven typed root symbols change class tags; all relevant references follow the
same canonical Node declaration.

The graph contains 851 physical strict units, 163 objects, 164,164 disjoint
comparison bytes and 860 source-present mappings. Authored exact coverage is
separately 122 functions / 36,169 bytes, with 125 confirmed authored origins.
Nine mapped whole functions remain nonexact. This reviewed subset does not
measure the whole-game 95% byte-exact objective.

Existing actual-owner O2/UBSan fixtures exercise registration order, every
dispatch action, retry/restart/shutdown, observers, current-link repair,
pending-node removal and real owned destruction. Cross-thread probes check
lock release around normal callbacks and retention around shutdown. Process
placement, allocator/global startup, arbitrary concurrent mutation, allocation
failure/exception domains and playable native game execution remain open.

All 80 public tests pass in 281.599 seconds. Protected retirement removes 108
obsolete object/receipt products totaling 3,564,421 bytes after preserving their
authentic original input versions and immutable receipts. All 326 current
canonical object/receipt hashes remain unchanged. Post-cleanup strict replay
passes all 851 complete units using existing objects, with zero compiler
invocations. Rejected probe sources, copied input headers and complete emission
observations remain retained privately.

Private proof is retained in core130-pre-header-inputs.json.gz,
core130-cold-proof.json, core130-affected-results.json.gz,
core130-new-exact-results.json, core130-folded-initializer.json,
core130-boundaries.json, rejected probe sources and attested native exports
under `.analysis/`. Completed proof/retirement writers must never rerun.
