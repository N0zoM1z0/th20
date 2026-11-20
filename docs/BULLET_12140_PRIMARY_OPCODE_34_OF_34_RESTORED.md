# CORE/RECON-1142 — all 34 primary Bullet command IDs now have natural C++ handlers

`src/BulletRunExtendedCommands.cpp` now contains a top-level C++ case for every original primary command ID `0..33`. The three native shared no-op IDs (5, 14, 28) advance through their common path; the other **31 IDs have gameplay handlers**. The two original nested dispatchers are also represented by natural C++ switches: command 4 has eight subtype cases and command 9 has eleven style-policy cases.

This is semantic/source coverage, not whole-function exactness. The original `Bullet::run_extended_commands()` is still **12,140B / 2,490 x86 instructions and NONEXACT**. No bytes from its 12,140B original body are credited. The native parent still needs full stack/ABI/control-flow/SEH/codegen convergence and original PE relocation acceptance.

## Last three complex handlers closed

### Command 13 — allocate metadata, build ShotParameters, and fire a Bullet pattern

The 153-instruction original CFG has 15 direct E8 calls. The C++ handler:

- Creates a real `std::shared_ptr<ShotMetadata>` through `std::allocate_shared` and `DebugAllocator<ShotMetadata>`.
- Fills the new `EtamaArgInf` metadata's native `field_38` and `field_44` from the current command.
- Constructs the real 40-byte `ShotParameters`, copying Bullet position, count/rows, aimed angle, angle step, speed selection, and speed step.
- Reads the following 44-byte command for type/color and the post-fire cancel bit, preserving the original two-command cursor advance.
- Copies the original PMR `BulletCommand` vector into the new metadata, then calls the already whole-exact `BulletController::fire` with the real by-value shared pointer.
- Performs the native conditional `Bullet::cancel(0)` after firing.

The current speed fallback uses the original `native_selector_min` threshold at `0x0056FD80` (`-999990.0f`), not the unrelated positive `990.0f` selector constant.

| Original E8 site | Original target | Role |
| --- | --- | --- |
| `0x0047F701` | `0x0040C080` | Native 8-byte shared result/local initialization |
| `0x0047F70E` | `0x0047B290` | `allocate_shared<EtamaArgInf, DebugAllocator<EtamaArgInf>>` |
| `0x0047F720` | `0x0040C300` | shared pointer `get` |
| `0x0047F72E` | `0x0047BD20` | `ShotParameters` constructor |
| `0x0047F7C9` | `0x004292E0` | Angle/clock scalar conversion |
| `0x0047F821` | `0x00485740` | `select_bullet_aim` |
| `0x0047F8EC` | `0x0040C300` | shared pointer `get` |
| `0x0047F8FE` | `0x0047C570` | PMR `vector<BulletCommand>` copy assignment |
| `0x0047F910` | `0x0040C300` | Context BulletController getter (folded getter head) |
| `0x0047F92A` | `0x0040B280` | `std::move` helper |
| `0x0047F935` | `0x0047B820` | `shared_ptr<EtamaArgInf>` move constructor |
| `0x0047F944` | `0x00481780` | `BulletController::fire` |
| `0x0047F970` | `0x0047C8F0` | conditional `Bullet::cancel` |
| `0x0047F97F` | `0x0047C300` | shared pointer destructor |
| `0x0047F994` | `0x0047C300` | shared pointer destructor |

### Command 18 — angle and speed transition

The 76-instruction original CFG has seven direct E8 calls. It restores the sentinel-based angle modes, the player-relative direction path, the original one-step wrap rules, the optional speed replacement, and the final `polar(velocity, angle, speed)` update. It advances the command cursor and returns to the parent loop.

Original E8 targets are checked at sites `0x004804B4 -> 0x0040FF90` (Timer current value), `0x004804CF -> 0x004FF350` (Player direction), `0x004804F6 -> 0x00438600` (angle addition), `0x0048050D/0x00480544 -> 0x00452F20` (Angle assignment), `0x0048058F -> 0x004292E0` (Angle/clock scalar conversion), and `0x004805C0 -> 0x00439330` (polar velocity update).

### Command 24 — construct and create an Enemy

The 53-instruction original CFG has three direct E8 calls. The handler constructs the real 84-byte `EnemySpawn`, copies the Bullet position, sets health to 10,000, copies all eight command payload words into the first eight `EnemyCounters` lanes, and calls `context->enemy_controller()->create(command.script, parameters, nullptr)`. The existing EnemySpawn constructor supplies the native zero initialization for the remaining fields and counters.

Original E8 sites are `0x00480A3D -> 0x0047BB30` (`EnemySpawn` constructor), `0x00480B16 -> 0x00412730` (Context EnemyController getter's folded physical head), and `0x00480B46 -> 0x004A8920` (`EnemyController::create`).

## Verification and limits

The focused pinned-MSVC x86 compilation of `src/BulletRunExtendedCommands.cpp` succeeds. The live original-PE verifier now checks the exact E8 site/target sets for commands 9, 13, 18, and 24, plus the complete 210 original E8 list, all three switch tables (34+8+11 = 53 PE HIGHLOW pointers), and all 38 body HIGHLOW fields.

A source-level parser verifies that the top-level `switch (command.opcode)` contains every primary case ID `0..33`; nested command-4 and command-9 cases are not used as substitutes for missing primary cases. This proves **34/34 primary ID coverage**, not original byte identity, gameplay equivalence for every malformed script input, whole-game link completeness, or full 12,140B acceptance.
