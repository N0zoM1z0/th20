# Enemy state opcode source frontier

## CORE/EXACT-148 scope

The private source for the whole EnemyState dispatcher at 0x48C010 now covers
53 effective values / 28 primary heads: the unchanged 400..448 movement body
plus 514, 521, 563 and 564. This is source work toward the complete root, not a
production implementation or partial exact credit. The exercise's explicit
instruction argument and out-of-domain exception are host boundaries; native
prologue, default, remaining cases, full tables/EH and compiler extent remain open.

Five complete dependencies are separately accepted from natural maintained
Session.cpp and PlayerRecord.cpp, using their existing per-source profiles:

| Entry | Complete bytes | Maintained function |
| --- | ---: | --- |
| 0x488850 | 42 | Session::field_70_is_two |
| 0x474D60 | 25 | Session::clamped_field_1f4 |
| 0x474D80 | 73 | PlayerTable::clamped_field_1f4 |
| 0x497CC0 | 87 | PlayerRecord::add_field_dc |
| 0x497C60 | 87 | PlayerRecord::add_field_e0 |

All five full contributions, totaling 314 bytes, strictly replay from fresh
canonical objects. Their authored/compiler/library origins remain pending;
authored exact coverage is unchanged. No target-sized prefix, assembly, padding,
ABI alteration or source-profile selector is used.

## Native caller behavior

The existing attested whole-root listing covers all four reviewed intervals:
514 at 0x493B74..0x493E53, 521 at 0x493E54..0x493EAB, 563 at
0x490C38..0x490D18 and 564 at 0x490D19..0x490D8F. These intervals are navigation
boundaries within the same root and do not define separate functions.

Opcode 514 borrows the name at instruction+32. Its ordinary path reads life
argument 1, caches the actual Enemy receiver, reads time argument 2, then index
argument 0, and calls the accepted phase producer.

The replacement path requires Session+0x70 equal to 2 and state flag word04 bit7.
It first observes whether state+0x270 is zero, then queries the mutating clamp of
PlayerTable+0x1F4. Only a result of 7 queries the existing clamp of +0x1FC, which
is compared with 41. Both queries clamp to 0..999. Replacing the first query with
a mode getter would lose its write and read the wrong field.

For the matching early range, the death name is `MBossDead` when state+0x270 is
zero and `MBossBDead` otherwise. Other ranges use `BossDead`. The replacement
reads arguments 2 then 0 and configures life 0. It reloads the receiver, reads
argument 0 again and sets the timeout name to `BossEscapeSpell`. It never reads
life argument 1 on this path. Native literals are independently bound to the
locked PE in the caller evidence; original spelling and case are preserved.

Opcode 521 borrows the name at instruction+24, caches its Enemy receiver before
reading index argument 0, then invokes the accepted timeout producer. Borrowed
names remain live pointers through operand evaluation.

Opcode 563 reads argument 0 only when the original state+0x284 is 0 or 1. For 0,
it stores the argument and adds it to the selected record's fieldDC only when
positive. For 1, it stores the argument and always adds the new value minus one
with native 32-bit wrapping. Other original values perform no operand read.

Opcode 564 skips its Session query when state+0x284 is zero. Otherwise it queries
the +0x1FC clamp even if state+0x280 will differ. Equality adds state+0x284 to the
selected record's fieldE0 and clears state+0x284. Record selection uses the real
Context and its borrowed PlayerRecord pointer.

## Callee identity and semantics

The complete predicate reads the actual Session field70 and returns bool in AL.
The 25-byte forwarding query reaches PlayerTable at Session+0x88. Independent
inspection of its full 73-byte callee establishes offset +0x1F4, bounds 0..999,
write-back and returned value. A rejected private raw +0x1E4 getter had only
20 bytes and disagreed with this native body; it never entered production source.

Both record updates add full 32-bit words before interpreting the signed result
and clamping to 0..999999. Unsigned source arithmetic preserves wrap without
portable signed-overflow UB. Native stores and ignored return-register contents
support void methods. Their complete relocation replay and the table query use
the previously established integer-clamp identity at 0x471170; no compared field
is solved for an anchor. Original roles for these neutral scalar names remain open.

## Verification and limits

The single expanded draft passes all 459 previous movement/read-order scenarios,
8,822 phase callers, 9 timeout callers and 540 counter callers: 9,830 total
O2/UBSan scenarios. Phase images cover every live 136-byte record; Session images
check all unrelated bytes. Tests exercise signed extremes, conditional query
writes, repeated indices, cached receivers, context retargeting, borrowed-string
mutation, count wrapping and conditional clearing. Actual canonical phase,
Session, Context and PlayerRecord bodies run unchanged.

ECL scalar operands and unresolved startup/resource lifetimes remain explicit
fixture boundaries. Names are valid, nonoverlapping and at most 63 bytes. The
private operand hooks test observable sequencing with live owners; these results
do not establish that every adversarial state occurs during native gameplay.
Whole dispatch execution and native runtime behavior remain unclaimed.

The focused public Session O2/UBSan test separately checks actual process/static
construction, whole-owner preservation, both query layers and record counters.
Captured includes select 18 providers / 169 previous units. They are cold-built
once and all strictly replay; 146 unchanged providers reuse existing evidence.
Eleven literal-label renames preserve full original/fresh COFF data and unchanged
roles, targets and addends. Only 169 affected and five new units are replayed.
Cleanup verifies protected hashes without additional replay or compiler calls.

## Protected evidence and next work

Private paths are relative to `.analysis/`:

- `core148-enemy-dispatch-candidate.cpp`, `core148-draft-scope.json`
- `core148-state-caller-evidence.json`, `core148-helper-probe-diagnostic.json`
- `core148-dispatch-host.cpp`, `core148-dispatch-host-recipe.json`, `core148-dispatch-host.log`
- `core148-session-semantics.log`, `core148-independent-bindings.json`
- `core148-cold-proof.json`, `core148-affected-results.json.gz`, `core148-new-exact-results.json.gz`
- `core148-pre-session-inputs.json.gz`, `core148-retired-inputs.json.gz`
- `core148-graph-audit.json`, `core148-cleanup.json`, `core148-gates.json`

Preserve original inputs/receipts and native exports; retire superseded binaries
only after verified replacements. Continue the same whole-root source beyond
these four state paths. The remaining 500..575 owner/state family includes HUD,
laser and other genuine receiver boundaries that reference service adapters do
not close. Preserve the complete root under [dispatcher evidence](CORE_ENEMY_DISPATCH_LAYOUT.md)
and reuse the accepted [phase producers](ENEMY_PHASE_PRODUCER_INVESTIGATION.md).
