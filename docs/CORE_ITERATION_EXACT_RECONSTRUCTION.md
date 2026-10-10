# Whole core iteration and dispatch exact reconstruction

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

CORE/EXACT-099 admits seven complete core methods on the actual shared
HitCtrlInf, FunctionChainController, allocator, Context and iterator owners.
It supersedes the iterator-related nonexact results in CORE097/098.

## Complete contributions

| Maintained method | Native address | Body | Complete compared bytes |
| --- | --- | ---: | ---: |
| HitCtrlInf ordinary destructor | 0x004C0120 | 230 | 235 |
| HitCtrlInf::find | 0x004C0D00 | 264 | 264 |
| HitCtrlInf::update | 0x004C02D0 | 248 | 248 |
| FunctionChainController::insert_update | 0x00411F80 | 381 | 381 |
| FunctionChainController::insert_draw | 0x00412100 | 381 | 381 |
| FunctionChainController::update | 0x00412810 | 611 | 648 |
| FunctionChainController::draw | 0x00412AA0 | 587 | 612 |

Every contribution strictly replays all bytes with independent relocation
anchors. Update includes one original NOP and its nine-entry pointer table;
draw includes one NOP and its six-entry table. The hit-owner destructor's
complete COFF contribution includes five INT3 alignment bytes. Another five
linker alignment bytes precede the next native head and do not belong to that
compiler contribution. Full locked-target decoding reconciles all direct
branches and instructions omitted by Ghidra function exports. No target-sized
prefix, omitted case or padding reduction is used.

## Declaration and lifetime evidence

A minimal candidate-compiler experiment distinguishes class/public from
struct declarations: only the class form naturally injects the observed
automatic member initialization before hidden-return iterator construction.
Default constructor arguments alone do not explain it; the actual constructor
still requires its start pointer. The production IntrusiveIterator uses this
class declaration with both fields public. It retains its two-pointer 8-byte
x86 layout, constructor/destructor bodies and observer repair protocol.

This is candidate compiler evidence and an inference about original source
spelling. It does not prove a project-wide compiler/profile setting. The
class declaration changes COFF class tags for aggregate results, pointers and
references, while complete typed producer/consumer replay corroborates the
same calling conventions and layout. Twenty-one complete shared contributions
replay as support. Both compiler-generated 31-byte initialization helpers map
to an existing physical root, receiving no duplicate credit. No hand-written
initializer or fabricated default constructor is introduced.

Ordinary destruction puts its real region iteration inside a block ending
before automatic TaskInfo cleanup. Dispatchers process non-null callbacks in
an outer conditional. Their action scopes preserve real lock release/reacquire,
shutdown entry without invoking the update callback, retry, restart, counts
and observer cleanup. Distinct update actions 4 and 8 retain separate exit
blocks. Invalid actions fall through the ordinary count path. Every original
table destination and otherwise unused native exit remains in the comparison.

Seven full x86 EH protocols also replay independently: 29 handler, FuncInfo,
unwind-map and complete cleanup contributions, totaling 699 support bytes.
The independently decoded native handlers identify their FuncInfo and unwind
tables; table consumers identify cleanup heads. These bindings are not solved
from compared root fields. Support records add no physical coverage.

## Verification and limits

Seven complete core functions add 2,769 disjoint compared bytes and 174
independent relocations: actual HitCtrlInf destruction, find and update,
FunctionChainController update/draw insertion and both full dispatchers.
The frozen 240-file graph passes 689/689 strict units across 135 fresh objects
and 134,296 disjoint bytes. Source mappings remain 702, with thirteen whole
nonexact methods. Authored exact coverage stays 84 functions/24,209 bytes;
reference absorption stays 238 and all 6,945 reviews remain terminal.

All 64 public tests pass in 205.315 seconds. Existing actual scheduler
and hit-owner fixtures additionally pass O2/ASan/UBSan. They exercise all
actions, retry/restart/shutdown, count/order/locking, pending-node removal,
observer repair, four owned registrations, both hit-owner views, identifier
wrap, shapes, pool reuse, double retirement, clocks, mixed 261-region update
retirement and 259-region destruction. Temporary test executables are removed.
Process placement, resource and allocator startup remain explicit fixtures.

The original whole damage query, Bomb/Player/item/reward/callback protocol and
playable game startup/runtime remain open. Global hit-owner creation, region/
node factories and unlocked removal remain whole nonexact bodies. Origins,
authored coverage and reference absorption are not inferred from byte matches.

Protected interim/final retirement removes 198 products/10,806,857 bytes
gross (8,371,341 net after lossless historical inputs). All current canonical
objects/receipts and native evidence stay protected. Post-cleanup strict
results equal the retained frozen reports without another cold build.

Private evidence: core099-production-bindings.json,
core099-native-roots-audit.json, core099-template-support.json,
core099-production-eh-support.json, core099-semantics.json,
core099-final-frozen-source.json, exact099-canonical-results.json.gz,
core099-registered.json, core099-interim-cleanup.json,
core099-final-cleanup.json and both core099 retired-inputs archives.
Completed writers must never rerun.
