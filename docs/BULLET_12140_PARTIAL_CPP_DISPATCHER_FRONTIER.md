# CORE/RECON-1140 through 1142 — natural-C++ source frontier for the 12,140B Bullet command Boss

The original `Bullet::run_extended_commands()` at `0x0047DCF0` is **SOURCE-PRESENT, with all 34/34 primary command IDs represented, and still NONEXACT** in `src/BulletRunExtendedCommands.cpp`. Every original primary ID `0..33` has a maintained C++ case. The three original shared no-op IDs (5, 14, 28) retain their common advance behavior; the other 31 IDs have gameplay handlers. This is complete primary opcode source coverage, not a claim that the 12,140-byte parent is byte-exact.

## All original primary commands

| Native command IDs | Current natural-C++ behavior |
| --- | --- |
| `0, 1, 2, 3` | Command flags, Timer/vector setup, animation interrupt, aim selection, polar initialization, and sound request |
| `4` | Complete 8-way subtype switch: fixed/player-relative/random angle selection, normalization, slot-12 vector/scalar inputs, and slot-3 Timer/operand setup |
| `5, 14, 28` | The three original IDs sharing the native no-op/advance tail |
| `6, 7` | Slot-4 trajectory parameters and Bullet scalar assignment |
| `8` | Slot-11 Timer and duration setup |
| `9` | BulletStyle type/color selection, Animation reset/callback/script load, child AnimationHandle retirement/spawn, all 11 cancel-type mappings, and alternate EnemyController AnimationFile route |
| `10, 11, 12` | Bullet cancel, positional sound request, and slot-6 setup |
| `13` | Allocate new ShotMetadata, construct ShotParameters from two command records, copy PMR commands, call BulletController::fire, and conditionally cancel |
| `15, 16` | Native field assignment and repeat/jump counter behavior |
| `17` | VectorInterpolation start/end/tangent/duration/mode setup with optional position-relative endpoint |
| `18` | Thresholded angle update with player-relative targeting, single-wrap normalization, and optional speed update |
| `19` | Slot-9 polar vector, Timer, and command-flag setup |
| `20` | Animation flag-byte selection through the three original typed helpers |
| `21` | Slot-10 speed interpolation and aimed polar vector |
| `22` | FloatInterpolation start/end/tangent/duration/mode setup |
| `23` | Slot-12 position/angle/speed snapshot |
| `24` | Construct EnemySpawn from Bullet position and eight command words, then call the real EnemyController::create |
| `25, 26` | Draw-group assignment and slot-13 Timer activation |
| `27` | Two-record LaserType0/1 creation: real PMR command-vector copy, typed parameter construction, Context LaserController factory call, and conditional Bullet cancel |
| `29, 30, 31, 32, 33` | Radius/size selection, slot-5/slot-7 setup, slot-1 speed interpolation, and upper command-flag update |

The two native nested dispatchers are also represented by natural C++ switches: command 4's 8-way subtype switch and command 9's 11-way style-policy switch. See [the original command-9 CFG and its 14 E8 sites](BULLET_12140_COMMAND9_STYLE_ANIMATION_FRONTIER.md) and [the final 34/34 primary opcode closure, including commands 13/18/24](BULLET_12140_PRIMARY_OPCODE_34_OF_34_RESTORED.md).

## Type and ABI evidence used

- The receiver is the actual `Bullet` instance, independently established by both strict original callers (`BulletController::emit` and `Bullet::update_physics`) and their identical native member symbol.
- The 24-command guard uses the real `Bullet+0x38` command cursor and `Bullet+0x98` shared metadata owner.
- `BulletCommand` is the real 44-byte record. Its eight payload words have float/signed-integer/raw-word aliases while opcode/flags/script remain at `+0x20/+0x24/+0x28`; the existing full 3,832-byte emitter COFF contribution and all 129 relocations remain identical after that overlay.
- The implementation uses existing typed `BulletExtendedCommands::at`, `Timer`, `Animation`, `Vector3`, `select_bullet_aim`, `normalize_angle`, `Context::player`, `Player::direction_to`, `Context::enemy_controller`, `EnemyController::animation_file/create`, `EnemySpawn`, `GameRandom`, `polar`, `SoundInf`, `bullet_radius`, `type_to_script`, `AnimationFile::load_script/spawn`, `AnimationHandle::retire`, `ShotParameters`, `ShotMetadata`, `LaserType0/1Parameters`, and `LaserController::create_laser` interfaces.
- Command 13 uses the real `std::allocate_shared<ShotMetadata>` / `DebugAllocator` path, existing PMR vector copy assignment, and the whole `BulletController::fire` method. Command 24 uses the existing whole `EnemySpawn` constructor and `EnemyController::create`. No duplicate helper bodies are added.
- No assembly, manual padding, fabricated native target, or duplicated object storage is used.

## Scoped verification and exactness boundary

The source compiles as an i386 COFF object with the repository's pinned MSVC profile:

`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`

The live original-PE verifier now checks the exact original E8 site/target sets for commands 9, 13, 18 and 24, as well as all 210 physical E8 calls in the parent. It independently verifies the three original switch tables (34+8+11 = 53 PE HIGHLOW pointers) and all 38 in-body HIGHLOW fields. It also parses the top-level `switch (command.opcode)` and requires every primary ID `0..33`.

The original full dispatcher remains **NONEXACT**. Its 12,140 original body bytes, 38 body HIGHLOW fields, 210 E8 calls, and 53 switch-table HIGHLOW fields are not credited by this source. There is no canonical `match-units.toml` entry for the parent and no claim of whole-function exactness. The two original E8 targets still outside canonical strict source coverage are compiler runtime helpers (`__security_check_cookie` and `__allshl`); this does not make the parent link-complete or byte-exact.

Next reconstruction work is whole-parent convergence: compare the current natural C++ against the 2,490-instruction original CFG, recover remaining compiler/SEH/stack lifetimes and exact call/relocation ordering, and extend the boundary into the 41,967B Enemy ECL dispatcher rather than stopping at leaf helpers.
