**CORE/RECON-1083 CURRENT SOURCE UPDATE (2026-11-25):** The RGBA4444
source now preserves the original grouped address expression
`row_offset + (x +/- delta_x)` rather than relying on left-associative
`row_offset + x +/- delta_x`. A two-byte `NativeGlyphAlpha4444` bitfield view
restores the four native 16-bit alpha-nibble extraction sequences (`mov` word,
`shr 12`, `and 0xf`) in natural C++. The complete maintained source now emits
**2,128B/561 i386, 37 E8/5 DIR32**. It preserves **37/37 original E8 target
roles**, **9/9 live stride getter roles**, **4/4 folded array-index roles**,
and **5/5 PE data-target roles**. It matches **292/1,960 ordinary
non-relocation bytes**; **7/37 physical E8 sites** and **4/5 PE HIGHLOW
site/target pairs** align, with aggregate E8 offset distance **819** (down
220 from the previous 1,039). The original 2,245B/612-i386 game Boss remains
**SOURCE-PRESENT/NONEXACT**, with a 117B/51-instruction gap; no parent
exactness credit is claimed. A sequential-four-`if` source variant was also
compiled and rejected (2,143B/565, 3/37 physical E8 sites, 1,075 aggregate
offset delta). The source-scoped replay rebuilt one object and preserved
**24/24** previously exact PMR/color descendants. Both
`verify-glyph-mask-offset-array2-native.py` and
`verify-glyph-mask-boss-live-pixels-native.py` attest the current candidate
against the pinned original.

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
- The RGBA4444 path now uses direct native-style early-exit control flow:
  the first non-opaque neighbor writes the packed outline value and jumps
  past the non-outline alpha-preserving write. This removes the per-pixel
  `touches_outline` flag and post-loop test while preserving the same four
  neighbor reads and pixel result. The prior candidate was **2,088B/549 i386** with 296/1,920 ordinary
  overlap bytes. The current grouped-address/bitfield candidate is
  **2,128B/561 i386**, 292/1,960 ordinary overlap bytes, 37/37 E8 target
  roles, 7/37 physical E8 sites and 819 aggregate E8 offset distance.


| Entire function evidence | First source | Earlier full-role source | Current source | Original |
| --- | ---: | ---: | ---: | ---: |
| Complete code bytes | 2,061 | 2,141 | **2,128** | 2,245 |
| Complete i386 instruction count | 545 | 565 | **561** | 612 |
| Physical E8 / compiled REL32 count | 36 | 37 | **37** | 37 |
| Physical HIGHLOW / compiled DIR32 | 5 | 5 | **5** | 5 |
| Native stride / candidate stride E8 | 9 / 8 | 9 / 9 | **9 / 9** | 9 / 9 |
| Original-target call roles in order | 23-role prefix | 37/37 | **37/37** | 37/37 |
| E8 opcode positions exactly aligned | 1 | 2 | **7** | 37 |
| PE HIGHLOW site/target pairs aligned | 2 | 2 | **4** | 5 |
| Folded two-int32 array-index calls | 4 | 4 | **4** | 4 |
| Aggregate absolute E8 offset distance | — | 1,196 | **819** | 0 |

Both the native PE's *real* physical target destinations and the
candidate COFF symbol prefix roles are checked in **all 37** positions,
including `+0x5E7`. Every candidate REL32 is a genuine E8 operand.
All five original PE HIGHLOW roles are separately checked against the
actual candidate DIR32 symbols. The 561/612 instruction difference,
remaining 117B original code-size gap, differing stack slots/EH state,
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
iterator/pointer-stack lifetime and the original 117B/51-instruction
compiler-control-flow gap, without losing any of the 37 call roles.

## 2026-11-25 follow-up: native RGBA4444 operand grouping and 16-bit alpha extraction

The original Ghidra expression computes each neighbor address as
`(stride * y) / 2 + (x +/- delta_x)`. The earlier C++ source wrote the same
mathematical result with left-associative `+ x +/- delta_x`, which emitted
separate add/sub instructions and shifted the subsequent stride calls. All
four expressions now retain the original horizontal grouping. The resulting
source compiles the neighbor address as a grouped horizontal operand before
adding it to the half-stride row offset.

The original four alpha tests load a 16-bit word and use 16-bit `shr 12` and
`and 0xf` before comparing the high nibble. A two-byte
`NativeGlyphAlpha4444` bitfield view (blue/green/red/alpha, four bits each)
expresses that source-level field read directly and reproduces those four
instruction sequences. This is a real packed-pixel representation, not a
compiler-only temporary or instruction shim.

The new complete candidate is **2,128B/561 i386**, with all **37/37 E8 target
roles**, all nine stride calls, four folded array-index calls and all five PE
data-target roles. It has **7/37** native E8 positions, **4/5** physical
HIGHLOW site/target pairs, **292/1,960** ordinary overlap bytes and **819B**
aggregate absolute E8 offset distance. The previous 2,088B candidate was
1,039B away; this is a 220B reduction. The remaining whole-function gap is
117B/51 instructions.

A sequential four-`if` translation of the native Ghidra control flow was also
compiled. It grew to 2,143B/565 instructions, fell to 3/37 aligned E8 sites
and regressed to 1,075B aggregate E8 offset distance, so the existing
short-circuit expression remains the better natural-C++ reconstruction.
The two native operand and bitfield changes are maintained; the parent is
still SOURCE-PRESENT/NONEXACT.


## 2026-11-25 follow-up: packed RGBA4444 bitfield write-shape matrix (not promoted)

The original RGBA4444 branch performs four separate channel-nibble updates
when constructing the outline word, and three separate destination nibble
updates when preserving destination alpha. A natural C++ `union` view of the
16-bit word was tested to model those operations with four-bit fields rather
than a single packed-word expression. The source remains ordinary C++; no
inline opcodes or padding are involved.

| Probe | Code / i386 heads | E8 sites | E8 offset delta | Ordinary bytes |
| --- | ---: | ---: | ---: | ---: |
| Current packed-word source | **2,128B / 561** | **7/37** | **819** | **292/1,960** |
| Four source-channel bitfield assignments only | 2,193B / 573 | 7/37 | 1,158 | 269/2,025 |
| Three destination-channel bitfield assignments only | 2,216B / 584 | 3/37 | 830 | 207/2,048 |
| Both source and destination bitfields | 2,286B / 596 | 3/37 | 1,680 | 174/2,077 |

The union probes preserve all 37 E8 target roles, all nine live stride calls,
four folded array-index calls and five DIR32 roles. They do not improve the
physical call/data layout: source-channel bitfields shift the live-stride
frontier, while destination bitfields move the cleanup and return path without
recovering the original instruction boundaries. The combined representation
is 41B larger than the original 2,245B body and still has 16 fewer i386
instruction heads. The maintained packed-word expression therefore remains
the better whole-function C++ reconstruction: it keeps 7/37 physical E8
sites, 4/5 PE HIGHLOW site/target pairs, 819 aggregate E8 offset distance and
292 ordinary overlap bytes. These bitfield variants are retained as
reproducible probes only; no source promotion or authored-byte credit is
claimed.

## 2026-11-25 follow-up: PMR insertion/growth chain source recovery

The same maintained `GlyphMaskComposite2245.cpp` now specializes the old MSVC
PMR vector insertion members in natural C++. The 8B `std::move` leaf is
byte-exact; the 108B/40, 140B/52 and 488B/170 helper bodies match every
non-relocation byte and every original E8 position. The 488B helper also
preserves both native HIGHLOW field positions as COFF DIR32 relocations. The
35B public wrapper is a 34B/14 candidate with both native E8 sites and one
native NOP omitted; the 200B/65 uninitialized-move body, 92B/34 backout
member and 31B/14 allocator bridge now match every non-relocation byte and
native E8 position. Their target identities still differ at the old 78B
allocator-construction leaf.

The targeted source cold replay rebuilt one object and retained 24/24 exact
PMR/color descendants. The parent remains 2,128B/561 versus native 2,245B/612,
with 37/37 E8 target roles, 7/37 aligned physical E8 sites, 292/1,960 ordinary
overlap bytes and 819 aggregate E8 offset distance. No whole-parent exactness
or game-authored byte credit is claimed. See
[the five-parent PMR frontier](GLYPH_OFFSET_PMR_FIVE_PARENTS_NATIVE_FRONTIER.md)
and [the complete insertion verifier](../scripts/verify-glyph-mask-emplace35-native.py).
