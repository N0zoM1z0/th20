# TH20 `ItemInf::update_main()` reconstruction

## Current result

`src/ItemInfUpdateMain.cpp` now contains a natural C++ reconstruction of the
large ItemInf frame-update routine at `0x004C25A0`. It is tracked as
`th20::ItemInf::update_main` and marked `reconstructed`, not `matching`.
No original-byte, canonical-replay, or authored-origin credit is claimed.

The native body spans 4,757 bytes through the return at `0x004C3834`. Its
15-entry reward dispatch table begins at `0x004C3838`; the three-byte alignment
interval plus table makes the native code/alignment/table extent 4,820 bytes.
Ghidra reports 4,742 instruction addresses for the body; the independent
inventory notes 1,125 decoded instructions versus 1,122 attested Ghidra heads,
with three unconditional branch heads omitted from the decompiler listing.
The update iterates the active list backed by the 1,536-item pool and has 57
distinct direct callees.

## Reconstructed behavior

- Publishes the owning ItemInf view index, clears `special_count` and
  `processed`, and iterates the active intrusive list.
- Handles the delayed-activation state (5) and delayed-effect state (1),
  including the exact transition when the countdown reaches zero.
- Advances ballistic falling items (state 2), applies frame-clock gravity,
  changes them back to state 1 on the upward-to-downward transition, and
  retires items outside the native screen bounds.
- Implements forced attraction and the state-4 attraction path, including the
  bomb/dialogue gate, speed scaling, gravity, velocity clamping, and the
  player-chase state (3).
- Uses the native player collision radius and the separate ItemInf attraction
  center/radius; updates the ordinary proximity-attraction state only for
  eligible item states.
- Updates both animation handles only when `animation_draw_enabled` permits
  it, forwards the Item position to its attachment handle, increments the
  Item timer, and increments `processed`.
- Dispatches the `type - 1` reward switch to the native helper targets. In
  particular, case 0 calls `0x004C4B90` (`item_award_reward_type_0`), case 2
  calls `0x004C4DA0` (`item_award_reward_type_2`), and case 7 calls
  `0x004C47C0` (`item_award_life_reward`). Cases 1 and 14 share the type-1
  helper. Cases 3-6 update the four PlayerRecord progress channels; cases
  8-12 route through WeaponStoneInfo and the corresponding record channels.
  Case 13 takes the native default path. Successful pickups request effect
  `0x25` at the Item's x coordinate and retire the Item.
- Restores the ItemInf speed scale toward one, clears the attraction flag, and
  returns one after the list is exhausted.

## Native boundary and open exactness

The native inventory places the return at `0x004C3834`, followed by the
alignment bytes and the 15-entry table. The local MSVC `/Od` probe currently
produces a 4,840-byte COFF contribution (4,780 bytes before its 60-byte table),
20 bytes larger than the native 4,820-byte extent. Its stack frame is also
smaller because the source intentionally does not reproduce two unconsumed
local Vector3 bounds and a call to `Timer::at_least(0x20)` whose result is
ignored. Those native operations remain unresolved at the original-source
level; they are not added as inert statements merely to shape object bytes.

The candidate is therefore a semantic reconstruction, not an exact replay.
It is not admitted to `match-units.toml`, and no cold replay is run for this
function. The 57-callee audit cross-checks the source against the current
function inventory; the reward dispatch correction is based on the actual
native direct-call addresses rather than inferred reward names.

## Targeted validation

- `scripts/compile-probe.sh src/ItemInfUpdateMain.cpp ... /Od /Ob0 /GS ...`
  succeeds and emits an i386 COFF object.
- `scripts/validate-tracking.py --skip-target-bytes` passes after adding the
  source-presence and symbol-map entries.
- No full cold replay is claimed or run for this nonexact candidate.

## Next work

Continue expanding the Item update boundary through its remaining semantic
owners and tackle the adjacent WeaponStone progress-mesh update boss. The
unconsumed native locals, exact 20-byte code-layout delta, and whole-function
replay remain open rather than being hidden with padding or assembly.
