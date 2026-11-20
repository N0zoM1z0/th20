# CORE/RECON-1143 — natural-C++ source fragments for Enemy ECL Laser opcodes 702 and 703

The maintained source now contains `execute_enemy_laser_opcode(EnemyState&, opcode)` in `src/EnemyStateLaserOpcode.cpp` for the two original large Enemy ECL Laser branches. This helper is a source-organization fragment for eventual integration into `EnemyState::execute_opcode()`; it is **not** claimed to be a separate original native function, and it does not define or replace the 41,967-byte parent.

## Original native branch proof

The immutable Japanese TH20 1.00a Steamless PE (SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`) has the following original case entries:

| Opcode | Original case head | Reachable x86 heads | Direct E8 count | Constructor E8 | Destructor E8 |
| ---: | --- | ---: | ---: | --- | --- |
| 702 | `0x004944C7` | 153 | 15 | `0x004944CD -> 0x0047C130` LaserType0 | `0x00494766 -> 0x0047C4B0` LaserType0 |
| 703 | `0x00494771` | 176 | 16 | `0x00494777 -> 0x0047C030` LaserType1 | `0x00494A79 -> 0x0047C490` LaserType1 |

The original native verifier independently confirms the whole 41,967B/8,896-instruction Enemy parent, its 704-byte compact opcode selector, all 174 relocatable case pointers, and both bounded case CFGs. The cases reach the common parent epilogue without unresolved branch edges. The parent itself remains **NONEXACT and source-absent**.

## Maintained C++ behavior

Both branches use the real `EnemyState::writable_shot()` 396B copy-on-write selector, returning the actual `EnemyQueuedRecord*` and `ShotMetadata*` pair. They copy the record's PMR `BulletCommand` vector into a real Laser parameter object, use the record/metadata fields to construct the original position, angle, speed/length/width, duration, sound, flags and view index, then call the actual Context-owned `LaserController::create_laser()`.

- Opcode 702 creates `LaserType0Parameters`, preserves the 0.9 position/Z gate, normalizes the queued shot angle, copies the type-0 sound fields and ORs the native low flag bit `1`, then invokes Laser type `0`.
- Opcode 703 creates `LaserType1Parameters`, preserves the same position/Z gate, copies all four duration values, sound/alternate-sound, type/color and the native low flag bit `2`, then reads VM integer operand `1` late into the real `handle` field before invoking Laser type `1`.

The helper uses the already whole-exact LaserType0/1 constructors/destructors, writable queued-record selector, PMR vector copy assignment, Context LaserController accessor and 474B Laser factory. No private `select_queued_metadata_boundary` or `create_native_laser_boundary` remains in the maintained source. No assembly, manual padding, or invented original function body is used.

## Scoped verification and exactness limits

`src/EnemyStateLaserOpcode.cpp` compiles as i386 COFF under the pinned MSVC profile. Its relocations reference the real typed C++ owners above. The original native case audit was rerun with `.analysis/core716-enemy-41967-Laser-opcode-native-case-CFG.py`; it independently confirms 702's 153/15 and 703's 176/16 original instruction/E8 counts and the constructor/destructor sites.

This helper does not receive a `config/functions.csv` original-function mapping because the original 702/703 bodies are inline regions inside `EnemyState::execute_opcode()`, not independent native functions. The 41,967B parent still has no maintained complete body, no canonical whole-parent unit and zero parent byte credit. No full cold replay was performed.

Next work: add the original 711/713 Type2/Type3 Laser opcode fragments and then integrate all supported opcode helpers into a natural-C++ parent dispatcher without treating this fragment as the complete 41,967B function.
