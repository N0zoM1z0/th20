# CORE/RECON-1065 — complete original 542B GDI glyph canvas Alpha Boss, whole strict exact

Original pinned target: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-owned `NativeGlyphCanvasView::invert_alpha_417ab0`
physical body at **`0x00417AB0`** is **542B/164 i386 instructions**,
whole native SHA-256
`b510c0d99e2c1d40f1388c77952a55775dfd24617858922e56ed178e1fdf64df`.
The genuine **2,227B/470-i386** GDI text Boss `0x00415830` calls
this full original function at E8 `+0x6D6` after rendering/outlining.

## Exact reconstruction of three real native pixel modes

The independently whole-exact maintained source is
[`src/GlyphCanvasAlphaInvert542.cpp`](../src/GlyphCanvasAlphaInvert542.cpp)
on the existing borrowed
[`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp).
It preserves exactly three different game-owned native pixel modes:

- **0x15 / BGRA32**: for each row and requested horizontal span,
  invert **only the high Alpha byte** with XOR `0xFF`, preserving the
  lower three BGR bytes. The meaningful row pointer is computed in
  **two steps**: physical row base using the native canvas-width getter,
  followed by the requested horizontal offset, each updating the
  original local row-pointer state. An explicit `BGRA32GlyphPixel`
  with four byte members describes the actual 4-byte pixel layout.
- **0x19 / RGB555A1**: step through the full native byte count in
  **2-byte** pixels. Toggle the actual **1-bit Alpha**. If the new
  Alpha is nonzero, leave its RGB colors unchanged; otherwise clear
  the real **5-bit red, 5-bit green, 5-bit blue** subfields in that
  order. The source uses the native `std::uint16_t` bitfield widths,
  which naturally generate the original **16-bit `shr`/`and`/`shl`**
  and the genuine **`0x83FF`, `0xFC1F`, `0xFFE0` channel masks**.
- **0x1A / RGBA4444**: use the physical **16-bit four-bit Alpha
  field**, complementing only that nibble with XOR `0xF` and preserving
  twelve RGB bits. The original procedure first initializes a true
  row pointer from the canvas pixel base **before** its outer loop,
  then reassigns and advances that pointer during each row/column.
  This real pointer lifetime produces two otherwise missing original
  three-byte x86 pointer instructions.

The source retains the original `bool` return and `ret 0x10` for four
native stack args (the last argument's semantic purpose is not yet
identified), and returns false for unrecognized pixel formats.

## Independent exactness: compiler hypotheses were challenged

Historical [CORE/RECON-1057](GLYPH_CANVAS_ALPHA542_TYPED_NATIVE_FRONTIER.md)
recorded a complete 540B/164 i386 NONEXACT C++20 body. Its original
byte mismatch was not a missing game branch but a **source semantics and
C++ type-width mismatch**: a cached local copy of the native format,
combined row address expression, and C++ integer-promoted 16-bit pixel
arithmetic prevented the original x86 register allocation and branch
layout. Multiple controlled private probes under ignored `.analysis/`
tested normal two-step GDI pointer state, genuine 1-bit/4-bit channel
bitfields, preserving two distinct row lifetimes and source-level
conditional structure.

The decisive case used a real `if/else` for the new RGB555 Alpha:
when the new Alpha bit is one, RGB is untouched; **otherwise** the
three genuine color channels are cleared. This compiles the original
**two-branch local exit** (`je` followed by a short `jmp` to the common
pixel-body exit), rather than a semantically equivalent but different
direct `continue` branch. The source does not add a dummy side effect,
no-op instruction, patch, fake ABI argument or manual assembly; it
expresses the exact original per-pixel state and branch ownership.

Locked MSVC 19.44 i386 C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
compiles the whole body to **542B/164 instructions**, with **526/526
nonrelocated original bytes** and four genuine original E8 locations:

| Original physical E8 | True native target | Original COFF relocation field |
| --- | --- | --- |
| `+0x0C` | `0x004156C0` exact stride getter | `+0x0D` |
| `+0x1B` | `0x004156A0` exact pixels getter | `+0x1C` |
| `+0x6B` | `0x00415800` exact width getter | `+0x6C` |
| `+0x198` | `0x00415800` exact width getter | `+0x199` |

The full original body has **zero PE HIGHLOW**. All original targets
and positions were independently read from the immutable original PE;
they were not inferred by solving compiled COFF differences. The
read-only native verifier
[`verify-glyph-alpha-invert542-native.py`](../scripts/verify-glyph-alpha-invert542-native.py)
SHA-pins the original complete 542B body and its 164 instructions,
three original format branches, the native 2,227B parent caller and
four physical E8 targets. It separately tests whole canonical source
strictness without shortening any original extent:

```text
glyph_canvas_alpha_invert_542: exact (542/542 bytes)
Exact replay: 1/1 units, 1 cold object
```

This admits **one new game-authored whole-exact physical function /
542 original `.text` bytes**. The previously exact 681B GDI bitmap
creator, 104B format fallback, 182B resource cleanup, 82B format
lookup and four distinct 20B canvas getters are **not** re-credited.
The original 2,227B glyph text core and 2,245B glyph compositor
remain separate SOURCE-PRESENT/NONEXACT large Bosses. No shared
borrowed ABI header or accepted source provider was changed; the
fresh exact build includes **only the one affected original 542B
owner**, with no project-wide cold replay.

```sh
scripts/repo-python scripts/verify-glyph-alpha-invert542-native.py \
  --candidate-object build/core1065-canonical/GlyphCanvasAlphaInvert542.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphCanvasAlphaInvert542.cpp
```
