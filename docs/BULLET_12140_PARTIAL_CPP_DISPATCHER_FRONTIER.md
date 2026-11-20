# CORE/RECON-1140 — first natural-C++ source frontier for the 12,140B Bullet command Boss

The original `Bullet::run_extended_commands()` at `0x0047DCF0` is now **SOURCE-PRESENT, PARTIAL, and NONEXACT** in `src/BulletRunExtendedCommands.cpp`. This is the first maintained C++ definition of the large dispatcher; it is deliberately not presented as a complete or byte-exact restoration.

## Current native command coverage

The original primary jump table has 34 command IDs (`0..33`). The maintained source currently has natural C++ control flow for 22 gameplay branches and the three original shared no-op/advance IDs:

| Native command IDs | Current source behavior |
| --- | --- |
| `0, 1, 2, 3` | Command-flag update, Timer/vector setup, animation interrupt, aim selection, polar vector initialization, and sound request |
| `4` | Complete 8-way subtype switch: fixed/player-relative/random angle selection, normalization, slot-12 vector/scalar inputs, and slot-3 timer/operand setup |
| `9` | BulletStyle type/color selection, Animation reset/callback/script load, child AnimationHandle retirement/spawn, all 11 cancel-type mappings, and alternate EnemyController AnimationFile route |
| `5, 14, 28` | The three original IDs sharing the native no-op/advance tail |
| `6, 7` | Slot-4 trajectory parameters and Bullet scalar assignment |
| `8` | Slot-11 Timer and duration setup |
| `9` | Full bullet style/type/color change, animation callback/script load, optional child-animation spawn, and 11-way cancel-style mapping |
| `10, 11, 12` | Bullet cancel, positional sound request, and slot-6 setup |
| `15, 16` | Native field assignment and repeat/jump counter behavior |
| `17` | VectorInterpolation start/end/tangent/duration/mode setup with optional position-relative endpoint |
| `21` | Slot-10 speed interpolation and aimed polar vector |
| `22` | FloatInterpolation start/end/tangent/duration/mode setup |
| `23` | Slot-12 position/angle/speed snapshot |
| `27` | Two-record LaserType0/1 creation: real PMR command-vector copy, typed parameter construction, context LaserController factory call, and conditional Bullet cancel |
| `25, 26` | Draw-group assignment and slot-13 timer activation |
| `29, 30, 31, 32, 33` | Radius/size selection, slot-5/slot-7 setup, slot-1 speed interpolation, and upper command-flag update |

That is **25/34 primary table entries represented**, including 22 nontrivial command handlers and the three original shared no-op cases. Command 4 is restored with its complete native 8-way subtype switch; command 9 now has both BulletStyle and alternate Enemy AnimationFile routes; command 27 constructs the real LaserType0/1 parameter records from two adjacent BulletCommand entries. The nine still-pending command handlers are `8, 13, 17, 18, 19, 20, 22, 23, 24`.

The unsupported commands currently return without consuming the command. This is an explicit partial-source boundary, not original game behavior: it prevents the reconstruction from silently skipping commands whose state transitions are not yet restored. The command-9 11-way cancel-type selector is now restored; the ECL/Enemy creation paths remain open. Command 27 uses the existing whole LaserType0/1 constructors, destructors, PMR vector copy assignment, Context accessor, and LaserController factory. Do not treat this source as playable or complete.

## Type and ABI evidence used

- The receiver is the actual `Bullet` instance, independently established by both strict original callers (`BulletController::emit` and `Bullet::update_physics`) and their identical native member symbol.
- The 24-command guard uses the real `Bullet+0x38` command cursor and `Bullet+0x98` shared metadata owner.
- `BulletCommand` is the real 44-byte record. Its eight payload words have float/signed-integer/raw-word aliases while opcode/flags/script remain at `+0x20/+0x24/+0x28`; the existing full 3,832-byte emitter COFF contribution and all 129 relocations remain identical after that overlay.
- The implementation uses existing typed `BulletExtendedCommands::at`, `Timer`, `Animation`, `Vector3`, `select_bullet_aim`, `normalize_angle`, `Context::player`, `Player::direction_to`, `Context::enemy_controller`, `EnemyController::animation_file`, `GameRandom`, `polar`, `SoundInf`, `bullet_radius`, `type_to_script`, `AnimationFile::load_script/spawn`, `AnimationHandle::retire`, `LaserType0/1Parameters`, and `LaserController::create_laser` interfaces. The fresh COFF probe contains a compiler-emitted 8-entry nested subtype jump table for command 4, an ordinary 11-way style-policy switch for command 9, and direct typed calls for the Animation and Laser lifetimes. No assembly, padding, fabricated native target, or duplicated object storage was added.

## Scoped verification and exactness boundary

The new source compiles as an i386 COFF object with the repository's pinned MSVC profile:

`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`

The separate strict canonical `bullet_emitter_whole_3735` object was freshly re-probed after the shared `BulletCommand` header overlay: its complete 3,832-byte contribution and all 129 relocation records are identical to `build/core645-canonical/BulletEmitter.obj`.

The original full dispatcher remains **NONEXACT**. Its 12,140 original body bytes, 38 body HIGHLOW fields, 210 E8 calls, and 53 switch-table HIGHLOW fields are not credited by this partial source. There is no canonical `match-units.toml` entry for the parent and no claim of whole-function exactness. The independent native closure verifier continues to account for all 210 original E8 sites, all 53 table pointers and all 38 in-body HIGHLOW fields.

Next reconstruction work is the pending complex handlers, prioritizing command 8's Animation slot branch, then the ECL/Enemy creation paths and command 13's slot-6 consumer.
