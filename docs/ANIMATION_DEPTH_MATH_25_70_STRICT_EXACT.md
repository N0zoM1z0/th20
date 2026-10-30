# CORE/RECON-838 — two original Animation renderer depth helpers, 25B+70B strict native exact

The immutable locked Japanese TH20 v1.00a Steamless executable
(SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains two distinct game-owned Vector3 depth helper functions used by
the larger Animation renderer modes. They were **source-absent** in the
function inventory before this checkpoint. This session reconstructed
both as natural maintained C++ in
[`src/AnimationDepthMath.cpp`](../src/AnimationDepthMath.cpp), with a
shared ordinary interface in
[`src/AnimationDepthMath.hpp`](../src/AnimationDepthMath.hpp).
Both *complete* original function bodies now pass pinned-MSVC
zero-difference **strict canonical** comparison, without assembly,
inert locals, shortened extents, invented call targets or copied native
machine bytes.

## Independent original PE evidence

| Physical original function | Complete native code | Semantics and original x86 |
| --- | ---: | --- |
| `0x00445720` | **70B /22 i386** | True cdecl `(x*x + y*y) + z*z` on a 12-byte Vector3; 3 scalar SSE `MULSS`, 2 scalar `ADDSS`, return via x87 `FLD` ST0 |
| `0x00445700` | **25B /10 i386** | True cdecl `sqrt(animation_depth_squared(vector))`, two real REL32 direct calls and a real `FSTP [esp]` parameter handoff |

The [original-only verifier](../scripts/verify-animation-depth-math-native.py)
attests both immutable PE extents with Capstone, their real instruction
boundaries/operations, absence of any PE HIGHLOW original relocations, and
the original calls **`0x00445707 -> 0x00445720`** and
**`0x0044570F -> 0x00446B30`**. The second is the existing independently
reconstructed 35-byte `scalar_math::square_root(float)` wrapper, which
widens the float to double for the CRT; it is **not** misattributed as
part of either of the two new functions.

Original real game-renderer consumers are also confirmed from complete
native caller functions, not a historical Ghidra guess: the 2,769-byte
mode6 at `0x004408B0` calls the 25-byte wrapper at
**`0x004409C8`**, and the 753-byte mode7 at `0x00441C00` calls it at
**`0x00441D2A`**. Their input values are screen-relative game
position vectors; the two original helper bodies are therefore game-owned
logic, not automatic C++ standard-library templates or CRT plumbing.
Names `animation_depth` and `animation_depth_squared` are descriptive
reconstruction spellings, **not** claims about original source identifiers.
The mode6 caller remains open NONEXACT. The 753B mode7 caller was
subsequently completed as whole-native [strict exact](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md),
and its 1,996B setup callee likewise became
[whole exact](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md). The
5,993B enclosing Draw dispatcher remains independently NONEXACT.

## Full canonical source and relocation replay

The shared pinned x86 MSVC 19.44.35211 source profile uses
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The two real functions are emitted by **one** ordinary source compile
into one canonical COFF object with matching saved compiler receipt,
`build/core838-canonical/AnimationDepthMath.obj`.

The new independent `config/match-units.toml` manifest units are:

- `animation_depth_squared_70`: full 70/70B, **zero COFF relocations**, as
  independently required by the native PE data path.
- `animation_depth_25`: full 25/25B, exactly **two** COFF REL32 fields:
  `+0x8` genuine `animation_depth_squared` -> `0x00445720`, and
  `+0x10` genuine `scalar_math::square_root` -> `0x00446B30`.

These targets were established **before** candidate byte comparison by
original physical E8 instructions and complete known caller/callee
operations. The strict comparator checks the actual COFF
relocation type, offset, symbol, independently named target and **every
replayed relocated byte**, not merely matching branch shapes.
A fresh source-filtered cold build and canonical replay passed:

```text
animation_depth_squared_70: exact (70/70 bytes)
animation_depth_25: exact (25/25 bytes)
Exact replay: 2/2 units, 1 cold objects
```

The tracking source map now holds one distinct physical mapping per
function in `reccmp-functions.csv`, `implemented.csv`, and
`functions.csv`. Independent game-specific callers and original
12-byte Vector3 fields ground both `function-origins.csv` rows as
game-authored, not compiler/library; `config/matches.csv` contains **one
matching row per original head**, counted once. This adds **two complete
game-authored functions /95 original `.text` bytes** and **two strict
canonical units /one canonical object**, without any overlapping caller
bytes or new length credit for the existing `square_root` library wrapper.

| Verified current tracking | Before | After | Delta |
| --- | ---: | ---: | ---: |
| Game-authored exact functions | 593 | **595** | +2 |
| Game-authored original native bytes | 196,722 | **196,817** | +95 |
| Source-present functions | 1,239 | **1,241** | +2 |
| Strict canonical units | 1,240 | **1,242** | +2 |
| Canonical object/receipt providers | 260 | **261** | +1 |

No previously exact source, public header, compiler profile or original
target changed. The only newly built source provider was
`src/AnimationDepthMath.cpp`; **existing exact provider replay scope =0**.
No unfiltered all-unit cold replay was run.

## Bounded reproduction

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-depth-math-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDepthMath.cpp
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/progress.py --check
```

The original 753B mode7 D3DX projection/fog caller was subsequently
[whole exact](ANIMATION_DRAW_MODE7_753_STRICT_EXACT.md), using this original
25B depth helper, as was its 1,996B matrix/corner
[setup function](ANIMATION_DRAW_MODE7_SETUP_1996_STRICT_EXACT.md).
Those later admissions do not duplicate these two independent depth leaf
match units or their 95 native game-authored bytes.
