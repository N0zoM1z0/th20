# ScreenInf 105B fade draw — strict native reconstruction

The original callback at `0x00424F30` is now restored as natural C++ in `src/ScreenDrawFade105.cpp`.

It builds the native screen rectangle from `(0, 0)` to the two signed draw-extent globals at `0x005B87F8` and `0x005B87FC`, packs `NativeScreenInf::alpha_18` into the high color byte with `field_20` in the lower 24 bits, submits through the real 1407B Graphics rectangle helper at `0x00423650`, and returns `1`.

The canonical `screen_draw_fade_105` unit verifies all 105 bytes and all five original relocations: security cookie, both rectangle extents, Graphics rectangle submission and security-cookie check. The independent native audit pins the original SHA-256, both E8 destinations and all three physical HIGHLOW fields.

The shared 1407B Graphics rectangle helper remains a separate open reconstruction boundary.
