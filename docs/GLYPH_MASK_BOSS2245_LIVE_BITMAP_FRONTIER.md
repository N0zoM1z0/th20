**CORE/RECON-1080 CURRENT SOURCE UPDATE:** The native 8B glyph-offset object now uses a real [two-int32 indexed `std::array` instead of the historical plain struct](GLYPH_MASK_OFFSET_ARRAY2_NATIVE_TYPE.md). The complete current source parent is **2,061B/545 i386, 36 E8/5 DIR32** (original whole **2,245B/612 i386, 37 E8/5 HIGHLOW**). Four native folded index calls are present, and the 15 earlier PMR/color strict units still replay exact with the corrected vector template type. Earlier 2,041B/1,987B snapshots below are historical.

# CORE/RECON-1079 — corrected live bitmap and stride ownership in 2,245B GDI glyph-mask Boss

Pinned original TH20 Japanese Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original game-authored glyph stencil/mask compositor
`0x00416420` is a complete **2,245B/612-instruction i386** function,
SHA-256
`06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad`,
with **37 original physical E8 and 5 PE HIGHLOW**. This is the real
2-format BGRA32/RGBA4444 compositing Boss invoked twice by the original
2,227B GDI text rasterizer, not a stand-alone stencil leaf. Both
large original Boss bodies remain SOURCE-PRESENT/NONEXACT.

## Rechecking the actual original code overturned the cached-row hypothesis

The previous meaningful C++20 source in
[`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
compiled to **1,987B/538 i386, 27 E8/5 DIR32**. That was
reproduced by cold compiling the **previous Git source** as an
independent ignored probe; it was not taken on trust from historical
documentation. Comparing its actual source calls with the original
entire native `.text` disclosed a material field-lifetime mistake:

| Actual call owner | Original complete 2,245B Boss | Previous compiler candidate | Corrected compiler candidate |
| --- | ---: | ---: | ---: |
| `NativeGlyphCanvasView::bitmap_pixels_4156a0()` | **1** | **3** | **1** |
| `NativeGlyphCanvasView::pixel_stride_4156c0()` | **9** | **1** | **8** |
| Folded `0x00414580` offset element index helper | **4** | **0** | **0** |
| All native E8/compiled REL32 | **37** | **27** | **32** |
| Whole function size | **2,245B** | **1,987B** | **2,041B** |
| Complete x86 instructions | **612** | **538** | **557** |
| Original HIGHLOW/compiled DIR32 | **5** | **5** | **5** |

The original calls `pixel_stride` at relative E8 offsets
`+0x32`, `+0x197`, `+0x1D7`, `+0x5A6`, `+0x5E7`, `+0x69B`,
`+0x6FA`, `+0x752`, `+0x7B4`, but gets actual pixels **only once**
at E8 `+0x44`, **before** allocating the snapshot buffer at
E8 `+0x61` and copying the full original DIB byte buffer by
`memcpy` at E8 `+0x81`. The old source allocated the snapshot
*before* fetching its pixel source and issued repeated pixel reads
inside both format loops, while incorrectly using one cached row
stride for the entire output. Both changes could affect real
aliasing and GDI surface lifetime, independent of machine-code
matching.

The corrected maintained source acquires the native pixel base
only once, before allocation and snapshot, and reuses that stable
pointer across both format branches. The BGRA32 path now computes
its original integer pixels-per-row once, maintains a **live row
advance** by rereading the stride getter after each row, and
preserves the reflected-neighbor stencil test. The RGBA4444 path
reads the live stride in its source/destination pixel coordinate
calculation, rather than replacing the original per-neighbor reads
with a cached width. The semantic four-way mirroring, native
16-bit/32-bit alpha and RGB update, memory snapshot and release
remain intact. No compiler dummy locals or false calls were added.

The newly generated complete natural candidate improves to
**2,041B/557 i386 with 32 E8/5 DIR32**, confirmed from the pinned
MSVC 19.44 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` real COFF, compared with the original full native
2,245B/612 and 37 E8. The remaining **5 native E8** correspond to
one live stride call and **four genuine original folded array-like
offset-index E8** (two per pixel format) that the struct-field
source currently inlines. These are a separate original data-type
frontier. The main Boss is **still NONEXACT**, and receives **zero
new game-authored exact byte credit** in this checkpoint.

[`verify-glyph-mask-boss-live-pixels-native.py`](../scripts/verify-glyph-mask-boss-live-pixels-native.py)
independently SHA-pins the *whole* 2,245B original, all 612 native
instructions, the exact original E8 sites and five PE HIGHLOW, then
verifies the complete 2,041B source compiler contribution and the
corrected one-pixel/eight-stride call graph. It also checks the
original PMR-vector helper receipts without claiming that a child
being exact means its large parent is exact. The **one affected
source object** is cold replayed for all **15/15 previously
accepted strict units**, all still whole exact:

```text
Previous genuine C++ source: 1987B /538 i386, 27 E8, 5 DIR32
Corrected genuine C++ source: 2041B /557 i386, 32 E8, 5 DIR32
Original complete game Boss: 2245B /612 i386, 37 E8, 5 PE HIGHLOW
Local canonical replay: 15/15 exact units, 1 cold object
Game-authored whole 2245B strict credit: none (still NONEXACT)
```

No project-wide cold replay, target-code patch, shortened native
comparison or source-byte padding was used.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/GlyphMaskComposite2245.cpp build/core1079-probes/GlyphMaskComposite2245.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-glyph-mask-boss-live-pixels-native.py \
  --candidate-object build/core1079-probes/GlyphMaskComposite2245.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
```
