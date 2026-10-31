# CORE/RECON-1052 — whole original 2,245B glyph mask compositor source, four nested PMR vector helpers strict exact

Original target: Japanese TH20 Steamless v1.00a, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original TH20-owned `0x00416420` is a complete **2,245B /612-i386**
bitmap glyph mask/outline compositor, whole original body SHA-256
`06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad`.
It has **37 physical E8 calls /five native PE HIGHLOW data fields**.
It is called from the original **2,227B** GDI glyph-text core at
`0x00415830` twice, at E8 `+0x4AF` and `+0x5EA`. The 2,227B parent
remains separately source-absent and is not accepted exact.

## Restored full 2,245B original game algorithm, source-present NONEXACT

[`src/GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
now retains both native game-specific outline paths on the existing
borrowed [`NativeGlyphCanvasView`](../src/NativeGlyphCanvasView.hpp):

- Acquire the true canvas pixel stride and mapped pixel pointer;
  allocate a separate copied stencil through the real
  `DiagnosticAllocator` and copy the original bitmap before any
  in-place modification. The native allocation site is specifically
  labelled as coming from `grpfont.cpp:615`.
- For **0x15 BGRA32** and **0x1A ARGB4444**, allocate a distinct
  **16-byte PMR vector of two signed 32-bit neighbor offsets**.
  Generate all nonzero, first-quadrant integer points satisfying
  `x*x + y*y < radius*radius`, then test their four reflected positions
  around each live pixel within the original native branch bounds.
- For BGRA32, apply the true color with flipped opaque alpha when a
  reflected stencil pixel is not fully opaque; otherwise update the
  three BGR channels without replacing the destination's alpha.
  The real four original `canvas_width_415800()` calls are preserved
  at relevant reflected-horizontal-bound checks.
- For ARGB4444, convert the full 32-bit color into native packed
  `R4G4B4A4` channel nibbles, including the original inverted alpha
  nibble. Replace the whole packed pixel at an outline neighbor,
  or update RGB while retaining the actual destination alpha nibble
  when no outline neighbor matches.
- Destroy the original PMR offset-vector scope in each branch and
  release the copied stencil through the genuine game allocator.
  The source does not substitute a simulated bitmap for the native
  external `NativeGlyphCanvasView` owner.

The maintained two-dimensional offset value type is
[`GlyphMaskOffset`](../src/NativeGlyphMaskOffsets.hpp), exactly two
signed 32-bit coordinates; its `std::pmr::vector` uses the observed
16-byte native allocation/iteration layout rather than a false
12-byte default-allocator vector. The **real 32-bit and 16-bit
neighborhood loops live in the main function** instead of being
lifted into calls absent from the original 2,245B body.
A first high-level source with separate loop helpers compiled its
parent to 837B; integrating the actual stencil and four-direction
loops improved it to a **1,987B/538-i386** main candidate under
pinned MSVC 19.44 C++20, with **27 REL32 /5 DIR32**.
The original remains **2,245B/612-i386, 37 E8/5 HIGHLOW**. Missing
native 2245B/612 byte/branch/EH code is not credited; the candidate
is a semantic **SOURCE-PRESENT, NONEXACT** frontier, not a whole
native exact acceptance.

## Four complete original standard-library child functions now exact

The original 2,245B main calls the following independently physical
`std::pmr::vector<GlyphMaskOffset>` template instances in **both**
color branches. The actual C++20 source emits *all four* naturally:

| Original head | Whole original body | Parent's actual E8 offsets | Own native calls |
| --- | ---: | --- | --- |
| `0x004141C0` PMR vector default constructor | **63B/25 i386** | `+0xD2`, `+0x44A` | `+0x17 -> 0x00412E10`, `+0x32 -> 0x0040EC90` |
| `0x00414440` PMR vector destructor | **20B/10 i386** | `+0x420`, `+0x885` | `+0x0A -> 0x00414E10` |
| `0x00414F30` unchecked begin | **26B/12 i386** | `+0x24B`, `+0x613` | `+0x0E -> 0x0040B280` |
| `0x00414F70` unchecked end | **26B/12 i386** | `+0x25C`, `+0x624` | `+0x0E -> 0x0040B280` |

The complete native original body SHA values for these four distinct
physical code heads are pinned by
[`verify-glyph-mask-composite2245-native.py`](../scripts/verify-glyph-mask-composite2245-native.py),
which independently validates all original nested E8 destinations,
the genuine original source parent's full 2,245B/612 instructions,
**37 E8/five PE HIGHLOW**, and two separate native call sites for
each helper. No original GDI image or proprietary bitmap resource is
committed. Ordinary C++20 emits exact native code for each helper,
all complete extents and independently native-verified relocations.

The canonical unit replay is intentionally restricted to these four
*complete individual library functions* and the existing glyph view
units affected by the shared declaration. One new canonical object
contains the nested PMR methods; the **2,245B parent itself does not
have an exact match unit**:

```text
glyph_mask_offsets_vector_ctor_63: exact (63/63 bytes)
glyph_mask_offsets_vector_dtor_20: exact (20/20 bytes)
glyph_mask_offsets_vector_begin_26: exact (26/26 bytes)
glyph_mask_offsets_vector_end_26: exact (26/26 bytes)
Exact replay of affected glyph sources: 12/12 units, 5 cold objects
```

This adds **four whole-exact standard-library/generic physical heads,
135 distinct original executable `.text` bytes**. Their original
implementation ownership is `origin=unknown/review` and earns **zero
new game-authored exact heads/bytes**. The original game-authored
2,245B compositor remains NONEXACT, as do the 2,227B GDI text core
and other unaccepted bosses. The already whole-exact 681B GDI bitmap
creator, 104B fallback, 82B selector, 182B cleanup and four 20B
canvas getters remain independent accepted code. This checkpoint
used no project-wide cold replay.

```sh
scripts/repo-python scripts/verify-glyph-mask-composite2245-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp \
  --source src/GlyphCanvasEnsure104.cpp \
  --source src/GlyphCanvasCreate681.cpp \
  --source src/GlyphCanvasFormatLookup82.cpp \
  --source src/GlyphCanvasRelease182.cpp
```

## CORE/RECON-1053 — original packed 16-bit color local recovered

The native `0x00414280` ARGB4444 color default ctor invoked by this
2,245B Boss at `+0x505` is now [a separate full 22/22 strict unit](GLYPH_PACKED_COLOR4444_CTOR22_STRICT_EXACT.md).
Its `NativeGlyphColor4444` value is now default constructed within
the real 16-bit branch before color nibbles are assigned, following
the already exact 24B `PackedColor` constructor invoked at `+0x4FD`.
The main Boss now compiles 1,987B/538 instructions (27 E8/5 DIR32)
versus native 2,245B/612; it remains NONEXACT. Four original PMR-vector
children and this 22B color ctor all still replay exact in one object.
