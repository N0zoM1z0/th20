# CORE/RECON-841 — two complete original Animation projection/math helpers: 73B and 86B strict exact

The immutable locked Japanese TH20 v1.00a Steamless original executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains two separate physical gameplay projection helpers called from the
unfinished original **1,378B mode6 geometry preparation** method at
`0x00440340`. Rechecking the complete original instruction bodies, original
E8 destinations and original .reloc evidence independently led to ordinary
C++ source in [`src/AnimationProjectionMath.cpp`](../src/AnimationProjectionMath.cpp)
and a small shared owner interface in
[`src/AnimationProjectionMath.hpp`](../src/AnimationProjectionMath.hpp).
Both entire functions now pass reproducible **strict canonical** replay, not
merely structurally equal instruction streams.

## Native independent evidence and source contracts

| Original physical game function | Native original size / x86 | Actual behavior |
| --- | --- | --- |
| `0x004399B0` | **73B /22 x86** | `animation_vector3_length(const Vector3&)`: original SSE `(x*x+y*y)+z*z`, forward scalar result to `scalar_math::square_root`, return float on x87 ST0 |
| `0x00445B20` | **86B /23 x86** | `AnimationDrawDetailedOwner::transform_projected_xy(Vector2*,x,y,sin,cos,tx,ty)`: original x86 thiscall, `ret 0x1C` for seven real stack arguments, `out.x=x*cos-y*sin+tx`, `out.y=x*sin+y*cos+ty` |

The independent
[`scripts/verify-animation-projection-math-native.py`](../scripts/verify-animation-projection-math-native.py)
extracts the original whole 73B and 86B bodies from the PE, verifies the
complete native x86 instruction count, arithmetic ordering, calling/return
protocol and absence of original PE HIGHLOW data fields. It verifies the
actual original `+0x3F` E8 at `0x004399EF` to the previously separately
accepted full 35B `scalar_math::square_root` at `0x00446B30`, without
counting that external library/math body again.

The original complete mode6 preparation caller `0x00440340` physically
calls `0x004399B0` once at original offset **`+0x210`**, and calls
`0x00445B20` four times at **`+0x3AB`, `+0x436`, `+0x4BE`, `+0x548`**.
All five original E8 targets are read from the immutable original
executable rather than inferred from candidate source symbols or copied
Ghidra names. These are native, game-specific geometry calculation and
rendering methods, not automatically generated CRT/STL template utilities.
Their names are descriptive reconstruction spellings; original source
identifier spelling is not attested.

## Critical source-type finding

A first complete source probe used `float*` for the projected XY output.
It emitted **103B**, not the native 86B, because MSVC lowered the output
writes `output[0]` and `output[1]` to explicit `4*index` pointer math. The
original uses the *two named float fields of a single actual Vector2*:
`movss [eax],xmm0` and `movss [ecx+4],xmm0`. Rewriting the real C++ output
owner as a typed **`Vector2*` with `output->x` and `output->y`** emitted
exactly the original **86B/23 i386**, with the true receiver and
seven-argument `ret 0x1C` ABI, and zero COFF relocations. No dummy code,
manual assembly or fake padding is present.

The 73B magnitude function naturally uses the actual `Vector3` owner with
12-byte XYZ layout and a separate previously accepted 35B sqrt wrapper. The
MSVC compiler emitted the original 73B /22-instruction `MULSS`, `ADDSS`,
float stack argument, actual E8 and cdecl return exactly.

## Complete canonical proof and scoped replay

The two new independently configured units in
[`config/match-units.toml`](../config/match-units.toml) share **one**
pinned MSVC x86 source object and receipt,
`build/core841-canonical/AnimationProjectionMath.obj`, with the project
standard C++20 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.

- `animation_projection_length_73`: original **73/73B**, one authentic
  `REL32` at `+0x40` with source symbol
  `?square_root@scalar_math@th20@@YAMM@Z` and independently attested
  target `0x00446B30`.
- `animation_projection_xy_86`: original **86/86B**, *zero* original PE
  HIGHLOW and *zero* candidate COFF relocations, genuine `ret 0x1C`.

```text
animation_projection_length_73: exact (73/73 bytes)
animation_projection_xy_86: exact (86/86 bytes)
Exact replay: 2/2 units, 1 cold objects
```

Both original functions are credited **once** in the game-authored
function/source ledgers with independently attested original native
callers. No bytes of the 1,378B mode6 preparation Boss, existing sqrt
wrapper or other dependency are counted here. This adds **two game-owned
original functions /159 native `.text` bytes**, **two canonical strict
units and source mappings**, **one new compiler provider**.

| Live exact tracking | Before | After | Delta |
| --- | ---: | ---: | ---: |
| Original game-authored exact functions | 597 | **599** | +2 |
| Game-authored native exact code bytes | 199,566 | **199,725** | **+159** |
| Source-present mappings | 1,243 | **1,245** | +2 |
| Strict native canonical units | 1,244 | **1,246** | +2 |
| Distinct exact COFF objects/receipts | 263 | **264** | +1 |

Adding the natural `transform_projected_xy` declaration to the shared
`AnimationDrawDetailedOwner` receiver header affects the already strict
753B mode7 draw and 1,996B setup source include closures. Both are therefore
replayed **individually**, alongside the two new units in their single
new provider. The large 5,993B Draw Boss remains SOURCE-PRESENT/NONEXACT
and is checked with its existing noncanonical original-PE source-role
verifier. No unrelated canonical provider, game original PE bytes,
compiler profile or old function extent changed. **No full cold replay**.

## Focused reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-projection-math-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationProjectionMath.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7Setup.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

The genuine original **1,378-byte mode6 preparation** function remains
under investigation as the next larger renderer Boss: it performs native
D3DX project calls, a screen-space depth check, inherited scales, shared
identity matrices, four projected-vertex calculations and real output
updates. Both newly exact mathematical helpers are native nodes in its
original call graph, but are not proof that this parent is matched.
