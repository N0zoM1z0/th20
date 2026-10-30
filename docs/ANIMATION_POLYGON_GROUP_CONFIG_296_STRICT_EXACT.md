# CORE/RECON-887 — entire original 296B polygon-group configuration Boss strict exact

The original target is locked Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The actual game-authored group configuration method at **`0x0045FB60`**
now has a natural C++ implementation in
[`src/AnimationPolygonMotionGroup233.cpp`](../src/AnimationPolygonMotionGroup233.cpp),
sharing the genuine group receiver with the previously
[whole-exact 233B draw method](ANIMATION_POLYGON_MOTION_GROUP_233_23_19_STRICT_EXACT.md).
Its complete **296B/90 original i386 instructions**, native
`sub esp,0x2C`, `ret 8`, zero EAX return and all real source/stack roles
are **strictly identical** to the locked executable after relocation.

| Original full-function criterion | Whole-native acceptance |
| --- | --- |
| Original code body | **296/296 bytes exact** |
| Real x86 instruction heads | **90/90** |
| Native frame and original return | `0x2C`, `ret 8` |
| True E8 call physical sites and original absolute targets | **11/11** |
| True original PE HIGHLOW field roles | **0**, matched exactly |
| Nonrelocation bytes | **252/252 identical** |
| Nearby existing game group Boss/helper units in same object | **233/233**, **23/23**, **19/19** exact |

## Immutable original PE native proof, not candidate assumptions

[`scripts/verify-animation-polygon-group-config296-native.py`](../scripts/verify-animation-polygon-group-config296-native.py)
independently decodes the entire original 296B PE body, validates all
11 E8 physical call/destination pairs and zero genuine HIGHLOW
references from the actual original PE relocation directory, and
checks the caller from the separately original game 47B wrapper
`0x0045FD10`, E8 at **`0x0045FD36`**.

The true eleven call roles are: one original `Timer::operator=(int)`
at `0x00423520`; **three** indexed `0x0045F400` native array-member
calls; **three** `0x0045FC90` polygon palette initializers;
and one each of `Animation::set_position` `0x0045DD60`,
`Animation::set_layer` `0x00450350`, original native Animation
configuration `0x00438C60`, and
`Animation::set_flag_byte_01` `0x0045DD40`.
The native `0x0045FC90` 120B palette callee remains separately open;
whole caller matching does not make all callees exact.

The actual group writes the input integer to receiver **`+0xB98`**,
copies its source control from `config+0x24` to **`+0xB84`**,
copies its source `Vector3` into original **`+0xB9C`** and a byte
from `config+0x28` to **`+0xBA8`**, and resets the actual
`Timer` at receiver **`+0xB88`**. It accesses the genuine three
**`0x3D4`-stride** segment records starting at receiver **`+8`**, and
supplies the actual source palette words:

- segment 0: `0x8040F010`
- segment 1: `0xFF20F000`
- segment 2: `0x80FF1010`

After three indexed palette initializations, the original applies the
actual Animation position to its receiver `+4`, selects layer 11,
invokes the native configuration with arguments `30,0,255,0`, then
sets its original flag byte to 1. All input/control bits and the
original local source pointer objects are preserved, not replaced by
inert padding or hand-written x86.

## Actual code-generation mistake: redundant source block scopes

The initial complete semantic source emitted **304B/98 x86** with
the correct `0x2C` frame, eleven E8 target types and no HIGHLOW.
It had seven extra nested `{}` blocks to hold each source array-
element pointer or Animation receiver. Under the pinned MSVC `/Od`
profile the block boundaries emitted **eight additional `NOP`
instructions**: one following the Timer reset, three after palette
initializers and four after Animation calls. Their cumulative eight
bytes shifted every later relocation field even though source
semantics were correct. The original PE contains **none** of these
block-boundary NOPs.

The original source instead uses the meaningful distinct local
receiver/array element variables **in one function scope**. Removing
only the redundant blocks—without removing those local variables,
reordering effects or manually injecting/purging machine-code bytes—
naturally reproduces the whole original **296B/90 x86** with the
correct original E8 sites, **252/252 nonrelocation bytes** and the
full strict relocated 296/296-body match.

## Four canonical units, one source-scoped cold object

The one existing pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` source provider
`build/core884-canonical/AnimationPolygonMotionGroup233.obj` now owns
**four original native strict units** in
[`config/match-units.toml`](../config/match-units.toml):

```text
animation_polygon_motion_group_233: exact (233/233 bytes)
animation_polygon_segment_at_23: exact (23/23 bytes)
animation_polygon_segment_end_19: exact (19/19 bytes)
animation_polygon_motion_config_296: exact (296/296 bytes)
Exact replay: 4/4 units, 1 cold objects
```

The 296B unit specifies all eleven true original PE E8 source-symbol,
physical site, type and destination roles independently. The prior
233B game Boss and two 23B/19B native container helpers remain
unaltered and fully exact. The small helpers still have unresolved
likely compiler/STL origin, and the palette 120B callee remains a
separate reconstruction target. The separately original 104B outline
caller is still NONEXACT. No unfiltered whole-graph cold replay was
run, and existing unrelated exact sources were not modified.

This checkpoint adds **one unique game-authored whole-original
function /296 disjoint `.text` bytes**, not the existing parent,
helper methods or palette callee. Live tracking becomes **634 whole
authored game exact functions /233,495 original native code bytes**,
**1,284 source mappings /1,283 strict native units /297 pinned
original-game compiler objects/receipts**; the object count does not
increase because the new function shares an already accepted source
provider.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-polygon-group-config296-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationPolygonMotionGroup233.cpp
scripts/repo-python scripts/compare-coff-function.py --unit animation_polygon_motion_config_296
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```
