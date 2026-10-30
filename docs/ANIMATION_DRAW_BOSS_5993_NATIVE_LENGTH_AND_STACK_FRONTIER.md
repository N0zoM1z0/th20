# CORE/RECON-835 — native-length 5,993B Animation Draw Boss / 0x204 frame (still NONEXACT)

This is a **fresh source-level convergence checkpoint**, not a strict native
admission. The independently locked Japanese TH20 v1.00a Steamless PE
(SHA-256 `a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`)
has one original complete `th20::AnimationPoolOwner::draw(Animation*)` body at
`0x00443880`, **5,993B /1,501 real x86 instructions**, original stack
`sub esp,0x204`, followed by a real **3B alignment sequence** and **49+31
PE HIGHLOW relocated code pointers**. The complete original code+table
comparison extent is **6,316 bytes**.

The maintained natural C++ `src/AnimationDrawBoss.cpp` now builds under the
pinned MSVC x86 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise
/sdl /EHsc` to a **5,993B /1,501-x86** real candidate body with exactly
**`sub esp,0x204`**, followed by **the same 3B alignment location and
80 true direct switch-pointer relocation positions**. The full candidate
COFF contribution is **6,316B**. Its original/source roles are attested by
the source-independent [locked-PE control-flow proof](../scripts/verify-animation-draw-boss-native.py),
[18-backend native ABI audit](../scripts/verify-animation-draw-boss-abi.py),
and a freshly built [source/PE comparison](../scripts/verify-animation-draw-boss-source-roles.py).

**It remains NONEXACT:** the generated i386 opcodes, local variables,
branch and relocation targets are *not* all equal. The C++ is **not** in
`config/match-units.toml`; it adds no credited original game code to
`config/matches.csv`. Exact body length, frame size and identical pointer
table positions are **structural evidence, not a zero-difference replay**.

## Independently checked full-original roles vs current candidate

| Whole native PE fact | Current single-method pinned MSVC candidate |
| --- | --- |
| 5,993B real executable body, 1,501 genuine i386 heads | **5,993B /1,501** |
| Prologue `sub esp, 0x204` | **Identical 0x204 frame size** |
| 49 original direct main case-pointer HIGHLOW and 31 nested pointers | **49+31 real COFF DIR32 at the same 80 physical offset positions** |
| 17 original primary mode-target aliases and 29 nested aliases | **17/29 pointer-target alias partitions**, identical for all 49/31 modes |
| 123 original real E8 /43 distinct true destination heads | **123/123 true target identities in their native physical order** |
| Original E8 physical instruction addresses | **86/123 exact E8 call-site locations** (first 81 consecutive; final compiler cookie also exact) |
| 32 original in-body `.reloc` HIGHLOW fields | **32/32 target-role multiplicities**; **23/32 physical site-and-target pairs exact** |
| Full code+3B alignment+80-pointer extent | **6,316/6,316 length**, not equal relocated machine code |

The scoped PE/COFF structural diagnostic excludes all 123+32+80 real
4-byte relocation fields when counting comparable original/candidate bytes.
**3,819 of 5,376 non-relocation bytes agree**; this is explicitly *not*
a canonical replay because 1,557 comparable bytes and nine in-body
absolute relocation sites still differ. A file-size coincidence cannot
be used to promote this parent to strict exact.

The 49 direct main and 31 direct nested pointer fields remain ordinary
compiler-generated jump-table data in the **same** function COFF contribution:
there is no private handcrafted switch array, manual padding or byte
patch. The full source still covers all 49 source mode values, 28 legitimate
nested backend modes, all 123 native call target roles and 18 independently
verified renderer backend stack contracts. The original whole-native exact
3,159B quad-submit Boss and its 20B C++ rounding wrapper are untouched.

## Newly verified per-mode argument evaluation order

Revisiting original native `COMISS`/E8/`fstp`/SSE operands rather than old
source records established why the earlier
[CORE/RECON-834](ANIMATION_DRAW_BOSS_5993_NATIVE_80_TABLE_ABI_FRONTIER.md)
candidate was **6,085B /1,514 x86, `0x218` stack**:

1. **Modes 35 and 36:** The original calls the inherited auxiliary-scale
   function once at `+0xFC8` / `+0x10B5`, then obtains the **secondary
   color** (`+0xFD6` / `+0x10C3`), **primary color** and real draw count.
   Only after those real arguments does it calculate one `height / 2.0f`,
   call the auxiliary-scale function **again**, and combine the second
   returned scale with that half-height. A separate `height / 2.0f` is
   performed when passing the **width** operand to the renderer. In the
   previous C++ direct call expression MSVC hoisted the width expression
   before the second auxiliary-scale call, introducing extra stack/early
   expression instructions. Native-order `const` locals for **used** color,
   count, half-height and adjusted scale, followed by the actual native
   draw call, restore the two separate native divisions and the correct
   side-effecting function order. The first standalone inherited-scale
   invocation is retained because the original genuinely makes both
   calls; its return value is not fabricated into a used argument.
2. **Modes 29 and 30:** The original obtains the two distinct packed colors
   and the real Animation draw count *before* evaluating the final
   `width ± height / 2.0f` float passed to `draw_shape_43be80`. C++
   argument expressions that mixed side-effecting color getters with that
   independent width expression caused the compiler to move the arithmetic
   earlier, storing a redundant precomputed width. Explicit color/count
   arguments that are truly passed naturally defer the width computation
   until the actual native push sequence.
3. **Mode 46:** The original computes secondary and primary packed color
   fields, draw count, a half-height term and a real inherited auxiliary
   scale/half-height subtraction **before** passing the final independent
   `width - height / 2.0f` argument. Named used values reproduce this
   evaluation ordering without changing its mathematical semantics.
   In contrast, applying the same source structure to **both** mode 45
   and 46 over-shortened the entire candidate by 20B. The stronger
   original-site result is achieved with the existing inline natural
   expression for **mode 45** and explicit evaluation for **mode 46**.

These corrections are semantic source reordering based on actual original
observable calls and operands, not a branch on an exact-match macro or
compiler-specific inert register fillers. The candidate still preserves
all 18 original native `2.0f` relocation-role occurrences and all native
E8 call multiplicities.

## Controlled probe results and rejected assumptions

Every variant below was built only from the same **NONEXACT** source with
one pinned compiler profile, with its private source/object under
`.analysis/core835-draw/` / `build/core835-probe/`. Each probe tests the
**whole function contribution** and its original PE roles, never a
convenient prefix:

| Scoped typed-C++ experiment | Executable bytes | x86 heads | Stack bytes |
| --- | ---: | ---: | ---: |
| Prior CORE/RECON-834 baseline | 6,085 | 1,514 | `0x218` |
| Separate **used** mode35/36 argument lifetimes | 6,045 | 1,508 | `0x210` |
| Also separate **used** mode29/30 color/count arguments | 6,013 | 1,504 | `0x208` |
| Additionally separate both mode45 and mode46 | 5,973 | 1,498 | `0x200` |
| Explicit mode45 only (mode46 unchanged) | 5,993 | 1,501 | `0x204` |
| **Explicit mode46 only (retained)** | **5,993** | **1,501** | **`0x204`** |

Both native-sized candidates are **NONEXACT** despite their identical
executable length, count, frame and 80 after-body pointer positions.
The mode46-only variant matches **86/123 E8 physical sites** versus
**82/123** for mode45-only, and **23/32 body HIGHLOW site-and-target
pairs** versus **22/32** for mode45-only. This is the retained
natural C++ source.

A separate **private rejected diagnostic**, which declared an otherwise
unused C++ variable to force an x87 return-value stack spill, aligned
some additional early E8 locations but supplied no meaningful consumer of
that value. In original mode35 the first inherited-scale call stores an
x87 float to `[ebp-0x160]`, whereas the ordinary standalone call lowers
to `fstp st(0)` in the modern compiler. No independent original consumer
of that stored value has yet been found. The public source deliberately
**does not add an inert compiler-shaping local** merely to mimic an
unconsumed spill. Resolve actual source/ABI lifetime from independent
native evidence before changing it.

## Remaining frontier and focused reproduction

The first original-vs-candidate E8 offset difference is still the original
`+0xFD6` color call in mode35 (candidate `+0xFD2`, four bytes earlier),
due to its preceding x87 spill. Later float expression temporaries,
specific nested-case jump targets and nine physical HIGHLOW sites still
differ, even though the original **final compiler-cookie E8 is physically
aligned**. Next: establish whether the first mode35/36 x87 spill is a
genuine source-owned local or an optimization/language-lowering artifact;
then reconcile late SSE expression **operand and register** ordering with
real per-case drawing arguments. Do not declare the full Boss exact until a
fresh canonical zero-difference replay of the original code, table and
all original relocations passes.

```bash
scripts/repo-python scripts/verify-target.py
scripts/repo-python scripts/verify-animation-draw-boss-native.py
scripts/repo-python scripts/verify-animation-draw-boss-abi.py
nice -n 15 scripts/repo-python scripts/verify-animation-draw-boss-source-roles.py
scripts/repo-python scripts/validate-tracking.py --require-target
scripts/repo-python scripts/report-reconstruction-status.py --summary
scripts/repo-python scripts/build.py --check
```

The only changed native source is `src/AnimationDrawBoss.cpp`, which is
still absent from **all canonical exact match providers**. Only the
**isolated one-source noncanonical MSVC probe** is compiled; no exact
source/header/manifest/compiler/target is modified. **Affected canonical
provider/unit count = 0.** Do not run an unfiltered whole-graph cold
replay for this checkpoint. The full original game-owned exact inventory
remains independently **590 functions /196,671 native .text bytes** with
**1,240 strict units/260 providers**. All past source-proven exact game
functions, including the whole 3,159B quad Boss, retain their independent
strict acceptance.
