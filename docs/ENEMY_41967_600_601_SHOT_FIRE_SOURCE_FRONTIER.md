# CORE/RECON-1148 — natural-C++ source for Enemy ECL opcodes 600 and 601

The maintained source now contains `execute_enemy_shot_fire_opcode(EnemyState&, opcode)` in `src/EnemyStateShotFireOpcode.cpp` for two substantial original primary cases inside the **41,967-byte** `EnemyState::execute_opcode()` Boss.

## Original native case evidence

The immutable TH20 1.00a Steamless PE audits establish:

| Opcode | Original case interval | Bytes | x86 instructions | Direct E8 |
| ---: | --- | ---: | ---: | ---: |
| 600 | `0x00492434..0x004925C7` | 403 | 90 | 10 |
| 601 | `0x00492803..0x00492A54` | 593 | 136 | 16 |

The complete original site/target lists and branch hashes are protected in `.analysis/core202-native-600-audit.json` and `.analysis/core204-native-601-audit.json`.

## Opcode 600 — full queued-shot reset

The branch uses the real writable 396B COW selector. It default-constructs and assigns the real 40B `ShotParameters`, then default-constructs an actual `EtamaArgInf` and move-assigns it into the selected metadata owner. This preserves the native PMR vector lifetime and the default metadata values, including sound IDs 21 and 38 and two default BulletCommand elements. It then clears exactly `record.vector_34.x/y`, `record.vector_40.x/y/z`, and finally `record.field_30`.

The `record.vector_34.z` lane at `+0x3C` is deliberately preserved. The source does not replace the reset with `memset`, broad structure zeroing, or an invented queue cleanup.

## Opcode 601 — position update, live Bullet owner mutation, and firing

The branch uses the real ensure-only `EnemyState::shared_shot()` selector, so an existing shared metadata owner is not cloned. It applies the native strict `record.vector_40.z > 0.9f` test: the relative branch uses `record.vector_40 + record.vector_34` and forces position Z to positive zero; the other branch uses `state.position_ref() + record.vector_34` and preserves the computed Z.

It then queries the live `Context::bullet_controller()` and sets scalar `field_48` to `state.field_274`, queries the Context again and calls the actual typed `BulletController::fire(record.parameters, record.owner)` with a real by-value `shared_ptr` copy, then queries the Context a third time and resets scalar `field_48` to zero. The controller is intentionally not cached: if firing retargets the Context, the final reset affects the new live controller. If firing throws, the final reset is not reached.

The 339B original `BulletController::fire` callee remains NONEXACT as a native function body; this opcode source calls the existing typed C++ method rather than claiming its implementation is byte-exact.

## Scoped verification and exactness boundary

`src/EnemyStateShotFireOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-shot-fire-opcode-source.py` checks the two immutable native branch ranges, byte/instruction counts, branch SHA-256 values, direct-call target multisets, exact reset fields, preserved `vector_34.z`, strict 0.9 comparison, three live Context lookups, real shared_ptr-by-value fire call, and final scalar reset order.

These are inline source fragments, not separate native functions. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy root now has a partial C++ entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence are still NONEXACT. No full cold replay was performed.
