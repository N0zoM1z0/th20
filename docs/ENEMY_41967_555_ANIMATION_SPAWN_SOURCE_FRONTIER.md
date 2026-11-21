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

The source deliberately preserves the three separate position reads and only evaluates the direction fallback when the strict distance comparison fails. It references the original 0.2, negative-pi and 2.0 PE data words directly rather than synthesizing new constants. `Motion::position_x()` is retained as the natural typed C++ accessor; its pinned `/Od` body is the same 16-byte first-float getter as the native folded `ClockScalar::operator float` body at `0x004292E0`. The native Context getter call at `0x00412730` is the same 17-byte `[this+8]` pointer-return body used by `Context::enemy_controller()`. It uses the actual Context, EnemyController, AnimationFile and SoundInf owners; no private file-selection boundary remains.

## Scoped verification and exactness boundary

`src/EnemyStateAnimationSpawnOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. The focused verifier checks the original 388B branch directly from the locked PE, all 81 instruction heads, all ten direct E8 site/target pairs, the three PE float constants and the ordered natural-C++ call path. The focused i386 object also retains the real data references to `0x0056FBF8`, `0x0056E0F8` and `0x0056C8D0`. It reuses the existing whole-exact `EnemyController::animation_file` and `AnimationFile::spawn` methods.

This is an inline source fragment, not a separate native function. No `config/functions.csv` mapping or parent byte credit is added. The 41,967B Enemy root now has a partial C++ entry (CORE/RECON-1196); remaining inline cases and whole-root equivalence are still NONEXACT. No full cold replay was performed.

## Maintained root-host integration

The focused dispatcher verifier now checks selector index 101, all 388 native
bytes / 81 instruction heads and the ten ordered E8 targets. The ASan/UBSan
root host executes the actual production helper with both gates disabled,
sound-only, animation-only near/far, and both-gates cases. It checks the 0.04 squared
distance threshold, -pi/2 fallback, computed XY direction, selected file index,
script, layer 3, null stem/output and sound-before-file-before-spawn ordering.
SoundInf request, EnemyController file selection and AnimationFile spawn are
explicit host boundaries. Their underlying leaves and geometry are independently
replayed exact in affected objects: SoundEffects **5/5**, GeometryMetrics **8/8**,
MeshInterfaces **10/10**, ClockScalar **3/3**, MeshResourceAccess **8/8**,
EnemyResourceSelection **1/1**, and the complete 922-byte
`AnimationFile::spawn` Boss **1/1**. The 922-byte Boss itself strictly replays
**922/922** in its own fresh canonical object. No full cold replay or whole-root
byte credit is claimed.
