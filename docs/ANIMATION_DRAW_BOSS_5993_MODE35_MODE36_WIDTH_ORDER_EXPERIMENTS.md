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

## Additional operand-materialization probes after the candidate-only audit

A final scalar-expression battery tried case-top predeclaration permutations
for `aux_half`, `inherited_scale` and `adjusted_scale`; all three declaration
orders produced the same **5,985B / 84/123 E8** native-order spill candidate
with memory-source adjusted-scale arithmetic. The obsolete C++ `register`
storage-class keyword emitted MSVC C5033, did not force a register load, and
moved the first-result temporary to `[ebp-0x164]` instead of the native
`[ebp-0x160]`. `volatile` scalar locals likewise did not force XMM1 and are
not accepted as a source explanation.

Using one shared half-height local for both adjusted-scale and width changed
the parent to **5,965B / 45/123 E8**, **1,871/5,356** ordinary bytes and
14/32 exact HIGHLOW sites. `std::plus<float>` / `std::minus<float>` functors
were emitted as out-of-line helper calls: the object had 125 E8 instructions,
only 28/123 native physical positions, and a 6,009B function. Bit-cast and
`memcpy` round-trips around the half-height introduced extra temporaries and
out-of-line helper code: the bit-cast candidate grew to 6,069B with 28/123
E8, while the memcpy variant did not retain a recognizable complete function
boundary and had 34/123 E8. These are rejected, not compiler-shaping progress.

`/O1` and `/O2` applied to both the direct-role-swap and native-order spill
sources also destroyed the 5,993B boundary and call graph (O1 had no matching
return boundary; O2 reduced the body to roughly 4.2KB). The maintained profile
remains `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc`.


## 2026-11-25 follow-up: restore native mode45/46 source order

The previously maintained mode45 role swap was value-equivalent for ordinary
finite floats but did not preserve the original evaluation order. It computed
`height / 2` for width before the inherited-scale getter and recomputed the
scale half after the getter. The native PE does the reverse. The production
source has now been corrected to compute `half_for_scale` before the getter,
use it for adjusted scale, and independently recompute the width half after
adjusted scale. Mode46 already used that original order and remains unchanged.

The focused source-role compile now measures **5,989B / 1,501 x86**,
**4,694/5,372** ordinary bytes, **109/123** E8 positions, **68B** total
absolute E8 displacement and **26/32** exact HIGHLOW sites. This is below the
former mode45 role-swap candidate (4,840/5,376; 114/123; 44B; 27/32), but
faithful C++ evaluation order takes precedence over a value-equivalent
compiler-shaping reorder. No padding or synthetic instruction was added.

The native verifier now pins these distinct mode-specific windows:

| Mode | Adjusted-scale | Width calculation |
| --- | --- | --- |
| 35 | `+0x1016`: x87 return then `addss xmm0,xmm1` | `+0x1068`: `height / 2`, then width add |
| 36 | `+0x1103`: x87 return then `subss xmm0,xmm1` | `+0x1155`: width in XMM1 then `subss xmm1,xmm0` |
| 45 | `+0x15DD`: x87 return then `addss xmm0,xmm1` | `+0x163D`: `height / 2`, then width add |
| 46 | `+0x16BC`: x87 return then `subss xmm0,xmm1` | `+0x171C`: width in XMM1 then `subss xmm1,xmm0` |

The old verifier called `+0x171C` `mode36_width`; that was a naming bug.
Mode36 width is at `+0x1155`, and `+0x171C` is mode46. Both native and
source-role focused verifiers now pass with all four modes pinned.

The candidate-only report now uses the actual `ret 4` instruction to locate
the candidate code boundary, caps ordinary-byte scoring at the 6,316B native
COFF contribution, and reports adjusted-scale and width arithmetic for all
four modes separately. This also makes longer intrinsic experiments
measurable without accidentally counting adjacent PE bytes as part of the
original function.

A mode46 role-swap probe did obtain a register-register subtraction, but it
reversed the destination (`subss xmm1,xmm0` at `+0x16DC`) and moved the width
half before the getter. Its candidate was **5,989B**, **4,786/5,372**
ordinary bytes, **113/123** E8, **48B** total displacement and **27/32**
HIGHLOW sites. The native-order `subss xmm0,xmm1` was not recovered. A
mode46 dual-half predeclaration candidate was 6,005B/112 E8; direct-return
was 5,992B/109 E8. Adding `+0`, multiplying/dividing the half by one, adding
a negative half, or negating the reverse subtraction all stayed at 109 E8
or worse and did not produce the native register operand order. These probes
are rejected; the source-accurate mode46 expression remains maintained.

### Mode45 native-order expression battery

With the production source already using the original mode45 order, five
additional C++ variants were compiled from the same parent:

| Variant | Code | Ordinary bytes | E8 | Abs. E8 displacement | HIGHLOW sites |
| --- | ---: | ---: | ---: | ---: | ---: |
| Maintained inline getter + half local | 5,989B | 4,694/5,372 | 109/123 | 68 | 26/32 |
| Named getter, reverse `half + inherited` | 5,989B | 4,693/5,372 | 109/123 | 68 | 26/32 |
| Named getter, forward `inherited + half` | 5,989B | 4,694/5,372 | 109/123 | 68 | 26/32 |
| Mutable compound add, either operand order | 5,999B | 1,994/5,380 | 45/123 | 474 | 14/32 |
| Width temporary declared after adjusted scale | 6,005B | 4,690/5,388 | 109/123 | 108 | 26/32 |

Naming the getter result and reversing the addition changed at most one ordinary
byte and did not recover a register-register ADDSS or any physical E8 site.
Mutable compound assignments collapsed the parent call/table layout. A named
width temporary after adjusted scale added 16 bytes and increased total E8
displacement by 40B. The maintained natural expression remains the best
native-order mode45 candidate; the older 114/123 role swap is not restored.

### Mode46 native-order versus role-swap subtraction

The candidate-only report now distinguishes the mode46 adjusted-scale window
from its width window and reports both register subtraction directions. The
maintained mode46 path still uses a memory-source `subss` for adjusted scale.
A role swap (width half before getter, scale half recomputed after) produces a
register-register `subss xmm1,xmm0` at `+0x16DC`, but this is the reverse
register destination from native `subss xmm0,xmm1` and moves the physical E8
census to 113/123. It scores 5,989B, 4,786/5,372 ordinary bytes, 48B total E8
displacement and 27/32 HIGHLOW sites; it is rejected. The native-order
mode46 dual-half predeclaration candidate is 6,005B/113 E8; direct-return is
5,992B/109 E8. The `+0`, `*1`, `/1`, negative-half and negated-reverse scalar
expression forms are 5,996–6,001B with 109 E8 and no native-order register
subtraction. Keep the original source order.

## Additional first-return stack-slot lifetime probes

After restoring native mode45 order, the first mode35/36 getter spill was
retested with three source scopes: a function-scope `first_inherited_scale`,
a case-local `[[maybe_unused]]` const/mutable/volatile scalar, and a set of
four function-scope shared temporaries (`first_inherited_scale`, `aux_half`,
`inherited_scale`, `adjusted_scale`) in all declaration orders. The single
function-scope or case-local first-result scalar lands at `[ebp-0x164]`, not
the native `[ebp-0x160]`, and the candidate becomes **5,997B / 85/123 E8**,
**3,855–3,863/5,380** ordinary bytes and 24/32 HIGHLOW sites. Const, mutable
and volatile case-local forms are identical.

Hoisting all four values to function scope does place both first getter stores
at `[ebp-0x160]`, but every declaration order produces the same **5,963B /
44/123 E8**, **1,669/5,344** ordinary bytes and 14/32 HIGHLOW result. Placing
the same four shared temporaries at the nested-switch scope instead yields
**5,979B / 44/123 E8**, **1,689/5,360** ordinary bytes and 14/32 HIGHLOW; it
does not recover the native first-result slot. These broad-scope local sets
change switch/table code generation too severely and are rejected.

No function-scope, case-scope, or nested-switch-scope scalar lifetime
reproduced both native first-return spills while retaining the original 123-E8
parent graph. The production source remains the native-order 5,989B candidate.


## 2026-11-25 follow-up: isolated mode45 SSE-load intrinsics rejected

After promoting the native mode45 evaluation order, an isolated mode45-only
battery attempted to make the saved scale half explicitly resident in XMM1
using _mm_load_ss and _mm_set_ss around the two scalar locals. The candidates
were compiled under the same pinned /Od /Ob0 profile and scored with the
candidate-only decoder:

| Variant | Code | Ordinary bytes | E8 | Exact HIGHLOW sites | Candidate mode45 scale |
| --- | ---: | ---: | ---: | ---: | --- |
| Native-order scalar C++ | 5,989B | 4,694/5,372 | 109/123 | 26/32 | memory-source addss |
| `_mm_load_ss` both scalar locals (`mode45_sse_load_intrinsic`) | 6,084B | 164/5,464 | 0/123 | 0/32 | no complete native call graph |
| `_mm_set_ss` both scalar lanes (`mode45_sse_inline_intrinsic`) | 6,084B | 259/5,464 | 0/123 | 0/32 | no complete native call graph |
| `_mm_load_ss` both lanes (`mode45_sse_intrinsic`) | 6,112B | 169/5,492 | 0/123 | 0/32 | no complete native call graph |

The vector intrinsic expressions materialize extra scalar/vector temporaries
and disrupt the switch contribution; they do not merely replace the native
memory-source addss with movss xmm1 plus register-register addss. These probes
are rejected and remain outside production source. The natural scalar C++
mode45 correction is retained.

The four small draw-access children were also cold-rebuilt as one affected
source only after their include closure changed. Strict canonical replay
passed 4/4: animation_draw_color_490_20 (20B), animation_draw_color_494_20
(20B), animation_draw_enabled_26 (26B), and animation_draw_inherited_aux_scale_93
(93B). This confirms the big parent's getter/color callees remain independently
exact; it does not grant exactness to the 5,993B parent.


## 2026-11-25 follow-up: scoped/aggregate first-result and argument-lifetime probes

A second, current-source-derived battery tried to make the native mode35/36
write-only first getter result a real C++ temporary without hoisting all
locals. Each mode was tested with a nested-scope value, const lvalue
reference, const rvalue reference, volatile value, one-field aggregate and
one-element array. Each was paired with either the current mode35 width local
or the inline width expression.

None preserved the parent call graph. The nested-scope variants with the
current width local ranged from 5,981B to 5,999B and retained only 84/123 E8
positions; the inline-width variants likewise remained at 84/123 or worse.
The one candidate reporting an fstp to [ebp-0x160] did so for a later mode36
getter, not for the first mode35/36 return. The candidate-only disassembly
therefore does not count it as recovery of the two original first-return
stores.

A structured-local battery grouped the actual mode35/mode36 temporary values
into structs in native stack order and reverse order. Full mode structs,
compact two-float first-result/adjusted-scale pairs, and the paired mode35+36
forms all changed switch layout substantially: 84–86/123 E8 positions,
23–24/32 HIGHLOW sites, and 3,713–3,829 ordinary bytes. No candidate emitted
the required first-result spill at the native call site or either native
register-register adjusted-scale operation. These aggregate representations
are rejected as compiler-layout shaping, not promoted C++ reconstruction.

A further attempt reused an actual renderer argument local for the first
getter return, then overwrote it with the final width/adjusted-scale value.
Mode35 width reuse and adjusted-scale reuse both collapsed the candidate to
45/123 E8; adding the same reuse to mode36 was worse. Declaring a real width
local and assigning it inside the renderer argument expression was also
tested in three declaration positions; all three compiled identically to the
maintained 5,989B/109-E8 candidate (4,691/5,372 ordinary bytes), with no
native spill or SSE register form. These source forms did not improve on the
current production expression.

The current parent remains 5,989B/1,501 instructions, 109/123 E8 positions,
68B total absolute E8 displacement and 26/32 exact HIGHLOW site/target pairs.
No local, struct, array, reference, volatile qualifier, opcode or padding is
added to production source. The first-result x87 slot and register-operand
frontier remain open.


## 2026-11-25 follow-up: recover the two script anchor-word roles

The two raw Animation flags at offsets +0x10/+0x14 are now named by their
actual uses: horizontal and vertical 0..2 corner-anchor indices. The native
mode28 parent sequence loads Animation+0x4AC first (vertical), then +0x4A8
(horizontal), and pushes them in cdecl reverse-argument order for the
1,601B triangle child at +0x0D73. The child signature already names its final
parameters horizontal_anchor and vertical_anchor; the mode6/mode7 setup
children use the same indices to select X/Y corner arrays, mode8 forms the
3x3 corner index as vertical*3+horizontal, and the animation update opcode
0x5D writes the two consecutive 16-bit operands into those slots.

The semantic names are layout-preserving union aliases in Animation.hpp;
the original word_10/word_14 names remain available to raw-layout consumers.
The five anchor-specific exact leaf units were cold-replayed and remain
byte-exact: 985/985, 1,486/1,486, 1,378/1,378, 1,996/1,996 and 4,347/4,347
coverage bytes (4,372/4,372 compared bytes). The complete affected
include-closure batch replayed 33/33 exact units across 11 source objects,
including seven AnimationBinding units, nine AnimationCallback units, four
DrawAccess leaves and the 5,388B AnimationGeometry boss. The 39,470B update
source and both laser initialization sources compile with the semantic field
names. A typed __forceinline reference accessor was tested and rejected
because the strict 1,378B mode6 setup replay grew to a 1,399B COFF contribution;
direct union aliases preserve the exact native codegen. The large 5,993B Draw
Boss parent retains its same 5,989B/1,501-instruction, 109/123-E8 NONEXACT
profile.


## 2026-11-25 follow-up: shared first-result local after common setup

A new placement battery moved one shared float first-result local out of the
function entry and into the enclosing 16..46 renderer block, after the common
position/angle/width/height and texture/scale setup but before the nested mode
switch. Both mode35 and mode36 assign their first inherited-scale getter to
this same source local. Under the locked compiler this is the first natural
source placement that emits both candidate-side fstp stores to the native
[ebp-0x160] slot:

| Mode | Candidate store | Native store | Result |
| --- | ---: | ---: | --- |
| 35 | +0x0FCD | +0x0FCD | exact site |
| 36 | +0x10B6 | +0x10BA | 4B early |

The full candidate is nevertheless only 5,981B/1,499 instructions,
3,726/5,364 ordinary bytes, 84/123 E8 positions, 320B total absolute E8
displacement and 23/32 exact HIGHLOW sites. It uses the inline mode35 width
expression; restoring the separate mode35 width local moves the shared
first-result value away from [ebp-0x160] and returns the candidate to 85/123
E8. Declaring width and first-result locals at function scope in either order
also produces the same 85/123 result. This confirms the native write-only
spill can be represented by an actual shared C++ local at the correct stack
slot, but the remaining nested-case lifetime/call layout is substantially
worse. The probe is rejected; production source remains unchanged.
