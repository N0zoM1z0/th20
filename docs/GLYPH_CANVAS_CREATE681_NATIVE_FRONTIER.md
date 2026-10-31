**CORE/RECON-1050 CURRENT STATUS CORRECTION:** The original 681B surface create Boss is now [whole canonical 681/681B STRICT EXACT](GLYPH_CANVAS_CREATE681_STRICT_EXACT.md). Earlier 684B NONEXACT observations below remain historical hypotheses: they were superseded by directly using the native `this` receiver, a committed-format `switch`, and genuine pixel-writer-before-alpha-local lifetimes. All eight independently original physical relocation roles are exact; +681 game-authored bytes.

# CORE/RECON-1044 — full 681-byte GDI glyph bitmap lifecycle source with original 108-byte V4 header

Locked target: Japanese TH20 v1.00a Steamless SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original `NativeGlyphCanvasView::create_gdi_surface_415120`
at `0x00415120..0x004153C8` is **681B /176 i386 instructions**, native
SHA-256 `62554c335c22f75345ca164715188e77712c1e8348c199e3757843b193aa33d3`.
It is physically called **three times** by the independently whole-exact
104B format fallback at `0x004153D0`: actual original E8 `+0x16`,
`+0x3F` and `+0x59`. Its real runtime protocol is a complete custom
TH20 bitmap/GDI resource lifecycle, not a trivial library accessor.

## Correcting the native header hypothesis

Ghidra's provisional local variable name in earlier analysis was
`BITMAPINFO`, but the immutable original explicitly zeros **0x6C
(108) bytes** with `memset` and stores `0x6C` in the first field,
*before* calling `CreateDIBSection`. This is the precise size and ABI
of Windows `BITMAPV4HEADER`, which contains four packed color masks.
Treating it as an ordinary 40-byte `BITMAPINFOHEADER`, or as
`BITMAPINFO` with arbitrary padding, misplaces the original mask
and palette data. The maintained
[`GlyphCanvasCreate681.cpp`](../src/GlyphCanvasCreate681.cpp)
uses the real SDK `BITMAPV4HEADER`, with
`static_assert(sizeof(BITMAPV4HEADER)==0x6C)` under MSVC i386,
not a fabricated local byte array.

The native function first releases the previous bitmap/DC resource
using original `0x00416360`, clears the complete V4 structure with
the original CRT `memset` and obtains the real selected pixel format
descriptor from `0x00415640`. The descriptor's observed six 32-bit
words contain format code, bit depth and four color masks. It computes
the signed 32-bit aligned row stride, sets width, **height = -(height+1)**,
plane count one, native bit depth and `biSizeImage = height*stride`.
For modes other than `0x18` and `0x16`, it publishes `BI_BITFIELDS`
and all four native masks.

It then creates the DIB with GDI `CreateDIBSection`, creates a
compatible DC, selects the bitmap and publishes the real custom
glyph canvas owner fields: pixel format `+0x100`, width `+0x104`,
height `+0x108`, image byte size `+0x10C`, row stride `+0x110`,
HDC `+0x114`, prior selected GDI object `+0x118`, HBITMAP `+0x11C`
and bitmap bits pointer `+0x120`.

The native code **re-reads the committed format at owner `+0x100`**
before special initialization, rather than relying on the caller's
original parameter. It initializes 32-bit `0x15` pixels with an
opaque alpha word `0xFF000000` in four-byte steps, or 16-bit `0x1A`
pixels with a `0xF000` alpha word in two-byte steps. Failed descriptor
lookup or failed `CreateDIBSection` return false; native code does
not add safety checks for subsequent `CreateCompatibleDC` or
`SelectObject` failures. Those original branches are not silently
changed to more robust behavior.

## Independently attested native functions, GDI imports, and remaining gap

[`verify-glyph-canvas-create681-native.py`](../scripts/verify-glyph-canvas-create681-native.py)
reads the immutable **whole original 681B/176** body through its
actual `ret 0x0C`, checks the 108-byte V4 length, all **four native
physical direct E8s**, all **four original PE HIGHLOW fields**, and
the three real calls from the exact 104B format-fallback parent:

| Original field | Original physical target/meaning |
| --- | --- |
| E8 `+0x19` | release GDI canvas `0x00416360` |
| E8 `+0x26` | real CRT `memset` `0x00544760` |
| E8 `+0x35` | original glyph pixel-format lookup `0x00415640` |
| PE HIGHLOW `+0x0A` | security cookie `0x005B25C0` |
| PE HIGHLOW `+0xFB` | actual GDI `CreateDIBSection` IAT `0x0056C020` |
| PE HIGHLOW `+0x119` | actual `CreateCompatibleDC` IAT `0x0056C044` |
| PE HIGHLOW `+0x133` | actual `SelectObject` IAT `0x0056C02C` |
| E8 `+0x29E` | native security cookie verification `0x005429EE` |

The genuine completed natural C++20 source compiles under pinned
MSVC 19.44 x86 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` to **684B /176 i386 instructions**, with four E8 and
four DIR32 roles. All three native GDI import field positions,
the security cookie HIGHLOW and the **first three original E8 field
sites match physically**. The remaining 3-byte whole-function
length/last-cookie displacement and a number of conditional/stack
local bytes do not. Several private controlled trials checked whether
C++ `switch` dispatch, use of the committed format from the actual
owner, and meaningful 16-/32-bit pixel initialization locals
reproduce the original exact dispatch. They compiled from 641B
through 711B; none passed whole-original strict comparison. The
684B/176 version retains coherent gameplay and GDI resource semantics,
**without inert locals, generated opcode patches, inline assembly or
a false shortened-original comparison**.

**Status: SOURCE-PRESENT, NONEXACT.** The original 681B method is now
implemented as an authentic native-source frontier and consumes the
same [`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp)
as the four **already exact** game-owned getter/format methods. The
shared declaration change affects **one** canonical provider:
`GlyphCanvasEnsure104.cpp`. That owner was cold rebuilt with **4/4
strict units** in a source-filtered replay. This new 681B file has
no strict match unit and receives **zero newly authored exact
credit**. The 2,227B text core, 2,245B glyph compositor, 578B text
formatter, 294B submit wrapper and entire linked game remain
separate unresolved work. No whole-repository cold replay ran.

```sh
nice -n 15 scripts/repo-python scripts/compile-probe.py \
  src/GlyphCanvasCreate681.cpp build/core1044-probes/GlyphCanvasCreate681.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python scripts/verify-glyph-canvas-create681-native.py \
  --candidate-object build/core1044-probes/GlyphCanvasCreate681.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasEnsure104.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```

## CORE/RECON-1045 — exact pixel format selector nested inside 681B Boss

The original `0x00415640` format lookup called at E8 `+0x35` is now
[whole 82/82 strict exact](GLYPH_PIXEL_FORMAT_LOOKUP82_STRICT_EXACT.md).
Its actual 24B `NativeGlyphPixelFormat` descriptor type is shared
with this maintained 681B source and contains the original six color
mask values followed by a signed `-1` sentinel. The 681B bitmap
creator remains NONEXACT at 684B/176 source bytes; no parent or
`.rdata` table credit is inferred.

## CORE/RECON-1046 — whole GDI/DC release child now exact

The original GDI owner cleanup `0x00416360` invoked by this 681B
method at E8 `+0x19` is now a [whole-exact 182B/42-instruction
source](GLYPH_CANVAS_RELEASE182_STRICT_EXACT.md), with three real
GDI IAT calls and native `bool` return. The earlier provisional
`void` declaration was wrong and is now corrected. All six strict
subchain units were rebuilt in three affected providers; the
681B parent still compiles to 684B/176 and remains NONEXACT.

## CORE/RECON-1047 — original 0x124 glyph canvas constructor exact

The native GDI canvas allocation object now has its own
[whole 124B original constructor](GLYPH_CANVAS_CONSTRUCTOR124_STRICT_EXACT.md),
including native `memset(0x124)` and the observed +0x100..+0x120
resource suffix. The 73B allocation wrapper is still separate.
This 681B GDI create method remains NONEXACT despite having its
constructor, 182B cleanup, 82B descriptor lookup and 104B caller
now separately whole exact.
