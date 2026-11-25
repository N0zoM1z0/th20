# 5,993B Animation Draw Boss: mode45/46 temporary and return frontier

The maintained AnimationPoolOwner::draw(Animation*) at 0x00443880 remains
SOURCE-PRESENT/NONEXACT. The immutable target body is 5,993B/1,501
instructions with a 0x204 frame and 6,316B complete code+table contribution.
The current production source preserves native mode45/46 half-height
evaluation order and compiles to 5,989B/1,501 instructions, with a 6,312B
complete code+table contribution. Current whole-source metrics are 109/123
original E8 physical sites, 26/32 exact in-body relocation site/target pairs
and 4,694/5,372 ordinary bytes. The remaining code-generation frontier is the
native register-register adjusted-scale operands in modes35/36/45/46, the first
mode35/36 x87 result spill, and the four-byte body/table displacement from the
source-correct mode45 expression. This report does not claim exactness.


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
The width argument independently recomputes `height / 2.0f` after the
getter; it does not reuse the saved scale half-height.

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

The maintained mode45 C++ deliberately uses a value-equivalent role swap:
its pre-getter half-height feeds width, and its post-getter half-height feeds
adjusted scale. Native mode45 does the opposite: the pre-getter half-height
feeds adjusted scale, while width independently recomputes the half-height
after the getter. The role swap retains native register-register `addss` and
the renderer call position, but moves the second `native_two` relocation from
the native width calculation to the adjusted-scale calculation. It is a
measured source/code-generation tradeoff, not the native temporary ownership.

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

A native-source-order mode45 probe keeps the pre-getter half for adjusted
scale and recomputes the width half after the getter. MSVC then selects the
shorter memory-source `addss`, producing a 5,989B/1,500-instruction body,
109/123 E8 positions and 4,688/5,372 ordinary-byte matches. The maintained
value-equivalent role swap retains 5,993B/1,501 instructions, 114/123 E8
positions and 4,834/5,376 ordinary-byte matches, so the source-order probe was
not promoted. Its result confirms the tradeoff is caused by the scalar SSE
operand form rather than a missing getter or renderer call.

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
**4,834/5,376** baseline.

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
exact in-body relocation positions and **4,834/5,376** ordinary-byte matches.
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

## First getter x87 spill and branch-local lifetime

The native mode35 and mode36 paths both store the first inherited-scale getter's
x87 return to `[ebp-0x160]` with `fstp m32`. That slot is not read later; the
current source evaluates the same getter for its side effects and emits
`fstp st(0)`. This is a real dead-store/code-generation difference, not a
missing getter call.

A shared first-result local plus native late width expressions can recover
`fstp [ebp-0x160]` in both paths and restore the native mode35/36 color/count,
half-height and adjusted-scale local slots. It still compiles to only
**5,985B/1,499 instructions**, **84/123** E8 positions and **3,720/5,368**
ordinary bytes. A scoped case-label variant has the same score. Adding the
value-equivalent mode35/36 half-height role swaps grows the body to
**5,989B/1,501 instructions**, aligns **89/123** E8 sites and reaches
**3,795/5,372** ordinary bytes, but later case layout and branch positions still
regress substantially. None is promoted over the maintained **5,993B** source.

Short-lived `volatile` locals in `do`/`for`/`if` statements do force x87 memory
stores, but MSVC allocates them at `[ebp-0x20c]` / `[ebp-0x208]`, adds control
flow, and expands the body to **6,013–6,041B** with only **81/123** E8 sites.
These are not natural reconstructions and are rejected. The first getter spill
remains open; do not add an unread dummy local, volatile storage, helper call,
opcode, or padding to claim progress.

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

## 2026-11-25 follow-up: width-half candidate rejected on native call order

The maintained source was rebuilt under the locked profile and rescored at
**5,993B code, 4,840/5,376 ordinary bytes, 114/123 physical E8 positions**,
with the existing 0x204 stack frame and 27/32 in-body HIGHLOW site/target
pairs. This is the current source baseline; older 4,834/5,376 receipts above
refer to an earlier source snapshot.

A fresh `mode35` declaration-order probe computes `shape_width` before
`aux_half` and then inlines the second inherited-scale getter into the adjusted
scale expression. It raises the raw ordinary-byte score to **4,844/5,376**
without changing the 5,993B body length or the count of physical E8 calls.
However, it moves the second mode35 getter from native `+0x1016` to candidate
`+0x102c` (22 bytes late) because both `/2` expressions now precede that call.
It also changes the native half-height evaluation order. The apparent four-byte
score improvement is therefore rejected; it is not a better reconstruction of
the original call/evaluation sequence and is not copied into `src/`.

Other current-source probes with mutable/volatile half locals, top-level
volatile return qualifiers, volatile casts, shared-result locals, pointer
aliases, aggregate scale pairs and SSE intrinsic temporaries either retain the
same codegen, move the call sequence, grow the contribution, or spill at
unrelated stack offsets. The mode46-native-expression-order variant scores
below the maintained baseline. No production Draw Boss source change is
accepted in this follow-up.

The current blockers remain sharply localized:

- mode35/36 first inherited-scale result: native `fstp m32 [ebp-0x160]`,
  maintained source `fstp st(0)`; the native slot has no later read in the body.
- mode35/36 adjusted-scale and half-height local lifetimes: native adjusted
  result at `-0x15c`, with distinct half-height slots; current locals occupy
  different stack roles.
- mode46 adjusted-scale: native reloads the half into XMM1 and emits
  `subss xmm0, xmm1`; maintained source uses the shorter direct-memory
  `subss xmm0, [half]`, leaving its renderer call four bytes early.

Do not accept the 4,844-byte candidate solely for its higher ordinary-byte
score. Keep the maintained 4,840-byte source until a candidate also preserves
the native E8 sequence positions, stack ownership, floating evaluation order,
and original PE relocation roles using ordinary C++.

## 2026-11-25 follow-up: mode36 register-load and spill probes

A second focused battery kept the mode36 getter order and the separate width
recomputation intact while moving declarations/assignments for
`aux_half`, `inherited_scale` and `adjusted_scale` around the case block. The
following natural C++ variants all compile back to the same maintained
**5,993B / 4,840-of-5,376 ordinary-byte / 114-of-123 E8-position** result;
none causes MSVC to materialize the native `movss xmm1, [ebp-0x168]` before
`subss xmm0, xmm1`:

- declare `adjusted_scale` before the color getters, assign after the second
  inherited-scale call;
- declare `inherited_scale` before the color getters, assign after the half;
- declare `aux_half` before the color getters and assign at the native
  half-height evaluation point;
- declare both half and adjusted temporaries before the getters;
- declare half before the getter but assign it after the getter;
- seed a mutable adjusted-scale local from the getter and apply `-=`.

A separate width-half local, whether declared before the case operations or
computed after adjusted scale, breaks the original 81-site exact E8 prefix and
reduces the candidate to 81/123 E8 positions. Reusing `aux_half` for width
instead of the native second division changes more of the nested switch and
is rejected. These are real value locals, not padding, but they do not improve
the reconstruction.

The source was also compiled with `/Zi` and `/Z7` diagnostics added to the
locked profile. Both produce the unchanged **5,993B / 4,840 / 114-of-123**
body and retain `fstp st(0)` for the first mode35/36 getter results; debug-info
selection does not explain the native dead-store spill.

`std::bit_cast<float>(std::bit_cast<std::uint32_t>(aux_half))` is a bit-preserving
C++ spelling, but under `/Od` it creates extra calls/temporaries and loses the
native call census. Scalar `_mm_load_ss`/`_mm_cvtss_f32` variants likewise
materialize vector temporaries, produce 6,372B+ contributions and no useful
native call alignment. They are not promoted: the source remains ordinary
scalar C++ and the locked compiler profile is unchanged.

These focused trials do not alter the parent source, canonical objects,
manifest, or full replay state. The first-getter write-only local and mode36
register operand remain unresolved; no fake local, assembly, intrinsic,
volatile storage, or padding is accepted as progress.

## 2026-11-25 follow-up: original write-only spill and late mode36 argument

A fresh native decompile/context pass of `0x00443880`, cross-checked against
the original PE instruction stream, confirms the first mode35 and mode36
`animation_inherited_aux_scale_x` calls are standalone expressions in the
recovered control flow, while the native machine code writes their x87 return
to the same write-only local `[ebp-0x160]` at `+0x0FCD` and `+0x10BA`.
A full decoded-body operand scan finds no subsequent read of that slot. The
source-level identity of this apparently dead local is still unknown.

A current-source-derived scalar C++ probe now models it as one function-scope
`[[maybe_unused]] float first_inherited_scale`, assigned by the first getter
in each case. It produces both original `fstp m32 [ebp-0x160]` stores. Keeping
the current mode45/46 source unchanged, the probe also restores the mode35
`addss xmm0,xmm1` and mode36 `subss xmm0,xmm1` register-register forms by
computing a real half-height local for the width argument before the second
getter and independently recomputing the same half-height for adjusted scale
after it. This is a value-equivalent ordering of a pure read/division against
the recursive getter; it is a compiler probe, not yet an accepted source edit.

| Candidate | Code | Ordinary bytes | E8 positions | Native spill / SSE forms |
| --- | ---: | ---: | ---: | --- |
| Maintained source | 5,993B | 4,840/5,376 | 114/123 | neither first spill; mode46 memory subtraction |
| Current-source spill probe | 5,989B | 3,801/5,372 | 89/123 | both spills; register add and subtract |
| Spill + double-roundtrip width probe | 5,997B | 3,930/5,380 | 90/123 | both spills; register add and subtract; rejected |

The current-source spill probe preserves the first **88** physical E8 sites,
including the mode35/36 getter and renderer calls through `+0x1103`. Starting
with the mode36 renderer call at native `+0x1198`, every later physical E8 is
four bytes early. The precise remaining difference is the final mode36 width
argument:

- Native recomputes `height / 2` after adjusted-scale, then loads `width` into
  XMM1 and subtracts the new half in XMM0 (`subss xmm1,xmm0`).
- The 5,989B probe reuses the earlier half local for width and emits a shorter
  direct-memory subtraction (`subss xmm0,[half_for_width]`).

That reuse removes four bytes before the renderer call and explains the
uniform `-4` tail call displacement. Replacing it with the native post-getter
width recomputation restores the expression order, but the locked compiler
still uses the memory form for the adjusted-scale subtraction when that
expression consumes the saved half local. The source battery varied mutable,
assigned, copied, referenced and volatile scalar locals; none yielded the
native XMM1 load. Scalar SSE intrinsic forms materially changed stack/register
allocation and contribution shape. They are not promoted.

A double float-to-double-to-float round trip adds the four-byte displacement
back and raises the raw E8-position count to 90/123, but it is not a native
operation and is not accepted as a reconstruction. It also leaves the full
body four bytes too long. No current probe improves on the maintained source's
4,840/5,376 ordinary-byte and 114/123 E8-position evidence while preserving
all source-level semantics, so `src/AnimationDrawBoss.cpp` remains unchanged.


## 2026-11-25 follow-up: native mode45 evaluation order restored in production

Production src/AnimationDrawBoss.cpp now computes the mode45 scale half-height
before the inherited-scale getter, uses it for adjusted scale after the getter,
and independently recomputes the width half in the renderer argument list.
Mode46 already used this original source order and remains unchanged. The
earlier role-swap sections in this report describe a historical source snapshot
and must not be read as the current production implementation.

The focused source-role replay emits 5,989B/1,501 instructions, a 0x204 stack
frame and a 6,312B code+table contribution. It matches 4,694/5,372 ordinary
bytes, 109/123 E8 positions, 68B summed absolute E8 displacement and 26/32
exact HIGHLOW site/target pairs. The former role-swap source had a better raw
machine score but reversed the native evaluation order; it is no longer
maintained.

The original-only native verifier pins the four modes' scale and width
sequences: mode35 scale +0x1016 / width +0x1068; mode36 scale +0x1103 /
width +0x1155; mode45 scale +0x15DD / width +0x163D; mode46 scale +0x16BC /
width +0x171C. The previous verifier mislabeled +0x171C as mode36 width; that
is mode46, while mode36 width is +0x1155. Both focused verifiers pass.

Candidate-only decoding confirms the corrected mode45 source still emits
memory-source addss rather than native movss xmm1 followed by register-register
addss. Mode46 likewise emits memory-source adjusted-scale subtraction. The
candidate-only report separates these scale operations from the later width
operations, so mode46's width subss xmm1,xmm0 is not misreported as its
adjusted-scale subtraction. No opcode or padding is introduced.
