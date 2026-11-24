# CORE/RECON-1112 — 5,993B Animation Draw Boss: nested-mode source convergence

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

The current maintained full function is still **5,993B/1,501 i386**, with
its `0x204` frame and 6,316B real code+table COFF contribution. Mode45 uses a
value-equivalent role swap: the pre-getter half feeds width and the post-getter
half feeds adjusted scale. Native mode45 instead uses the pre-getter half for
adjusted scale and recomputes the width half after the getter. The maintained
swap preserves the native register-register `addss` and renderer call position,
but moves the second `native_two` relocation from the native width site to the
adjusted-scale expression. Mode46 follows native half-height ownership: its
pre-getter half feeds adjusted scale and its width half is recomputed after the
getter. MSVC still chooses the shorter direct-memory adjusted-scale
subtraction, leaving the final mode46 renderer call four bytes early. This is
ordinary C++,
not a byte patch or padding. The mode46 ownership correction keeps the native 5,993B/1,501-instruction
extent, **114/123** physical E8 positions and **27/32** exact body relocation
site/target pairs. Its current ordinary-byte agreement is **4,834/5,376**,
one byte below the immediately preceding 4,835-byte value-equivalent source. The detailed native/compiled frontier
and rejected probes are in
[the focused mode45/46 report](ANIMATION_DRAW_BOSS_5993_MODE45_MODE46_RETURN_FRONTIER.md).

The maintained function changes remain ordinary C++ source; no binary bytes,
manual opcodes, or padding are introduced. The value-preserving source changes
preserve all 123 original E8 target roles and the actual renderer argument
values. Mode45's half-height operand ownership remains value-equivalent but reversed
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

## Whole original and whole candidate evidence

The pinned MSVC 19.44 i386 `/std:c++20 /Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` compiles the revised single-source
function to **5,993B/1,501 instructions**, retaining exactly the real
`sub esp, 0x204` frame and a full **6,316B COFF contribution**: the genuine
3B alignment and **80 actual compiler-generated DIR32 case pointers**
appear at the original offsets. Alias partitions for all 49 main/31
nested target pointers are equal to the physical original native tables;
there are no synthetic byte-index tables or hand-authored padding.

| Whole-function metric | Previous maintained source | This source | Original |
| --- | ---: | ---: | ---: |
| Executable code bytes | 5,993 | **5,993** | 5,993 |
| Original-code instruction heads | 1,501 | **1,501** | 1,501 |
| After-`ret` contribution (alignment/tables) | 323B | **323B** | 323B |
| Original E8 role targets and their order | 123/123 | **123/123** | 123/123 |
| Original E8 *physical instruction offsets* | 86/123 | **114/123** | 123/123 |
| Absolute E8 opcode offset-delta sum | 516 | **44** | 0 |
| Original in-body HIGHLOW target-role histogram | 32/32 | **32/32** | 32/32 |
| Original in-body HIGHLOW site+role positions | 23/32 | **27/32** | 32/32 |
| All complete ordinary bytes with actual COFF fields masked | 3,819/5,376 | **4,834/5,376** | 5,376/5,376 |

The ordinary byte denominator masks exactly **the compiler's actual
235 four-byte relocation fields** (123 E8 +32 in-body data +80 table
entries); original bytes are not patched or recompiled. The physical E8
callee roles come independently from the immutable PE, not from matching
object offsets or fabricated target data. The current nonrelocation agreement remains **1,015 bytes** above the older
3,819-byte checkpoint. The prior 4,835-byte score described the value-equivalent
mode46 source before the native ownership correction. E8 position agreement remains **114/123** and data site/target agreement
remains **27/32** through this mode46 source correction, preserving the native
code size and both 49+31 switch-pointer alias partitions.

The re-run whole-source original-role script
[`verify-animation-draw-boss-source-roles.py`](../scripts/verify-animation-draw-boss-source-roles.py)
now **requires** all 123 native calls in their original target order,
first 81 consecutive E8 sites, **114/123** exact native E8 offsets,
absolute offset deviation **44**, complete 80-pointer table partitions,
32/32 data roles including **27 exact site/target pairs**, and
**4,834/5,376** ordinary bytes. It checks all 49 game modes and the
correct source/ABI details for the 18 real rendering children.
The previous version's 86/23/3,819 expectations were superseded,
not silently accepted as a looser baseline.

## Remaining real native differences

There are still **nine original E8 positions that differ**: eight in and
around modes35/36 and one at the final mode46 renderer call. Five original
in-body HIGHLOW site/target positions still differ; all five remaining native
sites are `native_two` references whose candidate instruction offsets moved.
Mode45 still recomputes its adjusted-scale half after the getter instead of
reusing the native saved half. Mode46 now reuses the pre-getter half for
adjusted scale and recomputes the width half after the getter; the compiler's
direct-memory adjusted-scale subtraction is four bytes shorter than native,
leaving the final mode46 renderer call four bytes early. The parent has
**no canonical match-unit / no source-exact game credit**; **542 ordinary
bytes remain different**.

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

No existing exact source, type layout, public header or canonical unit
is modified by this checkpoint; the one changed parent remains **NONEXACT**.
The accepted **774 game-authored exact heads /265,580 bytes** from the
previous checkpoint are unchanged. See the previous dated
[5,993B frame/table frontier](ANIMATION_DRAW_BOSS_5993_NATIVE_LENGTH_AND_STACK_FRONTIER.md)
and [mode35 x87 spill experiments](ANIMATION_DRAW_BOSS_5993_MODE35_X87_PROBES.md)
for the original baseline and rejected variants.
