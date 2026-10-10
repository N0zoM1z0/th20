# Shared locks, callback nodes and random stream state

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

EXACT-052 adds nine complete native operations: 693 body bytes and five compiler
alignment bytes. The current graph has 372 units, 67 canonical objects and 58,232
disjoint complete comparison bytes. Original authored attribution stays at 57
functions / 4,074 bytes; the new operations retain pending origins. This batch
closes dependencies discovered while reviewing the FunctionChain insertion and
dispatch bodies, then follows the same real mutex protocol into GameRandom.

## Established owners and state

FunctionChainNode remains 44 bytes on x86. Its priority, four-byte flags word,
three cdecl `int32(void*)` callbacks, 20-byte typed link and userdata preserve all
previous offsets and field operations. Native construction at 411A70 initializes
the flags as an aggregate word, links the actual node receiver and clears every
callback and userdata. A plain scalar initializer has different emission; the
four-byte `FunctionChainFlags` aggregate reproduces the complete constructor.
Original source spelling of this aggregate remains an inference.

The constructor uses the same independently decoded handler 5679A0 and complete
36-byte FuncInfo at 5A91B8 as the previously accepted Region constructor. Its
nonthrowing contract and full 138-byte instruction body agree with that metadata.
The entire compiler contribution includes five trailing native INT3 bytes,
so `compare_size` is 143. Padding receives no body or authored credit.
The complete callback/userdata accessors return their actual pointer fields at
10/28 (hexadecimal), with no callback invocation or allocation.

LockRegistry has 22 real `std::recursive_mutex` elements (48 bytes each on locked
x86), 22 depth bytes at 420..435, enabled byte 436 and total size 438. Constructor
452E00 default-constructs the mutex array, zero-initializes the depth array and
disables tracked locking. Value-initializing the mutex array adds an absent clear
before its constructor; that hypothesis is rejected. The actual array constructor
452D80, element constructor 452EE0 and consumers corroborate the storage.

Slot selection is unchecked array indexing. Tracked enter locks first, then
increments the selected depth byte. Leave decrements the byte first, then
unlocks. Both operations do nothing while disabled, and depth arithmetic wraps
modulo 256. Valid indices are 0..21; paired calls require a stable enabled state
and the owning thread. Native out-of-domain indexing and unmatched operations
are not replaced with bounds checks or new errors.

The process-wide object at 5C0240 has a typed extern declaration, supported by
the full owner layout and native consumers. Its definition and startup/shutdown
order remain pending. Portable fixtures provide their own fully owned instance;
they do not establish the original global lifecycle.

## GameRandom state and compiler evidence

The existing 28-byte stream and its actual four-byte MSVC minstd engine retain
their layouts. Both seed and next unconditionally use `std::lock_guard` on shared
mutex slot 10, independently of the tracked enabled flag. These are ordinary
mutex operations, distinct from tracked enter/leave.

Seed resets minimum to zero, derives upper from the full unsigned maximum shifted
right once, sets modulus to upper minus minimum, stores the original input in
last, and seeds the actual engine subobject. Native normalization maps a zero
residue to one. The raw input remains in last until sampling; id and field_00
survive. The eight-byte all-ones helper has both numeric-limits and EOF-compatible
views; a compatible physical head does not prove its original source name.

Next advances the actual engine, writes its raw result into last, computes the
unsigned remainder using modulus, and releases the mutex before returning that
remainder. Last is not overwritten by reduction. The nonzero-modulus domain is
preserved; no exception or fallback replaces native DIV failure at zero.

With GS alone, natural bodies are 79/119 bytes against native 99/139. Enabling
`/sdl` produces the complete native bodies and stack-cookie placement without a
source-body change. Microsoft's [SDL documentation](https://learn.microsoft.com/en-us/cpp/build/reference/sdl-enable-additional-security-checks?view=msvc-170)
describes stricter GS checking and pre-constructor pointer initialization. Here
the locked compiler experiment corroborates the strict-GS explanation. This
local recipe does not establish executable-wide SDL flags or compiler identity.

GameRandomStream.cpp owns seed/next under precise-FP/GS/EHsc/Gd/SDL; the existing
constructor and scalar wrapper translation unit retains its previous recipe.
FunctionChain and LockRegistry each use one precise-FP/GS/EHsc/Gd recipe for all
their current units. Thirteen previous contributions remain exact after replay.
There are no profile-selected semantic bodies or substitute lock interfaces.

## Accepted complete operations

| Address | Body bytes | Operation |
| --- | ---: | --- |
| 00411A70 | 138 | Nonthrowing callback-node construction |
| 00411700 | 17 | Shutdown callback pointer access |
| 00412710 | 17 | Node userdata pointer access |
| 00452E00 | 61 | Real mutex-array/depth/enable construction |
| 0040C310 | 33 | Shared mutex slot selection |
| 00412550 | 94 | Tracked enter |
| 00412750 | 95 | Tracked leave |
| 00423EE0 | 99 | Locked random sampling and raw-last update |
| 004D9940 | 139 | Locked seed and range reset |

Native and locked-header evidence independently establish supporting guard,
mutex, array, numeric-limit and standard-engine calls. Complete supporting
contributions match structurally, including the 80-byte array contribution with
its five alignment bytes. They receive anchors, not extra coverage or authored
credit. Existing shared _Mymtx/position-reference head 40BDA0 remains counted once.

## Complete controller review and deferred emission

Both sorted insertion bodies 411F80/412100 (381 bytes each), update 412810 (611
bytes) and draw 412AA0 (587 bytes) are fully reviewed. The real enclosing state
is 56 bytes: current link at 0, two 24-byte lists at 4/1C and shutdown word at 34.
This is observed storage, not a maintained complete controller facade.

Before-insert callbacks run before acquiring slot 0 and clear after returning.
Insertion sets priority and inserts before the first node with priority greater
than or equal to the requested value, otherwise appending. Equal priorities thus
put the newly inserted node first. The retained reference's merged Environment/
bool wrapper does not preserve the original two-member ABI or lifecycle.

Update/draw release tracked slot 0 around enabled callbacks and reacquire it
before interpreting the result. Counts include non-null callbacks even when
disabled, while null callbacks skip the increment. The independently decoded
nine-entry update table maps actions 0..8 to remove, continue, retry the current
node's enabled test, return one, return zero, return minus one, restart, shutdown
callback and return zero. Shutdown mode also selects that shutdown callback path.
The six-entry draw table maps 0..5 to remove, continue, retry, return one, return
zero and return minus one. Draw subsequently clears remaining link observers.
Iterator destruction, restart/early exits and the update's otherwise unreferenced
jump at 412960 are retained evidence, not shortened comparison extents.

All four controller bodies clear an eight-byte stack object through 40C080 before
calling list begin. That helper calls memset; it is not an allocator. It has 255
native callers spanning globals, stack values and allocated objects. The pattern
is compatible with compiler initialization, but its exact source/flag policy is
not recovered. The natural insertion probe remains 371 versus native 381.
SDL, language-mode and constructor-visibility probes do not close that gap.
A separate minimal experiment can emit compiler __autoclassinit2 for a genuinely
uninitialized default constructor; that does not justify adding such a constructor
to the maintained iterator solely to shape callers. No controller gets exact
credit. List construction/reset, removal's allocator lifecycle, full controller
startup/shutdown and cross-module ownership remain open.

## Verification and limits

The entire source/probe graph freezes before a 372-unit / 67-object cold replay.
Complete canonical relocations and disjoint extents are checked over 58,232 bytes.
The new C++20/UBSan fixture covers disabled gates, every valid mutex slot,
256-level recursion and byte wrapping, ownership across threads, independent
slots, six seed normalization boundaries, 1,800 independent LCG recurrence steps,
raw-last preservation after reduction, and unconditional slot-10 locking/release.
Previous callback-node/TaskInfo tests retain all flag combinations and now check
constructor defaults and the pointer accessors. Wrapper conversion tests keep
their explicit dependency fixture; the actual sampler is tested separately.

All 23 public tests and CI pass. The original executable and full attested Ghidra
text are unchanged, as are the 6,945 reference bodies / 113 parser-gap reviews.
These results establish component state, ABI and byte identity. They do not
establish original class names/origins, fault execution, global/thread startup,
allocator cleanup, whole-program linkage or playable runtime.
