# CORE/RECON-1105 — complete 586B centered narrow Renderer text source, SSE frontier

The original Japanese TH20 Steamless v1.00a executable (SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`) contains a distinct **586-byte /140-instruction** Renderer text function at `0x0044ADD0..0x0044B019`. The entire native body SHA-256 is `f6f5cc2d5565eb50d13a16813098118685183bbaedbcb678eb6b766371f5f829`. A real `ret` ends at `0x0044B01A`; the following `0x0044B020` is the **different 578B ASCII renderer**. The original 586B centered function has two observed callers, at `0x004DECF0` and `0x0052DF30`.

The full natural C++ source is now maintained in [`AnimationRendererCenteredText586.cpp`](../src/AnimationRendererCenteredText586.cpp). Its `__cdecl` variadic member belongs to the same borrowed [`NativeRendererFormattedTextView`](../src/NativeRendererFormattedTextView.hpp) owner as the separately whole-exact **417B** formatted-text function. Both methods pass `this` and the eight-byte hidden result pointer on the stack, rather than impersonating a nonmember caller; both delegate to the original `0x0044FFF0` submit method using the same Renderer `this`. The 417B exact unit was rebuilt and passed **417/417** after adding this sibling declaration, with no wider shared-header changes.

The [narrow CRT ABI correction](RENDERER_TEXT_NARROW_CRT_ABI.md) resolves the
previous wide declaration without changing this complete 586B candidate or
its owned EH sections. Its SSE frontier remains open.

## Original game behavior and width calculation

The complete original acquires `process_locks.slot(9)`, loads a float font advance from the genuine `0x0056C768` indexed table, formats variadic input with the separately exact `0x00447940` narrow-text helper into a 0x500-byte `char` stack buffer, obtains `Animation::sprite_data()`, copies the four Animation transform words at `+0x3A8..+0x3B4`, sets bit zero of the actual **byte** at `Animation+0x49A` and independently reads bit ten of the **word** at `Animation+0x49C`.

The centered-horizontal displacement is the integer truncation of `sprite->extent_4c / 2.0f - ((font_advance * 2.0f - 1.0f) * float(strlen(formatted_bytes))) / 4.0f`. The original uses a real **unsigned 32-bit `strlen`** conversion, including its `0.0/4294967296.0` correction table, rather than a signed-only conversion or the unrelated scale used by the 578B ASCII caller. It looks up the Sprite texture, copies the original 40-byte `std::function<void()>` callback, passes the integer offset and `align << 1` to the 294B `submit_text_44fff0`, and releases the lock and callback under the genuine destructor/EH path. Formatting/encoding limitations of the native 0x500-byte stack region are not independently established.

## Complete physical call and data sites

All **11 physical E8 calls**, read from the immutable original machine-code relative displacements, are:

| Native call opcode offset | Original destination / role |
| --- | --- |
| `+0x39`, `+0x45` | `0x0040C310` lock registry slot, `0x0040B730` guard construction |
| `+0x7D`, `+0x92` | `0x00447940` formatter, `0x00437CD0` sprite lookup |
| `+0x12A`, `+0x1A4` | `0x0054FE20` byte `strlen`, `0x00445A00` texture lookup |
| `+0x1BE`, `+0x20A` | `0x004140F0` function copy, `0x0044FFF0` text submit |
| `+0x219`, `+0x228`, `+0x241` | `0x0040B900` guard release, `0x00414400` function destruction, `0x005429EE` security cookie check |

All **nine native PE HIGHLOW** fields are independently located at `+0x06 -> 0x00568578` (EH), `+0x18 -> 0x005B25C0` (cookie), `+0x35 -> 0x005C0240` (lock registry), `+0x56 -> 0x0056C768` (font table), `+0x10F -> 0x0056C8D0` (`2.0f`), `+0x117 -> 0x0056C8CC` (`1.0f`), `+0x14E -> 0x0056CDD0` (unsigned length correction), `+0x172 -> 0x0056C8E0` (`4.0f`), and `+0x185 -> 0x0056C8D0` (`2.0f`). These physical sites are measured from the original PE, not guessed by reverse-solving a candidate COFF field.

## Current source-size convergence, still not exact

With the pinned MSVC 19.44 i386 C++20 `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` profile, keeping the genuine width
formula in one direct expression produces a complete **586B /140-instruction**
function. The old maintained two-intermediate expression produced
**594B /140 instructions**; no change to public types, EH handling or its
independently exact 417B sibling was needed. All **11 actual REL32 call
roles** and **nine DIR32 target classes** remain present. The new source
aligns **10/11 original E8 opcode offsets** (only `strlen` moves from
`+0x12A` to `+0x125`) and matches **399/506 ordinary bytes** when the
20 real COFF relocation fields are masked. This is a complete-function
comparison against the locked target, *not* a shortened native extent.

The previous 594B expression matched only **303/510 ordinary bytes**
in the original 586B window, and its later E8 sites were displaced.
However, the new 586B result is **not an all-metric improvement**:
the earlier expression correctly calculated and spilled the font
advance before calling `strlen`. The direct-expression lowering reads
`sprite->extent_4c` first and defers the font-advance calculation until
after `strlen`. It retains the same arithmetic inputs but changes
MSVC's floating-point evaluation and register lifetimes. Only the
first **four of nine original HIGHLOW physical positions** now agree,
versus seven of nine in the earlier source. The remaining five source
DIR32 fields have the authentic constants, but different offsets and
order; neither this rearrangement nor matching code length proves
original machine-code identity.

In the original, the advance calculation loads `2.0f` at `+0x10F`,
subtracts `1.0f` at `+0x117`, spills the advance *between* the
`strlen` push and call, then loads the unsigned-length correction at
`+0x14E`. The final SSE sequence multiplies the converted length by
the earlier advance using `xmm1` and subtracts the result from the
sprite's half-width. The new source instead loads sprite half-width
before `strlen` and calculates advance after it, so recovering the
original evaluation order **without losing the native 586B footprint**
is the next exactness problem. Attempts with a separately named
`std::size_t`/`uint32_t` length preserved the earlier order but
compiled to at least 594B; changing the half-width and width
intermediates increased code size or instruction count. The separate
5,993B Draw and 2,884B particle Update Bosses were also investigated
in the same continuation; experimental changes did not beat their
existing full-source baselines and were not adopted.

**`0x0044ADD0` remains SOURCE-PRESENT, NONEXACT.** There is no new
canonical unit or strict game-authored byte credit. Only this source
file changed; its exact 417B neighbor is a different source/owner unit,
with its existing **417/417** comparison preserved. No shared header,
previously exact native provider or replay input changed, so the
required affected canonical cold-replay scope is **zero units**.
The private compiler variants remain under ignored
`.analysis/gptweb-centered586-new/` and historical experiments under
`.analysis/gptweb-centered586-probes/`.

Reproduce the one-source codegen and independently inspect all its
code and relocation fields:

```sh
nice -n 15 scripts/compile-probe.sh \
  src/AnimationRendererCenteredText586.cpp \
  build/gptweb-probe/Centered586_mainline.obj \
  /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
scripts/repo-python .analysis/gptweb-centered586-new/score.py \
  build/gptweb-probe/Centered586_mainline.obj
scripts/repo-python scripts/compare-coff-function.py --unit animation_renderer_formatted_text_417
```

Next work: recover the original intermediate float lifetime/register allocation that preserves the actual length-conversion order, prove the nine relocation targets against the unchanged machine-code positions, and only then consider adding a 586B strict unit. Do not count the independent whole-exact 417B parent again.

## 2026-11-26: expression-order controls after the narrow ABI correction

The native arithmetic order is **advance, strlen, unsigned length to float,
product divided by four, sprite width divided by two, subtraction**. New
locked-compiler controls compare complete COFF contributions and call roles:

| Source context | Complete code / instructions | Result |
| --- | ---: | --- |
| Implicit strlen-to-float conversion | 586B / 140 | Identical code and relocations to the current explicit cast |
| Advance first in the product | 602B / 142 | Sprite half still evaluated before strlen; literal factors leave code unchanged |
| Negative span plus sprite half | 593B / 141 | Advance/strlen prefix restored, but adds a nonnative `xorps` and reverses multiplication registers |
| Negated span-minus-half difference | 593B / 141 | Retains a nonnative sign-mask operation |
| One named text-span local | 598B / 141 | Adds a span store and memory-source subtraction |
| Explicit unsigned correction, as in the ASCII method | 582B / 139 | Sprite half precedes the float conversion/product; multiply still folds the saved advance into a memory operand |
| Half of the width-minus-text difference | 586B / 140 | All 11 E8 positions align, but division by two follows subtraction instead of the native separate quarter-span and half-sprite operations |

The last formula is byte/relocation-identical under `/fp:precise` and
`/fp:fast`. Its size and aligned calls do not justify promoting a different
arithmetic sequence. The 582B variant likewise cannot be described as only
missing a four-byte reload: its evaluation order also differs.

Full-parent `/Ob2` helper trials grow to 718B/164 and 698B/161. Each still
has 11 E8 calls, but lock-guard construction/release becomes mutex lock/unlock,
and callback copy/destruction becomes `_Reset_copy`/`_Tidy`. These are changed
call roles. [MSVC's inline-option documentation](https://learn.microsoft.com/en-us/cpp/build/reference/ob-inline-function-expansion?view=msvc-170)
also identifies `/Ob0` as disabling expansion. Reduced half-width accessors
do not supply an alternative: ordinary and locally optimized helpers produce
identical 141B callers, retain early half evaluation and add a scalar copy
relative to the direct 131B control.

Native volatile-access metadata covers the complete method and marks only
the GS cookie accesses at `0x0044ADEE` and `0x0044B00C`. A bounded search for
the EBP-relative double-to-float conversion, XMM1 reload and register scalar
arithmetic finds only this method and the pending ASCII sibling, at
`0x0044AF2A` and `0x0044B17A`; both matches are decoded instruction heads.
This search supplies no accepted source exemplar for the missing lowering.

Private `centered-order-controls.txt` records complete sizes, compiler/object/
source/include hash checks, call-role comparisons, arithmetic events and metadata
under `.analysis/renderer-centered-session/`. The two closest failed forms'
instructions are in `centered-order-frontier-disassembly.txt`; sources and
receipts are retained there and in `build/gpt61-renderer-text-probe/`.
The maintained 586B source and profile remain unchanged. Exact replay scope
for this investigation is **zero**. Future candidates must preserve the
native arithmetic order before their byte or call-site scores are useful.

Reduced unsigned-length expressions also agree across C11, C++14 and C++20:
length-first and advance-first forms retain identical complete **121B** and
**131B** bodies and relocation records respectively. Both still evaluate
sprite half early. `unsigned-language-controls.txt` retains the comparisons
and object hashes; these results do not justify a full-parent language-mode
variant or a public-header compatibility change.
