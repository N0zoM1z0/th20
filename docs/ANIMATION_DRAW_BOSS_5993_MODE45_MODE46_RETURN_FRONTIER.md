# 5,993B Animation Draw Boss: mode45/46 temporary and return frontier

The maintained `AnimationPoolOwner::draw(Animation*)` at `0x00443880` remains
SOURCE-PRESENT/NONEXACT. Its current production baseline is still the
5,993B/1,501-instruction candidate documented in
[the whole-source convergence report](ANIMATION_DRAW_BOSS_5993_MODE35_MODE45_SITE_CONVERGENCE.md):
113/123 original E8 sites, 26/32 body relocation sites and 4,801/5,376
ordinary bytes agree. This note records a newer read-only native investigation
and isolated C++ source probes for the final two nested modes. Production
source and acceptance records are unchanged.

## Native mode45 and mode46 lifetimes

The original PE keeps distinct half-height, inherited-scale and adjusted-scale
locals for each mode. These are not one shared precomputed half-height:

| Mode | Half-height | Inherited scale | Adjusted scale | Native draw call |
| --- | --- | --- | --- | --- |
| 45 | `[ebp-0x1d8]` | `[ebp-0x1d4]` | `[ebp-0x1e8]` | `0x00444EEE` (`+0x166e`) |
| 46 | `[ebp-0x1f0]` | `[ebp-0x1ec]` | `[ebp-0x200]` | `0x00444FD1` (`+0x1751`) |

Mode45 first reads both packed colors and the draw count. It then computes
`height / 2.0f`, loads the Animation receiver into ECX, spills that half-height,
and calls the inherited-scale getter at `+0x15dd`. The returned x87 value is
spilled, reloaded to XMM0, and added to a separately reloaded half-height in
XMM1. The adjusted value is stored before the renderer arguments are pushed.
A second independent `height / 2.0f` computes the width argument.

Mode46 follows the corresponding sequence: packed colors and count, a fresh
half-height division, receiver load and half-height spill, inherited-scale call
at `+0x16bc`, x87 spill, then XMM0/XMM1 subtraction and adjusted-scale spill.
Its width argument performs another independent half-height division. The
native renderer call is at `+0x1751`, followed by the common return/cookie path.

The two arithmetic sequences that matter for the remaining four-byte deltas
are:

```asm
; mode45
movss xmm0, [ebp-0x1d4]
movss xmm1, [ebp-0x1d8]
addss xmm0, xmm1
movss [ebp-0x1e8], xmm0

; mode46
movss xmm0, [ebp-0x1ec]
movss xmm1, [ebp-0x1f0]
subss xmm0, xmm1
movss [ebp-0x200], xmm0
```

The maintained C++ expression forms currently compile the second operand as
a direct memory operand (`addss xmm0, [half]` / `subss xmm0, [half]`). Each is
four bytes shorter than its native register-register form. The difference is
not a missing call, a changed mathematical operation or a missing table entry.

## Bounded source probes

A natural-C++ variant with mode45's used half-height and adjusted-scale locals
owned by the nested switch restores the native inherited-scale call position
at `+0x15dd`. The complete isolated function then compiles to 5,989B/1,500
instructions, four bytes short, and only 109/123 E8 sites align: the mode45
renderer and subsequent mode46 calls remain displaced by the missing
register-register arithmetic bytes. This is not an improvement over the
maintained 5,993B baseline and was not promoted.

A second isolated variant removes the redundant `return 0` immediately after
the nested switch and naturally falls through to the existing outer-switch
zero return. It removes the duplicate `jmp +2; xor eax,eax` tail, but leaves a
5,985B body and the same 109/123 E8-site result. It is a useful control-flow
hypothesis, not an accepted source change: the two mode-specific SSE operand
lifetimes still need to be reconstructed in ordinary C++.

## Mode35/36: shared half-height is the real native dataflow

A separate full-body probe isolated the two earlier nested modes. Their native
stack ownership is:

| Mode | First getter return | Color 494 | Color 490 | Count | Scale half | Second getter return | Adjusted scale |
| --- | --- | --- | --- | --- | --- | --- | --- |
| 35 | `[ebp-0x160]` | `[ebp-0x150]` | `[ebp-0x154]` | `[ebp-0x158]` | `[ebp-0x14c]` | `[ebp-0x148]` | `[ebp-0x15c]` |
| 36 | `[ebp-0x160]` | `[ebp-0x16c]` | `[ebp-0x170]` | `[ebp-0x174]` | `[ebp-0x168]` | `[ebp-0x164]` | `[ebp-0x178]` |

The first getter return is stored in the same `[ebp-0x160]` slot in both modes
and is not read later in the body. The second getter return is converted from
x87 to a scalar local. The scale half is computed **before** that second getter
and is reused by the adjusted-scale arithmetic; the renderer width is a
separate, later `height / 2.0f` computation. In mode35 the adjusted scale is
`second_return + scale_half`; in mode36 it is `second_return - scale_half`.

This corrected a previous probe's semantic inversion, which had computed the
width half early and recomputed the scale half after the getter. The natural
C++ half-reuse probe restores the native local-slot assignments for both modes
and the separate later width division. It compiles to 5,985B/1,499
instructions, however: MSVC emits `addss xmm0, [scale_half]` and
`subss xmm0, [scale_half]` instead of the native `movss xmm1, [scale_half]`
followed by register-register `addss`/`subss`. Each arithmetic sequence is
four bytes shorter, so the mode35 renderer is four bytes early and the mode36
renderer eight bytes early. This is a useful semantic convergence, not an
accepted exact candidate.

The first getter's `fstp [ebp-0x160]` remains a separate unresolved source
question: it is present twice in the native body and has no in-body read. No
unused variable is added merely to manufacture it.

## Getter ABI: Ghidra `float10` is not an MSVC `long double` source type

A fresh native decompile of `0x00445880` identifies the inherited auxiliary
scale getter as `float10 __fastcall`. It initializes a parent factor from the
original `1.0f` at `0x0056C8CC`; when `Animation+0x558` is non-null and flag
`Animation+0x49C` bit 12 is clear, it recursively obtains the parent's scale,
converts that result to `float`, and multiplies it by the current object's
`Animation+0x58` x-scale. The final multiplication is returned in x87 ST0.

This `float10` is the decompiler's extended x87 value type, not evidence that
the source declaration should be changed to MSVC `long double`. The maintained
`float __fastcall animation_inherited_aux_scale_x(Animation*)` implementation
is independently exact at **93/93 native bytes**, including its recursive
call, original `1.0f` relocation and x87 return. The Draw Boss caller's native
mode35/36 sequence stores that x87 return with `fstp m32` before loading it
into XMM0. The current C++ `float` declaration therefore remains the supported
source-level ABI model.

An isolated full-function probe changed only that declaration to `long double`
and explicitly cast the result back to `float`. Under MSVC 19.44, `long double`
is 64-bit: the candidate instead emits `fstp m64`, `movsd`, `cvtss2sd`,
`addsd`/`subsd`, and `cvtsd2ss`. It grows to a 6,005B code body and does not
match the original single-precision path. This hypothesis is rejected; neither
the exact getter nor its declaration is changed.

## Mode35/36 operand-register frontier

The current maintained full-body object has the established 5,993B/1,501
instruction baseline, **113/123** native E8 instruction offsets, **26/32**
exact in-body relocation positions and **4,801/5,376** ordinary-byte matches.
Its remaining mode35/36 arithmetic difference is precise: native mode35 loads
the spilled half-height with `movss xmm1, [ebp-0x14c]` before `addss xmm0,
xmm1`; native mode36 similarly loads `[ebp-0x168]` into XMM1 before
`subss xmm0, xmm1`. The corresponding natural-C++ half-reuse probe instead
uses `addss xmm0, [half]` and `subss xmm0, [half]`. Each direct-memory form
is four bytes shorter than the native register-register form.

Additional full-function trials with `volatile`, pointer/reference aliases,
aggregate/array storage, reversed operands, compound assignment, function-scope
locals and `register` did not recover the native register loads while preserving
the surrounding native call order and stack ownership. MSVC 19.44 warns that
`register` is no longer supported. SSE intrinsic variants materialize and spill
16-byte temporaries (the one-vector-local probe reaches a 6,181B code body);
they are not natural or useful replacements. These experiments remain ignored
under `.analysis/` and `build/`.

## Rejected code-generation shortcuts

Further isolated probes did not produce the native register-register form:

- `volatile` and `register` declarations leave the arithmetic as a direct
  memory operand; MSVC 19.44 warns that `register` is unsupported.
- `/fp:strict` and `/fp:fast` leave the same instruction forms and call-site
  positions.
- `_mm_load_ss`/`_mm_add_ss` source expressions under `/Od` materialize
  128-bit temporaries and spill them, expanding the COFF contribution beyond
  6,400B instead of recovering the four-byte native sequence.
- A `__vectorcall` arithmetic helper is not inlined under the locked `/Ob0`
  profile; it introduces two extra E8 calls and retains the memory-operand
  arithmetic.

These probes stay private under `.analysis/` and `build/`; none changes the
maintained source or the locked compiler profile.

Read-only Ghidra operand search across the full 5,993B body found exactly two
references to `[ebp-0x160]`: the first inherited-scale calls in modes35 and36
store there at `+0x0fcd` and `+0x10ba`. No decoded instruction in the body reads
that slot. The probe therefore does not add an unused local just to force those
x87 stores; their original source ownership remains unresolved.

The isolated probes used the locked MSVC x86 profile and did not edit
`src/AnimationDrawBoss.cpp`, shared headers, canonical objects, match units or
the target. No full cold replay was run. The next step remains to derive the
mode35/36 register-register SSE form and the mode45/46 receiver/spill ordering
from natural source semantics, then revisit the first getter's native x87 spill
ownership without inventing a dead temporary. The exact 93B getter and its
`float` declaration remain unchanged. The only active target remains the
5,993B Draw Boss; no function switch is authorized before its complete strict
exact replay.
