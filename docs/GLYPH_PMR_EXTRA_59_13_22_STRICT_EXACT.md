# CORE/RECON-1064 — three complete PMR glyph-vector functions: 59B, 13B and 22B strict exact

Pinned Japanese TH20 v1.00a Steamless executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original **2,245B** glyph mask-compositing Boss contains two genuine
`std::pmr::vector<GlyphMaskOffset>` scopes. The native **488B vector
reallocation Boss** `0x004133E0` (`CORE/RECON-1056`) itself remains
SOURCE-PRESENT/NONEXACT, but following its actual original E8 call
`+0x6F` reveals an additional complete physical STL `max_size`
function. A further direct E8 under that code leads to a distinct
13B allocator limit helper; the same natural glyph-mask C++ source
also emits a 22B allocator-traits `construct` method. The new three
complete physical original source heads are:

| Native original head | Full original extent | Original call relationship |
| --- | ---: | --- |
| `0x004162B0` PMR vector `max_size` | **59B/22 x86** | Original 488B vector `_Emplace_reallocate` E8 `+0x6F`, four genuine nested E8 to allocator, limits and `min` |
| `0x00416260` PMR allocator-traits `max_size` | **13B/6 x86** | Native 59B `max_size` E8 `+0x12`; one genuine E8 `+0x03` to original 0x004111E0 `_Max_limit` |
| `0x00415440` `_Normal_allocator_traits::construct` | **22B/11 x86** | Real nested 85B allocator `construct` is its sole E8 `+0x0E` target `0x00415460`; higher-level caller not yet independently established |

The independent locked PE verification
[`verify-glyph-pmr-extra-native.py`](../scripts/verify-glyph-pmr-extra-native.py)
SHA-pins all three **whole bodies** and their actual decoded original
instructions, original E8 target destinations and genuine parent call
edges where known, including the full 488B original parent SHA and
59B nested max-size owner. All three methods have **zero PE HIGHLOW**
fields. The native 22B construct helper has two ordinary source
specializations (lvalue/forwarded displacement) yielding the same
physical body, but is registered **only once** at its authentic
original address; semantic provenance stays under review.

The pinned MSVC 19.44 x86 C++20
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
compiler emits these three methods naturally from the **existing**
[`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
that performs real glyph stencil and native PMR vector operations.
There is no hand-written helper implementation or fabricated
runtime pointer table. The same canonical object also emits twelve
previously accepted distinct glyph-vector/color helper extents.
The scoped replay of **one affected provider** passes:

```text
glyph_vec_max_size_59: exact (59/59 bytes)
glyph_vec_allocator_max_size_13: exact (13/13 bytes)
glyph_vec_normal_traits_construct_22: exact (22/22 bytes)
Exact replay: 15/15 units, 1 cold object
```

These additions cover **three new distinct complete native generic
functions /94 original `.text` bytes**, not game-authored heads.
`function-origins.csv` retains `origin=unknown,disposition=review`
for these compiler/library functions. The original 488B and 2,245B
parent Bosses remain separately NONEXACT, and the existing 16B/165B/
81B vector-growth children and other exact functions are not
counted again. No full-graph cold replay was run.

```sh
scripts/repo-python scripts/verify-glyph-pmr-extra-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
```
