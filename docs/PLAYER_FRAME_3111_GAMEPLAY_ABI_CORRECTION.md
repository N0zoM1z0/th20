# CORE/RECON-550 — native gameplay call and floating-argument corrections in entire 3,111B Player frame

Original executable: Japanese TH20 v1.00a Steamless,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.

**The complete 3,111-byte Player main-frame source is maintained at
`src/PlayerMainFrame.cpp` and remains NONEXACT.** This checkpoint
corrects two *observable gameplay call/evaluation-order differences*
in the former complete source, discovers a misleading compiler-profile
assumption, and improves the independent native whole-body alignment.
Neither a prefix, child, one instruction sequence nor similar code
length grants any original-byte credit to the still-nonexact parent.

## Original whole-function provenance and actual targets

The real original physical owner `0x004F9C30..0x004FA856` contains
**3,111B / 783 native x86 instructions**, SHA-256
`7f0bff5c2e175ff3d223c9e958fd908e39016b136fd1ff0eb0e1ce0cf6672467`.
The independent original native E8 decoder finds **67 direct calls**;
the real PE `.reloc` parser finds **37 HIGHLOW fields**. It operates
on the real 0x1485C-byte Player class and routes movement, Animation,
InputInf and two PlayerOption arrays; its separate 555B
`Player::apply_move_delta` callee is still NONEXACT.

### 1. The Context EnemyController getter is **called twice**

The older source had saved a single pointer:
`auto* enemies = context->enemy_controller()`, then tested its presence
and used that cached pointer to call `enemies->count()`. This
incorrectly suppressed one actual original game call. The immutable
original E8s at **`0x004FA0D2` and `0x004FA0E8`** both target the
separately accepted `Context::enemy_controller()` native at
**`0x00412730`**, before the single original EnemyController count E8
at **`0x004FA0EF`** targeting **`0x00478080`**. Original code reloads
the Context pointer between the two getter invocations; it does
not simply cache the first result. The maintained source now
separately calls the real getter in the presence check and again in
the positive-count check, retaining the original Timer predicate and
reset/focus state on failure. This matters for the correct number
and order of game method invocations, not just bytes.

### 2. The focused sprite's two scale arguments are **computed twice**

The previous source evaluated
`(collision_expansion - native_one) * native_two + native_one` into a
single `float scale` and passed that same value to
`Animation::set_scale_58(scale,scale)`. The original does **not**
reuse a source temporary. At original
**`0x004FA300..0x004FA33F`**, x86 performs two independent sets of
`subss`, `mulss`, and `addss` on the actual Player float at
`+0x2238` and the real native global 1.0f/2.0f constants. It pushes
the two separately computed float arguments before the physical E8
at **`0x004FA34A`** to the real `Animation::set_scale_58` method
at **`0x004864F0`**. The alternative original default-scale call at
**`0x004FA371`** independently passes original 1.0f twice.

The maintained source now independently computes both genuine
floating expressions and uses the original positive conditional
(`if (collision_expansion_enabled())`) before the expanded-scale
path, with the 1.0f/1.0f path as its alternative. This restores the
real source-observable float load sequence. The order of the two
identical expressions is immaterial for ordinary scalar values but
their **number of real native reads and relocation fields is not**.

## Compiler profile false equivalence exposed

The previous 3,235B candidate used `/GS /sdl /EHsc` and unexpectedly
contained an **extra compiler security-cookie prologue and epilogue**.
The original x86 at `+0x1C` directly stores ECX as the Player receiver,
with **no stack cookie read**, and returns without any security-cookie
check. Multiple genuine locked MSVC 19.44.35211 i386 compilation
experiments established that `/sdl` enabled a `/GS` cookie in this
particular C++ method even when `/GS-` was supplied earlier, whereas
`/GS /EHsc` without `/sdl` does **not** emit that unwanted check.
This is a **local compiler observation**, not a claim that the game's
entire original build used `/sdl-` or disabled `/GS` globally. Other
already canonical source units keep their existing recipes unchanged.

## Complete C++ parent results and remaining byte frontier

| Whole parent metric | Original immutable game | Before this checkpoint | Corrected maintained C++ |
| --- | ---: | ---: | ---: |
| Entire game-body bytes | **3,111** | 3,235 | **3,239** |
| Original/candidate x86 instruction heads | **783** | 807 | **805** |
| Original mnemonic kinds aligned in native order | **783** | 672 | **730** |
| E8/REL32 call-reference fields | **67** | 67 (one false cookie, one missing getter) | **67** (no cookie; both getters) |
| PE HIGHLOW / COFF DIR32 fields | **37** | 35 | **37** |

**None of the 3,111-byte original parent is strict exact.** The improved
candidate even has a somewhat larger size than before: true
gameplay/member-call identity and original numerical evaluation
order take precedence over a falsely attractive code length.
The **67/37 candidate relocation counts now agree** with the
native original's **67/37**, but the **positions, exact callee
identities and remaining nonrelocated bytes have not all been
reconciled**. In particular, the original physical
`0x00449430` 45B handle equality method is distinct from the
existing `AnimationHandle::operator!=` 45B inequality method,
so they cannot be silently treated as a linker-folded alias without
proving the source type/ABI. The original 33-point history copy
retains its original by-value snapshot before the second indexed
lookup; a pointer-only variant can shorten the candidate code but
potentially changes the observed evaluation order and was rejected
as a source correction here. The original 273B Bullet draw-group
and 555B Player movement remain separate open fronts.

### Bounded source/codegen evidence

This improvement was proved by independent original native game E8
and float instruction reads, then **complete source recompilation**
under locked C++20 x86 MSVC `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /EHsc` (without the erroneous `/sdl` for this source).
The entire maintained function now produces a **3,239B/805-instruction**
ordinary C++ object in `build/core550-probes/PlayerMainFrame-maintained.obj`.
There is **no canonical exact unit** in
`src/PlayerMainFrame.cpp` yet, so the entire modified-source scope
has **zero existing native strict units to replay**. No shared header,
previously accepted source, compiler recipe, original target bytes,
physical original match ledger or 1,182 other original canonical units
were touched. Running a whole-graph cold replay here would not
verify anything relevant and was deliberately avoided.

Reproducible private whole original/candidate differences:
`.analysis/core542-player-main-blocks.json`,
`.analysis/core544-player-profile-matrix.json`,
`.analysis/core545-player-two-gameplay-fixes-results.json`,
`.analysis/core546-player-main-native-diff-blocks.json`,
`.analysis/core547-player-scale-branch-results.json`,
`.analysis/core548-player-focus-history-results.json`, and
`.analysis/core550-player-main-scoped-compiler-score.json`.

Game-authored original exact count remains **476 whole functions /
168,855 disjoint native bytes**. Original Player movement and main
frame remain NONEXACT. Whole linked gameplay is not yet available.
