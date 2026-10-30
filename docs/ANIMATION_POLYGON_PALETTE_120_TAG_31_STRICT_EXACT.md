# CORE/RECON-889/890/891 — original 120B polygon palette and two 31B tagged leaves native strict exact

The target is the immutable Japanese TH20 v1.00a Steamless executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint supplies ordinary C++ source for **three separate whole
native methods** on the genuine `0x3D4`-byte polygon segment records
used by the independently strict
[296B group configuration Boss](ANIMATION_POLYGON_GROUP_CONFIG_296_STRICT_EXACT.md).
All original game code extents, E8 calls and HIGHLOW relocations were
independently attested from the locked PE before comparing compiled COFF.

| Whole original method | Palette initializer | Color-tag forwarder | Radius-tag forwarder |
| --- | --- | --- | --- |
| Original game code head | `0x0045FC90` | `0x0045FFC0` | `0x0045FFA0` |
| Entire native length / x86 heads | **120B /39** | **31B /14** | **31B /14** |
| Physical original E8 sites/targets | **5/5** | **1/1** | **1/1** |
| Genuine original PE HIGHLOW fields | **1/1** | **0** | **0** |
| Original frame / return | `0x18`, `ret 4` | one saved ECX, `ret 4` | one saved ECX, `ret 4` |
| Nonrelocation bytes equal | **96/96** | **27/27** | **27/27** |
| Complete native strict replay | **120/120 exact** | **31/31 exact** | **31/31 exact** |
| Authored-game code credit | **120B** | **0B (origin pending)** | **0B (origin pending)** |

## Original PE and exact gameplay-facing operations

[`scripts/verify-animation-polygon-palette120-native.py`](../scripts/verify-animation-polygon-palette120-native.py)
reads the original executable `.text` and `.reloc` without consulting
candidate source. It validates all **39+14+14 native instruction heads**,
complete function boundaries, the five original palette E8 sites to
`PackedColor::PackedColor(uint32)` `0x004142A0`, the 31B color-tag
forwarder `0x0045FFC0`, `Vector3::operator[]` `0x00414580`,
`PackedColor::operator=(uint32)` `0x0045D650`, and the 31B radius
forwarder `0x0045FFA0`. The single actual PE HIGHLOW field at
palette offset **`+0x5C`** targets the genuine **32.0f** constant at
`0x0056CD94`. The original 296B group configuration Boss calls
this palette function three times, at genuine native E8 locations
`0x0045FBDE`, `0x0045FC01`, `0x0045FC24` with three distinct original
packed colors.

The 120B game source computes a packed-color local from the input
word, forwards its address through the real color-tag wrapper, then
resets the indexed **first `PackedColor` element** at original segment
`+0x1E8` to zero through the original two member calls. It finally
passes a true local float **32.0f** to the radius-tag wrapper rooted
at segment `+0x2DC`. Its real frame is `sub esp,0x18`; the original
has three meaningful `/Od` source-scope `NOP` sites `+0x2C`, `+0x4B`,
`+0x71` and **no compiler security-cookie prologue/epilogue**.

The two true 31B methods are native thiscall wrappers taking one
pointer argument and passing an owner pointer, an actual distinct
integer **tag**, and the pointer to a cdecl downstream routine:
color tag `0x3D` targets `0x0045D430`; radius tag `0x3E` targets
`0x0045D360`. Both correctly clean the three arguments of the
outbound cdecl (`add esp,0xC`) and return by `ret 4`. Their physical
original E8 site at offset **`+0x11`** and original absolute targets
are verified independently; neither native original has HIGHLOW
fields. They may have originated in compiler-instantiated typed
field helpers rather than hand-written game methods. Accordingly
**both are accepted whole strict units with source mappings but not
credited to authored game code pending original provenance**.

## Correct source lifetimes and compiler profile are not fake NOP padding

The ordinary, maintained natural C++
[`src/AnimationPolygonPalette120.cpp`](../src/AnimationPolygonPalette120.cpp)
uses the same real `NativePolygonSegmentSlot` type as the accepted
296B/233B group methods, now defined once in
[`src/NativePolygonSegmentSlot.hpp`](../src/NativePolygonSegmentSlot.hpp).
No duplicate original receiver class or new runtime object is made.

The initial code compiled in the existing group translation unit with
`/GS /sdl`, generating **142B/44 x86**: a cookie not present in the
original and an unnecessary pointer-return stack spill. A bounded
compiler profile experiment showed that the original native 120B
uses a distinct translation-unit behavior consistent with `/GS`
**without `/sdl`**. With the index-zero source expressed as an actual
`PackedColor&` assignment, the candidate emitted **118B/37 x86**;
placing the real color-index local into its own meaningful scope
reproduced the original two native scope-boundary NOPs and yielded
**120B/39 x86**. No inline assembly, `nop` source, object patching,
volatile trick or inert variable was used. Both tagged 31B wrappers
compile to their exact original extents under this same real profile.

The original previously accepted 296B configuration, 233B draw group
and 23B/19B native array helpers require `/sdl` in their own pinned
source profile. The palette method is therefore **in a separate
translation unit**, rather than changing the compiler profile of
four already exact functions. The shared slot header and separate
palette source preserve all original symbol identities and allow
actual group code to link to the newly defined palette method.

## Consecutive original 16.0f/32.0f `.rdata` is also complete

The separate [game data translation unit](../src/AnimationPolygonWidths8.cpp)
defines two genuine external float constants
`th20::native_sixteen` and `th20::native_polygon_radius32` as
**16.0f, 32.0f** in one ordinary `.rdata` region, at COFF offsets
`+0` and `+4`. The immutable original PE contains exactly these
**8 contiguous bytes at `0x0056CD90`**. The independent
[`scripts/verify-animation-polygon-widths8-data.py`](../scripts/verify-animation-polygon-widths8-data.py)
compares the entire original data region with the separate freshly compiled
`build/core890-probe/AnimationPolygonWidths8.obj` COFF
bytes and both real external symbol offsets: **8/8B exact**. The
16.0f global is also used by the separate 104B outline caller, which
remains SOURCE-PRESENT/NONEXACT. Defining the 32.0f symbol in the *same*
translation unit as the 120B caller instead caused MSVC to substitute
`__real@42000000`, breaking strict original COFF relocation identity.
The dedicated data translation unit preserves the real external reference
`?native_polygon_radius32@th20@@3MB` as well as the correct 8B contents. This newly restored native data is
**not game `.text` code credit**, nor proof that the whole game now
links and plays.

## Canonical strict replay, authorship and bounded scope

Three source units in
[`config/match-units.toml`](../config/match-units.toml) use exactly
one new pinned x86 MSVC C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /EHsc` object/receipt
`build/core889-canonical/AnimationPolygonPalette120.obj`:

```text
animation_polygon_palette_120: exact (120/120 bytes)
animation_polygon_color_forward_31: exact (31/31 bytes)
animation_polygon_radius_forward_31: exact (31/31 bytes)
Exact replay: 3/3 units, 1 cold objects
```

The existing group source provider, modified only to include the
shared slot header and move the palette definitions to their own
translation unit, was **separately cold-rebuilt and scoped replayed**:

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
animation_polygon_motion_config_296: exact (296/296 bytes)
Exact replay: 4/4 units, 1 cold objects
```

The original 104B outline caller remains NONEXACT; already strict
1204B polygon stroke and 455B filled fan children, and the large
5993B Animation Draw parent, are not falsely promoted. **No complete
unfiltered cold replay** was run.

This checkpoint adds **one original-authored whole native game function
and 120 `.text` bytes**, plus two origin-pending but independently
whole-strict 31B wrappers and one exact 8B native data source. The
live authored-game inventory becomes **635 exact functions /233,615
native original code bytes**, **1,287 source-present mappings /1,286
canonical strict units /298 pinned compiler object/receipt
providers**. Authored credit deliberately excludes the two 31B
unknown-origin leaves, prior 23B/19B native array helpers and original
`.rdata` constants.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-palette120-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonPalette120.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp
nice -n 15 scripts/compile-probe.sh src/AnimationPolygonWidths8.cpp build/core890-probe/AnimationPolygonWidths8.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /EHsc
scripts/repo-python scripts/verify-animation-polygon-widths8-data.py --object build/core890-probe/AnimationPolygonWidths8.obj
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
