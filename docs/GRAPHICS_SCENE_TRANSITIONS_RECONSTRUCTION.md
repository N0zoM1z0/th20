# Graphics scene transitions and update node (CLAUDE/EXACT-007)

Four functions from `game/mother.cpp` are strict exact, 1,873 credited
bytes:

| Address | Size | Function | Source |
| --- | --- | --- | --- |
| `0x004DA540` | 1,402 (+125 table/pad bytes) | `Graphics::update_scene_4da540()` | `src/GraphicsScenes.cpp` |
| `0x004DD730` | 234 | `Graphics::release_scenes_4dd730()` | `src/GraphicsScenes.cpp` |
| `0x004DC510` | 218 | `graphics_update_4dc510` (Graphics chain update node) | `src/GraphicsScenes.cpp` |
| `0x004DC180` | 19 | `Worker::joinable() const` | `src/GraphicsScenes.cpp` |

## Scene state machine

`field_b08` is the current scene, `field_b0c` the requested scene and
`field_b10` the previous scene. When they differ, the update takes lock
slot 5 and logs `scene %d -> %d\r\n`. It resets the clear colour, then
switches on the requested scene:

- 0 creates the title scene into `startup_scene` and requests scene 1. On
  failure it requests 3 and jumps to the shared quit path.
- 4 and 16 start the stage scene after releasing what the previous scene
  owned. Scene 16 also forces stage entry mode 3 and continues as scene 4.
- 7, 10..14, 19, 22 and 24 recreate the GameController in restart mode 0 or
  1, or in the mode returned by `GameController::restart()` for scene 12.
  They set `field_b18`/`field_b1c` and, for several scenes, reselect the
  PlayerTable card table. All of them continue as scene 7.
- 15 starts the ending scene. 3 and 17 release every scene owner and return
  4 or 5. Every other path stores the requested scene and returns 1.

`release_scenes_4dd730` clears Session flags 0/1 and marks Graphics shutdown
(`flags.bits5_6 = 1`) if no state is set yet. It then releases eleven scene
task owners and the GameController.

The update node asks for scene 3 once shutdown is pending and the Graphics
worker is no longer joinable. It then steps sound and input, returns 4 when
the AnimationPool asks to stop, and decrements the device-reset delay. While
`field_db0` is set (2 means stop) it skips scene changes; otherwise it applies
them.

## Source shape

- The 25-value outer switch (byte index plus 16 targets) and the 15-value
  scene-4 switch reproduce the native tables. Case bodies follow source
  order 0, 4, 16, 7, 13, 12, 10, 24, 22, 11, 19, 14, 15, 3, 17.
- Case 0 jumps to the case-3 body, which carries a `release_and_quit:` label.
  In scene 16, case 15 falls through into case 2.
- Single-label `switch (field_b08) { case 4: ... }` statements reproduce the
  native copy-and-compare. Each `return` inside the guarded scope stores
  through its own temporary before the guard destructor runs.
- In the update node, the second `reset_delay_value()` call has no
  following `nop`. Only the form
  `if (window_state.reset_delay_value(), field_db0 != 0)` reproduces this;
  `(void)` casts and discarded comparisons keep the `nop`.

Unmatched callees (title/stage/ending factories, GameController
create/destroy, the scene release helper `0x004217C0`, two PlayerTable
members and the Sound/Input/AnimationPool per-frame members) are declared
by their native entry points. Local overlay views avoid changing their
shared headers.

## Replay

`Graphics.hpp` (three members) and `Worker.hpp` (`joinable`) changed. A
source-filtered replay of their 93-source include closure, including the new
`GraphicsScenes.cpp`, gives 225/225 exact units in 93 cold objects.
