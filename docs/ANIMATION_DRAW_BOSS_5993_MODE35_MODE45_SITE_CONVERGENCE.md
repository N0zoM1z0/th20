# CORE/RECON-1112 — 5,993B Animation Draw Boss: nested-mode source convergence

> Current source update (2026-11-25): the historical mode45 role swap
> described below has been removed. Production C++ now follows the native
> pre-getter scale-half / post-adjustment width-half order. The current
> candidate is 5,989B/1,501 instructions, 4,694/5,372 ordinary bytes,
> 109/123 E8 positions, 68B total absolute E8 displacement and 26/32 exact
> HIGHLOW site/target pairs. See the final correction entry at the end of this
> report; earlier mode45 role-swap metrics are historical only.

**Current status: SOURCE-PRESENT, NONEXACT.** The immutable Japanese TH20
Steamless v1.00a PE (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
has one complete game-authored `AnimationPoolOwner::draw(Animation*)` at
`0x00443880`: **5,993B /1,501 i386 instructions**, native `0x204`
stack frame, **123 physical E8 instructions** and **32 original in-body
PE HIGHLOW** fields. After its real return and 3B alignment, **49 direct
main-mode and 31 nested-mode original jump pointers** complete the
**6,316B original code+table contribution**. The whole native and
backend ABI evidence remains in the independent original-only
[`verify-animation-draw-boss-native.py`](../scripts/verify-animation-draw-boss-native.py)
and [`verify-animation-draw-boss-abi.py`](../scripts/verify-animation-draw-boss-abi.py).

The prior source snapshot, before the 2026-11-25 mode45 correction, compiled to
5,993B/1,502 candidate i386 instructions with a 0x204 frame and 6,316B
code+table contribution. That snapshot used a value-equivalent mode45 role
swap: its pre-getter half fed width and its post-getter half fed adjusted
scale. Native mode45 instead uses the pre-getter half for adjusted scale and
recomputes the width half after the getter. The swap retained the native
register-register addss and renderer call position, but moved the second
native_two relocation away from the native width site. The current source no
longer uses that swap; it follows the original mode45 evaluation order and
compiles to the 5,989B candidate summarized at the top of this report.


Mode35/36 now name the second inherited-scale getter result as
`inherited_scale` before computing the real adjusted-scale argument. The first
getter remains a distinct discarded call because the original stores its x87
return to `[ebp-0x160]` without a later read; the source does not invent a
compiler-only local to mimic that dead spill. This improves the source-level
ownership description without changing the current 5,989B candidate or its
4,694/5,372 ordinary-byte score.

The nested dispatcher now uses mode-specific aliases for the shared ANM
variable slots: modes37/38 read `rounded_shape_radius`, while modes39-41 read
`ring_center_radius` and `ring_thickness`. The renderer children independently
confirm these roles through their original `radius`, `size_x/size_y`, and
`thickness` parameters. The aliases preserve the original 64B `AnmVariables`
layout and the original offsets +0x10/+0x14; four direct consumer translation
units compile with the unchanged ABI. The Boss-local semantic-debt scan now
reports zero anonymous identifiers. This naming work does not claim additional
machine-code exactness.

The maintained function changes remain ordinary C++ source; no binary bytes,
manual opcodes, or padding are introduced. The parent-angle flag test now uses
`((word_04 >> 12) & 1u) == 0`, reproducing the original `shr edx, 0xc; and edx, 1`
sequence at function offset `0x3E8` byte-for-byte. The prior mask expression
compiled to a six-byte `and edx, 0x1000`; the corrected expression adds one
instruction head but preserves the 5,993B code extent and raises ordinary-byte
agreement from 4,834 to 4,840. The value-preserving source changes
preserve all 123 original E8 target roles and the actual renderer argument
values. Modes37/38 now name the shared `+0x10` float as
`rounded_shape_radius`; modes39/40/41 name the same slot `ring_center_radius`
and the `+0x14` slot `ring_thickness`. The rounded renderers take an explicit
`radius` parameter, while the ring renderer computes `radius +/- thickness/2`.
These are mode-specific aliases, not universal renames of the shared ANM slots.
The `AnmVariables` size and offsets remain unchanged, and the redundant
`field_570` assertion was removed in favor of the existing `retirement_state`
assertion. The parent-only semantic-debt scan now returns zero lexical
candidates; this is a scope-limited heuristic result, not semantic completion
or exactness credit. Mode45's half-height operand ownership remains value-equivalent but reversed
relative to the native division sites. Mode46 has been returned to
native evaluation order; the locked compiler still chooses a shorter
direct-memory adjusted-scale subtraction:

1. **Mode 35 actual width argument:** A `const float shape_width`
   now owns the genuine `width + (height / native_two)` value used for
   the eventual `draw_shape_43c780` call. Previously that used expression
   was evaluated inline during the call. Original machine instructions
   establish the first scale getter, original secondary/primary packed
   colors, draw count, second scale getter, and two distinct height-halving
   operations. The new used C++ width local alters `/Od` evaluation and
   stack-space lifetime without adding an unused register-shaping value.
2. **Mode 45/46 actual argument values and lifetimes:** Both packed-color
   getters and the real draw count are saved before the renderer call. Mode45
   retains the pre-getter half for width and recomputes an equivalent half for
   adjusted scale; native mode45 uses the pre-getter half for adjusted scale
   and recomputes the width half after the getter. The value-equivalent source
   role swap keeps register-register `addss` and E8 call positions, but moves
   the second absolute `native_two` relocation. Mode46 now retains its
   pre-getter half for adjusted scale and recomputes the width half after the
   getter, matching native source order. MSVC emits a direct-memory
   adjusted-scale `subss` that is four bytes shorter than native.
   There is no invented helper or change to the renderer receiver ABI.

## Historical rejected mode45/46 role-swap candidate (not maintained source)

The pinned MSVC 19.44 i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` compiled this historical value-equivalent
mode45/46 role-swap probe to **5,993B/1,502 instructions** (the original is
1,501), retaining the `0x204` frame and full **6,316B COFF contribution**.
Its 3B alignment and 80 compiler-generated DIR32 case pointers were real,
but its source half-height roles were reversed and the candidate was rejected.

| Historical probe metric | Older source snapshot | Rejected role-swap probe | Original |
| --- | ---: | ---: | ---: |
| Executable code bytes | 5,993 | **5,993** | 5,993 |
| Original-code instruction heads | 1,501 | **1,502** | 1,501 |
| After-`ret` contribution (alignment/tables) | 323B | **323B** | 323B |
| Original E8 role targets and their order | 123/123 | **123/123** | 123/123 |
| Original E8 *physical instruction offsets* | 86/123 | **114/123** | 123/123 |
| Absolute E8 opcode offset-delta sum | 516 | **44** | 0 |
| Original in-body HIGHLOW target-role histogram | 32/32 | **32/32** | 32/32 |
| Original in-body HIGHLOW site+role positions | 23/32 | **27/32** | 32/32 |
| All complete ordinary bytes with actual COFF fields masked | 3,819/5,376 | **4,840/5,376** | 5,376/5,376 |

The ordinary byte denominator masks exactly **the compiler's actual
235 four-byte relocation fields** (123 E8 +32 in-body data +80 table
entries); original bytes are not patched or recompiled. The physical E8
callee roles come independently from the immutable PE, not from matching
object offsets or fabricated target data. The current nonrelocation agreement is **1,021 bytes** above the older
3,819-byte checkpoint. The prior 4,835-byte score described a historical
value-equivalent mode46 probe, not the maintained source. E8 position agreement remains **114/123** and data site/target agreement
remains **27/32** through this mode46 source correction, preserving the native
code size and both 49+31 switch-pointer alias partitions.

The historical role-swap probe was measured at 114/123 E8 positions, 27/32
body HIGHLOW site/target pairs and 4,840/5,376 ordinary bytes. The maintained
source-role verifier now checks the current **109/123**, **26/32** and
**4,694/5,372** baseline instead; it still requires all 123 call targets in
original order, the complete 80-pointer table partitions, all 49 game modes
and the source/ABI roles of the 18 real rendering children.

## Historical residual summary before the mode45 correction (superseded)

This nine-call summary described the rejected role-swapped probe. It is
superseded by the 14-call maintained-source map in the final 2026-11-25
follow-up below. The mode45 half-role reversal described here is not present
in production source.

A separate mode35/36 switch-scope local probe now reproduces both native
`fstp [ebp-0x160]` stores with the correct `0x204` frame and adjusted-scale
stack slots. It is **not promoted**: the full body falls to 5,985B/1,499
instructions, only 84/123 E8 positions and 23/32 data sites align, and
ordinary-byte agreement falls to 3,710/5,368. A case-local unused scalar
instead grows the frame to `0x208` and spills at `[ebp-0x208]`. SSE intrinsic
`_mm_store_ss` probes materialize 16-byte temporaries and grow the body beyond
6,100B.

The native Ghidra pseudocode confirms that the first mode35 (`0x23`) and
mode36 (`0x24`) inherited-scale getter calls are standalone expression
statements; the second getter result is the one assigned to the scale used by
the renderer. Thus the native first-return store has no decompiler-visible
consumer, despite the real `fstp [ebp-0x160]` at both call sites. A natural
`float first_scale_result` local assigned in both cases reproduces those two
stores and keeps the `0x204` frame, but loses whole-function convergence as
measured above. A second probe combines that local with the half-height role
swap: it recovers register-register `addss`/`subss` and both first-return
stores, but is still only 5,989B/1,500 instructions with 89/123 E8 positions;
the mode36 renderer remains four bytes early. Neither probe is promoted. The
maintained source therefore keeps the first getter expression as a discarded
call until a natural source lifetime reproduces the native spill without
sacrificing whole-function convergence.

Reproduce the full, **noncanonical** comparison without all-source
cold replay:

```sh
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/verify-animation-draw-boss-abi.py
scripts/repo-python scripts/verify-animation-draw-boss-native.py
```

The Draw Boss parent still has no canonical match-unit and remains
**NONEXACT**. The separate 244B corner projection dispatcher is now a strict
exact unit; it does not grant byte credit to this parent. See the previous dated
[5,993B frame/table frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md)
and [mode35 x87 spill experiments](ANIMATION_DRAW_BOSS_5993_MODE35_X87_PROBES.md)
for the original baseline and rejected variants.


## 2026-11-25 correction: native mode45 evaluation order is now maintained

The previous mode45 role swap was a compiler-layout optimization that did not
preserve the original evaluation order. It computed the width half before the
recursive getter and recomputed the scale half after it. The native PE computes
the scale half first, uses it after the getter, then recomputes the width half
in the renderer arguments. Production src/AnimationDrawBoss.cpp now follows
that original order. The mode45/46 source-role verifier asserts the sequence,
and the original-only native verifier pins both scale and width instruction
windows for modes35, 36, 45 and 46.

The corrected whole-parent candidate is 5,989B/1,501 i386 instructions,
4,694/5,372 ordinary bytes, 109/123 E8 positions, 68B summed
absolute E8 displacement and 26/32 exact HIGHLOW site/target pairs. This
regresses the previous role-swap byte/call metrics but removes the source
semantic mismatch. The remaining mode45 compiler difference is its
memory-source addss; the native reloads the saved half into XMM1 before
register-register addss. Mode46 has the analogous memory-source subtraction.
No opcode or padding was introduced.

## 2026-11-25 fresh maintained-source residual map

A new source-derived compile of the maintained `src/AnimationDrawBoss.cpp`
with the locked MSVC x86 profile reconfirms **5,989B / 1,501 instructions**,
**109/123** E8 positions, **68B** summed absolute E8 displacement,
**26/32** body HIGHLOW site/target pairs and **4,694/5,372** ordinary bytes.
All 123 REL32 call symbols remain in the exact original target order. The
14 physical call-position differences are:

| Native offset | Maintained offset | Native target | Area |
| ---: | ---: | ---: | --- |
| `+0x0FD6` | `+0x0FD2` | `0x004456C0` | mode35 color494 |
| `+0x0FE4` | `+0x0FE0` | `0x004456E0` | mode35 color490 |
| `+0x1016` | `+0x1012` | `0x00445880` | mode35 second inherited-scale getter |
| `+0x10A7` | `+0x10AF` | `0x0043C780` | mode35 renderer |
| `+0x10B5` | `+0x10BD` | `0x00445880` | mode36 first inherited-scale getter |
| `+0x10C3` | `+0x10C7` | `0x004456C0` | mode36 color494 |
| `+0x10D1` | `+0x10D5` | `0x004456E0` | mode36 color490 |
| `+0x1103` | `+0x1107` | `0x00445880` | mode36 second inherited-scale getter |
| `+0x166E` | `+0x166A` | `0x0043DF30` | mode45/46 renderer branch |
| `+0x167C` | `+0x1678` | `0x004456C0` | mode45/46 color494 |
| `+0x168A` | `+0x1686` | `0x004456E0` | mode45/46 color490 |
| `+0x16BC` | `+0x16B8` | `0x00445880` | mode45/46 inherited-scale getter |
| `+0x1751` | `+0x1749` | `0x0043DF30` | final renderer call |
| `+0x175E` | `+0x175A` | `0x005429EE` | security-cookie check |

The mode35/36 native first getter calls store their x87 results at
`[ebp-0x160]` (`+0x0FCD` and `+0x10BA`). A complete decoded-body operand scan
finds no read of that slot. The maintained source therefore preserves the
standalone getter calls without inventing a dead local solely to reproduce the
stores. The native second getter results are consumed by the adjusted-scale
expressions; MSVC's maintained candidate uses memory-source SSE add/subtract
where the original reloads the saved half into XMM1 and uses register-register
arithmetic.

A mode45-only explicit `inherited_scale` local is codegen-identical to the
maintained source. A second natural C++ probe named the post-getter width-half
values in modes45/46; it grew to 6,049B/1,508 instructions and increased the
E8 offset-delta sum to 260B, with no additional call-position matches. Neither
probe is promoted. The earlier 114/123 candidate also remains rejected because
it swaps the native mode45/46 scale-half and width-half roles.

The separate 244B `Animation::project_corners` dispatcher is now strict exact
as its own 260B code-plus-table unit; that leaf result does not change the
5,993B Draw parent status or its residual call map.
