# CORE/RECON-861 — whole original 755B simple TRIANGLEFAN Boss strict exact

The locked Japanese TH20 v1.00a Steamless original executable SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The original game-owned simple fan renderer at **`0x0043B960`** contains
an **entire 755B/197-native-i386** body. The original member has a
real ECX receiver and seven actual stack arguments, native
`sub esp,0x24` and `ret 0x1C`, returning zero in EAX. A real E8 from
the separate 5,993B Animation Draw dispatcher at **`0x0044466D`**
reaches this physical original head, without making the whole enclosing
Draw dispatcher exact.

The natural C++
[`src/AnimationShapeSimpleFan755.cpp`](../src/AnimationShapeSimpleFan755.cpp)
compiles with the project pinned i386 MSVC C++20 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` into the **entire 755/755B
original game function**, all **197/197 x86** and **691/691
non-relocation bytes**, with no manually patched object bytes.

## Independent original target census and precise fan geometry

The source-independent original PE verifier
[`scripts/verify-animation-shape-simplefan755-native.py`](../scripts/verify-animation-shape-simplefan755-native.py)
disassembles the entire immutable function including native return,
checks exactly eight genuine native E8 physical call sites/destinations,
all eight genuine HIGHLOW field offsets/destinations from the original
PE `.reloc`, and the real 5,993B parent call. The E8 targets are the
actual AnimationPool flush `0x004455C0`, polar2 `0x00439330`,
add_angles `0x00438600`, Graphics depth-write disable `0x004DDF80`,
real Graphics `SetRenderState(23,8)` forwarding `0x004D9DB0`,
color-mode `0x00446690`, and two device getters `0x00412730`.

The original PE HIGHLOW field targets are **two** real 1.0f fields at
`0x0056C8CC`, original pi `0x0056E0F0`, original 2.0f
`0x0056C8D0`, and **four** live Graphics owner references
`0x005C4D40`. Every site and target in the one canonical unit is
independently backed by original executable evidence rather than
inferred from the candidate's relocation bytes.

The actual game uses the renderer's genuine **65,536×20B**
`SpriteColoredVertex` pool, first checking space for
`segment_count+2` records with the original unsigned `JB` capacity
guard. Unlike some other shape methods, the original does **not** add
a separate count-at-least-two gate. The first record is the *center*
vertex indexed as `[0]`, containing the true x/y position, Z=0,
reciprocal-W=1, center diffuse color and renderer XY offsets. The
original `MOV EAX,0x14; IMUL ECX,EAX,0` instruction sequence
is naturally emitted by accessing the meaningful typed `[0]` center
record, not by a direct pointer field short-cut.

The source first saves the original incoming starting angle into one
real local float, then reuses the *actual mutable start-angle input
parameter slot* for the generated **`2*pi/segment_count` step**. It
loops for `segment_count+1` outer vertices, computing native polar2
with true radius, original world XY additions, Z=0, W=1, perimeter
color and renderer XY offsets; after each perimeter vertex, it
advances the real source pointer and calls `add_angles(current_angle,
step)`. The source finally issues real D3D9
`DrawPrimitiveUP(D3DPT_TRIANGLEFAN=6,segment_count,vertices,20)`
with FVF `0x44`, authentic renderer state 23/value8 and color mode2,
and updates the live vertex cursor and renderer draw counter.

This is a different game function from both the
[971B rounded LINESTRIP](ANIMATION_SHAPE_ROUNDEDLINE_971_STRICT_EXACT.md)
and the [1,174B rounded TRIANGLEFAN](ANIMATION_SHAPE_ROUNDEDFAN_1174_STRICT_EXACT.md):
its caller-specified start angle, simple-radius perimeter and no
rounded-rectangle quarter adjustments are native observations, not
inferences based on similar-looking type names.

## Strict canonical acceptance and disjoint physical credit

One new canonical `animation_shape_simplefan_755` unit in
[`config/match-units.toml`](../config/match-units.toml) compiles one
`build/core861-canonical/AnimationShapeSimpleFan755.obj` with a fresh
pinned MSVC receipt and **8 actual REL32 E8 plus 8 real DIR32/PE
HIGHLOW** symbol/offset/type/target roles. Whole relocated strict replay:

```text
animation_shape_simplefan_755: exact (755/755 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The shared provisional method header return type was corrected to the
real native `std::int32_t`/`ret 0x1C` ABI. Its already accepted
header-consumer sources are scoped for cold strict replay, along with
the separate noncanonical main Draw source-role verifier. No whole-
graph cold replay or artificial byte padding is performed.

The newly verified **971B rounded line +755B simple fan** pair credits
**two unique game-authored originals and 1,726 distinct `.text` bytes**,
without crediting existing exact math/Graphics subroutines twice. The
live totals are **615 game-authored exact whole native functions /
222,029 original game `.text` bytes**, **1,261 source mappings /
1,262 strict canonical units /280 accepted MSVC object providers**.
The 5,993B enclosing Animation Draw dispatcher remains **NONEXACT**.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-simplefan755-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeSimpleFan755.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
