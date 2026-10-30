# CORE/RECON-831 — 3,159-byte renderer quad submit: original-length and all 41 E8 site convergence (NONEXACT)

This checkpoint re-examines the **original locked Japanese TH20 v1.00a Steamless**
PE at `0x0043F6A0` (SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`),
independently of the earlier reconstruction notes. The entire native parent has
**3,159 executable bytes /763 i386 instruction heads**, one after-RET NOP and
five 32-bit switch table entries. Its maintained source is
`src/AnimationQuadSubmit.cpp`. **The original parent remains NONEXACT**;
no canonical match unit, original-game exact count, or accepted exact byte
credit is added by this source revision.

## Independently original-attested anchors and new pinned-MSVC candidate

| Full original PE fact | Current isolated pinned-MSVC C++ evidence |
| --- | --- |
| 3,159B executable /763 genuine x86 | **3,159B /763** from one whole `render_quad` definition |
| 41 native `E8` call sites: 40 game, one compiler security | **41/41 source roles AND 41/41 exact physical relative instruction offsets** |
| 96 original in-body PE HIGHLOW fields, ten physical target classes | **96/96 target multiplicities; 89/96 exact offset-and-target pairs** |
| 16 viewport COMISS comparisons, 13 `JBE`/3 `JA` | **16/16 original branch mnemonic sequence and operand orientation** |
| One NOP at original offset `+0xC57`, five table fields at `+0xC58..+0xC6B` | **Same NOP and five relocation positions; whole COFF contribution 3,180B** |
| Stack `sub esp, 0x54`, original register and UV instructions | **Still mismatched:** candidate `sub esp, 0x4C`; other code/operands differ |

For comparison, the previous [CORE/RECON-829 source frontier](ANIMATION_QUAD_RENDER_3159_41_E8_96_HIGHLOW_TYPED_SOURCE_FRONTIER.md)
compiled to **3,212B /810 x86 plus 20B table**, with 41 E8 role counts
and 96 HIGHLOW target counts but not their actual sites. The revised
candidate removes 53 executable bytes and 47 instruction heads, while
recovering native control flow and correcting genuine source behavior.
This is **structural convergence, not native byte equality**.

The original-PE verifier `scripts/verify-animation-quad-submit-native.py`
reads the original executable and its actual PE `.reloc` directory without
consulting the candidate. The focused
`scripts/verify-animation-quad-submit-source-roles.py` recompiles only this
NONEXACT source and compares its whole generated COFF contribution, exact
E8 *locations* and targets, complete PE HIGHLOW target histograms, physical
site intersections, clip branch sequence, and after-RET jump-table placement.
No manifest provider or shared header was changed.

## Source corrections derived from original x86, not dated hypotheses

1. **Clip path and unordered floats.** Sixteen original clipping compares
   load the real viewport field `Graphics+0xB00` independently. The first
   eight compare the lower viewport boundary against quad coordinates; the
   second eight compare the quad against the upper bounds. Real original
   `COMISS`/`JBE` allows unordered comparisons to pass. The previous
   `>=`/`<=` expressions compiled with the reverse operands and `JAE`,
   silently changing NaN behavior. The source now uses genuine
   `!(lower > vertex)` / `!(vertex > upper)` conditions, with an early
   offscreen return. The resulting 16 ordered `COMISS` plus branches are
   all in the correct physical order, including the original short local
   failure branch and `xor eax,eax; jmp` return path.
2. **Packed colors and native switch layout.** Hoisting inherited/tint
   flags and copying colors through extra 32-bit temporaries introduced
   differences in `/Od` machine code. Color mode is read from the actual
   Animation bitfield at each native read; the parent bit-24 check uses its
   existing typed bitfield. Packed RGBA channel values are modified in
   their actual four-byte union. Live renderer tint channels are read from
   the original owner offset directly. The `do/while(false)` macro form
   was also emitting dead `xor`/conditional branches under native `/Od`;
   regular compound statements remove these artificial loops. Putting the
   C++ `default:` case before mode zero restores the native short jump to
   the default branch and the five-pointer mode dispatch arrangement.
3. **Texture cache and material transition.** The original reads renderer
   cached texture and ready fields directly at `+0x6000E08` and
   `+0x6000E0E`; copying their *addresses* to stack aliases added unrelated
   instructions. Typed direct field reads recover the original two
   flush-call sites, native device acquisition, texture lookup and source
   instruction layout without creating a fake receiver or ABI wrapper.
4. **UV index/ordering error in prior source.** The original native `8`
   byte stride / shift-zero accesses in UV generation load
   `AnimationBase::vectors_378[1]`, **not `[2]`**, for output vertices 2
   and 3. The previous source used `[2]` and therefore read the wrong
   original animation coordinates. Both base UV reads now use `[1]`;
   output V1 is also stored before V2 as in the native sequence. The
   two corrected index shifts each add one genuine instruction byte,
   aligning the final two E8 call offsets.
5. **Render-color state selection.** The original uses a byte-mode
   bitfield and a byte-valued `mode != 3 ? 0 : 3` expression. Removing an
   extra promoted integer temporary recovers the native branch order and
   original single-byte temporary width in the final state transition.

The physical E8 offsets for all four snap calls, texture acquisition, both
flushes, device/lookup calls, all 28 color math calls, both state methods,
quad append and compiler cookie **now agree exactly** with the immutable
original native E8 instruction offsets. All 96 in-body HIGHLOW target
multiplicities still agree. Of their *site-and-target* pairs, 89 match;
the remaining seven original references are all to the actual original
quad U/V fields and occur at offsets `+0xB45`, `+0xB67`, `+0xB77`,
`+0xBA3`, `+0xBC6`, `+0xBD5`, and `+0xC01`. Candidate source fields sit
one or two bytes later. This is residual **codegen/layout debt**, not
missing native data owners.

An additional private provisional relocation-applied whole-code diagnostic
under `.analysis/core831-quad-byte-diff.py` observes **2,838 identical
bytes /3,159 (89.84%)**. That diagnostic maps COFF symbols to independent
original PE physical targets; it is not a canonical replay receipt.
The first differing raw instruction is already at offset `+0x5` (`sub esp,
0x54` vs `0x4C`), and substantial original UV expression/register-order
mismatches remain. Equal lengths, counts, call offsets and jump-table
positions do **not** establish a whole exact match.

## Focused reproduction and next native work

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-quad-submit-native.py
nice -n 15 scripts/repo-python scripts/verify-animation-quad-submit-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/build.py --check
```

The isolated compiled source receipt and COFF live at
`build/core831-probe/AnimationQuadSubmitRoles.{obj,receipt.json}`.
The prior `build/core829-probe/AnimationQuadSubmitRoles` evidence remains
preserved. Native exact replay scope is **zero**: this parent is not yet a
canonical match unit, and no currently exact source/header/profile/manifest
input changed. Do not run an all-unit cold replay for this checkpoint.

Next: re-evaluate original receiver and packed-local lifetime to solve
`0x54` versus `0x4C` frame shape, then reconcile the seven UV
relocation-site differences and the remaining instruction/register bytes.
Only a full canonical zero-difference replay of independently proven
relocation ownership can promote this original 3,159B parent to exact.
