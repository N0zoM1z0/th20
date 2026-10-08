# Bullet ownership, construction and resource release

EXACT-078 closes eleven complete contributions on the actual BulletInf owner
and its 2001-entry Bullet pool. They add 1,471 body /1,491 comparison bytes.
The frozen graph contains 591 units in 108 objects over 102,474 disjoint
comparison bytes. Origins remain separate: 518 pending /9 library /64 authored
and 16,948 authored bytes. Five complete reference associations close, bringing
the absorbed total to 194 across all 6,945 terminal reviews.

| Complete contribution | Address | Body / comparison bytes |
| --- | --- | --- |
| Bullet construction | 0047BE00 | 556 /556 |
| Bullet destruction | 0047C470 | 26 /26 |
| Fourteen ExtendedCommands construction | 0047B740 | 75 /80 |
| 2001-entry Bullet pool construction | 0047B790 | 44 /44 |
| 2001-entry handle array construction | 0047B7C0 | 78 /83 |
| Bullet Controller construction | 0047B8A0 | 386 /391 |
| Bullet pool destruction | 0047C2A0 | 78 /83 |
| Controller disable and metadata release | 00484260 | 131 /131 |
| Controller count query | 004992F0 | 17 /17 |
| Controller context binding | 00486530 | 54 /54 |
| Process Bullet Controller lookup | 00478E80 | 26 /26 |

## Native ownership and layout

Allocator 47B5F0 requests 0x286DA8 /2,649,512 bytes, performs the independently
observed preclear and calls constructor 47B8A0. The constructor stores vtable
56FC5C; its complete-object locator identifies original global class BulletInf.
The three native slots are 47C790, 4216A0 and 484260. The original literal at
56FC68 is `initialize BulletInf\n`. These establish constructor identity and
virtual protocol; the maintained neutral class spelling does not claim that
all emitted RTTI data is byte-identical.

Initialization 480FA0 obtains the actual indexed Session Context through
40BBC0, then publishes this owner through setter 4117A0 into Context slot0.
Getter 40C300 and process lookup 478E80 therefore reach actual BulletInf.
Context now declares a borrowed BulletController pointer and real value getter
and setter. Their complete 16/21-byte emissions match existing folded scalar
heads; no additional coverage is claimed. This independently resolves the
previous Game and intermediate EnemyController misattributions of 4992F0.
Actual process EnemyController lookup remains 478060 through slot8/412730.

Controller +14/+2C are separate six-element arrays of Bullet draw-chain heads
and tails. Native update 47D600 clears all six slots of each and indexes them
using Bullet +44; draw 47DC90 follows the resulting chains. Controller +44 is
the count reset and incremented by update. The count query returns the complete
32-bit word; it is not a Game frame query. Construction initializes each first
array entry explicitly to null and value-initializes its five remaining entries.
This explains native scalar stores followed by two twenty-byte zeroing groups
without splitting real arrays or importing the reference's flattened integers.

Each Bullet is 0x528 /1,320 bytes. Actual members include a self-referencing
IntrusiveLink, a distinct flag aggregate, animation pointers/handles, a borrowed BulletStyle pointer at58, vectors,
an Angle at84, a distinct packed color value at88, an aligned 64-bit command
flag aggregate at90, genuine
shared_ptr<ShotMetadata> ownership at98, fourteen ExtendedCommands atA0,
Vector/Float interpolation and seven Timers. Native 480C0E/480C1F independently
read/write high-word bit1, establishing bit33 of the command flag storage;
native 485B60 consumes low-word command flags. It is not floating storage.
The pool starts at Controller +60; native constructors establish count2001 and
stride528. Handle storage starts at284E08; native construction establishes
count2001 and stride4. Real free/active intrusive lists start at286D4C/286D64.
Context is at286DA0; native alignment supplies all gaps and the tail to286DA8.
Native482370..48237F computes style BSS base5C06A8 plus index*158 and stores
its borrowed pointer at58; the reference integer slot is replaced with the actual
BulletStyle pointer. Native482382 passes color0xFFD08080 to the +88 assignment operation; cancellation
47C8F0 transfers this value to the actual EffectParameters color at20. A neutral
BulletColor value preserves this separate role and the original zero-construction
ABI. Its complete23-byte construction folds with the independently observed
AnimationHandle head; that folding does not establish identifier semantics. The
original tag relationship to the argument-taking EffectParameters PackedColor
value remains unknown; the observed no-argument construction ABI is preserved. The
initial handle interpretation was rejected after these producer/consumer checks,
despite passing byte comparison. Its source and initial proof are retained as
historical evidence; acceptance uses the fresh corrected whole-graph proof.
No explicit padding, byte facade or source-only Services suffix is maintained.
Original wrapper/template spellings and several gameplay field roles remain
unknown; neutral types describe actual counted storage and observed contracts.

## Source and compiler responsibility

`src/Bullet.hpp` is the shared declaration. `src/Bullet.cpp` owns the complete
Bullet constructor and defaulted destructor; `src/BulletController.cpp` owns
the array protocols, Controller construction, disable, count and Context binding
and lookup. `src/Context.hpp/.cpp` owns the actual borrowed pointer protocol.
Typed dependencies reuse maintained Task/Angle/handle/Timer/vector/interpolation,
IntrusiveLink and ShotMetadata values; no alternate exact-only body exists.

Both translation units use pinned MSVC x86 19.44.35211, C++20 and
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl`. The array/Controller unit
also uses `/EHsc`; the Bullet unit retains the independently observed profile
without that option. Using one profile for both leaves complete emission
differences: the initial no-EH array/Controller probe misses native EH/array
cleanup; the EH-enabled Bullet constructor grows from556 to612 bytes. These
failed probes remain private evidence. This partition follows actual source
and array/resource responsibilities, not profile-specific body branches.

Command/handle construction, Controller construction and pool destruction
retain their full 29-byte EH handlers and 36-byte flags5 exception records.
Pool construction uses the real exception-aware array constructor iterator,
with both Bullet construction and destruction callbacks. Pool destruction uses
the real reverse array destructor iterator. Default Bullet destruction owns
the shared metadata destructor. Native shared-pointer construction/base,
destruction/decrement/reset/swap wrappers and typed pool begin/end emissions
receive complete strict support comparisons, including all relocations. The
runtime library, folded scalar and iterator heads receive no duplicate credit.

## Semantic checks and limits

`tests/bullet_storage_semantics.cpp` uses actual production construction,
dirty guarded heap storage and every one of the 2001 typed records. It checks
self-links, scalar/vector/Angle/interpolation/Timer/command/handle defaults,
natural gap preservation, pool endpoints and both real sentinel lists. Actual
Session/Context objects independently publish, look up and bind the borrowed
owner; whole snapshots verify the binding mutation boundary. Count checks
include signed extremes and verify complete-state preservation.

Disable uses actual FunctionChainNode operations and releases metadata across
the entire pool, including the last slot. Shared and independent real
ShotMetadata allocations/weak references verify ownership and final release;
snapshots check every byte outside metadata storage remains unchanged. Nullable
callbacks, repeated disable and actual pool destruction after reacquiring a
resource are covered at O2 with UBSan. The pool lives on the heap to keep stack
and memory use controlled.

Whole Controller destruction and virtual enable are explicitly declared but
remain undefined in maintained production source. Portable tests provide named
fixtures for those operations; member destruction still runs the actual pool
and Bullet bodies. These fixtures do not accept native Context retirement,
callback unlinking, ANM/file unload or full controller teardown. Factory,
initialize, update/draw, renderer ownership, whole Enemy readers and the 41 KB
opcode root remain open. No playable whole-game or native EH execution claim
follows from the portable tests.

Five reference constructor/destructor/binding/value-lookup associations close
with independently recovered native partitions. The reference Session
`primary_owner` accessor returns a pointer reference (the slot's address),
whereas native 478E80/40C300 return its stored pointer value. That reference
entry remains nonexact; typed owner closure does not justify an ABI substitution.
Original reference files and their changed ownership/flattened layouts are not
imported or asserted byte-identical.

Private evidence includes `core078-pool-native.asm`,
`core078-typed-consumers.asm`, `core078-flag-high-bit.asm`,
`core078-virtuals-shared.asm`, `core078-resource-support.asm`,
`core078-library-base.asm`, repeatable `core078-audit.py`, all preserved probe
sources/results, and compressed `exact078-final-canonical-results.json.gz`. The first
`exact078-canonical-results.json.gz` belongs to the superseded pre-color declaration
and is preserved only as historical byte evidence.

All49 public tests pass in145.482 seconds. Target/tracking/reference/progress
gates pass. Protected retirement removes six completed probe products,160000
bytes; original receipts survive byte-for-byte recovery from a45320-byte compressed
archive. Net savings are114680 bytes. All216 canonical hashes and native/failed
evidence are unchanged; post-cleanup591/591 strict replay uses existing objects
without rebuilding. The one-time configuration/registration/cleanup writers are
completed and must not be rerun. Source remains frozen.
