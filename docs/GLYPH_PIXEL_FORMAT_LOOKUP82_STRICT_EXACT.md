# CORE/RECON-1045 — whole exact original 82B glyph pixel format descriptor lookup

Target: immutable Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `0x00415640..0x00415691` is a **complete 82B/26-i386**
GDI pixel-format descriptor lookup, original SHA-256
`d1980926efef1321fd130e8f043d405927252e1dd05f69f54cba12a77b1e913f`.
It is called by the separately SOURCE-PRESENT but NONEXACT original
**681B GDI glyph bitmap creation Boss** `0x00415120` via the actual
native E8 `+0x35`; the 681B parent also uses the returned descriptor's
bit depth and four packed color masks. This is a real game-owned
pixel-format choice, not an arbitrary library wrapper.

The original table at **`0x005AE078`** is an ordered array of native
**0x18-byte/six-word** descriptors: signed format code, bit depth,
alpha/red/green/blue channel mask. The six native codes and widths
are `(0x16,32)`, `(0x15,32)`, `(0x18,16)`, `(0x17,16)`, `(0x19,16)`,
`(0x1A,16)`, followed by the actual **signed `-1` sentinel**.
The source scans forward until a descriptor code is `-1` or matches
the request. It then returns null **only for a requested `-1`**;
otherwise it returns the found descriptor pointer. A missing unknown
format therefore returns the sentinel entry rather than null, and
the source does not invent an extra validity check or table length.

The original body has **zero E8 instructions** and precisely three
physical original PE HIGHLOW at `+0x21`, `+0x2E`, `+0x48`, all resolving
to `0x005AE078`. The immutable source/native proof
[`verify-glyph-pixel-format-lookup82-native.py`](../scripts/verify-glyph-pixel-format-lookup82-native.py)
SHA-pins the entire 82B body through native `ret 4`, independently
reads the 24-byte descriptor entries and signed sentinel from the
locked original, checks all three HIGHLOW roles, and hashes the full
681B parent and original direct E8 `+0x35`.

An earlier *plausible but wrong* C++ `while`/ternary expression compiled
to **92B** and used an extra return temporary/stack slot. In contrast,
a real `for` loop over the observed native 24-byte descriptors followed
by an explicit `if(format==-1) return nullptr;` compiles naturally to
**82B/26 original instructions** with the native loop increment/exit
layout, and all **70/70 nonrelocated machine bytes** match.
[`src/GlyphCanvasFormatLookup82.cpp`](../src/GlyphCanvasFormatLookup82.cpp)
maintains this accepted semantic source, with the actual descriptor
layout in [`NativeGlyphPixelFormat.hpp`](../src/NativeGlyphPixelFormat.hpp).
The 681B GDI creator now includes this shared exact descriptor type
instead of repeating a separate, potentially divergent local type.
The table remains a **borrowed extern**; no original data is copied
into tracked source or credited as new game executable code.

Pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` replays one new canonical function/object:

```text
glyph_pixel_format_lookup_82: exact (82/82 bytes)
Exact replay: 1/1 units, 1 cold objects
PASS 82B/26 original; 3 HIGHLOW to original descriptor table
PASS six game format descriptors and signed -1 original terminator
PASS 681B source-present original parent E8 +0x35
```

This adds **one new game-authored exact head /82 original `.text`
bytes** and one canonical source object. The shared descriptor layout
only also affects the **still nonexact** `GlyphCanvasCreate681.cpp`,
which was recompiled as a scoped probe and retains its original
**684B/176** candidate extent without strict credit. The existing
104B format fallback and three 20B GDI field getters are unaffected
and must not be credited twice. The 681B GDI parent, 2,227B text
core and 2,245B glyph compositor remain independently unfinished.
No unfiltered full-graph cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-pixel-format-lookup82-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasFormatLookup82.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1046 — real cleanup before lookup accepted

The original 681B GDI bitmap creator first invokes the now
[whole-exact 182B release method](GLYPH_CANVAS_RELEASE182_STRICT_EXACT.md)
before entering this 82B exact table lookup. Its original return
is a boolean, not the speculative void declaration. Both distinct
physical helper heads remain strict exact under a 6/6 scoped replay;
the 681B parent is still NONEXACT.
