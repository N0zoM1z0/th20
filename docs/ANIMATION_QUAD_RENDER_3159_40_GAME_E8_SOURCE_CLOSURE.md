# CORE/RECON-808 — all forty game-call roles recovered in maintained 3,159B quad submission Boss C++ (NONEXACT)

> **Subsequent CORE/RECON-813:** The original separate 1,163B quad-renderer four-mode D3D9 state child at 0x00446690 is now independently whole strict native exact, including original after-RET four-pointer table and 54 PE/E8 fields. See [full 1,163B native exact proof](ANIMATION_QUAD_BLEND_STAGE_1163_STRICT_EXACT.md). This does not make the 3,159B parent exact; counts below describe the earlier CORE/RECON-808 snapshot.

> **Subsequent CORE/RECON-809/810:** Original 60B texture lookup is strict exact; its real `std::array<AnimationFile*,42>::at` 34B plus `_Xran` 16B (not the old Ghidra 13B guess) are two further whole strict STL methods, excluded from game authored byte credit. [Three native exact functions and original PE proof](ANIMATION_TEXTURE_LOOKUP_60_STL_ARRAY_34_16_EXACT.md). Earlier totals remain historical; parent still NONEXACT.

> **Subsequent CORE/RECON-809/810:** The original 60B texture-lookup callee is now strict exact, along with its separate **34B checked std::array::at STL helper**; the 34B method is excluded from authored game code credit. [Original native 60B+34B exact evidence](ANIMATION_TEXTURE_LOOKUP_60_AND_STL_ARRAY_34_STRICT.md). The quad parent remains NONEXACT; this older checkpoint's call-role totals are not the newest exact inventory.

Locked original: Japanese TH20 v1.00a Steamless, SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
The real original **`0x0043F6A0` 3,159B/763 x86** game-owned
`AnimationDrawModeOwner::render_quad(Animation*,int)` is now source-present
with a maintainable complete typed C++ candidate. This checkpoint
substantially improves its own 40-game-call E8 graph: **every one of the
40 original direct game E8 roles, all ten real physical game callees
and each callee's exact multiplicity** is reproduced by the new pinned
MSVC C++ `REL32` call relocation graph. The 41st original E8 is the
separate CRT/compiler **security-cookie check `0x005429EE`**; this is
not invented or inserted as a meaningless source call.

## Entire original native graph, independently attested

Two original PE-first verification scripts independently lock the entire
original 3,159-byte/763-instruction physical extent,
**41 native E8 /11 actual destinations**, **96 genuine in-body PE HIGHLOW
fields /10 physical absolute destinations**, the five original
`IMAGE_REL_BASED_HIGHLOW` color-mode pointers at `0x004402F8` (after the
original genuine `ret 8` and one alignment NOP), original 4x28B sprite
vertex data at `0x005AEF10` and real global graphics viewport
`0x005C5840 == process_graphics +0xB00`:

    scripts/repo-python scripts/verify-animation-render-quad-native.py
    scripts/repo-python scripts/verify-animation-quad-submit-native.py

The source is no longer silently hiding four per-color original native
calls inside a separate compiler helper function. For the actual
`AnimationDrawColorChannels` byte layout, the maintained C++
`src/AnimationQuadSubmit.cpp` explicitly uses original per-channel
integer math at all four bytes per color, applying actual custom
`multiply_color_128_saturating` / `multiply_color_255` on those bytes.
The helper emission can still have differing expression order and
`std::uint32_t` temporary lifetimes from the original, but actual
*game-call target counts* are equal to the original immutable original PE:

| Original native target | Original E8 count | Maintained C++ COFF REL32 count | Origin/role |
| --- | ---: | ---: | --- |
| `0x00445B80` | 4 | 4 | Genuine per-coordinate snap/round wrapper; currently provisional `animation_snap_round`, not falsely named compiler intrinsic |
| `0x00437CD0` | 1 | 1 | Typed original `Animation::sprite_data()` |
| `0x004455C0` | 2 | 2 | Already strict-exact 192B draw-batch flush |
| `0x00412730` | 1 | 1 | Original folded real Graphics device getter |
| `0x00445A00` | 1 | 1 | Original renderer-owned texture lookup |
| `0x0043F520` | **24** | **24** | Whole strict-exact custom original 45B color multiply/saturate |
| `0x0043F4F0` | **4** | **4** | Whole strict-exact custom original 35B color multiply/255 |
| `0x00445BA0` | 1 | 1 | Newly strict-exact 26B texture-state wrapper, original E8 to still-unsourced 2,725B backend |
| `0x00446690` | 1 | 1 | Still-unsourced original renderer state update |
| `0x0043E9B0` | 1 | 1 | Newly strict-exact 352B six-vertex batch append |
| `0x005429EE` | 1 | **0** | Compiler-only security-cookie check, excluded from 40 game calls and authored byte credit |

The whole original **3,159B submission body remains NONEXACT**, even
though all ten game direct-call targets are represented with exactly
correct target multiplicities. This call graph validation does **not**
prove physical E8 callsite offsets, argument value order, original
exception/security frame, original HIGHLOW relocations or source-level
historical spelling for all provisional backends.

## Correct compiler extent: 3,796 executable bytes, not a fabricated partial match

The original compiler/PE produces the real **3,159B/763 true x86**
function. The current one-object MSVC 19.44.35211 x86 candidate from
`src/AnimationQuadSubmit.cpp` has **3,816B complete COFF contribution**,
which comprises **3,796B/973 genuine executable x86 instruction heads**
ending at its actual `ret 8`, followed by the separate **20B of five
compiled color-mode switch table data**. Do **not** treat these five
`DIR32` data pointers as 20 additional bytes of executable code, or
accept a 3,159-byte prefix from a longer original C++ contribution.
This replaces the earlier 2,108B/558-x86 candidate from CORE/RECON-802,
which had only 32 direct COFF E8 references because compiler-generated
channel combination helpers hid multiple actual original calls.

The source-specific independent narrow check
`scripts/verify-animation-quad-submit-source-roles.py` now compiles
only this one source file under pinned MSVC and checks the complete
40/40 `REL32` roles by actual COFF symbol and target, all 10/10 game
callee identities, the original 24+4 channel operations, four genuine
snap and two draw-flush calls, actual five color-mode branches, and the
true before/after RET switch table boundaries. It deliberately reports
**NONEXACT 3,796 executable vs original 3,159**. There is no 3,159B
canonical exact match entry or original parent bytes credited in ledgers.

## Other strict child improvements from same original call graph

The original 352B/98-i386 batch append, implemented by natural 28-byte
array-address indexing and six `rep movsd` 7-dword copies, is separately
fully strict exact. The original 26B/12-i386 texture-state wrapper
with one E8 to original `0x00445BC0` is also independently whole exact.
Both share a single provisional but ABI-compatible
`AnimationQuadSubmitOwner` C++ declaration from
`src/AnimationQuadSubmitOwner.hpp`, used also by the noncanonical
3,159B parent. The two other exact original color helpers at 45B/35B
remain separate protected canonical units. The 352+26B native proof
and accepted two-object strict replay are in
[CORE/RECON-806/807](ANIMATION_QUAD_BATCH_APPEND_352_AND_TEXTURE_PREPARE_26_EXACT.md).
Neither original 3,159B renderer parent nor its 5,993B Animation draw
caller is now byte exact or linked. This checkpoint establishes *source
coverage and exact game E8 role coverage*, not finished executable linkage.

## Narrow build scope and current totals

One private source compiler probe, two new canonical exact leaf source
objects and only the existing original PE verifiers were run. No
previously protected old compiler source/header was changed. The exact
changed-only cold replay covers **only the two new source objects**, no
unfiltered all-repository cold replay:

    nice -n 15 scripts/repo-python scripts/verify-animation-quad-submit-source-roles.py
    nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationQuadBatchAppend.cpp --source src/AnimationTexturePrepare.cpp
    scripts/repo-python scripts/verify-animation-quad-submit-native.py
    scripts/repo-python scripts/validate-tracking.py --require-target

The new two physical original exact methods add **378B**, yielding live
**586 original game-authored whole physical strict functions /189,564
native bytes**, **1,233 source-present mappings /1,233 strict units**
from **256 canonical objects/receipts**. The 3,159B renderer parent
receives **zero additional original exact bytes** despite its stronger
40/40 game-call graph and improved typed source.
