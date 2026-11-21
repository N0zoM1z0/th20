# CORE/RECON-1153/1214 — natural-C++ source and maintained root-host integration for Enemy ECL opcodes 553 and 554

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

These are inline source fragments, not separate native functions. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy root now has a partial C++ entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence are still NONEXACT. No full cold replay was performed.

## Maintained partial-root host integration

The maintained `EnemyState::execute_opcode` router already forwards opcodes
553/554 to this helper. The focused dispatcher verifier checks selector
indices 99/100, the complete 66B/106B branch extents, 14/22 instruction heads
and all seven original ordered E8 targets. It also inspects the pinned i386
COFF object for the exact seven-call natural-C++ order:

1. `Context::enemy_controller`
2. `EnemyState::integer_argument`
3. `EnemyController::set_field_88`
4. `Context::bullet_controller`
5. `EnemyState::float_argument` (operand 1 / Y)
6. `EnemyState::float_argument` (operand 0 / X)
7. `BulletController::set_vector_4c`

The focused ASan/UBSan root host links and executes the real
`EnemyStateControllerSetterOpcode.cpp` helper, `EnemyController::set_field_88`
from `EnemyData.cpp`, and `BulletController::set_vector_4c` from
`BulletController.cpp`. There is no test stub for the helper or either setter.
The BulletController instances are real placement-constructed owners; the
production 39-byte setter is called on them, and a complete owner-image
comparison permits changes only to `vector_4c`'s two float words.

For opcode 553, a referenced integer read retargets both the original Context's
EnemyController and `EnemyState::context`; the original cached controller
still receives the raw `0x89ABCDEF` word and the alternate remains unchanged.
An injected operand exception produces no write. For opcode 554, referenced
float reads prove the manager indices arrive as `-101` then `-102` (Y then X).
The first read retargets both Context's BulletController and the state Context,
but only the original cached controller receives `(12.5,-7.25)`. Exceptions
at either the first or second operand prevent both owners from changing.

Affected-only strict replays passed **5/5** `EnemyData.cpp` units (including
`EnemyController::set_field_88` 25/25), **12/12** `BulletController.cpp`
units (including `BulletController::set_vector_4c` 39/39), **2/2** `Bullet.cpp`,
**3/3** `BulletValues.cpp`, and **3/3** `Context.cpp`. The focused root verifier
compiles 25 locked-profile i386 COFF source units and passes the root
ASan/UBSan fixture. These two case fragments receive no independent function
mapping or byte credit; the 41,967-byte parent remains NONEXACT. No full cold
replay was run.
