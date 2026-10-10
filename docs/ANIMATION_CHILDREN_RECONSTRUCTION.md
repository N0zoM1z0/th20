# Animation child traversal and recursive flags

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-118 recovers one coherent child traversal protocol: four complete
recursive flag operations, genuine indexed child-link access and node iteration.
The whole six-root comparison covers 1,351 bytes. The frozen 269-source
production graph passes 787 strict units across 154 fresh objects / 149,070
disjoint bytes. Production O2/ASan/UBSan passes 1,025 cases.
No authored-origin credit is inferred from these matches. The six roots replay
72 independent relocations; twelve complete shared supports compare 653 bytes
without adding duplicate physical coverage.

| Operation | Native address | Complete bytes |
| --- | --- | ---: |
| Clear bit zero of Animation +49C | 0x450160 | 272 |
| Set bit zero of Animation +49C | 0x44FA70 | 272 |
| Clear bit zero of Animation +4B4 | 0x44F170 | 272 |
| Set bit zero of Animation +4B4 | 0x44F2C0 | 272 |
| Indexed 20-byte child node | 0x4494B0 | 20 |
| Begin iteration on an actual node | 0x44B9F0 | 243 |

## Storage and independent consumers

All eleven reviewed callers of 4494B0 use indices zero or one at Animation+514.
The allocator at 44C9B0 initializes both indexed slots independently, and child
binding at 451050 inserts a new Animation's index-zero node after its parent's
index-one sentinel. The recursive publication consumer at 44F840 separately
initializes and appends the direct +53C node to its supplied actual list; it also
clears parent state and detaches indexed node zero. These producers and consumers
corroborate different sibling, child-sentinel and publication roles.

`AnimationChildLinks` maintains the two independently consumed nodes as a real
array. It replaces two previously independent fields without pointer arithmetic
across separate C++ members. The separate +53C node remains an actual member.
The complete Animation owner remains 0x5E4 on x86, with child storage +514/528
and publication +53C. Natural aggregate initialization retains all five native
node constructors in order; the complete existing 503-byte Animation constructor
is independently preserved. Original container spelling, index signedness beyond
observed zero/one, and original type declaration are inferred. The earlier private
three-slot hypothesis based solely on adjacency is superseded; index two is not
observed and adjacency alone does not establish original container cardinality.

## Whole traversal and exception behavior

Each operation changes only its selected word's low bit on the receiver. It
checks the child sentinel's next pointer and reads it again to obtain the first
actual child. An eight-byte intrusive iterator walks this sibling chain and
recursively invokes the same operation on each node's Animation pointer. It
starts with the first child, rather than revisiting the self-valued sentinel.
The complete loop, return and exception cleanup are compared.

Node `begin()` is distinct from the existing 24-byte list's sentinel begin.
A null-valued node yields an empty iterator even when its next pointer is nonnull.
Otherwise it returns an iterator starting at that node. End remains a null
iterator pointer. Native shared getters, iterator construction/destruction,
advance, comparison, dereference, value reference and compiler initialization
helper are replayed as twelve full support contributions. Existing physical
aliases add no duplicate coverage.

The first natural positive-condition ternary emits 181 bytes for node begin.
The equivalent null-first conditional emits the complete native 243 bytes,
including both conditional temporary lifetimes and EH cleanup flags. Its later
potentially throwing getter occurs after the compiler has established the first
conditional temporary state. Existing independently established noexcept iterator
construction/destruction contracts are preserved. No fake ABI, manual clearing,
inert locals, profile-dependent source, padding or shortened extent is introduced.

Complete 52-byte recursive EH sections uniquely identify code at 568630 and
44-byte unwind-map/FuncInfo data at 5A9CCC. Node begin's complete 59-byte section
independently identifies 5685B0 and its 44-byte data at 5A9CA0. Neither identity is
discovered through the handler field of a compared root. Constructor/destructor
noexcept handlers reuse independently audited physical generic iterator aliases
5674F0/567750 and complete 36-byte FuncInfo 5A91B8. All code and data relocation
fields are strictly replayed.

Ordinary iterator return/copy elision remains compiler dependent: MSVC's observed
conditional temporaries clear their node observer hooks before the returned copy
is used, whereas a portable compiler may elide the copy and retain hooks until
iterator destruction. The four accepted traversals do not detach or mutate
nodes during traversal. Runtime equivalence for mutation during this particular
node-begin traversal is not claimed. Existing direct iterator construction and
observer repair retain their established separate semantics.

## Maintained semantic scope and remaining work

Private same-body C++20/O2/ASan/UBSan passes 1,025 cases: 256 seeds across four
operations using 33 genuine Animation objects each, with deep chains, wide
siblings, balanced trees, selected subtrees and an unrelated root. Expected
membership is derived independently from parent indices. The fixture compares
all flag bytes, retained parent pointers, actual node/value/owner/observer state
and detaches every sibling before owner destruction. A null-valued node with a
nonnull successor exercises empty begin. Actual Animation/member construction,
resource retirement, allocator, locks and value implementations execute; original
callback destruction remains an explicit fixture and is not an original runtime
claim. Production and public versions use the same source bodies.

The complete Renderer consumers at 44C9B0 (298 bytes), 44F840 (411 bytes),
44FB80 (282 bytes) and 451050 (604 bytes) remain reviewed interfaces rather than
new source bodies. Their original large owner storage, resource/handle publication
and retirement protocol are still open. The recursive identifier lookup at
44C6B0 (241 bytes) additionally consumes signed +440 identity and positional
recursion; its full source and signedness corroboration remain next work. Full
922-byte VM creation, Item update/draw, renderer storage, RTTI/EH/full linkage,
startup and whole-game gameplay execution remain separate acceptance gates.

Original receipts and actual source/header/compiler inputs are archived before
shared-owner migration. Superseded private trials are retired during the batch;
current canonical objects, native Ghidra exports, failed experiments and original
SHA-bound closures remain protected. No unchanged-source rebuild is used solely
for cleanup or documentation.

All74 public tests pass in239.429 seconds; complete gate passes in240.992
seconds. The first complete run retains one explicit test-linkage failure: the
existing Animation runner omitted AnimationChildren.cpp after its fixture began
using the real indexed interface. The focused corrected regression and second
complete public run pass. No production source, profile or canonical bytes change
for that correction; no completed production object is rebuilt.

Protected final retirement removes436 files/8815691B:153 previous
canonical pairs, the migrated child-protocol pair and128 copied private host
dependency files. Original actual input/receipt/SDK closures are SHA-verified before
deletion. Combined with mid-batch retirement, 440 files/8924135B retire.
All787 completed exact results,269 source hashes,308 current canonical hashes
and9 native evidence hashes remain unchanged. Build9.8MiB/analysis140MiB.
Forty-five complete typed literal roles reconcile30 label renames; all154 affected
production objects compile once. Keep cleanup/path-hash plans and original
compressed input closures. No original target/reference/tools/database or active
canonical input is retired.


A final bytecode-cache pass retires4 regenerable files/37271B, yielding
444 files/8961406B (8.55 MiB) for the complete batch.
Current source,308 canonical hashes and9 native evidence hashes remain unchanged.
No compiler input is retired and no unchanged-source build is repeated.
