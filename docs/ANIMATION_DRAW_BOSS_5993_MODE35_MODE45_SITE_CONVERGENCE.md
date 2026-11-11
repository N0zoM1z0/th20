# CORE/RECON-1112 — 5,993B Animation Draw Boss: mode35 width/mode45 color lifetime source convergence

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

This checkpoint changes the *full maintained game-source function*,
[`src/AnimationDrawBoss.cpp`](../src/AnimationDrawBoss.cpp), in only
**three local hunks**, not by extracting a shorter subset of instructions
or patching binary bytes. Both changes preserve the original observable
call sequence and the actual values passed to the renderer:

1. **Mode 35 actual width argument:** A `const float shape_width`
   now owns the genuine `width + (height / native_two)` value used for
   the eventual `draw_shape_43c780` call. Previously that used expression
   was evaluated inline during the call. Original machine instructions
   establish the first scale getter, original secondary/primary packed
   colors, draw count, second scale getter, and two distinct height-halving
   operations. The new used C++ width local alters `/Od` evaluation and
   stack-space lifetime without adding an unused register-shaping value.
2. **Mode 45 actual color/count arguments:** The second packed-color
   getter is called and stored before the first packed-color getter,
   followed by a saved real draw count, *before* evaluating the native
   scale/width arguments to `draw_shape_43df30`. This matches the
   independently decoded original call order and color argument roles.
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
| Original E8 *physical instruction offsets* | 86/123 | **113/123** | 123/123 |
| Absolute E8 opcode offset-delta sum | 516 | **65** | 0 |
| Original in-body HIGHLOW target-role histogram | 32/32 | **32/32** | 32/32 |
| Original in-body HIGHLOW site+role positions | 23/32 | **26/32** | 32/32 |
| All complete ordinary bytes with actual COFF fields masked | 3,819/5,376 | **4,801/5,376** | 5,376/5,376 |

The ordinary byte denominator masks exactly **the compiler's actual
235 four-byte relocation fields** (123 E8 +32 in-body data +80 table
entries); original bytes are not patched or recompiled. The physical E8
callee roles come independently from the immutable PE, not from matching
object offsets or fabricated target data. The resulting nonrelocation
agreement rises by **982 bytes** and full-body reloc site agreement
improves while keeping native code size and the 49+31 switch-pointer
positions *unchanged*.

The re-run whole-source original-role script
[`verify-animation-draw-boss-source-roles.py`](../scripts/verify-animation-draw-boss-source-roles.py)
now **requires** all 123 native calls in their original target order,
first 81 consecutive E8 sites, **113/123** exact native E8 offsets,
absolute offset deviation **65**, complete 80-pointer table partitions,
32/32 data roles including **26 exact site/target pairs**, and
**4,801/5,376** ordinary bytes. It checks all 49 game modes and the
correct source/ABI details for the 18 real rendering children.
The previous version's 86/23/3,819 expectations were superseded,
not silently accepted as a looser baseline.

## Remaining real native differences

There are still **ten original E8 positions that differ**. Eight are
in and near modes 35/36 (the first inherited-scale getter's x87 return
is `fstp [ebp-0x160]` in original mode35 and `fstp [ebp-0x160]` in native
mode36, but the natural C++ unused return is discarded with `fstp st(0)`),
and two are later in the mode45/46 region. Six original in-body HIGHLOW
field locations still differ. The original mode45 computes and spills
`height/2.0f` *before* the second inherited-scale call and uses a
separate XMM operand; the candidate still reorders that evaluation and
some subsequent local stack slots. Although 113 call positions match,
**575 ordinary bytes remain different** and the parent has **no
canonical match-unit / no source-exact game credit**.

A separate local experiment that saved both mode35 and mode36 widths
made the code **6,025B/1,505 instructions**, not the original. Other
used C++ variants (`float adjusted_scale`, a separately named second
scale, mode45/46 half-height temporaries, and alternate color/count
lifetimes) were compiled as *full* functions under ignored `.analysis/`
and `build/`; most either increased code bytes or lost original E8
alignment. The best mode45 color/count candidate alone restores the
whole original 5,993B footprint. Trials did not introduce a dead first
scale float merely to trick the compiler into storing an unused x87
return; its source ownership is still unproven.

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
