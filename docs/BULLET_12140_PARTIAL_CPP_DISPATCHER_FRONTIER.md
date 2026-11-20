# CORE/RECON-1140 — first natural-C++ source frontier for the 12,140B Bullet command Boss

The original `Bullet::run_extended_commands()` at `0x0047DCF0` is now **SOURCE-PRESENT, PARTIAL, and NONEXACT** in `src/BulletRunExtendedCommands.cpp`. This is the first maintained C++ definition of the large dispatcher; it is deliberately not presented as a complete or byte-exact restoration.

## Current native command coverage

The original primary jump table has 34 command IDs (`0..33`). The maintained source currently has natural C++ control flow for 19 gameplay branches and the three original shared no-op/advance IDs:

| Native command IDs | Current source behavior |
| --- | --- |
| `0, 1, 2, 3` | Command-flag update, Timer/vector setup, animation interrupt, aim selection, polar vector initialization, and sound request |
| `5, 14, 28` | The three original IDs sharing the native no-op/advance tail |
| `6, 7` | Slot-4 trajectory parameters and Bullet scalar assignment |
| `10, 11, 12` | Bullet cancel, positional sound request, and slot-6 setup |
| `15, 16` | Native field assignment and repeat/jump counter behavior |
| `21` | Slot-10 speed interpolation and aimed polar vector |
| `25, 26` | Draw-group assignment and slot-13 timer activation |
| `29, 30, 31, 32, 33` | Radius/size selection, slot-5/slot-7 setup, slot-1 speed interpolation, and upper command-flag update |

That is **22/34 primary table entries represented**, including 19 nontrivial command handlers and the three original shared no-op cases. The 12 still-pending command handlers are `4, 8, 9, 13, 17, 18, 19, 20, 22, 23, 24, 27`.

The unsupported commands currently return without consuming the command. This is an explicit partial-source boundary, not original game behavior: it prevents the reconstruction from silently skipping commands whose state transitions are not yet restored. In particular, command 4's separate 8-way subtype table, command 9's 11-way selector, the ECL/Enemy creation path, and command 27's LaserType0/1 parameter construction remain open. Do not treat this source as playable or complete.

## Type and ABI evidence used

- The receiver is the actual `Bullet` instance, independently established by both strict original callers (`BulletController::emit` and `Bullet::update_physics`) and their identical native member symbol.
- The 24-command guard uses the real `Bullet+0x38` command cursor and `Bullet+0x98` shared metadata owner.
- `BulletCommand` is the real 44-byte record. Its eight payload words have float/signed-integer/raw-word aliases while opcode/flags/script remain at `+0x20/+0x24/+0x28`; the existing full 3,832-byte emitter COFF contribution and all 129 relocations remain identical after that overlay.
- The implementation uses existing typed `BulletExtendedCommands::at`, `Timer`, `Animation`, `Vector3`, `select_bullet_aim`, `polar`, `SoundInf`, and `bullet_radius` interfaces. No assembly, padding, fabricated native target, or duplicated object storage was added.

## Scoped verification and exactness boundary

The new source compiles as an i386 COFF object with the repository's pinned MSVC profile:

`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`

The separate strict canonical `bullet_emitter_whole_3735` object was freshly re-probed after the shared `BulletCommand` header overlay: its complete 3,832-byte contribution and all 129 relocation records are identical to `build/core645-canonical/BulletEmitter.obj`.

The original full dispatcher remains **NONEXACT**. Its 12,140 original body bytes, 38 body HIGHLOW fields, 210 E8 calls, and 53 switch-table HIGHLOW fields are not credited by this partial source. There is no canonical `match-units.toml` entry for the parent and no claim of whole-function exactness. The independent native closure verifier continues to account for all 210 original E8 sites, all 53 table pointers and all 38 in-body HIGHLOW fields.

Next reconstruction work is the pending complex handlers, prioritizing command 4's nested subtype switch and command 27's two real Laser parameter lifetimes, then the command-9 11-way selector and the ECL/Enemy branches.
