# Enemy ECL opcode 617 — Player-relative angle destination

## Status and boundary

Opcode 617 is restored as natural C++ in
`src/EnemyStatePlayerAngleOpcode.cpp`, routed through the maintained partial
`EnemyState::execute_opcode` root and executed by its ASan/UBSan test host.
It is an inline case in the original **41,967-byte** parent at `0x0048C010`,
not a standalone native function. The parent remains **NONEXACT**; no parent
byte credit or synthetic standalone match is claimed.

## Locked native branch

Target: Japanese TH20 1.00a Steamless `resources/th20.exe`, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

- Opcode: `617`; compressed selector index `135`.
- Branch: `0x004958C3..0x0049598E` (end-exclusive).
- Size: **203 bytes / 41 x86 instructions / 8 direct E8 calls**.
- Branch SHA-256:
  `495e3bf841a650d5b5ba51ce400eac059768f8557e0977d941cfb59aec965ff9`.
- The branch ends with a direct jump from `0x00495989` to the common
  dispatcher epilogue at `0x004963DF`.

| Call site | Target | Recovered role |
|---|---:|---|
| `0x004958CF` | `0x0040FF90` | `Context::player()`; shared +4 getter body |
| `0x004958D6` | `0x00460850` | `Player::position_ref()` |
| `0x004958E5` | `0x004AAFB0` | `EnemyState::float_argument(1)` |
| `0x00495910` | `0x0040FF90` | re-read `Context::player()` |
| `0x00495917` | `0x00460850` | re-read `Player::position_ref()` |
| `0x00495926` | `0x004AAFB0` | `EnemyState::float_argument(2)` |
| `0x00495962` | `0x00459280` | `scalar_math::arctangent(dy, dx)` |
| `0x00495978` | `0x004AA980` | `EnemyState::float_argument_destination(0)` |

The `0x0040FF90` 17-byte body is a shared/folded `+4` accessor. The existing
function ledger labels that physical body `Timer::operator int`; the caller's
actual receiver is `Context*`, and `Context::player()` is the source-level
semantic alias used here. This restoration does not relabel or double-credit
the shared native body. `Context::player()` is implemented alongside the
other Context accessors in `src/Context.cpp`.

The other three important leaves already exist: the exact 19-byte
`Player::position_ref()` at `0x00460850`, the 48-byte `scalar_math::arctangent`
wrapper at `0x00459280`, and the 36-byte float-destination forwarding wrapper
at `0x004AA980`.

## Recovered operation and sequencing

The operation is:

\[
  \operatorname{atan2}(P_y - Y,\;P_x - X)
\]

where `P` is the live Player position, and `X`/`Y` are VM float operands 1/2.
The result is written to VM float destination 0.

The exact C++ sequence is deliberately explicit:

1. Resolve `state.context->player()` and its `position_ref()`.
2. Read VM float argument 1, then compute `first_position.x - target_x`.
3. Re-read `state.context->player()` and its `position_ref()`.
4. Read VM float argument 2, then compute `second_position.y - target_y`.
5. Call the existing `scalar_math::arctangent(delta_y, delta_x)`.
6. Resolve `float_argument_destination(0)` and store the result.

Do not cache the Player across both operands. The original native code
re-reads `EnemyState.context` after the first VM read, so a Context retarget
during operand 1 affects the Y source but not the already-captured X source.
The root host constructs two real Player objects and tests this exact behavior.
It also uses the real `Context::player`, `Player::position_ref`, Player
constructor and `Player::set_entity_flag_10` source paths; only the still-open
Player virtual `enable` and destructor boundaries remain test-owned.

Do not replace this with `Player::direction_to()`. That different function
has an explicit coincident-point special case returning pi/2. Opcode 617 calls
`atan2` directly, so `atan2(0,0)` writes 0.0f. The root host tests that
observable distinction.

The VM packet uses destination operand 0 as a local stack slot and operands
1/2 as external references `-101`/`-102`. A second-operand exception occurs
after both Player position lookups but before atan2 and destination lookup;
the prior destination value remains unchanged.

## Focused verification

`scripts/verify-enemy-player-angle-opcode-source.py` checks the locked PE
fingerprint, selector index, 203-byte branch hash, all 41 decoded instructions,
all eight ordered E8 call sites/targets, the common epilogue jump, and the
natural source order. The maintained dispatcher verifier checks the locked
COFF relocation sequence:

`Context::player → Player::position_ref → float_argument(1) → Context::player → Player::position_ref → float_argument(2) → arctangent → float_argument_destination(0)`

The COFF checks separately confirm the Context +4 accessor and Player +0x614
position view. The ASan/UBSan root host tests the real Player fixture, live
Context retargeting between operands, the direct atan2 coincident-point result,
and second-operand exception preservation. The maintained dispatcher
verifier compiles **40 locked-profile i386 COFF source units** and executes
**105 focused host source units**. No full cold replay was run.

The opcode remains an inline fragment only. No standalone function unit,
ASM/padding substitute, or 41,967-byte parent exactness claim is created.
