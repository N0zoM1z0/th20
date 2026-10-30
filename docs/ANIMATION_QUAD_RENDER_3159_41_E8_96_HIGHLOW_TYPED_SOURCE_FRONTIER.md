# CORE/RECON-829 — 3,159-byte original quad submission Boss, fully sourced but NONEXACT

**SUPERSEDED HISTORICAL SOURCE CANDIDATE (CORE/MAINT-896).** This
report accurately records an *earlier NONEXACT experiment*, not current
quad-submit acceptance. The actual 3,159B parent is now **whole strict
exact**, including its 3,180B NOP/case-table compiler contribution; see
[the accepted original PE/COFF proof](ANIMATION_QUAD_SUBMIT_3159_STRICT_EXACT.md).
Its genuine 20B `round(float)` sibling is a
[standard-library method](ANIMATION_STD_ROUND_FLOAT_20_LIBRARY_EXACT.md),
not authored-game code. Do not reopen the obsolete 3,212B candidate as
current work. Dated raw observations below are retained for provenance.

This report records the **complete maintained C++ source**, not a strict native
match, for the original game-authored renderer method at `0x0043F6A0`.
It is independently compared with the locked Japanese TH20 v1.00a Steamless
PE (`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`).
Original executable extent is **3,159 bytes /763 real x86 instructions**.
The function is **SOURCE-PRESENT and NONEXACT**, and this work adds **zero**
whole-original exact game functions, original `.text` credit, or canonical units.

## Original PE facts, independently checked

`scripts/verify-animation-quad-submit-native.py` reads the actual PE and
`.reloc` entries, checks the original whole function boundary/RET, and verifies
**41 native direct E8 occurrences to eleven physical targets**: ten game
callee heads (40 calls) and compiler `__security_check_cookie` at `0x005429EE`
(one call). There are **96 genuine in-body PE HIGHLOW entries**; the target
histogram, which is independent of Ghidra naming and existing C++ code, is:

| Original absolute target | Count | Meaning |
| --- | ---: | --- |
| `0x005AEF10` | 23 | shared 28-byte quad vertex x-coordinate base |
| `0x005AEF14` | 22 | shared vertex y-coordinate base |
| `0x005AEF20` | 16 | shared vertex color field |
| `0x005AEF24` | 6 | shared vertex U field |
| `0x005AEF28` | 6 | shared vertex V field |
| `0x005C5840` | 16 | actual live `Graphics::current_viewport`, graphics owner +0xB00 |
| `0x0056E0EC` | 4 | original `0.5f` scalar constant |
| `0x005B25C0` | 1 | compiler stack security cookie |
| `0x005C4D40` | 1 | `process_graphics` owner |
| `0x004402F8` | 1 | native indexed five-mode color-switch table operand |
| **Total** | **96** | independently checked physical relocation entries |

The original RET is followed by one alignment NOP and **five separately
PE-relocated four-byte code pointers** at `0x004402F8`. Those five pointer
entries are not part of the 96 in-body count.

## Corrected C++ hypotheses and actual compiler output

`src/AnimationQuadSubmit.cpp` now directly manipulates all four shared native
`SpriteTexturedVertex` records, rather than introducing a range-for iterator
and local alias around the original global. It uses genuine 4-byte packed
`AnimationColorChannels` with a two-value reusable union to emit the original
per-channel saturation and divide-by-255 operations. The code preserves
**separate four-store branches** for the color gradient modes 2 and 3 instead
of folding those operations into two ternary expressions, keeps the four
pixel-snap results as real single-precision temporaries shared by their
opposite quad corners, and reads the actual live graphics viewport for
**all sixteen** original bounds comparisons (no one-time cached pointer).
These changes follow original x86 source-independent load/store evidence.

`nice -n 15 scripts/repo-python scripts/verify-animation-quad-submit-source-roles.py`
compiles **only this NONEXACT** method with the pinned i386 MSVC profile,
reads its genuine COFF `REL32` / `DIR32` source symbol/addend records,
and checks their physical target-role histograms against the independently
verified original PE. The compiler now emits the security-cookie call
naturally, with no invented manual call. The verified results are:

| Property | Original PE | Maintained C++ candidate |
| --- | ---: | ---: |
| Physical direct calls | 41 (40 game + 1 compiler) | **41, all target-role counts agree** |
| In-body absolute relocation target roles | 96 | **96, all ten target-class counts agree** |
| After-RET case-table pointers | 5 | **5** |
| Genuine executable code | **3,159B /763 x86** | **3,212B /810 x86** |
| Extra table/alignment | 1B NOP + 20B native PE pointers | 20B generated COFF pointer data |
| Complete C++ COFF contribution | N/A | **3,232B** |
| Whole native match | original reference | **NONEXACT** |

The previous unrefined candidate was **3,796B /973 x86** plus 20B table,
so this source revision removes **584 executable bytes and 163 instructions**
while recovering the native 41/96 original data-and-call roles. The candidate
still has **53 additional executable bytes /47 instruction heads** compared
with the original. Actual E8/DIR32 *instruction locations*, branching,
SSE register operations, stack frame and after-RET layout still differ.
**Matching call/relocation-target frequencies is never a substitute for
zero-difference whole-function canonical replay.** The original parents at
`0x0043F6A0` (3,159B) and `0x00443880` (5,993B) remain NONEXACT, despite
whole-native-exact renderer child bodies at `0x00445BC0` (2,725B),
`0x00446690` (1,163B), `0x0043E9B0` (352B), and others.

## Reproduction, guardrails, and next work

- Original PE-only audit: `scripts/repo-python scripts/verify-animation-quad-submit-native.py`.
- Real current source vs original E8 and HIGHLOW-target roles:
  `nice -n 15 scripts/repo-python scripts/verify-animation-quad-submit-source-roles.py`.
- Retained source-specific compiler proof object:
  `build/core829-probe/AnimationQuadSubmitRoles.obj` and matching
  `build/core829-probe/AnimationQuadSubmitRoles.receipt.json`
  (noncanonical, preserved as cited compiler-probe evidence).
- Original 40-game-call historical frontier:
  [CORE/RECON-808](ANIMATION_QUAD_RENDER_3159_40_GAME_E8_SOURCE_CLOSURE.md).
- Exact independent 2,725B and 1,163B child proofs:
  [texture/sampler states](ANIMATION_QUAD_TEXTURE_STATES_2725_STRICT_EXACT.md)
  and [color blending state](ANIMATION_QUAD_BLEND_STAGE_1163_STRICT_EXACT.md).
- Next: recover the native switch case instruction arrangement and repeated
  packed-color evaluation, actual snap-wrapper ABI/codegen, and whole-function
  E8/PE-HIGHLOW *site positions* before attempting strict acceptance.

Neither changed file is a source or header of any `config/match-units.toml`
canonical exact unit. **Affected exact replay scope: zero**; only the
noncanonical quad method was compiled and the original PE audited. No
full-graph cold replay, Ghidra database refresh, or whole-game build was run.
Current live original authored strict exactness remains **589 functions /
193,512 disjoint original `.text` bytes**, with **1,238 strict units and
259 canonical object/receipt providers**.
