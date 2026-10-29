# CORE/RECON-801 — original 3159B Animation quad renderer: 80B exact color math and native whole-function audit

> **Subsequent CORE/RECON-802:** The entire original 3,159B renderer quad submit parent now has one maintained, typed, compiling C++ candidate, but remains **NONEXACT** (2,085 executable C++ bytes/558 x86 vs 3,159 original/763). [Current whole-source proof and 80B strict exact children](ANIMATION_QUAD_RENDER_3159_TYPED_SOURCE_FRONTIER_AND_COLOR_80_EXACT.md). Old SOURCE-ABSENT labeling and totals below describe this earlier CORE801 checkpoint only.

Target is the immutable Japanese TH20 v1.00a Steamless executable,
SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint independently audits **the entire original 3,159B /763 x86
renderer submission function at `0x0043F6A0`** and admits two distinct
complete custom game functions used by it, totaling **80 disjoint original
`.text` bytes**. The 3,159B parent remains **SOURCE-ABSENT and NONEXACT**;
no partial-byte or parent exact credit is awarded.

## Original physical color methods and actual call graph

| Original head | Entire native function | Original call sites in 3159B parent | Original x86 arithmetic |
| --- | ---: | ---: | --- |
| `0x0043F520` | **45/45B, 15 x86** | **24** E8 | Unsigned byte channels multiplied, `>>7`, saturated at `255` when `result >= 256`, return low 8 bits |
| `0x0043F4F0` | **35/35B, 14 x86** | **4** E8 | Unsigned byte channels multiplied, unsigned integer division by `255`, return low 8 bits |

They are separate game-owned renderer channel-compositing operations,
not interchangeable normalization rules. `multiply_color_128_saturating`
and `multiply_color_255` are provisional maintained source identifiers,
not claims of the original historical method names. Both natural, typed
`std::uint8_t` `__cdecl` implementations live together in the maintained
`src/AnimationDrawColorMath.cpp`. The original native 45B body uses an
unsigned `jb` and cap at `0xFF`; its 35B counterpart uses `xor edx,edx`,
`mov ecx,0xff`, and unsigned `div ecx`. These are not decompiler-derived
floating-point approximations.

Both original entire functions have **zero genuine original PE relocation
fields**, and the pinned MSVC 19.44.35211 x86 compiler `/Od /Ob0 /GS /Gy
/Zl /arch:SSE2 /fp:precise /sdl /EHsc` generates **all 45/45 and 35/35
original bytes, 15/15 and 14/14 instruction heads**, respectively. There
are no guessed relocation symbols or omitted original return instructions.
A single new source/object provider
`build/core801-canonical/AnimationDrawColorMath.obj` passes
**2/2 whole-function strict canonical replay**:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawColorMath.cpp
    scripts/repo-python scripts/verify-animation-render-quad-native.py

## Rechecking the genuinely large 3159B renderer parent

Rather than trusting previous pseudocode, the new
`verify-animation-render-quad-native.py` independently reads the original
immutable PE and its `.reloc` section. It confirms the entire
`0x0043F6A0..0x004402F6` **3159B /763 real x86** body, the actual final
`ret 8`, **41 actual physical direct E8 call sites /11 distinct
original call targets**, and **96 original `IMAGE_REL_BASED_HIGHLOW`
fields /10 distinct original absolute targets**, including the true
original exception handler field. The accepted 192B draw flush is directly
called twice; the original four float-coordinate snap/round calls,
texture lookup and four grouped color blend operations are native machine
code, not accepted parent source. Original shared vertices start at the
real `0x005AEF10` and are 28 bytes per record; the separately physical
`0x0056E0EC` float literal is exactly `0.5f`.

Call multiplicities in that actual 3159B function are:

| Original physical E8 destination | Calls | Role/acceptance |
| --- | ---: | --- |
| `0x0043F520` | 24 | new whole strict color multiply/saturate |
| `0x0043F4F0` | 4 | new whole strict byte multiply/divide-255 |
| `0x00445B80` | 4 | original float position rounding helper; acceptance not claimed here |
| `0x004455C0` | 2 | already whole strict 192B draw-queue flush |
| `0x00437CD0`, `0x00412730`, `0x00445A00`, `0x00445BA0`, `0x00446690`, `0x0043E9B0`, `0x005429EE` | 1 each | other original game/compiler call roles, not silently recredited |

All 41 calls and all 96 original data reference fields are checked against
the *original* PE, including individual target multiplicities. In
particular the 24+4 original color calls are not inferred merely from
the existence of a new compiler object.

## Accurate boundary and impact

Only a new original-game translation unit, the exact match/origin tracking
records, native evidence and docs were touched. Existing public headers,
old compiler profiles and the accepted 582 original game functions were
not modified. Actual replay scope was **one new source/object, 2 new strict
units**, with **zero existing canonical units to rebuild**. No
unfiltered full cold replay was run. The true original 3,159B parent
is still unimplemented and its own 763 instruction/96 relocation closure
must be reconstructed as a whole before any parent code can be credited.

Live accepted coverage advances **582 →584 distinct original game
functions, 189,106 →189,186 game code bytes**, source present **1,228
→1,230**, canonical units **1,229 →1,231**, and protected canonical
object/receipt providers **253 →254**. The separate 5,993B Animation
mode-dispatch parent remains SOURCE-PRESENT/NONEXACT and its 12,140B
Bullet command counterpart remains SOURCE-ABSENT/NONEXACT.
