# CORE/RECON-1153 — natural-C++ source for Enemy ECL opcodes 553 and 554

The maintained source now contains `execute_enemy_controller_setter_opcode(EnemyState&, opcode)` in `src/EnemyStateControllerSetterOpcode.cpp` for two original inline Enemy ECL case branches.

## Original native evidence

| Opcode | Original interval | Bytes | x86 instructions | Direct E8 |
| ---: | --- | ---: | ---: | ---: |
| 553 | `0x00495860..0x004958A2` | 66 | 14 | 3 |
| 554 | `0x004961D5..0x0049623F` | 106 | 22 | 4 |

The exact original bytes and call sites are re-extracted from the locked Japanese TH20 1.00a Steamless PE by `scripts/verify-enemy-controller-setter-opcodes.py`.

## Restored call order

- **553** obtains `Context::enemy_controller()` before reading integer operand 0, then writes the raw 32-bit word through the real `EnemyController::set_field_88()` method. The controller is deliberately cached before the VM read, since the read can mutate session/context state.
- **554** obtains `Context::bullet_controller()` before either VM read, reads float operand 1 (Y) before operand 0 (X), then invokes the real `BulletController::set_vector_4c(x,y)` setter. The controller is deliberately not re-fetched after the operands.

The source uses the actual typed controller owners and setter methods, not direct writes to guessed offsets.

## Scoped verification and exactness boundary

The helper compiles as i386 COFF under the pinned MSVC profile. The verifier checks the exact original branch byte lengths, instruction counts, hashes, all seven E8 site/target pairs, and the relative order of Context lookup, VM reads and setter calls.

These are inline source fragments, not separate native functions. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy dispatcher remains **SOURCE-ABSENT, NONEXACT**. No full cold replay was performed.
