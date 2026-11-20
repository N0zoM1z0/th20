# Item reward-number queue — exact native owner and lookup

The 4757B ItemInf update and its four reward helpers publish floating score/power/life text through the selected player's Context `+0x1C` object. The native producer is now represented by a typed `ItemRewardPopupQueue` with an independently exact 255B enqueue method and the exact 26B indexed Session lookup.

## Native storage observed

- Context `+0x1C` points to the reward-number queue; `item_reward_popup_queue(index)` follows the original Session::context route and reuses the original shared `+0x1C` accessor head at `0x00421810` (also named `Player::animation_file_ref`).
- Queue cursor is at `+0x14` and wraps to zero when it reaches 10.
- Ten records begin at `+0x600`, each exactly `0x44` bytes.
- Record fields confirmed by original stores: decimal digit bytes at `+0x00`, Vector3 position at `+0x0C`, clock float at `+0x18`, color at `+0x1C`, Timer at `+0x20`, active byte at `+0x38`, digit count at `+0x39`.
- Unassigned storage remains named by offsets; no claim is made about its semantics.

## Exact source

`src/ItemRewardPopupQueue.cpp` reconstructs the native integer-to-digit loop, negative marker value 10, zero special case, Timer reset, position copy, clock value and cursor advance. The 255B body matches all 247 non-relocation bytes and both original relocation fields: Timer assignment at `+0xBD` to `0x00423520`, and the native 1.0 float at `+0xE1` to `0x0056C8CC`.

The indexed lookup at `0x004BD5A0` is 26/26 exact with all three original relocation roles: Session global, `Session::context`, and the shared `+0x1C` accessor head `0x00421810`. The latter is not counted twice; it remains the existing `Player::animation_file_ref` physical function.

This queue closes a real external dependency of the 307B/453B/523B/346B Item reward helpers and the 4757B ItemInf update parent. Those reward helpers and the parent remain independent open targets.
