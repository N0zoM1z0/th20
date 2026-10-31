# CORE/RECON-1046 — whole original 182B GDI resource-release method, strict exact

Target: immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The physical `0x00416360..0x00416415` is a complete
**182B/42-i386** game-owned bitmap/DC resource release with original
SHA-256 `632c4839135f7908fc5bda7f2a749944332b8ff3bb76de8484e428a03ce1258e`.
The still NONEXACT **681B** GDI bitmap creation Boss at `0x00415120`
physically calls this head through its true original E8 `+0x19` before
allocating the next bitmap. The method is **`bool`-returning**, not
`void`, correcting the earlier speculative declaration in
`NativeGlyphCanvasView.hpp` and corresponding source-owner ABI.

## Complete native GDI lifecycle

The method checks real HDC `this+0x114` for null. If absent, it returns
`false` without deleting resources. If present, in exactly the original
order it calls `SelectObject(HDC, previous_HGDIOBJ)`, then
`DeleteDC(HDC)`, then `DeleteObject(HBITMAP)`. The three original PE
HIGHLOW import fields, resolved *independently* from the locked PE, are:

| Physical field | Real GDI IAT address |
| --- | --- |
| `+0x2D` | `0x0056C02C`, `SelectObject` |
| `+0x3D` | `0x0056C03C`, `DeleteDC` |
| `+0x4D` | `0x0056C038`, `DeleteObject` |

It then resets the native pixel format at owner `+0x100` to signed
`-1`, dimensions `+0x104`/`+0x108` to zero, and GDI resource
pointers at `+0x114` HDC, `+0x11C` bitmap, `+0x118` previous object,
`+0x120` pixels to null, returning native `true` in AL. These are
actual data-member state changes, not temporary compiler padding.
The whole 182B body has **zero original E8** and precisely **three
actual PE HIGHLOW**, ending at native `ret`.

[`verify-glyph-canvas-release182-native.py`](../scripts/verify-glyph-canvas-release182-native.py)
reads the immutable original PE, SHA-pins the entire body and its
42 real instructions, checks the boolean test and `true`/`false`
return paths, all three original GDI import fields and the genuine
681B parent's `+0x19` call. The original digest was **recomputed
directly from the locked PE** rather than copied from prior notes.
No original instruction bytes or IAT data are written to the repository.

## Compiler hypothesis corrected, whole strict acceptance

The original whole method is naturally maintained in
[`GlyphCanvasRelease182.cpp`](../src/GlyphCanvasRelease182.cpp)
using the same existing borrowed `NativeGlyphCanvasView` as the
previously accepted 104B fallback, 82B format lookup, and three 20B
getters. The first private C++ experiment made a redundant
`auto* bytes = reinterpret_cast<uint8_t*>(this)` local and compiled
**190B/44 instructions**; it did not reproduce original local
ownership. Removing the redundant duplicate and reading the same
meaningful receiver fields directly from `this` generates the entire
**182B/42 native instructions** with **170/170 nonrelocated bytes** and
all three genuine DIR32 IAT relocations exact. No no-op, manually
placed x86 instruction, artificial member, fake return or temporary
source-only comparison boundary is involved.

The release method changes the public borrowed view declaration from
speculative `void` to original native `bool`. The captured include
closure requires rechecking only **three canonical objects**:
`GlyphCanvasEnsure104.cpp` (four already exact units),
`GlyphCanvasFormatLookup82.cpp` (one already exact unit), and the new
`GlyphCanvasRelease182.cpp` (one new exact unit). All **6/6**
original extents pass pinned MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`:

```text
glyph_canvas_format_fallback_104: exact (104/104 bytes)
glyph_canvas_device_context_20: exact (20/20 bytes)
glyph_canvas_bitmap_pixels_20: exact (20/20 bytes)
glyph_canvas_pixel_stride_20: exact (20/20 bytes)
glyph_pixel_format_lookup_82: exact (82/82 bytes)
glyph_canvas_release_182: exact (182/182 bytes)
Exact replay: 6/6 units, 3 cold objects
```

This adds **one distinct game-authored whole-exact head /182 native
`.text` bytes**. The 681B GDI bitmap create Boss was separately
recompiled with the corrected header and remains **684B/176 source
candidate vs 681B/176 original, NONEXACT**; its 182B callee does not
make it exact. The GDI formatter's 2,227B/2,245B originals are also
independent and unresolved. No full-graph cold replay was performed.

```sh
scripts/repo-python scripts/verify-glyph-canvas-release182-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasEnsure104.cpp \
  --source src/GlyphCanvasFormatLookup82.cpp \
  --source src/GlyphCanvasRelease182.cpp
```
