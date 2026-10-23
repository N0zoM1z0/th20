# Enemy drop protocol and dispatcher callers

## CORE/EXACT-149 scope

The same private whole EnemyState dispatcher draft at 0x48C010 now includes
506..510, 556, 567, 568 and 572. The preceding movement/phase/counter bodies are
unchanged. The resulting exercise has 62 effective values / 37 primary heads;
it is neither a production dispatcher nor partial exact credit. Native default,
remaining cases, tables, EH and complete compiler contribution remain open.

The maintained 168-byte EnemyPattern owns both sixteen-word arrays, Timer,
kind selections and radii. Its value operations remain in EnemyPattern.cpp;
the two complete spawning protocols share ItemSpawn.cpp with the real ItemInf
producer. Enemy.cpp owns the actual Enemy flag query. All existing per-source
profiles are preserved, including /fp:strict and /GS for ItemSpawn.cpp.

| Entry | Complete native bytes | Maintained function | Result |
| --- | ---: | --- | --- |
| 0x48BF10 | 239 | EnemyPattern::drop | Strict exact; authored |
| 0x4A5350 | 630 | EnemyPattern::emit_items | Whole source, 628 compiler bytes; nonexact |
| 0x411570 | 22 | EnemyPattern::set_base_kind | Strict exact; origin pending |
| 0x49C7B0 | 44 | EnemyPattern::set_count | Strict exact; origin pending |
| 0x49C780 | 44 | EnemyPattern::set_extra_count | Strict exact; origin pending |
| 0x49C6F0 | 42 | EnemyPattern::set_duration | Strict exact; origin pending |
| 0x49C830 | 45 | EnemyPattern::set_radii | Strict exact; origin pending |
| 0x49C0C0 | 26 | Enemy::bomb_drop_disabled | Strict exact; origin pending |

Seven new physical units total 462 strict bytes. Only the complete 239-byte
drop producer adds authored exact credit. Both complete producers have
independent game-specific origin evidence: Enemy-owned selections/counts,
actual Item pool production, ECL callers and the shared game RNG. Primitive
setters and predicates do not acquire authored origin from byte equality.
Ghidra's Gdiplus label at 0x411570 does not establish its ownership or origin.

The complete 22-byte set_bomb_kind body folds with the already accepted
cursor_set_count at 0x49C4E0. The typed sixteen-word array index folds with the
existing vector3_index at 0x414580: identical full code, no relocations and
matching x86 pointer/index ABI with four-byte elements. Neither typed use adds
another physical mapping or unit. Keep the existing canonical owners.

## Native protocol

Drop selects bomb_kind when nonzero and the caller's flag is false. Otherwise
it selects a nonzero base_kind. The flag's broader meaning remains unknown;
bomb_drop_disabled describes only this observed role. Each selected branch
looks up the actual Item controller before loading its selected kind, then
calls the full producer with the borrowed origin, white color, angle -pi/2,
speed 2.2, delay 0, extra 0 and sound -1. It then always calls emit_items and
clears only base_kind. bomb_kind persists, including across repeated drops.

The scatter producer constructs one Vector3 and draws an initial angle even
when all emitted counts are zero. For each of the first fifteen slots it
caches the current raw count. A nonzero duration and signed Timer less-than
comparison enable a positive signed extra count. The effective count is:

```text
raw_count += extra - signed_low32(timer.current * extra) / signed(duration)
```

Multiplication and count updates retain their low 32 bits; division truncates
toward zero. The maintained unsigned arithmetic explicitly preserves wrapping.
The native signed loop emits nothing for a nonpositive effective count. The
native IDIV overflow case INT_MIN / -1 remains outside the defined fixture
domain, as do exhausted ordinary pools and invalid count indices.

For every item, the producer rereads the radii, computes elliptical XY at the
cached angle, scales by a fresh uniform sample in [0.5,1], clears Z and adds the
live borrowed origin. It looks up the current player controller for each spawn
and uses the same arguments as the selected drop. After every item, including
the final one, it advances the angle by pi/2 plus a fresh signed-radian sample
divided by four and normalizes it. Real ItemInf::spawn can consume additional
randomness for passive bonuses; caller/callee draws share one stream.

Only after all fifteen slots are processed are all sixteen counts cleared.
Extra counts, duration, Timer, radii, player and bomb_kind are retained. Later
slots observe callback changes, while an already cached count remains fixed.
The sixteenth slot is stored and cleared but never emitted. The setters retain
the native kind-1 indexing precondition without invented bounds checks;
set_duration stores the full word and invokes the existing Timer assignment.

## Native dispatcher callers

These are paths inside the complete root, not standalone functions:

| Opcode | Head | Observed argument and receiver sequence |
| --- | --- | --- |
| 506 | 0x491989 | Clear counts, duration and Timer |
| 507 | 0x4919A0 | Read integer kind0; cache pattern; read value1; set count |
| 567 | 0x491A1B | Same order for extra count |
| 572 | 0x4919EB | Cache pattern before integer0; set bomb kind |
| 568 | 0x491A66 | Cache pattern before integer0; set duration |
| 508 | 0x491A96 | Cache pattern; read float1 before float0; set XY radii |
| 509 | 0x491AFB | Skip all drop work when Session.field70 is 2 |
| 556 | 0x491B62 | Unconditional drop |
| 510 | 0x491BB9 | Read integer0 before caching pattern; set base kind |

Both drop paths cache the pattern receiver, query bit5 of the actual entity's
state flag word08 at Enemy+0x358, then obtain the calling state's position by
reference. They pass the flag by value and the origin by reference. Opcode509's
Session gate suppresses both queries and the call; it never reads ECL operands.
The whole-root listing, direct callees and actual owner layouts establish these
observations independently of the reference's service adapters.

## Emission, verification and remaining limits

The full scatter source emits 628 bytes against the native 630. The first
instruction disagreement is the native ESI-to-EDX copy before low-word IMUL;
the maintained code multiplies in ESI. Explicit unsigned, implicit Timer and
signed-product diagnostic expressions all retain the same 628-byte result.
The signed trial is private and does not justify weakening the maintained
wrapping contract. No inert copy, assembly, shortened extent or partial exact
claim is introduced. The complete 630-byte native callee independently anchors
the exact drop caller; its source nonexactness remains separately recorded.

Captured includes select 19 existing providers / 83 previous units. Each provider
is cold-built once and every affected unit strictly replays, followed by the
seven complete new units. The other 145 providers reuse prior evidence. Two
string-label renames preserve complete old/new COFF data and unchanged relocation
roles, addends and destinations. Existing canonical Item/Timer/controller and
reviewed typed-fold identities provide callees; immutable floats are separately
checked at their native data addresses. No compared relocation field is solved.

The focused public Item test passes O2, Werror and nonrecovering UBSan with the
actual pools, lists, RNG, Timer and production drop/scatter/primary spawn bodies.
Its 543 independent-model/boundary scenarios cover signed gates, low-word product
wrap, all kind routes, ordinary clamping, special delays, point conversion,
whole-pattern preservation, zero-count sampling and live origin/count/player
callbacks. Resource effect/ANM binding and unimplemented virtual gameplay remain
explicit captures; genuine member lifetimes run on resource-absent owners.

The expanded private whole-root exercise passes all 9,830 previous scenarios
plus 2,091 drop callers: 11,921 total. It runs real value operations, flag query,
Session predicate and position access; it captures the whole drop call contract.
It does not execute the production drop body in that fixture. The public Item
test separately executes that body and the full scatter/primary spawn chain.
No original resource VM, complete native runtime or whole-program link is claimed.

## Preserved evidence and next work

Private paths are relative to `.analysis/`:

- `core149-pattern-native.asm`, `core149-pattern-items-native.asm`, and existing `exact055-enemy-range.asm`
- `core149-enemy-dispatch-candidate.cpp`, `core149-draft-scope.json`, `core149-drop-host-cases.inc`
- `core149-dispatch-host-recipe.json`, `core149-dispatch-host.log`, `core149-item-semantics.log`
- `core149-drop*-diagnostic.json`, `core149-value-probe-diagnostic.json`, `core149-independent-bindings.json`
- `core149-pre-pattern-inputs.json.gz`, `core149-retired-inputs.json.gz`
- `core149-cold-proof.json`, `core149-affected-results.json.gz`, `core149-new-exact-results.json.gz`
- `core149-graph-audit.json`, `core149-cleanup.json`, `core149-retirement-plan.json`, `core149-gates.json`

Continue the same whole root through the remaining HUD, laser and state receivers;
retain the nonexact scatter producer and its rejected emission evidence. Preserve
all native extents and shared storage/ABI. See [state callers](ENEMY_DISPATCH_STATE_RECONSTRUCTION.md)
and [whole dispatcher layout](CORE_ENEMY_DISPATCH_LAYOUT.md).
