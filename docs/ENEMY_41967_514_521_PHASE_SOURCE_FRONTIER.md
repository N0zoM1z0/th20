# CORE/RECON-1155 — natural-C++ Enemy phase opcodes 514 and 521

The maintained source now contains `execute_enemy_phase_opcode(EnemyState&, const EclInstruction&, opcode)` in `src/EnemyStatePhaseOpcode.cpp` for original opcodes 514 and 521. These are inline branches of the **41,967-byte** Enemy ECL dispatcher, not separate original native functions.

## Original primary case CFGs

The locked TH20 1.00a Steamless PE establishes:

| Opcode | Original primary interval | Bytes | x86 instructions | Direct E8 |
| ---: | --- | ---: | ---: | ---: |
| 514 | `0x00493B74..0x00493E54` | 736 | 171 | 25 |
| 521 | `0x00493E54..0x00493EAC` | 88 | 20 | 2 |

Opcode 514 has SHA-256 `55c5a73a8eb46f8789fc65f7de00c7d563a97a1402b6d2d8dc928a03283feb7d`. Opcode 521 has SHA-256 `a23b78db5c500c9b64138b193847123fd66c1b98eab93fa4489334121b17d5b3`.

The older CORE209 audit's 284B/60-instruction/10-call range for 521 is a contiguous switch neighborhood containing multiple subsequent primary heads; it must not be credited as one opcode-521 CFG. The actual 521 entry performs exactly `integer_argument(0)`, calls `Enemy::configure_timeout`, then jumps to the common epilogue. The next switch block begins at `0x00493EAC`.

## Opcode 514 — phase/death/timeout transitions

The source preserves the native packet pointers and the full repeated branch behavior:

- `instruction + 0x20` is the borrowed phase name pointer.
- The `Session::field_70_is_two()` check occurs before the EnemyState flag bit `0x80` test.
- When both gates pass, `state.field_270` chooses first-phase vs second-phase death handling.
- Each phase branch independently calls `clamped_field_1f4()` and `clamped_field_1fc()`. The original does not share these calls between the first/second phase branches.
- The first phase selects `MBossDead` or `BossDead`; the second selects `MBossBDead` or `BossDead`. Each branch has its own `configure_phase` call site, followed by a separately cached `Enemy*`, integer operand 0, and `configure_timeout(..., "BossEscapeSpell")` call.
- The normal branch reads integer operands 1, 2 and 0 in that order and configures the borrowed `instruction+0x20` name.

The natural-C++ source intentionally preserves **13 integer-argument reads, five configure_phase calls, three configure_timeout calls, one Session mode check, and two copies of each Session clamp call**. This retains the original repeated side effects and call boundaries rather than collapsing the first/second phase paths into a shared ternary.

## Opcode 521 — borrowed timeout name

Opcode 521 loads and caches `Enemy*` before reading integer operand 0, then passes the borrowed `instruction + 0x18` name pointer to the actual `Enemy::configure_timeout` method. The dispatcher does not allocate or copy a string; the accepted 154B producer performs the native checked/unchecked timeout-record behavior and copies into the owned phase record.

## Leaf boundaries and focused verification

The existing `Enemy::configure_phase` (**301B**) and `Enemy::configure_timeout` (**154B**) producers remain whole-exact. The three Session helpers used by opcode 514 are now also registered matching after focused exact replay: `field_70_is_two` (**42B**), `clamped_field_1f4` (**25B**) and `clamped_field_1fc` (**25B**). The EnemyState→Enemy→EclRuntime integer reader chain is now also fully matching (two 36B wrappers); see [the complete argument forwarding boundary](ENEMY_ARGUMENT_FORWARDING_BOUNDARY.md). The targeted source replays rebuilt only `EnemyInitialization.cpp` (10/10 units), `Session.cpp` (25/25 units), and `EnemyScript.cpp` (10/10 units).

`scripts/verify-enemy-phase-opcode-source.py` extracts both primary CFGs directly from the locked PE, verifies their hashes, instruction counts and E8 targets, checks all four original phase strings, validates the repeated C++ call/operand counts, and compares the compiled helper's 27 direct-call relocations with the combined original call multiset.

No full 41,967B dispatcher source or exactness claim is made. No full cold replay was performed.
