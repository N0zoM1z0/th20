**CORE/RECON-1080 CURRENT SOURCE UPDATE:** The native 8B glyph-offset object now uses a real [two-int32 indexed `std::array` instead of the historical plain struct](GLYPH_MASK_OFFSET_ARRAY2_NATIVE_TYPE.md). The complete current source parent is **2,061B/545 i386, 36 E8/5 DIR32** (original whole **2,245B/612 i386, 37 E8/5 HIGHLOW**). Four native folded index calls are present, and the 15 earlier PMR/color strict units still replay exact with the corrected vector template type. Earlier 2,041B/1,987B snapshots below are historical.

# CORE/RECON-1054 — four whole-native PMR vector lifecycle heads, 230 strict-exact bytes

Locked target: Japanese TH20 Steamless v1.00a SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-owned **2,245B** glyph mask/compositor Boss at
`0x00416420` constructs and destroys two **16-byte
`std::pmr::vector<GlyphMaskOffset>`** instances for the separate 32-bit
and 16-bit outline modes. Its four directly called 63B/20B/26B/26B
vector template functions are already whole-exact from the same
source owner. Following the actual native E8 dependency graph
revealed four more **distinct complete physical** standard-library
implementations nested under those native vector operations.

| Original physical head | Complete native extent | Actual original parent E8 | Original nested calls |
| --- | ---: | --- | --- |
| `0x00415820` `std::pmr::get_default_resource` | **10B/5 i386** | 24B PMR allocator ctor `+0x07` | `+0x03 -> 0x00541550` genuine aligned/default resource |
| `0x004141A0` `polymorphic_allocator<GlyphMaskOffset>` default ctor | **24B/11 i386** | 43B compressed-pair ctor `+0x11` | `+0x07 -> 0x00415820` default resource |
| `0x00412E10` vector `_Compressed_pair` default ctor | **43B/17 i386** | native 63B vector ctor `+0x17` | `+0x11 -> 0x004141A0` PMR allocator and `+0x1C -> 0x00414090` already exact vector value ctor |
| `0x00414E10` vector `_Tidy` destructor | **153B/54 i386** | native 20B vector dtor `+0x0A` | `+0x0C -> 0x0040F160` existing allocator getter, `+0x38 -> 0x0040E5E0` orphan-all, `+0x56 -> 0x0040C6B0` trivial destroy-range, `+0x75 -> 0x004154C0` real allocator deallocate |

Each complete native body has **zero original PE HIGHLOW** fields.
The original SHA-256, entire instruction extent through native
`ret`, all eight original E8 destinations and the genuine parent
E8 positions are independently verified in
[`verify-glyph-pmr-vector-lifecycle-native.py`](../scripts/verify-glyph-pmr-vector-lifecycle-native.py).
The complete **2,245B/612-i386** game parent and its two real direct
PMR-vector constructor/destructor caller sites were independently
verified in
[`verify-glyph-mask-composite2245-native.py`](../scripts/verify-glyph-mask-composite2245-native.py).
The previously accepted physical 43B vector-value constructor at
`0x00414090`, 19B allocator getter at `0x0040F160`, 11B orphan-all
at `0x0040E5E0` and 5B destroy-range at `0x0040C6B0` are **not
accepted again**; neither is the original 13B container proxy
`0x0040EC90` that is called by the distinct 63B vector constructor.

All four new methods are naturally compiled by the actual
[`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
program, which holds two real PMR vectors of
[`GlyphMaskOffset`](../src/NativeGlyphMaskOffsets.hpp) for the
game-specific glyph outline algorithm. The original template bodies
are not copied from disassembly or maintained as four artificial
standalone wrappers. One **existing pinned MSVC 19.44 i386** C++20
source object emits all four exact methods alongside the earlier
exact constructor, destructor, unchecked begin/end and 22B glyph
packed-color local:

```text
glyph_mask_offsets_vector_ctor_63: exact (63/63 bytes)
glyph_mask_offsets_vector_dtor_20: exact (20/20 bytes)
glyph_mask_offsets_vector_begin_26: exact (26/26 bytes)
glyph_mask_offsets_vector_end_26: exact (26/26 bytes)
glyph_packed_color4444_ctor_22: exact (22/22 bytes)
glyph_mask_default_resource_10: exact (10/10 bytes)
glyph_mask_pmr_allocator_ctor_24: exact (24/24 bytes)
glyph_mask_compressed_pair_ctor_43: exact (43/43 bytes)
glyph_mask_vector_tidy_153: exact (153/153 bytes)
Exact replay: 9/9 units, 1 cold objects
```

These are **four additional whole native strict units /230 distinct
original `.text` bytes**. They are generic, compiler/STL-owned
physical functions (`origin=unknown/review`) and earn **zero
new game-authored heads or bytes**. The enclosing original 2,245B
compositor remains **SOURCE-PRESENT/NONEXACT**, at its previously
independently evidenced C++20 1,987B/538-i386 candidate versus
2,245B/612 native (27 vs 37 E8, both with five DIR32/HIGHLOW).
The actual 2,227B GDI text core and 578B text formatter also remain
separate unresolved Bosses; their child exactness is not inferred.
No shared source header or canonical profile changed for this
checkpoint, and no project-wide cold replay ran.

```sh
scripts/repo-python scripts/verify-glyph-pmr-vector-lifecycle-native.py
scripts/repo-python scripts/verify-glyph-mask-composite2245-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
```
