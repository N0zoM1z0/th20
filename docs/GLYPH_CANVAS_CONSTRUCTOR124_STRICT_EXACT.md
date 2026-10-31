**CORE/RECON-1058/1059 status correction:** The original 2,227B glyph text core previously called source-absent is now [SOURCE-PRESENT, NONEXACT](GLYPH_TEXT_CORE2227_TYPED_NATIVE_FRONTIER.md) with a complete 2,052B/481-instruction native-typed candidate. Its separate original 132B game-specific queued-job capture is [WHOLE STRICT EXACT](GLYPH_TEXT_JOB_CAPTURE132_STRICT_EXACT.md). Historical source-absent claims below are dated; the 2,227B parent is still not exact.

# CORE/RECON-1047 — whole original 124B glyph canvas owner constructor, native exact

Target: immutable Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original TH20 GDI glyph canvas is **0x124 bytes**. The complete
native constructor at `0x00414200` is **124B/28 i386**, original SHA-256
`753f6983e88c30419652a69281f0f57138b3d583df317f85ad3be51e51fcc9dd`.
The separate original **73B/22-instruction** allocator wrapper at
`0x00413C50` calls this exact constructor at E8 `+0x2F` after
allocating genuine 0x124-byte storage and applying its native
initialization. The enclosing original **2,227B/470-instruction**
glyph text Boss at `0x00415830` calls that 73B allocator via its
actual E8 `+0x89`. Both parents remain physically separate from the
124B constructor's accepted extent.

## Native object layout and true source initialization

The maintained [`NativeGlyphCanvasStorage`](../src/NativeGlyphCanvasStorage.hpp)
is a genuine **0x124-byte storage owner**, distinct from the previously
borrowed-method-only `NativeGlyphCanvasView`. The first **0x100 bytes
exist in the original allocation** but their full glyph/render state
is not recovered; they are represented as explicitly *unresolved
native storage*, not invented padding to shift a compiler offset.
The physically observed resource fields are:

| Native owner offset | Actual field |
| --- | --- |
| `+0x100` | signed pixel format, initially `-1` |
| `+0x104/+0x108` | width and height, initially zero |
| `+0x10C/+0x110` | image byte count and pixel row stride |
| `+0x114` | native GDI HDC |
| `+0x118` | previously selected HGDIOBJ |
| `+0x11C` | HBITMAP |
| `+0x120` | mapped GDI bitmap pixels |

The actual native method clears the entire valid 0x124-byte memory
with the ordinary CRT `memset`, then explicitly publishes format=-1,
width=0, height=0, HDC=null, bitmap=null, previous object=null and
pixels=null in the original order. These stores are actually present
in the original machine code even though the memset also clears
parts of their storage; they are **the true constructor protocol**,
not inert compiler-shaping lines inserted solely for byte equality.
The native 124B constructor has **one physical E8 at `+0x12` to
original CRT `memset` `0x00544760`** and zero native PE HIGHLOW fields.

The natural maintained constructor is in
[`src/GlyphCanvasConstruct124.cpp`](../src/GlyphCanvasConstruct124.cpp),
with actual MSVC x86 size and field-offset static assertions. It is
compiled using pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`; its complete body matches
**120/120 ordinary original machine-code bytes** and the one genuine
original E8 source symbol, type and independently established target.

[`verify-glyph-canvas-construct124-native.py`](../scripts/verify-glyph-canvas-construct124-native.py)
SHA-attests the full immutable 124B body and all 28 instructions
through native `ret`, checks `0x124` original `memset` and format
publication, pins the full original 73B allocator and proves its
E8 `+0x2F` to the constructor, and hashes the full 2,227B parent
and its genuine E8 `+0x89` into the allocator. The source is admitted
as **one** new distinct canonical strict unit:

```text
glyph_canvas_constructor_124: exact (124/124 bytes)
Exact replay: 1/1 units, 1 cold objects
```

This adds **one game-authored original exact function /124 native
`.text` bytes**. No code is credited for the 73B allocator or 2,227B
parent by inference. The separate 104B format fallback, 82B format
descriptor lookup, 182B resource cleanup and three 20B field
accessors retain their own physical exact credit. The 681B GDI
create Boss and 2,245B compositor remain open. No shared borrowed
ABI or previously accepted source was changed; this one new
source object alone was cold-replayed.

```sh
scripts/repo-python scripts/verify-glyph-canvas-construct124-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasConstruct124.cpp
```

## CORE/RECON-1048 — original allocator preclear ABI separately pinned

The 73B original `0x00413C50` wrapper invoking this whole-exact 124B
constructor has a separately [SHA-pinned three-E8 allocation graph](GLYPH_CANVAS_ALLOCATOR73_NATIVE_FRONTIER.md):
`operator new(0x124)`, native 31B `__autoclassinit2` preclear, then
this real constructor. No natural pinned C++20 allocation trial
reproduced the entire 73B wrapper without extra or missing real
compiler helpers, so **only the 124B ctor remains exact**, not
its allocator or the 2,227B parent.
