# AnimationPoolOwner draw-chain callbacks (CLAUDE/EXACT-004)

The AnimationPoolOwner constructor at `0x00447E00` registers 50 draw
callbacks and two update callbacks through `register_draw`/`register_update`
(push callback, push priority). Fifty-one of these callbacks, plus their
shared view reset, are strict exact in `src/AnimationPoolDrawCallbacks.cpp`:
52 functions and 875 credited bytes.

- `0x004508C0` (13B) forwards the pool to the fastcall
  `animation_renderer_update_secondary_449a70`.
- Forty-two 15B callbacks `0x004508D0..0x00450C60` each return
  `owner->select_renderer_group_449e40(N)` for one renderer group, with
  groups 0..55.
- Eight 26B callbacks (`0x00450A10`, `A50`, `A90`, `AC0`, `AF0`, `B40`,
  `B70`, `C10`) first call `clear_view_selection_44ee70()` on
  `current_animation_pool`, then classify their group.
- `0x0044EE70` (24B) writes -1 to the owner `+0x6C0` view selection, the
  same state that the exact 806B classification action sets to
  `view_index + 1`, 13 or 0.

The callback names keep their native addresses because the groups have no
recovered meaning yet. The first update callback `0x00450880` was already
exact.

## Replay

`NativeRendererClassificationOwner.hpp` gained one declaration. Its include
closure is three sources plus the new file: 55/55 exact units in four cold
objects.

## Next lead

The 2,794B constructor itself has an EH frame. It constructs the Worker at
`+4`, the resident Animation at `+0xDC`, the renderer lists at `+0x6C8`,
the AnimationPool at `+0x710` and the final Animation at `+0x6000818`, the
same members as the overlay in `src/AnimationPoolDestructor138.cpp`. It
needs that complete layout before it can be matched.
