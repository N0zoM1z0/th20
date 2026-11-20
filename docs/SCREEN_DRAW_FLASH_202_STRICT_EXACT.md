# ScreenInf 202B flash draw — strict native reconstruction

The original callback at `0x00424FA0` is restored as natural C++ in `src/ScreenDrawFlash202.cpp`.

## Recovered behavior

- Uses the actual `WindowState` global at `0x005B6758` as the receiver for six native integer getter calls, preserving the original call order: X offset, playfield height, X offset, playfield width, playfield height, Y offset.
- Those calls reuse existing 17-byte physical getter heads at `0x0041CAD0`, `0x0041CAF0`, `0x00424010`, and `0x00421810`. Their historical owners are `Context::effect_info`, `FloatInterpolation::duration_value`, `Context::bomb_controller`, and `Player::animation_file_ref`; the Screen draw uses the same bodies as integer WindowState field getters.
- Converts the four returned integers to floats and constructs the contiguous rectangle `(offset_x, playfield_height, offset_x + playfield_width, playfield_height + offset_y)`.
- Packs `NativeScreenInf::alpha_18` into the top color byte and the low 24 bits of `field_24` into the remaining color bits.
- Submits the rectangle through the shared 1407B Graphics rectangle routine at `0x00423650`, then returns `1`.

## Exactness evidence

The canonical `screen_draw_flash_202` unit has passed scoped replay at **202/202 bytes (1/1 exact)** and verifies all fifteen original relocations: security cookie, six WindowState receiver references, six calls to the four shared getter heads, the rectangle submitter, and security-cookie check. The independent native audit pins the original SHA-256, all eight physical E8 targets, and all seven physical PE HIGHLOW fields.

The native `WindowState` field offsets are asserted in `WindowState.hpp`: playfield width `+0x18`, playfield height `+0x1C`, X offset `+0x20`, and Y offset `+0x24`. The 1407B Graphics rectangle routine remains a separate open reconstruction boundary. This callback does not claim to reconstruct that callee.
