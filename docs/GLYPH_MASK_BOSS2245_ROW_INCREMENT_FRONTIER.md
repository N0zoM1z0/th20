**CORE/RECON-1082 CURRENT SOURCE UPDATE (2026-11-25):** The RGBA4444
neighbor loop now follows the native early-exit/write topology directly in
ordinary C++: an outline hit writes the packed color and jumps past the
non-outline alpha-preserving write. This removes the per-pixel
`touches_outline` flag and its post-loop branch without inline assembly,
manual bytes or synthetic calls. The complete maintained source now emits
**2,088B/549 i386, 37 E8/5 DIR32** (down 18B/six instructions from the
2,106B/555 candidate). The candidate preserves **37/37 original E8 target
roles**, **9/9 live stride getter roles**, **4/4 folded array-index roles**,
and **5/5 PE data-target roles**. It matches **296/1,920 ordinary
non-relocation bytes**; **7/37 physical E8 sites** and **4/5 PE HIGHLOW
site/target pairs** align, with aggregate E8 offset distance **1,039**.
The whole 2,245B/612-i386 game Boss remains **SOURCE-PRESENT/NONEXACT**;
no parent exactness credit is claimed. The source-scoped replay rebuilt one
object and preserved **24/24** previously exact PMR/color descendants.
Both `verify-glyph-mask-offset-array2-native.py` and
`verify-glyph-mask-boss-live-pixels-native.py` now attest this full candidate
against the pinned original.

**PREVIOUS SOURCE UPDATE (2026-11-24):** The complete source now compiles to
**2,106B/555-i386**, retaining all **37/37 E8 target roles**, **9/9 live
stride calls**, and all four genuine folded `std::array<int32_t,2>` index
calls. A direct `pixel_stride*rows` length expression restores the original
first three physical E8 sites; typed `PackedColorChannels::alpha` reads restore the destination pixel-alpha
load and all four stencil neighbor byte loads, while aligning vector begin/end and both
first-branch array-index E8 sites. The BGRA32 path keeps its stencil pointer
alive across the row loop and writes the four-byte channel aggregate only on
the outline branch, preserving destination alpha on the non-outline branch.
The current candidate has **7/37 physical E8 sites**, **4/5 PE HIGHLOW
site/target pairs**, and aggregate E8 offset distance **945**. It remains
SOURCE-PRESENT/NONEXACT against the original **2,245B/612-i386** parent; no
game-authored parent bytes are credited. Scoped replay after the shared
`PackedColor` layout change passed **24/24** previously exact PMR/color
descendants. Older source totals below are historical.

# Glyph Mask 2,245B Boss — real row-increment E8 call-order recovery

The locked Japanese TH20 v1.00a Steamless target has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The entire original game-owned glyph compositor at `0x00416420` is
**2,245B/612 i386**, SHA-256
`06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad`,
with **37 real E8 /five PE HIGHLOW**. The two native 0x15/0x1A pixel
branches and independently exact 24-function PMR/color source family
are described in the [whole-Boss evidence](GLYPH_MASK_BOSS2245_LIVE_BITMAP_FRONTIER.md)
and [true array-index ABI](GLYPH_MASK_OFFSET_ARRAY2_NATIVE_TYPE.md).

## Source control flow, not a synthetic call

In the native BGRA32 outer row loop, the original update edge at
`+0x1CB..+0x1E7` increments row `y`, then invokes the real
`pixel_stride_4156c0` at E8 `+0x1D7`, adds its result to the live
row-byte accumulator, and **only then** checks `y < rows` at `+0x1E8`.
The previous source performed `row_advance+=pixel_stride_4156c0()` as
the final statement of the loop body. It had the right effect but
pinned `/Od` compiled the getter at E8 `+0x41A`, **after** all BGRA32
neighbor tests in the physical instruction stream.

The maintained `src/GlyphMaskComposite2245.cpp` instead expresses the
native loop edge directly with a real, used `for` update expression:

```cpp
std::int32_t row_advance=0;
for (std::int32_t y=0;y<rows;
     ++y,row_advance+=pixel_stride_4156c0()) {
    // ... actual stencil/outline operations ...
}
```

There is no extra getter, bogus temporary, unreachable branch, inline
assembly, manual NOP or target-byte patch. This preserves the true
live-stride semantics and original row/column bounds. The scoped MSVC
candidate still emits **2,061B/545 i386, 36 E8/five DIR32**, but
its loop-update E8 is now at `+0x1B5` rather than `+0x41A`. Native
`+0x1D7` is not yet physically aligned; the source is NOT exact.

The first **23 candidate E8 roles now match the first 23 original
physical E8 callee roles in sequence**, including the row-loop stride
call immediately after the first-row stride getter. Prior source
only matched the first nine roles before the call-order divergence.
The first BGRA32 index helper E8 positions are now candidate
`+0x2A2/+0x2B4` (COFF relocation fields `+0x2A3/+0x2B5`) versus
original `+0x29E/+0x2B0`. The following original *additional*
RGBA4444 per-pixel stride E8 at `+0x5E7` remains absent from the
source's 36-call graph. Adding a redundant, unused pixel pointer or
an unneeded stride call would be a false way to close this gap.

**Whole-Boss status: SOURCE-PRESENT, NONEXACT.** Full original boundary,
all 37 original call destinations and five PE relocation fields are
independently pinned. No newly exact game-original function or byte
credit is claimed from the improved source call order.

## Focused, reproducible verification

Only the affected C++ file was rebuilt under pinned MSVC 19.44 i386:

```sh
nice -n 15 scripts/compile-probe.sh \
  src/GlyphMaskComposite2245.cpp \
  build/gptweb-probe/GlyphMask2245_mainline.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
scripts/repo-python scripts/verify-glyph-mask-offset-array2-native.py \
  --candidate-object build/gptweb-probe/GlyphMask2245_mainline.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

The **entire 24/24 affected accepted generic/color descendants were
strict exact after one cold-compiled source object**, including the
PMR vector growth/backout descendants. No full graph cold replay was
run. The separate 22B folded index callee was already exact under
its own canonical source, and receives no duplicate credit.

Next native questions are the **real 16-bit per-pixel stride and base
pointer lifetime** around `+0x5E7..+0x678`, and the remaining
scalar/PMR loop ordering responsible for the 184B/67-instruction
difference between source and original. Both must be solved as real
source logic, not by adding unused locals or patching exact bytes.
