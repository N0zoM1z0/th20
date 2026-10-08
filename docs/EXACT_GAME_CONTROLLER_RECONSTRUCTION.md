# Actual Game construction and state

EXACT-077 establishes the real Game owner required by the Enemy readers'
restart-state dependency. Five complete construction/state contributions add
362 body /367 comparison bytes. Complete Game loading, updates, cleanup and
whole-game runtime remain open.

## Native owner and original identity

The diagnostic allocator at `4B9B10` requests `0x110` bytes (272), runs the
native compiler pre-clear helper and calls `4B9DF0`. The constructor calls the
real 16-byte Task base, installs the original vtable at `570B04`, and constructs
two actual Timers and the actual 176-byte Configuration. Independent original
RTTI identifies `GameInf`; its three virtual slots are scalar deletion at
`4BA400` followed by inherited Task enable/disable. The original log literal
at `570B10` is `initialize GameTaskInf\n`.

The two Timers begin at `10` and `20`, stage/state words at `30`/`34`, and
Configuration at `38`. A real zero-initialized flag aggregate starts at `E8`,
distinct from the inherited Task flags at `04`. Three scalar words occupy
`EC`/`F0`/`F4`; MOVSD writes establish two doubles at `F8`/`100`. Signed restart
mode and the last scalar word begin at `108`/`10C`. Natural double alignment
gives the observed whole size without an explicit padding field or Services
suffix. Independent factory `4BEC70` publishes the owner at `5BA828`, stores
the restart argument and sets flag bit2 before scheduling loading. That
factory is evidence; it is not a newly accepted source implementation.

`src/GameController.hpp/.cpp` maintains this storage and its construction/state
methods. Original names beyond the established roles are uncertain; offset
labels retain that uncertainty. Vtable/RTTI identity independently anchors the
constructor relocation, without claiming linked reconstruction of all original
RTTI data or disposal.

## Complete comparisons

| Native address | Maintained contribution | Body / comparison bytes |
| --- | --- | --- |
| `4B9DF0` | `GameController::GameController` | 245 / 250 |
| `424030` | `GameController::update_suppressed` | 40 / 40 |
| `424060` | `GameController::animation_frozen` | 25 / 25 |
| `488830` | `GameController::restart` | 20 / 20 |
| `4BD920` | `GameController::clear_flag_6` | 32 / 32 |

The constructor includes its entire compiler contribution and all five
following compiler INT3 bytes. Its complete 29-byte EH handler and 36-byte
nonthrowing information record match the native support. All relocation anchors
come from independent native member calls, original type/log identity and prior
canonical units. No compared relocation field is solved for a destination.

The predicates return full-width integer 0/1. Native callers test EAX; the
reference's bool return changes the original ABI and emission. Suppression
combines bit0 and bit2; animation freeze observes bit1. Clearing bit6 preserves
every other flag and all unrelated owner storage. Restart preserves the full
signed word, including negative values.

One `build/GameController.obj` uses
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The frozen graph passes 580 units /106 fresh objects /100,983 disjoint
comparison bytes. Origins are 507 pending, nine library and 64 authored /
16,948 authored bytes. Five whole reference associations close, bringing
absorption to 189 across all 6,945 terminal reviews. Their original parser
address-hint fields were empty; this batch independently establishes the
native associations. Source-only Services and extracted reference configuration
initialization are not imported or asserted exact.

## Owned semantic verification

O2/UBSan checks use production Game/Task/Timer/Configuration construction and
the actual release diagnostic body. Dirty guarded storage verifies typed
defaults, native binding defaults, preserved Configuration high option bits
and natural Configuration gaps. Exhaustive low-nine-bit patterns include
unrelated high flags; full snapshots check that both queries preserve the whole
owner and bit6 clearing changes only its flag word. Signed restart extremes
are observed without mutation.

The Game destructor is an explicitly declared fixture that performs no native
Game retirement. Native subsystem cleanup, callbacks, graphics/audio, global
publication/retirement, loading and updates are not verified by this test.
Native EH and x86 layout are independently checked by complete exact replay.

## Corrected shared getter routing and remaining work

The earlier label "Game +44 frame getter" for `4992F0` was incorrect. Full
reader exports show a direct Context slot0 lookup through `40C300` and process
lookup `478E80`. Attested disassembly proves that `478E80` itself calls the
actual Session context accessor `40BBC0` followed by the same slot0 getter
`40C300`. Both routes therefore reach the Context's borrowed primary owner.
The original complete primary-owner type/storage remains unresolved.

An intermediate attribution of `478E80` to EnemyController was also incorrect
and has been corrected in the maintained ledgers and handoff. Actual process
EnemyController lookup is `478060`, through Context slot8/accessor `412730`.
No EnemyController or Game storage attribution follows from these reader
routes. Game has Configuration storage at total offset `44`. No `4992F0`
getter or complete primary-owner source acceptance follows from this routing
investigation; do not introduce a padded owner to satisfy the displacement.

The `450880` wrapper conditionally returns integer1 when the Game suppression
and freeze predicates are true; otherwise it calls the actual renderer
Controller's `4497D0` update operation. This is not an Animation member or a
free bool composition. The reference's introduced helper stays nonexact, and
no fake renderer owner is declared to close it. Full renderer/pooled owner
storage and the wrapper's complete source protocol remain separate work.

Player's untouched `+14850` original declaration remains unresolved; its full
owner is not accepted. Both complete Enemy readers, the 41 KB opcode root,
Game startup/loading/update/disposal and whole-game linking/runtime remain
open. The real Game constructor and restart dependency are now available to
that work without substituting a partial owner.

Private evidence includes `core077-game-owner.asm`, `core077-game-support.asm`,
the bounded renderer update entry, `core077-primary-owner-routing.asm`,
`core077-audit.py`, native RTTI/vtable/log/EH
support and compressed canonical proof. Configuration, registration and
retirement writers are completed one-time operations and must never be rerun.
Current objects/receipts, native evidence and original tools/game/reference
are protected; cleanup verification reuses existing objects.

All 48 public tests pass (91.308 seconds); target, tracking, reference and
progress gates pass. Protected cleanup retires two probe object/receipt files,
27,645 bytes, and losslessly archives two inactive successful replay snapshots,
saving 248,274 bytes. Original-content SHA-256 roundtrips are checked; all 212
current canonical hashes and native/failed source evidence remain unchanged.
Post-cleanup strict replay passes 580/580 with existing objects and no rebuild.
Inventory and gzip proof are private. Total batch savings are 275,919 bytes;
cumulative retired products are 2,540 files /1,002,339,503 bytes, with separate
archival savings of 12,865,565 bytes. Analysis is about 74 MiB and build 4.7 MiB;
installed tools/game/reference/Ghidra stay protected.
