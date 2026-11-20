# CORE/RECON-1152 — natural-C++ source for Enemy ECL opcode 555 sound and animation spawn

The maintained source now contains `execute_enemy_animation_spawn_opcode(EnemyState&, opcode)` in `src/EnemyStateAnimationSpawnOpcode.cpp` for original opcode 555. This is one inline case region inside the **41,967-byte** `EnemyState::execute_opcode()` Boss, not a standalone original native function.

## Original native branch proof

The locked Japanese TH20 1.00a Steamless PE branch is `0x0048C3F4..0x0048C578`: **388 bytes / 81 x86 instructions / 10 direct E8 calls**, SHA-256 `5ab9c44d05b183785798d82102af4643c853bca652d0766f463c2548686016cd`. `scripts/verify-enemy-animation-spawn-opcode-source.py` extracts and disassembles these exact bytes and verifies every original E8 site/target pair.

The original branch also uses three immutable float constants: `0.2f` at `0x0056FBF8`, `-pi` at `0x0056E0F8`, and `2.0f` at `0x0056C8D0`. These values determine the strict near-distance threshold and the fallback `-pi/2` direction.

## Restored behavior and call order

- If `EnemyState::field_250 >= 0`, read the current Motion X coordinate and request the sound at that absolute X through the real process `SoundInf::request_effect_at`.
- If `EnemyState::field_254 >= 0`, first obtain the real current position and compute `geometry::squared_distance_xy(state.vector_6c, position)`.
- When `0.2f * 0.2f > distance`, choose the exact fallback direction `-pi / 2.0f`. Otherwise, obtain the position again and compute `geometry::direction_xy(state.vector_6c, position)`.
- Query the live `Context::enemy_controller()`, select the real AnimationFile by `field_258`, obtain the current position again, and call `AnimationFile::spawn(nullptr, field_254, position, direction, 3, nullptr)` with native layer 3.

The source deliberately preserves the three separate position reads and only evaluates the direction fallback when the strict distance comparison fails. It uses the actual Context, EnemyController, AnimationFile and SoundInf owners; no private file-selection boundary remains.

## Scoped verification and exactness boundary

`src/EnemyStateAnimationSpawnOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. The focused verifier checks the original 388B branch, all 81 instruction heads, all ten direct E8 targets, the three PE float constants, and the ordered natural-C++ call path. It reuses the existing whole-exact `EnemyController::animation_file` and `AnimationFile::spawn` methods.

This is an inline source fragment, not a separate native function. No `config/functions.csv` mapping or parent byte credit is added. The original 41,967B Enemy dispatcher remains **SOURCE-ABSENT, NONEXACT**. No full cold replay was performed.
