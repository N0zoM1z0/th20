# WindowState screen layout (CLAUDE/EXACT-001)

`WindowState::compute_layout` at `0x0041E050` (1,819B) and eleven WindowState
setters from `0x0041DE50` to `0x0041E030` are strict exact in
`src/WindowLayout.cpp`. Together they contribute 2,088 newly credited bytes.

## What the routine does

The native routine selects the client size and render scale from
`window_state.display_mode()`:

- Modes 9 and 8 copy the desktop size (`+0x20B0/+0x20B4`) into the client
  size. With the argument set, the routine selects scale 2.0, 1.5 or 1.0 by
  desktop thresholds (2560x1920, 1920x1440, 1280x960, 960x720). It also writes
  levels 4..0 to `process_graphics.configuration.scale_choice` (`0x005C4F8A`,
  Graphics `+0x1C8` + Configuration `+0x82`). Mode 9 stretches the viewport to
  the desktop aspect. Mode 8 grows the frame in half-frame steps.
- Modes 7, 6, 2/5 and 1/4 select fixed client sizes. All other modes select
  640x480 at scale 1.0.

The routine then writes the 640x480 nominal frame and the 384x448 playfield,
along with the centred offsets and the per-view tables at `+0x28..+0x64`,
through its receiver. Scaling fields are read and written through the global
`window_state` (DIR32 base `0x005B6758` + field addend), not through `this`.
Both native callers pass a WindowState: `0x0041CE7D` passes a local
WindowState pointer and `0x0041EC6C` passes `window_state`. The mode 8
narrow branch scales the viewport width from `scaled_height` and reuses the
previous `viewport_height`. Both reads are native, so the source keeps them.

## Compiler evidence

- `/fp:precise` folds `(640.0f - 384.0f) / 2.0f + 384.0f / 2.0f` to
  `add eax, 0x140` and produces a 1,729B body. `/fp:strict` keeps the native
  `movss/subss/divss/addss` sequence and the register rotation that follows,
  which gives the exact 1,819B. The unit uses the common strict profile
  `/GS /sdl /EHsc /fp:strict`.
- Named `float` locals are needed for the eight spilled ratios
  (`[ebp-0x10]..[ebp-0x24]`). The two snapping loops are `while` loops.

## Folded accessors

The receiver calls ten physical bodies that are already credited under other
class names: `0x00411700`, `0x0041CA90`, `0x0041CAD0`, `0x0041CAF0`,
`0x00412DA0`, `0x0041DE70`, `0x0041DE90`, `0x0041DF30`, `0x0041DF50` and
`0x0041DFB0`. The new WindowState methods compile to identical bytes. They were
strict-exact against those addresses during this replay, but were not kept as
units, because overlapping extents are rejected and the bytes are already
credited. The layout unit binds its REL32s to those addresses.

The eleven setters newly credited here have no earlier alias: `+0x14`, the
indexed `+0x28/+0x30/+0x38/+0x40/+0x48/+0x50` pairs, `+0x5C`, `+0x60`,
`+0x64` and `display_mode_value` (`+0x208C`). `WindowState::Pair` became
`std::int32_t[2]`, because the native setters index those members.

## Replay

The `WindowState.hpp` change affects 31 providers in its include closure. A
source-filtered replay of those providers gives 97/97 exact units in 31 cold
objects.

## Next leads

- `0x0041CCF0` (905B) is a caller in the same object that initializes a
  WindowState (`+0x2100`), calls `set_display_mode` and calls the layout with
  argument 1.
- `0x0041E7D0` (2,537B) is the startup caller that passes `window_state`.
- `0x0041E770` (17B) is a free cdecl forwarder to `0x00541562`.
