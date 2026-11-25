# 5,993B Animation Draw Boss: mode35/36 spill, width-order and local-reuse experiments

**Status: focused source/compiler investigation; no production-source promotion.**
The maintained `src/AnimationDrawBoss.cpp` remains the reference candidate.
All probes below are ordinary C++ compiled as isolated i386 COFF with the
repository's pinned MSVC 19.44.35211 profile (`/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc`). No canonical object, target byte, match
manifest or source file is changed by these experiments.

## Baseline and width-before-half tradeoff

The maintained parent is 5,993 code bytes /1,502 decoded i386 instructions,
with **4,840/5,376** comparable ordinary bytes, **114/123** original physical
E8 positions, and **27/32** exact body HIGHLOW site/target pairs. A natural
mode35 source reorder was recompiled and re-ranked:

```cpp
const float shape_width = width + (height / native_two);
const float aux_half = height / native_two;
const float adjusted_scale =
    animation_inherited_aux_scale_x(animation) + aux_half;
```

This retains the full 5,993B contribution, 1,502 instruction heads, 123 E8
roles and the 27/32 data-site count. Its comparable ordinary-byte score rises
to **4,844/5,376** and the E8 position count remains **114/123**. However, the
second mode35 getter call moves from native `+0x1016` to `+0x102C`; the mode35
renderer call and following mode36 entry sites move by +8/+4 bytes, while the
mode36 final renderer call is four bytes early. The total absolute E8 offset
error rises from **44** to **62**. The four-byte raw score improvement is
therefore not a better reconstruction frontier and is not promoted.

A 16-way battery moved the same real width calculation before/after the first
getter, colors, count, half-height, second getter and adjusted-scale local,
with both named and inline adjusted-scale forms. All 4,844-byte variants share
the same worse call-site displacement pattern; the variants retaining the
native getter position return to 4,840/5,376. No placement improves the
maintained source's combined byte/call-site evidence.

## Function-scope first-return local

The original native x86 body writes the first mode35 and mode36 getter returns
to `[ebp-0x160]` at `+0x0FCD` and `+0x10BA`; a complete decoded-body operand
scan finds no subsequent read of that slot. A natural function-scope
`[[maybe_unused]] float first_inherited_scale`, assigned by each first getter,
reproduces both x87 memory stores. When combined with value-equivalent
half-height role reuse, it also recovers both adjusted-scale register-register
forms (`addss xmm0,xmm1` and `subss xmm0,xmm1`).

The best such scalar probe is **5,989B**, **3,801/5,372** ordinary bytes and
**89/123** E8 positions. Its first 88 E8 positions match, but every physical
E8 from the mode36 renderer call at native `+0x1198` onward is four bytes
early. The probe reuses the pre-getter half-height local for the width
argument; native mode36 recomputes `height / 2` after adjusted-scale. Replacing
the reused value with a post-getter width calculation removes the register
operand form when the adjusted-scale calculation consumes the saved half.
The source battery also tried keeping all current locals while adding the
first-return local, declaring it after position setup and after scale setup,
and reusing the width temporary. These either shift later locals/calls,
materialize extra stack loads, or lose the original function extent/call
census. No first-return probe is promoted.

## Other rejected source forms and compiler profiles

- The exact native mode45 half-height ownership (scale half before the getter,
  width half recomputed after it) compiled to **5,989B /109/123 E8** and
  **4,694/5,372** ordinary bytes. Its adjusted-scale addition remains a
  memory-source `addss`, not the native register-register form.
- The same mode45 native-order form was tried with const/mutable/assigned
  locals, reverse addition, comma expression, case-top predeclarations and
  inline width recomputation. None restored the current source's call-site
  census or ordinary-byte score.
- `__forceinline` scalar add/subtract wrappers under `/Ob0` were not inlined;
  they changed the call graph and contribution extent and are rejected.
- `/Od /Ob1`, `/Od /Ob2`, `/Od /Oi`, `/Od /Ob1 /Oi` and `/Od /Oy-` produced
  the same maintained 4,840/5,376, 114/123 candidate. `/O1`, `/O2` and `/Ox`
  changed the whole function's contribution substantially and did not retain
  the native E8 graph.
- A `shape_width` local initialized from the first getter and then reused for
  the width argument made the compiler read `[ebp-0x160]`, unlike the native
  write-only spill, and lost the parent call census. This is not the native
  lifetime.
- Keeping the current mode35/36 locals and adding a function-scope first
  result store without simplifying those locals produced **6,001B /84/123
  E8**; declaring the same local after position setup or scale setup produced
  the same result. The first-return local alone therefore does not explain the
  native frame/call layout.
- Reusing a real `shape_width` local for the first getter result and then
  overwriting it with the width argument did not help: the compiler emitted a
  later read of `[ebp-0x160]`, while the original has no read of that slot, and
  the candidate lost the complete function boundary/call census.
- `__forceinline` scalar add/subtract helpers were not inlined under `/Ob0`.
  Adding `__vectorcall` and trying `/Ob1` changed the COFF contribution to
  6,017B/84 E8 positions or removed the expected function boundary; neither
  emitted the original XMM1 load. These helper/ABI routes are rejected.

The next useful avenue remains a natural C++ local/temporary lifetime that
simultaneously accounts for the write-only first-result spill, keeps the
pre-getter half alive in XMM1 across the recursive getter, recomputes width's
half at the original post-getter point, and preserves the 5,993B/123-E8/32-
HIGHLOW parent. The maintained source is unchanged; parent exact credit
remains zero.

## 2026-11-25 follow-up: direct arguments, mixed ownership and exact call displacement

The full Ghidra decompilation of `0x00443880` was refreshed. It confirms the
mode35/36 expression order already stated above: `fVar9 = height / 2` is
computed before the second getter; the adjusted scale consumes that saved
value; the width half is a distinct calculation after adjusted scale, in the
renderer argument sequence. The original PE verifier now pins both complete
width arithmetic windows as well as the two getter/store and register-register
adjusted-scale windows:

- Mode35 width at `+0x1068`: `movss xmm0,[height]`, `divss xmm0,[native_two]`,
  `addss xmm0,[width]`.
- Mode36 width at `+0x171c`: the same height division, then
  `movss xmm1,[width]` and `subss xmm1,xmm0`.

The source-role verifier now independently checks that the maintained C++
mode35/36 blocks preserve first getter, color getter, pre-getter scale half,
second getter, adjusted scale, and post-adjustment width calculation in that
order. Both focused verifiers pass; this adds semantic protection, not parent
exactness credit.

A fresh matrix combined the two half-height ownership choices independently
in modes35 and 36, and then crossed them with native-order mode45. It also
tried putting both expressions directly in the renderer call, letting MSVC
choose argument evaluation order. The measured results are:

| Candidate | Code | Ordinary bytes | E8 sites | Sum absolute E8 displacement | Exact HIGHLOW sites |
| --- | ---: | ---: | ---: | ---: | ---: |
| Maintained source | 5,993B | 4,840/5,376 | 114/123 | 44B | 27/32 |
| Mode35 width-before-half | 5,993B | 4,844/5,376 | 114/123 | 62B | 27/32 |
| First-result spill + both role swaps | 5,989B | 3,801/5,372 | 89/123 | 140B | 24/32 |
| First-result spill + native half ownership in both modes | 5,985B | 3,726/5,368 | 84/123 | 296B | 23/32 |
| First-result spill + mode35 role swap / mode36 native order | 5,989B | 3,800/5,372 | 89/123 | 140B | 24/32 |
| First-result spill + mode35 native order / mode36 role swap | 5,985B | 3,725/5,368 | 84/123 | 296B | 23/32 |
| Direct renderer arguments in both modes | 6,017B | 3,675/5,400 | 83/123 | 928B | 23/32 |
| Spill + both native half modes + native mode45 | 6,013B | 3,735/5,396 | 84/123 | 360B | 23/32 |
| Spill + mode35 role swap / mode36 native + native mode45 | 6,017B | 3,800/5,400 | 89/123 | 252B | 24/32 |

The displacement sum is the sum of absolute byte differences for all 123
physical E8 instruction offsets; it is useful alongside the simple count
because two candidates can both match 114/123 positions while moving the
remaining sites by different distances. The four-byte ordinary-byte increase
from the mode35 width-before-half probe is not a genuine convergence: its
absolute E8 displacement rises from 44B to 62B, while the mismatch count stays
at nine. The direct-call experiment is substantially worse because the
compiler's argument evaluation order moves the second getter and both nested
case tails.

No source variant improves the maintained parent's combined evidence. The
production source, canonical objects and exactness registry remain unchanged.

## 2026-11-25 follow-up: candidate-only disassembly audit

Added `scripts/report-animation-draw-boss-candidate.py` to decode the native PE
and each candidate COFF body independently. It reports the full contribution
score, actual decoded E8 offsets and total absolute E8 displacement, in-body
HIGHLOW-site overlap, and mode35/36 spill/arithmetic forms taken **only from
the candidate instruction list**. This avoids a recurring false positive in
plain `grep` over `dump-draw-boss-object-windows.py`, whose output contains both
`-- NATIVE --` and `-- CANDIDATE --` sections.

The candidate-only audit confirms the exact tradeoff:

| Candidate | Code / x86 | Ordinary bytes | E8 | Abs. E8 displacement | HIGHLOW sites | First spill | Adjusted-scale register forms |
| --- | ---: | ---: | ---: | ---: | ---: | ---: | --- |
| Maintained source | 5,993B / 1,502 | 4,840/5,376 | 114/123 | 44 | 27/32 | 0 | 0/2 |
| Width-before-half | 5,993B / 1,502 | 4,844/5,376 | 114/123 | 62 | 27/32 | 0 | 0/2 |
| `current_spill_direct` | 5,989B / 1,501 | 3,801/5,372 | 89/123 | 140 | 24/32 | 2/2 | 2/2 |
| `current_spill_native3536` | 5,985B / 1,500 | 3,726/5,368 | 84/123 | 296 | 23/32 | 2/2 | 0/2 |
| `named_inline_width` | 5,985B / 1,500 | 3,726/5,368 | 84/123 | 296 | 23/32 | 2/2 | 0/2 |
| `register_half_spill` | 6,001B / 1,502 | 3,753/5,384 | 84/123 | 328 | 23/32 | 0/2 at native slot | 0/2 |
| `shared_half_spill` | 5,965B / 1,497 | 1,871/5,356 | 45/123 | 1,442 | 14/32 | 0/2 at native slot | 0/2 |
| `stdplus` | 6,009B / 1,512 | 1,217/5,384 | 28/123 | 4,238 | 14/32 | 1/2 | 0/2 |

`current_spill_direct` really does emit the two candidate-side stores to
`[ebp-0x160]` and the two candidate-side register-register operations: mode35
`addss xmm0,xmm1` at `+0x1036`, mode36 `subss xmm0,xmm1` at `+0x1123`. It is
not native-order source, however: it computes the half used for width before
the second getter, and computes the half used for adjusted-scale after that
getter. The native does the opposite ownership. This is why the candidate
matches its first 88 E8 sites but loses the native mode36 renderer position
and has only 89/123 E8 sites overall.

`current_spill_native3536` is the converse. It preserves the native source
order (scale half before getter, width half after adjusted scale) and emits
both first-result stores, but the candidate-side adjusted-scale operations
are memory-source `addss xmm0,[half]` / `subss xmm0,[half]`. Its mode36 first
spill is four bytes early (`+0x10B6`, not native `+0x10BA`), and its body is
eight bytes short. Thus the native-order and register-register requirements
remain mutually unresolved under the tested natural scalar C++ forms.

The `register` storage-class experiment emitted MSVC warning C5033 and did
not alter candidate operand selection; its function-scope spill moved to
`[ebp-0x164]`, not the native `[ebp-0x160]`. `volatile` locals likewise kept
memory operands and were not promoted. Predeclaring the half/inherited/adjusted
locals in all three orders produced the same 5,985B/84-E8 result. A shared
half local used for both adjusted scale and width collapsed the contribution
to 5,965B/45 E8. `std::plus<float>`/`std::minus<float>` emitted extra out-of-line
calls (125 candidate E8) and collapsed alignment to 28/123. `/O1` and `/O2`
probes did not retain the native complete function boundary/call graph.

The candidate-only report is now the required check for future spill/register
experiments. No candidate is promoted; the production C++ and canonical
objects remain unchanged.
