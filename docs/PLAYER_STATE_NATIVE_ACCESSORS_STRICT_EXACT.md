# Player state dependencies: complete native helpers and return ABI

The maintained Player state frame now has thirteen new exact physical helper
units. Their complete native extents total 915B. Twelve game-specific
methods contribute 847 authored bytes; the 68B generic Angle method remains
under origin review. The parent at `0x004F7430` is source-present and still
NONEXACT because its independent relocation bindings are incomplete.

The target is Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Source is [PlayerStateNativeAccessors.cpp](../src/PlayerStateNativeAccessors.cpp).
The locked MSVC 19.44.35211 x86 profile is C++20, `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`. Each unit in `config/match-units.toml`
compares its entire code contribution and all canonical relocations.

| Address | Method | Complete bytes |
| --- | --- | ---: |
| `0x004F86C0` | `Player::revive_after_bomb` | 38 |
| `0x004FF3F0` | `Player::direction_from` | 157 |
| `0x004FFD80` | `Player::set_position_xy` | 136 |
| `0x004FF820` | `Player::entity_flag5` | 23 |
| `0x004FF610` | `Player::motion_scale_value` | 20 |
| `0x004FFEE0` | `Player::set_extra_motion` | 40 |
| `0x004AB2E0` | `GameController::flag_19_set` | 26 |
| `0x004B58E0` | `InputButtonState::replay_pressed_bits` | 25 |
| `0x004E1680` | `PlayerRecord::consume_power` | 130 |
| `0x004BD410` | `PlayerRecord::clamped_field_d4` | 73 |
| `0x004E15E0` | `PlayerRecord::set_field_cc_clamped` | 154 |
| `0x004FF710` | `Angle::to_vector` | 68 |
| `0x004AB610` | `Animation::set_secondary_color` | 25 |

## The power method returns a full integer

Ghidra's inferred `bool` for `PlayerRecord::consume_power` is misleading.
The original 130B method returns through full EAX: its early return uses
`xor eax,eax`, and its final load uses `mov eax,[ebp-8]`. A natural `bool`
candidate has the same length but emits `xor al,al` and `mov al,[ebp-8]`,
leaving two differing opcode bytes. Declaring and defining `std::int32_t`
recovers the entire body. The logical result is still zero or one.

The original first checks `field_30 <= field_38`, subtracts the requested
amount, clamps to `field_38`, and compares the integer quotients before and
after subtraction. An initial outer-conditional spelling added a jump and
was rejected. Keep the native early return and signed division sequence.

The 154B record setter also requires its original comparison order:
`field_cc > clamped_field_d8()`. Reversing the equivalent comparison changes
two instruction bytes. The method clamps negative values first, re-queries
the maximum on assignment and prepares all three progress arguments before
updating the current FrontInf.

## Ownership and independent bindings

The Player methods access its actual state, fixed/world positions, entity
flags and extra-motion fields. The record methods implement power and HUD
progress rules; the input method reads the replay-pressed mask; the game
predicate and Animation setter access their established game layouts. Their
native caller is the recovered Player state frame. These game-specific
protocols establish authored origin separately from compiler matching.
`Angle::to_vector` is a generic polar conversion with an optional offset;
its matching source does not establish historical authorship.

Call/data destinations come from existing canonical Timer, Player position,
option setter, scalar math, clamp, record getter, FrontInf, polar and Vector3
units and their anchors. The private replay binds the 22B Player state setter
at `0x00412DA0` to an already owned FunctionChain setter head. It receives no
second physical unit, mapping or byte credit.

Feedback update returns `void`; shot-controller update returns an integer.
These declarations preserve the native caller's return handling. Bomb start,
death entry, Identifier32 damage-flag, feedback and shot implementations
remain separate reconstruction work.

## Reproducible products and bounded validation

The thirteen public canonical comparisons pass from the fresh
`build/gpt61-player-state-canonical/PlayerStateNativeAccessors.obj` and its
receipt. The complete parent also compiles there as
`PlayerStateFrame4043.obj`: its 4,072B contribution matches the corrected
private candidate, including relocation roles and local-label destinations.
All 3,256 nonrelocation bytes match the original. The parent has no canonical
unit; see [its remaining binding frontier](PLAYER_STATE4043_NATIVE_FRONTIER.md).

Nine changed declaration headers expand the captured include closure to
1,146 existing exact units from 313 source providers. All 1,146 units passed using only those source
filters; their objects and receipts are in the fresh canonical directory. Old canonical products remain unchanged. The thirteen
new helpers add one provider to this scope.

Private evidence is retained in `.analysis/player-state4043-abi/`:
`helpers-proof`, `helpers-refined-proof` and `helpers-abi-proof` preserve the
failed and successful whole-helper comparisons; `accessors-bool-return.cpp`
retains the negative ABI control. `public-accessors-proof.txt` records all
thirteen canonical passes, and `public-frame-proof.txt` records the complete
parent diagnostic. `affected-before.json`, `replay-sources.json` and
`affected-replay.txt` capture the exact affected scope and replay;
`protected-before.json` records the preserved target and old products.
Earlier attested native queries remain in `.analysis/player-state4043-session/`.
