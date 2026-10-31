# CORE/RECON-1066 — correct native 22-HFONT table and complete exact 79B font cleanup

Original Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The native font table at **`0x005B66F0`** is a **genuine 22-entry
`std::array<HFONT,22>`**, with exactly `0x58` bytes of element storage
under the native i386 pointer ABI. This directly **corrects the previous
unproven 32-entry global font table declaration** in the source-present
2,227B GDI glyph text core `0x00415830`. The correct borrowed native
declaration is in [`NativeGlyphFontResources.hpp`](../src/NativeGlyphFontResources.hpp)
and is now shared by that large Boss and the independent font cleanup.

## Whole exact 79B original game-owned GDI font cleanup

The native `0x004155B0` whole function is **79B/28 i386**, original
SHA-256 `9e5f6bcf2be3a4a4f21e09d8693b463af56f5afd6e03b4deeca6691e2befce5c`.
It walks the actual native font table four bytes per element and calls
real Windows `DeleteObject` on each borrowed font handle. Its complete
original physical relocation graph has:

| Original location | Physical role |
| --- | --- |
| PE HIGHLOW `+0x09` | actual font table at `0x005B66F0` |
| E8 `+0x10` / COFF field `+0x11` | already exact folded `std::array::_Unchecked_begin` head `0x0040BDA0`, 14B |
| E8 `+0x1B` / COFF field `+0x1C` | distinct original `std::array::_Unchecked_end` head `0x00414F50`, 17B |
| PE HIGHLOW `+0x44` | actual GDI `DeleteObject` IAT at `0x0056C038` |

The native font array's complete **17B/9-i386** end method at
`0x00414F50`, original SHA-256
`f106cbce46348bfe471dda5f325d0e310a0557f477a497a821b3abb6fa359641`,
returns `this+0x58` and has zero E8/HIGHLOW. The 14B folded begin
method returns the receiver itself; it is already separately strict
exact under historical `motion_position_ref` at original `0x0040BDA0`,
so there is **no duplicate credit**. The source-present original
2,227B glyph text Boss physically calls the also previously exact
22B folded array `operator[]` at E8 `+0x57 -> 0x00414580` for this
same native font global, independently corroborating the actual owner.

## Source semantics and exactness

The maintained
[`GlyphFontRelease79.cpp`](../src/GlyphFontRelease79.cpp)
uses an ordinary `for (auto& handle : native_glyph_fonts_5b66f0)`
range loop and real Win32 `DeleteObject(handle)`; ordinary
`for (HFONT handle : ...)` generated different register/stack
ownership and **did not** match the complete original 79B body.
The correct range-by-reference form generates **79B/28 x86,
63/63 ordinary bytes** and all **four original PE relocation roles**.
A real standard `std::array<HFONT,22>::_Unchecked_end` instantiated
naturally from the same source emits the entire **17/17B** at its
independent original physical head. A speculative 32-element array
would have an incorrect `+0x80` end offset and is now rejected.

Read-only [`verify-glyph-font-release79-native.py`](../scripts/verify-glyph-font-release79-native.py)
SHA-pins the entire original 79B/28 body and 17B/9 end method, the
original 14B folded begin and 22B folded indexing method, all actual
PE E8/HIGHLOW targets, and the entire original 2,227B big text Boss
including its authentic font-index call. Under pinned MSVC 19.44
C++20 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`,
one new canonical source object and its affected large-text source
closure replay:

```text
glyph_font_release_79: exact (79/79 bytes)
glyph_font_array_end_17: exact (17/17 bytes)
glyph_text_job_capture_132: exact (132/132 bytes)
glyph_text_job_dtor_23: exact (23/23 bytes)
glyph_text_queue_submit_56: exact (56/56 bytes)
Exact replay: 5/5 units, 3 affected/captured objects
```

This adds **one game-authored exact function /79 original executable
`.text` bytes**, plus **one generic STL exact head /17 distinct bytes**.
The already exact 14B folded begin and 22B index are not counted
twice. The original 2,227B GDI text core now shares the **correct
22-font declaration**, but remains **SOURCE-PRESENT, NONEXACT** with
natural 2,072B/484-i386 source versus 2,227B/470 native (25
E8/54 DIR32 candidate versus 25 E8/43 PE HIGHLOW original).
No game text core or font data bytes are inferred as exact from the
corrected table, and **no full-project cold replay** was run.

```sh
scripts/repo-python scripts/verify-glyph-font-release79-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphFontRelease79.cpp \
  --source src/GlyphTextCore2227.cpp \
  --source src/GlyphTextQueueSubmit56.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
```
