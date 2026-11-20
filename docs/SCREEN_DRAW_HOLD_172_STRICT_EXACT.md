# ScreenInf 172B hold draw — strict native reconstruction

The original callback at `0x00424E80` is restored as natural C++ in `src/ScreenDrawHold172.cpp`.

## Recovered behavior

- Reads the ScreenInf per-view slot into the native local draw record.
- Builds the hold rectangle from the original float constants: `(640 - 384) / 2` for the left edge, `16` for the top, the same centered offset plus `384` for the right edge, and `16 + 448` for the bottom. This gives the centered playfield rectangle `(128, 16)–(512, 464)`.
- Packs `NativeScreenInf::alpha_18` into the high color byte with `field_20` in the lower 24 bits.
- Submits the rectangle through the real 1407B Graphics rectangle helper at `0x00423650`, then returns `1`.

## Exactness evidence

The canonical `screen_draw_hold_172` unit verifies all 172 bytes and all thirteen original relocations: security cookie, five distinct float constants with their repeated references, the Graphics rectangle submitter, and security-cookie check. The independent native audit pins the original SHA-256, both E8 destinations and all eleven physical PE HIGHLOW fields.

The 1407B Graphics rectangle helper remains a separate open reconstruction boundary.
