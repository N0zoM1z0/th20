# Graphics viewport layout and startup predicates (CLAUDE/EXACT-003)

Ten functions are strict exact, 5,778 credited bytes in total:

| Address | Size | Function | Source |
| --- | --- | --- | --- |
| `0x004DABA0` | 4,401 | `Graphics::initialize_viewports()` | `src/GraphicsViewports.cpp` |
| `0x004DDB20` | 1,113 | `Graphics::set_view_offset(x, y)` | `src/GraphicsViewports.cpp` |
| `0x004D9BC0` | 69 | `Graphics::stop_background_music()` | `src/GraphicsViewports.cpp` |
| `0x004DC0F0` | 37 | `Graphics::reset_view_selection()` | `src/GraphicsViewports.cpp` |
| `0x004DC120..0x004DC1A0` | 4 x 26 | text-detection, fog, vsync and DirectInput flag predicates | `src/GraphicsConfiguration.cpp` |
| `0x004DAB80` | 20 | `WindowState::reset_delay_value()` | `src/WindowLayout.cpp` |
| `0x004D9E70` | 34 | `WindowState::add_reset_delay(delta)` | `src/WindowLayout.cpp` |

## Viewport layout

`initialize_viewports` (single caller `0x004DD600`) builds the six
`ViewportState` records (stride `0x16C` from Graphics `+0x278`):

- `[2]` is the full scaled frame. It gets a zero eye/target, up `(0,1,0)`,
  `fov = pi / 6`, depth `0..1`, mode 2 and zero offsets.
- `[0]` is a copy of `[2]`: the centred 416x480 frame (`384+32`, `448+32`).
- `[1]` is the 384x448 playfield at `(128, 16) * scale`.
- `[4]` is the full frame at `[2]`'s offset.
- `[5]` is the playfield shifted by `[2]`'s offset. Its x offset adds half
  the playfield width. Its `width`/`height` fields also add the `[2]`
  offsets, as the native code does.
- `[3]` is the centred 416x480 frame computed from the float frame size.

Each record copies its pixel rectangle into `adjusted_viewport`. It then
converts the four unsigned fields to float clip bounds and calls
`recompute_current_4da1f0(state, &state->viewport)`. The repeated
unsigned-to-float bounds conversion is written as one local macro, which
expands to the same per-site temporaries and `__xmm@41f0...` correction
loads as the native code. `set_view_offset` (caller `0x004DBCE0`) updates
`[2]` without recomputing it, then re-places and recomputes `[5]` from the
new offset.

All placement constants stay unfolded under the strict profile, the same
behaviour seen in [the window layout](WINDOW_LAYOUT_RECONSTRUCTION.md).
Operand order matters for the `[5]` sums: the native code computes the
`viewports[2]` address before the float term, which requires
`viewports[2].offset_y + (int)(16 * scale)` rather than the reversed sum.
The reversed form has the same length but different instruction order and
relocation offsets.

## Small members

- The four configuration predicates are read by the configuration loader
  `0x004DC1C0` on the Graphics receiver: `flags` bits 6, 2, 5 and 3.
- `reset_view_selection` (caller `0x004DE1F0`) writes `field_b08 = -2` and
  `field_b0c = 0`.
- `stop_background_music` has eight menu and stage callers. It enqueues
  sound command 4 (preloaded music) or 3 with the `"dummy"` track
  (`0x00571B14`) and returns 0.
- The reset-delay accessors are WindowState members (`window_state` receiver
  at `0x004DC580..0x004DC5A0`). They are emitted in this Graphics object
  range, but they belong to WindowState.

## Replay

`Graphics.hpp` and `WindowState.hpp` changed again. The source-filtered
replay of the 90-source include closure passed 182 existing units. The new
`GraphicsViewports.cpp`, `GraphicsConfiguration.cpp` and `WindowLayout.cpp`
were then replayed explicitly: 4/4 and 20/20 exact.
