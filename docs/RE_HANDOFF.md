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

## Current worktree — preserve this in-progress opcode 620 work

The worktree is intentionally dirty in exactly these three paths:

- src/EnemyStateSharedQueuedParametersOpcode.cpp
- tests/enemy_state_dispatch_root.cpp
- scripts/verify-enemy-shared-queued-opcode-source.py (untracked)

This is an unfinished reconstruction of **Enemy ECL opcode 620**. Do not
reset, overwrite or discard it.

The original case is **250 bytes / 57 x86 instructions / 8 ordered E8 calls**
at 0x00492D4D, selector index 138. The source adds the case to the existing
shared queued-parameter helper. It reads two float operands, writes
EnemyQueuedRecord::vector_40.x/y, and sets Z according to the original
-990.0f threshold and 1.0f constant. The root test covers the sentinel
boundary, preservation of shared metadata ownership and a second-operand
exception after the X write.

The production dispatcher already routes this helper, but the root-host
integration is **not finished**:
- The test removed its old false-returning helper stub.
- scripts/verify-enemy-state-dispatch-frontier.py does not yet include
  src/EnemyStateSharedQueuedParametersOpcode.cpp in HOST_SOURCES.
- The new native verifier is not yet called by the maintained root verifier.
- The current 35-unit root-host pass predates these dirty changes. Opcode 620
  has no accepted COFF/replay or root-host result yet.

**Immediate next action:** finish the host link and locked-profile COFF
integration for the shared helper, wire the new native verifier into the
maintained verifier, run the focused root host and affected-only comparison,
then update the opcode-620 evidence and commit the completed source/test
checkpoint. The expected host source count will increase when this helper is
added. Do not claim the case complete until the real helper executes in the
root host and its COFF call order is checked.

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

The maintained root verifier currently compiles **35 locked-profile i386
COFF units** and runs the focused root host for the committed baseline. That
count does not include the uncommitted opcode-620 helper above. The exact
per-case boundaries and host limitations are documented in the
[dispatcher frontier](ENEMY_STATE_EXECUTE_OPCODE_41967_PARTIAL_SOURCE_FRONTIER.md)
and the focused case notes linked from the [evidence index](EVIDENCE_INDEX.md).

Other major open Bosses remain in the [backlog](RE_OPEN_BOSS_BACKLOG.md),
including the 12,140B Bullet extended-command dispatcher, 39,470B Animation
VM update, 5,993B Animation Draw Boss, 2,245B Glyph mask compositor,
2,227B Glyph text core, 1,896B Card Start and the 626B FrontInf command parent
(currently 622/626B). The 1,954B Window D3D9 reset-state Boss is also
source-present but NONEXACT.

## Continuation order

1. Finish and verify the dirty opcode-620 work described above.
2. Continue the remaining large Enemy dispatcher cases (the native case map
   still has substantial uncovered blocks, including the 618/632/617 range).
3. Continue the 41,967B parent convergence and the open FrontInf/Bullet/
   Animation Bosses. Work on large parents and their real leaf dependencies
   together; do not substitute a sequence of trivial setters for Boss work.

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
- scripts/repo-python scripts/replay-exact-units.py --source src/ChangedSource.cpp
- scripts/repo-python scripts/build.py --check
- git diff --check

The root verifier is a focused dispatcher/host check, not a full cold replay
or whole-parent exactness test. Use replay-exact-units.py --source only for
actual source changes and their captured include-closure consumers. Commit
stable checkpoints with the required gpt-web: prefix. Preserve and inspect
all dirty/untracked work before making changes.
