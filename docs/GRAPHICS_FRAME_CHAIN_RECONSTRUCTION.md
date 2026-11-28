# Graphics frame chain: registration, start-up and frame clears (CLAUDE/EXACT-005)

The Graphics owner's original TU is `game/mother.cpp`: the start-up
allocation labels read `D:\cygwin\home\zun\prog\th20\src\game\mother.cpp:233
SprtInf` through `:237`, and the shutdown log says `shutdown MotherInf`.
Ten functions from that TU are strict exact in `src/GraphicsPasses.cpp`,
2,373 credited bytes in total:

| Address | Size | Function |
| --- | --- | --- |
| `0x004DE1F0` | 359 | `register_graphics_chain()` |
| `0x004DD600` | 300 | `graphics_startup_4dd600` (node before-insert callback) |
| `0x004DC5F0` | 449 | `graphics_begin_frame_4dc5f0` (draw priority 1) |
| `0x004DD1C0` | 275 | `graphics_clear_scene_depth_4dd1c0` (priority 25) |
| `0x004DD2E0` | 275 | `graphics_clear_overlay_depth_4dd2e0` (priority 47) |
| `0x004DD400` | 135 | `graphics_select_backbuffer_4dd400` (priority 66) |
| `0x004DC7C0` | 240 | `graphics_clear_view_points_4dc7c0` (priority 110) |
| `0x004D9EA0` | 187 | `load_version_data()` |
| `0x004DBCE0` | 132 | `Graphics::apply_render_offset()` |
| `0x004DD820` | 21 | pool `+0x6000E12` layer-marker reset |

## Behaviour

`register_graphics_chain` resets the view selection and clears
`field_b14`. It creates the update node for `0x004DC510` with the Graphics
userdata and the start-up callback, then inserts it at priority 1, returning
any nonzero insert result. It registers ten draw callbacks at priorities
1, 14, 15, 25, 26, 47, 48, 66, 67 and 110, and finally fetches back buffer 0
into `resource_1a4` with `GetBackBuffer`. The remaining five draw
callbacks are exact under EXACT-006 below, and the update node `0x004DC510`
under EXACT-007 ([scene transitions](GRAPHICS_SCENE_TRANSITIONS_RECONSTRUCTION.md)).

Start-up loads `th20_0100a.ver` from `th20.dat`. It then sets the default
clock to 1.0 and the clear colour to opaque black, builds the viewports and
centres the frame. It seeds `script_random` and the streams at `0x005BA4C4`,
`0x005BA4E0` and `0x005BA4FC` with `t`, `t`, `t >> 1` and `t / 3` from
`timeGetTime()`. It also runs the two factories `0x004AC1A0`/`0x00422B00`
and the pool loader `0x0044D020`, allocates the five surface sprites and
clears both draw hooks at `0x005C4D30`/`0x005C4D34`.

The frame-start callback clears the offscreen target (`resource_19c`) to
white when present, binds it, and reports `error SetRenderTarget` on failure.
It then clears to `clear_color` and resets the AnimationPool per-frame render
state.

## Compiler evidence

- D3D9 calls through `process_graphics.get_device()` reproduce the native
  device and function-pointer temporaries without extra source locals.
- The `nop` after `node->enable()` appears only when the following
  statement is the `if`: `if ((result = process_chain->insert_update(node, 1)) != 0)`.
  A separate `result = ...; if (result != 0)` drops the `nop`. In every
  matched function so far, a call is followed by `nop` exactly when the next
  statement starts a control construct or closes a block.
- The two Shift-JIS diagnostics are written as hex-escaped narrow literals,
  with the Japanese text kept in comments.
- `sprintf_s` binds to the CRT inline at `0x0041F220`. That body calls the
  already reconstructed `__vsprintf_s_l` at `0x0041F1D0`.

## Replay

`Graphics.hpp` (one member) and `NativeRendererClassificationOwner.hpp` (two
members) changed. A source-filtered replay of the 94-source closure,
including the new `GraphicsPasses.cpp`, gives 256/256 exact units in 94
cold objects.

## World compositor and surface passes (CLAUDE/EXACT-006)

Six more functions are strict exact in the same source, 3,201 bytes:

- `0x004DC8B0` (2,307B, draw priority 14) composites the world target onto
  viewport 3's 416x480 frame. It sets render state `0x17 = 8`, separate alpha
  blending (colour ZERO/ONE, alpha ONE/ZERO) and selects the diffuse
  texture-stage arguments. It then draws a four-vertex opaque-black
  `SpriteColoredVertex` strip (`FVF 0x44`, `DrawPrimitiveUP` triangle strip),
  restores the stages and alpha blend, binds `resource_1a0` and clears it.
  The `D3DRECT` built before that clear is not passed to it (`Clear(0, NULL, ...)`).
- `0x004D9120`/`0x004D8E90` (scene/overlay) draw surface sprites 0 and 1
  unless the `0x005C4D30`/`0x005C4D34` hook is set. The scene pass also
  classifies renderer group `0x29`.
- `0x004D8F80` draws sprite 2. `0x004D9040` draws sprite 3 in view modes 7
  and 12 and sprite 4 otherwise, after classifying group `0x1F`.
- `0x0044C570` (26B) is the Animation member `return
  current_animation_pool->draw(this)`, with 16 native callers. It sits on a
  local `NativeSurfaceSprite` overlay so that Animation.hpp (a 186-source
  closure) stays unchanged. It can move into Animation once that header
  changes for another reason.

`nop` placement settled the scopes. Opening a block also puts a `nop` after
the preceding call, so the native compositor has a scope around its final
flush, retarget, rectangle and clear, and none around the vertex array. The
`int` return of `submit_draw_44c570` avoids the trailing `nop` that a `void`
wrapper emits. The source-filtered replay of `GraphicsPasses.cpp` gives
16/16 exact units. No shared header changed.
