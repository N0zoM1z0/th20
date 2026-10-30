# CORE/RECON-840 — complete original 1,996B Animation renderer mode7 preparation, strict exact

The original locked Japanese TH20 v1.00a Steamless executable (SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
contains a complete game-owned Animation renderer preparation method at
**`0x00441430`**. Its original source symbol spelling is not known;
`AnimationDrawDetailedOwner::prepare_simple_mode7(Animation*)` is a
semantic reconstruction name sharing the real receiver ABI with its
already whole-strict 753B mode7 caller at `0x00441C00`. The same original
head is also invoked by the previously strict 142B mode5 wrapper under a
provisional `prepare_quad_mode5` name; **this is ONE physical game function,
credited only once**.

The **whole 1,996B original native body /459 real x86 instruction heads**,
with original **`sub esp,0xCC`** stack and `ret 4` with `EAX=0`, is now
source-backed and strict native exact via ordinary
[`src/AnimationDrawMode7Setup.cpp`](../src/AnimationDrawMode7Setup.cpp).
The original input/return contract was recovered from physical instructions,
not the previous provisional void-return declaration. The shared receiver
header was updated to the proper integer-returning ABI without changing the
native code generated for its 753B caller.

## Immutable PE and full canonical proof

The [original-only verifier](../scripts/verify-animation-draw-mode7-setup-native.py)
independently extracts the locked complete PE .text, disassembles **459
native heads**, parses the real `.reloc` directory, and attests **all 11
physical E8 sites and all 26 PE HIGHLOW sites and targets**. These target
roles were declared independently of source output. The new canonical
`animation_draw_mode7_setup_1996` manifest records precisely the actual
**37 COFF relocations**: symbol, offset, type, independently attested
original destination and real object addend. Strict replay verifies every
relocated byte and every other original instruction byte without shortening
the function extent:

```text
animation_draw_mode7_setup_1996: exact (1996/1996 bytes)
Exact replay: 1/1 units, 1 cold objects
```

| Original PE evidence | Verified source reconstruction |
| --- | --- |
| 1,996B /459 i386, frame 0xCC, one integer return and `ret 4` | Exactly **1,996/1,996B** whole strict exact |
| Two E8 to `0x0040BDA0` at `+0x1E`, `+0x29` | Natural 64B `TransformMatrix` default construction, original order and stack locations |
| E8 to `0x00437770` at `+0x111` | Existing game-authored exact `Animation::rotation_sum()` |
| Three D3DX X/Y/Z rotation E8 to `0x00540684/8A/90` | Real imported D3DX matrix rotation functions with original signed float arguments |
| Three D3DX matrix multiply E8 to `0x0054067E` | Genuine in-place 64B Animation transform accumulation |
| Iterator E8 to `0x0040BC20` at `+0x50D` | Four natural 12B `Vector3` locals, real constructor pointer `0x00422E10` |
| Security-check E8 to `0x005429EE` at `+0x7C1` | Original compiler cookie, not authored code |
| 26 PE HIGHLOW data sites | **26/26 original field offsets/targets exact** |

The native original 26 data references consist of **three real double
zero constants** at `0x0056CD50`; **two shared `2.0f`** at `0x0056C8D0`;
**one `448.0f`** at `0x0056D7C0`; actual
`WindowState` dimensions at `0x005B87F8/FC`; the original four signed
world-axis bounds **`+/-128` and `+/-256`**, each repeated four times;
one original physical Vector3 construction function pointer at
`0x00422E10`; and a real security cookie at `0x005B25C0`. No fake
literal pools, copied PE bytes, or fabricated constants were used.

## Corrected source-level behavior

1. Two distinct 64B transform matrices are *constructed* in the original
   local lifetime order: the destination projection at `[ebp-0x80]` is
   constructed **before** the 64B rotation temporary at `[ebp-0xC0]`.
   Changing only their source declaration order corrected real original
   constructor E8 sites, without inventing compiler-shaping locals.
2. The original checks the `Animation+0x49C` bit26 via `SHR` and `AND`,
   then copies all 16 float words from base matrix `+0x3B8` to
   Animation `+0x57C`, applies two independently ordered scale products,
   clears an actual state bit, obtains the complete recursive rotation
   vector, and conditionally rotates the matrix about X/Y/Z using three
   genuine D3DX import pairs. Double zero comparisons use the original
   native constant and flag behavior.
3. The prepared 64B projection matrix is copied to the local projection,
   then real animated XY translation is accumulated. The screen/viewport
   offset path uses *actual* WindowState scaled dimensions, 448.0f and
   native 2.0f. The original Z translation is a **fresh assignment** of
   its three Animation position sources, not an addition to a stale
   matrix translation; this corrected a previous guessed behavior.
4. If the original Animation has an active parent at `+0x55C` with bit12
   clear, each XYZ translation receives the three parent Animation fields
   in physical order. Re-reading the real parent pointer per original
   occurrence reproduces native register lifetimes without a fake owner.
5. Four genuine Vector3 corner locals are constructed and their X/Y
   bounds are selected through two native value switches for mode values
   **0, 1/default, 2**. The physical original source branch order is
   `default/case1`, `case0`, `case2`, not a compact ascending case map.
   The corrected ordinary switch statements produce all original
   constant references and jump positions. All four Z coordinates are
   genuinely zeroed; the original local corner construction and
   stores are retained even though their later consumer is not visible
   in the same PE body.
6. All 64B of the prepared local matrix are copied to the actual renderer
   receiver at **`this+0x60007D8`**, then the original EAX-zero/`ret 4`
   ABI returns success. A provisional void-return signature previously
   emitted a function two bytes shorter; the real `return 0` is a
   semantic correction, not extra padding.

The remaining 5,993B parent Animation draw dispatcher is **NONEXACT**,
although its complete machine-code size and two real switch tables are
already recovered. The 753B mode7 consumer remains independently strict
exact, and `src/AnimationDrawMode7Setup.cpp` is the **single** natural
implementation for this original physical preparation function.

## Focused regression scope and current credited progress

The only new native compiler source is the complete mode7 preparation
implementation; its one new object/receipt and canonical unit were
cold-built and replayed. Its return type also changed the previously
accepted mode7 caller's *C++ symbol*, so the existing 753B caller was
**separately cold rebuilt and replayed with the updated manifest REL32
symbol**. No other formerly exact source/header/manifest provider changed.
Do not run an all-units cold replay.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-mode7-setup-native.py
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7Setup.cpp
nice -n 15 scripts/repo-python scripts/replay-exact-units.py --source src/AnimationDrawMode7.cpp
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
```

This adds **one game-authored original function, 1,996 distinct original
.text bytes, one source mapping, one canonical unit and one new source
object**, not another credit for its folded matrix constructor or for
D3DX/runtime import code. Current game-authored strict exact totals become
**597 complete physical functions /199,566 native bytes**, with **1,243
source-present mappings, 1,244 strict units and 263 canonical object
providers**. All counts are based on the actual ledgers, not historical
dated handoff snapshots.
