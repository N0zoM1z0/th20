# CORE/RECON-1215 — natural-C++ Enemy ECL script-control opcodes 800/801/802

The maintained partial EnemyState::execute_opcode() root now routes original
Enemy ECL opcodes **800, 801 and 802** through
src/EnemyStateScriptControlOpcode.cpp. They remain three inline regions of
the original **41,967-byte** dispatcher, not standalone original functions.

## Original native branch evidence

All addresses and direct-call targets below are taken from the locked Japanese
TH20 1.00a Steamless PE and are checked by
scripts/verify-enemy-state-dispatch-frontier.py.

| Opcode | Selector index | Original interval | Bytes | x86 heads | Direct E8 |
| ---: | ---: | --- | ---: | ---: | ---: |
| 800 | 167 | 0x00495FC1..0x00496051 | 144 | 30 | 6 |
| 801 | 168 | 0x00495DDE..0x00495E86 | 168 | 32 | 7 |
| 802 | 169 | 0x00495E86..0x00495FC1 | 315 | 66 | 12 |
| **Total** | | | **627** | **128** | **25** |

## Restored source behavior

### Opcode 800 — select another Enemy's inline script

The branch obtains the live Context's EnemyController before reading integer
operand 0, then calls the real EnemyController::find. A missing target ends
the branch without resetting any Enemy. A found target follows the original
order:

1. EclManager::terminate_async()
2. EclManager::reset()
3. EclManager::select() with the borrowed script name at
   EclInstruction + 0x18

The string is not copied into an invented buffer. The focused root host checks
the inline name, a missing identifier, and Context retargeting during the
integer read; the cached controller still receives the lookup.

### Opcode 801 — write another Enemy's XY position to ECL destinations

The branch obtains the Context controller, reads integer operand 2, and
resolves the target Enemy. It then deliberately performs two independent
position reads and two late destination resolutions in this order:

1. Enemy::position_ref().x
2. EnemyState::float_argument_destination(0)
3. Enemy::position_ref().y
4. EnemyState::float_argument_destination(1)

The host test uses real ScriptStack destination slots, checks both float
words, and retargets Context during operand evaluation to ensure the original
controller receiver is retained. The original branch has no null-target
fallback; the fixture supplies a valid selected Enemy.

### Opcode 802 — restart the selected Enemies at a phase script

The branch reads integer operand 0 once, then walks selected Enemy slots
**0, 1 and 2**. For each slot it re-fetches the live Context controller and
uses the real EnemyController::selected() / EnemyHandle::resolve() path.
It skips the current slot named by EnemyState::field_270, missing targets,
and phase records whose signed life is negative. For an eligible record it
checks the borrowed script-array address, then calls the target's async
termination and runtime reset before re-reading that phase's script pointer
and selecting it through EclManager::select().

The natural source preserves all three independent phase-vector index
operations and the repeated Enemy::state_value() owner view. The 19-byte
Enemy::state_value() C++ method emits the same relocation-free +0x88
getter bytes as the already represented Session::player_table() head at
0x004989F0. This is a shared physical code head: no second function mapping
or duplicate byte credit is added.

## Exact leaves and focused verification

EclManager::select(const char*) is restored as a complete natural-C++ leaf at
0x00540200: **40/40 bytes**, 16 instructions and its original E8 to the
already exact 66-byte EclLoader::select at 0x00540280. Its source caches
the manager receiver and the EclLoader* at +0x58, then forwards
(manager,name) without an invented wrapper or direct field mutation.

Affected-only strict replays passed:

- EclManagerSelect.cpp: **1/1**, including EclManager::select **40/40**
- EclSelection.cpp: **11/11**
- EnemyVariables.cpp: **4/4**, including EnemyController::selected **43/43**
  and EnemyHandle::resolve **73/73**
- Enemy.cpp: **6/6**, including Enemy::position_ref **25/25**
- EnemyInitialization.cpp: **10/10**, including the 136-byte EnemyPhase
  vector indexer **36/36**

The async termination dependency was also rechecked after correcting the
shared allocator template: its trivial IntrusiveLink release now preserves the
original empty destroy_at call and replays as part of EclRuntimeLifetime
**12/12**. The 97-byte release leaf and 93-byte terminate_async caller both
remain whole exact; see the [trivial-node release correction](ECL_RUNTIME_TRIVIAL_DESTROY_AT_REPLAY_CORRECTION.md).

The focused dispatcher verifier checks all three original selector entries,
branch extents, instruction counts and 25 ordered native E8 targets. It also
checks the 25 ordered natural-C++ helper relocations, the shared 19-byte
Enemy::state_value machine-code alias, the 40-byte exact selection leaf, and
the ASan/UBSan root host. The host exercises the actual runtime reset,
EclLoader selection, selected-handle traversal, phase records, position
getter and VM destination slots. Its EnemyController::find fixture is a
controlled lookup stub; the production 251-byte EnemyController::find
remains independently strict exact.

The focused build compiles **29** locked-profile i386 COFF source units.
These inline cases receive no standalone function mappings or parent byte
credit. The 41,967-byte dispatcher remains **NONEXACT**; no full cold replay
was run, and no assembly or padding is used.
