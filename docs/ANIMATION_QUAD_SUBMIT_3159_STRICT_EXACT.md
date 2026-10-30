# CORE/RECON-832 — complete original 3,159B renderer quad-submission Boss, strict native exact

The locked original Japanese TH20 v1.00a Steamless executable, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`,
contains the game-owned `AnimationDrawModeOwner::render_quad(Animation*, int)`
at **`0x0043F6A0`**. It is **3,159 real executable bytes /763 native
x86 instruction heads**, ending in `ret 8` at `0x004402F4` (final byte
`0x004402F6`). The PE then has a **one-byte alignment NOP** at
`0x004402F7` and **five genuine 32-bit mode-switch case pointers** at
`0x004402F8..0x0044030B`. All **3,180 bytes** are covered by the single
canonical unit `animation_quad_submit_boss_3159` with
`size = 3159`, `compare_size = 3180`. **Complete zero-difference canonical
comparison: 3,180/3,180 bytes strict exact.** Only the original 3,159 game
function bytes count toward authored .text coverage; the switch data is
included for strict verification without separate credit.

## Independent original PE evidence and complete native replay

The source-independent verifier
[`scripts/verify-animation-quad-submit-native.py`](../scripts/verify-animation-quad-submit-native.py)
reads the original locked PE, disassembles the complete body and separately
parses the original executable's `.reloc` directory. The genuine original has
**41 direct E8 calls to 11 physical destinations** (40 game calls to ten
callee heads; one natural compiler `__security_check_cookie`) and **96 in-body
PE HIGHLOW fields** in ten target classes. Their original native identities
include **73 quad vertex coordinate/color/UV fields**, **16 actual live
Graphics viewport pointers**, **four 0.5f constants**, **one security
cookie**, **one `process_graphics` instance**, and **one genuine five-mode
case-table pointer**. Original E8 destinations were independently verified
in the previous [whole native call/data census](ANIMATION_QUAD_RENDER_3159_41_E8_96_HIGHLOW_TYPED_SOURCE_FRONTIER.md),
not inferred from the current candidate object.

The actual original after-RET five-pointer table holds
`0x0043FC47, 0x0043FC47, 0x0043FDCC, 0x0043FDCC, 0x0043FF70`;
all three distinct targets are independently valid instruction heads inside
the entire original function. Their physical PE relocations at
`0x004402F8, 0x004402FC, 0x00440300, 0x00440304, 0x00440308` are also
attested from the PE. The table, target code offsets and trailing NOP
are **not** arbitrary padding or synthesized pointers.

The pinned x86 MSVC 19.44.35211 compile from the maintained
[`src/AnimationQuadSubmit.cpp`](../src/AnimationQuadSubmit.cpp) uses
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
with the repository-locked environment and headers. The whole function
produces a genuine ordinary COFF contribution of exactly **3,180B**:
**3,159B /763 x86**, the native **one-byte NOP**, and the **20B** five-way
mode-switch pointer table.

The canonical manifest
[`config/match-units.toml`](../config/match-units.toml) explicitly enumerates
all **142 real COFF relocation records**:

| Original/native field | Source relocation evidence | Strict replay |
| --- | ---: | --- |
| 41 direct callee / compiler calls | 41 real REL32, all exact E8 instruction sites | 41/41 |
| Original game/data/cookie/case table fields in body | 96 real PE HIGHLOW and source DIR32, all exact physical sites | 96/96 |
| Five original post-RET code-pointer fields | Five actual PE HIGHLOW /source DIR32, with three real case heads | 5/5 |
| All bytes after complete independent relocation replay | 3,159B body +1B NOP +20B table | **3,180/3,180 exact** |

Each manifest target is obtained from **independent** original PE call-role
census and genuine symbol/owner provenance: the actual 28B quad array base
`0x005AEF10`, live Graphics instance `0x005C4D40` (viewport at +`0xB00`),
original `0.5f` at `0x0056E0EC`, compiler security-cookie global
`0x005B25C0`, the 11 native E8 call identities, and the independently
attested local switch/table entry addresses above. COFF relocation addends
are applied by the strict comparator. No manifest target is obtained by
solving the PE field being compared; the PE field is used only to **check**
each independent source identity. Actual COFF relocation symbol/offset/type
triples must match the manifest exactly, and every relocated byte is replayed
and compared. The separate source-role verifier checks **all 41/41** physical
E8 sites, **all 96/96** body data sites, and **all five** table pointer
positions. This is a canonical strict result, not a structural-exact probe.

## Errors corrected after re-checking the native machine code

The previous [CORE/RECON-831](ANIMATION_QUAD_SUBMIT_3159_NATIVE_CONVERGENCE_NONEXACT.md)
had already converged to 3,159B/763 x86 with 41 exact E8 sites, but the
`0x54` original frame versus candidate `0x4C` and seven UV relocation-site
differences remained. Those historical observations were true **for that
candidate**, not immutable judgments about the source.

1. **Actual packed RGBA local ownership.** Mode 2/3 used two additional
   four-byte `SourcePackedColor a,b` temporaries, even though the original
   native mode 2/3 reads and writes the same **two shared four-byte packed
   RGBA locals at `[ebp-8]` and `[ebp-0xC]`** that the other branches use.
   Reusing the existing `main_color` / `other_color` makes the original
   whole-function stack layout and genuine channel call/store sequence
   agree, without inert compiler-shaping locals or ABI lies.
2. **Separate real float result and x87 spill.** `animation_snap_round(x)
   - 0.5f` in one typed initializer retains the separate natural x87
   return-value spill and final rounded float, whereas a later `snap -=
   0.5f` made the compiler reuse the local slot. The original native
   stack `sub esp, 0x54`, all original `this`/dx/dy/snap locals, real
   x87 spills and subsequent receiver and packed-color slots now match.
3. **Distinct native U and V indexing.** The last historical claim that
   both U and V secondary base reads were index `[1]` was **wrong**.
   Original instruction `mov ecx,8; shl ecx,1` at offsets
   `+0xB1F/+0xB24` reads **U base `vectors_378[2]`** (8B stride).
   Original `mov eax,8; shl eax,0` at `+0xBD9/+0xBDE`
   instead reads **V base `vectors_378[1]`**. The previous single-index
   assumption was not correct despite producing the right aggregate
   relocation target counts.
4. **Distinct native V output order.** The original V second operation
   writes output vertex **2** (`shl edx,1` at `+0xBCF`), not vertex 1.
   The third operation reads V base index 1 and stores output vertex **1**;
   the final V3 adds the **V1** output (`shl ecx,0` at `+0xC0A`), not V2.
   Natural maintained C++ now emits U outputs in order `0,1,2,3` and V
   outputs in order **`0,2,1,3`** with their correct dependencies.
   This corrects actual game data/texture behavior rather than merely
   changing instruction lengths.
5. **Other original code restored in the prior candidate.** The 16 native
   unordered-inclusive `COMISS` clip branches, direct sprite/renderer
   texture fields, five-pointer switch default placement, original
   renderer tint per-channel loads, and true object receiver/callee graph
   were retained from the verified previous work, without artificial code.

The isolated provisional byte comparison after independently assigning the
physical PE relocation roles now also observes **3,159/3,159 original body
bytes identical**. Crucially, this observation is independently superseded
by the **actual whole 3,180/3,180 canonical replay** above; the provisional
probe alone would not have established exact acceptance.

## Focused reproduction and scope

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-quad-submit-native.py
nice -n 15 scripts/repo-python scripts/verify-animation-quad-submit-source-roles.py
nice -n 15 scripts/repo-python scripts/build.py --unit animation_quad_submit_boss_3159
scripts/repo-python scripts/compare-coff-function.py --unit animation_quad_submit_boss_3159
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/progress.py --check
```

The preserved **canonical** compiler object and fully pinned source/include
receipt are at `build/core832-canonical/AnimationQuadSubmit.obj` and its
matching `.receipt.json`. The source-role diagnostic object and receipt are
separate at `build/core832-probe/AnimationQuadSubmitRoles.*`. The original
locked target, previous canonical objects and their receipts remain unchanged.
No previously exact C++ source, shared header, compiler profile or original
comparison target was changed: **previous exact-provider replay scope is zero**.
One **new** source/object and one **new** 3,180B canonical unit were freshly
built/replayed. No unfiltered all-graph cold replay was run.

This adds **one whole original game-authored exact function /3,159 original
.text bytes**, not the additional NOP/table bytes and not any of the ten
already credited independent children. The 5,993B Animation draw dispatcher,
12,140B Bullet command parent, 41,967B Enemy ECL parent and 39,470B
Animation VM remain independent unfinished bosses.
