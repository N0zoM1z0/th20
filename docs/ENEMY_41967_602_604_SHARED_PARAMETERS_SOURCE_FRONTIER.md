# CORE/RECON-1147 — natural-C++ source for Enemy ECL opcodes 602, 603 and 604

The maintained source now contains `execute_enemy_shared_queued_parameters_opcode(EnemyState&, opcode)` in `src/EnemyStateSharedQueuedParametersOpcode.cpp` for original opcodes 602, 603 and 604. These are three inline regions inside the **41,967-byte** `EnemyState::execute_opcode()` Boss, not standalone original native functions.

## Original native case evidence

The locked Japanese TH20 1.00a Steamless PE audit `.analysis/core205-native-602-604-audit.json` independently records:

| Opcode | Original interval | Bytes | x86 instructions | Direct E8 |
| ---: | --- | ---: | ---: | ---: |
| 602 | `0x00492A54..0x00492B09` | 181 | 43 | 8 |
| 603 | `0x00492B09..0x00492BC6` | 189 | 43 | 8 |
| 604 | `0x00492E47..0x00492F1C` | 213 | 51 | 10 |

All three start with `integer_argument(0)` and use the real **305-byte** `EnemyState::shared_shot()` selector. This is the ensure-only selector: it creates a missing metadata owner but does not clone an existing shared owner. That distinction is intentional and native; these branches never use the 396B writable COW selector.

## Restored field mutations

- **602** reads integer operands 1 and 2 in order and writes their raw 32-bit values to `ShotParameters::type` and `color` at `EnemyQueuedRecord+0x8/+0xC`.
- **603** reads float operands 1 and 2 in order and writes `EnemyQueuedRecord::vector_34.x/y` at `+0x34/+0x38`. The Z component at `+0x3C` and all shot type/color fields remain untouched.
- **604** reads float operand 1, normalizes it with the actual `normalize_angle`, and writes `ShotParameters::angle`; only then reads float operand 2, normalizes it independently and writes `angle_step`. The two reads/writes are not combined, so earlier successful mutations remain visible if the second operand throws.

The selected queue entry, actual shared owner, PMR list and surrounding state are the existing production objects. No fabricated COW, queue, or metadata type is introduced.

## Scoped verification and exactness boundary

`src/EnemyStateSharedQueuedParametersOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-shared-queued-parameters-opcode-source.py` checks the original branch addresses, byte/instruction counts, native SHA-256 values, direct-call target multisets, use of `shared_shot` (and absence of `writable_shot`), and every field/normalization write. The compiled object calls the actual typed `EnemyState::shared_shot`, integer/float accessors and `normalize_angle` methods.

No `config/functions.csv` function mapping or parent byte credit is added: these are inline opcode case fragments. The 41,967B Enemy dispatcher remains **SOURCE-ABSENT, NONEXACT**, with no canonical whole-parent unit. No full cold replay was performed.
