# FrontInf dialogue command — 626B natural-C++ source frontier

The original FrontInf dialogue command at `0x004B9740` is now represented by
`NativeFrontInfDialogueCommandView::set_dialogue_command_4b9740` in
`src/FrontInfDialogueCommand626.cpp`. The view avoids changing the shared
`FrontInf` layout while using the observed borrowed fields: message
`AnimationFile*` at `+0x170` and current `Dialogue*` at `+0x1bc`.

## Recovered branches

- Commands `-1` and `-3` select one of two voice records, suppress a duplicate
  voice when two-player mode is active and the game is not restarting, queue
  the voice path, and spawn the corresponding message animation (`selector+1`).
  The 20-byte queued-track and message-file getters are strict exact. The
  104-byte voice helper is now a natural C++ source frontier and uses the
  reconstructed `SoundInf::enqueue` queue writer.
- Command `-2` selects one of two dialogue-finished transitions based on the
  Card extra-sound flag. The transition callees at `0x004BC570` and
  `0x004E5BD0` remain large open Boss functions and are represented as external
  view boundaries, not no-op stubs.
- Ordinary script commands release an existing Dialogue through the strict
  97-byte `0x004AE830` leaf and allocate a zeroed `0x140` Dialogue before its
  existing constructor. The new 156-byte allocator source at `0x004AE930` is
  natural C++ using nothrow allocation, zero initialization and placement
  construction; it remains NONEXACT and receives no strict parent credit.

The 626-byte FrontInf method remains **NONEXACT**. Its original class owner and
some stage/voice global view types are still provisional. The voice helper
retains explicit external boundaries for the preloaded-music predicate, stage
voice-flag storage and the original diagnostic string. No assembly or
synthetic padding is used.

## Opcode 518 integration

`EnemyState::execute_opcode` now routes opcode 518 through
`execute_enemy_dialogue_opcode`. The wrapper reads operand zero, invokes the
FrontInf command view, then clears the player-zero Bullet, Laser and Enemy
controllers in native order. The focused dispatcher verifier checks the
original compressed selector/pointer entry and the required E8 targets for
case 518. The 41,967-byte dispatcher parent remains NONEXACT.
