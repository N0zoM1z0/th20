# CORE/RECON-834 — full original 5,993B Animation Draw Boss: native 80-pointer CFG and ABI recovery (NONEXACT)

The **entire original Japanese TH20 v1.00a Steamless** renderer dispatcher
`AnimationPoolOwner::draw(Animation*)` at **`0x00443880`** has an independently
verified original **5,993B /1,501 actual x86 instructions**. The target's
locked SHA-256 is
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint revisits the maintained, source-present
[`src/AnimationDrawBoss.cpp`](../src/AnimationDrawBoss.cpp) without trusting
historical compiler/ABI hypotheses. The **whole parent remains NONEXACT**;
no newly exact original game functions or bytes are claimed.

## Verified full-original PE facts and new isolated MSVC evidence

| Independent original PE facts | Current pinned C++ compiler evidence |
| --- | --- |
| Complete 5,993B /1,501 native x86 | Complete candidate **6,085B /1,514 i386**; still NONEXACT |
| True native direct 49-pointer primary dispatch | **49 direct COFF pointer relocations**, same 17-target case-alias partition |
| True native 31-pointer nested dispatch | **31 direct COFF pointer relocations**, same 29-target case-alias partition |
| 123 actual native E8 calls /43 real physical targets | **123/123 target identities, multiplicities and the entire original physical call *order*** |
| Native E8 sites from function start through first 81 calls | **First 81/123 actual E8 offsets and all target identities coincide** |
| 32 in-body original PE HIGHLOW relocation entries | **32 genuine compiler DIR32 with identical target-role counts, first 14 exact physical field offsets** |
| Original three-byte code/table alignment and 80 native table entries | **3B compiler alignment and all 80 direct entries**, no compressed lookup bytes |
| Native `sub esp,0x204` and remaining original nested case code | Candidate `sub esp,0x218`, still different codegen and later relocation sites |

The current single function COFF contribution is **6,408B**: **6,085B real
executable code**, **3B compiler alignment**, **196B/49 main pointers** and
**124B/31 nested pointers**. Original full code+table extent is **6,316B**:
5,993B body +3B alignment +196B main table +124B nested table. The
**92-byte difference** remains in executable code, not omitted case data.
The original PE-only native census is
[`scripts/verify-animation-draw-boss-native.py`](../scripts/verify-animation-draw-boss-native.py).

`nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py`
builds **only this NONEXACT source** with the pinned MSVC x86 profile
`/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`
and checks original PE versus compiler COFF *actual* E8 targets, E8 order,
the first 81 physical E8 sites, all 32 body DIR32 target roles, the first
14 original body data-field positions, both table pointer counts and **every
mode-alias relationship**. It is not the canonical exact comparator; no
manifest match unit is admitted for this parent.

Original in-body HIGHLOW target multiplicities, independently from the PE:
18 native `2.0f` references at `0x0056C8D0`; five original
`process_graphics` references at `0x005C4D40`; four true
`window_state.scale` references at `0x005B8818`; two original `0.5f`
references at `0x0056E0EC`; one security cookie at `0x005B25C0`, and
one operand reference to each of the two real native dispatch tables
`0x00444FEC` /`0x004450B0`. The rebuilt source reproduces every one of
these **32 target roles**. Original case-table pointers are verified from
real PE `.reloc` HIGHLOW records, not Ghidra guesses.

## Original source/ABI hypotheses disproved

1. **A compressed primary switch was an authoring artifact.** The previous
   C++ had a shared `default` for 28 original nested-case mode values,
   so MSVC emitted **17 pointer entries plus 49 byte indexes**. The original
   PE has **49 actual direct pointer entries**. Explicitly listing cases
   `16..22` and `26..46` as one normal C++ main `switch` branch naturally
   restores the complete **49+31 direct-pointer** CFG and the real 17/29
   pointer alias partitions, with no hand-built table or assembly.
2. **The original mode 6 call is a thiscall, NOT a one-parameter free
   fastcall.** The earlier C++ `animation_draw_mode6(Animation*)` passed the
   animation only in ECX and omitted the renderer receiver and stack
   argument. Original caller `+0x19E` loads Animation*, `+0x1A1` **pushes**
   it, `+0x1A2` loads the actual renderer receiver from `[ebp-0x14]`, then
   calls `0x004408B0` at `+0x1A5`. The complete original **2,769B** callee
   stores ECX as its owner, reads `[ebp+8]` as Animation*, and ends in
   **`ret 4`**. A genuine local typed `draw_complex_mode6(Animation*)`
   member recovers the real call without adding fake receiver storage.
   This callee itself remains **SOURCE-ABSENT/NONEXACT** and receives no
   exact byte credit.
3. **Two renderer callee stack contracts were wrong.** The complete
   original `0x0043CD40` body ends in **`ret 0x20`**, not the 28 bytes
   implied by the previous seven-argument mode26 declaration. Native case26
   loads both original Animation flag words `+0x4AC` and `+0x4A8`, and
   pushes both along with its color and float arguments. The fixed typed
   eight-argument declaration naturally emits these actual field loads.
   The original `0x0043C4E0` also ends in **`ret 0x20`**. In mode33, the
   `0x004456C0` packed alternate-color getter was **not a useless extra
   call**: its return value is physically pushed as the eighth argument
   alongside the other packed color from `0x004456E0`. The source now
   passes **both colors**, with no fabricated unused call. The separate
   [original 18-backend ABI verifier](../scripts/verify-animation-draw-boss-abi.py)
   validates the complete original physical callee RET widths.
4. **The original case ordering is not numerical mode ordering.** The
   native 49-pointer main table has 17 distinct physical entries and
   orders the code blocks `0,1,4,5,6,7,8,15,9,11,24/25,47,48,2,3`
   before the nested branch. The second 31-pointer table has **29 distinct
   real entry addresses**; its actual physical code layout begins
   `26,16,27,20,21,22,37,38,39,40,41,28,...` rather than ascending
   modes. Placing these **real typed cases** in physical original order,
   and keeping the nested switch inside one main-switch shared case block,
   recovers **all 123 E8 call identities in the same actual sequence**.
   It also aligns **the first 81 physical E8 sites** from the very
   beginning of the function, including the entire root dispatch and the
   first substantial nested draw cases.
5. **Eagerly cached expressions changed observable machine-code roles.**
   Before the original main mode dispatch, the prior source cached a
   receiver pointer and a doubled draw count, adding non-native stack
   and instructions. The current natural thiscall receiver and per-case
   doubled count recover original early x86. Likewise caching the nested
   `half_height = height / native_two` once erased nine real original
   `native_two` PE HIGHLOW references: the ten independent per-mode
   arithmetic sites plus other authentic 2.0f operations now reproduce
   **18/18** physical target-role multiplicities. The individual
   original Animation flag/count/radius/delta fields are read in their
   proper mode-specific call paths, instead of being globally hoisted
   before the native nested dispatch.
6. **The native `0x00445BC0` role is no longer guessed geometry setup.**
   Earlier code declared `prepare_render_geometry(Animation*)` as a
   provisional new local member for this real E8. Independent
   [2,725B whole strict exact reconstruction](ANIMATION_QUAD_TEXTURE_STATES_2725_STRICT_EXACT.md)
   already establishes this physical function as
   `AnimationQuadSubmitOwner::bind_native_texture_state(Animation*)`.
   The maintained Boss now calls the true existing typed function with
   no duplicate implementation and the same original receiver/callee.

## Native boundaries, remaining genuine nonexact frontier

The original root and candidate **first 28 E8 sites** are at the same
relative offsets, and the source's first 81 E8 locations/targets match
as a consequence of source-order, prototype and per-case parameter fixes.
The source may have the same role/parameter count across all branches without
matching each original instruction, branch encoding or stack offset.

**The next measurable difference begins in native mode35**, whose first
inherited auxiliary-scale call is at original `+0xFC8`, after which the
original stores its x87 result to a real stack slot. The current compiler
lowers the first discarded result differently and also computes the two
separate `height/2` expressions in a different evaluation order relative
to a second scale call. Similar divergences grow across modes 36, 29/30,
45/46. Original function stack is `0x204` while candidate is `0x218`;
its **6,085B/1,514-x86** compiler contribution remains **92 bytes /13
instructions longer** than the native 5,993B/1,501-x86. Do not add
inert compiler-shaping locals or fake return values merely to match that
shape; resolve actual expression/stack ownership first.

The original source-present authored parent at `0x00443880` stays
**NONEXACT** with zero new `.text` byte credit, no `config/matches.csv`
addition and no claim that TH20 links or runs. Existing whole-native
exact quad submission `0x0043F6A0`, Graphics 92B render-state transitions,
color getters and related leaf routines remain separately exact. Their
source/header/manifest/compiler profiles are **unchanged**.

## Reproduce (affected-only, never an all-graph cold replay)

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-boss-native.py
scripts/repo-python scripts/verify-animation-draw-boss-abi.py
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/build.py --check
```

The isolated new **noncanonical** whole-function compiler object/receipt is
`build/core834-probe/AnimationDrawBoss.obj` and
`build/core834-probe/AnimationDrawBoss.receipt.json`. Previous probe objects
under `build/core797-probe` and the private experimental variants under
`.analysis/core834-draw/` remain ignored retained evidence.

**Affected canonical exact replay scope: zero.** The sole modified native
source `src/AnimationDrawBoss.cpp` is not yet a canonical accepted object.
No exact caller/callee source, shared header, manifest/provider/compiler
profile, original PE or receipt was changed. Only the single NONEXACT
source was compiled in an isolated pinned MSVC probe, and the physical
original PE read. The other 1,240 accepted units were not cold replayed.
