# CORE/RECON-1056 — three full-native PMR vector growth children (16B /165B /81B exact)

Target: immutable Japanese TH20 v1.00a Steamless executable SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

The original **488B/170-instruction** vector growth/reallocation Boss at
`0x004133E0` has original complete SHA-256
`5e5ecf3d3ff27b00fd364a728acb23dcae883c179f8e5d3e1fdde93788697b57`,
**14 real native E8** and **two genuine HIGHLOW** fields (`+0x06`
EH `0x00567CED`; `+0x15` security cookie `0x005B25C0`). The genuine
`std::pmr::vector<GlyphMaskOffset>` in the game-owned 2,245B glyph
compositor instantiates a matching semantic source for this reallocation
path. Under pinned MSVC 19.44 i386 C++20 the generated full candidate
is **467B/163 instructions, 13 E8/2 DIR32**, so the 488B parent is
SOURCE-PRESENT, **NONEXACT**. Its physical extent is not truncated.

Three deeper native code heads called by that full original 488B Boss
are now independently **whole strict exact** from the *same existing*
[`GlyphMaskComposite2245.cpp`](../src/GlyphMaskComposite2245.cpp)
translation unit:

| Exact physical head | Complete code | Native 488B original E8 caller | Its independently native-verified calls/fields |
| --- | ---: | --- | --- |
| `0x00414FE0` vector `_Xlength` | **16B/7 instructions** | `+0x79` | original error diagnostic `+0x04` HIGHLOW `0x0056C7C0`, actual E8 `+0x08 -> 0x00540ED5` |
| `0x00414960` `_Change_array` | **165B/62 instructions** | `+0x1A9` | 4 real E8: allocator `0x0040F160`, orphan `0x0040E5E0`, destroy `0x0040C6B0`, deallocate `0x004154C0` |
| `0x004144E0` `_Reallocation_guard` destructor | **81B/33 instructions** | `+0x1C5` | 2 native E8: destroy `0x0040C6B0`, deallocate `0x004154C0` |

SHA-256 of those complete original physical bodies, independent original
call offsets and PE HIGHLOW roles are verified by
[`verify-glyph-vector-growth-leaves-native.py`](../scripts/verify-glyph-vector-growth-leaves-native.py).
The full **488B/170** parent and all **14 E8/2 HIGHLOW** are independently
attested by
[`verify-glyph-vector-growth488-native.py`](../scripts/verify-glyph-vector-growth488-native.py),
which separately checks the authentic MSVC candidate **467B/163**
without falsely admitting the original 488B whole extent.

The natural source-generated methods reproduce all three complete
function bodies and all independently anchored native relocations:

```text
glyph_vec_growth_xlength_16: exact (16/16 bytes)
glyph_vec_growth_change_array_165: exact (165/165 bytes)
glyph_vec_growth_reallocation_guard_81: exact (81/81 bytes)
Exact replay: 12/12 units, 1 cold object (same existing glyph source owner)
```

**Three distinct original native exact heads /262 original `.text` bytes**
are newly covered. They are compiler/standard-library template bodies
(`origin=unknown/review`), so **game-authored head/byte credit is zero**.
The original 488B vector growth Boss, 108B downstream insertion backend,
35B glyph offset insertion wrapper and 2,245B game compositor remain
separate unfinished functions. No already accepted 153B vector `_Tidy`,
PMR allocator or previously exact native method is double-counted.

```sh
scripts/repo-python scripts/verify-glyph-vector-growth-leaves-native.py
scripts/repo-python scripts/verify-glyph-vector-growth488-native.py \
  --candidate-object build/core1052-canonical/GlyphMaskComposite2245.obj
nice -n 15 scripts/repo-python scripts/replay-exact-units.py \
  --source src/GlyphMaskComposite2245.cpp
```

## CORE/RECON-1064 — true nested PMR max-size helpers exact

The original 488B vector growth Boss also calls a now
[WHOLE EXACT 59B PMR vector `max_size`](GLYPH_PMR_EXTRA_59_13_22_STRICT_EXACT.md)
at native E8 `+0x6F`; its further original 13B allocator-traits
`max_size` is exact, as is the separate physical 22B construction
wrapper. They contribute another 94 native STL bytes, zero authored
game byte credit, and do not close the 488B/2,245B original parents.

## CORE/RECON-1081 — nine deeper original PMR vector children now exact

The full original 488B vector-growth Boss and its exception-safe
200B/140B construction subtrees now have [nine additional whole-exact
original STL descendants, totaling 361 distinct native bytes](GLYPH_VECTOR_GROWTH_DEEP_NINE_STRICT_EXACT.md):
84B growth calculator, 19B allocator-at-least, 58B PMR allocation,
42B overflow-size helper, 36B capacity, 42B/28B/39B backout
constructor/release/destructor, and 13B orphan-range.
All are ordinary C++20 generated from the corrected native two-int32
array vector and replay **24/24** strict units in one affected source
object. The original 488B and 2,245B parents are still NONEXACT,
and generic source is not credited to game-authored `.text`.
