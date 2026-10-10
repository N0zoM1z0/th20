# Animation callback owners and calling conventions

CORE/EXACT-123 reconstructs the callback protocol used by the whole ANM VM.
Native evidence establishes the complete eight-byte callback base, its five
virtual slots, the two C callback signatures and the actual Bullet owner used
by one script callback. The 40,752-byte VM remains a whole, open reconstruction
objective. This batch does not claim a partial match for that function.

## Complete owners and native contracts

Native RTTI names the base `SprtFuncBaseInf` and a directly derived 72-byte
`EffectMenuWindowInf`. The base has a vptr followed by `Animation*` at +4.
Constructor446B60, destructor446BA0, deleting destructor446BC0, the
five-entry vtable56E1AC and native RTTI independently corroborate the eight-byte
owner. The derived hierarchy has exactly two base descriptors: itself and this
base. The reference hypothesis with a four-byte abstract base and a separate
eight-byte attached class does not explain that hierarchy.

Maintained source uses `th20::AnimationCallback` as its semantic name. Its
native layout and emitted slot table are verified; its different RTTI name is
explicitly outside exact admission. The derived owner, its drawing operation
and its natural constructor's exception contract remain unimplemented.

| Native virtual slot | Maintained operation | Native contract |
| --- | --- | --- |
| +00 | Virtual destruction | Deleting flags; scalar delete uses sizeof8 |
| +04 | `update()` | Signed32 result; nonzero makes the VM retire the animation |
| +08 | `draw()` | Signed32 result; base returns zero |
| +0C | `slot_0c()` | Base returns signed32 zero; concrete role unresolved |
| +10 | `interrupt(event)` | Signed32 argument and result; callee pops4 |

The three no-argument defaults fold to412540, already represented by a whole
canonical iterator unit. The one-argument default folds to414B50, already
represented by a whole canonical loader unit. Their complete13/15-byte
emissions are independently replayed, without duplicate physical byte credit.

`Animation::set_callback` returns the incoming pointer after publishing +568.
`Animation::interrupt` first calls the virtual interrupt slot, discards its
result, then publishes the event at AnimationBase+438. A null callback still
publishes the event. Tests cover callbacks which change this field during the
call, so the observed ordering is checked rather than assumed.

## C callbacks and signed script selection

The VM has one call through +5DC and three through +5E0. Together with the
native setters and their producers, they establish these x86 default `__cdecl`
contracts:

```cpp
std::int32_t (*entry)(Animation*);
std::int32_t (*script)(Animation*, std::int32_t);
```

The caller removes4/8 argument bytes. The unary callback runs at VM entry and its result participates in retirement;
script results are signed script selections. Maintained +5DC/+5E0 storage and
setters now use these function pointer types. Zero reset remains null assignment.
The current typedef name `AnimationHitCallback` is provisional: native evidence
establishes a VM-entry hook, without establishing a collision event. A neutral
name is scheduled with the next necessary header migration, to avoid a separate
unchanged-code rebuild of the complete graph for this naming correction.
No portable fixture fabricates an integer token as a callable pointer.

Native producer48227D/47F315 publishes47D580, whose complete121-byte callback
reads the genuine528-byte `Bullet` through `Animation::user_data`. Signed16
type/color getters at485640/485720 sign-extend to32 bits. The callback checks
the signed view of `bullet_styles[type].colors[0].words[0]`. A negative sentinel
returns the incoming script unchanged, without reading color or indexing a
word. Otherwise it returns the selected unsigned word's signed32 bit pattern.
The existing158-byte style and20-byte color records retain their original
unsigned storage declaration; one signed consumer does not rewrite the owner.
Native base5C06AC is colors+4 within the independently anchored array5C06A8.

The nonnegative path retains the native unchecked domains type0..49,
color0..15 and script0..4. The negative path permits any signed32 script and
does not require a valid color index. Ghidra omitted an internal two-byte JMP
at47D5F0; complete PE control-flow review and the compiler comparison retain it.

Other producers publish4CF550/4CF5C0 with a different user-data owner, or
single-argument lambda adapters4AC290/531050. Their complete native contracts
and bodies are recorded privately. Those concrete owners and lambda emission
remain open; they receive no source or exact credit in this batch.

## Real virtual retirement

Animation resource cleanup now uses the existing shared
`DiagnosticAllocator::release_object<T>` body for the complete callback type.
It returns immediately for null, runs `std::destroy_at` before taking lock1,
then performs scalar storage release under that lock. The full97-byte callback
instantiation folds to the already canonical Bomb instantiation41F7C0. The
complete27-byte virtual destroy helper41F880 is newly represented physically.
The constructor, resource and lock startup boundaries remain explicit fixtures.
Existing independently anchored CRT/STL callees are not newly reconstructed.

Tests exercise actual virtual destruction rather than an opaque callback token.
At destruction they observe cleared geometry, the still-published callback,
the original handle and instruction offset. A second thread can acquire lock1
during destruction, corroborating destruction outside the storage-release lock.
After cleanup, callback/handle are null/zero and the instruction offset is -1.

## Compiler, exact and semantic gates

The private batch passes nine new whole physical roots414B and five folded
aliases151B. An independent full20-byte vtable replay corroborates the slot
contract but is not an admitted data unit. Its COFF weak vector-deleting spelling
falls back to the independently verified46-byte scalar deleting body. Complete
native RTTI parsing establishes the original hierarchy; it is not inferred from
the constructor relocation under comparison.

The natural typed setters and shared virtual-release migration independently
preserve all18 affected whole Animation/Binding units3360B. Maintained semantic
fixtures pass149903 cases under O2, ASan, UBSan and float-cast-overflow checks:
all65536 signed16 getter representations, every valid type/color/word selection,
signed result bits, negative-sentinel bypass, full-width events, virtual dispatch,
field publication order, null handling and real resource retirement.

Production root/support replay passes the frozen276-source graph,827 complete
strict units,160 fresh objects and160921 disjoint comparison bytes. Maintained
production149903-case semantics and all79 public tests pass. Authorship, original global initialization,
gameplay execution and native RTTI identity are separate acceptance boundaries.

Original159 canonical and three private compiler closures, the first trial and
the failed host fixture are archived before migration or retirement. Replaced
builds and host copies retire only after replacement proofs, unchanged protected
hashes and complete exact replay. Current canonical products, original input
archives and native evidence stay protected; cleanup does not rebuild an
unchanged source graph. Work remains serial at reduced priority with bounded
Ghidra resources, as requested.

All79 public tests pass in 385.866s; the complete public gate passes in
387.968s. The first public attempt retains its original
fixture/link inputs after missing genuine callback RTTI is observed. The second
retains all79 original test inputs after three legacy mock-call counters fail.
Fifteen existing fixtures now link the real callback implementation/RTTI; Item
fixtures observe actual virtual destruction, including3072 owned callbacks in
each whole pool test. Null callback release is not counted as destruction.
No production source change or cold rebuild follows those fixture corrections.

Each of160 objects compiles once. All45 complete independent literal roles
reconcile45 fresh label names; no compared target relocation field is solved.
Protected retirement removes475 final files /
9495944 bytes; including the archived first trial, the batch
retires591 files /
9739861 bytes
(9.29 MiB). All827 exact results,
276 frozen source hashes,320 current products,81
native evidence hashes and original compiler/failed-fixture archives remain
unchanged. Original159 canonical/three private closures are verified before
retirement; no unchanged-source build runs for cleanup.

The +5DC callback is observed at VM entry. Its current AnimationHitCallback
typedef label is provisional and does not establish a collision trigger; rename
it together with the next necessary shared-header batch. Full40752B VM,
Renderer+6000DFC, concrete callback owners/lambdas and native packet/buffer
lifetime remain open. Prior CORE122 matching-head remote CI succeeds at3c03d2b,
run38013441492. The reconstruction goal remains active.

