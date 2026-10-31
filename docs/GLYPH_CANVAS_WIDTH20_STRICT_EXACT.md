# CORE/RECON-1051 — native 20B glyph canvas width member, whole strict exact

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The genuine native `0x00415800` is a complete **20B/9-instruction**
GDI glyph canvas width accessor, whole-body original SHA-256
`97c6c65b5c5a98f6312636a1ebc9b041bdd6ee5342f3be907178f7afaa868936`.
It reads the real custom glyph resource owner's **`+0x104`
width field** into EAX and returns. No original E8 or PE HIGHLOW fields
occur within its physical body; the native final instruction is a
bare `ret`. It is a distinct physical method from the existing
20B HDC (`+0x114`), pixels (`+0x120`) and row stride (`+0x110`)
accessors, rather than a reused alias or a folded duplicate.

The original **2,245B/612-i386** glyph compositor at `0x00416420`
(SHA-256
`06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad`)
physically calls this exact head at four different original E8
positions: **`+0x307`, `+0x39A`, `+0x6E0`, `+0x797`**.
The complete original 2,245B compositor is independent and
**remains SOURCE-ABSENT/NONEXACT**. Its four genuine E8 caller
fields and the entire 20B getter are independently SHA-attested by
[`verify-glyph-canvas-width20-native.py`](../scripts/verify-glyph-canvas-width20-native.py).

The ordinary source in
[`GlyphCanvasEnsure104.cpp`](../src/GlyphCanvasEnsure104.cpp) now
implements the fourth native getter on the **existing** borrowed
[`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp)
using its true 32-bit field read, not a new owner or duplicated
renderer storage. Pinned MSVC 19.44 i386 C++20 naturally produces
**20/20 identical bytes**, with zero relocations. The shared
view-header include closure requires only four canonical objects:
this existing font view/format source, the previously exact 681B
GDI surface creator, the exact 82B format lookup and exact 182B
release. All eight affected strict units remain whole exact:

```text
glyph_canvas_format_fallback_104: exact (104/104 bytes)
glyph_canvas_device_context_20: exact (20/20 bytes)
glyph_canvas_bitmap_pixels_20: exact (20/20 bytes)
glyph_canvas_pixel_stride_20: exact (20/20 bytes)
glyph_canvas_width_20: exact (20/20 bytes)
glyph_pixel_format_lookup_82: exact (82/82 bytes)
glyph_canvas_release_182: exact (182/182 bytes)
glyph_canvas_create_681: exact (681/681 bytes)
Exact replay: 8/8 units, 4 cold objects
```

This is **one new game-authored native exact head /20 distinct
original `.text` bytes**. None of the seven already accepted physical
methods or the 2,245B caller is double-counted. No broad/cold
whole-graph replay was performed.

```sh
scripts/repo-python scripts/verify-glyph-canvas-width20-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasEnsure104.cpp \
  --source src/GlyphCanvasCreate681.cpp \
  --source src/GlyphCanvasFormatLookup82.cpp \
  --source src/GlyphCanvasRelease182.cpp
```

## CORE/RECON-1052 — original 2,245B glyph compositor now source-present

The native compositor invoking this exact width getter four times has
[maintained complete two-format glyph mask/outline source](GLYPH_MASK_COMPOSITE2245_NATIVE_AND_VECTOR_EXACT.md).
Its own complete code remains NONEXACT at 1,961B/536 source instructions
versus original 2,245B/612, while four nested PMR-vector methods are
independently whole exact. The original 20B width source and prior
strict credit remain unchanged after the shared-view local replay.
