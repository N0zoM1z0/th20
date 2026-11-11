# Glyph Mask 2,245B Boss — real RGBA4444 source pixel stride and full E8 graph

The immutable Japanese TH20 v1.00a Steamless target (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
has the complete **2,245B/612-i386** GDI stencil compositor at
`0x00416420`, whole SHA-256
`06b62972af7ef2644b5a17d032b4124525d9b6aab0a5097f740ec777d14a40ad`.
Its full physical original contains **37 E8 / 5 PE HIGHLOW**, including
exactly **nine** E8 to the existing native `pixel_stride_4156c0` at
`+0x32,+0x197,+0x1D7,+0x5A6,+0x5E7,+0x69B,+0x6FA,+0x752,+0x7B4`.
Four further E8 call the native folded 22B `std::array<int32_t,2>`
index helper, already exact as its own physical code owner.

## Actual live source address in the 16-bit per-pixel path

Earlier source had only eight stride getter calls: its RGBA4444
pixel loop captured a single `original` bitmap base and indexed four
reflected neighbors directly. The original executes its **ninth** live
stride getter at `+0x5E7` after the inner `x<end` condition but
**before** the vector-offset iterator is built. It multiplies the live
stride by `y`, divides the signed product by two (round toward zero),
adds `x`, and forms a real `uint16_t*` sample address from the original
bitmap. A separate getter in each eligible reflected-neighbor condition
then computes that neighbor's live address and checks its alpha nibble.

The maintained `src/GlyphMaskComposite2245.cpp` now uses one mutable,
**genuinely used stencil pointer** for both the current sampled pixel
and each guarded neighbor. Its first address reads the actual per-pixel
stride; subsequent checked neighbor tests update the pointer and read
`(*stencil >> 12)`. Each sample uses signed **multiply-before-divide**
address arithmetic, rather than the earlier `(stride / 2) * y` that can
round differently. Thus the extra call is an original observable getter
within the actual pixel-processing data flow, **not** a dummy call,
unused padding local, invented branch or patched target code.

The earlier BGRA32 update edge remains in the real `for` increment,
and the original four array-index calls remain present. The one native
`bitmap_pixels_4156a0()` call is still performed before its allocator/
`memcpy` snapshot, not repeatedly for each pixel.

## Full source and original comparison

The real pinned-MSVC 19.44 i386 C++20 profile is
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The current source is **SOURCE-PRESENT, NONEXACT**:

| Entire function evidence | Previous source | Current source | Original |
| --- | ---: | ---: | ---: |
| Complete code bytes | 2,061 | **2,141** | 2,245 |
| Complete i386 instruction count | 545 | **565** | 612 |
| Physical E8 / compiled REL32 count | 36 | **37** | 37 |
| Physical HIGHLOW / compiled DIR32 | 5 | **5** | 5 |
| Native stride / candidate stride E8 | 9 / 8 | **9 / 9** | 9 / 9 |
| Original-target call roles in order | 23-role prefix | **37/37** | 37/37 |
| E8 opcode positions exactly aligned | 1 | **2** | 37 |
| Folded two-int32 array-index calls | 4 | **4** | 4 |

Both the native PE's *real* physical target destinations and the
candidate COFF symbol prefix roles are checked in **all 37** positions,
including `+0x5E7`. Every candidate REL32 is a genuine E8 operand.
All five original PE HIGHLOW roles are separately checked against the
actual candidate DIR32 symbols. The 565/612 instruction difference,
remaining 104B original code-size gap, differing stack slots/EH state,
and most physical call/data locations mean the parent is **not exact**;
matching a full call-role census does **not** grant 2,245B game bytes.

### Bounded reproduction

```sh
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
scripts/repo-python scripts/verify-glyph-mask-offset-array2-native.py \
  --candidate-object build/core1052-canonical/GlyphMaskComposite2245.obj
scripts/repo-python scripts/validate-tracking.py --require-target
```

Only the changed glyph compositor's **one source object** was cold
replayed: **24/24** previously accepted PMR/color generic descendants
remained strict whole-native exact. The separately original-exact folded
22B array helper does **not** receive duplicate credit; there was **no
full or unfiltered cold replay**. Next: recover actual 16-bit stencil
iterator/pointer-stack lifetime and the remaining original 104B of
compiler control flow, without losing any of the 37 call roles.
