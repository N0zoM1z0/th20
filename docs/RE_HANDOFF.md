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

## Latest checkpoint — Enemy ECL opcode 620

The prior dirty opcode-620 work has been integrated into the maintained root
host and focused verifier. The three original in-progress paths are now
reviewed production/test/verifier work, not disposable changes:

- `src/EnemyStateSharedQueuedParametersOpcode.cpp`
- `tests/enemy_state_dispatch_root.cpp`
- `scripts/verify-enemy-shared-queued-opcode-source.py`

Native opcode 620 is the **250-byte / 57-instruction / 8-E8** case at
`0x00492D4D`, selector index 138. Its natural C++ source uses the real
ensure-only `shared_shot` path and pair `std::get` extraction, writes the
queued record's `vector_40.x/y/z`, preserves the `-990.0f` threshold and
`1.0f` constant, and matches the original `COMISS/JBE` NaN behavior. The root
test checks shared metadata ownership, threshold boundary, NaN, and the
second-operand exception after the X write.

The false-returning root-test stub is removed. The production helper is
included in `HOST_SOURCES` and the locked-profile COFF compile list; the
native opcode verifier is invoked by the maintained root verifier. The
focused root host passes under ASan/UBSan, and the root verifier compiles
**36 locked-profile i386 COFF source units**. See the dedicated
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
- **620:** 250B shared queued-vector update; real ensure-only shared record,
  pair extraction, ordered X/Y writes, native `COMISS/JBE` NaN behavior and
  second-operand exception coverage.
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

The maintained root verifier currently compiles **36 locked-profile i386
COFF units** and runs the focused root host under ASan/UBSan, including opcode
620. The exact per-case boundaries and host limitations are documented in the
[dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md)
and the focused case notes linked from the [evidence index](EVIDENCE_INDEX.md).

Other major open Bosses remain in the [backlog](RE_OPEN_BOSS_BACKLOG.md),
including the 12,140B Bullet extended-command dispatcher, 39,470B Animation
VM update, 5,993B Animation Draw Boss, 2,245B Glyph mask compositor,
2,227B Glyph text core, 1,896B Card Start and the 626B FrontInf command parent
(currently 622/626B). The 1,954B Window D3D9 reset-state Boss is also
source-present but NONEXACT.

## Continuation order

1. Continue the remaining large Enemy dispatcher cases. The next native
   targets include the 618/632/617 range; investigate each parent branch and
   its real leaf dependencies together.
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
