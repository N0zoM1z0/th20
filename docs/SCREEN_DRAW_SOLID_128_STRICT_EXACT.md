# ScreenInf 128B solid draw — strict native reconstruction

The original draw callback at `0x00424E00` is now reconstructed as natural C++ in `src/ScreenDrawSolid128.cpp`.

## Recovered behavior

- Builds the solid rectangle from `(0, 0)` to the two native signed draw-extent values at `0x005B87F8` and `0x005B87FC`.
- Flushes the actual `AnimationPoolOwner` draw queue before changing the Graphics clip.
- Uses the real `Graphics` object at `0x005C4D40` and its original `NativeGraphicsModeAction::set_clip_41dce0(2)` boundary.
- Draws the rectangle through the 1407B Graphics rectangle submission helper at `0x00423650`, using `(NativeScreenInf::alpha_18 << 24) | NativeScreenInf::field_20` as the packed color.
- Returns native status `1` after the draw.

## Exactness evidence

The canonical `screen_draw_solid_128` unit verifies the complete 128-byte function and all nine original relocations: security cookie, two draw extents, animation pool, pool flush, Graphics owner, clip setter, rectangle submitter and security-cookie check. `scripts/verify-screen-draw-solid128-native.py` independently pins the original SHA-256, all four E8 destinations and all five physical PE HIGHLOW targets.

The called `0x00423650` rectangle submission routine is a separate 1407-byte Graphics boundary and remains open; this callback only declares its native ABI and does not claim to reconstruct that large callee.
