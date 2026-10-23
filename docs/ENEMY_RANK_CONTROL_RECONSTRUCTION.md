# Enemy rank destinations and script-time control

## CORE/EXACT-158 scope

The private whole-root draft for EnemyState::execute_opcode at 0x48C010 now
contains 107 effective values / 78 primary heads. Eleven added paths are 529,
530, 538, 540, 541, 542, 550, 552, 570, 571 and 574. They do not establish
partial exactness or production source acceptance for the dispatcher. Its native
prologue, default, other cases, complete tables/EH and compiler extent remain open.

Five complete dependencies are maintained in EnemyScriptAdvance.cpp and
EclSelection.cpp, with declarations on the actual existing owners:

| Native entry | Bytes | Maintained function |
| --- | ---: | --- |
| 0x4AA9E0 | 36 | EnemyState::integer_argument_destination |
| 0x4AA980 | 36 | EnemyState::float_argument_destination |
| 0x4AAA10 | 36 | Enemy::integer_argument_destination |
| 0x4AA9B0 | 36 | Enemy::float_argument_destination |
| 0x49CC30 | 38 | EclManager::subtract_time |

All five complete functions strictly replay, totaling 182 comparison bytes.
Original source names and authored/compiler origins remain unknown. The final
function is placed on the genuine EclManager base; native field access alone
does not distinguish original base versus derived source qualification. There
is no new owner facade, source profile branch, padding or target-sized prefix.

## Native observations and corroboration

The complete attested root listing and four independently reconciled nested
tables establish the rank paths. Opcodes 529/530 select from four values;
570/571 select from eight. The selector is state+0x50, read before the operand.
Negative and unsigned out-of-range selectors use the last value. The last
listed rank shares that same final branch. The private source retains explicit
nested switches rather than replacing native control flow with an indexed read.

Integer paths evaluate one selected argument, then resolve destination argument
0 and store its complete word. Float paths do the analogous binary32 copy.
Destination resolution reloads state.entity after the value read, then loads
that Enemy's current_runtime. Both 36-byte layers use actual receiver fields
and forward the signed argument index unchanged to the canonical Runtime
destination methods. These are separate from Enemy's virtual destination methods,
which receive an already decoded negative register selector. Substituting the
virtual interface at the outer layer would skip instruction/local-stack decoding.

Opcode 538 replaces word04 bit11 from argument0 bit0; 552 replaces bit3.
Opcode 540 replaces bit12, reads argument1 into field54, copies the then-current
field28 to field58, clears word04 bit13 and clears word00 bit0, in that order.
Failure of argument1 therefore retains the earlier flag update. No later stores
are moved ahead of operand evaluation.

Opcode 541 copies float argument0 into the established process ClockScalar at
0x5AEFE4. It adds no clamp. Opcode 550 borrows the name at instruction+20,
obtains the actual Enemy loader, performs its existing sorted-name lookup and
writes only state.field27C. It does not select or reset a running script.

Opcode 542 reads all four integer operands, caches state.entity, then queries
Session::mode in its observed conditional sequence. Modes 0/1/2 select the first
three values; every other mode selects the fourth. Conversion to binary32
precedes subtraction from the selected Enemy's current Runtime time. Opcode 574
performs the same complete time operation with 1.0f only when word08 bit6 is
clear, without an operand read. This is not a Timer or health update.

The new bounded Ghidra export confirms the complete inner destination wrappers
and time operation. Ghidra reports no ordinary callers for 0x49CC30 because
its inferred root membership is incomplete; the full listing/PE audit retains
the root's direct call sites. Existing canonical Runtime/loader/clock bodies
independently corroborate the receiver chain and native operation.

## Semantic and compiler verification

The expanded O2/UBSan whole-draft fixture passes 26,781 scenarios: 19,350 prior
cases, 7,200 rank cases and 231 flag/time/name cases. Actual new forwarding,
Runtime destination decoding, stack-local storage, loader construction/lookup,
ClockScalar and time subtraction run. Rank tests cover invalid signed selectors,
integer extremes and arbitrary copied float words, main/alternate runtimes,
owner changes during value reads and operand/destination exceptions. Full
state/frame images and stack values detect unintended writes. Time and flag
tests cover partial writes before failure, selected receivers and borrowed names.

Destinations are valid and nonnull, stack offsets are in range, loaded records
are valid and names are sorted, terminated strings. Resource/startup, whole
defeat and other unresolved native boundaries remain explicit fixture captures.
These tests do not establish native game startup, rendering or full execution.

The three changed headers and two implementations select 29 providers / 162
previous units from captured includes. Each provider is freshly built once and
all 162 units strictly replay; 135 unaffected providers reuse their valid evidence.
Four generated literal renames preserve complete data and existing relocation
roles. Thirty complete EH code/data sections for fifteen affected parents are
unchanged, including all relocations and relative function labels, so their
independent bindings are reused. Five new units pass complete canonical replay.
No unfiltered replay or full CI runs. Cleanup adds no builds or replay.

## Protected evidence and remaining work

Private paths are relative to `.analysis/`:

- `core158-enemy-dispatch-candidate.cpp`, `core158-draft-scope.json`
- `core158-dispatch-host.cpp`, `core158-rank-host-cases.inc`, `core158-dispatch-host-recipe.json`, `core158-dispatch-host-v3.log`
- `core158-missing-state-native.asm`, `core158-destination-native.asm`, `core158-helper-callers.txt`
- `core158-production-diagnostic.json`, `core158-independent-bindings.json`, `core158-eh-reuse.py`, `core158-eh-evidence-reuse.json`
- `core158-cold-proof.json`, `core158-affected-results.json.gz`, `core158-new-exact-results.json.gz`
- `core158-pre-rank-inputs.json.gz`, `core158-pre-registration-ledgers.json.gz`
- `core158-enemy-current-dependencies.json`, `core158-graph-audit.json`, `core158-retirement-plan.json`, `core158-cleanup.json`

The unchanged complete root has 1,264 direct sites / 236 dependencies. The
current navigation audit finds 124 canonical entry targets covering 843 sites;
these are dependency counts, not root completion or partial byte credit.

Seventeen nondefault 500..575 paths remain: 502/503, 516..519, 524, 527, 534,
539, 548/549, 551, 553..555 and 575. Opcode 569 uses the normal default.
Actual HUD, Stage, audio, animation and other receiver protocols still need
reconciliation. In particular, 502/503 call animation flag wrappers whose failed
lookup preserves the old handle. Existing AnimationHandle::resolve clears failed
handles and is therefore not an interchangeable shortcut. Preserve the genuine
Renderer boundary and continue the whole root under
[dispatcher evidence](CORE_ENEMY_DISPATCH_LAYOUT.md).
