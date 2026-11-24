# 5,993B Animation Draw Boss: mode45/46 temporary and return frontier

The maintained `AnimationPoolOwner::draw(Animation*)` at `0x00443880` remains
SOURCE-PRESENT/NONEXACT. Its current production body is 5,993B/1,501
instructions with a 0x204 frame and 6,316B complete code+table contribution.
The current whole-source metrics are **114/123** original E8 physical sites,
**27/32** exact in-body relocation site/target pairs and **4,834/5,376**
ordinary bytes. The latest source correction restores native mode46 half-height
ownership; the remaining code-generation frontier is the mode46 adjusted-scale
register operand, mode45 half reuse, and the earlier mode35/36 call deltas.
This report does not claim exactness.

## Native mode45 and mode46 lifetimes

The original PE keeps distinct half-height, inherited-scale and adjusted-scale
locals for each mode. Both modes compute a half-height before the inherited-
scale getter for adjusted scale, then independently recompute the width half
after the getter:

| Mode | Half-height | Inherited scale | Adjusted scale | Native draw call |
| --- | --- | --- | --- | --- |
| 45 | `[ebp-0x1d8]` | `[ebp-0x1d4]` | `[ebp-0x1e8]` | `0x00444EEE` (`+0x166e`) |
| 46 | `[ebp-0x1f0]` | `[ebp-0x1ec]` | `[ebp-0x200]` | `0x00444FD1` (`+0x1751`) |

Mode45 first reads both packed colors and the draw count. It then computes
`height / 2.0f`, loads the Animation receiver into ECX, spills that half-height,
and calls the inherited-scale getter at `+0x15dd`. The returned x87 value is
spilled, reloaded to XMM0, and added to a separately reloaded half-height in
XMM1. The adjusted value is stored before the renderer arguments are pushed.
The same saved half-height is loaded again for the width argument.

Mode46 follows the corresponding sequence: packed colors and count, a fresh
half-height division, receiver load and half-height spill, inherited-scale call
at `+0x16bc`, x87 spill, then XMM0/XMM1 subtraction and adjusted-scale spill.
Its width argument performs another independent half-height division after the getter. The native renderer call is at `+0x1751`, followed by the common return/cookie path.

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

The maintained mode45 C++ still computes the half-height for width before the
getter and recomputes it for adjusted scale after the getter. The values are
equivalent, but native mode45 reuses the pre-getter half-height for both
arguments; that local-lifetime/code-generation difference remains open.

Mode46 has now been corrected to native source-level ownership: its pre-getter
half-height feeds adjusted scale, and the width expression independently
recomputes `height / native_two` after the getter. The compiled body retains
5,993B/1,501 instructions, 114/123 E8 positions and 27/32 exact data-site
pairs. MSVC still emits the adjusted-scale subtraction as the shorter
`subss xmm0, [half]` instead of native `movss xmm1, [half]; subss xmm0, xmm1`;
that four-byte instruction delta leaves the final mode46 renderer call at
`+0x174d` rather than native `+0x1751`. The width subtraction now follows the
native register-register form. The whole-parent ordinary-byte score is
4,834/5,376. No opcode or padding is introduced.

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
unused variable is added merely to manufacture it. The native verifier now
pins both getter-call/store pairs and the second-return XMM0/XMM1 arithmetic
windows, so later source probes cannot mistake the first discarded result for
the second value consumed by adjusted scale.

## First getter return: native m32 spill versus discarded x87 result

The immutable native body calls the inherited-scale getter at `+0x0fc8` and
`+0x10b5`; each first call is immediately followed by
`fstp dword ptr [ebp-0x160]`. A full-body operand search finds no read of that
slot. The second getter calls at `+0x1016` and `+0x1103` instead spill to
`[ebp-0x148]` and `[ebp-0x164]`. Each second result is loaded into XMM0, the
precomputed half-height into XMM1, and consumed by register-register `addss`
or `subss`. `scripts/verify-animation-draw-boss-native.py` now asserts these
four exact byte windows and confirms that all four calls target `0x445880`.

The maintained source still spells the first calls as discarded expressions;
MSVC emits `fstp st(0)`, not the native m32 stores. A switch-scope
`first_scale_result` assignment does reproduce both `[ebp-0x160]` stores and
the native `0x204` frame, but its full-body probe falls to **5,985B/1,499
instructions**, **84/123** E8 positions, **23/32** data sites and
**3,710/5,368** ordinary bytes. This probe also reproduces the native local
slot map: mode35 color/count/half/second-return/adjusted values occupy
`-0x150/-0x154/-0x158/-0x14c/-0x148/-0x15c`; mode36 uses
`-0x16c/-0x170/-0x174/-0x168/-0x164/-0x178`. Its remaining two adjusted-scale
operations still use direct-memory `addss`/`subss`, four bytes shorter apiece.
Combining the local with the newer mode35 width temporary instead produces a
**6,001B/1,501-instruction** body with a `0x208` frame, only **84/123** E8
positions and **23/32** data sites, and **3,760/5,384** ordinary bytes.
Neither is promoted. A case-local initialized scalar stores to a new
`[ebp-0x208]` slot and also expands the frame.

Volatile half-height locals still select direct-memory arithmetic. Pointer
aliases produce `addss xmm0, [edx]` / `subss xmm0, [eax]`, not the native
register-register form. SSE intrinsic attempts materialize 16-byte vector
temporaries and expand the function beyond 6,100B. These remain isolated
experiments; production stays at **5,993B/1,501 instructions**, frame
`0x204`, **114/123** E8 positions, **27/32** data sites and
**4,834/5,376** ordinary bytes.

## Whole-parent cost of recovering the first spills and SSE register forms

A combined first-result/half-height role-swap probe reproduces both native
`fstp [ebp-0x160]` stores and both register-register adjusted-scale operations
in ordinary C++. It keeps the `0x204` frame, but the full parent is only
**5,989B/1,500 instructions**, **89/123** E8 sites, **24/32** data sites and
**3,794/5,372** ordinary bytes. The extra local changes too much of the
parent's stack and relocation layout; this is not promoted over the maintained
**4,835/5,376** baseline.

A separate mode36-only role swap on the maintained source keeps the native
5,993B/1,501-instruction body and **114/123** E8 sites, and aligns the final
mode46 renderer call. However, ordinary-byte agreement falls to
**4,765/5,376** and data-site agreement to **26/32**. It is also rejected:
local call-boundary recovery is not worth the larger whole-parent regression.

Further attempts to materialize the first return without a named local were
not successful. `static_cast<volatile float>(getter())` is optimized back to
`fstp st(0)`. Short-lived case-block objects spill at `[ebp-0x20c]`; a local
inserted between the mode35 and mode36 labels spills at `[ebp-0x208]` and
expands the frame. `_ReadWriteBarrier()` inserts NOPs but leaves the
register-memory arithmetic unchanged. No such compiler-shaping probe is
promoted.

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
instruction baseline, **114/123** native E8 instruction offsets, **27/32**
exact in-body relocation positions and **4,835/5,376** ordinary-byte matches.
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

Mode45 still uses a value-equivalent role swap: its pre-getter half feeds
width and a second `height / native_two` calculation after the getter feeds
adjusted scale. Native mode45 does the opposite: the saved pre-getter half
feeds adjusted scale, and the width half is recomputed after the getter. The
maintained expression keeps the native register-register `addss` form and E8
call positions, but moves the second absolute `native_two` relocation from
the native width site `+0x1646` to the candidate adjusted-scale site `+0x15f9`.
A probe using native mode45 half ownership compiled to 5,989B/1,500
instructions, only 109/123 E8 positions and 4,685/5,369 ordinary bytes, so it
was not promoted.

Mode46 now follows native source-level ownership: its pre-getter half feeds
adjusted scale and its width expression recomputes `height / native_two` after
the getter. The compiler emits the adjusted-scale subtraction as a shorter
direct-memory `subss`; the final renderer E8 remains candidate `+0x174d` versus
native `+0x1751`. The width subtraction now has the native register-register
form.

A follow-up natural expression `0.0f - (half_for_width - width)` makes the
full body 5,993B/1,501 instructions, but inserts a non-native `xorps` plus
`subss` sign-negation sequence and moves that renderer call three bytes late.
It is not accepted. The value-equivalent role-swap is a useful register-form
proof, not a production improvement: the isolated full-body comparison remains
well below the maintained source's current 4,834/5,376 ordinary-byte and
114/123 E8-site baseline because other local ownership and mode45/46 layout
still differ.
Both probes remain private under `.analysis/` and `build/`.

The earlier mode36 width-operand probes tested volatile and reference aliases,
copy-then-subtract, compound assignment, operand reversal, `width + (-half)`,
`width + (0.0f - half)`, and `width - (half * 1.0f)`. The maintained source now
uses the native register-register width expression in mode36; the remaining
mode36 arithmetic mismatch is its adjusted-scale subtraction, which MSVC still
emits with a direct-memory second operand. `0.0f - (half - width)` used a
register-register form by zeroing XMM1 first, but added a non-native
`xorps`/`subss` pair and left the renderer call three bytes late.
`__forceinline` identity/negation helpers also remain real E8 calls under
`/Ob0`; they do not inline away. These are rejected compiler-shaping routes,
not production source changes.

## Rejected code-generation shortcuts

Further isolated probes did not produce the native register-register form:

- `volatile` and `register` declarations leave the arithmetic as a direct
  memory operand; MSVC 19.44 warns that `register` is unsupported.
- `std::atomic_signal_fence(std::memory_order_seq_cst)` is not a zero-code
  compiler barrier in this locked `/Od` probe: MSVC emits a `push 5; call;
  add esp, 4` helper sequence at each adjusted-scale site, adding two extra
  E8 calls and moving the original call order. It does not force XMM1 and is
  rejected as both non-native and semantically unrelated.
- `/fp:strict` and `/fp:fast` leave the same instruction forms and call-site
  positions.
- `_mm_load_ss`/`_mm_add_ss` source expressions under `/Od` materialize
  128-bit temporaries and spill them, expanding the COFF contribution beyond
  6,400B instead of recovering the four-byte native sequence.
- A `__vectorcall` arithmetic helper is not inlined under the locked `/Ob0`
  profile; it introduces two extra E8 calls and retains the memory-operand
  arithmetic.
- Unary-plus and scalar-cast spellings, pointer aliases, and volatile half
  locals still select direct-memory `addss`/`subss`. `std::ignore` and
  temporary-reference bindings for the first getter add calls or stack traffic
  rather than reproducing the native `fstp` stores.
- For mode46 adjusted scale, `0.0f - (half_for_scale - inherited_scale)`
  replaces the direct-memory subtraction with `subss` plus `xorps`/`subss`,
  but expands the body to 5,997B/1,499 instructions and leaves the mode46
  renderer call three bytes late. It is not an exact replacement.

These probes stay private under `.analysis/` and `build/`; none changes the
maintained source or the locked compiler profile.

Read-only Ghidra operand search across the full 5,993B body found exactly two
references to `[ebp-0x160]`: the first inherited-scale calls in modes35 and36
store there at `+0x0fcd` and `+0x10ba`. No decoded instruction in the body reads
that slot. The probe therefore does not add an unused local just to force those
x87 stores; their original source ownership remains unresolved.

The isolated probes used the locked MSVC x86 profile and did not edit
shared headers, canonical objects, match units or the target. No full cold
replay was run. The next step remains the mode35/36 E8-site deltas, both
register-register adjusted-scale operands, the mode45 half-height operand ownership and the
first getter's native x87 spill ownership. A switch-scope `first_scale_result` probe did recover
`fstp [ebp-0x160]` in both modes without changing the 0x204 frame, but its
5,985B body, 84/123 E8 positions, 23/32 data sites and 3,710/5,368 ordinary
bytes make it worse than the maintained source, so it was not promoted.

A follow-up combined that first-result capture with the value-equivalent
half-height role swap in both modes. It restores register-register `addss`
and `subss` by recomputing the half-height after each getter, while the
pre-getter half feeds width. Both first-result stores remain at
`[ebp-0x160]`, the frame remains `0x204`, and the whole function is
5,989B/1,500 instructions. The first 89/123 E8 positions now align, but
the mode36 renderer call is still four bytes early; the later calls remain
displaced. This is not promoted because it loses to the maintained source's
114/123 E8 positions and 4,834/5,376 ordinary bytes, and still depends on
an unread first-result local whose source ownership is unproven.

The
exact 93B getter and its `float` declaration remain unchanged. The only active
target remains the 5,993B Draw Boss; no function switch is authorized before
its complete strict exact replay.
