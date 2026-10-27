# Full Enemy dispatcher: complete opcode 516 and 575 host integration (CORE168)

This is a bounded **whole-root source reconstruction** checkpoint for the
locked Japanese 1.00a Steamless target (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
`EnemyState::execute_opcode` begins at `0x0048C010`: its native body is
**41,967 bytes**, with additional indexed tables, compiler-owned metadata,
exception cleanup and final full-contribution ownership still unimplemented.
No production method, canonical root comparison unit or partial root byte
credit is introduced here. The exact SoundInf/Player callees were separately
accepted as complete functions in CORE167 and CORE166.

## Original paths, not reference-adapter guesses

The attested complete 174-head case catalog identifies the following actual
native call order. Counts include shared exit instructions; case paths are
**not** separate compiler contributions.

| Opcode | Native case head | Reachable instruction heads | Key native calls |
| --- | --- | ---: | --- |
| 516 | `0x00493F3F` | 31 | `EnemyState::position_ref` at `0x499350`, `integer_argument(0)` at `0x4AB080`, `SoundInf::request_effect_at` at `0x426EB0` |
| 575 | `0x004956EC` | 28 | `player(0)` at `0x460830`, `integer_argument(0)` at `0x4AB080`, `Player::set_entity_flag_10` at `0x49C390` |

In opcode 516, the native reads `position_ref()->x` into a temporary **before**
reading sound ID argument 0, then invokes the genuine `process_sound` object at
`0x005BA830`. The call converts the captured X coordinate into signed pan
using the exact already-verified `int((x * 1000.0f) / 192.0f)` method.

In opcode 575, the native resolves and caches **`player(0)` first**;
argument 0 is read afterward. The resulting call clears/sets bit 10 in the
captured Player+0x14 flag word, preserving all 31 other bits. An operand read
that redirects the Session Player pointer does not retarget that invocation.

The two complete candidate bodies, in the same natural C++ method switch,
are retained as follows (these are our reconstruction expressions, not copied
reference-game source):

```cpp
case 516: {
    const float x = state.position_ref().x;
    const auto id = state.integer_argument(0);
    process_sound.request_effect_at(id, x);
    break;
}
case 575: {
    Player* receiver = player(0);
    const auto flag = static_cast<std::uint32_t>(state.integer_argument(0));
    receiver->set_entity_flag_10(flag);
    break;
}
```

The entire previous private draft is preserved. These are two more effective
opcode values and two more distinct primary heads: **110 values/81 heads become
112 values/83 heads**. Unimplemented table entries, case tails and shared
native EH continue to prevent full-root code emission/strict exactness.

## Real-owner tests, mutation and failure order

The prior CORE161 private `-O2 -fsanitize=undefined -fno-sanitize-recover=all`
whole-root host exercised **36,232** cases, including a complete real Dialogue
owner instead of the earlier synthetic ready getter. A fresh private CORE168
host preserves all of those cases and adds **78** independent native-path
scenarios:

- **52 opcode-516 cases:** four full signed sound IDs and thirteen signed X
  values, with the integer-operand hook deliberately changing the Enemy's
  position before invoking the real `SoundInf::request_effect_at`; the queued
  effect receiver, full ID and signed pan still reflect the original X
- **24 opcode-575 cases:** four starting Player flag words and six signed
  argument values, with the argument hook retargeting `Session::context(0)`
  from the original Player to another real Player; only the original Player's
  bit 10 changes, leaving the alternate owner and unrelated bits intact
- **2 exception cases:** the integer-operand read throws before any sound
  queue call or Player bit modification; neither native-callee side effect
  occurs, while the hooks' pre-throw receiver retargeting is observed

The **entire 36,310-case** host executes successfully. The private test uses
the two *production C++ member bodies*, not a shape-only stub for their
conversions or flag operations. The unresolved downstream `request_effect`
queue is captured, and actual original process startup/VM rendering remain
outside this fixture.

The old CORE161 host linked with a fabricated pre-Dialogue-destruction assumption
that every `AnimationHandle::retire()` processed only sentinel ID 11. Restoring
the real Dialogue destructor surfaced this error. The refreshed fixture
preserves the original strict sentinel-11 behavior and separately forwards
only the real Dialogue fixture's zero and `0x200..0x203` handles to its known
retirement recorder. Linking now also includes the actual
`src/AnimationChildren.cpp` that the recovered follow-box traversal needs;
no invented child lookup or relaxed production destructor was introduced.
These fixture repairs were necessary to preserve all older large-root cases.

## Reproducibility and evidence separation

Private ignored products, relative to `.analysis/`, are:

- `core168-enemy-dispatch-candidate.cpp` — full candidate with two new cases,
  without replacing `core159-enemy-dispatch-candidate.cpp`
- `core168-dispatch-host.cpp`, `core168-sound-player-host-cases.inc` — complete
  current host and its 78 new cases, without modifying `core161-dispatch-host.cpp`
- `core168-dispatch-host-recipe.json`, `core168-dispatch-host.log` — fixed host
  compiler flags, 78 source providers and passing output
- `core168-whole-enemy-root-proof.json` — locked native root/catalog identities,
  the original/new SHA-256 of private code, all 78 input source SHA-256 values,
  both exact callee-unit receipts and the 36,310 scenario count

The private host can be rebuilt from its owned recipe with
`scripts/repo-python`, using its exact source list, profile and output;
it is a host-only program and **not** an attempt to claim a new native-root
compiler contribution. No tracked production source, match ledger, canonical
object or progress numerator changes in CORE168.

## Next full-root boundary

The 502/503 animation-flag traversals must preserve old handle words on a
failed pool lookup; `AnimationHandle::resolve()` clears failures and cannot be
substituted. Original 516/575 source ordering is now tested through actual
SoundInf/Player owners, but other animation, resource, damage, stage-like and
sound paths remain unresolved. The shared 174-head dispatch table, 704-byte
compressed index, four nested rank tables, 41,967-byte body, EH handler and
its true compiler contribution still need complete reconciliation.
Continue with [dispatcher layout](CORE_ENEMY_DISPATCH_LAYOUT.md),
[SoundInf source proof](SOUND_EFFECT_PAN_RECONSTRUCTION.md) and
[Player flag owner](ENEMY_OPCODE_575_PLAYER_FLAG_RECONSTRUCTION.md).
