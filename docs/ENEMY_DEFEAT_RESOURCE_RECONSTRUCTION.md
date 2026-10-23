# Enemy defeat resource dependencies and corrected owner fields

CORE/EXACT-153 follows the complete Enemy::defeat caller at 0x4A5640, preserving
its entire 1,371-byte ordinary body as the reconstruction boundary. It closes
actual angle, file-routing and effect-handle dependencies. The whole defeat
implementation and the whole Enemy opcode dispatcher remain undefined. Current
acceptance and protected products are in [the handoff](RE_HANDOFF.md).

## Corrected storage hypotheses

EnemyController +128 is an Angle, rather than the former Identifier32 hypothesis.
The constructor's shared zeroing head at 0x447DE0 alone could not distinguish
those types. The complete native setter at 0x4AB820 passes a float to the already
accepted Angle assignment at 0x452F20, which normalizes it and writes a float.
The complete defeat caller supplies a death-effect direction to that setter.
Maintained `angle_128` now uses the genuine shared Angle body. x86 size 0x134 and
all offsets remain unchanged; no whole-game flag or compiler assumption follows.
The constructor relocation changes to the independently accepted Angle identity,
with the same canonical destination and complete bytes.

EffectInfo's former six-file-pointer declaration also conflated different native
members. The real loader at 0x49DA70 writes three file slots at +10, +14 and +18.
Native slot selection independently advances the signed handle cursor at +20;
constructor 0x49CE80 initializes these fields separately. Maintained storage now
has three actual file pointers followed by neutral field1C, handle_cursor and
field24 words. Worker remains +28, handles +3C, requests +103C, and the complete
x86 owner remains 0x13044 bytes. Scalar roles beyond the reviewed cursor stay
unknown. File lookup fixtures cover the positively identified indices 0..2;
no additional file slot or interpretation of field1C/field24 is inferred from
zero initialization alone. This is the existing genuine owner in ItemResourceOwners.hpp; no service
suffix, method-only facade or invented padding is added.

## Complete accepted dependencies

| Method | Native entry | Complete bytes | Origin |
| --- | --- | ---: | --- |
| EnemyController::set_angle_128 | 0x4AB820 | 39 | Pending |
| Enemy::animation_file | 0x499430 | 44 | Pending |
| EffectAnimationHandle::matches_value | 0x449430 | 45 | Pending |
| EffectAnimationHandle::missing | 0x49BED0 | 45 | Pending |
| EffectInfo::select_handle_slot | 0x498E70 | 196 | Authored |
| EffectInfo::publish_handle | 0x497D20 | 79 | Authored |

All six complete roots strictly replay 448 disjoint bytes. The two custom
publication roots contribute 275 authored bytes. Their bounded pool traversal,
original stale/live resolution policy, cursor state and tagged publication are
game-owned orchestration, separately establishing origin. Small wrappers and
accessors retain pending origin classification.

The Enemy file getter caches its actual Context Controller and forwards the full
signed index to the genuine Controller::animation_file. Its complete 151-byte
native dispatcher at 0x4AAE10 routes indices 0, 1 and 7 through distinct actual
resource owners before its ordinary array path. That method remains undefined;
replacing it with a convenient array-only getter would discard observed behavior.

## Native publication order

Selection saves the previous cursor, advances the live signed cursor modulo
1024, then inspects the new slot. A zero raw word returns the previous cursor
without resolution. Otherwise the real handle resolves through the existing
AnimationHandle interface: a nonnull result returns the previous cursor, while
a missing result continues the scan. Resolution may clear stale words. After
1024 missing results, selection returns -1 and retains those side effects.

Publication rejects -1 or a result at least 1024, returning zero. Otherwise it
writes the full input word to the returned previous slot and returns that index
with bit31 set. It performs no implicit retirement or rollback. In particular,
selection tests the advanced slot but publication writes the returned previous
slot. Zero and live entries are accepted; missing entries are skipped. These are
native observations, not an allocator policy to repair.

Callbacks may change the live cursor during resolution. The selected previous
index remains cached, while callback changes survive. An exception leaves the
already advanced cursor and earlier stale-word clears, but prevents publication.
The reviewed input domain starts with a cursor in 0..1023 and live owner/array
storage. No production bounds guard is invented for invalid cursor state.

The first source used `previous = handle_cursor++`; the compiler introduced a
second temporary and six additional bytes. Separately saving the old cursor and
incrementing it expresses the observed state sequence directly and matches the
complete 196-byte root. All maintained bodies remain natural shared C++, with
unchanged per-source profiles and no alternate match paths or shaping locals.

## Independent verification

Captured input closures select 16 providers / 73 prior units. Those serial cold
builds and strict replays pass. The cursor-order correction then rebuilds only
ItemLifecycleAccess.cpp and replays its eight prior units; the other 15 freshly
built providers are reused. Six new roots pass complete canonical replay.
The other 148 providers reuse their existing valid evidence. No unfiltered
replay or full CI is run.

The constructor alias and pointer-array type correction are reconciled per
relocation role, with unchanged target, offset, type and addend. Complete old/new
unchecked pointer-index bodies equal the existing 22-byte physical index unit;
no duplicate credit is added. Previously accepted Angle, Context and handle
resolve identities supply the remaining canonical bindings. New callee identities
are reviewed with complete native bodies and actual owner flow; no compared
relocation field is solved.

Public O2/UBSan fixtures pass 4,484 publication scenarios, including every cursor,
full-width inputs, wrap, live/zero/stale entries, a full 1024-miss scan, whole owner
images, lookup exceptions and callback cursor mutation. Fifteen Controller cases
check float normalization and unchanged owner bytes, including negative zero,
infinity and NaN. Retained Item and Enemy creation/clear checks also pass. The
unchanged private whole-root draft is rebuilt against current declarations and
passes its existing 19,350 cases over 96 values / 67 heads. It receives no new
source acceptance, case credit or partial exact credit in this batch.

Native Renderer resolution, actual Effect/Controller resource loading and
resource-owning startup/destruction remain explicit fixture boundaries.

## Remaining whole defeat work

The complete caller recursively defeats child nodes, re-reads each child through
its observed link before setting bit9, destroys its iterator, and detaches its
parent link. It then handles sound, death animation/direction, actual Controller
angle publication and drop state. Its reward branch uses PlayerFeedback,
PlayerRecord, WeaponStoneInfo and process random state, followed by optional ECL
termination/reset/call/tick and the actual callback. Child, resource and callback
order must survive exceptions and mutation.

The process slot at 0x5C6118, read by 0x513DD0, supplies an owner whose byte +B0
is tested at 0x485A40. Its actual type, construction and lifetime remain unresolved;
no owner prefix or replacement service is introduced. Native xrefs include writes
at 0x513CD4 and 0x514253. Continue from those actual producers before maintaining
the whole reward path. The 151-byte Controller file dispatcher also needs its
remaining genuine resource owners. Keep complete control flow, EH and all
resource effects in scope; declarations and captured calls do not close defeat.

Private evidence under `.analysis/` includes `core153-native-body-audit.json`,
`core153-independent-bindings.json`, `core153-symbol-role-reconciliation.json`,
`core153-cold-proof.json`, `core153-slot-order-exact-results.json.gz` and
`core153-new-exact-results.json.gz`. Original inputs/receipts are preserved in
`core153-pre-defeat-inputs.json.gz` and `core153-pre-slot-order-inputs.json.gz`.
Current frozen sources and cleanup are recorded in the handoff. Receipts remain
immutable; cleanup verifies protected hashes with zero extra builds or replay.
