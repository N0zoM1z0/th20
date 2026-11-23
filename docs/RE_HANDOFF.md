# TH20 reconstruction — current handoff

## Start here

1. Read [repository rules](../AGENTS.md) before changing code or deleting artifacts.
2. Use this file for the current state and immediate next action.
3. Use the [open Boss backlog](RE_OPEN_BOSS_BACKLOG.md) for the wider priority map.
4. Use the [Enemy dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md) for the maintained 41,967B root.
5. Use the [evidence index](EVIDENCE_INDEX.md) to find detailed native investigations and exact proofs.
6. Target/compiler/oracle rules live in [target provenance](TARGET_PROVENANCE.md), [workflow](RE_WORKFLOW.md), [oracles](ORACLES.md) and [tools](TOOLS.md).

## Locked target and authoritative status

The target is resources/th20.exe, the Japanese TH20 1.00a Steamless executable:
- Size: **1,858,560 bytes**
- SHA-256: a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897
- Registry/package identity is v1.00a. Embedded title/replay strings say 1.00c in this same file; see [provenance](TARGET_PROVENANCE.md).
- A complete playable game has **not** yet been built, linked or runtime-validated.

The canonical status is in config/matches.csv, config/match-units.toml,
config/functions.csv and config/function-origins.csv. The ledger-derived
summary checked on 2026-11-22 is:

| Measure | Current value |
| --- | ---: |
| Provisional candidates | 6,929 |
| Review / authored / excluded | 5,868 / 975 / 86 |
| Mapped functions | 1,812 |
| Source-present functions | 1,798 |
| Exact functions | 955 |
| Exact original bytes | 298,898 |
| Manifest units | 1,790 |

Use scripts/repo-python scripts/report-reconstruction-status.py --summary
for a fresh count. These are ledger totals, not a claim that the full game is
complete.

## Latest checkpoints — Enemy ECL opcodes 616, 617, 618, 619, 620, 627/628, 629/630, 632 and 633

Enemy ECL opcodes 616, 617, 618, 619, 620, 627, 628, 629, 630, 632 and 633 are now integrated into the
maintained root host and focused verifiers. Their production/test/verifier
changes are checkpointed and retained:

- `src/EnemyStatePlayerAngleOpcode.cpp`
- `src/EnemyStateSharedQueuedParametersOpcode.cpp`
- `src/EnemyStateQueuedParametersOpcode.cpp`
- `src/EnemyStateScriptPointerOpcode.cpp`
- `src/EnemyStateBulletLaserCancelOpcode.cpp`
- `src/BulletLimitedCancellation.cpp`
- `src/EnemyStateBulletClearOpcode.cpp`
- `src/EnemyStateScorePopupOpcode.cpp`
- `src/BulletTimer4D8.cpp`
- `src/SessionScore.cpp`
- `tests/enemy_state_dispatch_root.cpp`
- `scripts/verify-enemy-bullet-laser-cancel-opcode-source.py`
- `scripts/verify-enemy-player-angle-opcode-source.py`
- `scripts/verify-enemy-shared-queued-opcode-source.py`
- `scripts/verify-enemy-shared-queued-polar-opcode-source.py`

Native opcode 616 is the **175-byte / 37-instruction / 7-E8** case at
`0x004954D1`, selector index 134. It reads radius operand 0, then executes
the real 320B BulletController::cancel_near Boss using the current Context
and live Enemy position reference. After that traversal it re-reads Context
and position and executes the real 288B LaserController::cancel_near Boss.
The root host verifies live position aliasing during Bullet traversal, Context
retargeting between phases, Bullet/Laser state filters, virtual circle-cancel
arguments and radius exception-before-side-effects. Bullet::cancel and the
concrete Laser::cancel_circle child remain explicit test capture boundaries.
See [the opcode-616 source frontier](ENEMY_41967_616_BULLET_LASER_RADIAL_CANCEL_SOURCE_FRONTIER.md).

Native opcode 617 is the **203-byte / 41-instruction / 8-E8** case at
`0x004958C3`, selector index 135. It reads the live Context Player position,
subtracts VM float operands 1/2 in X-then-Y order, calls the existing
`scalar_math::arctangent(dy, dx)`, and writes float destination 0. Context is
re-read between operands, and the root host tests retargeting with two real
Player objects, direct atan2(0,0)==0 semantics, and second-operand exception
preservation. See [the opcode-617 source frontier](ENEMY_41967_617_PLAYER_ANGLE_SOURCE_FRONTIER.md).

Native opcode 618 is the **243-byte / 55-instruction / 10-E8** case at
`0x00492BC6`, selector index 136. Its natural C++ source reads the integer
selector and both float operands before the real ensure-only `shared_shot`,
then extracts the pair, constructs a temporary `Vector3`, calls the existing
`polar` leaf and writes only queued-record vector_34 XY. The root host tests
second-float exception before queue growth, shared-owner stability, Z and
vector_40 preservation. See [the opcode-618 source frontier](ENEMY_41967_618_SHARED_QUEUED_POLAR_SOURCE_FRONTIER.md).

Native opcode 620 is the **250-byte / 57-instruction / 8-E8** case at
`0x00492D4D`, selector index 138. Its natural C++ source uses the real
ensure-only `shared_shot` path and pair `std::get` extraction, writes the
queued record's `vector_40.x/y/z`, preserves the `-990.0f` threshold and
`1.0f` constant, and matches the original `COMISS/JBE` NaN behavior. The root
test checks shared metadata ownership, threshold boundary, NaN, and the
second-operand exception after the X write.

Native opcode 619 is the 148-byte / 35-instruction / 7-E8 writable queued
metadata update at 0x00492CB9, selector index 137. It calls the real
writable_shot COW selector, extracts both pair members in native order, then
reads float operand 1 and writes ShotMetadata::field_00, consumed as the
Bullet/Laser radial offset. The root host proves COW precedes the float read:
a float exception preserves the clone but leaves the metadata field unchanged.
See the opcode-619 source frontier
(ENEMY_41967_619_WRITABLE_METADATA_RADIAL_OFFSET_SOURCE_FRONTIER.md).

Native opcode 629 is the **46-byte / 10-instruction** callback-table branch
at `0x00490B4D`, selector index 147. Its native table at `0x0056FE8C` selects
the 768B animation-rectangle Bullet callback or the 291B all-Bullet reset
callback. Both complete callbacks are now natural C++ `EnemyState` members,
with real AnimationHandle resolution, rotated `geometry::rectangle_circle`,
active Bullet iterator, Bullet Timer/color/field setters, Context/Player
position reads and Player movement-scale writeback. The original 6.0f and
10.0f globals are mapped; root tests exercise both callbacks, no state/field
filter, overlap/no-overlap and exception ordering. See
[the opcode-629 callback frontier](ENEMY_41967_629_BULLET_CLEAR_CALLBACK_SOURCE_FRONTIER.md).

Native opcode 630 is the **109-byte / 24-instruction / 5-E8** score-popup
branch at `0x0048C24A`, selector index 148. It uses real Session score
accounting, the Context +0x1C ItemRewardPopupQueue owner, live Enemy position
and the strict-exact 255B popup enqueue Boss. Root tests cover queue payload,
score, Context retargeting and operand exception-before-side-effects. See
[the opcode-630 source frontier](ENEMY_41967_630_SCORE_POPUP_SOURCE_FRONTIER.md).

`Bullet::set_timer_4d8` is now a separate **39-byte strict-exact** leaf at
`0x0049CAE0`: all 35 non-relocation bytes match and the single REL32 at
`+0x1C` targets exact `Timer::operator=(float)` at `0x0047C5F0`. See
[BULLET_TIMER_4D8_SETTER_EXACT.md](BULLET_TIMER_4D8_SETTER_EXACT.md).

Native opcode 633 is the 163-byte / 41-instruction / 6-E8 queued-record
decrement at 0x0049378E, selector index 151. It retains writable_shot and
both ordered pair extractions, performs wrapping uint32 decrement of record
field_30, then clamps a signed-negative result to zero. Boundary and
selector-exception tests cover both arithmetic and COW side effects.
See the opcode-633 source frontier
(ENEMY_41967_633_WRITABLE_QUEUED_RECORD_DECREMENT_SOURCE_FRONTIER.md).

Native opcode 632 is the **252-byte / 62-instruction / 10-E8** borrowed
BulletCommand script-pointer case at 0x00493831, selector index 150. Both
integer indexes are read before writable metadata COW, pair extraction and
PMR command-vector size/resize/index. The stored pointer is the original
EclInstruction + 0x1c trailing payload address; no string is copied. The
root host verifies COW, vector growth, pointer identity and second-index
exception-before-side-effects. See
[the opcode-632 source frontier](ENEMY_41967_632_BORROWED_SCRIPT_POINTER_SOURCE_FRONTIER.md).

Native opcodes 627 and 628 are each **182-byte / 39-instruction / 7-E8**
paired capped Bullet/Laser radial-cancellation cases at 0x00495580 and
0x00495636, selector indexes 145/146. They call the real 401B
BulletController::cancel_near_limited Boss with mode 0, limit 99,999 and
effects 0, then re-read Context/position and call the real 288B
LaserController::cancel_near Boss with mode 0 / argument 1. The root host
tests real intrusive traversal, state/field filters, effect-bit reset,
Context/position retargeting and radius exception ordering. See
[the opcode-627/628 source frontier](ENEMY_41967_627_628_CAPPED_RADIAL_CANCEL_SOURCE_FRONTIER.md).

The false-returning root-test stubs for the shared, writable queued-parameter
and script-pointer helpers are removed. The production helpers are included
in HOST_SOURCES and the locked-profile COFF compile list; their native opcode
verifiers are invoked by the maintained root verifier. The focused root host
passes under ASan/UBSan, and the root verifier compiles **58 locked-profile
i386 COFF source units** and 124 focused host sources. See the dedicated
[opcode-620 source frontier](ENEMY_41967_620_SHARED_QUEUED_VECTOR_SOURCE_FRONTIER.md).

This is still an inline fragment only. No standalone function unit or
strict exact-byte claim is created, and the 41,967-byte parent remains
**NONEXACT**. No full cold replay was run.

## Active Boss — EnemyState::execute_opcode

The main target is the original **41,967-byte** EnemyState::execute_opcode
at 0x0048C010. It now has a substantial partial natural-C++ root and
focused ASan/UBSan host, but the complete parent remains **NONEXACT**. No
whole-parent byte credit is claimed.

Recent committed case families exercised by the maintained root include:

- **609/610/611/612:** shared 1,457B shot-command branch; real writable-shot
  COW selector and PMR BulletCommand vector.
- **614:** 572B queued-record copy; real PMR forward-list and exact 119B record
  assignment.
- **616:** 175B paired Bullet/Laser radial cancellation; real 320B and
  288B controller cancellation Bosses, live Context/position retargeting,
  state filtering, virtual dispatch capture and radius exception ordering.
- **617:** 203B Player-relative angle; two live Context/Player position reads,
  existing atan2 leaf, destination writeback, Context-retarget semantics and
  second-operand exception coverage.
- **618:** 243B shared queued-polar update; real ensure-only shared record,
  pair extraction, temporary Vector3 and existing polar leaf; XY-only writes
  with Z/vector_40 preservation and second-float exception ordering.
- **620:** 250B shared queued-vector update; real ensure-only shared record,
  pair extraction, ordered X/Y writes, native `COMISS/JBE` NaN behavior and
  second-operand exception coverage.
- **619:** 148B writable queued-metadata radial-offset update; real COW selector,
  ordered pair extraction, COW-before-float and exception-after-clone coverage.
- **633:** 163B writable queued-record decrement; real COW selector, ordered pair
  extraction, uint32 wrap/signed high-bit clamp and selector-exception coverage.
- **632:** 252B borrowed script pointer; both indexes before COW, real PMR command
  growth and exact EclInstruction+0x1C pointer identity, plus second-index exception.
- **627/628:** two 182B capped Bullet/Laser cancellation branches; real 401B limited
  Bullet and 288B Laser Bosses, 99,999 cap/effects arguments and live Context retargeting.
- **629:** 46B callback-table case plus 768B and 291B native callback Bosses;
  real AnimationHandle/geometry/Bullet iterator/Timer/color/Player paths and both
  callback modes execute under ASan/UBSan.
- **630:** 109B score-popup case; real Session score, Context +0x1C popup queue,
  live Enemy position and strict-exact 255B enqueue Boss.
- **621:** 346B mesh-owner lifecycle; real allocator templates and
  EnemyMeshOwner destructor. Renderer-dependent RenderMesh ctor/dtor and
  allocator startup remain host fixtures.
- **702/703/711/713:** four Laser parameter branches; real typed parameter
  lifetimes, COW and PMR command copies. LaserController::create_laser is a
  capture-only host boundary; its separate factory is strict exact.
- **712:** 196B rectangle-cancel branch; real 707B cancellation Boss and
  rectangle geometry. The 456B animation-pool resolver and 662B
  Bullet::cancel remain host boundaries.
- **800/801/802:** cross-Enemy script selection, selected-Enemy XY writeback
  and three-slot phase-script restarts through real EclManager/EclLoader and
  EnemyPhase owners.
- **553/554:** real EnemyData and BulletController setters, with Context
  retargeting and operand-order tests.
- Earlier routed families include movement, Pattern, bounds/health/controller,
  timer/mode, Card/health, animation spawn, membership, fog, bit flags,
  sound/gauge/title and selected-position cases.

The maintained root verifier currently compiles **58 locked-profile i386
COFF units** and runs 124 focused host source units under ASan/UBSan, including
opcodes 616, 617, 618, 619, 620, 627, 628, 629, 630, 632 and 633. The exact per-case boundaries and host limitations are documented in the
[dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md)
and the focused case notes linked from the [evidence index](EVIDENCE_INDEX.md).

Other major open Bosses remain in the [backlog](RE_OPEN_BOSS_BACKLOG.md),
including the 12,140B Bullet extended-command dispatcher, 39,470B Animation
VM update, 5,993B Animation Draw Boss, 2,245B Glyph mask compositor,
2,227B Glyph text core, 1,896B Card Start and the 626B FrontInf command parent
(currently 622/626B). The 1,954B Window D3D9 reset-state Boss is also
source-present but NONEXACT.

## Continuation order

1. Continue the remaining large Enemy dispatcher cases. Scan the still-open
   622–631 selector neighborhood and the other unhandled ranges; investigate
   each parent branch and its real leaf dependencies together.
2. Continue convergence of the 41,967B Enemy root and the open FrontInf,
   Bullet and Animation Bosses. Do not substitute trivial setters for Boss
   work; preserve natural C++ control flow and real ownership.

For source changes, replay only affected units and changed shared-header
consumers. Do not run a full cold replay for routine progress. Preserve
original C/C++ control flow, ABI, exceptions and operand order. No ASM,
synthetic padding, fake returns or shortened extents.

## Protected products and local storage

Preserve the locked target, supplied game files, useful native evidence,
Ghidra project/runtime and canonical build objects:

- resources/th20.exe
- ../game_exe/ if present
- .analysis/ native evidence and active investigation inputs
- .analysis/factory-native-ghidra/, .analysis/factory-runtime/
- ghidra-project/ and .tools/
- every build/*-canonical/ object/receipt directory

Noncanonical build outputs may be pruned only when they are generated
.obj/receipt artifacts, are not referenced by current scripts/docs, and do
not preserve an unresolved investigation. Keep current Enemy/Bullet/Item/
WeaponStone/FrontInf and other open-Boss work products. Do not delete an
entire analysis or build tree to save space.

## Useful focused commands

- git status --short --branch
- scripts/repo-python scripts/report-reconstruction-status.py --summary
- scripts/repo-python scripts/verify-enemy-state-dispatch-frontier.py
- scripts/repo-python scripts/verify-enemy-shared-queued-opcode-source.py
- scripts/repo-python scripts/replay-exact-units.py --source src/ChangedSource.cpp
- scripts/repo-python scripts/build.py --check
- git diff --check

The root verifier is a focused dispatcher/host check, not a full cold replay
or whole-parent exactness test. Use replay-exact-units.py --source only for
actual source changes and their captured include-closure consumers. Commit
stable checkpoints with the required gpt-web: prefix. Preserve and inspect
all dirty/untracked work before making changes.
