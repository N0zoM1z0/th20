# `WeaponStoneInfo::update_main()` reconstruction

## Native boundary

The native method at `0x00532B20` is 1,018 bytes (`0x00532B20..0x00532F19`).
The ECX receiver is the actual `WeaponStoneInfo` owner: the body accesses its
phase (`+0x54`), four weapon strategy pointers (`+0x28..+0x34`), animation
handle (`+0x20`), animation file (`+0x24`), radius (`+0x74`), and two Timers
(`+0x10`, `+0x64`). The Ghidra prototype had lost the receiver; the native
instructions and the caller establish a thiscall member.

## Reconstructed state machine

1. If the current GameController has flag bit 6 and a phase is active, interrupt
   and clear the phase animation handle, set phase to zero, and call the main
   weapon's `end_phase()` virtual.
2. Gate on the current GameController update-node enable state and the current
   FrontInf dialogue state. If the gate is closed, a live dialogue retires the
   animation handle and calls `cancel_phase()`; otherwise return 1 without
   advancing the phase state.
3. Initialize the cancellation policy from the player mode: modes 5 and 7 do
   not perform radial cancellation. For phase 2, call `end_phase()`: a true
   result transitions to phase 1; a false result selects radius 128 and a
   60-frame cancellation window when permitted, then completes the phase.
4. For phase 1, validate the aura handle. If absent, spawn the native `aura`
   animation from the owner's AnimationFile at script 29 and the current player
   position. Forward the current player position to the live handle, then call
   `update_phase()`. A false result leaves phase 1 active. A true result calls
   `end_phase()`, disables cancellation for mode 6, selects a four-frame window
   when still permitted, selects radius 24, and completes the phase.
5. Phase completion interrupts and clears the handle, resets phase to zero,
   invokes the 581-byte `initialize_phase_effect()` reconstruction, and resets
   PlayerRecord field `+0x4c` through the existing setter.
6. While the cancellation Timer is positive and the mode permits it, cancel
   nearby bullets using `BulletController::cancel_near_limited`, cancel nearby
   lasers using the reconstructed `LaserController::cancel_near`, then
   decrement the Timer.
7. Update the four weapon strategies through their real virtual slots in
   order: `update_main`, `update_focused`, `update_unfocused`, and
   `update_passive`. Increment the frame Timer and return 1.

The GameController gate now calls the independently exact 56-byte
`GameController::update_node_enabled()` wrapper; its 22-byte
`FunctionChainNode::enabled()` leaf is also independently exact. The two
Weapon virtual phase slots and four final strategy slots remain genuine virtual
dispatches, not calls to guessed concrete implementations.

## Exactness status

The natural `/Od /Ob0 /GS /sdl` i386 COFF contribution is 1,016 bytes versus the
1,018-byte native function. It is tracked as `reconstructed`, not `matching`.
The two-byte difference is left visible; no NOP, padding, inert statement, or
assembly is added. The source compiles as i386 COFF. The exact GameController
helpers were replayed separately; the main function itself is not admitted to
`match-units.toml` and no full cold replay was run for this nonexact candidate.

## Related boundaries

- `WeaponStoneInfo::initialize_phase_effect()` — 581-byte native boundary,
  574-byte natural C++ candidate.
- `WeaponStoneInfo::update_progress_mesh()` — 1,780-byte native boundary,
  1,223-byte natural C++ candidate.
- `LaserController::cancel_near()` — 288-byte native boundary,
  281-byte natural C++ candidate.
- `GameController::update_node_enabled()` — 56/56 exact.
- `FunctionChainNode::enabled()` — 22/22 exact.
