# Enemy frame, movement, spawn and variable review

Batch counts and open-work statements describe the checkpoint documented here.
For present acceptance and remaining work, read the [current handoff](RE_HANDOFF.md).

## REF-038 — 2026-10-07

All **236** scoped reference implementations were individually read, including
nested lambdas and fixture endpoints. The batch covers 23 indexed files:
`enemy_frame` and its tests, `enemy_update`, `enemy_movement`,
`enemy_interpolation`, `enemy_spawn` and CPU cases, `enemy_variables`,
`enemy_reads` and CPU cases, the common opcode reader, movement opcode sources,
adapters and CPU cases, lifecycle/game services, and resource tests. Relevant
zero-definition type headers and the existing recipe/report evidence were also
read. Original CRLF body hashes and the pinned reference commit remain intact.

New decisions are **1 absorbed / 36 nonexact / 199 support**. The previously
reviewed `EnemyMovementRecord` constructor is independently revisited and upgraded
from nonexact to absorbed; it is not counted as another new review. Two missing
`type_identifier` nodes on line25 of `enemy_opcode_movement.cpp` are its default
`Vec3{}` arguments, both contained in the complete indexed `position_curve`
implementation. The entire file is manually reconciled without modifying it.

Global coverage is **5,547 terminal / 1,397 pending** of 6,944 implementations;
parser-gap files are **84 complete / 29 pending**. Gameplay has **553 pending**.
Each body retains its own hash and implementation-specific decision in
`config/reference-function-reviews.csv`. This closes this batch's review, not
all Gameplay behavior or the exhaustive repository goal.

## Independently rewritten complete values

| Natural maintained member | Original address | Complete bytes |
| --- | --- | ---: |
| `EnemySpawn::EnemySpawn` | `0x0047BB30` | 95 |
| `EnemyMotionInterpolation::EnemyMotionInterpolation` | `0x0048B270` | 123 |
| `EnemyMovement::EnemyMovement` | `0x0048B550` | 90 |
| `Vector2Interpolation::Interpolation` | `0x00447AC0` | 97 |

All four native routines fully decode through their sole final `RET`, with no
branches, hidden tails or truncated contributions. Original call operands were
read before probing and supply the canonical anchors. They add **405 disjoint
bytes**. All **166 canonical units / 48 cold objects / 11,559 complete bytes**
replay with zero differences against the locked Steamless target and frozen
maintained source. These four origins remain unknown; source presence is166,
pending origins105, library4, confirmed authored57 of4,074 unchanged. No
unknown-origin match is promoted into the authored ledger.

The 84-byte spawn value constructs a real `Vector3`, scalar words, a flags value,
`EnemyCounters` at20 (four integer words and eight floats), and a four-byte value
subobject at50. The reference's twelve-integer variable block and whole-record
`memset` lose those native child constructors. Original4A89C0 copies21 words,
uses mask1C bit0 for viewport-relative movement and copies50 to Enemy8C;
49ABC0 reads that destination through an unsigned four-byte accessor. Its original
tag and semantic role are unknown. `Identifier32` is an explicit provisional
value type, not an inferred AnimationHandle: a shared zero constructor at425CC0
proves no unique source tag. That dependency receives no second standalone
canonical unit or extra address credit.

Enemy movement's 100-byte position interpolation puts current first, followed
by start/end/two tangents, Timer3C, duration4C, three axis modes50/54/58, shared
mode5C and flags60. Native4A8D70 selects shared versus per-axis mode using bit0,
corroborating the actual field roles. This differs from the existing84-byte ANM
`VectorInterpolation`; no padded facade or conditional matching body is used.
The 388-byte movement value contains Motion0, position48, scalar curvesAC/D8
and64-byte two-lane curves104/144. Its original six child calls establish that
partition. The two-lane curve uses the unchanged generic `Interpolation<T>`
body, five Vector2 constructors4398A0 and Timer422D90. Other newly emitted
template members have no additional exact credit.

Portable C++20/UBSan checks construct all four values in dirty, guarded storage,
verify every initialized byte and preserved adjacent bytes, and reset dirty
integer/float representations in the embedded variable block while preserving
all other spawn fields. These tests supply no implementation of the unrecovered
Enemy frame, VM, allocator, animation or resource owners.

## Production and behavioral boundaries

Eleven actual reference production TUs were rebuilt after the final maintained
source freeze. Gameplay sources retain their reviewed `/fp:strict` recipe;
entry adapters retain `/fp:precise`. Full defined COFF symbol inventories include
static functions. Diagnostic comparisons use complete contribution sizes and
never slice prefixes. The inventory has560 defined functions, including189
static;37 complete comparisons across36 mapped bodies all differ in length,
with no structural match.
All older unrelated reference receipts require rebuilding before reuse.

The frame controller preserves countdown/HUD/order and full integer1 return;
4A5300's `MOV EAX,1` corrects Ghidra's inferred void result. Source retirement
explicitly clears the observer's current link before freeing, a deliberate
improvement rather than original full-body equivalence. HUD saturation tests
seconds for both fields, including negative values. Slowdown uses
`!(scale <= 0)`, so NaN enters the slowed branch; shared clock restoration,
stale handle clearing and persistent bit16 remain documented. Extra Services,
raw-pointer free helpers and genuine primary/HUD/ANM owners prevent exactness.

Movement updates scalarAC/D8 and vector104; the second vector144 is initialized
and populated by opcodes but not sampled in ordinary movement. Parent following,
position aggregation, ordered bounds, direction transition script/layer mapping,
file lookup before deletion/spawn and absolute dimensions are preserved in the
source. Original whole-owner/PMR/prototype/global-clock/ANM allocation protocols
remain unresolved. Script/state updates retain bit4/bit26 gates and early-failure
ordering; historical CPU coverage uses already-moved/no-damage/no-mesh domains,
while source-order fixtures record those bodies.

The movement handler covers400..448 with missing-position sentinels, shared and
per-axis curves, mirrored angles, durations, random/player targeting, record
collapse and retained interpolation current. It is an optional-result Reader/
Services extraction from the whole48C010 dispatcher/table, not an independent
native opcode-case function. RAII MotionEditor commits even on exceptions;
checked vector access and required-target exceptions are outside native exact
acceptance. Generic interpolation sampling still bridges different source
representations and return/clock protocols.

Variable selection always resolves through player0's controller. Nearest search
uses strict radius, preserves the first tie, excludes unordered distances, and
destroys the observer before reading the selected identifier. Integer and float
getters share a tagged source query, unlike separate native49ABC0/4995D0 members.
Checked indices, explicit environment, unsigned conversions, mutating PlayerTable
clamps, RNG and repeated lookup remain individual observations. Native integer
null915/916 dereferences are excluded; floating defaults are tested. Four script
globals5C49D8..E4 remain distinct from Enemy generator globals5C49EC/F0.

Virtual production services bind actual shared owners and required dependencies,
but add source vtables/RTTI/static lifetimes and different prototypes. Address-
named bridges do not close original functions. Reviewing these endpoints does not
review their pending Damage/Mesh/Defeat/opcode dependencies. `damage_source_cases`
included by the frame driver likewise retains its own pending implementation
reviews. No copied reference implementation is published; its license is absent.

## Retained reports and limits

No Windows CPU oracle, frame/resource executable or report writer was executed.
Historical CPU report1,254,134/0 and frame report7,682 assertions bind all105
current source hashes each. They do not bind the executed executable/compiler/
startup/includes to a fresh build, and do not establish whole-game equivalence.

The movement CPU fixture reports **94,080 groups**:49 opcodes times640 scenarios
for full1064-byte Enemy, all388-byte movement payloads/return, and RNG28. It uses
real PMR records, four prepared records, finite coordinates/rates, negative and
positive durations, all34 modes and explicit sentinels/valid required targets.
The host angle4297D0 and integer497470 call original RNG endpoints; this is not
independent validation of a source RNG implementation.

Getter CPU coverage reports **88,666 groups** (44,216 integer / 44,450 float)
across350 seeded scenarios and119 variables. It compares raw results, complete
PlayerTable clamp side effects and RNG on prepared real Enemies/controllers/
players/ANM storage. Integer null915/916, invalid indices and unpopulated/nonfinite
objects are excluded. Spawn fixtures include5,000 dirty84-byte constructions,
800 whole Enemy constructors,500 initialized owners and1,600 applications with
explicit pointer/vptr/capacity normalization and recorded core-update gates.

The source frame test uses real destruction followed by `PAGE_NOACCESS` while
keeping addresses reserved:512 deletion/nested-query masks plus clear_entities,
14 slowdown edges,256 failure/gate patterns and30 direction transitions.
This differs from the retained20 CPU observer-hazard cases that keep retired
storage accessible and poison it. Neither fixture establishes full native frames.

Resource report3,304 assertions/stage1..7 counts has **100 of105 current source
hashes**. Five are stale: `enemy.cpp`, `enemy_frame.cpp`, `enemy_cpu_compare.cpp`,
`enemy_resource_tests.cpp`, `enemy_frame_tests.cpp`. Its assertion total is only
historical evidence, not validation of current files. The current reviewed
resource source checks real encrypted archive/SCPT cache/include ordering,
shared writable instruction aliasing, two-player callback/lifetime behavior and
file unloads; GPU allocation is recorded and simulation/drawing explicitly throw.
No fresh resource result is inferred.

Private evidence: `ref038-inventory/files/bodies/decisions`, native value and
callee/consumer Ghidra reads, `ref038-native-audit`, historical report hash audit,
all actual production COFF symbols/complete diagnostics, full canonical cold
replay and portable semantic checks. The one-shot registration writer executed
successfully and must never be rerun. Continue the553 pending Gameplay bodies,
then Sprite540/StageBackground121 and183 other implementations, preserving
individual decisions for every remaining body and grammar file.
