# CORE/RECON-842 — complete original 1,378B Mode6 screen projection Boss, whole strict native exact

The locked Japanese TH20 v1.00a Steamless original executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains a whole game-authored mode6 projection preparation method at
**`0x00440340`**, called by the original still-NONEXACT 2,769B mode6
renderer at its physical E8 **`0x004408CB`**. The function was originally
source-absent in the TH20 inventory. The maintained ordinary C++
[`src/AnimationDrawMode6Setup.cpp`](../src/AnimationDrawMode6Setup.cpp)
now reproduces the complete original **1,378B /335 genuine x86 instruction
heads**, original **`sub esp,0xAC`**, and the natural `ret 4` screen-projection
result protocol, *byte-for-byte*. Its one original function earns **1,378
native game-owned `.text` bytes once**, without counting its dependencies.

The separately exact 73B Vector3 length and 86B 2D projection helpers
[CORE/RECON-841](ANIMATION_PROJECTION_MATH_73_86_STRICT_EXACT.md)
were essential genuine native callees to reconstruct this larger parent;
this is **not** a result obtained by only matching leaves. The original
5,993B main Draw Boss and 2,769B mode6 renderer caller remain distinct
unfinished functions and receive **zero** parent code-byte credit.

## Immutable original PE evidence and whole canonical acceptance

The independent [original PE-only audit](../scripts/verify-animation-draw-mode6-setup-native.py)
reads the original immutable .text and actual PE `.reloc` directory, and
verifies every one of **17 original direct E8 sites/physical targets** and
**21 original PE HIGHLOW site/target identities** before any source or
compiler object is accepted. It verifies all **335 disassembled x86
instruction heads**, actual original conditional branch operands, four
original projected-XY call sites, the real 64B identity matrix at
`0x0056E100`, and the genuinely file-backed **`[2][3][4]`** float
coordinate table starting at `0x0056E140`.

| Immutable physical original role | Native source/replay proof |
| --- | --- |
| Whole original 1,378B, 335 x86, `sub esp,0xAC`, genuine `ret 4` | **1,378/1,378B whole canonical strict exact** |
| `+0x1E` Animation rotation sum, `+0x3E` sine, `+0x5A` cosine | Three original E8 sites with independent accepted callee targets |
| `+0x68/+0x70/+0x78/+0x80` true default matrix/vector constructors | Four real folded trivial-constructor E8 sites at native `0x0040BDA0`, not duplicate authored game credit |
| `+0xA3` real zero Vector3 constructor | Original x86 with actual `0x00422DD0` constructor head |
| `+0x189/+0x1E2` two genuine D3DXVec3Project calls | Original imported `0x00540678` thunk, correct live viewport +0xE0 and true view/projection matrix locations |
| `+0x1F6` native Vector3 subtraction, `+0x210` actual Vector3 length | Real original `0x00429440` and now-strict `0x004399B0` |
| `+0x3AB/+0x436/+0x4BE/+0x548` projected corners | Four original E8 sites to whole exact `0x00445B20` with real 7-stack-argument member ABI |
| `+0x557` compiler security checker | One genuine `0x005429EE` E8, not game-created helper |
| All 21 PE HIGHLOW data references | **21/21 exact physical offsets and independently established true data target owners** |

The 21 actual data fields include the compiler security cookie, immutable
identity transform, **seven** real Graphics current-viewport pointer
reads at `0x005C5840`, original game-owned 1.0f/0.5f scalar references,
**four** original 28B-stride quad Z coordinates `0x005AEF18`, two
references to the real `0x0056E140` 2-axis/3-mode/4-corner coordinate
tensor, and four projected XY output references to `0x005AEF10`.
The original table's six true groups of four single-precision values are:

| X-axis mode | Four native X offsets | Y-axis mode | Four native Y offsets |
| --- | --- | --- | --- |
| 0 | −0.5, +0.5, −0.5, +0.5 | 0 | −0.5, −0.5, +0.5, +0.5 |
| 1 | 0, 1, 0, 1 | 1 | 0, 0, 1, 1 |
| 2 | −1, 0, −1, 0 | 2 | −1, −1, 0, 0 |

The pinned native x86 MSVC 19.44.35211 compiler profile is
`/nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.
The new `animation_draw_mode6_setup_1378` manifest unit declares all
**38 real COFF relocation records** from independently mapped source
symbols: **17 REL32** and **21 DIR32**. No target is derived by solving
the corresponding PE original field. The strict comparison verifies
original native instruction bytes, every physical relocation offset,
symbol/type/addend/independently proven destination, and all final
relocated bytes:

```text
animation_draw_mode6_setup_1378: exact (1378/1378 bytes)
Exact replay: 1/1 units, 1 cold objects
```

## Rejected historical assumptions and actual codegen corrections

The original 1,378B function is a complete, genuinely *one-body* game
state-machine/geometry helper: first calculate original inherited
rotation Z and its native sine/cosine, construct the real world/three
projected-point locals and a zero Vector3, copy the native identity
4×4 matrix, apply Animation base/current XY/Z translation, project
screen-center via D3DX, reject out-of-depth points, project the original
viewport reference and subtract screen vectors, derive true Euclidean
screen distance and half-height-scaled axes, write all four original
quad Z coordinates, and calculate each XY corner through the independent
exact 86B projected XY method.

Important source experiments and corrected facts:

1. **The real viewport field is +0xE0, not +0x104.** An early complete
   candidate accidentally passed `ViewportState::adjusted_viewport`
   instead of the original real `ViewportState::viewport`. The original
   disassembled D3DX input physically uses `process_graphics.current_viewport`
   +`0xE0`. Using the correct typed `viewport` fixed the original two
   D3DX argument-displacement words, without changing body length.
2. **No fifth Vector3 local exists in the original.** A separate temporary
   for subtracting the two projected vectors increased the compiler
   stack to `0xB0` and changed the first matrix-constructor x86 encoding.
   Assigning the natural `Vector3::operator-` return directly into the
   existing projected-difference object lets the compiler create its
   genuine 12B return-value temporary at the original location, restoring
   the original `0xAC` frame and **first 12 genuine E8 call sites**.
3. **One meaningful float has two real lifetimes.** The scalar half-distance
   is used to calculate X and Y scales and then its original compiler
   local slot is reused for the projected X origin. Using separate
   `scaled_half` and `offset_x` values prolonged an unnecessary four-byte
   local, producing 1,390B rather than the original 1,378B. Reusing
   the **already consumed** half-distance local after both scale
   calculations restored all four real vertex-Z store positions and
   original `0xAC` frame, without inert placeholders.
4. **The physical native array is 2×3×4, not flattened 6×4.** The
   original computes a 0x30-byte axis stride, a 0x10-byte mode stride,
   and 4×float corner stride. Explicit two-axis/three-mode/four-corner
   declaration `projection_mode_offsets[2][3][4]` preserves the real
   original data owner. Letting the selected row *decay naturally to a
   pointer*, instead of taking an explicit final `[0]`, removes a
   redundant zero-index calculation emitted under `/Od`. This aligns
   **all 17 E8 call sites and all 21 PE HIGHLOW physical locations**
   before source-level return scope correction.
5. **The final original NOP is a natural block boundary.** The original
   has real NOPs after both imported D3DX projection calls and one at
   `+0x54D` after the fourth projected-corner call, before `xor eax,eax`.
   The straightforward source success path compiled to **1,377B /334
   i386** and omitted precisely this last NOP, although all other
   source roles were correct. Placing the genuinely successful screen
   projection computations in their **own C++ lexical calculation scope**
   naturally emitted that final native NOP. There is no explicit `nop`,
   assembler, fabricated return, fake unused expression or manual code
   alignment. This restored **1,378B /335 x86**, with all
   **1,226/1,226 non-relocation bytes** identical in the provisional
   comparison, before independently replaying all 38 relocations.
6. **The original clip preserves unordered float behavior.** Original
   `COMISS`/`JA` and `COMISS`/`JBE` reject negative or greater-than-one
   projected depth while allowing unordered NaN inputs to continue.
   The C++ `if (0.0f > depth || depth > native_one)` preserves exactly
   this physical operand/branch behavior; it was not replaced by a
   conventional but semantically different `depth < 0 || depth > 1`
   branch that would change the native instruction/NaN contract.

All original constructor/call/data reference roles are source-backed by
actual game geometry and SDK data. The externally imported D3DX routines,
compiler security code, and folded 14B no-op constructor receive **no
additional authored-game function credit**.

## Bounded replay and progress

The only newly authored compiler source is the complete
`src/AnimationDrawMode6Setup.cpp`, one new full native match unit/one
canonical COFF provider. The natural method declaration is added to the
shared `AnimationDrawDetailedOwner.hpp` receiver ABI without adding
storage or virtual methods. This header is included by the previously
strict 73+86B projection math provider, the strict 753B mode7 renderer
and the strict 1,996B mode7 setup, so **those three existing provider
closures are separately cold-replayed**. The large 5,993B noncanonical
Draw Boss is independently recompiled under its existing focused source
verifier. No unrelated source, original PE, exact manifest unit or
compiler profile changed; no unfiltered cold replay is performed.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-mode6-setup-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode6Setup.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationProjectionMath.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7Setup.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

This adds **one complete original game-owned exact function /1,378
disjoint native bytes**, without credit for its four strict XY calls or
whole 2,769B mode6 rendering caller. Current live totals become
**600 complete authored original exact functions /201,103 native bytes**,
**1,246 source mappings /1,247 strict canonical units /265 pinned
COFF object/receipt providers**. The game as a whole is still not
linked or playable from this reconstruction.
