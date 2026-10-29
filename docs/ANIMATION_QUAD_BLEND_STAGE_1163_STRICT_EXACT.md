# CORE/RECON-813 — whole original 1,163-byte /343-x86 quad renderer texture-stage state Boss strict exact

Original locked Japanese TH20 v1.00a Steamless PE SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
**The entire original game-owned `0x00446690` four-mode graphics texture-state
machine is now 1,163/1,163 bytes, 343/343 native x86 instruction heads
strictly exact.** The original after-return **1-byte NOP and four 4-byte
switch entries are additionally 17/17 bytes exact**. Every one of the
complete **54 independently PE-verified relocation fields** is preserved
at the actual offset, with the true original destination and COFF symbol
identity, not inferred by reverse-solving the under-comparison addresses.

## Native whole behavior, not a 25-byte padded C++ prefix

The genuine game renderer receiver is the already maintained
`AnimationQuadSubmitOwner`, which is a declaration-only ABI view of the
existing `AnimationPoolOwner` runtime object. The original function takes
one `uint8_t` source mode, compares it with the first physical byte of
its ECX receiver and, only when the mode changes, calls the existing strict
**192-byte `AnimationPoolOwner::flush_draws`** at original `0x004455C0`
*before* any D3D9 state changes. It then selects one of four native
texture-stage mode paths, calls `process_graphics.get_device()` **six times
per mode**, and immediately invokes the returned genuine D3D9
`IDirect3DDevice9::SetTextureStageState` virtual method at vtable
**`+0x10C`** for each of the following six state/value pairs. The first
argument to every original call is texture stage 0.

| Original mode | ALPHAARG1 (5) | ALPHAARG2 (6) | COLORARG1 (2) | COLORARG2 (3) | ALPHAOP (4) | COLOROP (1) |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| 0, and out-of-range default | 2 | 0 | 2 | 0 | 4 | 4 |
| 1 | 2 | 3 | 2 | 3 | 4 | 4 |
| 2 | 0 | 0 | 0 | 0 | 2 | 2 |
| 3 | 2 | 0 | 2 | 0 | 3 | 4 |

Once the full six-state path has completed, the original stores the new
byte back to the first owner byte and performs the genuine original
`ret 4`. It does **not** repeat D3D9 setup when the requested state equals
the cached byte. These are observable gameplay renderer-state transitions,
not individual generic D3D9 library functions; the entire owner method is
correctly credited once as original authored-game code.

## The original PE's executable boundary and after-body real jump table

The immutable executable starts at **`0x00446690`**, and its last
complete instruction is the original `ret 4` at **`0x00446B18`**.
The *entire native executable function body is exactly 1,163B*, ending
just before the **single original `NOP` at `0x00446B1B`**. The four
actual switch-table code pointers at original **`0x00446B1C..0x00446B2B`**
are physically separate `.text` *data*, and every table element has its
own genuine PE32 `IMAGE_REL_BASED_HIGHLOW` relocation:

| Original 32-bit PE field | Original physical target |
| --- | --- |
| `0x00446B1C` | `0x004466CE` — mode 0 |
| `0x00446B20` | `0x004467C4` — mode 1 |
| `0x00446B24` | `0x004468DE` — mode 2 |
| `0x00446B28` | `0x004469F8` — mode 3 |

The real x86 indirect jump at **`0x004466C7`** uses one more real
in-function HIGHLOW field at **`0x004466CA`** and points to the actual
switch-table **address** `0x00446B1C`. It guards unsigned mode indices
`0..3` with `cmp index,3; ja default`, making default values outside
that range use the mode-0 semantics. No pointer-table data is treated
as extra native x86 instructions, no synthetic code tail is credited
as a game function, and there is no 1,163-byte prefix-only comparison.

**Whole original native reference census** (independently from the
immutable original `.reloc` directory and E8 machine-code displacements):

- **25 real original E8/REL32:** 24 direct calls to the genuine original
  `Graphics::get_device()` compatible original function `0x00412730`,
  and one call to the previously exact 192B game draw-queue flush
  `0x004455C0`. The original **24 virtual D3D9 calls** at `+0x10C`
  are *indirect*, not additional E8 relocations.
- **29 real original HIGHLOW/DIR32** across the complete 1,180B extent:
  24 direct pointer references to the existing `process_graphics` global
  `0x005C4D40`, one in-body table operand `0x004466CA →0x00446B1C`,
  and four switch-table target entries listed above.
- **54/54 original relocation fields across the full 1,180B original
  code/NOP/data extent**, with zero wrong call/data role or target.

## The original MSVC source spelling and exact compiler extent

The source in `src/AnimationQuadBlendState.cpp` is one entirely natural
`void AnimationQuadSubmitOwner::select_render_color_mode(uint8_t)`
implementation: a true direct byte comparison, natural guard/flush, one
`switch` with explicit `case 0` and out-of-range `default`, 24 *real*
repeated `process_graphics.get_device()->SetTextureStageState(...)`
invocations using the official SDK enum names, and a genuine byte-state
assignment on exit. No fake vtable, padding, inert compiler variable,
assembly/NOP patch, PE patch or fabricated external call is involved.

The initial credible C++ body with a cached `uint8_t&` receiver and
`case 1/2/3` plus `default` produced **1,188B** of compiler contribution,
with the original switch lowered to a comparison chain instead of the
original indexed jump. Independently testing natural source variants
showed that directly reading the real owner byte removes the extra
compiler reference temporary, and explicitly listing `case 0` beside
`default` instructs **the same pinned MSVC x86 compiler** to generate the
original four-entry direct dispatch table. The actual compiler
contribution is **1,180B**: **1,163B executable /343 x86** followed
by the same original **1B NOP and 16B table**.

The new canonical unit `animation_quad_blend_stage_boss_1163` records
`size=1163`, **`compare_size=1180`** to include the *entire* original
C++ compiler contribution, and **all 54 independently original-PE-verified
relocation kind/offset/symbol/absolute-target identities**, including
those four after-return HIGHLOW fields. Native pinned MSVC
19.44.35211 i386 flags `/Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` compile one new
`build/core813-canonical/AnimationQuadBlendState.obj` and matching
compiler receipt. The strict full-original replay passes exactly:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQuadBlendState.cpp

    animation_quad_blend_stage_boss_1163: exact
      1163/1163 original coverage bytes,
      1180/1180 original code + NOP + table compared bytes

The independent source-blind `scripts/verify-animation-quad-blend-native.py`
reads all original 343 i386 instructions, 24 virtual D3D9 call argument
triplets, 25 original physical E8 sites and destinations, 29 physical
PE HIGHLOW sites and target values, plus all four original switch entries,
without using the compiled C++ or prior Ghidra decompilation as an oracle.
It is a separate evidence gate, not a substitute for canonical replay:

    scripts/repo-python scripts/verify-animation-quad-blend-native.py

## Local impact, exact code accounting and large parent boundary

This checkpoint edits **only one new source/provider** plus tracking,
original-PE audit and documentation. The already accepted shared
`AnimationQuadSubmitOwner.hpp`, the five-mode wrapper unit, texture
lookup and 352B append retain their original source/header bytes and
compiler receipts. Existing affected strict units = **zero**; one new
1163B native unit is cold-compiled/replayed. No all-graph cold replay.

Author-owned exact original game coverage advances **587 →588 complete
distinct game functions**, **189,624 →190,787 original `.text` bytes**;
source mappings **1,236 →1,237**, native strict units **1,236 →1,237**,
protected canonical object/receipt providers **257 →258**. The original
3,159B renderer quad submit Boss **calls this entire strict-exact state
method once**, as well as the separately exact 352B append and real
45B/35B color math, but its own parent still produces a different
3,796B/973-instruction C++ body from the original 3,159B/763 x86.
The 5,993B Animation draw and 12,140B Bullet command parent bosses
also remain separately NONEXACT, not recredited by this exact child.
