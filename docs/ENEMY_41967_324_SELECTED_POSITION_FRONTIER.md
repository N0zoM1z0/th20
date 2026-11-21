# CORE/RECON-1213 — Enemy ECL opcode 324 selected-position query

Opcode 324 is a 276-byte inline case in the 41,967-byte
`EnemyState::execute_opcode` root, not a standalone native function. Its
original native interval is `0x004960C1..0x004961D5` (end exclusive), with
53 x86 instructions and 11 direct E8 calls. The exact case SHA-256 is
`e6f47339bcd51d0e79eee86cf3040af132dfc390128055edb3602f574fbad9ce`.
The compressed dispatch selector is index 17.

## Original ordered calls

| Native call site | Target | Role |
| --- | --- | --- |
| `0x004960CD` | `0x00412730` | Context's cached EnemyController getter (folded pointer getter) |
| `0x004960E0` | `0x004AB080` | `EnemyState::integer_argument(2)` |
| `0x004960F8` | `0x00498A80` | `EnemyController::find(identifier)` |
| `0x00496112` | `0x0047A2C0` | selected `Enemy::position_ref()` for X |
| `0x0049612B` | `0x004AA980` | late float destination 0 |
| `0x00496142` | `0x0047A2C0` | selected `Enemy::position_ref()` again for Y |
| `0x0049615C` | `0x004AA980` | late float destination 1 |
| `0x00496175` | `0x00499350` | fallback `EnemyState::position_ref()` for X |
| `0x0049618E` | `0x004AA980` | late float destination 0 |
| `0x004961A5` | `0x00499350` | fallback `EnemyState::position_ref()` again for Y |
| `0x004961BF` | `0x004AA980` | late float destination 1 |

## Restored natural-C++ path

`execute_enemy_selected_position_opcode` now lives in
`src/EnemyStateExecuteOpcode.cpp` and handles native opcode 324 alongside the
lower-numbered 17/21/25/45/260 source aliases. It caches the Context's
EnemyController before reading integer operand 2, calls the actual
`EnemyController::find`, then branches on the returned pointer. The found path
calls `Enemy::position_ref()` independently for X and Y; the fallback path
calls `EnemyState::position_ref()` independently for X and Y. Each component
is copied before its corresponding `float_argument_destination` is resolved.
This deliberately avoids caching a `Vector3&`: the original machine code makes
both position getter calls and both destination calls in that order.

The pinned `/Od /Ob0` i386 COFF object is inspected by
`scripts/verify-enemy-state-dispatch-frontier.py`; its eleven `DISP32`
relocations are asserted in the same order as the native E8 map. The root
ASan/UBSan fixture drives both a matching Enemy and the no-match fallback using
two real ECL float destinations.

## Exact leaf dependencies and validation scope

The supporting leaves remain independently credited, not duplicated as case
bytes: `EnemyController::find` is 251/251 exact, `Enemy::position_ref` is
25/25 exact, `EnemyState::position_ref` is 25/25 exact, and the 36-byte
`EnemyState::float_argument_destination` chain is exact. Affected-only source
replays passed **14/14** `DamageQueryProtocol.cpp` units, **6/6** `Enemy.cpp`
units, **10/10** `MeshInterfaces.cpp` units and **5/5** `EnemyScriptAdvance.cpp`
units. The `Context.cpp` owner source separately replays 3/3.

The 276-byte case receives no standalone function mapping or exact-byte credit.
The 41,967-byte Enemy root remains incomplete and NONEXACT; no full cold replay
or playable-game claim is made.
