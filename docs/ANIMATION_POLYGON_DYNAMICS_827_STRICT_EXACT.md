# CORE/RECON-901 — complete original 827-byte polygon dynamics Boss strict exact

The immutable Japanese TH20 v1.00a Steamless target is SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The **entire original game-authored 827B /237-i386 function at `0x0045F670`**
now passes **827/827 canonical relocated native bytes** from natural maintained
C++20 under the pinned MSVC 19.44 x86 compiler. This is a complete enclosing
original Boss, **not** inherited exactness from any helper.

## Independent original executable ground truth

`scripts/repo-python` executes
[`scripts/verify-animation-polygon-dynamics827-native.py`](../scripts/verify-animation-polygon-dynamics827-native.py),
which reads the immutable `.text` and independent original `.reloc` section.
It previously recorded **all 31 original physical E8 site/target pairs** and
**all ten original PE HIGHLOW site/target pairs**, before this candidate was
assembled. The original `ret 4` occupies original final byte `+0x33A`, and the function's
real start has **eight-byte stack realignment** (`push ebx`, save ESP,
`and esp,-8`) and an actual **`0x90`-byte local frame**.

The function updates the genuine fixed `0x3D4`-byte polygon segment layout:
61 XY vertices (`0x1E8` bytes), 61 packed-color slots (`0xF4` bytes), and
62 float radii (`0xF8` bytes). Independent original native `std::array::size()`
methods return **61** and **62**, unlike the earlier incorrect 60-item
radius-loop assumption. See the [intermediate native range evidence](ANIMATION_POLYGON_DROP_VIEW_62_61_NATIVE_EXACT.md)
for the four separately exact 16B/93B standard-library helper bodies.

Two genuine `std::views::drop(1)` range-for loops naturally reproduce all
native range-closure creation, counted begin/end constructors, iterator
advances, comparisons and dereferences. The first updates radius entries
1..61 via `GameRandom::signed_unit()` at physical `0x004298E0`, scales by 2.0f,
and clamps against the input argument ±4.0f using original COMISS/NaN
behavior. The second visits vertices 1..60, reads radius by an independent
index, invokes `polar` at `0x00439330` and advances `Angle` by `(pi*2)/59`.
The closing path copies vertex 1 to vertex 60. An original 140B whole-exact
group tick caller reaches this Boss at physical E8 `0x0045F648`.

## Natural C++20 source convergence, not an artificial alignment trick

The first maintained plain-loop candidate compiled to **513B /137 i386 /
7 E8**. Recovering actual `std::array<float,62>`, `std::array<Vector2,61>`
and two dropped range-for loops made **768B /225 i386 /31 E8**. A live
source-only series of private probes separated real `this` member access,
first-point alias lifetime and closing-point temporary variants (retained
under ignored `.analysis/gptweb-827-variants/`). A direct typed object-view
member expression — corresponding to the original native member accesses
rather than a single cached radius/perimeter reference — restored the
**true 0x90 frame** and the first 14 exact original call offsets.

Preserving the genuinely used `Vector3* const initial_point` before `polar`
restored the original first three array pointer computations and call order.
Finally, initializing the used `std::int32_t index = 1` **before** constructing
`Angle angle(0.0f)` reproduced the original seven-byte index initialization
before the Angle constructor and its authentic one-byte NOP. That yields
**827B /237 original instructions /31 E8** with every E8 opcode at its
original offset. The source does not inject NOPs, artificial padding,
compiler-only dead locals, assembly or an alternate exact-only code path.

The resulting body has **663/663 identical non-relocation bytes**, **31/31
E8 REL32** positions and targets and **10/10 DIR32** original PE HIGHLOW
positions and data targets. Native target verification and independently
recorded original relocations establish their destinations; they were not
inferred by solving candidate-relative fields against the target under
comparison. The candidate code contributes exactly 827B: there is no
truncated-prefix or adjacent-function acceptance.

## Scoped canonical acceptance and accounting

The new unit `animation_polygon_dynamics_827` in
[`config/match-units.toml`](../config/match-units.toml) holds all 41 explicit
physical relocations, source
[`src/AnimationPolygonDynamics827.cpp`](../src/AnimationPolygonDynamics827.cpp),
and compiler object
`build/core900-canonical/AnimationPolygonDynamics827.obj`. Fresh locked
MSVC x86 compilation plus **complete canonical relocation replay** gave:

```text
animation_polygon_radius_size_16: exact (16/16 bytes)
animation_polygon_vertex_size_16: exact (16/16 bytes)
animation_polygon_radius_drop_begin_93: exact (93/93 bytes)
animation_polygon_vertex_drop_begin_93: exact (93/93 bytes)
animation_polygon_dynamics_827: exact (827/827 bytes)
Exact replay: 5/5 units, 1 cold objects
```

The 827B parent is one **new authored-game whole original function**. Exactly
**827 new original `.text` bytes** are credited once via `config/matches.csv`.
The original 218B of separate STL-like exact helper functions and seven
previously matched iterator helpers remain `origin=unknown`, **excluded**
from game-authored credit pending independent provenance review. The shared
`NativePolygonSegmentSlot.hpp` declaration remains consistent with the exact
296B configuration and 233B draw Bosses, and changes to its comment text are
verified only through its actual three source include providers.

At this checkpoint the live inventory becomes **638 game-authored whole
exact functions /234,629 native `.text` bytes**, **1,301 source-present
mappings /1,300 strict units /300 compiler object providers**. Whole-game
linkage and playability are not established.

### Reproduce only affected graph

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-dynamics827-native.py
scripts/repo-python scripts/verify-animation-polygon-drop-ranges-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonDynamics827.cpp --source src/AnimationPolygonMotionGroup233.cpp --source src/AnimationPolygonPalette120.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_dynamics_827
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

No whole-graph cold replay and no executable or database mutation were used.
