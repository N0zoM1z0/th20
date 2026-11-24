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
The current source is **SOURCE-PRESENT, NONEXACT**. The 2026-11-24
source checkpoint now records four natural lifetime/dataflow corrections:

- The snapshot length is now expressed directly as
  `pixel_stride_4156c0()*rows`, removing a redundant `row_stride` local and
  restoring the original first three physical E8 sites (`+0x32`, `+0x44`,
  `+0x61`).
- The BGRA32 path hoists the original-buffer stencil pointer once before its
  row loop. Its live pixel-alpha test now uses the typed
  `PackedColorChannels::alpha` byte view, naturally restoring the original
  `movzx [pixel+3]` access and aligning the vector begin/end calls plus both
  folded array-index calls. The outline path flips the packed alpha byte and
  assigns the four-byte BGRA channel aggregate; the non-outline path writes
  only B/G/R and preserves destination alpha.
- Both stencil-offset generators now preserve the original short-circuit
  operand order: test `delta_y != 0` before `delta_x != 0`. The predicates are
  equivalent, but this recovers the native branch evaluation order in both
  pixel-format paths without changing code size, call roles, or runtime data.
- The four BGRA32 neighbor tests now read `PackedColorChannels::alpha`
  directly instead of loading a 32-bit pixel and shifting by 24. This emits
  the original byte-at-`+3` alpha loads in all four bounds-checked paths.
  The complete candidate shrinks by 4B/4 instructions and gains 21 ordinary
  overlap-byte matches (283/1,938 versus 262/1,942); E8 physical alignment
  remains 7/37 while aggregate call-offset distance moves from 927 to 945.
- The preceding 2,110B/559 candidate had **7/37 physical E8 sites** and
  **4/5 PE HIGHLOW site/target pairs** aligned, with aggregate E8 offset
  distance 927. The current typed-stencil candidate retains those same
  physical-site/role counts and improves ordinary byte agreement; its E8
  offset distance is 945.


| Entire function evidence | First source | Earlier full-role source | Current source | Original |
| --- | ---: | ---: | ---: | ---: |
| Complete code bytes | 2,061 | 2,141 | **2,106** | 2,245 |
| Complete i386 instruction count | 545 | 565 | **555** | 612 |
| Physical E8 / compiled REL32 count | 36 | 37 | **37** | 37 |
| Physical HIGHLOW / compiled DIR32 | 5 | 5 | **5** | 5 |
| Native stride / candidate stride E8 | 9 / 8 | 9 / 9 | **9 / 9** | 9 / 9 |
| Original-target call roles in order | 23-role prefix | 37/37 | **37/37** | 37/37 |
| E8 opcode positions exactly aligned | 1 | 2 | **7** | 37 |
| PE HIGHLOW site/target pairs aligned | 2 | 2 | **4** | 5 |
| Folded two-int32 array-index calls | 4 | 4 | **4** | 4 |
| Aggregate absolute E8 offset distance | — | 1,196 | **945** | 0 |

Both the native PE's *real* physical target destinations and the
candidate COFF symbol prefix roles are checked in **all 37** positions,
including `+0x5E7`. Every candidate REL32 is a genuine E8 operand.
All five original PE HIGHLOW roles are separately checked against the
actual candidate DIR32 symbols. The 555/612 instruction difference,
remaining 139B original code-size gap, differing stack slots/EH state,
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
full or unfiltered cold replay**. Next: recover the remaining 16-bit stencil
iterator/pointer-stack lifetime and the original 139B/57-instruction
compiler-control-flow gap, without losing any of the 37 call roles.
