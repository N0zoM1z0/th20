# CORE/RECON-1154 — natural-C++ Enemy opcode 551 and Stage/Fog owner boundary

The maintained source now contains `execute_enemy_fog_opcode(EnemyState&, opcode)` in `src/EnemyStateFogOpcode.cpp`. It restores original opcode 551 as a natural-C++ inline case fragment inside the **41,967-byte** `EnemyState::execute_opcode()` root and, importantly, replaces the previous opaque `0x005C069C` receiver with a typed partial production owner.

## Original Enemy opcode 551

The locked Japanese TH20 1.00a Steamless PE branch is `0x00495C1F..0x00495D20`: **257 bytes / 58 x86 instructions / 9 direct E8 calls**, SHA-256 `9d0a1a47670fbca33a9ba4ec3a3f90e8178448d6048d078e97a4feba569234d0`.

The exact VM evaluation order is:

1. Default-construct a real four-byte `PackedColor`.
2. Read integer operands 0, 1, 2 in order; assign the third raw word through `PackedColor::operator=(uint32_t)`.
3. Read float operands **4 then 3**.
4. Construct the real 28-byte `FogValue(near, far, blue, green, red, alpha)` using the four unsigned bytes of the packed word, low byte first.
5. Only after all five VM reads and FogValue construction, load the live process owner at `0x005C069C` and call its typed `set_fog` method.

The branch has no state-dependent shortcut or operand reordering. Earlier VM exceptions occur before the global owner is loaded or any fog state is changed.

## Recovered StageResource / Background / Fog layout

The global at `0x005C069C` is now represented by the existing neutral `StageResourceOwner* process_stage_resource`. Its original class spelling remains unproved, so the new `StageBackgroundFogOwner` name is explicitly a neutral layout description, not a claim about the game's source identifier.

The original 45-byte wrapper `0x0049C5B0` adds `0x10` to its `StageResourceOwner*` receiver and calls the 130-byte nested fog method `0x004776C0`. That method adds `0x134` to its receiver, giving the real `FogInterpolation` at **owner+0x144**. It also copies the stored current `FogValue` from nested receiver+`0x354`, i.e. **owner+0x364**. The separate accepted EnemyController animation-file selector calls `0x004AADF0`, whose 20-byte getter reads the real `AnimationFile*` at **owner+0x3334**.

The partial production layout therefore contains:

| Member | Owner offset | Size |
| --- | ---: | ---: |
| `background` nested state | `+0x10` | `0x370` |
| `background.fog_interpolation` | `+0x144` | `0xA4` (164B) |
| `background.current_fog` | `+0x364` | 28B |
| `animation_file_value` | `+0x3334` | 4B |

Unobserved bytes remain explicit `std::byte` spans. No unproven whole-owner size, constructor, startup, or destructor is claimed.

## Natural C++ restoration of all three owner methods

- `StageResourceOwner::animation_file()` returns `animation_file_value` and its pinned i386 object body matches all **20/20** original bytes at `0x004AADF0`.
- `StageResourceOwner::set_fog()` forwards through the real nested `background` subobject at `+0x10`; its body matches all **45/45** original non-relocation bytes at `0x0049C5B0` and preserves the native E8 to `0x004776C0`.
- `StageBackgroundFogOwner::set_fog()` updates the real `FogInterpolation` in original order: duration, mode, start from the stored current FogValue, end from the caller's FogValue, then reset Timer. Its body matches all **130/130** original non-relocation bytes at `0x004776C0` and preserves all five E8 calls.

The five real `Interpolation<FogValue>` leaf methods are also present in the existing canonical `Interpolation.cpp` object and independently match the original native bodies: set_duration **25B**, set_mode **28B**, set_start **30B**, set_end **33B**, and reset_timer **28B**. The final reset_timer E8 calls the already accepted `Timer::operator=(int)` at `0x00423520`. This preserves the original fields: it does not overwrite FogInterpolation's current value or either tangent.

## Scoped verification and exactness boundary

`src/StageResourceFog.cpp` and `src/EnemyStateFogOpcode.cpp` compile as i386 COFF under the pinned MSVC profile. `scripts/verify-enemy-fog-opcode-source.py` extracts the original 551 bytes directly from the locked PE, verifies all nine original E8 site/target pairs, checks VM order and packed channel order, validates all partial owner offsets, and compares all eight owner/interpolation method bodies against original PE bytes with only the four-byte COFF E8 displacement fields masked. The call targets are checked independently.

All eight restored owner/interpolation functions now have `matching` function rows and canonical match units. The three `StageResourceFog.cpp` methods replay **3/3 exact** in one fresh object. The five FogValue interpolation leaves were added to the existing `Interpolation.cpp` source provider; after its required header refresh, all **64/64 Interpolation units** replay exact in one fresh object. The pre-existing `BulletStyle.cpp` profile collision was resolved by moving the 17B accessor into `src/BulletStyleAccessor.cpp`; the two BulletStyle source providers replay **2/2 and 1/1 exact**.

This is a source and owner-boundary restoration, not a whole-root exactness claim. The 41,967B Enemy dispatcher remains **SOURCE-ABSENT as a complete parent and NONEXACT**. Only the affected StageResource, Interpolation and BulletStyle source providers were replayed; no full cold replay was performed.
