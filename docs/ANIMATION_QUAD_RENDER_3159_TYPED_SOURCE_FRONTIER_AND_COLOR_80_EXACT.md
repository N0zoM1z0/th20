# CORE/RECON-801/802 — whole 3,159B Animation quad renderer source frontier and 80B strict color arithmetic
> **Subsequent CORE/RECON-819:** The actual 2,725B/699-i386 texture/sampler-state backend called by the strict 26B wrapper is now **whole strict exact**, including all 107 native E8/HIGHLOW and ten original switch entries over 2,768B compiler extent. [Full original PE and canonical proof](ANIMATION_QUAD_TEXTURE_STATES_2725_STRICT_EXACT.md). The separate 3,159B quad submission parent remains SOURCE-PRESENT/NONEXACT; older counts below are historical.
> **Subsequent CORE/RECON-813:** Original 1,163B/343-x86 D3D9 texture-stage state machine called by this renderer at `0x0044015B` is now **whole-native exact**, including all 54 original E8/HIGHLOW COFF fields and the full original 4-entry jump table. [Whole original state machine proof](ANIMATION_QUAD_BLEND_STAGE_1163_STRICT_EXACT.md). This 3,159B parent remains independently NONEXACT; counts below are historical.

> **Subsequent CORE/RECON-806/807:** Full original six-vertex batch append (352B) and texture-state wrapper (26B) are now both whole strict exact from shared native ABI C++ and independently original PE; [352+26B full strict proof](ANIMATION_QUAD_BATCH_APPEND_352_AND_TEXTURE_PREPARE_26_EXACT.md). The parent 3,159B C++ remains NONEXACT; counts below were historical CORE802.
> **Subsequent CORE/RECON-808 current source revision:** [Independently verified full C++ game-call-role proof](../scripts/verify-animation-quad-submit-source-roles.py) now confirms **40/40 original gameplay E8 target identities and multiplicities across ten real native game functions**, including **24 saturating-color +4 divide-255 +4 pixel-snap +2 flush +1 new 352B append**. Original 41st call is the compiler-generated security-cookie check, which is **not** faked in C++. Replacing /Od-noninlined local wrappers with actual per-channel source operations produces a **3,796B/973 x86 executable candidate plus 20B five-pointer data =3,816B COFF**; original is **3,159B/763 x86**, with distinct original relocation sites. This is substantive call-graph coverage but **still NONEXACT, zero whole-parent byte credit**. Earlier 2,085B/558 i386 and 32-call measurements below describe the dated initial CORE/RECON-802 candidate only. The real 352B/26B strict children are also separately verified.

The immutable original Japanese TH20 v1.00a Steamless executable is verified
by SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint directly attacks a second significant original game-owned
renderer function, **`0x0043F6A0`, 3,159 bytes /763 true x86 instructions**,
called by the original three 97B draw wrappers and the 48B/142B mode
wrappers previously accepted strict exact from the 5,993B Animation draw
Boss. A **whole-method, natural typed C++ semantic implementation is now
present**, but its physical native body remains **NONEXACT**; no original
3,159-byte exact credit is asserted.

## Original entire function: independently attested real code and dispatch

The new `scripts/verify-animation-quad-submit-native.py` reads the locked
original PE, its real section headers and `.reloc` directory. The original
entire physical `0x0043F6A0..0x004402F6` method ends with original `ret 8`
at `0x004402F4`, and has **3,159 original .text bytes /763 genuine x86
instruction heads**. The body contains **41 original physical E8 calls to
11 distinct original target heads**, plus **96 actual
`IMAGE_REL_BASED_HIGHLOW` fields** inside the function. Those 96 refer to
10 original data-reference destinations, with original call/data roles
read independently of Ghidra's function names or our source/COFF target.

| Original direct E8 physical target | Original direct call count | Native role |
| --- | ---: | --- |
| `0x00445B80` | 4 | Float-coordinate rounding helper; CRT operation details still subject to independently exact ABI review |
| `0x00437CD0` | 1 | Real `Animation::sprite_data()` getter (already strict source) |
| `0x004455C0` | 2 | Fully exact 192B draw-batch flush, before device state changes |
| `0x00412730` | 1 | Real Graphics device pointer getter (a folded 17B native value helper) |
| `0x00445A00` | 1 | Original native texture resource lookup |
| `0x0043F520` | **24** | Newly **45/45B whole-native strict exact** game per-channel color saturation |
| `0x0043F4F0` | **4** | Newly **35/35B whole-native strict exact** game per-channel divide-255 blend |
| `0x00445BA0` | 1 | Native 26B wrapper invoking still-unsourced 2,725B texture-state setup |
| `0x00446690` | 1 | Native 1,163B draw/blend-mode state update |
| `0x0043E9B0` | 1 | Original 352B quad batch append into true 28B vertex stream |
| `0x005429EE` | 1 | Compiler security cookie check, **not authored gameplay byte credit** |

The real five-entry color-mode switch table begins immediately after the
native body and a genuine one-byte original NOP at **`0x004402F8`**.
Every original entry is a true `.reloc` HIGHLOW code pointer into the
same original function: the actual targets are **`0x0043FC47`,
`0x0043FC47`, `0x0043FDCC`, `0x0043FDCC`, `0x0043FF70`** for modes 0..4.
The body itself points to that real table, and all 96 body HIGHLOW
fields (including 23 to quad X base and 22 to quad Y base) are verified
from original immutable executable bytes. Do not mistake these after-body
20 data bytes for more x86 instructions.

A key re-review resolves a previously anonymous pointer **`0x005C5840`**:
this is exactly the real game global `process_graphics` at `0x005C4D40`
plus `Graphics::current_viewport` offset `0xB00`. The actual
`ViewportState::bounds_11c` and `bounds_124` are already typed `Vector2`
fields at +0x11C/+0x124; the original uses these as coarse clip limits
against the true four 28-byte `SpriteTexturedVertex` positions. The
source uses the existing typed members, with x86 compile-time offset
assertions, not a fabricated second graphics global/view owner.

## Two complete original game color routines strictly matched, no relocation

The 24-called `0x0043F520` body is **45 bytes, 15 native x86 instructions**.
It multiplies two original unsigned byte channels, shifts the product
right by 7 and caps any result 256 or above to 255, returning an unsigned
byte. The 4-called `0x0043F4F0` body is **35 bytes, 14 native x86
instructions**: multiply two bytes as a 32-bit integer, unsigned divide
by 255 and return the low byte. Both are genuine custom game graphics
helpers (not standard library code) with **zero COFF/PE relocation fields**.
The maintained natural C++ source `src/AnimationDrawColorMath.cpp` uses
these actual math operations, *not* approximations with floats or a
hardcoded code section. Their two canonical strict functions
`animation_color_128_saturating_45` and `animation_color_divide_255_35`
are accepted as two complete, distinct physical original .text bodies:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawColorMath.cpp

The bounded pinned MSVC 19.44.35211 i386 build `/Od /Ob0 /GS /Gy /Zl
/arch:SSE2 /fp:precise /sdl /EHsc` emitted **45/45B** and **35/35B**,
with **zero whole-native byte differences**, **2/2 strict units in one
new canonical object/receipt**. The original native source-independent
verifier checks all their 24/4 original E8 producer/consumer sites,
complete returns and absence of native relocation fields.

## Complete semantic C++ candidate for the 3,159B parent: still NONEXACT

The new `src/AnimationQuadSubmit.cpp` defines the existing ABI method
`AnimationDrawModeOwner::render_quad(Animation*,int)` already called by
five separate strict exact renderer methods. It uses real
`Animation`/`AnimationFile::SpriteData`/`SpriteTexturedVertex`/
`Graphics`/`ViewportState` types, original four-vertex coordinate
translation using owner+0xC8/+0xD0 and +0xCC/+0xD4, four conditional
integer-pixel rounding operations, original viewport clip boundaries,
true `SpriteData::texture_id`, draw-batch flushing before D3D9 texture
changes, original color modes 0/1/2/3/4 with alpha inheritance and
global tint, state preparation, native UV updates and final quad append.
Wide unresolved renderer-owner field offsets are accessed by constrained
typed byte views; there is no invented hundreds-of-megabytes padded
class. The original method's real typed public caller ABI remains
unchanged, and no existing shared header/old exact source was modified.

Under the same pinned compiler, the complete parent candidate compiles as
**2,108 COFF bytes**, but its executable body ends at its own real `ret 8`
after only **2,085 executable bytes /558 true x86 instruction heads**,
with **23 bytes of compiler color-switch pointer/alignment data** after
that return. The original body is **3,159B /763 actual x86**, followed
by the independent native five-pointer color table. The candidate's
local helper and lambda structure generates **32 direct COFF REL32 fields**
versus original **41 direct E8**, with different physical call sites,
argument lifetimes, branches and switch lowering. The exact CRT rounding
contract, some provisional renderer texture/state signatures and native
color-channel evaluation order still need precise codegen exploration.
Thus the parent C++ is **semantic source-present, `reconstructed`, strict
match 0%/NONEXACT**; it has no original unit in `config/matches.csv` or
`config/match-units.toml`, no original byte credit and no claim of a
linked executable. The exact 80B two color children do not make its
3,159-byte parent exact, just as the 5,993-byte enclosing draw Boss
is source-present but not whole-native exact.

## Scope and accountable progress

Compiler inputs changed: **only two brand-new C++ source files** and
new original-PE verifier/tracking/docs. The complete 3,159B source was
compiled in a disposable one-object probe, not promoted to canonical.
The two 45B/35B child units alone were strict canonical replayed from
**one new source/object**; existing old exact canonical source/header
inputs changed **zero**, so old cold replay scope is **zero**. No
full/unfiltered cold replay or binary patches were used.

Source-present mappings advance **1,228 →1,231** (two exact children and
one nonexact parent); original game-authored whole strict exact functions
**582 →584**, bytes **189,106 →189,186**; canonical strict units
**1,229 →1,231** from **253 →254** distinct canonical object/receipt
providers. The 3,159B quad submit and 5,993B Animation draw parent remain
NONEXACT, as do the separate 12,140B Bullet command, 41,967B Enemy ECL,
39,470B Animation VM giants. Original game-wide playability is not proven.

Reproduce only the affected source and original PE:

    scripts/repo-python scripts/verify-target.py
    scripts/repo-python scripts/verify-animation-quad-submit-native.py
    nice -n 15 scripts/compile-probe.sh src/AnimationQuadSubmit.cpp build/core802-probe/AnimationQuadSubmit.obj /nologo /c /std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl /EHsc
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawColorMath.cpp
    scripts/repo-python scripts/validate-tracking.py --require-target
