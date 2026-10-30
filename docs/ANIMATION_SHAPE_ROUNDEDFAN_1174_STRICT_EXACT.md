# CORE/RECON-859 — complete original 1,174B game rounded-corner triangle fan strict exact

The immutable Japanese TH20 v1.00a Steamless target, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a **whole 1,174B/303 real-native-i386 game-authored**
rounded-corner triangle fan Boss at `0x0043A2B0`. Its original
member has an ECX renderer, nine actual stack arguments and
`sub esp,0x28`/`ret 0x24`, returning zero. The larger 5,993B
Animation Draw dispatcher calls this exact physical head at
original E8 `0x0044415E`, but itself remains separately **NONEXACT**.

One real C++ method
[`src/AnimationShapeRoundedFan1174.cpp`](../src/AnimationShapeRoundedFan1174.cpp)
now exactly emits **1,174/1,174 entire native original bytes** and
**303/303 complete real x86 instruction heads**, under pinned MSVC
19.44.35211 i386 C++20. The original `0x28` frame, **9/9 E8
positions and physical destination heads**, all **19/19 original PE
HIGHLOW field offsets and absolute targets** and **1,062/1,062
non-relocation bytes** are identical. This is not a loop-fragment
match, truncated prefix or hand-authored native byte array.

## Original PE-only physical game provenance

[`scripts/verify-animation-shape-roundedfan1174-native.py`](../scripts/verify-animation-shape-roundedfan1174-native.py)
reads the original selected PE `.text` and `.reloc` independently of
candidate COFF, disassembles all 303 original native i386 heads and
checks the true code extent/ABI, all original E8 sites, native global
storage references and the main Draw parent call. The real original
nine E8 roles include game pool `flush_draws` `0x004455C0`, folded
89B `polar2` at `0x00439330`, 137B XY rotation at `0x00458FA0`,
29B `add_angles` at `0x00438600`, actual Graphics depth write disable
`0x004DDF80`, real Graphics `SetRenderState` wrapper at
`0x004D9DB0`, original color mode `0x00446690`, and two real
Graphics device acquisitions `0x00412730`.

All **19 physical PE HIGHLOW** data fields target independently
original game owners: one `-π` constant `0x0056E0F8`, one `+π`
`0x0056E0F0`, **11 float 2.0f** values at `0x0056C8D0`, **two 1.0f**
values at `0x0056C8CC`, and **four live Graphics globals** at
`0x005C4D40`. There is no guessed unresolved data target, additional
imported library code credit or fabricated local pointer owner.

## Whole original rounded-fan geometry, not just matching instruction count

The original uses the real **65,536 ×20B** `SpriteColoredVertex`
fixed vertex pool beginning at renderer `this+0x7C00E80` and its
mutable write cursor at `this+0x7D40E80`. The original unsigned
`JB` capacity guard verifies space for **segment_count+2** typed
records and checks `segment_count>=2`, then flushes the genuine pool.

The first live vertex is the *center*: original `x,y`, Z=0,
reciprocal W=1 and center packed color, plus the native renderer
XY offsets `+0xD0/+0xD4`. The renderer then advances the shared
cursor to the first perimeter point, subtracts `2*radius` separately
from both **actual mutable width/height input parameters**, and
iterates **segment_count+1** perimeter vertices. The genuine
`polar2`/`rotate_xy` math, signed quarter-boundary corrections,
perimeter packed color, world XY/renderer offsets, and native
`add_angles(−π,2π/count)` angular progression are preserved.
The final Graphics pipeline disables depth writes, applies original
`SetRenderState(23,8)`, chooses color mode 2 and FVF `0x44`, then
issues the genuine D3D9 `DrawPrimitiveUP(D3DPT_TRIANGLEFAN=6,
segment_count,vertices,20)` and advances the live pool cursor by
`segment_count+2` records. The renderer draw counter increments.

An initial complete typed C++ candidate emitted **1,093B/285 x86**
instead of original 1,174B/303 x86, even though it matched all nine
original E8 target identities in order and all 19 data-owner classes.
The exact missing **81 bytes** were caused by writing the center
with `current->position` direct member accesses: the original
really uses **the typed vertex at array index `[0]`** for each of its
center fields. This makes pinned `/Od` legitimately emit the real
`MOV EAX,0x14; IMUL ECX,EAX,0` indexed access sequence at every
center field, before advancing the single actual pointer for the ring.
Replacing the direct center accesses with **used, game-semantic
`current[0]` typed accesses** restores every original opcode, the
true stack frame and all E8/HIGHLOW physical offsets without fake
NOPs, inert variables or manual assembly.

## Exact acceptance, ABI, replay scope and live progress

The one canonical unit `animation_shape_roundedfan_1174` in
[`config/match-units.toml`](../config/match-units.toml) owns only
one new pinned object/receipt
`build/core859-canonical/AnimationShapeRoundedFan1174.obj`. It has
**9 genuine REL32 E8 +19 authentic DIR32/PE HIGHLOW** explicit original
symbol, offset, type, and target roles independently mapped from the
original executable. Its complete fresh canonical replay yields:

```text
animation_shape_roundedfan_1174: exact (1174/1174 bytes)
Exact replay: 1/1 units, 1 cold objects
```

The provisional shared renderer methods for this whole native Boss
and the companion [240B outline leaf](ANIMATION_SHAPE_OUTLINE_240_STRICT_EXACT.md)
were changed from `void` to the true original int-returning `ret 0x24`
contracts. Previously exact source providers sharing that header are
recompiled and replayed **only in their changed include closures**;
the 5,993B main Draw candidate is checked independently and still
marked NONEXACT. No complete unfiltered cold replay is run.

The two disjoint new game-owned exact functions (1174B+240B) add
**1,414 actual game `.text` bytes**. Final live tracking from these
accepted original physical heads is **613 game-authored whole-native
exact functions /220,303 strict game bytes**, **1,259 source-present
mappings /1,260 canonical strict units /278 accepted pinned
compiler objects/receipts**. None of their existing exact math,
Graphics or rectangle callees, nor the enclosing nonexact main
Draw parent, is counted again.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-shape-roundedfan1174-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationShapeRoundedFan1174.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
