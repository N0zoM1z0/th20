# CORE205: three complete queued-parameter heads in the entire Enemy boss root

The locked TH20 Japanese v1.00a Steamless executable has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This work extends **one same complete 41,967-byte native
`EnemyState::execute_opcode` root** at `0x0048C010`. Three further original
primary opcode heads have been reconstructed as natural *semantic* source;
none is a fabricated standalone native function, and neither the new heads
nor the entire root are claimed machine-code byte-exact.

## Independently recovered original code boundaries

Original PE instructions, 43/43/51 complete x86 instruction heads, all
direct-call targets and the original normal exit jump were independently
checked against the separate complete native case-path catalog:

| Opcode | Complete original interval (end exclusive) | Native bytes | Instructions | Direct calls |
| --- | --- | ---: | ---: | ---: |
| **602** | `0x00492A54..0x00492B09` | **181** | 43 | 8 |
| **603** | `0x00492B09..0x00492BC6` | **189** | 43 | 8 |
| **604** | `0x00492E47..0x00492F1C` | **213** | 51 | 10 |

Each starts by calling the original ECL `integer_argument(0)` and the
**genuine native-byte-exact 305-byte `EnemyState::shared_shot`** at
`0x00498D10`, accessing the actual raw record/metadata pointer pair. They
**never call the 396-byte writable COW selector**. Existing shared
`EtamaArgInf` ownership persists without cloning, while null metadata is
allocated through its authentic `DebugAllocator`, and the real PMR queue
extends if necessary.

The three functions then make two distinct, independently ordered ECL
argument reads each:

- 602 reads `integer_argument(1)` and writes all 32 bits to selected
  `EnemyQueuedRecord::parameters.type` at record offset `+0x8`; then reads
  `integer_argument(2)` and writes `ShotParameters::color` at `+0xC`.
- 603 reads `float_argument(1)` then `(2)` and writes raw IEEE-754 bits to
  `EnemyQueuedRecord::vector_34.x/y` at `+0x34/+0x38`, *preserving*
  `vector_34.z` and all existing shot type/color fields.
- 604 reads `float_argument(1)`, calls the genuine native-bound
  `normalize_angle` at `0x00438540` and stores the resulting value into
  `ShotParameters::angle` at record offset `+0x1C`. It then independently
  reads and normalizes `float_argument(2)` into `angle_step` at `+0x20`.
  It does not combine the two angles or defer the first write until the
  second operand succeeds.

No other VM operands are read, and a later throwing read does **not** undo
previously completed record writes or the queue/metadata selection. The
entire instruction transcripts and hash-grounded call sites are preserved
as `.analysis/core205-native-op602.asm`, `core205-native-op603.asm`,
`core205-native-op604.asm` and in the locked-native audit
`.analysis/core205-native-602-604-audit.json`.

## One complete-root implementation and genuine-owner tests

The actual active private root source draft is
`.analysis/core205-enemy-dispatch-candidate.cpp`. The new cases coexist with
all previous 539/555, 600/601, 609–612, 700–703, 711/713 and other
completed native case families in the **same**
`enemy_draft::exercise_dispatch_candidate` function. The genuinely exact
`EnemyState::shared_shot` from maintained
`src/EnemyQueuedSelection.cpp` runs unmodified; no fake COW/ensure
implementation or null-owner fixture replaces it.

`.analysis/core205-queued-602-604-host-cases.inc` adds **483 new cases**:
**152** successful type/color raw integer updates, **152** successful
floating vector updates and **152** two-stage angle normalizations, plus
**27 staged ECL operand exceptions**. They exercise 120 genuine
shared-owner aliases that remain intact, 216 new metadata allocations,
96 real forward-list expansions, signed-zero/infinity/quiet-NaN float
representations, raw negative/positive integer bits, and exact earlier
write preservation for failed operand 0, 1 or 2. The complete 752-byte
nonqueue `EnemyState` image remains unchanged, except the real queued
container header when actual growth occurs.

The full **85-source-unit** GCC13 entire-root host passes
**43,922/43,922** cases in *both* `-O2 -Wall -Wextra -Werror` UBSan
and ASan+UBSan configurations: all previous **43,439** cases plus 483
new ones. Only the unrelated unavailable `WeaponStoneInfo` vptr
instrumentation is disabled; ASan leak detection is enabled. Full logs,
SHA-bound active sources/recipe and both full host binaries are protected
in `.analysis/core205-enemy-whole-root-proof.json`,
`.analysis/core205-dispatch-host.log`, and
`.analysis/core205-dispatch-host-asan.log`. All earlier CORE204/203/202
and historical native source/object/test proofs remain intact.

## Native exactness and scoped cold-build limits

CORE205 modifies **zero maintained production source/header/compiler
inputs**, so **no canonical native cold builds/replays** were required in
this semantic-only checkpoint, and **no full cold replay** was run. The
TH20 exact ledger remains **225 authored exact whole functions /
58,718 native instruction bytes**, including the previously accepted
26-byte `BulletController` scalar setter and real 305/396-byte queued
selectors. The draft now covers **139 effective opcode values / 107
original native primary heads of 174**, not all native switch cases or EH.
The original **41,967-byte Enemy boss root is still nonexact**.

A large adjacent high-value next native branch is the complete **572-byte
opcode 614** at `0x004925C7..0x00492803`, with independently recorded
iterator/queue resize and command-retirement calls. The other major
339-byte BulletController shot emission at `0x00481780`, its larger spawn
loop and the actual whole-root C++/MSVC jump/EH partition also remain open.
