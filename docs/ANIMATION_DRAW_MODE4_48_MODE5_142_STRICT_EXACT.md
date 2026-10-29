# CORE/RECON-796 — entire native mode-4 48B and mode-5 142B Animation draw paths strict exact

> **Subsequent CORE/RECON-800:** The whole 5,993B Animation draw parent now has one maintained, compilable 49-mode C++ candidate and a 123/123 source/native E8 target-role census. It is **SOURCE-PRESENT but NONEXACT** (5,141 actual compiled instruction bytes vs 5,993 original). [Current whole-parent evidence](ANIMATION_DRAW_BOSS_5993_TYPED_49_MODE_PARENT_FRONTIER.md). Earlier SOURCE-ABSENT labels below were accurate only at this dated checkpoint.

Locked original Japanese TH20 v1.00a Steamless SHA-256:
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
After the earlier [three complete original 97B quad wrappers](ANIMATION_DRAW_QUAD_THREE_97B_STRICT_EXACT.md), this checkpoint
closes **two more distinct entire native game-owned functions** reached
from the **5,993-byte/49-mode Animation draw Boss**. The new accepted
C++ methods share the **same existing source/object provider**
`src/AnimationDrawQuadModes.cpp`, under the same local receiver ABI.
The original giant parent itself remains **SOURCE-ABSENT and NONEXACT**.

## Two original complete functions, new native source contracts

| Parent mode | Actual original head | Original full code | Real source behavior |
| --- | --- | ---: | --- |
| 4 | `0x00440310` | **48/48B, 20 original x86** | Call original 32-bit **integer** guard `0x00440340` with `Animation*`; on a nonzero return propagate the original `-1` failure path, otherwise return actual `render_quad(animation,0)` from `0x0043F6A0` |
| 5 | `0x004413A0` | **142/142B, 34 original x86** | Perform genuine geometry preparation `0x00441430`; save real result of `render_quad(animation,0)`; update **four actual `SpriteTexturedVertex::reciprocal_w` members** to the original 1.0f, in native vertex order **3,2,1,0**; return the saved original render result |

The original mode-4 `0x00440310` contains exactly two real E8 relocation
fields, **`+0xF →0x00440340`** and **`+0x26 →0x0043F6A0`**. The
natural `bool` return candidate for the first helper emitted a spurious
`movzx`, proving the previous inferred guard type wrong. Declaring the
genuine opaque native helper as **`std::int32_t`** and using the natural
`if (guard(animation)) return -1; return render_quad(animation,0);`
recovers **all 48 bytes and 20 instruction heads**, including the original
unconditional short jump at the end of the failure path. A gratuitous
`else` would instead add two bytes; that hypothesis was rejected by the
locked original PE, not patched with assembler.

The original mode-5 `0x004413A0` contains exactly **ten** independent
original relocation fields: two signed E8 targets at **`+0x11 →0x00441430`**
and **`+0x1F →0x0043F6A0`**, plus **eight actual
`IMAGE_REL_BASED_HIGHLOW`** fields. Four refer to the immutable original
1.0f literal **`0x0056C8CC`**, and four are the real four-vertex
**`SpriteTexturedVertex`** buffer's `reciprocal_w` member at
**`0x005AEF1C`** (array base `0x005AEF10`, 28-byte stride,
member offset `+0xC`). The compiler emits the original `0x1C*3`,
`0x1C<<1`, `0x1C<<0`, `0x1C*0` x86 indexed addressing in native order.

The four COFF fields for those vertex member stores have actual
**relocation addend 12**: the manifest therefore correctly records
original **COFF symbol base `0x005AEF10`**, while immutable original PE
contains the effective **address `0x005AEF1C`** after applying the addend.
An initial manifest incorrectly used the *effective* PE address as a
symbol base and failed focused strict replay **138/142B**, despite an
otherwise full byte-identical candidate. This was caught and fixed by
examining the actual COFF addends and original PE HIGHLOW physical
addresses, **not** by changing original bytes or hiding relocation fields.
The subsequent canonical replay passes **142/142B strict**, all ten fields.

## Local scoped compiler replay, unchanged old programs, and counting

Pinned MSVC 19.44.35211 i386 `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc` compiles the one existing canonical source
`src/AnimationDrawQuadModes.cpp` to its existing protected
`build/core793-canonical/AnimationDrawQuadModes.obj` with a fresh strict
receipt. Actual affected pre-edit scope is **one canonical source/object
with the previous three 97B strict units**. All **five entire native
methods from this source** are now exactly reproduced:

    animation_draw_quad_mode0_97    exact 97/97
    animation_draw_quad_mode1_97    exact 97/97
    animation_draw_quad_mode2_97    exact 97/97
    animation_draw_quad_mode4_48    exact 48/48
    animation_draw_quad_mode5_142   exact 142/142

Reproduce with:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawQuadModes.cpp
    scripts/repo-python scripts/verify-animation-draw-boss-native.py

The source-independent PE verifier checks both actual parent mode caller
paths, complete return boundaries, all original E8s, eight genuine
HIGHLOW fields, original integer guard/real 1.0f member stores, while
still verifying the enclosing 5,993B Boss's **123 physical E8, 49+31
actual PE jump pointers and its 49 individually mapped mode paths**.
No public header, existing external method or compiler profile was
modified. There was **no all-repository/full cold replay**.

Strict original game authored whole functions advance **580 →582** and
original disjoint game .text bytes **188,916 →189,106** (+190B);
source-present mappings **1,225 →1,227**, whole canonical units
**1,227 →1,229**, protected canonical object/receipt providers remain
**253**. The original large 5,993B Animation draw, 12,140B Bullet
command, 41,967B Enemy ECL and 39,470B Animation VM parents remain
NONEXACT and whole-program linkage/playability are not asserted.
