# CORE/RECON-1042 — whole exact 104B GDI glyph canvas format fallback below 2,227B text Boss

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original function `0x004153D0..0x00415437` is a complete
**104B/43-i386** font glyph surface-format fallback, native SHA-256
`20fdd9d772ec1d057d3a77d9795c7c974d44a790a02dff9a3fffdc0fafa78c47`.
It is invoked by the **whole original 2,227B/470-i386 glyph-text Boss**
`0x00415830` at the genuine original E8 `+0x362 -> 0x004153D0`.
The entire 2,227B parent is independently SHA-attested
(`c5a90c98ad5ac1ad5ec78f990dd4aec48d33abaebd5b28d12b7b92f6c85bbc70`)
but remains source-absent, not accepted exact.

## Original complete behavior

The original 104B method is **game-specific format negotiation** for
its GDI font bitmap. It first calls the native 681B bitmap/DC initializer
at `0x00415120` with the user's requested `width`, `height` and
`pixel_format`. If that method returns `true`, the 104B wrapper returns
`true` immediately. If native creation failed, the format fallback is:

- `0x19` or `0x1A` -> retry the **same** actual initializer with `0x15`
- `0x17` -> retry the original initializer with `0x16`
- all other inputs -> return `false`

It does **not** silently change the requested format before the first
attempt, retry a third time, replace the underlying initializer or
change boolean width. The original body has exactly **three physical
E8** at offsets `+0x16`, `+0x3F`, `+0x59`, all independently resolved
to `0x00415120`. It ends in `ret 0x0C` with no PE HIGHLOW relocations.

The natural source
[`src/GlyphCanvasEnsure104.cpp`](../src/GlyphCanvasEnsure104.cpp)
implements exactly these real branches using a borrowed
[`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp) for the
true original receiver; the unknown 681B creation body is only a
declared external method. No invented GDI allocation, additional
class data, vtable or undocumented error logic is introduced.

## Whole pinned MSVC acceptance

[`verify-glyph-canvas-ensure104-native.py`](../scripts/verify-glyph-canvas-ensure104-native.py)
checks the immutable complete 104B/43-i386 original SHA, true
`ret 0x0C`, all actual native format comparisons, the three genuine
E8 targets and the original 2,227B parent E8. The candidate from
pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` matches **92/92 ordinary code bytes**
and every native relocation field, target and symbol role; its
single new canonical unit passes:

```text
glyph_canvas_format_fallback_104: exact (104/104 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This is **one newly accepted game-authored function /104 real original
`.text` bytes**. The adjacent 20B DC getter, the underlying **681B**
bitmap initializer and the **2,227B** glyph text parent are independent
physical heads and **are not automatically exact**. The 294B text
submit and 578B text formatting parent also remain separate NONEXACT
C++ frontiers. No existing shared header ABI is changed, and no
whole-repository cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-canvas-ensure104-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasEnsure104.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1043 — three real glyph canvas accessors now exact

The same native GDI glyph canvas owner now has [three new whole-exact
20B/9-i386 member reads](GLYPH_CANVAS_ACCESSORS_20_20_20_STRICT_EXACT.md)
for HDC `+0x114`, pixel memory `+0x120`, and stride `+0x110`.
Original 2,227B/2,245B large text rendering callers were independently
verified. All four methods (including this 104B format fallback) stay
strict exact in one native C++ source/one focused canonical receipt.
No large boss or existing 104B head is double-counted.
