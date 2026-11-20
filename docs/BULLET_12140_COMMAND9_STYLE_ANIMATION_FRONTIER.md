# CORE/RECON-1141 — native Bullet command 9: style selection, Animation reload, and alternate Enemy file route

The partial natural-C++ dispatcher in `src/BulletRunExtendedCommands.cpp` now includes original primary opcode **9**. This is a new maintained branch in the 12,140-byte `Bullet::run_extended_commands()` Boss; the enclosing function remains **SOURCE-PRESENT, PARTIAL, NONEXACT** and receives no original parent byte credit.

## Original command-9 behavior recovered

The original primary case head is `0x0047F194` (the following primary case-10 head is `0x0047F691`); its bounded CFG reaches 267 original x86 instructions and 14 direct E8 calls. The nested 11-way style policy dispatch is at `0x0047F48A`, backed by the original table at `0x00480D04`. Its two paths are selected by bit `0x8000` of operand word `+0x10`.

### Normal BulletStyle path (`operand_10 & 0x8000 == 0`)

- Stores the type and low-15-bit color into the actual signed-short `Bullet+0x4C/+0x4E` fields.
- Reads the real `BulletStyle[50]` record at its `0x158` stride: radius, draw group, child script, and cancel-type policy.
- Updates both components of `Bullet::size` from the original `bullet_radius(type)` accessor and copies the style draw-group value.
- Resets the existing Animation, installs the original `bullet_animation_script` callback in `Animation+0x5E0`, publishes the Bullet pointer in `Animation+0x5C8`, resolves the type's script with `type_to_script`, and loads it through the owning Context's BulletController AnimationFile.
- Sets the Bullet flag and Animation viewport mode, retires the prior child `AnimationHandle`, and conditionally spawns the style's child script through the real AnimationFile `spawn` method.
- Reproduces all eleven `BulletStyle::cancel_type` values (`0..10`): color-derived script IDs, the 8-entry color map, the 16-entry style color-word table, fixed IDs, and the native flag updates.
- Uses the original `interrupt_animation_mode2` helper when operand `+0x14` has bit `0x8000` set.

### Alternate Enemy AnimationFile path (`operand_10 & 0x8000 != 0`)

- Resets the existing Animation.
- Resolves `Context::enemy_controller()`, selects its AnimationFile using the low 15 bits of operand `+0x10`, and loads the script selected by the low 15 bits of operand `+0x14`.
- Applies the same original Animation viewport mode after loading.

Both paths advance the real `Bullet+0x38` command cursor exactly once before returning to the parent interpreter.

## Original E8 call-site proof

The immutable original PE has these 14 direct calls in the command-9 CFG; their site and destination pairs are checked by the updated live command-coverage verifier:

| Original E8 site | Original destination | Maintained C++ role |
| --- | --- | --- |
| `0x0047F1B1` | `0x004299D0` | `Animation::reset` (alternate Enemy route) |
| `0x0047F1C2` | `0x00412730` | Context EnemyController getter's physical folded getter head |
| `0x0047F1EF` | `0x004AAE10` | `EnemyController::animation_file` |
| `0x0047F232` | `0x004383A0` | `AnimationFile::load_script` (alternate route) |
| `0x0047F297` | `0x00485700` | `bullet_radius` |
| `0x0047F2F6` | `0x004299D0` | `Animation::reset` (BulletStyle route) |
| `0x0047F315` | `0x00438A30` | `Animation::set_field_5e0` |
| `0x0047F33B` | `0x0040C300` | Context BulletController getter |
| `0x0047F356` | `0x004856C0` | `type_to_script` |
| `0x0047F387` | `0x004383A0` | `AnimationFile::load_script` (BulletStyle route) |
| `0x0047F3CC` | `0x0044FCD0` | `AnimationHandle::retire` |
| `0x0047F3F4` | `0x0040C300` | Context BulletController getter for child spawn |
| `0x0047F44B` | `0x004790E0` | `AnimationFile::spawn` with hidden `AnimationHandle` result |
| `0x0047F671` | `0x00486330` | `interrupt_animation_mode2` |

## Existing typed native boundaries reused

The new branch deliberately calls maintained C++ owners instead of reproducing their machine code:

- `Animation::reset` — original 1,106B method.
- `Animation::set_field_5e0` — original 25B callback-slot setter.
- `bullet_animation_script` — existing original Bullet callback.
- `type_to_script` — original 18B BulletStyle accessor.
- `AnimationFile::load_script` — original 338B script loader.
- `AnimationHandle::retire` — original 37B handle-retirement leaf.
- `AnimationFile::spawn` — original 61B spawn boundary and genuine hidden-result `AnimationHandle` return.
- `interrupt_animation_mode2` — original 22B mode-2 animation helper.
- `Context::enemy_controller` and `EnemyController::animation_file` — existing typed Enemy-owner route.

The command-9 C++ object was freshly compiled as i386 COFF under the pinned MSVC profile. Its relocations name the actual typed helper symbols above, including the hidden-result AnimationFile spawn, and the 11-way style switch is ordinary C++ `switch` code. No assembly, manual jump table, fake padding, or duplicate helper body was introduced.

## Exactness boundary

This source represents the two command-9 paths semantically; it does not claim the 470-byte original branch or the 12,140-byte parent is byte-exact. The whole parent still has no canonical match unit, and all original 12,140 body bytes remain uncredited. The independent original-PE verifier continues to account for 210/210 E8 sites, 53/53 switch-table HIGHLOW fields, and 38/38 body HIGHLOW fields.

The current primary dispatch coverage is **25/34 entries** (22 gameplay handlers plus the three original shared no-op entries). The nine still-pending primary IDs are `8, 13, 17, 18, 19, 20, 22, 23, 24`.
