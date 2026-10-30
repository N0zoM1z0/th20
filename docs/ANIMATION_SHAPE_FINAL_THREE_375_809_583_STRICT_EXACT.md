# CORE/RECON-869/870/871 — whole original 375B POINTLIST, 809B alternating fan, and 583B alternating line strict exact

The immutable Japanese TH20 v1.00a Steamless original PE is locked at SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Three distinct game-authored complete renderer bodies have now been
reconstructed into ordinary C++ and strictly matched to their original
physical native code and all authentic relocation roles:

| Native original property | Point | Alternating-radius fan | Alternating-radius line |
| --- | ---: | ---: | ---: |
| Physical game code head | `0x0043D830` | `0x0043D9B0` | `0x0043DCE0` |
| Whole original `.text` body | **375B** | **809B** | **583B** |
| Full original x86 instruction heads | **100** | **214** | **160** |
| Original stack / return | `0x1C` / `ret 0xC` | `0x28` / `ret 0x20` | `0x28` / `ret 0x1C` |
| Original E8 site/destination roles | **5** | **8** | **6** |
| Original PE HIGHLOW field/target roles | **4** | **8** | **5** |
| Identical nonrelocation code bytes | **339/339** | **745/745** | **539/539** |
| Whole strict canonical native relocation replay | **375/375 exact** | **809/809 exact** | **583/583 exact** |
| Genuine D3D9 primitive type | `POINTLIST = 1` | `TRIANGLEFAN = 6` | `LINESTRIP = 3` |

## Independent original PE evidence

[`scripts/verify-animation-shape-final-three-native.py`](../scripts/verify-animation-shape-final-three-native.py)
reads the original PE `.text` and `.reloc` independently of each new
compiler object, confirms the entire three code extents, real native
stack/return, **19 E8 physical call site/destination pairs** and **17
HIGHLOW physical data field/target pairs**, and independently disassembles
the still-NONEXACT 5,993B main Animation Draw dispatcher to prove its
real parent E8 call locations:

- Point at `0x0043D830`: native caller `0x00444C57`; genuine
  `AnimationPoolOwner::flush_draws`, Graphics depth-disable,
  renderer color selection and two Graphics device getters, plus one
  original `1.0f` and three Graphics HIGHLOW fields.
- Alternating fan at `0x0043D9B0`: native caller `0x00444CED`;
  original flush, `polar2`, `add_angles`, Graphics depth/state,
  renderer color and two D3D9 device getters. Eight authentic
  HIGHLOW fields: two 1.0f, pi, 2.0f, four Graphics references.
- Alternating line at `0x0043DCE0`: native caller `0x00444D6E`;
  original flush, `polar2`, `add_angles`, renderer color and two
  D3D9 getters. Five HIGHLOW fields: pi, 2.0f, 1.0f and two Graphics.

Original physical target addresses are attested before compilation
comparison. No guessed source, library ownership or PE-relocation
substitution determines the accepted target identity.

## Important source-level findings, not machine-code padding

The real point renderer
[`src/AnimationShapePoint375.cpp`](../src/AnimationShapePoint375.cpp)
submits **one actual 20B `SpriteColoredVertex`** and advances the
existing renderer cursor once. Its original buffer-end guard compares
`&cursor[0]` against the one-past-end of the genuine
**65,536×20B fixed pool**, not a guessed `cursor < receiver+cursorOffset`
check. More subtly, the original MSVC `/Od` accesses every field as
**typed vertex index `[0]`** with real stride multiplication. An
initial superficially equivalent direct pointer/extra alias source
produced only **309B/90 x86** and an inflated `0x24` frame; restoring
true fixed-array buffer ownership and index-zero field access produces
the actual **375B/100 x86**, native `0x1C` frame and all source field
positions. It writes native x/y plus actual renderer offsets, Z=0,
reciprocal W=1, one packed diffuse color, disables Graphics depth
writes, selects native color mode2, FVF `0x44`, and issues
`DrawPrimitiveUP(POINTLIST,1,vertex,20)`.

The alternating filled fan
[`src/AnimationShapeAlternateFan809.cpp`](../src/AnimationShapeAlternateFan809.cpp)
uses the same real pool and an actual center `vertex[0]` with independent
center color, plus `segment_count+1` perimeter points. Each perimeter
iteration performs the **original signed C++ `i%2`** radius selection:
even segments use `radius_a`, odd segments use `radius_b`. Genuine
`polar2`, `add_angles`, the original x/y and renderer offsets,
Z0/W1, second diffuse color, Graphics state and D3D9
`DrawPrimitiveUP(TRIANGLEFAN,segment_count,vertices,20)` are all
preserved. It reserves/advances `segment_count+2` vertices and has
native stack `0x28` and `ret 0x20`.

The alternating perimeter line
[`src/AnimationShapeAlternateLine583.cpp`](../src/AnimationShapeAlternateLine583.cpp)
has **no center vertex**. It preserves the same signed native `i%2`
radius selection and original input angle parameter reused as the
`2*pi/count` step, but submits `segment_count+1` perimeter vertices
with `DrawPrimitiveUP(LINESTRIP,segment_count,vertices,20)` and no
invented Graphics depth-state call. It has the real `0x28` frame and
`ret 0x1C`. None of the three new sources duplicates the bytes of its
already exact geometry/math/Graphics callees or its enclosing Draw
parent; no machine bytes, padding locals or NOPs have been inserted.

## Whole strict native acceptance, source-scoped regression and credit

The three separate units in
[`config/match-units.toml`](../config/match-units.toml) have pinned
MSVC 19.44.35211 i386 C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` objects and fresh receipts. Their complete
source-symbol, relocation-type, physical offset and native PE target
roles are explicit and source-independently attested: **5+4, 8+8,
6+5**, respectively. Full original relocated native replays report:

```text
animation_shape_point_375: exact (375/375 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_shape_alternatefan_809: exact (809/809 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_shape_alternateline_583: exact (583/583 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The original native methods return zero through EAX, so three old
provisional `void` method signatures in shared
`AnimationDrawDetailedOwner.hpp` are corrected to `std::int32_t`.
Only previously accepted exact sources in this header's affected
include closures are cold-recompiled and strictly replayed. The still
NONEXACT 5,993B main Draw source undergoes a separate focused
original-native role/switch test, not falsely promoted to exact.
**No unfiltered full-graph cold replay** is run.

Three newly accepted whole game-original physical function heads add
**1,767 disjoint native `.text` bytes**. Live coverage becomes **625
whole authored-game strict exact functions /229,642 original `.text`
bytes**, **1,271 source-present mappings /1,272 strict canonical
units /290 accepted pinned object/receipt providers**. The original
5,993B main Draw parent remains a distinct open larger Boss, even
though the entire set of its game-owned rendering callees now has
much broader exact coverage.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-final-three-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapePoint375.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeAlternateFan809.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeAlternateLine583.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
