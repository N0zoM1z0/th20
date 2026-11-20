# CORE/RECON-1157 — exact EnemyState / Enemy / EclRuntime argument forwarding boundary

The Enemy VM argument bridge is now restored as a complete chain of twelve natural-C++ methods. The functions were already present in production source, but their function-map status remained `reconstructed`; this checkpoint independently replays the two source providers and upgrades only the twelve complete, standalone original methods to `matching`.

## Twelve original functions

| Native address | Bytes | Maintained C++ owner/method | Original direct target |
| --- | ---: | --- | --- |
| `0x004AAFB0` | 36 | `EnemyState::float_argument` | `0x004AB010` |
| `0x004AB010` | 36 | `Enemy::float_argument` | `0x0053E970` |
| `0x004AB080` | 36 | `EnemyState::integer_argument` | `0x004AB0E0` |
| `0x004AB0E0` | 36 | `Enemy::integer_argument` | `0x0053ED50` |
| `0x004AA980` | 36 | `EnemyState::float_argument_destination` | `0x004AA9B0` |
| `0x004AA9B0` | 36 | `Enemy::float_argument_destination` | `0x0053E720` |
| `0x004AA9E0` | 36 | `EnemyState::integer_argument_destination` | `0x004AAA10` |
| `0x004AAA10` | 36 | `Enemy::integer_argument_destination` | `0x0053E850` |
| `0x004AAFE0` | 47 | `EnemyState::float_argument_value` | `0x004AB040` |
| `0x004AB040` | 47 | `Enemy::float_argument_value` | `0x0053EA90` |
| `0x004AB0B0` | 40 | `EnemyState::integer_argument_value` | `0x004AB110` |
| `0x004AB110` | 40 | `Enemy::integer_argument_value` | `0x0053EE30` |

The accepted wrapper bytes total **462 bytes**. This is exact native function coverage; original authored/compiler origin remains unknown for these wrappers and no authored-byte credit is claimed.

## Actual owner and call semantics

The first layer is an `EnemyState` member. It reads the live `entity` pointer and forwards the signed VM index unchanged to the corresponding `Enemy` method. The second layer is a member of the real `Enemy` object. It reads the current inherited `EclManager::current_runtime` pointer and calls the corresponding `EclRuntime` reader, destination resolver, or supplied-value method.

The distinction between these protocols is preserved:

- `integer_argument` and `float_argument` read the current VM operand.
- `integer_argument_destination` and `float_argument_destination` resolve an instruction destination; they are not the virtual register-destination methods that accept an already-decoded register selector.
- `integer_argument_value` and `float_argument_value` forward a supplied value without replacing them with a consuming read.

The exact E8 chain remains visible in the original PE and the canonical source. In particular, opcode 549 caches its Context-selected EnemyController before operand 1, runs the real 244B membership query, then resolves destination 0 through the late EnemyState→Enemy→EclRuntime destination chain. Opcodes 514/521 use the same reader chain, while opcode 551 uses both integer and float readers.

## Focused replay and verification

The affected source providers were rebuilt independently under the pinned i386 MSVC profile:

- `src/EnemyScript.cpp`: **10/10 units exact**, one fresh object.
- `src/EnemyScriptAdvance.cpp`: **5/5 units exact**, one fresh object.

`scripts/verify-enemy-argument-forwarding-boundary.py` extracts all twelve complete bodies directly from the locked PE, verifies each original E8 site and target, checks the production forwarding expressions and requires each function row to be `matching`. The original 41,967B Enemy dispatcher remains NONEXACT; no full cold replay was performed.
