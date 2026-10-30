# CORE/RECON-874/875/876 — whole 985B original quad projection and two 455B colored vertex Bosses strict exact

The immutable original Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains three **distinct physical original game-authored complete functions**.
These native game methods were not previously source-present, despite the
large exact-renderer corpus around them. Their source declarations,
original PE call sites and original data owners were recovered independently;
no byte patching, copied original instruction stream or NOP shaping was used.

| Independently immutable original evidence | Quad corner transform | Vertex TRIANGLEFAN | Vertex LINESTRIP |
| --- | ---: | ---: | ---: |
| Original game head | `0x0043EB40` | `0x0043CB70` | `0x0043D1A0` |
| Entire real game `.text` | **985B /233 x86** | **455B /129 x86** | **455B /129 x86** |
| Native frame / return ABI | `sub esp,0x24`; `ret 0x14` | `sub esp,0x20`; `ret 0x10` | `sub esp,0x20`; `ret 0x10` |
| Physical E8 site/target pairs from original PE | **6/6** | **4/4** | **4/4** |
| Actual PE HIGHLOW field/target pairs | **13/13** | **3/3** | **3/3** |
| Nonrelocation code identical | **909/909 bytes** | **427/427 bytes** | **427/427 bytes** |
| Complete relocated strict canonical whole native body | **985/985 exact** | **455/455 exact** | **455/455 exact** |
| Real original D3D9 primitive | Geometry function | `TRIANGLEFAN=6` | `LINESTRIP=3` |

## Original PE-only proof and physical caller provenance

[`scripts/verify-animation-corner-projector-985-vertices-455-native.py`](../scripts/verify-animation-corner-projector-985-vertices-455-native.py)
reads the locked original `.text` and its actual `.reloc` directory. It
attests the **complete 491 native i386 instructions** of the three
methods, the **14 original E8 site/actual target head pairs** and
**19 original HIGHLOW field/actual data target pairs**, not candidate
symbol placeholders or historical decompiler assumptions.

The 985B method calls original `Animation::sprite_data` at
`0x00437CD0`, original `Animation::position(Vector3&)` at
`0x004376E0`, and four original `Vector3::operator+=(const Vector3&)`
physical heads at `0x004296E0`. It uses two genuine PE references
to the immutable quad table at `0x0056E140`, four source-owned
`window_state.scale` fields at **`0x005B8818`** (existing original
`window_state` owner `0x005B6758` plus real `+0x20C0` scale member),
two genuine `0.5f` fields `0x0056E0EC`, and five references to the
actual world-translation `Vector3` at `0x005C0018`. Its original
`ret 0x14` proves five stack args in addition to an unused but saved
ECX receiver. The exact original source class spelling remains
provisional; the local `NativeAnimationCornerProjector` is only a
nominal method receiver, and no runtime data/vtable is allocated.

The two 455B methods each genuinely call the already exact
`AnimationPoolOwner::flush_draws` `0x004455C0`, renderer color-mode
selection `0x00446690`, and two actual Graphics device getters
`0x00412730`, with one real `1.0f` HIGHLOW at `0x0056C8CC` and two
live Graphics references at `0x005C4D40`. The independent original
E8 scan verifies representative **original game callers**, not just
plausible function boundaries: quad projector `0x0043F598`,
`0x0043F608`, `0x004457D3`, `0x00445858`; fan
`0x0045DB20`, `0x0045FB50`, `0x004620D1`; line
`0x0045E220`, `0x0045EB00`, `0x0046789D`. These bodies are
independently authored game code and count only once per physical head.

## Genuine 96B 2-axis × 3-mode × 4-corner data structure

The **entire original data table** at `0x0056E140` was read as 24
immutable binary floats, not inferred from the source probe:

| Source axis / 16B mode | Four original float corner values |
| --- | --- |
| X / centered | `-0.5, +0.5, -0.5, +0.5` |
| X / from zero | `0, 1, 0, 1` |
| X / negative | `-1, 0, -1, 0` |
| Y / centered | `-0.5, -0.5, +0.5, +0.5` |
| Y / from zero | `0, 0, 1, 1` |
| Y / negative | `-1, -1, 0, 0` |

The actual native x86 begins with a **0x30-byte source axis stride**,
indexes the X axis by `Animation+0x4A8` and the Y axis by
`Animation+0x4AC`, and *shifts both mode indices by exactly 4 bits*.
The initial plausible source treated each mode as a scalar float
index. It compiled to **979B/231 i386**, missing two real `SHL reg,4`
mode operations, and would select incorrect corner geometry in game.
The natural corrected source in
[`src/AnimationCornerProjection985.cpp`](../src/AnimationCornerProjection985.cpp)
uses a meaningful `float corners[3][4]` for **each of two axis
records**, naturally emitting both original 16-byte mode strides and
all **985B/233 native instructions**, with a genuine `0x24` frame.

It preserves original sprite resource extents and animation offset,
parent-scale inheritance gated by the real native flag, window scale
mode-specific multiplication order, four separate X/Y corner source
transformations, four `Vector3::operator+=` calls to the original
world-position global, and exactly four Z stores of the original
`Animation+0x34`, `+0x5C4`, `+0x48C` combined depth. The original
96B table is currently an external source declaration; this result
**does not claim** that the table definition/linkage or whole game
linkability has been completed. Its physical data owner and all
original references are now independently established.

## Two different, complete 455B vertex submission functions

[`src/AnimationVertexFan455.cpp`](../src/AnimationVertexFan455.cpp)
and [`src/AnimationVertexLine455.cpp`](../src/AnimationVertexLine455.cpp)
share the real receiver-owned **65,536×20B**
`SpriteColoredVertex` pool and original fixed array address expression.
Both reserve `count+1` typed records with native unsigned `JB`, flush
pending draws, then use four real stack arguments: count, a source
`Vector2` origin, an advancing `Vector2*` point stream, and an
advancing 32-bit packed-color stream. Each emitted vertex stores
source+origin XY, Z=0, reciprocal W=1, its own color, and actual
renderer XY offsets. The real native instructions then set renderer
color mode 2 and FVF `0x44`, invoke D3D9 and advance the existing
cursor by `count` vertices, incrementing the original draw counter.

The semantic differences are physical native facts: the fan requires
**`count >= 3`**, calls `DrawPrimitiveUP(TRIANGLEFAN=6,count-2,...)`;
the line requires **`count >= 2`** and submits
`DrawPrimitiveUP(LINESTRIP=3,count-1,...)`. The separate native heads
are both 455B/129 x86 with 427 identical nonrelocation bytes in their
respective original regions, but their distinct branch thresholds,
primitive types, caller sets and source owners prohibit merging them
or double-crediting one original physical function.

## Strict acceptance, header scope and exact game code credit

Each source has one fresh pinned i386 MSVC C++20
`/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc` object/receipt
and one full canonical unit in
[`config/match-units.toml`](../config/match-units.toml):

```text
animation_corner_projection_985: exact (985/985 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_vertex_fan_455: exact (455/455 bytes)
Exact replay: 1/1 units, 1 cold objects

animation_vertex_line_455: exact (455/455 bytes)
Exact replay: 1/1 units, 1 cold objects
```

All **33 genuine original E8/HIGHLOW symbol, relocation type, physical
field offsets and original physical destination roles** are explicitly
attested independently in the one source-owned unit for each method.
The two 455B member declarations extend the shared
`AnimationDrawDetailedOwner.hpp`, so previously accepted sources
including that header are cold-recompiled and strictly replayed
**only within this changed include closure**. The 5,993B main Draw
parent is checked separately by its focused original-native
role/switch verifier and remains NONEXACT. No unfiltered whole graph
cold replay is needed or run.

The three whole source functions add **3 new unique physical
original-authored game functions and 1,895 disjoint original `.text`
bytes**. Live coverage becomes **628 game whole-native exact functions /
231,537 native bytes**, **1,274 source mappings /1,275 strict native
units /293 pinned exact object/receipt providers**. The already
exact geometry/renderer callees, unsigned PE data table and still
NONEXACT main Draw parent receive no duplicate authored game code bytes.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-corner-projector-985-vertices-455-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationCornerProjection985.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationVertexFan455.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationVertexLine455.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
