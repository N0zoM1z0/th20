# CORE/RECON-302 — entire 1,404-byte Bullet command-11 boss, maintained source frontier

The complete original game-owned `Bullet::advance_command11` at
`0x00481200..0x0048177B` (1,404 bytes / 357 x86 instructions,
SHA-256 `48a4da455a231997829ed66a57a9604d32988b2d8eb604749a935da80f94f546`)
now has a *maintained, independently re-examined* entire C++20 source body:
`src/BulletCommand11.cpp`. This is a source-present **nonexact**
reconstruction, not a canonical strict match; no original parent bytes are
added to `config/matches.csv` and no match unit is registered.

## Revalidated native inputs and algorithm

The immutable Japanese TH20 v1.00a Steamless original has SHA-256
`a274b45fe6ec53511718bb328c2ff169a74e67f95d1b0c74d97d348b955a0897`.
Fresh target-attested Ghidra analysis and independent entire-span Capstone
inspection confirm the full bounds, original Bullet physics caller
`0x00485B60`, and all 12 callee destinations. The behavior is:

1. Decrement the *actual* indexed `ExtendedCommand[11].timer` through the
   native Timer operation, then test its `word_30` and the actual rendered
   sprite's width/height. Only when the bullet is outside the original
   sprite-adjusted screen region is the expensive geometry evaluated.
2. Construct two actual 8-byte `Vector2` values and zero two separate
   four-element float arrays. Compute an XY direction from the Bullet Angle
   with original radius 1.0f. Four screen corner vectors use the true
   signed X `-384/+384`, Y `-448/+448` and 448-centered offset, sprite
   half-size, and bullet position. Preserve each original operation order.
3. Normalize all four vectors using the separately strict 155-byte
   `normalize_vector2`; use the separately strict 50-byte `cross_components`
   and 50-byte `dot_components` functions for each corner. Store x87 float
   results in separate crossing and projection arrays; do not merge their
   storage just to simplify the source.
4. First scan strictly valid crossing-nonpositive/projected-nonnegative
   candidates; then crossing-nonnegative/projected-nonnegative candidates.
   Both running maxima initialize to native -999.0f and use strict
   less-than updates. If either maximum is below -998.0f, clear only Bullet
   command bit `0x100` and return 1. Otherwise, test the actual command
   Timer `at_most(0)`, clear the same flag only if expired, return its
   boolean-as-int value. The two paths have different call/side-effect
   behavior and must not be combined.

All source references are typed current game structs and game geometry APIs;
there is no fabricated byte array for `Bullet`, `Animation` or `Vector2`.
The XY polar operation is declared as an external `polar2(Vector2&,float,float)`
because the original entry at `0x00439330` has the same XY-writing body as
the separately exact `polar(Vector3&,float,float)`. The exact native
*linker-folded symbol ownership and resolution of the new typed alias*
remain an explicit open item, not claimed solved by this source draft.

## Entire-function MSVC evidence, not an exactness claim

Cold-compiled **only** `src/BulletCommand11.cpp` with locked MSVC x86
19.44 `/std:c++20 /Od /Ob0 /GS /Gy /Zl /arch:SSE2 /fp:precise /sdl
/EHsc`; actual single object and receipt are
`build/core302-probes/BulletCommand11-maintained.obj` and its adjacent
`.receipt.json`. Independent original native disassembly has 357 x86
instructions; complete emitted candidate body has 353. Ordered Capstone
instruction mnemonic alignment: **353/357**, with **the only missing four
native instructions** at `+0x105`, `+0x10D`, `+0x112`, `+0x11A`.
They are two `movss` loads of the genuine native 384.0f (`0x0056CDA4`)
and 448.0f (`0x0056D7C0`) followed by two stores to stack frame
`[ebp-0x78]` and `[ebp-0x7C]`. A fresh read of the *entire original
function* independently confirmed those stack locations are never read
again. The retained source emits **1,378 bytes instead of 1,404**, and a
smaller stack frame (`0x74` versus `0x7C`). No inert variable or NOP is
inserted merely to coerce the last 26 bytes and stack layout.

The full original target has **68 direct original relocation sites**:
**33 `REL32` calls and 35 `DIR32` absolute address fields**, derived from
complete original x86 operands rather than from compiler candidate locations.
All **35/35 native DIR32 fields** were independently confirmed against the
original PE `.reloc` `HIGHLOW` table, with zero additional unmapped base
relocations inside this function. The candidate's **66 ordinary COFF
relocations** align **66/66 by original/probe instruction identity, field
offset and type**, with zero disagreements; the missing two originals are
the two 384.0f and 448.0f absolute-address loads. The whole independently
observed set of twelve original callee addresses matches the Ghidra callee
inventory. These data are saved in the ignored private
`.analysis/core302-command11-independent-original-relocations.tsv` and
`.analysis/core302-command11-retained-relocation-alignment.txt`.

Because the candidate is 26 bytes shorter, this is **structural evidence,
not a 1,404-byte exact relocation replay**: original linker symbol ownership
and 1,404-byte strict target bytes still require a separate proof. The four
remaining instructions represent unknown original local-variable source
ownership, not a reason to claim a whole root is solved. The earlier exact
geometry children remain accepted and unmodified.

The new source is a standalone provider using *unchanged* public headers.
No existing exact source/provider was modified; the affected strict
canonical replay scope is therefore **zero existing units**. One isolated
compiler probe and a fresh target/source ledger validation were performed;
no full-graph cold replay was requested or run. The original 12,140-byte
Bullet dispatcher and 3,735-byte emitter remain independent open bosses.
