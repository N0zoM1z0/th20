# Enemy dispatcher movement source frontier

## CORE/EXACT-145 scope

The complete EnemyState::execute_opcode root at 0x0048C010 remains undefined in
production. Its 41,967-byte body and associated tables require whole-function
acceptance; neither the 49 movement opcode values nor their 24 shared primary
heads receive partial exact credit. See [complete layout](CORE_ENEMY_DISPATCH_LAYOUT.md).

A private, handwritten semantic candidate now covers opcode values 400 through
448 using the actual EnemyState, EnemyMovement, Motion and interpolation owners.
It exercises the source construction frontier of the complete root. Its host
entry and three factoring helpers are provisional; they are not original
functions, accepted translation-unit boundaries or production replacements.

One required dependency is accepted separately: the complete 94-byte
GameRandom::next_word body at 0x00497470. The graph now contains 897 physical
units / 164 objects / 168,151 disjoint comparison bytes and 905 source mappings.
Its original authored/compiler/library provenance remains pending, so authored
exact coverage stays 181 functions / 47,071 bytes.

## Raw random-word protocol

The native word sampler acquires the actual recursive mutex in slot 10,
unconditionally advances the 32-bit engine, stores its complete output in
GameRandom::last and returns the low 16 bits. It performs no modulus division.
In contrast, next returns last modulo modulus. Zero modulus is valid for word
sampling and remains invalid for next. Both retain their real shared owner and
lock protocol.

Native opcode 412/413 paths use the existing ECL stream at 0x005BA4A8. Their
integer choice calls 0x00497470 and zero-extends AX before signed division by 3.
An earlier private candidate used next followed by a word mask. Seeded tests
with modulus 0x7FFFFFFF did not distinguish that substitution; native callee
review exposed the difference. The current candidate calls next_word and also
checks nondefault moduli. Preserve the rejected candidate and original inputs.

GameRandomStream.cpp owns the natural implementation under its unchanged
C++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc /Gd /sdl profile.
Its fresh complete COFF contribution is 94 bytes, including the sole return;
there is no omitted table or shortened prefix. Seven relocations reuse prior
next/seed identities for the cookie, lock registry/slot, guard lifetime and
engine call. No destination is solved from the compared field. Original method
spelling is inferred; the observed producer/consumer widths support the public
uint16 result contract.

Before the shared declaration changed, all 164 original object/receipt pairs
and their authentic input versions were preserved. Captured include closures
select 35 providers / 153 prior units. Each provider is freshly built once;
all 153 units strictly replay and 129 providers are reused. Eight compiler string
labels change. Their complete original/fresh literal bytes are identical and
their targets/addends are preserved by relocation role, without global renaming.

## Native movement constraints retained in the draft

| Protocol | Native observation |
| --- | --- |
| Selection and growth | Most primary variants select field_44; paired variants use index 1. Opcodes 414/418/432 use fixed index 0. Storage grows before operand reads. |
| Position interpolation | current remains unchanged. Shared-mode setup clears flags bit 0; per-axis setup sets it and writes only the requested axis modes. Tangents, start/end, duration and timer are distinct writes. |
| Scalar interpolation | Angle/speed begin operations replace current; the manually configured orbit curves retain current. Nonpositive duration stops the corresponding curves without changing motion mode. |
| Relative endpoints | Relative coordinate arithmetic precedes the missing-value fallback. Mirroring affects the selected native opcode families, not every angle/position operation. |
| Opcode 412/413 | Duration is read separately for the two curves. The second mode call still addresses the angular curve, leaving the speed curve's mode unchanged. |
| Opcode 427 | The loop uses a signed comparison with size minus 1, then retains one record and clears its position/vector while selecting linear mode. Discarded native access calls remain unexplained emission evidence. |

Bounded attested helper exports corroborate the established storage: Enemy
position interpolation uses start/end at +0C/+18, tangents at +24/+30, timer at
+3C, duration at +4C, axis modes at +50, shared mode at +5C and flags at +60.
The shared-mode helper clears only flags bit 0 and returns its input. The axis
helper sets only that bit, writes the indexed mode and returns its value.
Vector2 interpolation uses timer +28 and duration/mode +38/+3C; Float uses
timer +14. No owner layout or field width changes in this batch.

The missing-coordinate threshold is an independently read double -999999.0.
The negative vertical-angle exclusion uses float 0.05, whereas the positive
comparison uses double 0.05. Preserve those distinctions during whole-root
emission work. Do not add unconsumed getters or inert operations to imitate the
discarded calls in opcode 427.

## Checks and remaining integration

The O2/UBSan host fixture passes 459 scenarios across all 49 values, mirrored
and ordinary state, positive/zero durations, mode 7, changing repeated duration
reads, retained interpolation channels, a zero-record 427 input and genuine
Player/Enemy storage. Independent E8/PUSH evidence supplies operand-read order.
Central player-position cases check both player sides and three moduli using an
independent integer LCG model, raw second-word choice and resulting angle.
The actual controller find and Context player provider run; selected-slot lookup,
ECL operand reads, resource-absent retirement and unresolved startup/lifetimes
remain explicit captures. This is host corroboration, not native execution.
The fixture domain uses finite operands, small representable vector lengths and
live targets. Allocation failure and NaN behavior remain outside these checks.

The public random fixture additionally checks 7,200 raw-word transitions over
six seed boundaries and four moduli, including zero, plus slot-10 exclusion and
release while tracked locking is disabled.

Extend the same whole-root source work to the remaining opcode families. Resolve
actual member-call boundaries for the provisional helpers, remaining typed
interfaces, default behavior, EH and complete table/tail ownership before
production admission. The private exercise's unsupported-opcode exception must
never replace the native default return. Whole-game 95% exactness and playable
integration remain unachieved.

Private evidence lives under `.analysis/`: `core145-enemy-movement-candidate.cpp`,
`core145-movement-host.cpp`, the v7 recipe/build log, native movement read-order
JSON, configuration/remaining/accessor exports, `core145-word-strict.json`,
`core145-affected-results.json.gz` and literal-role reconciliation. Original
inputs are preserved in `core145-pre-header-inputs.json.gz` and
`core145-host-original-inputs.json.gz`. The refreshed complete root dependency
inventory is `core145-enemy-current-dependencies.json` (91 canonical entry targets
/ 751 of 1,264 call sites); those navigation counts do not measure root completion.
