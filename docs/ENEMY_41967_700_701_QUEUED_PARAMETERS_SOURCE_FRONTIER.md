# CORE/RECON-1146 — natural-C++ source for Enemy ECL opcodes 700 and 701

The maintained source now contains `execute_enemy_queued_parameters_opcode(EnemyState&, opcode)` in `src/EnemyStateQueuedParametersOpcode.cpp` for original opcodes 700 and 701. Both are inline case regions of the **41,967-byte** `EnemyState::execute_opcode()` Boss, not independent original functions.

## Immutable original case evidence

The locked Japanese TH20 1.00a Steamless PE audit `.analysis/core198-native-700-701-audit.json` confirms:

| Opcode | Original case interval | Bytes | x86 instructions | Direct E8 |
| ---: | --- | ---: | ---: | ---: |
| 700 | `0x0049392D..0x00493A3A` | 269 | 59 | 10 |
| 701 | `0x00493A3A..0x00493B5B` | 289 | 67 | 11 |

Both branches read integer operand 0, then call the real `EnemyState::writable_shot()` and consume the native pair of `EnemyQueuedRecord*` / `ShotMetadata*` pointers. The writable selector's 396-byte implementation is now accepted whole-native exact (CORE/EXACT-200); this source does not recreate or wrap it.

## Restored mutations and operand order

- Opcode 700 reads `float_argument(1)`, `(2)`, `(3)` and writes the exact raw float values to the selected record's `ShotParameters::position.x/y/z` (`record+0x10/+0x14/+0x18`). It then reads `float_argument(4)` and writes `EtamaArgInf::field_14`. Earlier successful stores remain visible if a later VM read throws.
- Opcode 701 reads `integer_argument(1)` through `(5)` and writes the exact 32-bit word representations to metadata offsets `+0x24/+0x28/+0x2C/+0x30/+0x34`. The C++ source uses `uint32_t` casts to preserve the raw native word bits, including negative signed inputs.

Neither opcode changes `ShotMetadata::field_30` cursor. They preserve the selected metadata object's actual COW owner and use the same real queue/list storage and pair ABI as the original case.

## Scoped verification and exactness boundary

`src/EnemyStateQueuedParametersOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-queued-parameters-opcode-source.py` checks the original 700/701 branch intervals, byte/instruction counts, native SHA-256 values, direct-call destination multisets, and all maintained source writes. The object relocations point to the actual `EnemyState::integer_argument`, `float_argument` and accepted `writable_shot` methods.

The source is a case fragment, not a standalone native-function definition. No `config/functions.csv` mapping or original parent byte credit is added. The 41,967B Enemy ECL dispatcher now has a partial C++ root entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence remain NONEXACT. No full cold replay was performed.
