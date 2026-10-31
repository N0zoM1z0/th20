# CORE/RECON-1043 — three whole-exact 20-byte GDI glyph canvas field accessors

Locked target: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original glyph canvas is a custom game-specific 0x124-byte resource
owner. Its original 681B initializer `0x00415120` creates actual Win32
bitmap/DC data; the enclosing original **2,227B glyph text Boss** at
`0x00415830` and **2,245B compositor** at `0x00416420` use its fields
through these **three distinct complete physical getters**:

| Native original head | Complete body | Actual source owner field | Original caller |
| --- | ---: | --- | --- |
| `0x00415620` | **20B/9 i386** | device context pointer at glyph receiver `+0x114` | original 2,227B core E8 `+0x36D` |
| `0x004156A0` | **20B/9 i386** | bitmap pixel byte pointer at `+0x120` | original 2,245B compositor E8 `+0x44` |
| `0x004156C0` | **20B/9 i386** | bitmap row stride int32 at `+0x110` | original 2,245B compositor **nine** E8 sites `+0x32`, `+0x197`, `+0x1D7`, `+0x5A6`, `+0x5E7`, `+0x69B`, `+0x6FA`, `+0x752`, `+0x7B4` |

Each full native body is exactly **nine instructions, a true bare `ret`,
zero E8 and zero PE HIGHLOW**. The only per-member machine-code
difference is the genuine observed field displacement `+0x114`,
`+0x120` or `+0x110`; the physical function addresses and bytes are
not folded with an earlier exact unit. Their independent native
SHA-256 are `ef877a67be3c67c5afdbf486dbef09942bf750bd3e2ef50a5cc510cb06a55d7c`,
`76e2b0e00c4fde908a610902941a1e01ee596ba4d901069e1c342b70a1bcbde4`,
and `64e00b3aa7139dc316f671d53a7dc4c7fad720ac6dad4c7a6612e3574400e3a3`.

Read-only [`verify-glyph-canvas-accessors-native.py`](../scripts/verify-glyph-canvas-accessors-native.py)
attests all three whole PE bodies and independently hashes the complete
original **2,227B/470-i386** and **2,245B/612-i386** caller bodies.
It decodes the actual original E8 fields and their destinations,
including all nine non-folded stride calls. Neither of the two
original large Bosses is source/exact accepted by this proof.

The three real C++ methods are maintained on the **same borrowed
[`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp)** as the
previously whole-exact 104B format fallback, with all four bodies
in [`GlyphCanvasEnsure104.cpp`](../src/GlyphCanvasEnsure104.cpp).
No parallel look-alike glyph surface, artificial 0x100-byte prefix,
vtable, resource allocation or altered global class layout is added.
The code reads the actual observed field through ordinary typed C++
reads and returns it, under pinned MSVC 19.44 i386 C++20.

One focused canonical object was recompiled for this **exact include
closure**. The existing 104B fallback and all three new 20B methods
replay whole strict exact:

```text
glyph_canvas_format_fallback_104: exact (104/104 bytes)
glyph_canvas_device_context_20: exact (20/20 bytes)
glyph_canvas_bitmap_pixels_20: exact (20/20 bytes)
glyph_canvas_pixel_stride_20: exact (20/20 bytes)
Exact replay: 4/4 units, 1 cold objects
```

The original owner ABI is specific to TH20's font bitmap and glyph
compositing protocol. These are three newly reconstructed, unique
game-owned method bodies: **+3 authored heads /60 native `.text`
bytes**. The previously exact 104B format fallback is unchanged and
is **not** counted twice. The adjacent 681B surface initializer,
2,227B GDI text Boss, 2,245B compositing Boss, 578B formatting Boss
and 294B submit Boss remain separate unaccepted functions. No
all-graph cold replay was used.

```sh
scripts/repo-python scripts/verify-glyph-canvas-accessors-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasEnsure104.cpp
```
