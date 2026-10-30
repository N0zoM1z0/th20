# CORE/RECON-893/894 — original 827B polygon dynamics Boss source, 140B group tick strict exact and seven native iterator helpers whole exact

The original Japanese TH20 v1.00a Steamless image is locked by SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This investigation addresses **both the still-open large polygon dynamics
Boss and its actual original caller/helper graph**, rather than selecting
unrelated short functions. One original game-authored **140B group update
Boss is now whole strict exact**, and seven independent **19B–32B
counted-range iterator helper methods** also match their entire original
native extents. The original **827B/237-i386 per-segment dynamics Boss is
SOURCE-PRESENT/NONEXACT**, with a natural C++ semantic candidate and an
original-PE-only full control-flow/call/data census, **not** credited as exact.

## Independent original PE full-function facts

[`scripts/verify-animation-polygon-group-tick140-native.py`](../scripts/verify-animation-polygon-group-tick140-native.py)
reads the original PE `.text` and original `.reloc` independently of
candidate bytes. The native game method at **`0x0045F5E0`** has a real
**140-byte /46-x86 body**, the original `sub esp,0x18` stack frame and
an original `ret` instruction at offset **`+0x8B`**. Its **six true E8
physical callsite/target pairs** are:

| Original site | Physical callee |
| --- | --- |
| `+0x12` | `0x0045D030` (timer/trigger gate, existing physical source) |
| `+0x27` | `0x0040BDA0` (offset-zero Motion::position_ref) |
| `+0x32` | `0x0045FD40` (already exact 19B three-segment array end) |
| `+0x5C` | `0x004379C0` (whole exact Animation scale_x_value, x87 float) |
| `+0x68` | `0x0045F670` (827B *still NONEXACT* segment dynamics Boss) |
| `+0x81` | `0x00423540` (native Timer postincrement) |

There are **zero original PE HIGHLOW fields** in these 140 bytes. The
method checks the original timer condition at group offset `+0xB88`,
walks the real three `0x3D4`-stride polygon segment records from
`group+8` through the existing native container end, calls the 827B
segment updater with the actual Animation scalar on each segment,
post-increments the real timer, and returns native EAX zero.

**The boundary matters:** the original executable has exactly **four
independent `0xCC` INT3 alignment bytes at `0x0045F66C..0x0045F66F`
(original offsets `+0x8C..+0x8F`)**, after the real 140B `ret` and
before the separate valid 827B original function head `0x0045F670`.
These are not game-authored executed instructions, and their bytes are
**not** masked, patched into the source or counted as original function
code. The provisional `config/functions.csv` already correctly
records the **140B true body**; the 827B body is separately recorded.
The strict 140/140 comparison covers the **entire real code extent**
through the return, not a shortened mismatching prefix.

## The large 827B Boss: original native CFG verified, C++ still NONEXACT

[`scripts/verify-animation-polygon-dynamics827-native.py`](../scripts/verify-animation-polygon-dynamics827-native.py)
independently reads **all 827 original executable bytes and 237 real
x86 instructions** at `0x0045F670`, including its uncommon 8B
`ESP` realignment prologue, actual `ret 4`, **31 genuine E8
physical site/absolute target pairs** and **ten original PE HIGHLOW
field/target pairs**. It independently proves that the true 140B
parent invokes this specific 827B head from E8 `0x0045F648`.
The true data include the single native GameRandom source
`0x005BA4C4`, original 2.0f at `0x0056C8D0`, four uses of the original
4.0f field `0x0056C8E0`, pi at `0x0056E0F0` and the genuine 59.0f
angular denominator `0x0056EE48`.

The original preserves two distinct counted-range loops: it zeroes a
native float at segment `+0x2DC`, obtains an initial XY position via
the native `0x0045D670` 8B-stride accessor, perturbs source radii by
the original x87 `GameRandom::signed_unit()*2.0f` and clamps about the
input scalar by native 4.0f boundaries. Its second counted-range loop
uses a real `Angle`, passes the current original float and radius to
the native polar function `0x00439330`, advances the angle by
`(pi*2)/59.0f`, and finally copies the actual **eight bytes of point
index 1 to point index 60** through the same native accessor.
Original COMISS/JBE NaN branch behavior and exact range bounds still
require further source investigation.

The maintained natural C++ in
[`src/AnimationPolygonDynamics827.cpp`](../src/AnimationPolygonDynamics827.cpp)
**now implements the one authentic `NativePolygonSegmentSlot` owner**
used by the already exact 233B draw, 296B initialization and 120B
palette methods; it does not invent a second competing runtime segment
class. Its typed geometry view describes the real 8B point stride,
61 indexed output points, radii at `+0x2DC` and overall original
`0x3D4` segment size, with explicit layout assertions. It models the
native scalar clamp, per-point polar transform, angle progression and
closure. The *straightforward C++ loop bounds* in this candidate are
**hypotheses** until the original counted-range and adapter code is
fully reconstructed; in particular, the candidate currently lacks
the original C++ range factory, pair, cursor and sentinel construction
calls and may differ in NaN handling.

Under the normal pinned i386 MSVC `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` profile, the 827B candidate compiles to
**513B/137 i386 instructions, seven E8 and ten DIR32** fields—versus
the original **827B/237 i386, 31 E8 and ten PE HIGHLOW**. This is a
complete maintained semantic hypothesis and genuine substantial
calling/geometry evidence, **but it fails whole-body strict exactness**.
There is no 827B canonical unit or `matches.csv` game-code credit,
and the original caller's whole strict exactness is not treated as
proof of this unfinished callee.

## Seven real native counted-range helper functions, not arbitrary leaves

The original 827B dynamic Boss directly calls five helper wrappers;
two of those wrappers call two more genuine native pointer increment
functions. All seven physical heads below have been independently
confirmed by the locked executable, including their original C++
return-pointer ABI and any E8 site/absolute destination identities:

| Original head | Native semantics | Whole strict result | Original E8 |
| --- | --- | --- | --- |
| `0x0045F420` | Dereference counted cursor, **returns float* in EAX** | **19B/9 x86 exact** | `+0xA → 0x0040C300` |
| `0x0045F440` | Advance one `float*` by **4B**, return self | **27B/13 x86 exact** | none |
| `0x0045F460` | Advance one `Vector2*` by **8B**, return self | **27B/13 x86 exact** | none |
| `0x0045F480` | Scalar range next wrapper, return self | **22B/10 x86 exact** | `+0xA → 0x0045F440` |
| `0x0045F4A0` | Vertex range next wrapper, return self | **22B/10 x86 exact** | `+0xA → 0x0045F460` |
| `0x0045FF00` | Scalar range begin, return destination | **32B/14 x86 exact** | `+0xF → 0x0045EF10` |
| `0x0045FF20` | Vertex range end, return destination | **32B/14 x86 exact** | `+0xF → 0x0045EF90` |

The seven source functions live together in
[`src/AnimationPolygonIteratorLeaves.cpp`](../src/AnimationPolygonIteratorLeaves.cpp),
and have **zero original PE HIGHLOW data fields**. Five functions
contain one genuine E8, and the two directly typed pointer increments
have **zero original relocations**. Both `float*` and `Vector2*`
increments reproduce the original 4B/8B pointer stride without
manually shaping machine code.

An important original semantic fix was required for the **19B
`0x0045F420`** helper: a plausible source declared its forwarding
call `void`, which produced **20B/10 x86** with an unwanted NOP.
The native 827B parent explicitly captures EAX immediately after
both dereference calls (`+0x124` and `+0x261`) and then reads the
float through that pointer. Changing the C++ declaration to
**`float*` return from both the wrapper and its `0x0040C300`
downstream helper** naturally removes the NOP and yields the genuine
**19B/9 x86**, native return ABI and original E8 location.

All seven full-original native bodies have fresh strict units in
[`config/match-units.toml`](../config/match-units.toml), sharing one
pinned compiler object/receipt
`build/core893-canonical/AnimationPolygonIteratorLeaves.obj`:

```text
animation_polygon_range_deref_19: exact (19/19 bytes)
animation_polygon_range_next_scalar_22: exact (22/22 bytes)
animation_polygon_range_next_vertex_22: exact (22/22 bytes)
animation_polygon_range_begin_32: exact (32/32 bytes)
animation_polygon_range_end_32: exact (32/32 bytes)
animation_polygon_scalar_step_27: exact (27/27 bytes)
animation_polygon_vertex_step_27: exact (27/27 bytes)
Exact replay: 7/7 units, 1 cold objects
```

These seven methods strongly resemble compiler/STL counted-range and
iterator instantiations. Their original authorship is **not independently
proved** by original symbol data; they remain `unknown/review` in the
origin ledger and **are not counted as hand-authored game `.text` code**.
Their complete original strict byte acceptance is still real and
recorded separately from that credit decision.

## Full original 140B group Boss strict replay, bounded scope, progress

The exact group method was added to the same natural source file as
previously exact 233B draw, 296B initialization, 47B registry wrapper
and the 23B/19B container helpers:
[`src/AnimationPolygonMotionGroup233.cpp`](../src/AnimationPolygonMotionGroup233.cpp).
The real `NativePolygonSegmentSlot` method declaration was added to
[`src/NativePolygonSegmentSlot.hpp`](../src/NativePolygonSegmentSlot.hpp)
so that the 140B and 827B sources share one runtime receiver/ABI.
Each previously accepted dependent strict source was cold-replayed
only in its affected source include closure. The fresh original PE
verifier authenticated all six genuine tick Boss E8 roles with zero
HIGHLOW fields before the pinned MSVC COFF was accepted:

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
animation_polygon_motion_config_296: exact (296/296 bytes)
animation_polygon_registry_wrapper_47: exact (47/47 bytes)
animation_polygon_group_tick_140: exact (140/140 bytes)
Exact replay: 6/6 units, 1 cold objects
```

The separate 120B palette source, which includes the changed slot
header, was also cold-replayed within that affected include closure
(three original native strict units, all still exact). **No
unfiltered whole-project cold replay was used.**

New credit: **one hand-authored original game head /140 original
`.text` bytes** for the 140B tick. The seven iterator helper bodies
are strictly exact but origin-pending (**181 original native bytes
uncredited to authored game**); the 827B dynamics Boss is
SOURCE-PRESENT/NONEXACT and earns no exact native bytes.
Live whole-original authored game coverage becomes **637 functions /
233,802 original `.text` bytes**, with **1,297 source mappings /
1,295 canonical native strict units /299 pinned compiler
object/receipt providers**. The project is not yet globally linked or
playable.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-group-tick140-native.py
scripts/repo-python scripts/verify-animation-polygon-dynamics827-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonIteratorLeaves.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonPalette120.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
