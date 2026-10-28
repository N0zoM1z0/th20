# CORE201: real exact queued selectors in the complete Enemy opcode boss

CORE201 integrates the **actual maintained native-byte-exact**
`EnemyState::writable_shot` and `EnemyState::shared_shot` methods into the
**same entire 41,967-byte** `EnemyState::execute_opcode` source-draft host
at original `0x0048C010`. This is not a stand-alone partial opcode or a
separate replacement dispatcher, and the 41,967-byte original native boss
remains **machine-code nonexact**.

## Native accepted dependencies and real production call path

The two complete genuine COW/ensure-only selection methods accepted under
CORE/EXACT-200 are **396/396 bytes** at `0x00498B80` and **305/305 bytes**
at `0x00498D10`. Both matched locked MSVC 19.44 x86 native body bytes,
with all **38 original relocation destinations independently recovered
from original PE instructions**, and **112/112** affected canonical native
units strictly replayed after cold-compiling only their **20** actual
source providers. Their authentic return ABI is an eight-byte pair of
`EnemyQueuedRecord*` and `ShotMetadata*`, not a `shared_ptr` copy.
Source: [complete native exact selectors](ENEMY_QUEUED_SELECTORS_EXACT_RECONSTRUCTION.md).

The active full-root draft is `.analysis/core201-enemy-dispatch-candidate.cpp`
with GCC test host `.analysis/core201-dispatch-host.cpp`. The host links the
**unmodified production** `src/EnemyQueuedSelection.cpp` as its 85th
translation unit. Its historical `writable_queued_metadata_candidate` and
`shared_queued_metadata_candidate` helper names are now *only trivial
forwarders to the real production members*, without any separate private
COW algorithm body. The complete ECL caller's
`select_queued_metadata_boundary` likewise forwards every **unhooked**
call to `EnemyState::writable_shot`. Existing optional test-only failure
injection remains explicitly available to preserve earlier exception-order
regression scenarios, but there is no fake selection implementation in the
normal path.

This replacement applies to the real current complete-root source-draft
branches 609–612 (four-way PMR `BulletCommand` mutations), 700/701 (record
position and metadata writes), and 702/703/711/713 (typed Laser parameters
and true PMR command deep copies). Real downstream complete native-byte-exact
`LaserController::create_laser` and `register_laser` production methods remain
linked and executed in the previously validated source-draft paths.

## New verification in addition to all prior complete-root cases

The new `.analysis/core201-exact-queued-selector-host-cases.inc` adds
**230** scenarios, including **152 direct calls** with real
`std::pmr::forward_list` and `std::shared_ptr` ownership covering missing,
unique and multiply shared metadata values; list extension; native return
pointer identity; deep copied PMR commands; no COW on the ensure-only route;
and complete nonqueue EnemyState byte-image preservation.

Another **60 complete original-opcode executions** traverse the actual 396B
writable selector for 609–612, 700/701, 702/703 and 711/713. These exercise
real typed record/metadata structures and the distinct native write/VM
operand order. **24** of those include live typed Laser parameter creation
paths. The final **18 staged VM exceptions** verify COW or null-owner
allocation has already committed, preserving original shared metadata
isolation before later operand reads throw. All old 631 owner scenarios,
all previous 42,743 complete-root cases and every older native-byte-exact
callee are retained.

The **full 85-translation-unit** host passes **42,973/42,973** scenarios
under both GCC13 `-O2 -Wall -Wextra -Werror` UBSan and ASan+UBSan, with
ASan leak detection enabled. Only `vptr` checking is disabled for unrelated
unimplemented `WeaponStoneInfo` fixture RTTI. Both full build/run logs,
all five active private source/recipe input hashes, actual production
source/receipt hashes and both host binary digests are recorded in
`.analysis/core201-enemy-whole-root-proof.json`. The live host outputs are
`.analysis/core201-dispatch-host.log` and
`.analysis/core201-dispatch-host-asan.log`; the binaries are
`build/core201-dispatch-host` and `build/core201-dispatch-host-asan`.
All CORE199/198/197 and prior root, native and historical proof artifacts
remain protected.

## Acceptance scope and next important work

CORE201 changed **only ignored private host inputs**, *not* maintained
production source, canonical manifest or compiler profile. Therefore its
native affected cold-build/replay scope is **zero**: CORE200's already
accepted **112/112** receipt-grounded native units remain unchanged.
No whole repository native cold replay was run. Conservative exact totals
remain **224 authored whole native functions / 58,692 code bytes**.
The current *semantic* whole-root source draft covers **134 effective opcode
values and 102 native primary heads** of 174; this is **not** x86 compiler
identity for the original **41,967-byte** Enemy boss. Original switch/EH
partition, missing primary branches, concrete derived Laser allocation and
virtual init, Stage/Renderer ownership and other large roots remain open.
Continue to attack **large boss functions and their genuine leaf dependencies**,
without using the passing GCC fixture to claim complete executable exactness.
