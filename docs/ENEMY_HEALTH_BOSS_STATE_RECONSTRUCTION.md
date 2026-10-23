# Enemy health, boss slots and state parameters

## CORE/EXACT-150 scope

The same private whole EnemyState dispatcher draft at 0x48C010 includes eighteen
more native paths, reaching 80 effective values / 55 primary heads. All earlier
movement, phase, counter and drop bodies are preserved. The production dispatcher
remains undefined; no switch fragment, helper-sized prefix or private exercise
entry receives original-function credit. Complete remaining owners, default,
tables, EH and compiler contribution remain open.

| Entry | Complete bytes | Maintained function | Origin |
| --- | ---: | --- | --- |
| 0x49C2E0 | 85 | EnemyController::set_selected | Authored |
| 0x49C4B0 | 42 | EnemyController::set_field_84_bit_0 | Pending |
| 0x49C340 | 23 | EnemyHealth::set_scaled_health | Pending |

These three complete strict units add 150 comparison bytes. Only the 85-byte
publisher adds authored exact credit. Its independent origin evidence is the
custom game-owned Enemy identifier/null handling and Controller slot protocol,
corroborated by the actual ECL registration/clear caller. Primitive writes and
byte identity do not establish authorship. Original names and the broader role
of the Controller flag remain unknown.

## Actual owners and complete callees

EnemyData.cpp owns the publisher, flag write and scalar EnemyHandle assignment,
alongside the real Data/handle constructors. EnemyHealth.cpp owns the raw read
and scaled write. No translation-unit profiles change. EnemyDataWord remains
four bytes, with a native bit-zero view over its existing word; the old Data and
Controller constructors retain complete exact output.

The publisher obtains a by-value Enemy::identifier_value for a non-null actor,
then reads the copied scalar. A null actor supplies zero. Only afterward does
it access the actual sixteen-slot array at Controller+0x54 with at() and assign
the identifier. It stores an identifier rather than a pointer, does not alter
the actor or other slots, and retains the checked access for null publication.
The flag method writes only bit0 at Controller+0x94, preserving the upper bits.
The scaled write stores low32(input*7) at EnemyHealth+0x0C with defined unsigned
arithmetic, including overflow.

Four typed uses fully equal existing physical contributions, with identical
complete bytes, no relocations and compatible x86 scalar/pointer widths:

| Typed use | Existing canonical contribution | Bytes |
| --- | --- | ---: |
| EnemyHandle::operator=(uint32) | identifier_set, 0x4117A0 | 21 |
| EnemyHealth::get_health | identifier_get, 0x40C300 | 16 |
| EnemyHealth::set_initial | enemy_pattern_set_base_kind, 0x411570 | 22 |
| EnemyHealth::set_phase | cursor_set_count, 0x49C4E0 | 22 |

These aliases add neither a physical mapping nor duplicate exact credit.

The prior canonical selected caller independently binds the checked array
access to 0x484980. Its complete native 32-byte body checks unsigned index<16,
then returns the four-byte element address or invokes the range-failure path.
The current compiler emits a 34-byte helper under the retained profile. This
helper receives no exact unit. The exact publisher reuses its independently
reviewed native identity; no relocation destination is solved from a compared
field and no exception/profile contract is changed to remove the difference.

The existing void set_health body emits 21 bytes against the native 24-byte
scalar write at 0x45D650. Native health callers discard EAX; the broader folded
function's return contract is unresolved. The exported additional color-word
caller also ignores EAX and does not settle that question. No invented return,
new mapping, exact credit or prototype change is introduced for this write.
The private health-path fixture claims its observed ignored-return writes only.

## Native state paths

The attested whole-root listing and complete callee exports establish these
paths inside one dispatcher, rather than eighteen new functions:

| Opcode | Native behavior |
| --- | --- |
| 500 | Write bounds+5C X then Y; afterward, pending+284 equal to zero becomes one and credits the selected record's fieldDC |
| 501 | Write bounds+64 X then Y |
| 504 / 505 | Set bit1 of word04 before reading/storing four bounds+178 floats; or clear only that bit without operands |
| 511 | Read integer0 once; write current, initial and phase health; marked word04 bit7 also sets bit14; scale a fresh raw-health read by seven |
| 566 | Write only current and scaled health; retain initial/phase values and state flags |
| 512 | Register or clear a boss handle with the sequencing below |
| 513 / 515 / 535 | Assign timerA8 zero without operands; or assign timer288/timer298 integer0 through the real Timer protocol |
| 526 | Store float0 at +274, then square that stored field |
| 557 / 543 | Read integer0 before replacing only bit12 of word00 or bit15 of word04 from its low bit |
| 558 / 559 | Store float0 at +38 or +4C |
| 544 / 546 / 547 | Store integer0 at +30, +34 or +264 |

Names for unresolved scalar roles remain neutral. Bounds writes are observable
between successive operand reads. Opcode500 tests pending and selects Context
only after both float writes, retaining the existing wrapping/clamping record
method. Timer assignment preserves its independently established mode flags,
previous/current/fraction values and full signed input.

Opcode512 reads signed integer0 before any Context query. It clears Controller
Data flag bit0 first. For a negative input, only a previously marked boss clears
its old +270 slot; the state boss bit is cleared after that checked call. An
unmarked negative path never reads the old slot and retains +270.

For a nonnegative input it sets the boss bit before publishing the current
entity, then stores +270 only after successful checked publication. It reloads
the actual Context controller for publication. Consequently, invalid registration
retains the newly set boss bit and old +270; invalid marked removal retains the
old boss bit. Both failures still clear the Controller flag bit first. The
maintained private caller and exception-image models preserve these writes.

## Verification and boundaries

Captured includes select 18 providers / 86 previous exact units. They are
cold-built once and strictly replay, followed by the three new complete units.
The other 146 providers reuse valid evidence. Two string-label renames preserve
complete old/new COFF data, relocation roles, addends and native destinations.
There is no unfiltered replay, full CI run or cleanup-triggered rebuild/replay.

The focused public creation fixture runs actual Controller/Data/handle storage,
publication, by-value identifier/getter, checked array and scalar-assignment
bodies. Its 204 publication/exception cases verify all sixteen slots, null,
full-width identifiers, range failures and whole Controller/actor images. Six
raw-health edge inputs verify sevenfold wrapping and preservation. Existing
creation/reset/phase/selection checks still pass under O2, Werror and
nonrecovering UBSan. Startup, activation, whole-list find and resource-absent
Controller destruction remain explicit fixture boundaries.

The expanded private root passes all 11,921 prior scenarios plus 3,698 new
health/boss/parameter cases: 15,619 total O2/UBSan scenarios. Full state,
Controller and Session images cover operand mutation, late Context/entity
selection, signed slot/gate extremes, exception write order, Timer modes,
wrapping health and field preservation. Raw float storage includes signed zero,
infinities and quiet NaNs; arithmetic NaNs claim classification only. The
integrated fixture captures the already canonical by-value identifier getter
while retaining earlier ECL/resource/drop boundaries. The public creation test
separately executes that genuine getter with the full publication chain.
Original CRT exceptions, startup, full runtime and whole-program linkage are
not established by these host fixtures.

## Preserved evidence and next work

Private paths are relative to `.analysis/`:

- `core150-health-context-native.asm`, `core150-handles-at-native.asm`, `core150-state-parameters-native.asm`
- `core150-health-write-xrefs.txt`, `core150-health-return-consumer.asm`
- `core150-owner/`, `core150-owner-probe-diagnostic.json`, `core150-owner-v2-diagnostic.json`
- `core150-enemy-dispatch-candidate.cpp`, `core150-draft-scope.json`, `core150-health-host-cases.inc`
- `core150-dispatch-host-recipe.json`, `core150-dispatch-host.log`, `core150-creation-semantics.log`
- `core150-independent-bindings.json`, `core150-unaccepted-emission.json`
- `core150-pre-owner-inputs.json.gz`, `core150-retired-inputs.json.gz`
- `core150-cold-proof.json`, `core150-affected-results.json.gz`, `core150-new-exact-results.json.gz`
- `core150-graph-audit.json`, `core150-cleanup.json`, `core150-retirement-plan.json`, `core150-gates.json`

Continue the same whole-root source through genuine remaining HUD, Card, laser,
selection/clear and state receivers. Preserve the unresolved scalar return,
checked helper and [scatter emission](ENEMY_DROP_PROTOCOL_RECONSTRUCTION.md);
do not repeat unchanged trials. See [whole dispatcher layout](CORE_ENEMY_DISPATCH_LAYOUT.md).
