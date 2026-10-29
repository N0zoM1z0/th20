# CORE/RECON-793 — three original 97B Animation renderer quad modes, all whole-native strict exact

The immutable original TH20 Japanese v1.00a Steamless PE has whole-file SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
This checkpoint closes **three genuinely distinct, complete original 97B
Animation renderer methods /291 disjoint game .text bytes** from the 5,993B
`0x00443880` Animation draw Boss's original **49-mode switch**. Each method
has its own 32 original x86 instruction heads and complete original `ret 4`,
and has **four authentic original PE HIGHLOW fields** plus **two physical
original native E8 calls**. The enclosing 5,993B Boss remains
**SOURCE-ABSENT/NONEXACT**, not 5,993 bytes of newly matched gameplay.

## Original immutable call sites, modes and vertices

| 5,993B parent mode | Whole native child | Original setup E8 target | Original submission E8 target, argument | Physical native method |
| --- | --- | --- | --- | --- |
| 0 | `0x0043F550`, **97/97B** | `0x0043EB40` | `0x0043F6A0`, mode 1 | `draw_quad_mode0` |
| 1 and 3 | `0x0043F630`, **97/97B** | `0x0043EF20` | `0x0043F6A0`, mode 0 | `draw_quad_mode1` |
| 2 | `0x0043F5C0`, **97/97B** | `0x0043EB40` | `0x0043F6A0`, mode 0 | `draw_quad_mode2` |

The original four vertex-address arguments to the setup call are the
physical `SpriteTexturedVertex[4]` array at original PE address
**`0x005AEF10`**, with genuine 28-byte spacing: the native executable
uses the original `0x1C*3`, `0x1C<<1`, `0x1C<<0` and `0x1C*0` indexed
address-generation operations. Its original data occupies **112 bytes**
starting at the same real native base. This is neither an arbitrary raw
pointer table nor a 24-byte `SpriteWorldTexturedVertex` layout; the
maintained `SpriteTexturedVertex` has an independent `sizeof ==28` proof.
Each original `setup_quad` E8 receives four distinct pointers to this
array with the original argument order, and the subsequent original E8
passes the actual `Animation*` with one selected integer submission mode.

For **each** of the three complete methods, the independently verified
COFF/native original relocation field identities are:

- offsets `+0x11`, `+0x1F`, `+0x2D`, `+0x3C` are four genuine original
  `IMAGE_REL_BASED_HIGHLOW` locations in the physical PE `.reloc` section.
  Every one points to real original `0x005AEF10` array base, with native
  x86 instructions generating each separate 28-byte element offset;
- offset `+0x49` is the actual signed original `E8` `REL32` operand to
  either `0x0043EB40` or `0x0043EF20`, depending on mode;
- offset `+0x57` is the actual signed original `E8` `REL32` operand to
  `0x0043F6A0` for all three modes. This is an original native call,
  not a claim that the separate 3,159B submission callee is source-exact.

The full original `0x00443...` selected case-to-wrapper callsite map is
separately verified by the source-independent
[49-mode PE CFG](ANIMATION_DRAW_BOSS_49_MODE_ORIGINAL_E8_CFG.md) and its
[49-row table](../config/animation-draw-boss-mode-e8.csv). The
[draw-Boss original PE verifier](../scripts/verify-animation-draw-boss-native.py)
now independently confirms all 18 native fields across these three
functions, all four live caller modes, the entire physical array region
and all complete method boundaries, in addition to the enclosing 5,993B
Boss's full 123 E8/49+31 switch/32 PE HIGHLOW census.

## Complete maintained C++, ABI, and limited validation

The maintained `src/AnimationDrawQuadModes.cpp` has three natural C++
`__thiscall` receiver methods with the actual `Animation*`, four typed
`SpriteTexturedVertex*` addresses and actual integer draw mode. A locally
named `AnimationDrawModeOwner` derives from the existing opaque
`AnimationPoolOwner`, solely to retain the native receiver ABI and
method declarations **without** changing the public owner layout or
requiring recompilation of its many accepted C++ users. It has no new
instance, data members, duplicate runtime manager, fabricated ABI
adapter or target-byte patch. Historical spelling of these internal
method and owner types is not established by x86 evidence; their
**original physical addresses, behavior and receiver calling conventions**
are established. The declaration for original shared vertex array is
an **external** symbol mapped through the actual native data relocation;
it is not a separately defined guessed global object in this checkpoint.

Pinned MSVC 19.44.35211 x86, `/Od /Ob0 /GS /Gy /Zl /arch:SSE2
/fp:precise /sdl /EHsc`, compiles exactly **one new** translation unit
and its accepted `build/core793-canonical/AnimationDrawQuadModes.obj`
with a canonical compiler receipt. The three original whole-native
functions pass **3/3 strict exact (97/97B each)**, including all 18
independently PE-verified relocation field kinds/offsets/targets and
zero additional mismatched bytes:

    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawQuadModes.cpp
    scripts/repo-python scripts/verify-animation-draw-boss-native.py

**Existing canonical compiler input changed: zero.** No original source
file, public header, compiler profile or old protected compiler receipt
was modified: only the one new provider with its three new canonical
strict units was rebuilt, never an unfiltered full cold replay. The
original 5,993B Animation draw Boss's entry/predicate/49+31 routing
remains a separate source-reconstruction task; these exact children do
not imply a valid whole-game link or playable original executable.

Authored strict original game code advances **577 →580 complete physical
functions**, **188,625 →188,916 bytes**; source-present mappings **1,222
→1,225**, canonical strict units **1,224 →1,227**, and distinct
canonical object/receipt providers **252 →253**. These are *physical*
whole original functions, not copies of a parent block or additional
code credit for the shared 112B `.data` vertex array.
